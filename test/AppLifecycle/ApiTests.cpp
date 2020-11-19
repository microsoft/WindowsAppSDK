// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <testdef.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionCppTest
{
    class AppLifecycleApiTests
    {
        TEST_CLASS(AppLifecycleApiTests);

        static wil::unique_event CreateTestEvent(const std::wstring& eventName)
        {
            bool alreadyExists = false;
            SECURITY_ATTRIBUTES attributes = {};
            wil::unique_hlocal_security_descriptor descriptor;

            // Grant access to world and appcontainer.
            THROW_IF_WIN32_BOOL_FALSE(ConvertStringSecurityDescriptorToSecurityDescriptor(L"D:(A;;GA;;;WD)(A;;GA;;;AC)",
                SDDL_REVISION_1,
                &descriptor,
                nullptr));
            attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
            attributes.lpSecurityDescriptor = descriptor.get();

            wil::unique_event event;
            event.create(wil::EventOptions::None, eventName.c_str(), &attributes, &alreadyExists);
            return event;
        }

        void WaitForEvent(const wil::unique_event& event)
        {
            if (!event.wait(g_phaseTimeout))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }
        }

        static std::wstring GetModulePath()
        {
            std::wstring path(100, L'?');
            uint32_t path_size{};
            DWORD actual_size{};

            do
            {
                path_size = static_cast<uint32_t>(path.size());

                wil::unique_hmodule module;
                THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                    reinterpret_cast<LPCWSTR>(GetModulePath), &module));
                actual_size = ::GetModuleFileName(module.get(), path.data(), path_size);

                if (actual_size + 1 > path_size)
                {
                    path.resize(path_size * 2, L'?');
                }
            } while (actual_size + 1 > path_size);

            path.resize(actual_size);
            return path;
        }

        static std::wstring GetModuleDirectoryPath()
        {
            auto modulePath = GetModulePath();
            auto filenamePos = modulePath.rfind(L"\\");
            return modulePath.substr(0, filenamePos);
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
            if (!ShellExecute(nullptr, nullptr, L"AppLifecycleTestApp.exe", L"/RegisterProtocol",
                GetModuleDirectoryPath().c_str(), SW_SHOW))
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
            if (!ShellExecute(nullptr, nullptr, L"AppLifecycleTestApp.exe", L"/UnregisterProtocol",
                GetModuleDirectoryPath().c_str(), SW_SHOW))
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
            auto event = CreateTestEvent(c_testProtocolPhaseEventName_Packaged);

            // TODO: Deploy packaged app to register handler through the manifest.

            // TODO: Validate register scenario before continuing.

            // Launch a protocol and wait for the event to fire.
            Uri launchUri{ c_testProtocolScheme_Packaged + L"://this_is_a_test" };
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
                GetModuleDirectoryPath().c_str(), SW_SHOW))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_FAILED(lastError);
            }

            // TODO: Validate register scenario before continuing.

            // Launch the file and wait for the event to fire.

            // TODO: LaunchFileAsync
            /*Uri launchUri{ c_testProtocolScheme + L"://this_is_a_test" };
            auto launchResult = Launcher::LaunchUriAsync(launchUri).get();
            VERIFY_IS_TRUE(launchResult);*/

            // Wait for the protocol activation.
            WaitForEvent(event);

            // TODO: Test unregister scenario.
        }

        TEST_METHOD(GetActivatedEventArgsForFile_PackagedWin32)
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testFilePhaseEventName_Packaged);

            // TODO: Deploy packaged app to register handler through the manifest.

            // TODO: Validate register scenario before continuing.

            // Launch the file and wait for the event to fire.

            // TODO: LaunchFileAsync


            // Wait for the protocol activation.
            WaitForEvent(event);

            // TODO: Test unregister scenario.
        }
    };
}
