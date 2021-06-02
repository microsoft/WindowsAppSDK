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
        wil::unique_handle m_processHandle;
        winrt::com_ptr<IApplicationActivationManager> m_testAppLauncher;

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"Description", L"Project Reunion Push Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        static PCWSTR GetDeploymentDir()
        {
            WEX::Common::String testDeploymentDir;
            WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDeploymentDir);
            return reinterpret_cast<PCWSTR>(testDeploymentDir.GetBuffer());
        }

        static std::filesystem::path GetTestPackageFile()
        {
            auto filename{ std::filesystem::path(GetDeploymentDir()) };
            filename /= L"PushNotificationsTestAppPackage";
            return filename;
        }

        static PCWSTR GetTestPackageFullName()
        {
            return L"PushNotificationsTestAppPackage_1.0.0.0_" PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";
        }

        TEST_CLASS_SETUP(ClassInit)
        {
            try
            {
                TP::AddPackage_ProjectReunionFramework(); // Installs PRfwk
                TP::WapProj::AddPackage(L"PushNotificationsTestAppPackage", L"1.0.0.0"); // Installs PushNotificationsTestApp.msix
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
                TP::RemovePackage_ProjectReunionFramework();
                TP::RemovePackage(GetTestPackageFullName());
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

            if (m_processHandle)
            {
                m_processHandle.reset();
            }
            return true;
        }

        void RunTest(const PCWSTR& testName, const int& waitTime)
        {
            DWORD processId;
            VERIFY_SUCCEEDED(m_testAppLauncher.get()->ActivateApplication(L"PushNotificationsTestAppPackage_8wekyb3d8bbwe!App", testName, AO_NONE, &processId));

            m_processHandle = wil::unique_handle(OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId));
            VERIFY_IS_TRUE(m_processHandle.is_valid());

            VERIFY_ARE_EQUAL(WaitForSingleObject(m_processHandle.get(), waitTime), WAIT_OBJECT_0);

            DWORD exitCode;
            VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(m_processHandle.get(), &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0);
        }

        TEST_METHOD(BackgroundActivation)
        {
            RunTest(nullptr, c_pushTestWait); // Need to launch one time to enable background activation.

            auto LocalBackgroundTask = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance = winrt::make<MockBackgroundTaskInstance>();
            VERIFY_NO_THROW(LocalBackgroundTask.Run(mockBackgroundTaskInstance));
        }

        TEST_METHOD(MultipleBackgroundActivation)
        {
            RunTest(nullptr, c_pushTestWait); // Need to launch one time to enable background activation.

            auto LocalBackgroundTask1 = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance1 = winrt::make<MockBackgroundTaskInstance>();

            auto LocalBackgroundTask2 = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance2 = winrt::make<MockBackgroundTaskInstance>();

            VERIFY_NO_THROW(LocalBackgroundTask1.Run(mockBackgroundTaskInstance1));
            VERIFY_NO_THROW(LocalBackgroundTask2.Run(mockBackgroundTaskInstance2));

        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            RunTest(L"ChannelRequestUsingNullRemoteId", c_pushTestWait);
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
            RunTest(L"ChannelRequestUsingRemoteId", c_pushTestChannelWait);
        }

        TEST_METHOD(MultipleChannelRequestUsingSameRemoteId)
        {
            RunTest(L"MultipleChannelRequestUsingSameRemoteId", c_pushTestChannelWait);
        }

        TEST_METHOD(MultipleChannelRequestUsingMultipleRemoteId)
        {
            RunTest(L"MultipleChannelRequestUsingMultipleRemoteId", c_pushTestChannelWait);
        }

        TEST_METHOD(ActivatorTest)
        {
            RunTest(L"ActivatorTest", c_pushTestWait);
        }

        TEST_METHOD(RegisterActivatorNullDetails)
        {
            RunTest(L"RegisterActivatorNullDetails", c_pushTestWait);
        }

        TEST_METHOD(RegisterActivatorNullClsid)
        {
            RunTest(L"RegisterActivatorNullClsid", c_pushTestWait);
        }

        TEST_METHOD(UnregisterActivatorNullToken)
        {
            RunTest(L"UnregisterActivatorNullToken", c_pushTestWait);
        }

        TEST_METHOD(UnregisterActivatorNullBackgroundRegistration)
        {
            RunTest(L"UnregisterActivatorNullBackgroundRegistration", c_pushTestWait);
        }

        TEST_METHOD(MultipleRegisterActivatorTest)
        {
            RunTest(L"MultipleRegisterActivatorTest", c_pushTestWait);
        }

    };
}
