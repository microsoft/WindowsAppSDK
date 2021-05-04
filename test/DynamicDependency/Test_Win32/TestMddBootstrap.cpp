// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddBootstrap.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test::DynamicDependency
{
    TEST_CLASS(BootstrapTests)
    {
    public:

        TEST_CLASS_INITIALIZE(Setup)
        {
            // CppUnitTest initializes COM as STA before we get called
            // But we don't need (or want) STA, and we do want MTA. We can't
            // stop CppUnitTest from initializing COM but we can uninitialize
            // it and (re)initialize it as MTA. Don't think of it as crude
            // and brutish but rather 'thinking outside the box'...
            COM::CoSuperInitialize();

            // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
            // Normally it's colocated with the application (i.e. same dir as the exe)
            // but that's not true of our test project (a dll) in our build environment
            // (different directories). So we'll explicitly find and load it so the
            // rest of our test is fine
            auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
            wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
            const auto lastError{ GetLastError() };
            Assert::IsNotNull(bootstrapDll.get());

            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_ProjectReunionFramework();
            TP::AddPackage_ProjectReunionFramework();
            TP::AddPackage_DynamicDependencyLifetimeManager();

            m_bootstrapDll = std::move(bootstrapDll);
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            m_bootstrapDll.reset();

            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_ProjectReunionFramework();

            // Undo COM::CoSuperInitialize() and restore the thread to its initial state
            // as when CppUnitTest  called us. Or as close as we can get to it
            winrt::uninit_apartment();
            winrt::init_apartment(winrt::apartment_type::single_threaded);
        }

        TEST_METHOD(Initialize_DDLMNotFound)
        {
            Assert::AreEqual(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Version 0.0.0.0 == Major version 0 == No such framework package
            const PACKAGE_VERSION doesNotExist{};
            Assert::AreEqual(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(doesNotExist));
        }

        TEST_METHOD(Initialize_DDLMMinVersionNoMatch)
        {
            Assert::AreEqual(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Version <major>.65535.65535.65535 to find framework packages for the major version but none meeting this minVersion criteria
            PACKAGE_VERSION minVersionNoMatch{ static_cast<UINT64>(Test::Packages::DynamicDependencyLifetimeManager::c_Version.Major) << 48 | 0x0000FFFFFFFFFFFFuI64 };
            Assert::AreEqual(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(minVersionNoMatch));
        }

        TEST_METHOD(Initialize)
        {
            Assert::AreEqual(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Version <major>.0.0.0 to find any framework package for this major version
            PACKAGE_VERSION minVersion{ static_cast<UINT64>(Test::Packages::DynamicDependencyLifetimeManager::c_Version.Major) << 48 };
            Assert::AreEqual(S_OK, MddBootstrapInitialize(minVersion));

            MddBootstrapShutdown();
        }

        TEST_METHOD(ShutdownWithoutInitialize)
        {
            MddBootstrapShutdown();
            MddBootstrapShutdown();
        }

        TEST_METHOD(GetCurrentPackageInfo_NotPackaged_InvalidParameter)
        {
            const UINT32 c_filter{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };

            {
                Assert::AreEqual(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, nullptr, nullptr, nullptr)));
            }
            {
                UINT32 count{};
                Assert::AreEqual(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, nullptr, nullptr, &count)));
            }

            {
                UINT32 bufferLength{ 1 };
                Assert::AreEqual(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, nullptr, nullptr)));
            }
            {
                UINT32 bufferLength{ 1 };
                UINT32 count{};
                Assert::AreEqual(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, nullptr, &count)));
            }

            {
                BYTE buffer[1]{};
                UINT32 bufferLength{ static_cast<UINT32>(ARRAYSIZE(buffer)) };
                Assert::AreEqual(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, buffer, nullptr)));
            }
        }

        TEST_METHOD(GetCurrentPackageInfo_NotPackaged)
        {
            VerifyGetCurrentPackageInfo();

            winrt::hstring packageFamilyName{ Test::Packages::DynamicDependencyLifetimeManager::c_PackageFamilyName };
            auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };

            Assert::AreEqual(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Version <major>.0.0.0 to find any framework package for this major version
            PACKAGE_VERSION minVersion{ static_cast<UINT64>(Test::Packages::DynamicDependencyLifetimeManager::c_Version.Major) << 48 };
            Assert::AreEqual(S_OK, MddBootstrapInitialize(minVersion));

            VerifyGetCurrentPackageInfo(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 700);

            winrt::Windows::ApplicationModel::AppExtensions::AppExtensionCatalog::Open(L"Does.Not.Exist");

            MddBootstrapShutdown();

            VerifyGetCurrentPackageInfo();
        }

#if defined(TODO_EnableAfterConvertingToTAEF)
        TEST_METHOD(GetCurrentPackageInfo_Packaged)
        {
            VerifyGetCurrentPackageInfo();

            winrt::hstring packageFamilyName{ Test::Packages::DynamicDependencyLifetimeManager::c_PackageFamilyName };
            auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };

            Assert::AreEqual(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Version <major>.0.0.0 to find any framework package for this major version
            PACKAGE_VERSION minVersion{ static_cast<UINT64>(Test::Packages::DynamicDependencyLifetimeManager::c_Version.Major) << 48 };
            Assert::AreEqual(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddBootstrapInitialize(minVersion));

            VerifyGetCurrentPackageInfo();
        }
#endif

    private:
        static void VerifyGetCurrentPackageInfo(
            const HRESULT expectedHR = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE),
            const UINT32 expectedCount = 0,
            const UINT32 minExpectedBufferLength = 0)
        {
            UINT32 bufferLength{};
            UINT32 count{};
            Assert::AreEqual(expectedHR, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC, &bufferLength, nullptr, &count)));
            Assert::AreEqual(expectedCount, count);
            if (minExpectedBufferLength > 0)
            {
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"GetCurrentPackageInfo() expectedBufferLength>=%u bufferLength=%u", minExpectedBufferLength, bufferLength) };
                Assert::IsTrue(bufferLength >= minExpectedBufferLength, message.get());
            }
            else
            {
                Assert::AreEqual(0u, bufferLength);
            }
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::BootstrapTests::m_bootstrapDll;
