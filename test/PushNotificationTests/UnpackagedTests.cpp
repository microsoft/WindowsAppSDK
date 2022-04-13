// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <TestDef.h>
#include "UnpackagedTests.h"

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
    HRESULT UnpackagedTests::ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
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

    void UnpackagedTests::ChannelRequestUsingNullRemoteId()
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().CreateChannelAsync(winrt::guid()).get(), E_INVALIDARG);
    }

    void UnpackagedTests::ChannelRequestUsingRemoteId()
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
        VERIFY_SUCCEEDED(ChannelRequestHelper(channelOperation));
    }

    // Currently failing - https://github.com/microsoft/WindowsAppSDK/issues/2392
    void UnpackagedTests::MultipleChannelClose()
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

    void UnpackagedTests::VerifyRegisterAndUnregister()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.Register();
        m_registered = true;

        pushNotificationManager.Unregister();
    }

    void UnpackagedTests::VerifyUnregisterFails()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        VERIFY_THROWS_HR(pushNotificationManager.Unregister(), E_UNEXPECTED);
    }

    void UnpackagedTests::VerifyUnregisterAllFails()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        VERIFY_THROWS_HR(pushNotificationManager.UnregisterAll(), E_UNEXPECTED);
    }

    void UnpackagedTests::VerifyRegisterAndUnregisterAll()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.Register();
        m_registered = true;

        pushNotificationManager.UnregisterAll();
        m_registered = false;
    }

    void UnpackagedTests::MultipleRegister()
    {
        auto pushNotificationManager{ PushNotificationManager::Default() };
        pushNotificationManager.Register();
        m_registered = true;

        VERIFY_THROWS_HR(pushNotificationManager.Register(), HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED));
    }

    void UnpackagedTests::VerifyMultipleRegisterAndUnregister()
    {
        PushNotificationManager::Default().Register();
        m_registered = true;

        PushNotificationManager::Default().Unregister();
        VERIFY_THROWS_HR(PushNotificationManager::Default().Register(), HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED));
    }

    void UnpackagedTests::VerifyMultipleRegisterAndUnregisterAll()
    {
        PushNotificationManager::Default().Register();
        m_registered = true;

        PushNotificationManager::Default().UnregisterAll();
        m_registered = false;

        PushNotificationManager::Default().Register();
        m_registered = true;

        PushNotificationManager::Default().UnregisterAll();
        m_registered = false;
    }

    void UnpackagedTests::VerifyUnregisterTwice()
    {
        PushNotificationManager::Default().Register();
        m_registered = true;

        PushNotificationManager::Default().Unregister();
        VERIFY_THROWS_HR(PushNotificationManager::Default().Unregister(), E_UNEXPECTED);
    }

    void UnpackagedTests::VerifyUnregisterAllTwice()
    {
        PushNotificationManager::Default().Register();
        m_registered = true;

        PushNotificationManager::Default().UnregisterAll();
        m_registered = false;

        VERIFY_THROWS_HR(PushNotificationManager::Default().UnregisterAll(), E_UNEXPECTED);
    }

    void UnpackagedTests::VerifyUnregisterAndUnregisterAll()
    {
        PushNotificationManager::Default().Register();
        m_registered = true;

        PushNotificationManager::Default().Unregister();
        PushNotificationManager::Default().UnregisterAll();
        m_registered = false;
    }

    void UnpackagedTests::VerifyForegroundHandlerSucceeds()
    {
        PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
        PushNotificationManager::Default().Register();
        m_registered = true;
    }

    void UnpackagedTests::VerifyForegroundHandlerFails()
    {
        PushNotificationManager::Default().Register();
        m_registered = true;

        VERIFY_THROWS_HR(PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {}), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
    }
}
