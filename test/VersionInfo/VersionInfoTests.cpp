// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MddWin11.h>
#include <WindowsAppRuntime.SelfContained.h>
#include <WindowsAppRuntime.VersionInfo.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::VersionInfo
{
    class VersionInfoTests
    {
    public:
        BEGIN_TEST_CLASS(VersionInfoTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(VersionInfo_Release)
        {
            using ReleaseInfo = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::ReleaseInfo;

            VERIFY_ARE_EQUAL(uint16_t{}, ReleaseInfo::Major());
            VERIFY_ARE_EQUAL(uint16_t{}, ReleaseInfo::Minor());
            VERIFY_ARE_EQUAL(uint16_t{}, ReleaseInfo::Patch());
            VERIFY_IS_TRUE(ReleaseInfo::VersionTag().empty());
            VERIFY_ARE_EQUAL(L"0.0.0", ReleaseInfo::AsString());
        }

        TEST_METHOD(VersionInfo_Runtime)
        {
            using RuntimeInfo = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeInfo;

            const auto version{ RuntimeInfo::Version() };
            VERIFY_ARE_EQUAL(uint16_t{}, version.Major);
            VERIFY_ARE_EQUAL(uint16_t{}, version.Minor);
            VERIFY_ARE_EQUAL(uint16_t{}, version.Build);
            VERIFY_ARE_EQUAL(uint16_t{}, version.Revision);
            VERIFY_IS_TRUE(RuntimeInfo::AsString().empty());
        }

        TEST_METHOD(VersionInfo_SelfContained)
        {
            // Bootstrap injects the framework package family name, bypassing the resource lookup.
            // Clear it to verify the module location still identifies framework deployment.
            auto restoreTestInitialization{ wil::scope_exit([] {
                if (MddCore::Win11::IsSupported())
                {
                    ::WindowsAppRuntime::VersionInfo::TestInitialize(
                        TP::WindowsAppRuntimeFramework::c_PackageFamilyName);
                }
                else
                {
                    ::WindowsAppRuntime::VersionInfo::TestInitialize(
                        TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                        TP::WindowsAppRuntimeMain::c_PackageFamilyName);
                }
            }) };

            ::WindowsAppRuntime::VersionInfo::TestShutdown();
            VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }
    };
}
