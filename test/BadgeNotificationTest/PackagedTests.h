// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt::Microsoft::Windows::BadgeNotifications;

class PackagedTests
{
    BEGIN_TEST_CLASS(PackagedTests)
        TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")
        TEST_CLASS_PROPERTY(L"Data:SelfContained", L"{true, false}")
        TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
        TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCWA")
        TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"BadgeNotifications-AppxManifest.xml")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
    {
        ::Test::Bootstrap::Setup();
        return true;
    }

    TEST_CLASS_CLEANUP(ClassUninit)
    {
        ::Test::Bootstrap::Cleanup();
        return true;
    }

    TEST_METHOD_SETUP(MethodInit)
    {
        bool isSelfContained{};
        VERIFY_SUCCEEDED(TestData::TryGetValue(L"SelfContained", isSelfContained));

        if (!isSelfContained)
        {
            ::WindowsAppRuntime::VersionInfo::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                                                            ::Test::Bootstrap::TP::WindowsAppRuntimeMain::c_PackageFamilyName);
            VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }
        else
        {
            ::WindowsAppRuntime::VersionInfo::TestInitialize(L"I_don't_exist_package!", L"I_don't_exist_package!");
            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }
        return true;
    }

    TEST_METHOD_CLEANUP(MethodUninit)
    {
        BadgeNotificationManager::Current().ClearBadge();

        ::WindowsAppRuntime::VersionInfo::TestShutdown();
        return true;
    }

    TEST_METHOD(VerifyBadgeNotificationManagerCurrent);
};

