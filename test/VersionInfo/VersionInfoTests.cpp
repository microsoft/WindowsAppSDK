// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

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
    };
}
