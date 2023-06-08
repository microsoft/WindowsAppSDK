// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <wil/win32_helpers.h>
#include <iostream>
#include <winrt/Windows.ApplicationModel.Background.h>
#include <MddBootstrap.h>
#include <MddBootstrapTest.h>
#include <propkey.h> //PKEY properties
#include <propsys.h>
#include <ShObjIdl_core.h>
#include <roapi.h>
#include <winstring.h>
#include <wil/resource.h>
#include "AppModel.PackageGraph.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppLifecycle;
    using namespace winrt::Microsoft::Windows::PushNotifications;
    using namespace winrt::Microsoft::Windows::AppNotifications;
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Storage;
    using namespace winrt::Windows::Storage::Streams;
}

winrt::IAsyncOperation<winrt::PushNotificationChannel> RequestChannelAsync()
{
    // To obtain an AAD RemoteIdentifier for your app,
    // follow the instructions on https://docs.microsoft.com/azure/active-directory/develop/quickstart-register-app
    auto channelOperation = winrt::PushNotificationManager::Default().CreateChannelAsync(
        winrt::guid("cea1342d-8293-4acb-b18a-ed8b0d6f7d6c"));

    // Setup the inprogress event handler
    channelOperation.Progress(
        [](auto&& /*sender*/, auto&& args)
        {
            if (args.status == winrt::PushNotificationChannelStatus::InProgress)
            {
                // This is basically a noop since it isn't really an error state
                std::cout << "Channel request is in progress." << std::endl << std::endl;
            }
            else if (args.status == winrt::PushNotificationChannelStatus::InProgressRetry)
            {
                LOG_HR_MSG(
                    args.extendedError,
                    "The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it. RetryCount = %d",
                    args.retryCount);
            }
        });

    auto result = co_await channelOperation;

    if (result.Status() == winrt::PushNotificationChannelStatus::CompletedSuccess)
    {
        auto channelUri = result.Channel().Uri();

        std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl << std::endl;

        auto channelExpiry = result.Channel().ExpirationTime();

        // Caller's responsibility to keep the channel alive
        co_return result.Channel();
    }
    else if (result.Status() == winrt::PushNotificationChannelStatus::CompletedFailure)
    {
        LOG_HR_MSG(result.ExtendedError(), "We hit a critical non-retryable error with channel request!");
        co_return nullptr;
    }
    else
    {
        LOG_HR_MSG(result.ExtendedError(), "Some other failure occurred.");
        co_return nullptr;
    }

};

winrt::PushNotificationChannel RequestChannel()
{
    auto task = RequestChannelAsync();
    if (task.wait_for(std::chrono::seconds(300)) != winrt::AsyncStatus::Completed)
    {
        task.Cancel();
        return nullptr;
    }

    auto result = task.GetResults();
    return result;
}

int main()
{
    Test::Bootstrap::SetupBootstrap();
    ::WindowsAppRuntime::VersionInfo::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
        ::Test::Bootstrap::TP::WindowsAppRuntimeMain::c_PackageFamilyName);

    THROW_HR_IF(E_FAIL, ::WindowsAppRuntime::SelfContained::IsSelfContained());

    if (!Test::AppModel::IsPackagedProcess())
    {
        // Not mandatory, but it's highly recommended to specify AppUserModelId
        THROW_IF_FAILED(SetCurrentProcessExplicitAppUserModelID(L"PushTestAppId"));
    }

    // Register Push Event for Foreground
    winrt::event_token token = winrt::PushNotificationManager::Default().PushReceived([](const auto&, winrt::PushNotificationReceivedEventArgs const& args)
        {
            auto payload = args.Payload();

            // Do stuff to process the raw payload
            std::string payloadString(payload.begin(), payload.end());
            std::cout << "Push notification content received from FOREGROUND: " << payloadString << std::endl << std::endl;
        });

    winrt::AppNotificationManager::Default().Register();

    winrt::PushNotificationManager::Default().Register();

    auto args = winrt::AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();
    if (kind == winrt::ExtendedActivationKind::Push)
    {
        winrt::PushNotificationReceivedEventArgs pushArgs = args.Data().as<winrt::PushNotificationReceivedEventArgs>();

        // Call GetDeferral to ensure that code runs in low power
        auto deferral = pushArgs.GetDeferral();

        auto payload = pushArgs.Payload();

        // Do stuff to process the raw payload
        std::string payloadString(payload.begin(), payload.end());
        printf("Push notification content received from BACKGROUND: %s\n", payloadString.c_str());
        printf("Press 'Enter' to exit the App.");

        // Call Complete on the deferral when finished processing the payload.
        // This removes the override that kept the app running even when the system was in a low power mode.
        deferral.Complete();
        std::cin.ignore();
    }
    else if (kind == winrt::ExtendedActivationKind::AppNotification)
    {
        winrt::AppNotificationActivatedEventArgs appActivatedArgs = args.Data().as<winrt::AppNotificationActivatedEventArgs>();
        printf("App activated from AppNotification!\n");
        std::cin.ignore();
    }
    else if (kind == winrt::ExtendedActivationKind::Launch)
    {
        winrt::PushNotificationChannel channel = RequestChannel();
        printf("Press 'Enter' at any time to exit App.");
        std::cin.ignore();
    }
    else if (kind == winrt::ExtendedActivationKind::ToastNotification)
    {
        printf("ToastNotification received!");
        printf("Press 'Enter' at any time to exit App.");
        std::cin.ignore();
    }

    winrt::PushNotificationManager::Default().Unregister();

    winrt::AppNotificationManager::Default().Unregister();
    if (!Test::AppModel::IsPackagedProcess())
    {
        MddBootstrapShutdown();
    }

    return 0;
}
