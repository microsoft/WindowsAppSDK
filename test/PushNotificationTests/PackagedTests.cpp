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
#define VERIFY_THROWS_HR(expression, hr)        \
        VERIFY_THROWS_SPECIFIC(expression,          \
            winrt::hresult_error,                   \
            [&](winrt::hresult_error e) -> bool     \
            {                                       \
                return (e.code() == hr);    \
            })

    class PackagedTests
    {
    public:
        BEGIN_TEST_CLASS(PackagedTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"PushNotifications-AppxManifest.xml")
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
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            return true;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            // Need to use SelfContained test hook to setup tests.
            ::WindowsAppRuntime::SelfContained::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);

            TestFunctions::ChannelRequestUsingNullRemoteId();
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
            TestFunctions::ChannelRequestUsingRemoteId();
        }

        // Currently failing.
        TEST_METHOD(MultipleChannelClose)
        {
            TestFunctions::MultipleChannelClose();
        }

        TEST_METHOD(VerifyRegisterAndUnregister)
        {
            TestFunctions::VerifyRegisterAndUnregister();
        }

        TEST_METHOD(VerifyRegisterAndUnregisterAll)
        {
            TestFunctions::VerifyRegisterAndUnregisterAll();
        }

        TEST_METHOD(MultipleRegister)
        {
            TestFunctions::MultipleRegister();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregister)
        {
            TestFunctions::VerifyMultipleRegisterAndUnregister();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregisterAll)
        {
            TestFunctions::VerifyMultipleRegisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterTwice)
        {
            TestFunctions::VerifyUnregisterTwice();
        }

        TEST_METHOD(VerifyUnregisterAll)
        {
            TestFunctions::VerifyUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterAllTwice)
        {
            TestFunctions::VerifyUnregisterAllTwice();
        }

        TEST_METHOD(VerifyUnregisterAndUnregisterAll)
        {
            TestFunctions::VerifyUnregisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyForegroundHandlerSucceeds)
        {
            TestFunctions::VerifyForegroundHandlerSucceeds();
        }

        TEST_METHOD(VerifyForegroundHandlerFails)
        {
            TestFunctions::VerifyForegroundHandlerFails();
        }
    };
}
