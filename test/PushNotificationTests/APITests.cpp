// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "Shared.h"
#include "MockBackgroundTaskInstance.h"

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

namespace Test::PushNotifications
{
    class APITests
    {
    private:
        wil::unique_event m_failed;

        const std::wstring c_testPackageFile = g_deploymentDir + L"PushNotificationsTestAppPackage_1.0.0.0_x64.msixbundle";
        const std::wstring c_testPackageCertFile = g_deploymentDir + L"PushNotificationsTestAppPackage_1.0.0.0_x64.cer";
        const std::wstring c_testPackageFullName = L"PushNotificationsTestAppPackage_1.0.0.0_x64__8wekyb3d8bbwe";

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"Description", L"Project Reunion Push Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            try
            {
                InstallPackage(c_testVCLibsPackageFile);
            }
            catch (...)
            {
                return false;
            }

            TP::AddPackage_ProjectReunionFramework();
            try
            {
                InstallPackage(c_testPackageFile);
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            TP::RemovePackage_ProjectReunionFramework();

            try
            {
                UninstallPackage(c_testPackageFullName);
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_ProjectReunionFramework());

            m_failed = CreateTestEvent(c_testFailureEventName);

            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_ProjectReunionFramework());

            return true;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://ChannelRequestUsingNullRemoteId" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://ChannelRequestUsingRemoteId" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(MultipleChannelRequestUsingSameRemoteId)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://MultipleChannelRequestUsingSameRemoteId" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(MultipleChannelRequestUsingMultipleRemoteId)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://MultipleChannelRequestUsingMultipleRemoteId" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(BackgroundActivation)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);
            auto LocalBackgroundTask = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance = winrt::make<MockBackgroundTaskInstance>();
            LocalBackgroundTask.Run(mockBackgroundTaskInstance);
            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(RegisterActivatorNullDetails)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://RegisterActivatorNullDetails" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(RegisterActivatorNullClsid)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://RegisterActivatorNullClsid" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(UnregisterActivatorNullToken)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://UnregisterActivatorNullToken" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(UnregisterActivatorNullBackgroundRegistration)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://UnregisterActivatorNullBackgroundRegistration" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(ActivatorTest)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://ActivatorTest" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(MultipleRegisterActivatorTest)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://MultipleRegisterActivatorTest" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }
    };
}
