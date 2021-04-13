// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <testdef.h>
#include "Shared.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::ProjectReunion;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;

// TODO: Write Register/Unregister tests that utilize the Assoc APIs to validate results.

namespace Test::AppLifecycle
{
    class APITests
    {
    private:
        wil::unique_event m_failed;

        const std::wstring c_testDataFileName = L"testfile" + c_testFileExtension;
        const std::wstring c_testDataFileName_Packaged = L"testfile" + c_testFileExtension_Packaged;
        const std::wstring c_testPackageFile = g_deploymentDir + L"MSIXPackager_1.0.0.0_x64_Debug.msixbundle";
        const std::wstring c_testPackageCertFile = g_deploymentDir + L"MSIXPackager_1.0.0.0_x64_Debug.cer";
        const std::wstring c_testPackageFullName = L"PushNotificationsWin32App_1.0.0.0_x64__8wekyb3d8bbwe";

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages();

            // Write out some test content.
            try
            {
                //InstallPackage(c_testPackageFile);
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
            //try
            //{
            //    UninstallPackage(c_testPackageFullName);
            //}
            //catch (...)
            //{
            //    return false;
            //}

            //
            //return true;
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

        TEST_METHOD(LaunchTest)
        {
            //wil::unique_event event = CreateTestEvent(c_testProtocolPhaseEventName);

            //// This is associated protocol for the MSIX installed app for launch.
            //// Use the ://path to define the component you want to test.
            //Uri launchUri{ c_testProtocolScheme_Packaged + L"://this_is_a_test" };
            //auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            //VERIFY_IS_TRUE(launchResult);

            //WaitForEvent(event, m_failed);
            //// winrt::Windows::ApplicationModel::Background::
            VERIFY_IS_TRUE(true);
        }

        //TEST_METHOD(GetActivatedEventArgsIsNull_UAP)
        //{
        //    BEGIN_TEST_METHOD_PROPERTIES()
        //        TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
        //        TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"AppLifecycle-AppxManifest.xml")
        //    END_TEST_METHOD_PROPERTIES();

        //    PushNotificationActivationInfo info(
        //        PushNotificationRegistrationKind::PushTrigger | PushNotificationRegistrationKind::ComActivator,
        //        winrt::guid("c54044c4-eac7-4c4b-9996-c570a94b9306")); // same clsid as app manifest

        //    //// Registers a Push Trigger and sets up an inproc COM Server for Activations
        //    auto token = PushNotificationManager::RegisterActivator(info);
        //    //
        //    VERIFY_IS_NULL(AppInstance::GetCurrent().GetActivatedEventArgs().Data());
        //    VERIFY_ARE_EQUAL(AppInstance::GetCurrent().GetActivatedEventArgs().Kind(), ExtendedActivationKind::Push);

        //    
        //}
    };
}
