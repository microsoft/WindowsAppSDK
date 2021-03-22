#include "pch.h"
//#include "PowerTests.h"
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
            //VERIFY_ARE_EQUAL(stat, BatteryStatus::Discharging);
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

        TEST_METHOD(BatteryStatusChanged)
        {
            bool callbackSuccessful = false;
            auto token = PowerManager::BatteryStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
                {
                    callbackSuccessful = true;
                });
            PowerManager::BatteryStatusChanged(token);
            VERIFY_ARE_EQUAL(callbackSuccessful, true);
        }

        TEST_METHOD(GetRemainingDischargeTime)
        {
            auto stat = PowerManager::RemainingDischargeTime();
            //VERIFY_ARE_EQUAL(stat, 57);
        }

        TEST_METHOD(GetEnergySaverStatus)
        {
            auto stat = PowerManager::EnergySaverStatus();
            //VERIFY_ARE_EQUAL(stat, EnergySaverStatus::On);
        }

        TEST_METHOD(GetPowerSourceStatus)
        {
            auto stat = PowerManager::PowerSourceStatus();
            //VERIFY_ARE_EQUAL(stat, PowerSourceStatus::AC);
        }

        TEST_METHOD(GetDisplayStatus)
        {
            auto stat = PowerManager::DisplayStatus();
            VERIFY_ARE_EQUAL(stat, DisplayStatus::Dimmed);
        }
        TEST_METHOD(DisplayStatusCallback)
        {
            bool callbackSuccessful = false;
            auto token = PowerManager::DisplayStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
                {
                    callbackSuccessful = true;
                });
            PowerManager::DisplayStatusChanged(token);
            VERIFY_ARE_EQUAL(callbackSuccessful, true);
        }

        TEST_METHOD(GetPowerSchemePersonality)
        {
            auto stat = PowerManager::PowerSchemePersonality();
            //VERIFY_ARE_EQUAL(stat, PowerSchemePersonality::HighPerformance);
        }

        TEST_METHOD(GetUserPresenceStatus)
        {
            auto stat = PowerManager::UserPresenceStatus();
            //VERIFY_ARE_EQUAL(stat, UserPresenceStatus::Present);
        }

        TEST_METHOD(GetSystemAwayModeStatus)
        {
            auto stat = PowerManager::SystemAwayModeStatus();
            //VERIFY_ARE_EQUAL(stat, SystemAwayModeStatus::Entering);
        }

    };
}
