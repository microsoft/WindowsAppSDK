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

        TEST_METHOD(BatteryStatusChangedTest)
        {
            bool callbackSuccessful = false;
            auto token = PowerManager::BatteryStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
                {
                    callbackSuccessful = true;
                });
            PowerManager::BatteryStatusChanged(token);
            VERIFY_ARE_EQUAL(callbackSuccessful, true);
        }






        TEST_METHOD(GetDisplayStatusTest)
        {
            auto stat = PowerManager::DisplayStatus();
            VERIFY_ARE_EQUAL(stat, DisplayStatus::Dimmed);
        }
        TEST_METHOD(DisplayStatusCallbackTest)
        {
            bool callbackSuccessful = false;
            auto token = PowerManager::DisplayStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
                {
                    callbackSuccessful = true;
                });
            PowerManager::DisplayStatusChanged(token);
            VERIFY_ARE_EQUAL(callbackSuccessful, true);
        }

    };
}
