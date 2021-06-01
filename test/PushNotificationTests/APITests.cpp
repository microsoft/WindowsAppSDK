// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "MockBackgroundTaskInstance.h"
#include "Shared.h"

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
        HANDLE m_process;
        winrt::com_ptr<IApplicationActivationManager> m_testAppLauncher;

        //const std::wstring c_testPackageFile = g_deploymentDir + L"PushNotificationsTestAppPackage.msix";
        //const std::wstring c_testPackageFullName = L"PushNotificationsTestAppPackage_1.0.0.0_" PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";
        //const std::wstring c_testVCLibsPackageFile = g_deploymentDir + L"VCLibs.appx";

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"Description", L"Project Reunion Push Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        static std::wstring GetDeploymentDir()
        {
            WEX::Common::String testDeploymentDir;
            WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDeploymentDir);
            return reinterpret_cast<PCWSTR>(testDeploymentDir.GetBuffer());
        }

        static std::filesystem::path GetTestVCLibsPackageFile()
        {
            auto filename{ std::filesystem::path(GetDeploymentDir()) };
            filename /= L"VCLibs.appx";
            return filename;
        }

        static std::filesystem::path GetTestPackageFile()
        {
            auto filename{ std::filesystem::path(GetDeploymentDir()) };
            filename /= L"PushNotificationsTestAppPackage.msix";
            return filename;
        }

        static std::wstring GetTestPackageFullName()
        {
            return L"PushNotificationsTestAppPackage_1.0.0.0_" PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";
        }

        TEST_CLASS_SETUP(ClassInit)
        {
            try
            {
                TP::AddPackage_ProjectReunionFramework();
                InstallPackage(GetTestVCLibsPackageFile());
                InstallPackage(GetTestPackageFile());
            }
            catch (...)
            {
                return false;
            }

            m_testAppLauncher = winrt::create_instance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_ALL);
            VERIFY_IS_NOT_NULL(m_testAppLauncher);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            try
            {
                TP::RemovePackage_ProjectReunionFramework();
                UninstallPackage(GetTestPackageFullName());
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
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_ProjectReunionFramework());

            if (m_process)
            {
                VERIFY_IS_TRUE(CloseHandle(m_process));
            }
            return true;
        }

        void RunTest(const PCWSTR& testName)
        {
            DWORD pid;
            VERIFY_SUCCEEDED(m_testAppLauncher.get()->ActivateApplication(L"PushNotificationsTestAppPackage_8wekyb3d8bbwe!App", testName, AO_NONE, &pid));
            VERIFY_IS_NOT_NULL(pid);

            m_process = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            VERIFY_IS_NOT_NULL(m_process);

            VERIFY_ARE_EQUAL(WaitForSingleObject(m_process, 3000), WAIT_OBJECT_0);

            DWORD exitCode;
            VERIFY_IS_TRUE(GetExitCodeProcess(m_process, &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0);

            VERIFY_IS_TRUE(CloseHandle(m_process));
            m_process = nullptr;
        }

        TEST_METHOD(BackgroundActivation)
        {
            RunTest(nullptr); // Just need to launch.

            auto LocalBackgroundTask = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance = winrt::make<MockBackgroundTaskInstance>();
            VERIFY_NO_THROW(LocalBackgroundTask.Run(mockBackgroundTaskInstance));
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            RunTest(L"ChannelRequestUsingNullRemoteId");
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
            RunTest(L"ChannelRequestUsingRemoteId");
        }

        /*TEST_METHOD(MultipleChannelRequestUsingSameRemoteId)
        {
            RunTest(L"MultipleChannelRequestUsingSameRemoteId");
        }

        TEST_METHOD(MultipleChannelRequestUsingMultipleRemoteId)
        {
            RunTest(L"MultipleChannelRequestUsingMultipleRemoteId");
        }*/

        TEST_METHOD(ActivatorTest)
        {
            RunTest(L"ActivatorTest");
        }

        TEST_METHOD(RegisterActivatorNullDetails)
        {
            RunTest(L"RegisterActivatorNullDetails");
        }

        TEST_METHOD(RegisterActivatorNullClsid)
        {
            RunTest(L"RegisterActivatorNullClsid");
        }

        TEST_METHOD(UnregisterActivatorNullToken)
        {
            RunTest(L"UnregisterActivatorNullToken");
        }

        TEST_METHOD(UnregisterActivatorNullBackgroundRegistration)
        {
            RunTest(L"UnregisterActivatorNullBackgroundRegistration");
        }

        TEST_METHOD(MultipleRegisterActivatorTest)
        {
            RunTest(L"MultipleRegisterActivatorTest");
        }
    };
}
