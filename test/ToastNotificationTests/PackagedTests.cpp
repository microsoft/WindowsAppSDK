// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include <TlHelp32.h>

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
using namespace winrt::Microsoft::Windows::AppNotifications;

namespace Test::AppNotifications
{
    class PackagedTests
    {

    public:
        BEGIN_TEST_CLASS(PackagedTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"AppNotifications-AppxManifest.xml")
            TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCWA")
            END_TEST_CLASS()

            TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            ::WindowsAppRuntime::SelfContained::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            // Need to keep each TEST_METHOD in clean state.
            try
            {
                AppNotificationManager::Default().UnregisterAll();
            }
            catch (...)
            {
                // We want to unregister regardless of pass/fail to clean the state.
            }
            return true;
        }

        AppNotification CreateToastNotification(winrt::hstring message)
        {
            winrt::hstring xmlPayload{ L"<toast>" + message + L"</toast>" };
            return AppNotification(xmlPayload);
        }

        AppNotification CreateToastNotification()
        {
            return CreateToastNotification(L"intrepidToast");
        }

        void EnsureNoActiveToasts()
        {
            auto removeAllAsync = AppNotificationManager::Default().RemoveAllAsync();
            if (removeAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
            {
                removeAllAsync.Cancel();
                THROW_HR_MSG(E_FAIL, "Failed to remove all active toasts");
            }
        }

        bool VerifyToastIsActive(UINT32 expectedToastId)
        {
            auto retrieveNotificationsAsync{ AppNotificationManager::Default().GetAllAsync() };
            if (retrieveNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
            {
                retrieveNotificationsAsync.Cancel();
                return false;
            }

            auto notifications = retrieveNotificationsAsync.get();

            bool found{ false };
            for (auto notification : notifications)
            {
                if (notification.Id() == expectedToastId)
                {
                    found = true;
                    break;
                }
            }

            return found;
        }

        bool VerifyProgressData(const AppNotificationProgressData& expected, const AppNotificationProgressData& actual)
        {
            if (!expected && !actual)
            {
                return true;
            }

            if (!expected || !actual)
            {
                return false;
            }

            if (expected.Status() != actual.Status())
            {
                return false;
            }

            if (expected.Title() != actual.Title())
            {
                return false;
            }

            if (expected.Value() != actual.Value()) // Need an epsilon...
            {
                return false;
            }

            if (expected.ValueStringOverride() != actual.ValueStringOverride())
            {
                return false;
            }

            return true;
        }

        enum class ExpectedTransientProperties {
            EQUAL,    // Actual values are expected to be same as expected and will be checked.
            DEFAULT,  // Actual values are expected to have been defaulted and will be checked.
            UNKNOWN   // Actual values can't be determined and won't be checked.
        };
        bool VerifyToastNotificationIsValid(const AppNotification& expected, const AppNotification& actual, ExpectedTransientProperties expectedTransientProperties = ExpectedTransientProperties::EQUAL)
        {
            if (expected.Tag() != actual.Tag())
            {
                return false;
            }

            if (expected.Group() != actual.Group())
            {
                return false;
            }

            if (expected.Id() != actual.Id())
            {
                return false;
            }

            auto expectedPayload = expected.Payload();
            auto actualPayload = actual.Payload();
            if (expectedPayload != actualPayload)
            {
                return false;
            }

            if (!VerifyProgressData(expected.Progress(), actual.Progress()))
            {
                return false;
            }

            if (expected.Expiration() > actual.Expiration())
            {
                // External factors, like setting ProgressData can bump the expiration time.
                // We're happy as long as the actual expiration time is equal or larger than the expected
                return false;
            }

            if (expected.ExpiresOnReboot() != actual.ExpiresOnReboot())
            {
                return false;
            }

            switch (expectedTransientProperties)
            {
            case ExpectedTransientProperties::EQUAL:
                if (expected.Priority() != actual.Priority())
                {
                    return false;
                }

                if (expected.SuppressDisplay() != actual.SuppressDisplay())
                {
                    return false;
                }
                break;

            case ExpectedTransientProperties::DEFAULT:
                if (winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority::Default != actual.Priority())
                {
                    return false;
                }

                if (false != actual.SuppressDisplay())
                {
                    return false;
                }
                break;

            case ExpectedTransientProperties::UNKNOWN:
                // Nothing to validate here.
                break;

            default:
                // Unexpected selection
                return false;
            }

            return true;
        }

        AppNotificationProgressData GetToastProgressData(
            std::wstring const& status,
            std::wstring const& title,
            double const& progressValue,
            std::wstring const& progressValueString,
            uint32_t sequenceNumber)
        {
            AppNotificationProgressData progressData{ sequenceNumber };
            progressData.Status(status);
            progressData.Title(title);
            progressData.Value(progressValue);
            progressData.ValueStringOverride(progressValueString);
            return progressData;
        }

        bool ProgressResultOperationHelper(IAsyncOperation<AppNotificationProgressResult> progressResultOperation, AppNotificationProgressResult progressResult)
        {
            if (progressResultOperation.wait_for(std::chrono::seconds(2)) != winrt::Windows::Foundation::AsyncStatus::Completed)
            {
                progressResultOperation.Cancel();
                return false; // timed out or failed
            }

            return progressResultOperation.GetResults() == progressResult;
        }

        bool PostToastHelper(std::wstring const& tag, std::wstring const& group)
        {
            AppNotification toast{ CreateToastNotification() };

            toast.Tag(tag.c_str());
            toast.Group(group.c_str());

            AppNotificationManager::Default().Show(toast);

            if (toast.Id() == 0)
            {
                return false;
            }

            return true;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
        }
    };
}
