// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include <iostream>
#include <sstream>
#include <wil/win32_helpers.h>
#include <winrt/Windows.ApplicationModel.Background.h> // we need this for BackgroundTask APIs
#include "WindowsAppRuntime.Test.AppModel.h"

using namespace winrt;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Windows::PushNotifications;
using namespace winrt::Microsoft::Windows::AppNotifications;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;

constexpr auto c_timeout{ std::chrono::seconds(300) };
inline const winrt::hstring c_rawNotificationPayload = L"rawNotificationValue";

HRESULT ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
{
    if (channelOperation.wait_for(c_timeout) != AsyncStatus::Completed)
    {
        channelOperation.Cancel();
        return HRESULT_FROM_WIN32(ERROR_TIMEOUT); // timed out or failed
    }

    auto result = channelOperation.GetResults();
    auto status = result.Status();
    if (status != PushNotificationChannelStatus::CompletedSuccess)
    {
        return result.ExtendedError(); // did not produce a channel
    }

    result.Channel().Close();
    return S_OK;
}

int main() try
{
    bool testResult = false;
    ::Test::Bootstrap::SetupBootstrap();

    // Test hook to ensure that the app is not self-contained
    WindowsAppRuntime::VersionInfo::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                                                   ::Test::Bootstrap::TP::WindowsAppRuntimeMain::c_PackageFamilyName);

    auto scope_exit = wil::scope_exit([&] {
        ::WindowsAppRuntime::VersionInfo::TestShutdown();
        ::Test::Bootstrap::CleanupBootstrap();
        });

    event_token pushToken{ PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& args)
    {
        auto payload = args.Payload();

        // Do stuff to process the raw payload
        std::wstring payloadString(payload.begin(), payload.end());
        return c_rawNotificationPayload == payloadString;
    }) };

    event_token appNotificationToken{ AppNotificationManager::Default().NotificationInvoked([](const auto&, AppNotificationActivatedEventArgs const& toastArgs)
    {
        hstring argument{ toastArgs.Argument() };
        IMap<hstring, hstring> userInput { toastArgs.UserInput() };
        return 0;
    }) };

    PushNotificationManager::Default().Register();
    AppNotificationManager::Default().Register();

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Push)
    {
        PushNotificationReceivedEventArgs pushArgs = args.Data().as<PushNotificationReceivedEventArgs>();
        auto payload = pushArgs.Payload();
        std::wstring payloadString(payload.begin(), payload.end());

        testResult = payloadString == c_rawNotificationPayload;
        return testResult;
    }
    else if (kind == ExtendedActivationKind::AppNotification)
    {
        AppNotificationActivatedEventArgs appNotificationArgs{ args.Data().as<AppNotificationActivatedEventArgs>() };
        hstring argument{ appNotificationArgs.Argument() };
        IMap<hstring, hstring> arguments{ appNotificationArgs.Arguments() };
        return 0;
    }

    return testResult ? 0 : 1; // We want 0 to be success and 1 failure
}
catch (...)
{
    std::cout << winrt::to_string(winrt::to_message()) << std::endl;
    return 1; // in the event of unhandled test crash
}
