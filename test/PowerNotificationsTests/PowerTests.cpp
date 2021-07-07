// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "winrt/Microsoft.ProjectReunion.h"

using PowerEventHandle =
winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>;

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionPowerTests
{
    constexpr auto TIMEOUT = 2000;
    class PowerTests
    {
    public:
        BEGIN_TEST_CLASS(PowerTests)
            TEST_CLASS_PROPERTY(L"ActivationContext", L"PowerTests.dll.manifest")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_METHOD(GetBatteryStatus)
        {
            auto stat = PowerManager::BatteryStatus();
            VERIFY_ARE_EQUAL(stat, BatteryStatus::NotPresent);
        }
        TEST_METHOD(GetPowerSupplyStatus)
        {
            auto stat = PowerManager::PowerSupplyStatus();
            VERIFY_ARE_EQUAL(stat, PowerSupplyStatus::Adequate);
        }
        TEST_METHOD(GetRemainingChargePercent)
        {
            auto stat = PowerManager::RemainingChargePercent();
            VERIFY_ARE_EQUAL(stat, 100);
        }

        TEST_METHOD(CompositeBatteryStatusCallback)
        {
            // This test can only be run on systems/VM with a battery
            // The values will need to be changed to reflect real-time values
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"Ignore", L"true")
            END_TEST_METHOD_PROPERTIES()

            auto batteryStat = BatteryStatus::Discharging;
            auto powerStat = PowerSupplyStatus::Inadequate;
            int32_t remainingCharge = 15;
            auto token = PowerManager::BatteryStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                batteryStat = PowerManager::BatteryStatus();
                powerStat = PowerManager::PowerSupplyStatus();
                remainingCharge = PowerManager::RemainingChargePercent();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            PowerManager::BatteryStatusChanged(token);
            VERIFY_ARE_EQUAL(batteryStat, BatteryStatus::Idle);
            VERIFY_ARE_EQUAL(powerStat, PowerSupplyStatus::Adequate);
            VERIFY_ARE_EQUAL(remainingCharge, 100);
        }

        TEST_METHOD(GetRemainingDischargeTime)
        {
            auto stat = PowerManager::RemainingDischargeTime();
            VERIFY_ARE_EQUAL(stat.count(), -10000000);
        }

        TEST_METHOD(RemainingDischargeTimeCallback)
        {
            static wil::unique_handle event(CreateEvent(nullptr, false, false, nullptr));
            THROW_LAST_ERROR_IF_NULL(event.get());

            auto stat = winrt::Windows::Foundation::TimeSpan(std::chrono::seconds(1));
            auto token = PowerManager::RemainingDischargeTimeChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                SetEvent(event.get());
                stat = PowerManager::RemainingDischargeTime();
            });
            PowerManager::RemainingDischargeTimeChanged(token);           

            VERIFY_IS_TRUE(WaitForSingleObject(event.get(), TIMEOUT) == WAIT_OBJECT_0);
            VERIFY_ARE_EQUAL(stat.count(), -10000000);
        }

        TEST_METHOD(GetEnergySaverStatus)
        {
            auto stat = PowerManager::EnergySaverStatus();
            VERIFY_ARE_EQUAL(stat, EnergySaverStatus::Disabled);
        }

        TEST_METHOD(EnergySaverStatusCallback)
        {
            auto stat = EnergySaverStatus::Disabled;
            auto token = PowerManager::EnergySaverStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::EnergySaverStatus();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            PowerManager::EnergySaverStatusChanged(token);
            VERIFY_ARE_EQUAL(stat, EnergySaverStatus::Disabled);
        }

        TEST_METHOD(GetPowerSourceKind)
        {
            auto stat = PowerManager::PowerSourceKind();
            VERIFY_ARE_EQUAL(stat, PowerSourceKind::AC);
        }

        TEST_METHOD(PowerSourceKindCallback)
        {
            auto stat = PowerSourceKind::DC;
            auto token = PowerManager::PowerSourceKindChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::PowerSourceKind();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            PowerManager::PowerSourceKindChanged(token);
            VERIFY_ARE_EQUAL(stat, PowerSourceKind::AC);
        }

        TEST_METHOD(GetDisplayStatus)
        {
            auto stat = PowerManager::DisplayStatus();
            VERIFY_ARE_EQUAL(stat, DisplayStatus::On);
        }

        TEST_METHOD(DisplayStatusCallback)
        {
            auto stat = DisplayStatus::Off;
            auto token = PowerManager::DisplayStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::DisplayStatus();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            PowerManager::DisplayStatusChanged(token);
            VERIFY_ARE_EQUAL(stat, DisplayStatus::On);
        }
        TEST_METHOD(SystemIdleStatusCallback)
        {
            // Ignoring this test since there is no default value for SystemIdle
            // and there is no way to know when the callback will be fired
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"Ignore", L"true")
            END_TEST_METHOD_PROPERTIES()

            auto callback_success = false;
            auto token = PowerManager::SystemIdleStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                callback_success = true;
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            PowerManager::SystemIdleStatusChanged(token);
            VERIFY_ARE_EQUAL(callback_success, true);
        }

        TEST_METHOD(GetUserPresenceStatus)
        {
            auto stat = PowerManager::UserPresenceStatus();
            VERIFY_ARE_EQUAL(stat, UserPresenceStatus::Present);
        }
        TEST_METHOD(UserPresenceStatusCallback)
        {
            auto stat = UserPresenceStatus::Absent;
            auto token = PowerManager::UserPresenceStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::UserPresenceStatus();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            PowerManager::UserPresenceStatusChanged(token);
            VERIFY_ARE_EQUAL(stat, UserPresenceStatus::Present);
        }

        TEST_METHOD(SystemSuspendStatusCallback)
        {
            // Since the called API is for sleep/hibernate, we just test the registration
            auto token = PowerManager::SystemSuspendStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable) {});
            VERIFY_IS_NOT_NULL(token);
            PowerManager::SystemSuspendStatusChanged(token);
        }
    };
}
