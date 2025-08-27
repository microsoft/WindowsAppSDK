// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <TestDef.h>
#include <TlHelp32.h>
#include <NotificationsLongRunningProcess_h.h>
#include "NotificationPlatformActivation.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System;

namespace Test::LRP
{
    static const PCWSTR c_processName = L"TAEF.exe";
    static const PCWSTR c_appId = L"toastAppId";
    static const winrt::guid c_remoteId{ winrt::guid_of<INotificationsLongRunningPlatform>() }; // Add this line

    class LRPTests
    {

    public:
        BEGIN_TEST_CLASS(LRPTests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK Push Notifications Long Running Process tests")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        wil::com_ptr<INotificationsLongRunningPlatform> GetNotificationPlatform()
        {
            auto notificationPlatform{ NotificationPlatform::GetNotificationPlatform() };
            VERIFY_IS_NOT_NULL(notificationPlatform);

            return notificationPlatform;
        }

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages(Test::Bootstrap::Packages::Framework | Test::Bootstrap::Packages::Singleton);
            
            // Launch the LRP service so COM interface becomes available
            LaunchLRPService();
            
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            // Stop the LRP service
            StopLRPService();
            
            ::Test::Bootstrap::CleanupPackages(Test::Bootstrap::Packages::Framework | Test::Bootstrap::Packages::Singleton);
            return true;
        }

        void LaunchLRPService()
        {
            // Only launch if not already running
            if (!IsLRPRunning())
            {
                STARTUPINFO startupInfo{};
                ZeroMemory(&startupInfo, sizeof(startupInfo));
                startupInfo.cb = sizeof(startupInfo);

                auto startupTaskExePath{ Test::FileSystem::GetSolutionOutDirPath() / Test::Packages::WindowsAppRuntimeSingleton::c_PackageDirName };
                startupTaskExePath += LR"(.Msix/msix/PushNotificationsLongRunningTask.StartupTask.exe)";

                wil::unique_process_information processInfo;
                VERIFY_NO_THROW(winrt::check_bool(CreateProcess(
                    startupTaskExePath.c_str(),
                    nullptr,
                    nullptr,
                    nullptr,
                    FALSE,
                    NORMAL_PRIORITY_CLASS,
                    nullptr,
                    nullptr,
                    &startupInfo,
                    &processInfo)));

                // Wait for the service to be ready
                Sleep(2000);
                VERIFY_IS_TRUE(IsLRPRunning());
            }
        }

        void StopLRPService()
        {
            // Find and terminate the LRP process
            wil::unique_handle processesSnapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
            if (processesSnapshot.get() != INVALID_HANDLE_VALUE)
            {
                PROCESSENTRY32 processEntry{};
                processEntry.dwSize = sizeof(processEntry);

                BOOL result{ Process32First(processesSnapshot.get(), &processEntry) };
                while (result != FALSE)
                {
                    if (wcscmp(L"PushNotificationsLongRunningTask.exe", processEntry.szExeFile) == 0)
                    {
                        wil::unique_handle processHandle(OpenProcess(PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID));
                        if (processHandle.get())
                        {
                            TerminateProcess(processHandle.get(), 0);
                            WaitForSingleObject(processHandle.get(), 5000);
                        }
                        break;
                    }
                    result = Process32Next(processesSnapshot.get(), &processEntry);
                }
            }
        }

        bool IsLRPRunning()
        {
            wil::unique_handle processesSnapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
            if (processesSnapshot.get() == INVALID_HANDLE_VALUE)
                return false;

            PROCESSENTRY32 processEntry{};
            processEntry.dwSize = sizeof(processEntry);

            BOOL result{ Process32First(processesSnapshot.get(), &processEntry) };
            while (result != FALSE)
            {
                if (wcscmp(L"PushNotificationsLongRunningTask.exe", processEntry.szExeFile) == 0)
                {
                    return true;
                }
                result = Process32Next(processesSnapshot.get(), &processEntry);
            }
            return false;
        }

        void VerifyLRP_IsRunning(bool isRunning)
        {
            VERIFY_ARE_EQUAL(IsLRPRunning(), isRunning);
        }

        TEST_METHOD(LaunchLRP_FromStartupTask)
        {
            // Stop any existing LRP service first for this test
            StopLRPService();
            VerifyLRP_IsRunning(false);

            LaunchLRPService();
            VerifyLRP_IsRunning(true);
        }

        TEST_METHOD(RegisterUnregisterLongRunningActivator)
        {
            auto notificationPlatform{ GetNotificationPlatform() };

            wil::unique_cotaskmem_string lrpAppId;
            VERIFY_NO_THROW(notificationPlatform->RegisterFullTrustApplication(c_processName, winrt::guid(), &lrpAppId));
            VERIFY_NO_THROW(notificationPlatform->RegisterLongRunningActivator(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterLongRunningActivator(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterFullTrustApplication(c_processName));
        }

        TEST_METHOD(RegisterUnregisterLongRunningActivatorWithClsid)
        {
            auto notificationPlatform{ GetNotificationPlatform() };

            wil::unique_cotaskmem_string lrpAppId;
            VERIFY_NO_THROW(notificationPlatform->RegisterFullTrustApplication(c_processName, c_remoteId, &lrpAppId));
            VERIFY_NO_THROW(notificationPlatform->RegisterLongRunningActivatorWithClsid(c_processName, c_remoteId));
            VERIFY_NO_THROW(notificationPlatform->UnregisterLongRunningActivator(c_processName));
            VERIFY_NO_THROW(notificationPlatform->UnregisterFullTrustApplication(c_processName));
        }

        TEST_METHOD(AddRemoveToastRegistrationMappingNoSink)
        {
            auto notificationPlatform{ GetNotificationPlatform() };

            VERIFY_NO_THROW(notificationPlatform->AddToastRegistrationMapping(c_processName, c_appId));
            VERIFY_NO_THROW(notificationPlatform->RemoveToastRegistrationMapping(c_processName));
        }

        TEST_METHOD(AddRemoveToastRegistrationMappingWithSink)
        {
            auto notificationPlatform{ GetNotificationPlatform() };

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
