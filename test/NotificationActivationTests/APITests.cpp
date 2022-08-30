// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include <TlHelp32.h>
#include "NotificationActivationCallback.h"
#include "NotificationActivation.Test.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System;
using namespace NotificationActivation::TestFunctions;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Windows::PushNotifications;
using namespace winrt::Microsoft::Windows::AppNotifications;


namespace Test::NotificationActivation
{
    class ActivationTests
    {

    public:
        BEGIN_TEST_CLASS(ActivationTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        static const int testWaitTime()
        {
            return 3000;
        }

        static PCWSTR GetTestPackageFile()
        {
            return L"NotificationActivationPackage";
        }

        static PCWSTR GetTestPackageFullName()
        {
            return L"NotificationActivationPackage_1.0.0.0_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";
        }

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages();
            TP::WapProj::AddPackage(TAEF::GetDeploymentDir(), GetTestPackageFile(), L".msix"); // Installs NotificationActivationPackage.msix
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            TP::RemovePackage(GetTestPackageFullName());
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            return true;
        }

        TEST_METHOD(AppNotificationForeground)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"NotificationActivation-AppxManifest.xml")
                END_TEST_METHOD_PROPERTIES();

            bool notificationReceived{};
            winrt::event_token appNotificationToken{ AppNotificationManager::Default().NotificationInvoked([&](const auto&, AppNotificationActivatedEventArgs const& toastArgs)
            {
                winrt::hstring argument{ toastArgs.Argument() };
                // IMap<hstring, hstring> userInput { toastArgs.UserInput() };
                VERIFY_ARE_EQUAL(argument, c_appNotificationArgument);

                notificationReceived = true;
            }) };

            AppNotificationManager::Default().Register();

            auto toastActivationCallback{ winrt::create_instance<INotificationActivationCallback>(c_taefAppNotificationComServerId, CLSCTX_ALL) };
            // Returns after payload delivered to foreground handler
            VERIFY_SUCCEEDED(toastActivationCallback->Activate(c_appNotificationFakeAUMID.c_str(), c_appNotificationArgument.c_str(), nullptr, 0));

            VERIFY_IS_TRUE(notificationReceived);
        }

        TEST_METHOD(AppNotificationBackground)
        {
            RunTest(L"AppNotificationBackgroundTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto event{ CreateTestEvent(c_testNotificationPhaseEventName) };
            auto toastActivationCallback{ winrt::create_instance<INotificationActivationCallback>(c_appNotificationComServerId, CLSCTX_ALL) };
            VERIFY_SUCCEEDED(toastActivationCallback->Activate(c_appNotificationFakeAUMID.c_str(), c_appNotificationArgument.c_str(), nullptr, 0));

            wil::unique_event failed{ CreateTestEvent(c_testFailureEventName) };
            WaitForEvent(event, failed);
        }

        TEST_METHOD(PushNotificationForeground)
        {
            // Need to incorporate COM server work for PushNotification foreground handling.
        }

        TEST_METHOD(PushNotificationBackground)
        {
            RunTest(L"PushNotificationBackgroundTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto event{ CreateTestEvent(c_testNotificationPhaseEventName) };

            auto localBackgroundTask{ winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_pushNotificationComServerId, CLSCTX_ALL) };
            auto mockBackgroundTaskInstance{ winrt::make<MockBackgroundTaskInstance>() };
            VERIFY_NO_THROW(localBackgroundTask.Run(mockBackgroundTaskInstance));

            wil::unique_event failed{ CreateTestEvent(c_testFailureEventName) };
            WaitForEvent(event, failed);
        }
    };
}
