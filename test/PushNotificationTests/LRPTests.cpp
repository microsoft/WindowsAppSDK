// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "MockBackgroundTaskInstance.h"

#include <NotificationsLongRunningProcess_h.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System;

namespace Test::PushNotifications
{
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
                TP::AddPackage_WindowsAppSDKFramework();           // Installs WASfwk
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
                TP::RemovePackage_WindowsAppSDKFramework();
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppSDKFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppSDKFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());

            return true;
        }

        TEST_METHOD(LaunchLRP_FromCoCreateInstance)
        {
            VERIFY_SUCCEEDED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

            auto scopeExit = wil::scope_exit(
                [&]() { VERIFY_NO_THROW(CoUninitialize()); });

            VERIFY_NO_THROW(winrt::create_instance<INotificationsLongRunningPlatform>(_uuidof(NotificationsLongRunningPlatform), CLSCTX_ALL));
        }

    };
}
