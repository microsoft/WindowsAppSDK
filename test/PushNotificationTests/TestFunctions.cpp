#include "pch.h"

#include "TestFunctions.h"
#include "pch.h"
#include <TestDef.h>
#include "MockBackgroundTaskInstance.h"
#include <TlHelp32.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;
using namespace winrt::Microsoft::Windows::PushNotifications;

#define VERIFY_THROWS_HR(expression, hr)        \
        VERIFY_THROWS_SPECIFIC(expression,          \
            winrt::hresult_error,                   \
            [&](winrt::hresult_error e) -> bool     \
            {                                       \
                return (e.code() == hr);    \
            })

HRESULT ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
{
    if (channelOperation.wait_for(c_timeout) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        channelOperation.Cancel();
        return HRESULT_FROM_WIN32(ERROR_TIMEOUT); // timed out or failed
    }

    auto result{ channelOperation.GetResults() };
    auto status{ result.Status() };
    if (status != PushNotificationChannelStatus::CompletedSuccess)
    {
        return result.ExtendedError(); // did not produce a channel
    }

    result.Channel().Close();
    return S_OK;
}

void TestFunctions::ChannelRequestUsingNullRemoteId()
{
    VERIFY_THROWS_HR(PushNotificationManager::Default().CreateChannelAsync(winrt::guid()).get(), E_INVALIDARG);
}

void TestFunctions::ChannelRequestUsingRemoteId()
{
    auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
    VERIFY_SUCCEEDED(ChannelRequestHelper(channelOperation));
}

// Currently failing.
void TestFunctions::MultipleChannelClose()
{
    auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
    if (channelOperation.wait_for(c_timeout) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        channelOperation.Cancel();
        VERIFY_FAIL(L"Channel request hit timeout.");
    }

    auto result{ channelOperation.GetResults() };
    VERIFY_ARE_EQUAL(result.Status(), PushNotificationChannelStatus::CompletedSuccess);

    result.Channel().Close();
    VERIFY_THROWS_HR(result.Channel().Close(), WPN_E_CHANNEL_CLOSED);
}

void TestFunctions::VerifyRegisterAndUnregister()
{
    auto pushNotificationManager{ PushNotificationManager::Default() };
    pushNotificationManager.Register();
    pushNotificationManager.Unregister();
}

void TestFunctions::VerifyRegisterAndUnregisterAll()
{
    auto pushNotificationManager{ PushNotificationManager::Default() };
    pushNotificationManager.Register();
    pushNotificationManager.UnregisterAll();
}

void TestFunctions::MultipleRegister()
{
    auto pushNotificationManager{ PushNotificationManager::Default() };
    pushNotificationManager.Register();
    VERIFY_THROWS_HR(pushNotificationManager.Register(), HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED));
}

void TestFunctions::VerifyMultipleRegisterAndUnregister()
{
    PushNotificationManager::Default().Register();
    PushNotificationManager::Default().Unregister();
    VERIFY_THROWS_HR(PushNotificationManager::Default().Register(), HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED));
}

void TestFunctions::VerifyMultipleRegisterAndUnregisterAll()
{
    PushNotificationManager::Default().Register();
    PushNotificationManager::Default().UnregisterAll();

    PushNotificationManager::Default().Register();
    PushNotificationManager::Default().UnregisterAll();
}

void TestFunctions::VerifyUnregisterTwice()
{
    PushNotificationManager::Default().Register();
    PushNotificationManager::Default().Unregister();
    VERIFY_THROWS_HR(PushNotificationManager::Default().Unregister(), E_UNEXPECTED);

}

void TestFunctions::VerifyUnregisterAll()
{
    PushNotificationManager::Default().Register();
    PushNotificationManager::Default().UnregisterAll();
}

void TestFunctions::VerifyUnregisterAllTwice()
{
    PushNotificationManager::Default().Register();
    PushNotificationManager::Default().UnregisterAll();
    VERIFY_THROWS_HR(PushNotificationManager::Default().UnregisterAll(), E_UNEXPECTED);
}

void TestFunctions::VerifyUnregisterAndUnregisterAll()
{
    PushNotificationManager::Default().Register();
    PushNotificationManager::Default().Unregister();
    PushNotificationManager::Default().UnregisterAll();
}

void TestFunctions::VerifyForegroundHandlerSucceeds()
{
    PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
    PushNotificationManager::Default().Register();
}

void TestFunctions::VerifyForegroundHandlerFails()
{
    PushNotificationManager::Default().Register();
    VERIFY_THROWS_HR(PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {}), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
}

