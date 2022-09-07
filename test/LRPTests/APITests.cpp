// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include <TlHelp32.h>
#include <NotificationsLongRunningProcess_h.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System;

namespace Test::LRP
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
            ::Test::Bootstrap::SetupPackages(Test::Bootstrap::Packages::Singleton);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::CleanupPackages(Test::Bootstrap::Packages::Singleton);
            return true;
        }

        TEST_METHOD(LaunchLRP_FromStartupTask)
        {
            VerifyLRP_IsRunning(false);

            STARTUPINFO startupInfo{};
            ZeroMemory(&startupInfo, sizeof(startupInfo));
            startupInfo.cb = sizeof(startupInfo);

            // Build the Solution OutDir path where the Startup Task exe is.
            // Path: $OutDir/WindowsAppRuntime.Test.Singleton.Msix/msix/PushNotificationsLongRunningTask.StartupTask.exe
            auto startupTaskExePath{ Test::FileSystem::GetSolutionOutDirPath() / Test::Packages::WindowsAppRuntimeSingleton::c_PackageDirName };
            startupTaskExePath += LR"(.Msix/msix/PushNotificationsLongRunningTask.StartupTask.exe)";

            wil::unique_process_information processInfo;
            BOOL wasProcessCreated{ CreateProcess(
                startupTaskExePath.c_str(),
                nullptr, // command line options
                nullptr, // process attributes
                nullptr, // thread attributes
                FALSE,   // inherit handles
                NORMAL_PRIORITY_CLASS, // creation flags
                nullptr, // lpEnvironment
                nullptr, // current directory for the process
                &startupInfo,
                &processInfo) };

            if (wasProcessCreated == FALSE)
            {
                VERIFY_SUCCEEDED(GetLastError());
            }

            // Wait for the process to come up and be captured in the snapshot from verification step.
            Sleep(1000);
            VerifyLRP_IsRunning(true);
        }

        void VerifyLRP_IsRunning(bool isRunning)
        {
            wil::unique_handle processesSnapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
            VERIFY_IS_NOT_NULL(processesSnapshot.get());

            PROCESSENTRY32 processEntry{};
            processEntry.dwSize = sizeof(processEntry);

            BOOL result{ Process32First(processesSnapshot.get(), &processEntry) };
            while (result != FALSE)
            {
                if (wcscmp(L"PushNotificationsLongRunningTask.exe", processEntry.szExeFile) == 0)
                {
                    VERIFY_IS_TRUE(isRunning);
                    DWORD processId{ processEntry.th32ProcessID };

                    wil::unique_handle longRunningProcessHandle(OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processId));
                    DWORD exitCode{};
                    BOOL exitCodeProcess{ GetExitCodeProcess(longRunningProcessHandle.get(), &exitCode) };

                    VERIFY_SUCCEEDED(exitCodeProcess == FALSE ? GetLastError() : S_OK);
                    VERIFY_ARE_EQUAL(exitCode, STILL_ACTIVE);

                    return;
                }

                result = Process32Next(processesSnapshot.get(), &processEntry);
            }

            VERIFY_IS_FALSE(isRunning);
        }

        TEST_METHOD(LaunchLRP_FromCoCreateInstance)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());
        }

        TEST_METHOD(RegisterUnregisterLongRunningActivator)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());

            wil::unique_cotaskmem_string lrpAppId;
            VERIFY_NO_THROW(notificationPlatform->RegisterFullTrustApplication(c_processName, winrt::guid(), &lrpAppId));
            VERIFY_NO_THROW(notificationPlatform->RegisterLongRunningActivator(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterLongRunningActivator(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterFullTrustApplication(c_processName));
        }

        TEST_METHOD(RegisterUnregisterLongRunningActivatorWithClsid)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());

            wil::unique_cotaskmem_string lrpAppId;
            VERIFY_NO_THROW(notificationPlatform->RegisterFullTrustApplication(c_processName, c_remoteId, &lrpAppId));
            VERIFY_NO_THROW(notificationPlatform->RegisterLongRunningActivatorWithClsid(c_processName, c_remoteId));
            VERIFY_NO_THROW(notificationPlatform->UnregisterLongRunningActivator(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterFullTrustApplication(c_processName));
        }

        TEST_METHOD(AddRemoveToastRegistrationMappingNoSink)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());

            VERIFY_NO_THROW(notificationPlatform->AddToastRegistrationMapping(c_processName, c_appId));
            VERIFY_NO_THROW(notificationPlatform->RemoveToastRegistrationMapping(c_processName));
        }

        TEST_METHOD(AddRemoveToastRegistrationMappingWithSink)
        {
            winrt::com_ptr notificationPlatform{ winrt::try_create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL) };
            VERIFY_IS_NOT_NULL(notificationPlatform.get());

            wil::unique_cotaskmem_string lrpAppId;
            VERIFY_NO_THROW(notificationPlatform->RegisterFullTrustApplication(c_processName, c_remoteId, &lrpAppId));
            VERIFY_NO_THROW(notificationPlatform->RegisterLongRunningActivator(lrpAppId.get()));
            VERIFY_NO_THROW(notificationPlatform->AddToastRegistrationMapping(c_processName, c_appId));
            VERIFY_NO_THROW(notificationPlatform->RemoveToastRegistrationMapping(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterLongRunningActivator(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterFullTrustApplication(c_processName));
        }
    };
}
