// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <wil/win32_helpers.h>
#include <iostream>
#include <winrt/Windows.ApplicationModel.Background.h>
#include "WindowsAppRuntime.Test.AppModel.h"
#include <MddBootstrap.h>

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppLifecycle;
    using namespace winrt::Microsoft::Windows::PushNotifications;
    using namespace winrt::Microsoft::Windows::ToastNotifications;
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::Storage;
    using namespace winrt::Windows::Storage::Streams;
    using namespace winrt::Windows::Data::Xml::Dom;
}

winrt::IAsyncOperation<winrt::PushNotificationChannel> RequestChannelAsync()
{
    // To obtain an AAD RemoteIdentifier for your app,
    // follow the instructions on https://docs.microsoft.com/azure/active-directory/develop/quickstart-register-app
    auto channelOperation = winrt::PushNotificationManager::CreateChannelAsync(
        winrt::guid("0160ee84-0c53-4851-9ff2-d7f5a87ed914"));

    // Setup the inprogress event handler
    channelOperation.Progress(
        [](auto&& sender, auto&& args)
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

        // Register Push Event for Foreground
        winrt::event_token token = result.Channel().PushReceived([](const auto&, winrt::PushNotificationReceivedEventArgs const& args)
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

winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel RequestChannel()
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

std::wstring GetEnumString(winrt::ToastNotificationSetting const& setting)
{
    static std::map<winrt::ToastNotificationSetting, std::wstring> enumMapping = {
        { winrt::ToastNotificationSetting::Enabled,  L"Enabled"},
        { winrt::ToastNotificationSetting::DisabledForApplication, L"DisabledForApplication" },
        { winrt::ToastNotificationSetting::DisabledForUser, L"DisabledForUser"},
        { winrt::ToastNotificationSetting::DisabledByGroupPolicy, L"DisabledByGroupPolicy"},
        { winrt::ToastNotificationSetting::DisabledByManifest, L"DisabledByManifest"}
    };
    return enumMapping[setting];
}

winrt::ToastNotification GetToastNotification()
{

    winrt::hstring xmlPayload =
        LR"(<toast launch="action = viewDownload &amp; downloadId = 9438108">
        <visual>
            <binding template = "ToastGeneric">
                <text>Downloading this week's new music...</text>
                <progress
                    title = "{progressTitle}"
                    value = "{progressValue}"
                    valueStringOverride = "{progressValueString}"
                    status = "{progressStatus}" />
            </binding>
        </visual>
    </toast>)";


//    winrt::hstring xmlPayload{ L"<toast>intrepidToast</toast>" };

    winrt::XmlDocument xmlDocument{};
    xmlDocument.LoadXml(xmlPayload);

    return winrt::ToastNotification(xmlDocument);
}

constexpr auto timeout{ std::chrono::seconds(5) };

winrt::ToastProgressResult ProgressResultOperationHelper(winrt::IAsyncOperation<winrt::ToastProgressResult> progressResultOperation)
{
    if (progressResultOperation.wait_for(timeout) != winrt::AsyncStatus::Completed)
    {
        progressResultOperation.Cancel();
        return winrt::ToastProgressResult::Failed; // timed out or failed
    }

    return progressResultOperation.GetResults();
}

winrt::ToastProgressData GetToastProgressData(std::wstring const& status, std::wstring const& title, double const& progressValue, std::wstring const& progressValueString, uint32_t sequenceNumber)
{
    winrt::ToastProgressData progressData{};
    progressData.Status(status);
    progressData.Title(title);
    progressData.Value(progressValue);
    progressData.ValueStringOverride(progressValueString);
    progressData.SequenceNumber(sequenceNumber);

    return progressData;
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

    std::wcout << L"--------------------------------\n";
    std::wcout << L"- Toast Notifications Demo App -\n";
    std::wcout << L"--------------------------------\n\n";

    // Display if app is running as packaged | unpackaged.
    std::wcout << L"Running as " << (isPackaged ? L"packaged.\n\n" : L"unpackaged.\n\n");

    // Grab an instance of ToastNotificationManager
    auto toastNotificationManager{ winrt::ToastNotificationManager::Default() };

    // Display the current ToastNotificationSetting for the app.
    std::wcout << L"Printing ToastNotificationSetting for app: " << GetEnumString(toastNotificationManager.Setting()) << "\n\n";

    winrt::ToastActivationInfo activationInfo{ nullptr };
    // Create toastActivationInfo depending on packaged | unpackaged scenario.
    if (isPackaged)
    {
        std::wcout << L"Calling ToastActivationInfo::CreateFromActivationGuid with ToastActivatorCLSID in manifest...\n";
        activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(winrt::guid("FE8C7374-A28F-4CBE-8D28-4288CBDFD431"));
        std::wcout << L"Done.\n\n";
    }
    else
    {
        std::wcout << L"Calling ToastActivationInfo::CreateFromToastAssets...\n";
        winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });
        activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);
        std::wcout << L"Done.\n\n";
    }

    // Registering app for activation
    std::wcout << L"Calling ToastNotificationManager::RegisterActivator(activationInfo)...\n";
    toastNotificationManager.RegisterActivator(activationInfo);
    std::wcout << L"Done.\n\n";

    // Retrieve the activation event args
   /* auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    // Check if activated from background by ToastActivation
    if (kind == ExtendedActivationKind::AppNotification)
    {
        std::wcout << L"Activated by ToastActivation from background.\n";
        ToastActivatedEventArgs toastArgs{ args.Data().as<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs>() };
        winrt::hstring arguments{ toastArgs.ActivationArgs() };
        std::wcout << arguments.c_str() << std::endl << std::endl;

        IMap<winrt::hstring, winrt::hstring> userInput = toastArgs.UserInput();
        for (auto pair : userInput)
        {
            std::wcout << "Key= " << pair.Key().c_str() << " " << "Value= " << pair.Value().c_str() << L"\n";
        }
        std::wcout << std::endl;
    }

    // Setting up foreground handler for ToastActivation
    std::wcout << L"Registering foreground handler to receive ToastActivationEventArgs...\n";
    winrt::event_token token = toastNotificationManager.ToastActivated([](const auto&, winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs const& toastArgs)
    {
        std::wcout << L"ToastActivation received foreground!\n";
        winrt::hstring arguments{ toastArgs.ActivationArgs() };
        std::wcout << arguments.c_str() << L"\n\n";

        IMap<winrt::hstring, winrt::hstring> userInput{ toastArgs.UserInput() };
        for (auto pair : userInput)
        {
            std::wcout << "Key= " << pair.Key().c_str() << " " << "Value= " << pair.Value().c_str() << L"\n";
        }
        std::wcout << L"\n";
    });
    std::wcout << L"Done.\n\n";

    std::wcout << L"Requesting PushNotificationChannel...\n\n";
    PushNotificationChannel channel{ RequestChannel() }; */

    // Post a toast
    std::wcout << L"Posting a new toast" << std::endl;
    winrt::ToastNotification toast{ GetToastNotification() };

    winrt::hstring tag = L"weekly-playlist";
    winrt::hstring group = L"downloads";

    toast.Tag(tag);
    toast.Group(group);

    winrt::ToastProgressData toastProgressData1 = GetToastProgressData(L"Downloading...", L"Weekly playlist", 0.6, L"15/26 songs", 1);
    toast.ProgressData(toastProgressData1);

    toastNotificationManager.ShowToast(toast);


    Sleep(5000);
    winrt::ToastProgressData toastProgressData2 = GetToastProgressData(L"Downloading...", L"Weekly playlist", 0.7, L"18/26 songs", 2);

    std::wcout << L"Update toast Progress data for a given tag and group" << std::endl;
    auto progressResultOperation = winrt::ToastNotificationManager::Default().UpdateToastProgressDataAsync(toastProgressData2, tag, group);
    auto progressResult = ProgressResultOperationHelper(progressResultOperation);

    if (progressResult == winrt::ToastProgressResult::Succeeded)
    {
        std::wcout << L"Update notification data succeeded" << std::endl;
    }

    std::wcout << L"Press enter to exit the app.\n\n";
    std::cin.ignore();

    // If you want to stop receiving ToastNotifications for the app
    /* toastNotificationManager.UnregisterActivator(); */
    if (!isPackaged)
    {
        MddBootstrapShutdown();
    }
    return 0;
}
