// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <PowerManager.g.h>
#include <wil\result_macros.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PowerManager
    {
        PowerManager() = default;

        static EnergySaverStatus EnergySaverStatus()
        {
            return EnergySaverStatus::Disabled;
        }

        static winrt::event_token EnergySaverStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_energySaverStatusChangedEvent.get().add(handler);
        }

        static void EnergySaverStatusChanged(winrt::event_token const& token)
        {
            m_energySaverStatusChangedEvent.get().remove(token);
        }

        static BatteryStatus BatteryStatus()
        {
            return BatteryStatus::Charging;
        }

        static winrt::event_token BatteryStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_batteryStatusChangedEvent.get().add(handler);
        }

        static void BatteryStatusChanged(winrt::event_token const& token)
        {
            m_batteryStatusChangedEvent.get().remove(token);
        }

        static PowerSupplyStatus PowerSupplyStatus()
        {
            return PowerSupplyStatus::Adequate;
        }

        static winrt::event_token PowerSupplyStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_powerSupplyStatusChangedEvent.get().add(handler);
        }

        static void PowerSupplyStatusChanged(winrt::event_token const& token)
        {
            m_powerSupplyStatusChangedEvent.get().remove(token);
        }

        static int RemainingChargePercent()
        {
            return 100;
        }

        static winrt::event_token RemainingChargePercentChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_remainingChargePercentChangedEvent.get().add(handler);
        }

        static void RemainingChargePercentChanged(winrt::event_token const& token)
        {
            m_remainingChargePercentChangedEvent.get().remove(token);
        }
        
        static Windows::Foundation::TimeSpan RemainingDischargeTime()
        {
            return Windows::Foundation::TimeSpan();
        }

        static winrt::event_token RemainingDischargeTimeChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_remainingDischargeTimeChangedEvent.get().add(handler);
        }

        static void RemainingDischargeTimeChanged(winrt::event_token const& token)
        {
            m_remainingDischargeTimeChangedEvent.get().remove(token);
        }

        static PowerSourceStatus PowerSourceStatus()
        {
            return PowerSourceStatus::AC;
        }

        static winrt::event_token PowerSourceStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_powerSourceStatusChangedEvent.get().add(handler);
        }

        static void PowerSourceStatusChanged(winrt::event_token const& token)
        {
            m_powerSourceStatusChangedEvent.get().remove(token);
        }

        static DisplayStatus DisplayStatus()
        {
            return DisplayStatus::On;
        }

        static winrt::event_token DisplayStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_displayStatusChangedEvent.get().add(handler);
        }

        static void DisplayStatusChanged(winrt::event_token const& token)
        {
            m_displayStatusChangedEvent.get().remove(token);
        }

        static SystemIdleStatus SystemIdleStatus()
        {
            return SystemIdleStatus::Busy;
        }

        static winrt::event_token SystemIdleStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_systemIdleStatusChangedEvent.get().add(handler);
        }

        static void SystemIdleStatusChanged(winrt::event_token const& token)
        {
            m_systemIdleStatusChangedEvent.get().remove(token);
        }

        static PowerSchemePersonality PowerSchemePersonality()
        {
            return PowerSchemePersonality::Balanced;
        }

        static winrt::event_token PowerSchemePersonalityChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_powerSchemePersonalityChangedEvent.get().add(handler);
        }

        static void PowerSchemePersonalityChanged(winrt::event_token const& token)
        {
            m_powerSchemePersonalityChangedEvent.get().remove(token);
        }

        static UserPresenceStatus UserPresenceStatus()
        {
            return UserPresenceStatus::Present;
        }

        static winrt::event_token UserPresenceStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_userPresenceStatusChangedEvent.get().add(handler);
        }

        static void UserPresenceStatusChanged(winrt::event_token const& token)
        {
            m_userPresenceStatusChangedEvent.get().remove(token);
        }

        static SystemAwayModeStatus SystemAwayModeStatus()
        {
            return SystemAwayModeStatus::Exiting;
        }

        static winrt::event_token SystemAwayModeStatusChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler)
        {
            return m_systemAwayModeStatusChangedEvent.get().add(handler);
        }

        static void SystemAwayModeStatusChanged(winrt::event_token const& token);

    private:
        // REVIEW: leaks during ExitProcess, to avoid making cross-binary calls. Probably insufficient if we need to tolerate final CoUninitialize scenarios.
        // Ultimately depends on whether Reunion binaries are persistently kept loaded by something other than COM.
        using eventType = wil::object_without_destructor_on_shutdown<winrt::event<Windows::Foundation::EventHandler<Windows::Foundation::IInspectable>>>;

        static eventType m_energySaverStatusChangedEvent;
        static eventType m_batteryStatusChangedEvent;
        static eventType m_powerSupplyStatusChangedEvent;
        static eventType m_remainingChargePercentChangedEvent;
        static eventType m_remainingDischargeTimeChangedEvent;

        static eventType m_powerSourceStatusChangedEvent;
        static eventType m_displayStatusChangedEvent;
        static eventType m_systemIdleStatusChangedEvent;
        static eventType m_powerSchemePersonalityChangedEvent;
        static eventType m_userPresenceStatusChangedEvent;
        static eventType m_systemAwayModeStatusChangedEvent;
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PowerManager : PowerManagerT<PowerManager, implementation::PowerManager>
    {
    };
}
