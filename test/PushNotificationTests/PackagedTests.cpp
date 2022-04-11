// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "MockBackgroundTaskInstance.h"
#include <TlHelp32.h>
#include "TestFunctions.h"

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
    class PackagedTests
    {

    public:
        BEGIN_TEST_CLASS(PackagedTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"PushNotifications-AppxManifest.xml")
            TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCWA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            ::WindowsAppRuntime::SelfContained::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            // Need to keep each TEST_METHOD in clean state.
            try
            {
                PushNotificationManager::Default().UnregisterAll();
            }
            catch (...)
            {
                // We want to unregister regardless of pass/fail to clean the state.
            }
            return true;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            PushNotificationTestFunctions::ChannelRequestUsingNullRemoteId();
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
            PushNotificationTestFunctions::ChannelRequestUsingRemoteId();
        }

        // Currently failing.
        TEST_METHOD(MultipleChannelClose)
        {
            PushNotificationTestFunctions::MultipleChannelClose();
        }

        TEST_METHOD(VerifyRegisterAndUnregister)
        {
            PushNotificationTestFunctions::VerifyRegisterAndUnregister();
        }

        TEST_METHOD(VerifyRegisterAndUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyRegisterAndUnregisterAll();
        }

        TEST_METHOD(MultipleRegister)
        {
            PushNotificationTestFunctions::MultipleRegister();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregister)
        {
            PushNotificationTestFunctions::VerifyMultipleRegisterAndUnregister();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyMultipleRegisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterTwice)
        {
            PushNotificationTestFunctions::VerifyUnregisterTwice();
        }

        TEST_METHOD(VerifyUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterAllTwice)
        {
            PushNotificationTestFunctions::VerifyUnregisterAllTwice();
        }

        TEST_METHOD(VerifyUnregisterAndUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyUnregisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyForegroundHandlerSucceeds)
        {
            PushNotificationTestFunctions::VerifyForegroundHandlerSucceeds();
        }

        TEST_METHOD(VerifyForegroundHandlerFails)
        {
            PushNotificationTestFunctions::VerifyForegroundHandlerFails();
        }
    };
}
