// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <testdef.h>
#include "Shared.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Microsoft::ProjectReunion;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;

// TODO: Write Register/Unregister tests that utilize the Assoc APIs to validate results.

namespace ProjectReunionCppTest
{
    class PushNotificationsFunctionalTests
    {
    private:
        wil::unique_event m_failed;

        const std::wstring c_testPackageFile = g_deploymentDir + L"MSIXPackager_1.0.0.0_x86_Debug.msixbundle";
        const std::wstring c_testPackageCertFile = g_deploymentDir + L"MSIXPackager_1.0.0.0_x86_Debug.cer";
        const std::wstring c_testPackageFullName = L"PushNotifications_1.0.0.0_x86__e1t4my21da5bj";

    public:
        BEGIN_TEST_CLASS(PushNotificationsFunctionalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"InteractiveUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            RunCertUtil(c_testPackageCertFile);
            InstallPackage(c_testPackageFile);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            UninstallPackage(c_testPackageFullName);
            RunCertUtil(c_testPackageCertFile, true);
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            m_failed = CreateTestEvent(c_testFailureEventName);
            return true;
        }

        TEST_METHOD(LaunchPackagedWin32)
        {
            // Create a named event for communicating with test app.
            wil::unique_event event = CreateTestEvent(c_testProtocolPhaseEventName);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://this_is_a_test" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }
    };
}
