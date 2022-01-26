// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <wil/win32_helpers.h>
#include <iostream>
#include <winrt/Windows.ApplicationModel.Background.h>
#include "WindowsAppRuntime.Test.AppModel.h"
#include <MddBootstrap.h>

using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Windows::PushNotifications;
using namespace winrt::Microsoft::Windows::ToastNotifications;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;

winrt::Windows::Foundation::IAsyncOperation<PushNotificationChannel> RequestChannelAsync()
{
    // To obtain an AAD RemoteIdentifier for your app,
    // follow the instructions on https://docs.microsoft.com/azure/active-directory/develop/quickstart-register-app
    auto channelOperation = PushNotificationManager::CreateChannelAsync(
        winrt::guid("0160ee84-0c53-4851-9ff2-d7f5a87ed914"));

    // Setup the inprogress event handler
    channelOperation.Progress(
        [](auto&& sender, auto&& args)
        {
            if (args.status == PushNotificationChannelStatus::InProgress)
            {
                // This is basically a noop since it isn't really an error state
                std::cout << "Channel request is in progress." << std::endl << std::endl;
            }
            else if (args.status == PushNotificationChannelStatus::InProgressRetry)
            {
                LOG_HR_MSG(
                    args.extendedError,
                    "The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it. RetryCount = %d",
                    args.retryCount);
            }
        });

    auto result = co_await channelOperation;

    if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
    {
        auto channelUri = result.Channel().Uri();

        std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl << std::endl;

        auto channelExpiry = result.Channel().ExpirationTime();

        // Register Push Event for Foreground
        winrt::event_token token = result.Channel().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& args)
            {
                auto payload = args.Payload();

                // Do stuff to process the raw payload
                std::string payloadString(payload.begin(), payload.end());
                std::cout << "Push notification content received from FOREGROUND: " << payloadString << std::endl << std::endl;
                args.Handled(true);
            });
        // Caller's responsibility to keep the channel alive
        co_return result.Channel();
    }
    else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
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

winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel RequestChannel()
{
    auto task = RequestChannelAsync();
    if (task.wait_for(std::chrono::seconds(300)) != AsyncStatus::Completed)
    {
        task.Cancel();
        return nullptr;
    }

    auto result = task.GetResults();
    return result;
}

std::wstring GetEnumString(ToastNotificationSetting const& setting)
{
    static std::map<ToastNotificationSetting, std::wstring> enumMapping = {
        { ToastNotificationSetting::Enabled,  L"Enabled"},
        { ToastNotificationSetting::DisabledForApplication, L"DisabledForApplication" },
        { ToastNotificationSetting::DisabledForUser, L"DisabledForUser"},
        { ToastNotificationSetting::DisabledByGroupPolicy, L"DisabledByGroupPolicy"},
        { ToastNotificationSetting::DisabledByManifest, L"DisabledByManifest"}
    };
    return enumMapping[setting];
}

int main()
{
    // Retrieve the app scenario.
    bool isPackaged{ Test::AppModel::IsPackagedProcess() };
    if (!isPackaged)
    {
        // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
        const UINT32 c_Version_MajorMinor{ 0x00040001 };
        const PACKAGE_VERSION minVersion{};
        RETURN_IF_FAILED(MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));
    }

    std::wcout << L"--------------------------------" << std::endl;
    std::wcout << L"- Toast Notifications Demo App -" << std::endl;
    std::wcout << L"--------------------------------" << std::endl << std::endl;

    // Display if app is running as packaged | unpackaged.
    std::wcout << L"Running as " << (isPackaged ? L"packaged." : L"unpackaged.") << std::endl << std::endl;

    // Grab an instance of ToastNotificationManager
    auto toastNotificationManager{ ToastNotificationManager::Default() };

    // Display the current ToastNotificationSetting for the app.
    std::wcout << L"Printing ToastNotificationSetting for app: " << GetEnumString(toastNotificationManager.Setting()) << std::endl << std::endl;

    ToastActivationInfo activationInfo{ nullptr };
    // Create toastActivationInfo depending on packaged | unpackaged scenario.
    if (isPackaged)
    {
        std::wcout << L"Calling ToastActivationInfo::CreateFromActivationGuid with nitro activation guid..." << std::endl;
        activationInfo = ToastActivationInfo::CreateFromActivationGuid(winrt::guid("FE8C7374-A28F-4CBE-8D28-4288CBDFD431"));
        std::wcout << L"Done." << std::endl << std::endl;
    }
    else
    {
        std::wcout << L"Calling ToastActivationInfo::CreateFromToastAssets..." << std::endl;
        ToastAssets assets(L"ToastNotificationApp", Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });
        activationInfo = ToastActivationInfo::CreateFromToastAssets(assets);
        std::wcout << L"Done." << std::endl << std::endl;
    }

    // Registering app for activation
    std::wcout << L"Calling ToastNotificationManager::RegisterActivator(activationInfo)..." << std::endl;
    toastNotificationManager.RegisterActivator(activationInfo);
    std::wcout << L"Done." << std::endl << std::endl;

    // Retrieve the activation event args
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    // Check if activated from background by ToastActivation
    if (kind == ExtendedActivationKind::AppNotification)
    {
        std::wcout << L"Activated by ToastActivation from background." << std::endl;
        ToastActivatedEventArgs toastArgs{ args.Data().as<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs>() };
        winrt::hstring arguments{ toastArgs.ActivationArgs() };
        std::wcout << arguments.c_str() << std::endl << std::endl;

        IMap<winrt::hstring, winrt::hstring> userInput = toastArgs.UserInput();
        for (auto pair : userInput)
        {
            std::wcout << "Key= " << pair.Key().c_str() << " " << "Value= " << pair.Value().c_str() << std::endl;
        }
        std::wcout << std::endl;
    }

    // Setting up foreground handler for ToastActivation
    std::wcout << L"Registering foreground handler to receive ToastActivationEventArgs..." << std::endl;
    winrt::event_token token = toastNotificationManager.ToastActivated([](const auto&, winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs const& toastArgs)
    {
        printf("ToastActivation received foreground!\n");
        winrt::hstring arguments{ toastArgs.ActivationArgs() };
        std::wcout << arguments.c_str() << std::endl << std::endl;

        IMap<winrt::hstring, winrt::hstring> userInput{ toastArgs.UserInput() };
        for (auto pair : userInput)
        {
            std::wcout << "Key= " << pair.Key().c_str() << " " << "Value= " << pair.Value().c_str() << std::endl;
        }
        std::wcout << std::endl;
    });
    std::wcout << L"Done." << std::endl << std::endl;

    std::wcout << L"Requesting PushNotificationChannel..." << std::endl << std::endl;
    PushNotificationChannel channel{ RequestChannel() };

    std::wcout << L"Press enter to exit the app." << std::endl << std::endl;
    std::cin.ignore();

    // If you want to stop receiving ToastNotifications for the app
    /* toastNotificationManager.UnregisterActivator(); */
    if (!isPackaged)
    {
        MddBootstrapShutdown();
    }
    return 0;
}
