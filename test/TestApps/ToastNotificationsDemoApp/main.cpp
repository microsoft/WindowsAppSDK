// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
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
        { winrt::AppNotificationSetting::DisabledByManifest, L"DisabledByManifest"}
    };
    return enumMapping[setting];
}

winrt::AppNotification CreateToastNotification(winrt::hstring message)
{
    winrt::hstring xmlPayload{ L"<toast>" + message + L"</toast>" };
    return winrt::AppNotification(xmlPayload);
}

winrt::AppNotification CreateToastNotification()
{
    return CreateToastNotification(L"intrepidToast");
}

bool PostToastHelper(std::wstring const& tag, std::wstring const& group)
{
    winrt::AppNotification toast{ CreateToastNotification() };

    toast.Tag(tag.c_str());
    toast.Group(group.c_str());

    winrt::AppNotificationManager::Default().Show(toast);

    if (toast.Id() == 0)
    {
        return false;
    }

    return true;
}

// This function is intended to be called in the unpackaged scenario.
void SetDisplayNameAndIcon() noexcept try
{
    // Not mandatory, but it's highly recommended to specify AppUserModelId
    THROW_IF_FAILED(SetCurrentProcessExplicitAppUserModelID(L"TestAppId"));

    // Icon is mandatory
    winrt::com_ptr<IPropertyStore> propertyStore;
    wil::unique_hwnd hWindow{ GetConsoleWindow() };

    THROW_IF_FAILED(SHGetPropertyStoreForWindow(hWindow.get(), IID_PPV_ARGS(&propertyStore)));

    wil::unique_prop_variant propVariantIcon;
    wil::unique_cotaskmem_string sth = wil::make_unique_string<wil::unique_cotaskmem_string>(LR"(%SystemRoot%\system32\@WLOGO_96x96.png)");
    propVariantIcon.pwszVal = sth.release();
    propVariantIcon.vt = VT_LPWSTR;
    THROW_IF_FAILED(propertyStore->SetValue(PKEY_AppUserModel_RelaunchIconResource, propVariantIcon));

    // App name is not mandatory, but it's highly recommended to specify it
    wil::unique_prop_variant propVariantAppName;
    wil::unique_cotaskmem_string prodName = wil::make_unique_string<wil::unique_cotaskmem_string>(L"The Toast Demo App");
    propVariantAppName.pwszVal = prodName.release();
    propVariantAppName.vt = VT_LPWSTR;
    THROW_IF_FAILED(propertyStore->SetValue(PKEY_AppUserModel_RelaunchDisplayNameResource, propVariantAppName));
}
CATCH_LOG()

int main()
{
    // Retrieve the app scenario.
    bool isPackaged{ Test::AppModel::IsPackagedProcess() };
    if (!isPackaged)
    {
        constexpr PCWSTR c_PackageNamePrefix{ L"WindowsAppRuntime.Test.DDLM" };
        constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
        RETURN_IF_FAILED(MddBootstrapTestInitialize(c_PackageNamePrefix, c_PackagePublisherId));

        // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
        const UINT32 c_Version_MajorMinor{ 0x00040001 };
        const PACKAGE_VERSION minVersion{};
        RETURN_IF_FAILED(MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

        SetDisplayNameAndIcon();
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
            winrt::hstring arguments{ toastArgs.ActivationArgs() };
            std::wcout << arguments.c_str() << L"\n\n";

            winrt::IMap<winrt::hstring, winrt::hstring> userInput{ toastArgs.UserInput() };
            for (auto pair : userInput)
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
        winrt::hstring arguments{ appNotificationArgs.ActivationArgs() };
        std::wcout << arguments.c_str() << std::endl << std::endl;

        winrt::IMap<winrt::hstring, winrt::hstring> userInput = appNotificationArgs.UserInput();
        for (auto pair : userInput)
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
