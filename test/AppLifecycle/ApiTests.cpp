// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <testdef.h>

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

namespace ProjectReunionCppTest
{
    class AppLifecycleApiTests
    {
    private:
        wil::unique_event m_failed;

        const std::wstring c_testDataFileName = L"testfile" + c_testFileExtension;
        const std::wstring c_testPackageFile = GetDeploymentDir() + L"AppLifecycleTestPackage.msixbundle";
        const std::wstring c_testPackageCertFile = GetDeploymentDir() + L"AppLifecycleTestPackage.cer";

    public:
        BEGIN_TEST_CLASS(AppLifecycleApiTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"InteractiveUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            // Deploy packaged app to register handler through the manifest.
            RunCertUtil(c_testPackageCertFile);
            InstallPackage(c_testPackageFile);

            // Write out some test content.
            WriteContentFile(c_testDataFileName);

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            // Swallow errors in cleanup.
            try
            {
                DeleteContentFile(c_testDataFileName);
                UninstallPackage(c_testPackageFile);
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

        StorageFile CreateDocFile(std::wstring filename)
        {
            return KnownFolders::DocumentsLibrary().CreateFileAsync(filename, CreationCollisionOption::OpenIfExists).get();
        }

        StorageFile OpenDocFile(std::wstring filename)
        {
            return KnownFolders::DocumentsLibrary().GetFileAsync(filename).get();
        }

        wil::unique_handle Execute(const std::wstring& command, const std::wstring& args,
            const std::wstring& directory)
        {
            SHELLEXECUTEINFO ei{};
            ei.cbSize = sizeof(SHELLEXECUTEINFO);
            ei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
            ei.lpFile = command.c_str();
            ei.lpParameters = args.c_str();
            ei.lpDirectory = directory.c_str();

            if (!ShellExecuteEx(&ei))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }

            wil::unique_handle process{ ei.hProcess };
            return process;
        }

        void RunCertUtil(const std::wstring& path, bool removeCert = false)
        {
            std::wstring action = (removeCert ? L"-delstore" : L"-addstore");
            std::wstring args{ action + L" TrustedPeople " + path };
            auto process = Execute(L"%SystemRoot%\\system32\\certutil.exe",
                args.c_str(), GetDeploymentDir());

            // Wait for the cer to be installed.
            auto waitResult = WaitForSingleObject(process.get(), c_phaseTimeout);
            if (waitResult != WAIT_OBJECT_0)
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }

            // Make sure the exitcode for the tool is success.
            DWORD exitCode{};
            THROW_IF_WIN32_BOOL_FALSE(GetExitCodeProcess(process.get(), &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0);
        }

        void InstallPackage(const std::wstring& packagePath)
        {
            // Deploy packaged app to register handler through the manifest.
            PackageManager manager;
            IVector<Uri> depPackagePaths;
            auto result = manager.AddPackageAsync(Uri(packagePath), depPackagePaths,
                DeploymentOptions::ForceApplicationShutdown).get();
            auto errorText = result.ErrorText();
            auto errorCode = result.ExtendedErrorCode();
            VERIFY_SUCCEEDED(errorCode, errorText.c_str());
        }

        void UninstallPackage(const std::wstring& packagePath)
        {
            // Deploy packaged app to register handler through the manifest.
            PackageManager manager;
            IVector<Uri> depPackagePaths;
            auto result = manager.AddPackageAsync(Uri(packagePath), depPackagePaths,
                DeploymentOptions::ForceApplicationShutdown).get();
            auto errorText = result.ErrorText();
            auto errorCode = result.ExtendedErrorCode();
            VERIFY_SUCCEEDED(errorCode, errorText.c_str());
        }

        static wil::unique_event CreateTestEvent(const std::wstring& eventName)
        {
            bool alreadyExists = false;
            SECURITY_ATTRIBUTES attributes = {};
            wil::unique_hlocal_security_descriptor descriptor;

            // Grant access to world and appcontainer.
            THROW_IF_WIN32_BOOL_FALSE(ConvertStringSecurityDescriptorToSecurityDescriptor(
                L"D:(A;;GA;;;WD)(A;;GA;;;AC)", SDDL_REVISION_1, &descriptor, nullptr));
            attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
            attributes.lpSecurityDescriptor = descriptor.get();

            wil::unique_event event;
            event.create(wil::EventOptions::None, eventName.c_str(), &attributes, &alreadyExists);
            return event;
        }

        void WaitForEvent(const wil::unique_event& event)
        {
            HANDLE waitEvents[2] = { event.get(), m_failed.get() };
            auto waitResult = WaitForMultipleObjects(_countof(waitEvents), waitEvents, FALSE,
                c_phaseTimeout);

            // If waitResult == failureEventIndex, it means the remote test process signaled a
            // failure event while we were waiting for a different event.
            auto failureEventIndex = WAIT_OBJECT_0 + 1;
            VERIFY_ARE_NOT_EQUAL(waitResult, failureEventIndex);

            VERIFY_ARE_NOT_EQUAL(waitResult, WAIT_TIMEOUT);
            if (waitResult == WAIT_FAILED)
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }

            event.ResetEvent();
            m_failed.ResetEvent();
        }

        static std::wstring GetDeploymentDir()
        {
            WEX::Common::String testDeploymentDir;
            WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDeploymentDir);
            return reinterpret_cast<LPCWSTR>(testDeploymentDir.GetBuffer());
        }

        void WriteContentFile(std::wstring filename)
        {
            auto file = CreateDocFile(filename);
            FileIO::WriteTextAsync(file, L"Hello, World!").get();
        }

        void DeleteContentFile(std::wstring filename)
        {
            auto file = CreateDocFile(filename);
            file.DeleteAsync().get();
        }

        // Validate that UWP is not a supported scenario.
        TEST_METHOD(GetActivatedEventArgsIsNull)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
            END_TEST_METHOD_PROPERTIES();

            VERIFY_IS_NULL(AppLifecycle::GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                // Run this test for both PackagedWin32 and Win32.
                TEST_METHOD_PROPERTY(L"RunAs", L"{UAP,InteractiveUser}")

                // UAP:Host/UAP:AppXManifest are ignored when RunAs != UAP.
                TEST_METHOD_PROPERTY(L"UAP:Host", L"PackagedCwa")
                TEST_METHOD_PROPERTY(L"UAP:AppXManifest", L"PackagedCwaFullTrust")
            END_TEST_METHOD_PROPERTIES();

            VERIFY_IS_NOT_NULL(AppLifecycle::GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                // Run this test for both PackagedWin32 and Win32.
                TEST_METHOD_PROPERTY(L"RunAs", L"{UAP,InteractiveUser}")

                // UAP:Host/UAP:AppXManifest are ignored when RunAs != UAP.
                TEST_METHOD_PROPERTY(L"UAP:Host", L"PackagedCwa")
                TEST_METHOD_PROPERTY(L"UAP:AppXManifest", L"PackagedCwaFullTrust")
            END_TEST_METHOD_PROPERTIES();

            auto args = AppLifecycle::GetActivatedEventArgs();
            VERIFY_IS_NOT_NULL(args);
            VERIFY_ARE_EQUAL(args.Kind(), ActivationKind::Launch);

            auto launchArgs = args.as<LaunchActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(launchArgs);
        }

        // TODO: Ensure all manifests have proper version requirements for the project!

        TEST_METHOD(GetActivatedEventArgsForProtocol_Win32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testProtocolPhaseEventName);

            // Launch the test app to register for protocol launches.
            if (!Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", GetDeploymentDir()))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }

            // Wait for the register event.
            WaitForEvent(event);

            // Launch a protocol and wait for the event to fire.
            Uri launchUri{ c_testProtocolScheme + L"://this_is_a_test" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event);

            // TODO: Test unregister scenario.
            if (!Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", GetDeploymentDir()))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }

            // Wait for the unregister event.
            WaitForEvent(event);

            // TODO: Validate it was unregistered properly.
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol_PackagedWin32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testProtocolPhaseEventName);

            RunCertUtil(L"AppLifecycleTestPackage.cer");

            // Deploy packaged app to register handler through the manifest.
            std::wstring packagePath{ GetDeploymentDir() + L"\\AppLifecycleTestPackage.msixbundle" };
            InstallPackage(packagePath);

            // TODO: Validate register scenario before continuing.

            // Launch a protocol and wait for the event to fire.
            Uri launchUri{ c_testProtocolScheme + L"://this_is_a_test" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event);

            // TODO: Test unregister scenario.
        }

        TEST_METHOD(GetActivatedEventArgsForFile_Win32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testFilePhaseEventName);

            // Launch the test app to register for protocol launches.
            if (!ShellExecute(nullptr, nullptr, L"AppLifecycleTestApp.exe", L"/RegisterFile",
                GetDeploymentDir().c_str(), SW_SHOW))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }

            // Wait for the register event.
            WaitForEvent(event);

            // TODO: Validate register scenario before continuing.

            // Launch the file and wait for the event to fire.
            auto file = OpenDocFile(c_testDataFileName);
            auto launchResult = Launcher::LaunchFileAsync(file).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event);

            // TODO: Test unregister scenario.
        }

        TEST_METHOD(GetActivatedEventArgsForFile_PackagedWin32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testFilePhaseEventName);

            // TODO: Validate register scenario before continuing.
            
            // Launch the file and wait for the event to fire.
            auto file = OpenDocFile(c_testDataFileName);
            auto launchResult = Launcher::LaunchFileAsync(file).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event);

            // TODO: Test unregister scenario.
        }
    };
}
