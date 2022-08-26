// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include <TlHelp32.h>
#include "NotificationActivationCallback.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Windows::PushNotifications;
using namespace winrt::Microsoft::Windows::AppNotifications;

namespace Test::NotificationActivation
{
    class ActivationTests
    {

    private:
        wil::unique_event m_failed;
        wil::unique_process_handle m_processHandle;
        winrt::com_ptr<IApplicationActivationManager> m_testAppLauncher;

    public:
        BEGIN_TEST_CLASS(ActivationTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        static const int testWaitTime()
        {
            return 3000;
        }

        static PCWSTR GetTestPackageFile()
        {
            return L"NotificationActivationPackage";
        }

        static PCWSTR GetTestPackageFullName()
        {
            return L"NotificationActivationPackage_1.0.0.0_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";
        }

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages();
            TP::WapProj::AddPackage(TAEF::GetDeploymentDir(), GetTestPackageFile(), L".msix"); // Installs NotificationActivationPackage.msix

            m_testAppLauncher = winrt::try_create_instance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_ALL);
            VERIFY_IS_NOT_NULL(m_testAppLauncher);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            TP::RemovePackage(GetTestPackageFullName());
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            m_processHandle.reset();
            return true;
        }

        void RunTest(const PCWSTR& testName, const int& waitTime)
        {
            DWORD processId{};
            HRESULT hr{ m_testAppLauncher->ActivateApplication(L"NotificationActivationPackage_8wekyb3d8bbwe!App", testName, AO_NONE, &processId) };
            VERIFY_SUCCEEDED(hr);
            //VERIFY_SUCCEEDED();

            m_processHandle.reset(OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId));
            VERIFY_IS_TRUE(m_processHandle.is_valid());

            VERIFY_IS_TRUE(wil::handle_wait(m_processHandle.get(), waitTime));

            DWORD exitCode{};
            VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(m_processHandle.get(), &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0u);
        }

        wil::unique_handle RunUnpackaged(const std::wstring& command, const std::wstring& args, const std::wstring& directory)
        {
            SHELLEXECUTEINFO ei{};
            ei.cbSize = sizeof(SHELLEXECUTEINFO);
            ei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
            ei.lpFile = command.c_str();
            ei.lpParameters = args.c_str();
            ei.lpDirectory = directory.c_str();
            ei.nShow = SW_NORMAL;

            if (!ShellExecuteEx(&ei))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_SUCCEEDED(lastError);
            }

            wil::unique_handle process{ ei.hProcess };
            return process;
        }

        const std::wstring GetDeploymentDir()
        {
            WEX::Common::String deploymentDir;
            WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", deploymentDir);
            return reinterpret_cast<PCWSTR>(deploymentDir.GetBuffer());
        }

        TEST_METHOD(AppNotificationForeground)
        {

        }

        TEST_METHOD(AppNotificationBackground)
        {
            RunTest(L"BackgroundActivationTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto toastActivationCallback = winrt::create_instance<INotificationActivationCallback>(c_appNotificationComServerId, CLSCTX_ALL);
            VERIFY_SUCCEEDED(toastActivationCallback->Activate(c_appNotificationFakeAUMID.c_str(), c_appNotificationArgument.c_str(), nullptr, 0));
        }

        TEST_METHOD(PushNotificationForeground)
        {
            
        }

        TEST_METHOD(PushNotificationBackground)
        {

        }
    };
}
