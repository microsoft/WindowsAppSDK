// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <TestDef.h>
#include "Base.h"

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

void Base::ClassSetup()
{
    ::Test::Bootstrap::Setup();
    bool isSelfContained{ false };
    if (SUCCEEDED(TestData::TryGetValue(L"SelfContained", isSelfContained)))
    {
        if (!isSelfContained)
        {
            ::WindowsAppRuntime::SelfContained::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);
        }
    }
}

void Base::ClassCleanup()
{
    ::Test::Bootstrap::Cleanup();
}

void Base::MethodCleanup()
{
    if (m_registered)
    {
        PushNotificationManager::Default().UnregisterAll();
        m_registered = false;
    }
}

HRESULT Base::ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
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

void Base::ChannelRequestUsingNullRemoteId()
{
    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().CreateChannelAsync(winrt::guid()).get(), E_INVALIDARG);
    }
    else
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(winrt::guid()) };
        VERIFY_ARE_EQUAL(ChannelRequestHelper(channelOperation), E_FAIL);
    }
}

void Base::ChannelRequestUsingRemoteId()
{
    if (PushNotificationManager::Default().IsSupported())
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
        VERIFY_SUCCEEDED(ChannelRequestHelper(channelOperation));
    }
    else
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
        VERIFY_ARE_EQUAL(ChannelRequestHelper(channelOperation), E_FAIL);
    }
}

// Currently failing - https://github.com/microsoft/WindowsAppSDK/issues/2392
void Base::MultipleChannelClose()
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

void Base::VerifyRegisterAndUnregister()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    PushNotificationManager::Default().Unregister();
}

void Base::VerifyUnregisterFails()
{
    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().Unregister(), E_UNEXPECTED);
    }
    else
    {
        PushNotificationManager::Default().Unregister();
    }
}

void Base::VerifyUnregisterAllFails()
{
    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().UnregisterAll(), E_UNEXPECTED);
    }
    else
    {
        PushNotificationManager::Default().UnregisterAll();
    }
}

void Base::VerifyRegisterAndUnregisterAll()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    PushNotificationManager::Default().UnregisterAll();
    m_registered = false;
}

void Base::MultipleRegister()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().Register(), HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED));
    }
    else
    {
        PushNotificationManager::Default().Register();
    }
}

void Base::VerifyMultipleRegisterAndUnregister()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    PushNotificationManager::Default().Unregister();

    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().Register(), HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED));
    }
    else
    {
        PushNotificationManager::Default().Register();
    }
}

void Base::VerifyMultipleRegisterAndUnregisterAll()
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

void Base::VerifyUnregisterTwice()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    PushNotificationManager::Default().Unregister();
    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().Unregister(), E_UNEXPECTED);
    }
    else
    {
        PushNotificationManager::Default().Unregister();
    }
}

void Base::VerifyUnregisterAllTwice()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    PushNotificationManager::Default().UnregisterAll();
    m_registered = false;

    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().UnregisterAll(), E_UNEXPECTED);
    }
    else
    {
        PushNotificationManager::Default().UnregisterAll();
    }
}

void Base::VerifyUnregisterAndUnregisterAll()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    PushNotificationManager::Default().Unregister();
    PushNotificationManager::Default().UnregisterAll();
    m_registered = false;
}

void Base::VerifyForegroundHandlerSucceeds()
{
    PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
    PushNotificationManager::Default().Register();
    m_registered = true;
}

void Base::VerifyForegroundHandlerFails()
{
    PushNotificationManager::Default().Register();
    m_registered = true;

    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {}), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
    }
    else
    {
        PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
    }
}
