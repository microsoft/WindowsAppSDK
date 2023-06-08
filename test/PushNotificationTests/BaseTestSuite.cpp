// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "PushNotification-Test-Constants.h"
#include "BaseTestSuite.h"

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
using namespace std::literals;
using namespace std::chrono;

void BaseTestSuite::ClassSetup()
{
    ::Test::Bootstrap::Setup();
}

void BaseTestSuite::ClassCleanup()
{
    ::Test::Bootstrap::Cleanup();
}

void BaseTestSuite::MethodSetup()
{
    bool isSelfContained{};
    VERIFY_SUCCEEDED(TestData::TryGetValue(L"SelfContained", isSelfContained));

    if (!isSelfContained)
    {
        ::WindowsAppRuntime::VersionInfo::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
            ::Test::Bootstrap::TP::WindowsAppRuntimeMain::c_PackageFamilyName);
        VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
    }
    else
    {
        ::WindowsAppRuntime::VersionInfo::TestInitialize(L"I_don't_exist_package!", L"I_don't_exist_package!");
        VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
    }
}

void BaseTestSuite::MethodCleanup()
{
    if (!m_unregisteredFully)
    {
        PushNotificationManager::Default().UnregisterAll();
        m_unregisteredFully = true;
    }

    ::WindowsAppRuntime::VersionInfo::TestShutdown();
}

HRESULT BaseTestSuite::ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
{
    if (channelOperation.wait_for(c_timeout) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        channelOperation.Cancel();
        RETURN_WIN32(ERROR_TIMEOUT); // timed out or failed
    }

    auto result{ channelOperation.GetResults() };
    auto status{ result.Status() };
    RETURN_HR_IF(result.ExtendedError(), status != PushNotificationChannelStatus::CompletedSuccess);

    result.Channel().Close();
    return S_OK;
}

void BaseTestSuite::RegisterWithPushNotificationManager()
{
    PushNotificationManager::Default().Register();
    m_unregisteredFully = false;
}

void BaseTestSuite::UnregisterAllWithPushNotificationManager()
{
    PushNotificationManager::Default().UnregisterAll();
    m_unregisteredFully = true;
}

void BaseTestSuite::ChannelRequestUsingNullRemoteId()
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

void BaseTestSuite::ChannelRequestUsingRemoteId()
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

void BaseTestSuite::ChannelRequestCheckExpirationTime()
{
    if (PushNotificationManager::Default().IsSupported())
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
        VERIFY_SUCCEEDED(ChannelRequestHelper(channelOperation));

        auto channel{ channelOperation.GetResults().Channel() };
        auto expirationTime{ channel.ExpirationTime() };

        auto expiryLowerBound{ winrt::clock::now() };
        auto expiryUpperBound{ expiryLowerBound + (hours(24) * 30) + minutes(1) };

        // Need to add 30 days to match expiration time.
        VERIFY_IS_GREATER_THAN(expirationTime, expiryLowerBound);
        VERIFY_IS_LESS_THAN(expirationTime, expiryUpperBound);
    }
    else
    {
        auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
        VERIFY_ARE_EQUAL(ChannelRequestHelper(channelOperation), E_FAIL);
    }
}

// Currently failing - https://github.com/microsoft/WindowsAppSDK/issues/2392
void BaseTestSuite::MultipleChannelClose()
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

void BaseTestSuite::VerifyRegisterAndUnregister()
{
    RegisterWithPushNotificationManager();

    PushNotificationManager::Default().Unregister();
}

void BaseTestSuite::VerifyUnregisterFails()
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

void BaseTestSuite::VerifyUnregisterAllFails()
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

void BaseTestSuite::VerifyRegisterAndUnregisterAll()
{
    RegisterWithPushNotificationManager();
    UnregisterAllWithPushNotificationManager();
}

void BaseTestSuite::MultipleRegister()
{
    RegisterWithPushNotificationManager();
    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().Register(), HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED));
    }
    else
    {
        PushNotificationManager::Default().Register();
    }
}

void BaseTestSuite::VerifyMultipleRegisterAndUnregister()
{
    RegisterWithPushNotificationManager();

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

void BaseTestSuite::VerifyMultipleRegisterAndUnregisterAll()
{
    RegisterWithPushNotificationManager();
    UnregisterAllWithPushNotificationManager();

    RegisterWithPushNotificationManager();
    UnregisterAllWithPushNotificationManager();
}

void BaseTestSuite::VerifyUnregisterTwice()
{
    RegisterWithPushNotificationManager();

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

void BaseTestSuite::VerifyUnregisterAllTwice()
{
    RegisterWithPushNotificationManager();
    UnregisterAllWithPushNotificationManager();

    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().UnregisterAll(), E_UNEXPECTED);
    }
    else
    {
        PushNotificationManager::Default().UnregisterAll();
    }
}

void BaseTestSuite::VerifyUnregisterAndUnregisterAll()
{
    RegisterWithPushNotificationManager();
    PushNotificationManager::Default().Unregister();
    UnregisterAllWithPushNotificationManager();
}

void BaseTestSuite::VerifyForegroundHandlerSucceeds()
{
    PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
    RegisterWithPushNotificationManager();
}

void BaseTestSuite::VerifyForegroundHandlerFails()
{
    RegisterWithPushNotificationManager();
    if (PushNotificationManager::Default().IsSupported())
    {
        VERIFY_THROWS_HR(PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {}), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
    }
    else
    {
        PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
    }
}
