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
        const std::wstring c_testPackageFile = g_deploymentDir + L"AppLifecycleTestPackage.msixbundle";
        const std::wstring c_testPackageCertFile = g_deploymentDir + L"AppLifecycleTestPackage.cer";
        const std::wstring c_testPackageFullName = L"AppLifecycleTestPackage_1.0.0.0_x64__ph1m9x8skttmg";

    public:
        BEGIN_TEST_CLASS(AppLifecycleFunctionalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"InteractiveUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            // Deploy packaged app to register handler through the manifest.
            //RunCertUtil(c_testPackageCertFile);
            //InstallPackage(c_testPackageFile);

            // Write out some test content.
            WriteContentFile(c_testDataFileName);
            WriteContentFile(c_testDataFileName_Packaged);

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            // Swallow errors in cleanup.
            try
            {
                DeleteContentFile(c_testDataFileName_Packaged);
                DeleteContentFile(c_testDataFileName);
                //UninstallPackage(c_testPackageFullName);
                //RunCertUtil(c_testPackageCertFile, true);
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

        // Validate that UWP is not a supported scenario.
        TEST_METHOD(GetActivatedEventArgsIsNull)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
            END_TEST_METHOD_PROPERTIES();

            VERIFY_IS_NULL(AppInstance::GetCurrent().GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"InteractiveUser")
                //// Run this test for both PackagedWin32 and Win32.
                //TEST_METHOD_PROPERTY(L"RunAs", L"{UAP,InteractiveUser}")

                //// UAP:Host/UAP:AppXManifest are ignored when RunAs != UAP.
                //TEST_METHOD_PROPERTY(L"UAP:Host", L"PackagedCwa")
                //TEST_METHOD_PROPERTY(L"UAP:AppXManifest", L"PackagedCwaFullTrust")
            END_TEST_METHOD_PROPERTIES();

            VERIFY_IS_NOT_NULL(AppInstance::GetCurrent().GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"InteractiveUser")
                //// Run this test for both PackagedWin32 and Win32.
                //TEST_METHOD_PROPERTY(L"RunAs", L"{UAP,InteractiveUser}")

                //// UAP:Host/UAP:AppXManifest are ignored when RunAs != UAP.
                //TEST_METHOD_PROPERTY(L"UAP:Host", L"PackagedCwa")
                //TEST_METHOD_PROPERTY(L"UAP:AppXManifest", L"PackagedCwaFullTrust")
            END_TEST_METHOD_PROPERTIES();

            auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
            VERIFY_IS_NOT_NULL(args);
            VERIFY_ARE_EQUAL(args.Kind(), ExtendedActivationKind::Launch);

            auto launchArgs = args.as<LaunchActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(launchArgs);
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol_Win32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testProtocolPhaseEventName);

            // Launch the test app to register for protocol launches.
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", g_deploymentDir);

            // Wait for the register event.
            WaitForEvent(event, m_failed);

            // Launch a protocol and wait for the event to fire.
            Uri launchUri{ c_testProtocolScheme + L"://this_is_a_test" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event, m_failed);

            Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", g_deploymentDir);

            // Wait for the unregister event.
            WaitForEvent(event, m_failed);
        }

        //TEST_METHOD(GetActivatedEventArgsForProtocol_PackagedWin32)
        //{
        //    // Create a named event for communicating with test app.
        //    auto event = CreateTestEvent(c_testProtocolPhaseEventName);

        //    RunCertUtil(L"AppLifecycleTestPackage.cer");

        //    // Deploy packaged app to register handler through the manifest.
        //    std::wstring packagePath{ g_deploymentDir + L"\\AppLifecycleTestPackage.msixbundle" };
        //    InstallPackage(packagePath);

        //    // Launch a protocol and wait for the event to fire.
        //    Uri launchUri{ c_testProtocolScheme_Packaged + L"://this_is_a_test" };
        //    auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
        //    VERIFY_IS_TRUE(launchResult);

        //    // Wait for the protocol activation.
        //    WaitForEvent(event, m_failed);
        //}

        TEST_METHOD(GetActivatedEventArgsForFile_Win32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testFilePhaseEventName);

            // Launch the test app to register for protocol launches.
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterFile", g_deploymentDir);

            // Wait for the register event.
            WaitForEvent(event, m_failed);

            // Launch the file and wait for the event to fire.
            auto file = OpenDocFile(c_testDataFileName);
            auto launchResult = Launcher::LaunchFileAsync(file).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event, m_failed);
        }

        //TEST_METHOD(GetActivatedEventArgsForFile_PackagedWin32)
        //{
        //    // Create a named event for communicating with test app.
        //    auto event = CreateTestEvent(c_testFilePhaseEventName);

        //    // Launch the file and wait for the event to fire.
        //    auto file = OpenDocFile(c_testDataFileName_Packaged);
        //    auto launchResult = Launcher::LaunchFileAsync(file).get();
        //    VERIFY_IS_TRUE(launchResult);

        //    // Wait for the protocol activation.
        //    WaitForEvent(event, m_failed);
        //}
    };
}
