// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <TestDef.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::Windows::PushNotifications;

class BaseTestSuite
{
    public:
        // Unit test environment functions
        void ClassSetup();
        void ClassCleanup();
        void MethodSetup();
        void MethodCleanup();

        // Base unit tests
        void ChannelRequestUsingNullRemoteId();
        void ChannelRequestCheckExpirationTime();
        void ChannelRequestUsingRemoteId();
        void MultipleChannelClose(); // Currently failing
        void VerifyRegisterAndUnregister();
        void VerifyRegisterAndUnregisterAll();
        void VerifyUnregisterFails();
        void VerifyUnregisterAllFails();
        void MultipleRegister();
        void VerifyMultipleRegisterAndUnregister();
        void VerifyMultipleRegisterAndUnregisterAll();
        void VerifyUnregisterTwice();
        void VerifyUnregisterAllTwice();
        void VerifyUnregisterAndUnregisterAll();
        void VerifyForegroundHandlerSucceeds();
        void VerifyForegroundHandlerFails();

    private:
        HRESULT ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation);
        void RegisterWithPushNotificationManager();
        void UnregisterAllWithPushNotificationManager();

        bool m_unregisteredFully{ true };
};
