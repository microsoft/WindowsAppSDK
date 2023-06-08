// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <testdef.h>
#include "Shared.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;

namespace Test::AppLifecycle
{
    static const std::wstring c_runKeyPath = LR"(Software\Microsoft\Windows\CurrentVersion\Run\)";

    class FunctionalTests
    {
    private:
        wil::unique_event m_failed;
        std::wstring m_testName;

        const std::wstring c_testDataFileName = L"testfile" + c_testFileExtension;
        const std::wstring c_testDataFileName_Packaged = L"testfile" + c_testFileExtension_Packaged;
        const std::wstring c_testPackageFile = g_deploymentDir + L"AppLifecycleTestPackage.msix";
        const std::wstring c_testVCLibsPackageFile = g_deploymentDir + L"VCLibs.appx";

        const std::wstring c_testPackageFullName = L"AppLifecycleTestPackage_1.0.0.0_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";

    public:
        BEGIN_TEST_CLASS(FunctionalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::Setup();

            m_failed = CreateTestEvent(c_testFailureEventName);

            // Deploy packaged app to register handler through the manifest.
            InstallPackage(c_testPackageFile);

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
                UninstallPackage(c_testPackageFullName);
            }
            catch (const std::exception&)
            {
            }
            catch (const winrt::hresult_error&)
            {
            }

            ::Test::Bootstrap::Cleanup();
            return true;
        }

        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            VERIFY_IS_NOT_NULL(AppInstance::GetCurrent().GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
            VERIFY_IS_NOT_NULL(args);
            VERIFY_ARE_EQUAL(args.Kind(), ExtendedActivationKind::Launch);

            auto launchArgs = args.Data().as<LaunchActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(launchArgs);
        }

        TEST_METHOD(GetActivatedEventArgsForFile_Win32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testFilePhaseEventName);

            // Cleanup any leftover data from previous runs i.e. ensure we running with a clean slate
            try
            {
                Execute(L"AppLifecycleTestApp.exe", L"/UnregisterFile", g_deploymentDir);
                WaitForEvent(event, m_failed);
            }
            catch (...)
            {
                //TODO:Unregister should not fail if ERROR_FILE_NOT_FOUND | ERROR_PATH_NOT_FOUND
            }

            // Launch the test app to register for protocol launches.
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterFile", g_deploymentDir);

            // Wait for the register event.
            WaitForEvent(event, m_failed);

            // Launch the file and wait for the event to fire.
            auto file = OpenDocFile(c_testDataFileName);
            auto launchResult = Launcher::LaunchFileAsync(file).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the file activation.
            WaitForEvent(event, m_failed);

            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterFile", g_deploymentDir);

            // Wait for the unregister event.
            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(GetActivatedEventArgsForFile_PackagedWin32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testFilePhaseEventName);

            // Launch the file and wait for the event to fire.
            auto file = OpenDocFile(c_testDataFileName_Packaged);
            auto launchResult = Launcher::LaunchFileAsync(file).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol_Win32)
        {
            // Create a named event for communicating with test app.
            auto event{ CreateTestEvent(c_testProtocolPhaseEventName) };

            // Cleanup any leftover data from previous runs i.e. ensure we running with a clean slate
            try
            {
                Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
                WaitForEvent(event, m_failed);
            }
            catch (...)
            {
                //TODO:Unregister should not fail if ERROR_FILE_NOT_FOUND | ERROR_PATH_NOT_FOUND
            }

            // Register the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);

            // Launch a URI with the protocol schema and wait for the app to fire the event
            Uri launchUri{ c_testProtocolScheme + L"://" + c_genericTestMoniker + L"?TestName=" + TESTNAME() };
            auto launchResult{ Launcher::LaunchUriAsync(launchUri).get() };
            VERIFY_IS_TRUE(launchResult);
            WaitForEvent(event, m_failed);

            // Deregister the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol_PackagedWin32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testProtocolPhaseEventName);

            // Launch a URI with the protocol schema and wait for the app to fire the event
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://" + c_genericTestMoniker + L"?TestName=" + TESTNAME() };
            auto launchResult{ Launcher::LaunchUriAsync(launchUri).get() };
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(GetActivatedEventArgsForPush_Win32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testPushPhaseEventName);

            // Launch the test app using the push activationprotocol.
            Execute(L"AppLifecycleTestApp.exe", L"----WindowsAppRuntimePushServer:-Payload:\"<toast></toast>\"", g_deploymentDir);

            // Wait for the protocol activation.
            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(GetActivatedEventArgsForStartup_Win32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testStartupPhaseEventName);

            // Launch the test app to register for protocol launches.
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterStartup", g_deploymentDir);

            // Wait for the register event.
            WaitForEvent(event, m_failed);

            // Instead of managing a reboot during a test, validate the registration was
            // written correctly.  This is done by reading the registration, splitting the
            // command line parameters into a separate string, running the command, and
            // waiting for the success event to be signaled.
            DWORD size{ 0 };
            std::wstring command;
            auto result = RegGetValue(HKEY_CURRENT_USER, c_runKeyPath.c_str(), c_genericTestMoniker.c_str(),
                RRF_RT_REG_SZ, nullptr, command.data(), &size);

            if (result == ERROR_MORE_DATA)
            {
                command.resize(size);
                result = RegGetValue(HKEY_CURRENT_USER, c_runKeyPath.c_str(), c_genericTestMoniker.c_str(),
                    RRF_RT_REG_SZ, nullptr, command.data(), &size);
            }
            THROW_IF_WIN32_ERROR(result);

            auto argsStart = command.rfind(L"\"----");
            auto exe = command.substr(0, argsStart);
            auto params = command.substr(argsStart);
            Execute(exe, params, g_deploymentDir);

            // Wait for the protocol activation.
            WaitForEvent(event, m_failed);

            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterStartup", g_deploymentDir);

            auto protEvent = CreateTestEvent(c_testStartupPhaseEventName);

            // Wait for the unregister event.
            WaitForEvent(protEvent, m_failed);
        }

        TEST_METHOD(SingleInstanceTest_Win32)
        {
            // Create a named event for communicating with test app.
            auto protocolActivationEvent{ CreateTestEvent(c_testProtocolPhaseEventName) };
            auto redirectedEvent{ CreateTestEvent(c_testInstanceRedirectedPhaseEventName) };

            // Cleanup any leftover data from previous runs i.e. ensure we running with a clean slate
            try
            {
                Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
                WaitForEvent(protocolActivationEvent, m_failed);
            }
            catch (...)
            {
                //TODO:Unregister should not fail if ERROR_FILE_NOT_FOUND | ERROR_PATH_NOT_FOUND
            }

            // Register the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", g_deploymentDir);
            WaitForEvent(protocolActivationEvent, m_failed);

            // Launch a URI with the protocol schema and wait for the app to fire the event
            Uri launchUri{ c_testProtocolScheme + L"://" + c_genericTestMoniker + L"?TestName=" + TESTNAME() };
            auto launchResult{ Launcher::LaunchUriAsync(launchUri).get() };
            VERIFY_IS_TRUE(launchResult);
            WaitForEvent(protocolActivationEvent, m_failed);
            WaitForEvent(redirectedEvent, m_failed);

            // Deregister the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
            WaitForEvent(protocolActivationEvent, m_failed);
        }

        TEST_METHOD(SingleInstanceTest_PackagedWin32)
        {
            // Create a named event for communicating with test app.
            auto protocolActivationEvent{ CreateTestEvent(c_testProtocolPhaseEventName) };
            auto redirectedEvent{ CreateTestEvent(c_testInstanceRedirectedPhaseEventName) };

            // Launch a URI with the protocol schema and wait for the app to fire the event
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://" + c_genericTestMoniker + L"?TestName=" + TESTNAME() };
            auto launchResult{ Launcher::LaunchUriAsync(launchUri).get() };
            VERIFY_IS_TRUE(launchResult);
            WaitForEvent(protocolActivationEvent, m_failed);
            WaitForEvent(redirectedEvent, m_failed);
        }

        TEST_METHOD(RequestRestart_Win32)
        {
            // Create a named event for communicating with test app.
            auto event{ CreateTestEvent(c_testProtocolPhaseEventName) };
            
            // Cleanup any leftover data from previous runs i.e. ensure we running with a clean slate
            try
            {
                Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
                WaitForEvent(event, m_failed);
            }
            catch (...)
            {
                //TODO:Unregister should not fail if ERROR_FILE_NOT_FOUND | ERROR_PATH_NOT_FOUND
            }

            // Register the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);

            auto restartNowEvent{ CreateTestEvent(c_testRequestRestartNowPhaseEventName) };
            auto restartNowRestartedEvent{ CreateTestEvent(c_testRequestRestartNowRestartedPhaseEventName) };

            // Launch a URI with the protocol schema and wait for the app to fire the event
            Uri launchUri{ c_testProtocolScheme + L"://" + c_genericTestMoniker + L"?TestName=" + TESTNAME() };
            auto launchResult{ Launcher::LaunchUriAsync(launchUri).get() };
            VERIFY_IS_TRUE(launchResult);

            // Wait for Restart code path in caller.
            WaitForEvent(restartNowEvent, m_failed);

            // Wait for the restarted process with args!
            WaitForEvent(restartNowRestartedEvent, m_failed);
            
            // Deregister the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);
        }

        TEST_METHOD(RequestRestart_PackagedWin32)
        {
            // Create a named event for communicating with test app.
            auto event{ CreateTestEvent(c_testProtocolPhaseEventName) };

            // Cleanup any leftover data from previous runs i.e. ensure we running with a clean slate
            try
            {
                Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
                WaitForEvent(event, m_failed);
            }
            catch (...)
            {
                //TODO:Unregister should not fail if ERROR_FILE_NOT_FOUND | ERROR_PATH_NOT_FOUND
            }

            // Register the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);

            auto restartNowEvent{ CreateTestEvent(c_testRequestRestartNowPhaseEventName) };
            auto restartNowRestartedEvent{ CreateTestEvent(c_testRequestRestartNowRestartedPhasePackagedEventName) };

            // Launch a URI with the protocol schema and wait for the app to fire the event
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://" + c_genericTestMoniker + L"?TestName=" + TESTNAME() };
            auto launchResult{ Launcher::LaunchUriAsync(launchUri).get() };
            VERIFY_IS_TRUE(launchResult);

            // Wait for Restart code path in caller.
            WaitForEvent(restartNowEvent, m_failed);

            // Wait for the restarted process with args!
            WaitForEvent(restartNowRestartedEvent, m_failed);

            // Deregister the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);
        }
    };
}
