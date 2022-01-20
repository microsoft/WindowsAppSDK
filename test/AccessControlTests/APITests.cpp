// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <Security.AccessControl.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace Test::AccessControl
{
    class APITests
    {
        wil::unique_process_handle m_processHandle;
        winrt::com_ptr<IApplicationActivationManager> m_testAppLauncher;

        static PCWSTR GetTestPackageFile()
        {
            return L"AccessControlTestAppPackage";
        }

        static PCWSTR GetTestPackageFullName()
        {
            return L"AccessControlTestPackage_1.0.0.0_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE "8wekyb3d8bbwe";
        }

        static PCWSTR GetTestPackageAppId()
        {
            return L"AccessControlTestAppPackage_8wekyb3d8bbwe!App";
        }

        void RunTestApp()
        {
            DWORD processId{};
            VERIFY_SUCCEEDED(m_testAppLauncher->ActivateApplication(GetTestPackageAppId(), L"", AO_NONE, &processId));

            m_processHandle.reset(::OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId));
            VERIFY_IS_TRUE(m_processHandle.is_valid());
        }

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK AccessControl test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            try
            {
                ::Test::Packages::RemovePackage(GetTestPackageFullName());
                ::Test::Bootstrap::SetupPackages();
                ::Test::Packages::WapProj::AddPackage(TAEF::GetDeploymentDir(), GetTestPackageFile(), L".msix"); // Installs PushNotificationsTestApp.msix
            }
            catch (...)
            {
                return false;
            }

            m_testAppLauncher = winrt::create_instance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_ALL);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            try
            {
                if (m_processHandle.is_valid())
                {
                    VERIFY_IS_TRUE(wil::handle_wait(m_processHandle.get(), 10000));

                    DWORD exitCode{};
                    VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(m_processHandle.get(), &exitCode));
                    VERIFY_ARE_EQUAL(exitCode, 0);
                }
                // Remove in reverse order to avoid conflicts between inter-dependent packages.
                ::Test::Packages::RemovePackage(GetTestPackageFullName());
                ::Test::Bootstrap::CleanupPackages();
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(::Test::Packages::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(::Test::Packages::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(::Test::Packages::IsPackageRegistered_DynamicDependencyLifetimeManager());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            if (m_processHandle.is_valid())
            {
                VERIFY_IS_TRUE(wil::handle_wait(m_processHandle.get(), 10000));
                DWORD exitCode{};
                VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(m_processHandle.get(), &exitCode));
                VERIFY_ARE_EQUAL(exitCode, 0);
            }
            VERIFY_IS_TRUE(::Test::Packages::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(::Test::Packages::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(::Test::Packages::IsPackageRegistered_DynamicDependencyLifetimeManager());

            m_processHandle.reset();
            return true;
        }

        TEST_METHOD(FlatAPITest)
        {
            RunTestApp();

            AppContainerNameAndAccess ac[1] = { { GetTestPackageFile(), EVENT_MODIFY_STATE | SYNCHRONIZE} };
            wil::unique_hlocal_security_descriptor sd;
            DWORD sdLength = 0;
            THROW_IF_FAILED(::GetSecurityDescriptorForAppContainerNames(1, ac, nullptr, EVENT_MODIFY_STATE | SYNCHRONIZE, &sd, &sdLength));

            wil::unique_event win32_event;
            SECURITY_ATTRIBUTES sa{ sizeof(sa), sd.get(), FALSE };
            win32_event.create(wil::EventOptions::None, L"AccessControlTest_Event", &sa);

            VERIFY_IS_TRUE(win32_event.wait(5000));
        }
    };
}
