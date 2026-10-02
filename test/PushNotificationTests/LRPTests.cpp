// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "MockBackgroundTaskInstance.h"
#include <TlHelp32.h>

#include <NotificationsLongRunningProcess_h.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System;

namespace Test::PushNotifications
{
    static const PCWSTR c_processName = L"TAEF.exe";
    static const PCWSTR c_appId = L"toastAppId";
    class LRPTests
    {

    public:
        BEGIN_TEST_CLASS(LRPTests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK Push Notifications Long Running Process tests")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            try
            {
                VERIFY_SUCCEEDED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));
                TP::RemovePackage_PushNotificationsLongRunningTask();
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();

                TP::AddPackage_WindowsAppRuntimeFramework();       // Installs WASfwk
                TP::AddPackage_DynamicDependencyDataStore();       // Installs WASmain
                TP::AddPackage_DynamicDependencyLifetimeManager(); // Installs WASddlm
                TP::AddPackage_PushNotificationsLongRunningTask(); // Installs the Push Notifications Long Running Process (LRP).
            }
            catch (...)
            {
                return false;
            }

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            try
            {
                // Remove in reverse order to avoid conflicts between inter-dependent packages.
                TP::RemovePackage_PushNotificationsLongRunningTask();
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();
                VERIFY_NO_THROW(CoUninitialize());
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());

            return true;
        }

        TEST_METHOD(LaunchLRP_FromCoCreateInstance)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());
        }

        TEST_METHOD(LaunchLRP_FromStartupTask)
        {
            STARTUPINFO startupInfo = { 0 };
            wil::unique_process_information processInfo;

            ZeroMemory(&startupInfo, sizeof(startupInfo));
            startupInfo.cb = sizeof(startupInfo);

            // Build the Solution OutDir path where the Startup Task exe is.
            auto startupTaskExePath = Test::FileSystem::GetSolutionOutDirPath();
            startupTaskExePath /= Test::Packages::PushNotificationsLongRunningTask::c_PackageDirName;
            startupTaskExePath += L".Msix";
            startupTaskExePath /= L"msix";
            startupTaskExePath /= L"PushNotificationsLongRunningTask.StartupTask.exe";

            BOOL wasProcessCreated = CreateProcess(
                startupTaskExePath.c_str(),
                nullptr, // command line options
                nullptr, // process attributes
                nullptr, // thread attributes
                FALSE,   // inherit handles
                NORMAL_PRIORITY_CLASS, // creation flags
                nullptr, // lpEnvironment
                nullptr, // current directory for the process
                &startupInfo,
                &processInfo
            );

            if (wasProcessCreated == FALSE)
            {
                VERIFY_SUCCEEDED(GetLastError());
            }

            // Wait for the process to come up and be captured in the snapshot from verification step.
            Sleep(1000);

            // Poll the app status every second. It should be alive for 5 seconds.
            for (int i = 0; i < 5; i++)
            {
                VerifyLRP_IsRunning(true);
                Sleep(1000);
            }

            // Verify the LRP is not running.
            VerifyLRP_IsRunning(false);
        }

        void VerifyLRP_IsRunning(bool isRunning)
        {
            wil::unique_handle processesSnapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
            VERIFY_IS_NOT_NULL(processesSnapshot.get());

            PROCESSENTRY32 processEntry = { 0 };
            processEntry.dwSize = sizeof(processEntry);

            BOOL result = Process32First(processesSnapshot.get(), &processEntry);
            while (result != FALSE)
            {
                if (wcscmp(L"PushNotificationsLongRunningTask.exe", processEntry.szExeFile) == 0)
                {
                    VERIFY_IS_TRUE(isRunning);
                    DWORD processId = processEntry.th32ProcessID;

                    wil::unique_handle longRunningProcessHandle(OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processId));
                    DWORD exitCode = 0;
                    BOOL exitCodeProcess = GetExitCodeProcess(longRunningProcessHandle.get(), &exitCode);

                    VERIFY_SUCCEEDED(exitCodeProcess == FALSE ? GetLastError() : S_OK);
                    VERIFY_ARE_EQUAL(exitCode, STILL_ACTIVE);

                    return;
                }

                result = Process32Next(processesSnapshot.get(), &processEntry);
            }

            VERIFY_IS_FALSE(isRunning);
        }

        TEST_METHOD(AddToastRegistrationMappingNoSink)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());

            VERIFY_NO_THROW(notificationPlatform->AddToastRegistrationMapping(c_processName, c_appId));
        }

        TEST_METHOD(RemoveToastRegistrationMappingNoSink)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());

            VERIFY_NO_THROW(notificationPlatform->RemoveToastRegistrationMapping(c_processName));
        }

        TEST_METHOD(AddRemoveToastRegistrationMappingWithSink)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());

            wil::unique_cotaskmem_string unpackagedAumid;
            VERIFY_NO_THROW(notificationPlatform->RegisterFullTrustApplication(c_processName, c_remoteId, &unpackagedAumid));
            VERIFY_NO_THROW(notificationPlatform->RegisterLongRunningActivator(unpackagedAumid.get()));
            VERIFY_NO_THROW(notificationPlatform->AddToastRegistrationMapping(c_processName, c_appId));
            VERIFY_NO_THROW(notificationPlatform->RemoveToastRegistrationMapping(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterLongRunningActivator(c_processName));
        }
    };
}
