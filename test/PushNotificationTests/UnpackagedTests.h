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
    class UnpackagedTests
    {
    private:
        HRESULT ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation);

        bool m_registered{ false };
    public:
        BEGIN_TEST_CLASS(UnpackagedTests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK Push Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
            END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::Setup();
            ::WindowsAppRuntime::SelfContained::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::Cleanup();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            if (m_registered)
            {
                PushNotificationManager::Default().UnregisterAll();
                m_registered = false;
            }

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
