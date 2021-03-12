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

            winrt::uninit_apartment();
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

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::BootstrapTests::m_bootstrapDll;
