// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

namespace winrt
{
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Microsoft::Windows::AppNotifications;
    using namespace winrt::Windows::Foundation;
}

namespace AppNotifications::Test
{
    winrt::AppNotification CreateToastNotification(winrt::hstring message)
    {
        winrt::hstring xmlPayload{ LR"(<toast><visual><binding template="ToastGeneric"><text>)" + message + LR"(</text></binding></visual></toast>)" };

        return winrt::AppNotification(xmlPayload);
    }

    winrt::AppNotification CreateToastNotification()
    {
        return CreateToastNotification(L"intrepidToast");
    }

    void VerifyToastStatus(UINT32 expectedToastId, bool isToastActive)
    {
        auto retrieveNotificationsAsync{ winrt::AppNotificationManager::Default().GetAllAsync() };
        auto scope_exit = wil::scope_exit(
        [&] {
            retrieveNotificationsAsync.Cancel();
        });

        VERIFY_ARE_EQUAL(retrieveNotificationsAsync.wait_for(std::chrono::seconds(300)), winrt::AsyncStatus::Completed);
        scope_exit.release();

        auto notifications{ retrieveNotificationsAsync.get() };

        bool found{};
        for (auto notification : notifications)
        {
            if (notification.Id() == expectedToastId)
            {
                found = true;
                break;
            }
        }
        VERIFY_ARE_EQUAL(found, isToastActive);
    }

    void VerifyToastIsActive(UINT32 expectedToastId)
    {
        VerifyToastStatus(expectedToastId, true);
    }

    void VerifyToastIsInactive(UINT32 expectedToastId)
    {
        VerifyToastStatus(expectedToastId, false);
    }

    winrt::AppNotificationProgressData GetToastProgressData(
        std::wstring const& status,
        std::wstring const& title,
        double const& progressValue,
        std::wstring const& progressValueString,
        uint32_t sequenceNumber)
    {
        winrt::AppNotificationProgressData progressData{ sequenceNumber };
        progressData.Status(status);
        progressData.Title(title);
        progressData.Value(progressValue);
        progressData.ValueStringOverride(progressValueString);
        return progressData;
    }

    void ProgressResultOperationHelper(winrt::IAsyncOperation<winrt::AppNotificationProgressResult> progressResultOperation, winrt::AppNotificationProgressResult progressResult)
    {
        auto scope_exit = wil::scope_exit(
        [&] {
            progressResultOperation.Cancel();
        });

        VERIFY_ARE_EQUAL(progressResultOperation.wait_for(c_timeout), winrt::AsyncStatus::Completed);
        scope_exit.release();

        VERIFY_ARE_EQUAL(progressResultOperation.GetResults(), progressResult);
    }

    void VerifyProgressData(const winrt::AppNotificationProgressData& expected, const winrt::AppNotificationProgressData& actual)
    {
        VERIFY_IS_NOT_NULL(expected);
        VERIFY_IS_NOT_NULL(actual);

        VERIFY_ARE_EQUAL(expected.Status(), actual.Status());
        VERIFY_ARE_EQUAL(expected.Title(), actual.Title());
        VERIFY_ARE_EQUAL(expected.Value(), actual.Value());
        VERIFY_ARE_EQUAL(expected.ValueStringOverride(), actual.ValueStringOverride());
        VERIFY_ARE_EQUAL(expected.Status(), actual.Status());
    }

    enum class ExpectedTransientProperties {
        EQUAL,    // Actual values are expected to be same as expected and will be checked.
        DEFAULT,  // Actual values are expected to have been defaulted and will be checked.
        UNKNOWN   // Actual values can't be determined and won't be checked.
    };

    void VerifyToastNotificationIsValid(const winrt::AppNotification& expected, const winrt::AppNotification& actual, ExpectedTransientProperties expectedTransientProperties = ExpectedTransientProperties::EQUAL)
    {
        VERIFY_ARE_EQUAL(expected.Tag(), actual.Tag());
        VERIFY_ARE_EQUAL(expected.Group(), actual.Group());
        VERIFY_ARE_EQUAL(expected.Id(), actual.Id());
        VERIFY_ARE_EQUAL(expected.Payload(), actual.Payload());

        VerifyProgressData(expected.Progress(), actual.Progress());

        // External factors, like setting ProgressData can bump the expiration time.
        // We're happy as long as the actual expiration time is equal or larger than the expected
        VERIFY_IS_GREATER_THAN_OR_EQUAL(actual.Expiration(), expected.Expiration());

        VERIFY_ARE_EQUAL(expected.ExpiresOnReboot(), actual.ExpiresOnReboot());

        switch (expectedTransientProperties)
        {
        case ExpectedTransientProperties::EQUAL:
            VERIFY_ARE_EQUAL(expected.Priority(), actual.Priority());
            VERIFY_ARE_EQUAL(expected.SuppressDisplay(), actual.SuppressDisplay());
            break;

        case ExpectedTransientProperties::DEFAULT:
            // The default priority value is Default, and the default for SuppressDisplay is false.
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority::Default, actual.Priority());
            VERIFY_IS_FALSE(actual.SuppressDisplay());
            break;

        case ExpectedTransientProperties::UNKNOWN:
            // Nothing to validate here.
            break;

        default:
            // Unexpected selection
            VERIFY_FAIL();
        }
    }

    bool VerifyToastsPosted(std::vector<winrt::Microsoft::Windows::AppNotifications::AppNotification> const& expectedToastVector)
    {
        bool result{ false };
        for (int i { 0 }; i < 5; i++)
        {
            const auto start{ GetTickCount() };
            auto elapsed{ start };
            for (;;)
            {
                auto getAllAsync{ winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default().GetAllAsync() };
                auto scopeExitGetAll = wil::scope_exit(
                    [&] {
                        getAllAsync.Cancel();
                    });

                VERIFY_ARE_EQUAL(getAllAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
                scopeExitGetAll.release();

                auto actualToastVector{ getAllAsync.GetResults() };
                if (actualToastVector.Size() == expectedToastVector.size())
                {
                    for (uint32_t actualToastIndex{ 0 }; actualToastIndex < actualToastVector.Size(); actualToastIndex++)
                    {
                        for (uint32_t expectedToastIndex{ 0 }; expectedToastIndex < expectedToastVector.size(); expectedToastIndex++)
                        {
                            if (actualToastVector.GetAt(actualToastIndex).Id() == expectedToastVector[expectedToastIndex].Id())
                            {
                                VERIFY_ARE_EQUAL(actualToastVector.GetAt(actualToastIndex).Payload(), expectedToastVector[expectedToastIndex].Payload());
                                break;
                            }
                        }
                    }

                    result = true;
                    break;
                }
                else if (elapsed > c_sleepTimeout.count())
                {
                    break;
                }

                Sleep(static_cast<DWORD>(c_delay.count()));
            }
        }
        return result;
    }

    void PostToastHelper(std::wstring const& tag, std::wstring const& group)
    {
        winrt::AppNotification toast{ CreateToastNotification() };

        toast.Tag(tag.c_str());
        toast.Group(group.c_str());

        winrt::AppNotificationManager::Default().Show(toast);

        std::vector<winrt::AppNotification> toastVector{ toast };
        VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));
    }

    bool VerifyToastsCleared()
    {
        bool result{ false };
        for (int i{ 0 }; i < 5; i++)
        {
            const auto start{ GetTickCount() };
            auto elapsed{ start };
            for (;;)
            {
                auto getAllAsync{ winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default().GetAllAsync() };
                auto scopeExitGetAll = wil::scope_exit(
                    [&] {
                        getAllAsync.Cancel();
                    });

                VERIFY_ARE_EQUAL(getAllAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
                scopeExitGetAll.release();

                auto actualToastVector{ getAllAsync.GetResults() };
                if (actualToastVector.Size() == 0u)
                {
                    result = true;
                    break;
                }
                else if (elapsed > c_sleepTimeout.count())
                {
                    break;
                }

                Sleep(static_cast<DWORD>(c_delay.count()));
            }
        }
        return result;
    }

    bool EnsureNoActiveToasts()
    {
        auto removeAllAsync{ winrt::AppNotificationManager::Default().RemoveAllAsync() };
        if (removeAllAsync.wait_for(c_timeout) != winrt::Windows::Foundation::AsyncStatus::Completed)
        {
            removeAllAsync.Cancel();
            THROW_HR_MSG(E_UNEXPECTED, "Failed to remove all active toasts");
        }

        VERIFY_IS_TRUE(VerifyToastsCleared());
        return true;
    }
}
