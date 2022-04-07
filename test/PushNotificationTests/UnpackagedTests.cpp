// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "MockBackgroundTaskInstance.h"
#include <TlHelp32.h>
#include "TestFunctions.h"

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
using namespace winrt::Microsoft::Windows::PushNotifications;

namespace Test::PushNotifications
{
    #define VERIFY_THROWS_HR(expression, hr)        \
        VERIFY_THROWS_SPECIFIC(expression,          \
            winrt::hresult_error,                   \
            [&](winrt::hresult_error e) -> bool     \
            {                                       \
                return (e.code() == hr);    \
            })

    class UnpackagedTests
    {
    public:
        BEGIN_TEST_CLASS(UnpackagedTests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK Push Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            try
            {
                // Cleanup previous installations. Need this to remove any manual installations outside of running this tests.
                TP::RemovePackage_PushNotificationsLongRunningTask();
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();

                TP::AddPackage_WindowsAppRuntimeFramework();       // Installs WARfwk
                TP::AddPackage_DynamicDependencyDataStore();       // Installs WARmain
                TP::AddPackage_DynamicDependencyLifetimeManager(); // Installs WARddlm
                TP::AddPackage_PushNotificationsLongRunningTask(); // Installs the PushNotifications long running task.
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        void TerminateLRP()
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
                    DWORD processId = processEntry.th32ProcessID;

                    wil::unique_handle longRunningProcessHandle(OpenProcess(PROCESS_TERMINATE, FALSE, processId));
                    VERIFY_IS_TRUE(TerminateProcess(longRunningProcessHandle.get(), 0));
                    ::WaitForSingleObject(longRunningProcessHandle.get(), 10000);
                    return;
                }

                result = Process32Next(processesSnapshot.get(), &processEntry);
            }
        }
        
        TEST_CLASS_CLEANUP(ClassUninit)
        {
            try
            {
                // Remove in reverse order to avoid conflicts between inter-dependent packages.
                TerminateLRP();
                TP::RemovePackage_PushNotificationsLongRunningTask();
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();
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

            VERIFY_ARE_EQUAL(S_OK, MddBootstrapTestInitialize(Test::Packages::DynamicDependencyLifetimeManager::c_PackageNamePrefix, Test::Packages::DynamicDependencyLifetimeManager::c_PackagePublisherId));

            // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
            const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
            const PACKAGE_VERSION c_minVersion{};
            VERIFY_ARE_EQUAL(S_OK, MddBootstrapInitialize(c_Version_MajorMinor, nullptr, c_minVersion));

            // Need to use SelfContained test hook to setup tests.
            ::WindowsAppRuntime::SelfContained::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);

            // Need to keep each TEST_METHOD in a clean state in the LRP.
            try
            {
                PushNotificationManager::Default().UnregisterAll();
            }
            catch (...)
            {
                // We want to unregister regardless of pass/fail to clean the state.
            }
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            MddBootstrapShutdown();

            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());
            TerminateLRP();

            return true;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            TestFunctions::ChannelRequestUsingNullRemoteId();
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
            TestFunctions::ChannelRequestUsingRemoteId();
        }

        // Currently failing.
        TEST_METHOD(MultipleChannelClose)
        {
            TestFunctions::MultipleChannelClose();
        }

        TEST_METHOD(VerifyRegisterAndUnregister)
        {
            TestFunctions::VerifyRegisterAndUnregister();
        }

        TEST_METHOD(VerifyRegisterAndUnregisterAll)
        {
            TestFunctions::VerifyRegisterAndUnregisterAll();
        }

        TEST_METHOD(MultipleRegister)
        {
            TestFunctions::MultipleRegister();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregister)
        {
            TestFunctions::VerifyMultipleRegisterAndUnregister();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregisterAll)
        {
            TestFunctions::VerifyMultipleRegisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterTwice)
        {
            TestFunctions::VerifyUnregisterTwice();
        }

        TEST_METHOD(VerifyUnregisterAll)
        {
            TestFunctions::VerifyUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterAllTwice)
        {
            TestFunctions::VerifyUnregisterAllTwice();
        }

        TEST_METHOD(VerifyUnregisterAndUnregisterAll)
        {
            TestFunctions::VerifyUnregisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyForegroundHandlerSucceeds)
        {
            TestFunctions::VerifyForegroundHandlerSucceeds();
        }

        TEST_METHOD(VerifyForegroundHandlerFails)
        {
            TestFunctions::VerifyForegroundHandlerFails();
        }
    };
}
