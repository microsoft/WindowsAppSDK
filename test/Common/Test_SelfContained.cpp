// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MddWin11.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::Common
{
    class SelfContainedTests
    {
    private:
        void CommonTestInitialize(PCWSTR testFrameworkPackageFamilyName, PCWSTR testMainPackageFamilyName)
        {
            // For Windows 11 newer versions, the TestInitialize will fail fast if we pass a non null package family name.
            if (MddCore::Win11::IsSupported())
            {
                testMainPackageFamilyName = nullptr;
            }

            ::WindowsAppRuntime::VersionInfo::TestInitialize(testFrameworkPackageFamilyName, testMainPackageFamilyName);
        }

    public:
        BEGIN_TEST_CLASS(SelfContainedTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            END_TEST_CLASS()

            TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::CleanupPackages();
            return true;
        }

        TEST_METHOD(Unpackaged_SelfContained_Yes)
        {
            ::TB::SetupBootstrap();
            auto cleanup = wil::scope_exit([&]
            {
                ::WindowsAppRuntime::VersionInfo::TestShutdown();
                ::TB::CleanupBootstrap();
            });


            const auto c_doesNotExistPackageFamilyName{ L"Test.PackageFamilyName.DoesNotExist_1234567890abc" };
            PCWSTR testFrameworkPackageFamilyName{ c_doesNotExistPackageFamilyName };
            PCWSTR testMainPackageFamilyName{ c_doesNotExistPackageFamilyName };

            CommonTestInitialize(testFrameworkPackageFamilyName, testMainPackageFamilyName);

            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }

        TEST_METHOD(Unpackaged_SelfContained_No)
        {
            ::TB::SetupBootstrap();
            auto cleanup = wil::scope_exit([&]
            {
                ::WindowsAppRuntime::VersionInfo::TestShutdown();
                ::TB::CleanupBootstrap();
            });

            PCWSTR testFrameworkPackageFamilyName{ ::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName };
            PCWSTR testMainPackageFamilyName{ ::Test::Bootstrap::TP::WindowsAppRuntimeMain::c_PackageFamilyName };

            CommonTestInitialize(testFrameworkPackageFamilyName, testMainPackageFamilyName);

            VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }

        TEST_METHOD(Unpackaged_SelfContained)
        {
            ::TB::SetupBootstrap();
            auto cleanup = wil::scope_exit([&]
            {
                ::WindowsAppRuntime::VersionInfo::TestShutdown();
                ::TB::CleanupBootstrap();
            });
            const auto c_doesNotExistPackageFamilyName{ L"Test.PackageFamilyName.DoesNotExist_1234567890abc" };
            CommonTestInitialize(c_doesNotExistPackageFamilyName, c_doesNotExistPackageFamilyName);
            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());

            CommonTestInitialize(::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                                                           ::TP::WindowsAppRuntimeMain::c_PackageFamilyName);
            VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
            CommonTestInitialize(c_doesNotExistPackageFamilyName, c_doesNotExistPackageFamilyName);

            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }
    };
}
