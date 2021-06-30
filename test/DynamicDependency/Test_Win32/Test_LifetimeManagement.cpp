// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddLifetimeManagement.h>
#include <MddLifetimeManagementTest.h>

#include <MddBootstrap.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

namespace Test::DynamicDependency
{
    class LifetimeManagementTests
    {
    public:
        BEGIN_TEST_CLASS(LifetimeManagementTests)
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

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

            VERIFY_ARE_EQUAL(S_OK, MddLifetimeManagementTestInitialize(Test::Packages::DynamicDependencyLifetimeManagerGC::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManagerGC::c_PackagePublisherId));

            return true;
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            MddBootstrapShutdown();

            m_bootstrapDll.reset();

            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_ProjectReunionFramework();

            return true;
        }

        TEST_METHOD(GC_Found0)
        {
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();

            VERIFY_IS_FALSE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName));
            VERIFY_IS_FALSE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName));

            VERIFY_ARE_EQUAL(S_OK, MddLifetimeManagementGC());

            VERIFY_IS_FALSE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName));
            VERIFY_IS_FALSE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName));
        }

        TEST_METHOD(GC_Found1)
        {
            TP::AddPackageIfNecessary_DynamicDependencyLifetimeManagerGC1000();
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();

            VERIFY_IS_TRUE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName));
            VERIFY_IS_FALSE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName));

            VERIFY_ARE_EQUAL(S_OK, MddLifetimeManagementGC());

            VERIFY_IS_TRUE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName));
            VERIFY_IS_FALSE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName));
        }

        TEST_METHOD(GC_Found2)
        {
            TP::AddPackageIfNecessary_DynamicDependencyLifetimeManagerGC1000();
            TP::AddPackageIfNecessary_DynamicDependencyLifetimeManagerGC1010();

            VERIFY_IS_TRUE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName));
            VERIFY_IS_TRUE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName));

            VERIFY_ARE_EQUAL(S_OK, MddLifetimeManagementGC());

            VERIFY_IS_TRUE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1000::c_PackageFullName));
            VERIFY_IS_TRUE(TP::IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManagerGC1010::c_PackageFullName));
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::LifetimeManagementTests::m_bootstrapDll;
