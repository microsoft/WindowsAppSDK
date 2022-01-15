// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "MockBackgroundTaskInstance.h"

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
        wil::unique_process_handle m_processHandle;
        winrt::com_ptr<IApplicationActivationManager> m_testAppLauncher;

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK Push Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        static const int testWaitTime()
        {
            return 3000;
        }

        static const int channelTestWaitTime()
        {
            return 303000; // Need to wait 300000ms for channel request + 3000ms for application overhead
        }

        static PCWSTR GetTestPackageFile()
        {
            return L"PushNotificationsTestAppPackage";
        }

        static PCWSTR GetTestPackageFullName()
        {
            return L"PushNotificationsTestAppPackage_1.0.0.0_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";
        }

        TEST_CLASS_SETUP(ClassInit)
        {
#if 0
            try
            {
                TP::AddPackage_WindowsAppRuntimeFramework();       // Installs WARfwk
                TP::AddPackage_DynamicDependencyDataStore();       // Installs WARmain
                TP::AddPackage_DynamicDependencyLifetimeManager(); // Installs WARddlm
                TP::AddPackage_PushNotificationsLongRunningTask(); // Installs the PushNotifications long running task.
                TP::WapProj::AddPackage(TAEF::GetDeploymentDir(), GetTestPackageFile(), L".msix"); // Installs PushNotificationsTestApp.msix
            }
            catch (...)
            {
                return false;
            }

            m_testAppLauncher = winrt::create_instance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_ALL);
#endif
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
#if 0
            try
            {
                // Remove in reverse order to avoid conflicts between inter-dependent packages.
                TP::RemovePackage(GetTestPackageFullName());
                TP::RemovePackage_PushNotificationsLongRunningTask();
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();
            }
            catch (...)
            {
                return false;
            }
#endif
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
#if 0
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());
#endif
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
#if 0
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());

            m_processHandle.reset();
#endif
            return true;
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
		
        void RunTest(const PCWSTR& testName, const int& waitTime)
        {
            DWORD processId {};
            VERIFY_SUCCEEDED(m_testAppLauncher->ActivateApplication(L"PushNotificationsTestAppPackage_8wekyb3d8bbwe!App", testName, AO_NONE, &processId));

            m_processHandle.reset(OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId));
            VERIFY_IS_TRUE(m_processHandle.is_valid());

            VERIFY_IS_TRUE(wil::handle_wait(m_processHandle.get(), waitTime));

            DWORD exitCode {};
            VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(m_processHandle.get(), &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0);
        }

        const std::wstring GetDeploymentDir()
        {
            WEX::Common::String deploymentDir;
            WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", deploymentDir);
            return reinterpret_cast<PCWSTR>(deploymentDir.GetBuffer());
        }

        void RunTestUnpackaged(const PCWSTR& testName, const int& waitTime)
        {
            auto processHandle = RunUnpackaged(L"PushNotificationsTestApp.exe", testName, GetDeploymentDir());
            VERIFY_IS_TRUE(processHandle.is_valid());

            VERIFY_IS_TRUE(wil::handle_wait(processHandle.get(), channelTestWaitTime()));

            DWORD exitCode{};
            VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(processHandle.get(), &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0);
        }

        TEST_METHOD(BackgroundActivation)
        {
#if 0
            RunTest(L"BackgroundActivationTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto LocalBackgroundTask = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance = winrt::make<MockBackgroundTaskInstance>();
            VERIFY_NO_THROW(LocalBackgroundTask.Run(mockBackgroundTaskInstance));
#endif
        }

        TEST_METHOD(BackgroundActivation_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"BackgroundActivationTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto LocalBackgroundTask = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance = winrt::make<MockBackgroundTaskInstance>();
            VERIFY_NO_THROW(LocalBackgroundTask.Run(mockBackgroundTaskInstance));
#endif
        }

        TEST_METHOD(MultipleBackgroundActivation)
        {
#if 0
            RunTest(L"BackgroundActivationTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto LocalBackgroundTask1 = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance1 = winrt::make<MockBackgroundTaskInstance>();

            auto LocalBackgroundTask2 = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance2 = winrt::make<MockBackgroundTaskInstance>();

            VERIFY_NO_THROW(LocalBackgroundTask1.Run(mockBackgroundTaskInstance1));
            VERIFY_NO_THROW(LocalBackgroundTask2.Run(mockBackgroundTaskInstance2));
#endif
        }

        TEST_METHOD(MultipleBackgroundActivation_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"BackgroundActivationTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto LocalBackgroundTask1 = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance1 = winrt::make<MockBackgroundTaskInstance>();

            auto LocalBackgroundTask2 = winrt::create_instance<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(c_comServerId, CLSCTX_ALL);
            auto mockBackgroundTaskInstance2 = winrt::make<MockBackgroundTaskInstance>();

            VERIFY_NO_THROW(LocalBackgroundTask1.Run(mockBackgroundTaskInstance1));
            VERIFY_NO_THROW(LocalBackgroundTask2.Run(mockBackgroundTaskInstance2));
#endif
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
#if 0
            RunTest(L"ChannelRequestUsingNullRemoteId", testWaitTime());
#endif
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"ChannelRequestUsingNullRemoteId", testWaitTime());
#endif
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
#if 0
            RunTest(L"ChannelRequestUsingRemoteId", channelTestWaitTime());
#endif
        }

        TEST_METHOD(ChannelRequestUsingRemoteId_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"ChannelRequestUsingRemoteId", channelTestWaitTime());
#endif
        }

        TEST_METHOD(MultipleChannelClose_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"MultipleChannelClose", channelTestWaitTime());
#endif
        }

        TEST_METHOD(MultipleChannelRequestUsingSameRemoteId)
        {
#if 0
            RunTest(L"MultipleChannelRequestUsingSameRemoteId", channelTestWaitTime());
#endif
        }

        TEST_METHOD(MultipleChannelRequestUsingSameRemoteId_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"MultipleChannelRequestUsingSameRemoteId", channelTestWaitTime());
#endif
        }

        TEST_METHOD(MultipleChannelRequestUsingMultipleRemoteId)
        {
#if 0
            RunTest(L"MultipleChannelRequestUsingMultipleRemoteId", channelTestWaitTime());
#endif
        }

        TEST_METHOD(MultipleChannelRequestUsingMultipleRemoteId_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"MultipleChannelRequestUsingMultipleRemoteId", channelTestWaitTime());
#endif
        }

        TEST_METHOD(ActivatorTest)
        {
#if 0
            try
            {
                TP::AddPackage_WindowsAppRuntimeFramework();       // Installs WARfwk
//                TP::AddPackage_DynamicDependencyDataStore();       // Installs WARmain
//                TP::AddPackage_DynamicDependencyLifetimeManager(); // Installs WARddlm
//                TP::AddPackage_PushNotificationsLongRunningTask(); // Installs the PushNotifications long running task.
//                TP::WapProj::AddPackage(TAEF::GetDeploymentDir(), GetTestPackageFile(), L".msix"); // Installs PushNotificationsTestApp.msix
            }
            catch (...)
            {
                VERIFY_FAIL();
            }

            m_testAppLauncher = winrt::create_instance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_ALL);

            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());
#endif
            RunTest(L"ActivatorTest", testWaitTime());
#if 0
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());

            m_processHandle.reset();

            try
            {
                // Remove in reverse order to avoid conflicts between inter-dependent packages.
                TP::RemovePackage(GetTestPackageFullName());
                TP::RemovePackage_PushNotificationsLongRunningTask();
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();
            }
            catch (...)
            {
                VERIFY_FAIL();
            }
#endif
        }

        TEST_METHOD(ActivatorTest_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"ActivatorTest", channelTestWaitTime());
#endif
        }

        TEST_METHOD(RegisterActivatorNullDetails)
        {
#if 0
            RunTest(L"RegisterActivatorNullDetails", testWaitTime());
#endif
        }

        TEST_METHOD(RegisterActivatorNullDetails_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"RegisterActivatorNullDetails", testWaitTime());
#endif
        }

        TEST_METHOD(RegisterActivatorNullClsid)
        {
#if 0
            RunTest(L"RegisterActivatorNullClsid", testWaitTime());
#endif
        }

        TEST_METHOD(RegisterActivatorNullClsid_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"RegisterActivatorNullClsid", testWaitTime());
#endif
        }

        TEST_METHOD(MultipleRegisterActivatorTest)
        {
#if 0
            RunTest(L"MultipleRegisterActivatorTest", testWaitTime());
#endif
        }

        TEST_METHOD(MultipleRegisterActivatorTest_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"MultipleRegisterActivatorTest", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyComActivatorSupported)
        {
#if 0
            RunTest(L"VerifyComActivatorSupported", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyComActivatorNotSupported_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"VerifyComActivatorNotSupported", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyProtocolActivatorSupported_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"VerifyProtocolActivatorSupported", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyProtocolActivatorNotSupported)
        {
#if 0
            RunTest(L"VerifyProtocolActivatorNotSupported", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyComAndProtocolActivatorNotSupported)
        {
#if 0
            RunTest(L"VerifyComAndProtocolActivatorNotSupported", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyComAndProtocolActivatorNotSupported_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"VerifyComAndProtocolActivatorNotSupported", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyNullActivatorNotSupported)
        {
#if 0
            RunTest(L"VerifyNullActivatorNotSupported", testWaitTime());
#endif
        }

        TEST_METHOD(VerifyProtocolActivation_Unpackaged)
        {
#if 0
            RunTestUnpackaged(L"----WindowsAppRuntimePushServer:-Payload:\"<toast></toast>\"", testWaitTime());
#endif
        }
    };
}
