// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>

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

class Base
{
    public:
        Base() = default;

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

        bool m_registered{ false };
};
