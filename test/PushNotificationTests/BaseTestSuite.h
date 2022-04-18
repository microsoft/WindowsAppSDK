// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
        void MethodCleanup();

        // Base unit tests
        void ChannelRequestUsingNullRemoteId();
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

        bool m_registered{};
};
