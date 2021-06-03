// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "winrt/Microsoft.ProjectReunion.h"

using PowerEventHandle =
winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>;

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionPowerTests
{
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
            VERIFY_ARE_EQUAL(stat, BatteryStatus::Discharging);
        }
        TEST_METHOD(GetPowerSupplyStatus)
        {
            auto stat = PowerManager::PowerSupplyStatus();
            VERIFY_ARE_EQUAL(stat, PowerSupplyStatus::Inadequate);
        }
        TEST_METHOD(GetRemainingChargePercent)
        {
            auto stat = PowerManager::RemainingChargePercent();
            VERIFY_ARE_EQUAL(stat, 77);
        }

        TEST_METHOD(CompositeBatteryStatusCallback)
        {
            auto batteryStat = BatteryStatus::Discharging;
            auto powerStat = PowerSupplyStatus::Inadequate;
            int32_t remainingCharge = 15;
            auto token = PowerManager::BatteryStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                batteryStat = PowerManager::BatteryStatus();
                powerStat = PowerManager::PowerSupplyStatus();
                remainingCharge = PowerManager::RemainingChargePercent();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::BatteryStatusChanged(token);
            VERIFY_ARE_EQUAL(batteryStat, BatteryStatus::Charging);
            VERIFY_ARE_EQUAL(powerStat, PowerSupplyStatus::Adequate);
            VERIFY_ARE_EQUAL(remainingCharge, 57);
        }

        TEST_METHOD(GetRemainingDischargeTime)
        {
            auto stat = PowerManager::RemainingDischargeTime();
            VERIFY_ARE_EQUAL(stat.count(), 30000000);
        }

        TEST_METHOD(RemainingDischargeTimeCallback)
        {
            auto stat = winrt::Windows::Foundation::TimeSpan(std::chrono::seconds(1));
            auto token = PowerManager::RemainingDischargeTimeChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::RemainingDischargeTime();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::RemainingDischargeTimeChanged(token);
            VERIFY_ARE_EQUAL(stat.count(), 50000000);
        }

        TEST_METHOD(GetEnergySaverStatus)
        {
            auto stat = PowerManager::EnergySaverStatus();
            VERIFY_ARE_EQUAL(stat, EnergySaverStatus::On);
        }

        TEST_METHOD(EnergySaverStatusCallback)
        {
            auto stat = EnergySaverStatus::Disabled;
            auto token = PowerManager::EnergySaverStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::EnergySaverStatus();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::EnergySaverStatusChanged(token);
            VERIFY_ARE_EQUAL(stat, EnergySaverStatus::Off);
        }

        TEST_METHOD(GetPowerSourceStatus)
        {
            auto stat = PowerManager::PowerSourceStatus();
            VERIFY_ARE_EQUAL(stat, PowerSourceStatus::AC);
        }

        TEST_METHOD(PowerSourceStatusCallback)
        {
            auto stat = PowerSourceStatus::ShortTerm;
            auto token = PowerManager::PowerSourceStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::PowerSourceStatus();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::PowerSourceStatusChanged(token);
            VERIFY_ARE_EQUAL(stat, PowerSourceStatus::DC);
        }

        TEST_METHOD(GetDisplayStatus)
        {
            auto stat = PowerManager::DisplayStatus();
            VERIFY_ARE_EQUAL(stat, DisplayStatus::Dimmed);
        }

        TEST_METHOD(DisplayStatusCallback)
        {
            auto stat = DisplayStatus::Off;
            auto token = PowerManager::DisplayStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::DisplayStatus();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::DisplayStatusChanged(token);
            VERIFY_ARE_EQUAL(stat, DisplayStatus::On);
        }


        TEST_METHOD(SystemIdleStatusCallback)
        {
            auto callback_success = false;
            auto token = PowerManager::SystemIdleStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                callback_success = true;
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::SystemIdleStatusChanged(token);
            VERIFY_ARE_EQUAL(callback_success, true);
        }

        TEST_METHOD(GetPowerSchemePersonality)
        {
            auto stat = PowerManager::PowerSchemePersonality();
            VERIFY_ARE_EQUAL(stat, PowerSchemePersonality::HighPerformance);
        }
        TEST_METHOD(PowerSchemePersonalityCallback)
        {
            auto stat = PowerSchemePersonality::HighPerformance;
            auto token = PowerManager::PowerSchemePersonalityChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::PowerSchemePersonality();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::PowerSchemePersonalityChanged(token);
            VERIFY_ARE_EQUAL(stat, PowerSchemePersonality::PowerSaver);
        }

        TEST_METHOD(GetUserPresenceStatus)
        {
            auto stat = PowerManager::UserPresenceStatus();
            VERIFY_ARE_EQUAL(stat, UserPresenceStatus::Present);
        }
        TEST_METHOD(UserPresenceStatusCallback)
        {
            auto stat = UserPresenceStatus::Present;
            auto token = PowerManager::UserPresenceStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
            {
                stat = PowerManager::UserPresenceStatus();
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PowerManager::UserPresenceStatusChanged(token);
            VERIFY_ARE_EQUAL(stat, UserPresenceStatus::Absent);
        }

    };
}
