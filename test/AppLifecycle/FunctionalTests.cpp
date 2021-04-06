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
    class AppLifecycleFunctionalTests
    {
    private:
        wil::unique_event m_failed;

        const std::wstring c_testDataFileName = L"testfile" + c_testFileExtension;
        const std::wstring c_testDataFileName_Packaged = L"testfile" + c_testFileExtension_Packaged;
        const std::wstring c_testPackageFile = g_deploymentDir + L"MSIXPackager_1.1.30.0_x64_Debug.msix";
        const std::wstring c_testPackageCertFile = g_deploymentDir + L"MSIXPackager_1.1.30.0_x64_Debug.cer";
        const std::wstring c_testPackageFullName = L"PushNotificationsWin32App_1.1.30.0_x64__9eg3vg7cmy3rj";

    public:
        BEGIN_TEST_CLASS(AppLifecycleFunctionalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"InteractiveUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            // Deploy packaged app to register handler through the manifest.
            try
            {
                RunCertUtil(c_testPackageCertFile);
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
            // Swallow errors in cleanup.
            try
            {
                UninstallPackage(c_testPackageFullName);
                RunCertUtil(c_testPackageCertFile, true);
            }
            catch (const std::exception&)
            {
            }
            catch (const winrt::hresult_error&)
            {
            }

            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            m_failed = CreateTestEvent(c_testFailureEventName);
            return true;
        }

        TEST_METHOD(ChannelRequestTest)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://channelRequest" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(ForegroundActivationTest)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://foregroundTest" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(BackgroundActivationTest)
        {
            wil::unique_event event = CreateTestEvent(c_testProtocolScheme_Packaged);

            // This is associated protocol for the MSIX installed app for launch.
            // Use the ://path to define the component you want to test.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://backgroundTest" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            WaitForEvent(event, m_failed);
        }
    };
}
