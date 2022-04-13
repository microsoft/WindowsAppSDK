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

namespace Test::PushNotifications
{
    class UnpackagedSelfContainedTests
    {
    private:
        HRESULT ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation);

    public:
        BEGIN_TEST_CLASS(UnpackagedSelfContainedTests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK Push Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::Cleanup();
            return true;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId);
        TEST_METHOD(ChannelRequestUsingRemoteId);
        TEST_METHOD(MultipleChannelClose); // Currently failing
        TEST_METHOD(VerifyRegisterAndUnregister);
        TEST_METHOD(VerifyRegisterAndUnregisterAll);
        TEST_METHOD(VerifyUnregisterFails);
        TEST_METHOD(VerifyUnregisterAllFails);
        TEST_METHOD(MultipleRegister);
        TEST_METHOD(VerifyMultipleRegisterAndUnregister);
        TEST_METHOD(VerifyMultipleRegisterAndUnregisterAll);
        TEST_METHOD(VerifyUnregisterTwice);
        TEST_METHOD(VerifyUnregisterAllTwice);
        TEST_METHOD(VerifyUnregisterAndUnregisterAll);
        TEST_METHOD(VerifyForegroundHandlerSucceeds);
        TEST_METHOD(VerifyForegroundHandlerFails);
    };
}
