// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include "pch.h"
#include <wil/win32_helpers.h>
#include <iostream>
#include <winrt/Windows.ApplicationModel.Background.h>
#include "WindowsAppRuntime.Test.AppModel.h"
#include <MddBootstrap.h>
#include <MddBootstrapTest.h>
#include <winrt/Windows.Data.Xml.Dom.h>

#include <propkey.h> //PKEY properties
#include <propsys.h>
#include <ShObjIdl_core.h>

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppLifecycle;
    using namespace winrt::Microsoft::Windows::PushNotifications;
    using namespace winrt::Microsoft::Windows::AppNotifications;
    using namespace winrt::Microsoft::Windows::AppNotifications::Builder;
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::Storage;
    using namespace winrt::Windows::Data::Xml::Dom;
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

std::wstring GetEnumString(winrt::AppNotificationSetting const& setting)
{
    static std::map<winrt::AppNotificationSetting, std::wstring> enumMapping = {
        { winrt::AppNotificationSetting::Enabled,  L"Enabled"},
        { winrt::AppNotificationSetting::DisabledForApplication, L"DisabledForApplication" },
        { winrt::AppNotificationSetting::DisabledForUser, L"DisabledForUser"},
        { winrt::AppNotificationSetting::DisabledByGroupPolicy, L"DisabledByGroupPolicy"},
        { winrt::AppNotificationSetting::DisabledByManifest, L"DisabledByManifest"},
        { winrt::AppNotificationSetting::Unsupported, L"Unsupported"}
    };
    return enumMapping[setting];
}

winrt::AppNotification CreateToastNotification()
{
    winrt::hstring payload =
        LR"(<toast launch="action = viewDownload &amp; downloadId = 9438108">
        <visual>
            <binding template = "ToastGeneric">
                <text>Downloading this week's new music...</text>
            </binding>
        </visual>
    </toast>)";
    return winrt::AppNotification(payload);
}

bool PostToastHelper(std::wstring const& tag, std::wstring const& group)
{
    winrt::AppNotification toast{ CreateToastNotification() };

    toast.Tag(tag.c_str());
    toast.Group(group.c_str());

    auto builder{ winrt::AppNotificationBuilder().AddArgument(L"key", L"value").AddArgument(L"key", L"value").SetTag(tag.c_str()).SetGroup(group.c_str())};

    winrt::AppNotificationManager::Default().Show(builder.BuildNotification());

    if (toast.Id() == 0)
    {
        return false;
    }

    return true;
}

int main()
{
    // Retrieve the app scenario.
    bool isPackaged{ Test::AppModel::IsPackagedProcess() };
    if (!isPackaged)
    {
        constexpr PCWSTR c_PackageNamePrefix{ L"WindowsAppRuntime.Test.DDLM" };
        constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
        constexpr PCWSTR c_FrameworkPackageFamilyName = L"Microsoft.WindowsAppRuntime.Framework-4.1_8wekyb3d8bbwe";
        constexpr PCWSTR c_MainPackageFamilyName = L"WindowsAppRuntime.Test.DynDep.DataStore-4.1_8wekyb3d8bbwe";
        RETURN_IF_FAILED(MddBootstrapTestInitialize(c_PackageNamePrefix, c_PackagePublisherId, c_FrameworkPackageFamilyName, c_MainPackageFamilyName));

        // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
        const UINT32 c_Version_MajorMinor{ 0x00040001 };
        const PACKAGE_VERSION minVersion{};
        RETURN_IF_FAILED(MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

        // Not mandatory, but it's highly recommended to specify AppUserModelId
        THROW_IF_FAILED(SetCurrentProcessExplicitAppUserModelID(L"TestAppId"));
    }

    std::wcout << L"--------------------------------\n";
    std::wcout << L"- App Notifications Demo App -\n";
    std::wcout << L"--------------------------------\n\n";

    // Display if app is running as packaged | unpackaged.
    std::wcout << L"Running as " << (isPackaged ? L"packaged.\n\n" : L"unpackaged.\n\n");

    // Grab an instance of AppNotificationManager
    auto appNotificationManager{ winrt::AppNotificationManager::Default() };

    // Setting up foreground handler for AppNotification
    std::wcout << L"Registering foreground handler to receive AppNotificationActivatedEventArgs...\n";
    winrt::event_token token = appNotificationManager.NotificationInvoked([](const auto&, winrt::AppNotificationActivatedEventArgs const& toastArgs)
        {
            std::wcout << L"AppNotification received foreground!\n";
            winrt::hstring argument{ toastArgs.Argument() };
            std::wcout << argument.c_str() << L"\n\n";

            winrt::IMap<winrt::hstring, winrt::hstring> arguments{ toastArgs.Arguments() };
            for (auto pair : arguments)
            {
                std::wcout << "Key= " << pair.Key().c_str() << " " << "Value= " << pair.Value().c_str() << L"\n";
            }
            std::wcout << L"\n";
        });

    std::wcout << L"Done.\n\n";

    // Display the current AppNotificationSetting for the app.
    std::wcout << L"Printing AppNotificationSetting for app: " << GetEnumString(appNotificationManager.Setting()) << "\n\n";

    // Registering app for activation
    std::wcout << L"Calling AppNotificationManager::Register()...\n";
    appNotificationManager.Register();
    std::wcout << L"Done.\n\n";

    // Retrieve the activation event args
    auto args = winrt::AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    // Check if activated from background by AppNotification
    if (kind == winrt::ExtendedActivationKind::AppNotification)
    {
        std::wcout << L"Activated by AppNotification from background.\n";
        winrt::AppNotificationActivatedEventArgs appNotificationArgs{ args.Data().as<winrt::AppNotificationActivatedEventArgs>() };
        winrt::hstring argument{ appNotificationArgs.Argument() };
        std::wcout << argument.c_str() << std::endl << std::endl;

        winrt::IMap<winrt::hstring, winrt::hstring> arguments = appNotificationArgs.Arguments();
        for (auto pair : arguments)
        {
            std::wcout << "Key= " << pair.Key().c_str() << " " << "Value= " << pair.Value().c_str() << L"\n";
        }
        std::wcout << std::endl;
    }

    std::wcout << L"Requesting PushNotificationChannel...\n\n";
    winrt::PushNotificationChannel channel{ RequestChannel() };

    std::wcout << L"Post a Toast..." << std::endl;
    PostToastHelper(L"Tag", L"Group");
    std::wcout << L"Done.\n\n";

    std::wcout << L"Press enter to exit the app.\n\n";
    std::cin.ignore();

    // Call Unregister so that COM can launch a new process for ToastInvokes after we terminate this process.
    appNotificationManager.Unregister();
    if (!isPackaged)
    {
        MddBootstrapShutdown();
    }
    return 0;
}
