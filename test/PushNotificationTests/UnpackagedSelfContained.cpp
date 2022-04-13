// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <TestDef.h>
#include "UnpackagedSelfContainedTests.h"

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


namespace Test::PushNotifications
{
    HRESULT UnpackagedSelfContainedTests::ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
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

    void UnpackagedSelfContainedTests::ChannelRequestUsingNullRemoteId()
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(winrt::guid()) };
        VERIFY_ARE_EQUAL(ChannelRequestHelper(channelOperation), E_FAIL);
    }

    void UnpackagedSelfContainedTests::ChannelRequestUsingRemoteId()
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
        VERIFY_ARE_EQUAL(ChannelRequestHelper(channelOperation), E_FAIL);
    }

    // Currently failing - https://github.com/microsoft/WindowsAppSDK/issues/2392
    void UnpackagedSelfContainedTests::MultipleChannelClose()
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

    void UnpackagedSelfContainedTests::VerifyRegisterAndUnregister()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.Register();
        pushNotificationManager.Unregister();
    }

    void UnpackagedSelfContainedTests::VerifyUnregisterFails()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.Unregister();
    }

    void UnpackagedSelfContainedTests::VerifyUnregisterAllFails()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.UnregisterAll();
    }

    void UnpackagedSelfContainedTests::VerifyRegisterAndUnregisterAll()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.Register();
        pushNotificationManager.UnregisterAll();
    }

    void UnpackagedSelfContainedTests::MultipleRegister()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.Register();
        pushNotificationManager.Register();
    }

    void UnpackagedSelfContainedTests::VerifyMultipleRegisterAndUnregister()
    {
        PushNotificationManager::Default().Register();
        PushNotificationManager::Default().Unregister();
        PushNotificationManager::Default().Register();
    }

    void UnpackagedSelfContainedTests::VerifyMultipleRegisterAndUnregisterAll()
    {
        PushNotificationManager::Default().Register();
        PushNotificationManager::Default().UnregisterAll();

        PushNotificationManager::Default().Register();
        PushNotificationManager::Default().UnregisterAll();
    }

    void UnpackagedSelfContainedTests::VerifyUnregisterTwice()
    {
        PushNotificationManager::Default().Register();
        PushNotificationManager::Default().Unregister();
        PushNotificationManager::Default().Unregister();
    }

    void UnpackagedSelfContainedTests::VerifyUnregisterAllTwice()
    {
        PushNotificationManager::Default().Register();
        PushNotificationManager::Default().UnregisterAll();
        PushNotificationManager::Default().UnregisterAll();
    }

    void UnpackagedSelfContainedTests::VerifyUnregisterAndUnregisterAll()
    {
        PushNotificationManager::Default().Register();
        PushNotificationManager::Default().Unregister();
        PushNotificationManager::Default().UnregisterAll();
    }

    void UnpackagedSelfContainedTests::VerifyForegroundHandlerSucceeds()
    {
        PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
        PushNotificationManager::Default().Register();
    }

    void UnpackagedSelfContainedTests::VerifyForegroundHandlerFails()
    {
        PushNotificationManager::Default().Register();
        PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
    }
}
