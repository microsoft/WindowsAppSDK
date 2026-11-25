// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "winrt/Microsoft.Windows.System.Power.h"

namespace Test::PowerNotifications::EnergySaverStatus2TestHelpers
{
    // Timeout in milliseconds
    constexpr auto c_timeoutInMSec{ 5000 };

    inline bool IsEnergySaverStatus2ApiPresent()
    {
        using winrt::Windows::Foundation::Metadata::ApiInformation;
        return ApiInformation::IsPropertyPresent(L"Windows.System.Power.PowerManager", L"EnergySaverStatus2") &&
            ApiInformation::IsEventPresent(L"Windows.System.Power.PowerManager", L"EnergySaverStatus2Changed");
    }

    inline void Verify_GetEnergySaverStatus2()
    {
        using namespace winrt::Microsoft::Windows::System::Power;

        auto value = PowerManager::EnergySaverStatus2();
        VERIFY_IS_TRUE(value == EnergySaverStatus2::Unknown ||
                       value == EnergySaverStatus2::Off ||
                       value == EnergySaverStatus2::Standard ||
                       value == EnergySaverStatus2::HighSavings);
    }

    inline void Verify_EnergySaverStatus2Callback()
    {
        using namespace winrt::Microsoft::Windows::System::Power;

        if (!IsEnergySaverStatus2ApiPresent())
        {
            VERIFY_THROWS_HR(PowerManager::EnergySaverStatus2Changed(
                [](const auto&, winrt::Windows::Foundation::IInspectable) {}), E_NOTIMPL);
            return;
        }

        wil::unique_handle event(CreateEvent(nullptr, false, false, nullptr));
        THROW_LAST_ERROR_IF_NULL(event.get());
        auto value = EnergySaverStatus2::Unknown;
        auto token = PowerManager::EnergySaverStatus2Changed([&](const auto&, winrt::Windows::Foundation::IInspectable /*obj*/)
            {
                value = PowerManager::EnergySaverStatus2();
                SetEvent(event.get());
            });

        if (WaitForSingleObject(event.get(), c_timeoutInMSec) == WAIT_OBJECT_0)
        {
            VERIFY_IS_TRUE(value == EnergySaverStatus2::Unknown ||
                           value == EnergySaverStatus2::Off ||
                           value == EnergySaverStatus2::Standard ||
                           value == EnergySaverStatus2::HighSavings);
        }
        PowerManager::EnergySaverStatus2Changed(token);
    }

    inline void Verify_EnergySaverStatus2SeededOnSubscribe()
    {
        using namespace winrt::Microsoft::Windows::System::Power;

        if (!IsEnergySaverStatus2ApiPresent())
        {
            VERIFY_THROWS_HR(PowerManager::EnergySaverStatus2Changed(
                [](const auto&, winrt::Windows::Foundation::IInspectable) {}), E_NOTIMPL);
            return;
        }

        auto directValue = PowerManager::EnergySaverStatus2();
        auto token = PowerManager::EnergySaverStatus2Changed([](const auto&, winrt::Windows::Foundation::IInspectable) {});
        auto subscribedValue = PowerManager::EnergySaverStatus2();
        PowerManager::EnergySaverStatus2Changed(token);

        VERIFY_ARE_EQUAL(subscribedValue, directValue);
    }
}
