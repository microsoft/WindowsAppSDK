// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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
            // We need to find Microsoft.WindowsAppRuntime.Bootstrap.dll.
            // Normally it's colocated with the application (i.e. same dir as the exe)
            // but that's not true of our test project (a dll) in our build environment
            // (different directories). So we'll explicitly find and load it so the
            // rest of our test is fine
            auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
            wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
            const auto lastError{ GetLastError() };
            VERIFY_IS_NOT_NULL(bootstrapDll.get(), WEX::Common::String().Format(L"LastError: %d (0x%X)", lastError, lastError));

            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_WindowsAppRuntimeFramework();
            TP::RemovePackage_FrameworkWidgets();
            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();
            TP::AddPackage_WindowsAppRuntimeFramework();
            TP::AddPackage_DynamicDependencyDataStore();
            TP::AddPackage_DynamicDependencyLifetimeManager();

            m_bootstrapDll = std::move(bootstrapDll);

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                              Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                              Test::Packages::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                              Test::Packages::WindowsAppRuntimeMain::c_PackageNamePrefix));

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
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_WindowsAppRuntimeFramework();

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

    class LifetimeManagementTests_Elevated : LifetimeManagementTests
    {
    public:
        BEGIN_TEST_CLASS(LifetimeManagementTests_Elevated)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup_Elevated)
        {
            return Setup();
        }

        TEST_CLASS_CLEANUP(Cleanup_Elevated)
        {
            return Cleanup();
        }

        TEST_METHOD(GC_Found0_Elevated)
        {
            GC_Found0();
        }

        TEST_METHOD(GC_Found1_Elevated)
        {
            GC_Found1();
        }

        TEST_METHOD(GC_Found2_Elevated)
        {
            GC_Found2();
        }
    };
}

wil::unique_hmodule Test::DynamicDependency::LifetimeManagementTests::m_bootstrapDll;
