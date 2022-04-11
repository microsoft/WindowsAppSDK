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
    class UnpackagedSelfContainedTests
    {

    public:
        BEGIN_TEST_CLASS(UnpackagedSelfContainedTests)
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

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            try
            {

                // Remove in reverse order to avoid conflicts between inter-dependent packages.
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

            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            // Need to keep each TEST_METHOD in a clean state in the LRP.
            try
            {
                PushNotificationManager::Default().UnregisterAll();
            }
            catch (...)
            {
                // We want to unregister regardless of pass/fail to clean the state.
            }
            MddBootstrapShutdown();

            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());

            return true;
        }

        HRESULT ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
        {
            if (channelOperation.wait_for(c_timeout) != winrt::Windows::Foundation::AsyncStatus::Completed)
            {
                channelOperation.Cancel();
                return HRESULT_FROM_WIN32(ERROR_TIMEOUT); // timed out or failed
            }

            auto result{ channelOperation.GetResults() };
            auto status{ result.Status() };
            if (status != PushNotificationChannelStatus::CompletedSuccess)
            {
                return result.ExtendedError(); // did not produce a channel
            }

            result.Channel().Close();
            return S_OK;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(winrt::guid()) };
            VERIFY_ARE_EQUAL(ChannelRequestHelper(channelOperation), E_FAIL);
        }

        TEST_METHOD(ChannelRequestUsingRemoteId)
        {
            auto channelOperation{ PushNotificationManager::Default().CreateChannelAsync(c_azureRemoteId) };
            VERIFY_ARE_EQUAL(ChannelRequestHelper(channelOperation), E_FAIL);
        }

        // Currently failing.
        TEST_METHOD(MultipleChannelClose)
        {
            PushNotificationTestFunctions::MultipleChannelClose();
        }

        TEST_METHOD(VerifyRegisterAndUnregister)
        {
            PushNotificationTestFunctions::VerifyRegisterAndUnregister();
        }

        TEST_METHOD(VerifyRegisterAndUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyRegisterAndUnregisterAll();
        }

        TEST_METHOD(MultipleRegister)
        {
            auto pushNotificationManager{ PushNotificationManager::Default() };
            pushNotificationManager.Register();
            pushNotificationManager.Register();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregister)
        {
            PushNotificationManager::Default().Register();
            PushNotificationManager::Default().Unregister();
            PushNotificationManager::Default().Register();
        }

        TEST_METHOD(VerifyMultipleRegisterAndUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyMultipleRegisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterTwice)
        {
            PushNotificationManager::Default().Register();
            PushNotificationManager::Default().Unregister();
            PushNotificationManager::Default().Unregister();
        }

        TEST_METHOD(VerifyUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyUnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterAllTwice)
        {
            PushNotificationManager::Default().Register();
            PushNotificationManager::Default().UnregisterAll();
            PushNotificationManager::Default().UnregisterAll();
        }

        TEST_METHOD(VerifyUnregisterAndUnregisterAll)
        {
            PushNotificationTestFunctions::VerifyUnregisterAndUnregisterAll();
        }

        TEST_METHOD(VerifyForegroundHandlerSucceeds)
        {
            PushNotificationTestFunctions::VerifyForegroundHandlerSucceeds();
        }

        TEST_METHOD(VerifyForegroundHandlerFails)
        {
            PushNotificationManager::Default().Register();
            PushNotificationManager::Default().PushReceived([](const auto&, PushNotificationReceivedEventArgs const& /* args */) {});
        }
    };
}
