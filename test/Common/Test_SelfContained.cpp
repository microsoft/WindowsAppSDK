// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::Common
{
    class SelfContainedTests
    {
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
            auto cleanup = wil::scope_exit([&] {
                ::WindowsAppRuntime::VersionInfo::TestShutdown();
                ::TB::CleanupBootstrap();
            });
            const auto c_doesNotExistPackageFamilyName{ L"Test.PackageFamilyName.DoesNotExist_1234567890abc" };
            ::WindowsAppRuntime::VersionInfo::TestInitialize(c_doesNotExistPackageFamilyName, c_doesNotExistPackageFamilyName);

            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }

        TEST_METHOD(Unpackaged_SelfContained_No)
        {
            {
                ::TB::SetupBootstrap();
                auto cleanup = wil::scope_exit([&]{
                    ::WindowsAppRuntime::VersionInfo::TestShutdown();
                    ::TB::CleanupBootstrap();
                });
                WindowsAppRuntime::VersionInfo::TestInitialize(::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                                                               ::TP::WindowsAppRuntimeMain::c_PackageFamilyName);

                VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
            }
        }

        TEST_METHOD(Unpackaged_SelfContained)
        {
            ::TB::SetupBootstrap();
            auto cleanup = wil::scope_exit([&] {
                ::WindowsAppRuntime::VersionInfo::TestShutdown();
                ::TB::CleanupBootstrap();
            });
            const auto c_doesNotExistPackageFamilyName{ L"Test.PackageFamilyName.DoesNotExist_1234567890abc" };
            WindowsAppRuntime::VersionInfo::TestInitialize(c_doesNotExistPackageFamilyName, c_doesNotExistPackageFamilyName);
            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());

            WindowsAppRuntime::VersionInfo::TestInitialize(::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                                                           ::TP::WindowsAppRuntimeMain::c_PackageFamilyName);
            VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
            WindowsAppRuntime::VersionInfo::TestInitialize(c_doesNotExistPackageFamilyName, c_doesNotExistPackageFamilyName);

            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }
    };
}
