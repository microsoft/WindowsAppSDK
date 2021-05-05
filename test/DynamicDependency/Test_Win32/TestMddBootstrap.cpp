// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddBootstrap.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

namespace Test::DynamicDependency
{
    class BootstrapTests
    {
    public:
        BEGIN_TEST_CLASS(BootstrapTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup)
        {
            // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
            // Normally it's colocated with the application (i.e. same dir as the exe)
            // but that's not true of our test project (a dll) in our build environment
            // (different directories). So we'll explicitly find and load it so the
            // rest of our test is fine
            auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
            wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
            const auto lastError{ GetLastError() };
            VERIFY_IS_NOT_NULL(bootstrapDll.get());

            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_ProjectReunionFramework();
            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();
            TP::AddPackage_ProjectReunionFramework();
            TP::AddPackage_DynamicDependencyLifetimeManager();

            m_bootstrapDll = std::move(bootstrapDll);

            return true;
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            m_bootstrapDll.reset();

            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_ProjectReunionFramework();

            return true;
        }

        TEST_METHOD(Initialize_DDLMNotFound)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Major.Minor = 0.0 == No such framework package
            const UINT32 doesNotExist{};
            const PACKAGE_VERSION minVersionMatchAny{};
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(doesNotExist, nullptr, minVersionMatchAny));
        }

        TEST_METHOD(Initialize_DDLMMinVersionNoMatch)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Version <major>.65535.65535.65535 to find framework packages for the major.minor version but none meeting this minVersion criteria
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            PACKAGE_VERSION minVersionNoMatch{ static_cast<UINT64>(Test::Packages::DynamicDependencyLifetimeManager::c_Version.Major) << 48 | 0x0000FFFFFFFFFFFFuI64 };
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_NO_MATCH), MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersionNoMatch));
        }

        TEST_METHOD(Initialize)
        {
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

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
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, nullptr, nullptr, nullptr)));
            }
            {
                UINT32 count{};
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, nullptr, nullptr, &count)));
            }

            {
                UINT32 bufferLength{ 1 };
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, nullptr, nullptr)));
            }
            {
                UINT32 bufferLength{ 1 };
                UINT32 count{};
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, nullptr, &count)));
            }

            {
                BYTE buffer[1]{};
                UINT32 bufferLength{ static_cast<UINT32>(ARRAYSIZE(buffer)) };
                VERIFY_ARE_EQUAL(E_INVALIDARG, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(c_filter, &bufferLength, buffer, nullptr)));
            }
        }

        TEST_METHOD(GetCurrentPackageInfo_NotPackaged)
        {
            VerifyGetCurrentPackageInfo();

            winrt::hstring packageFamilyName{ Test::Packages::DynamicDependencyLifetimeManager::c_PackageFamilyName };
            auto applicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

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

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

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
            VERIFY_ARE_EQUAL(expectedHR, HRESULT_FROM_WIN32(::GetCurrentPackageInfo(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC, &bufferLength, nullptr, &count)));
            VERIFY_ARE_EQUAL(expectedCount, count);
            if (minExpectedBufferLength > 0)
            {
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"GetCurrentPackageInfo() expectedBufferLength>=%u bufferLength=%u", minExpectedBufferLength, bufferLength) };
                VERIFY_IS_TRUE(bufferLength >= minExpectedBufferLength, message.get());
            }
            else
            {
                VERIFY_ARE_EQUAL(0u, bufferLength);
            }
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::BootstrapTests::m_bootstrapDll;
