// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <mutex>
#include <PowerManager.g.h>
#include <PowerNotificationsPal.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    using PowerEventHandle = Windows::Foundation::EventHandler<Windows::Foundation::IInspectable>;
    using EventToken = winrt::event_token ;

    struct CompositeBatteryStats
    {
        int   oldBatteryChargePercent, batteryChargePercent;
        winrt::Microsoft::ProjectReunion::BatteryStatus     oldBatteryStatus, batteryStatus;
        winrt::Microsoft::ProjectReunion::PowerSupplyStatus oldPowerSupplyStatus, powerSupplyStatus;
    };

    struct PowerManager
    {
        PowerManager() = default;

        using eventType = wil::object_without_destructor_on_shutdown<winrt::event<PowerEventHandle>>;

        static winrt::Microsoft::ProjectReunion::EnergySaverStatus EnergySaverStatus();
        static EventToken EnergySaverStatusChanged(PowerEventHandle const&);
        static void EnergySaverStatusChanged(EventToken const&);
        static void EnergySaverStatusChanged_Callback(::EnergySaverStatus);

        static winrt::Microsoft::ProjectReunion::BatteryStatus BatteryStatus();
        static EventToken BatteryStatusChanged(PowerEventHandle const&);
        static void BatteryStatusChanged(EventToken const&);
        static void CompositeBatteryStatusChanged_Callback(CompositeBatteryStatus*);

        static winrt::Microsoft::ProjectReunion::PowerSupplyStatus PowerSupplyStatus();
        static EventToken PowerSupplyStatusChanged(PowerEventHandle const&);
        static void PowerSupplyStatusChanged(EventToken const&);

        static int RemainingChargePercent();
        static EventToken RemainingChargePercentChanged(PowerEventHandle const&);
        static void RemainingChargePercentChanged(EventToken const&);
        
        static Windows::Foundation::TimeSpan RemainingDischargeTime();
        static EventToken RemainingDischargeTimeChanged(PowerEventHandle const&);
        static void RemainingDischargeTimeChanged(EventToken const&);
        static void RemainingDischargeTimeChanged_Callback(ULONGLONG);

        static winrt::Microsoft::ProjectReunion::PowerSourceStatus PowerSourceStatus();
        static EventToken PowerSourceStatusChanged(PowerEventHandle const&);
        static void PowerSourceStatusChanged(EventToken const&);
        static void PowerSourceStatusChanged_Callback(DWORD);

        static winrt::Microsoft::ProjectReunion::DisplayStatus DisplayStatus();
        static EventToken DisplayStatusChanged(PowerEventHandle const&);
        static void DisplayStatusChanged(EventToken const&);
        static void DisplayStatusChanged_Callback(DWORD);

        static winrt::Microsoft::ProjectReunion::SystemIdleStatus SystemIdleStatus();
        static EventToken SystemIdleStatusChanged(PowerEventHandle const&);
        static void SystemIdleStatusChanged(EventToken const&);
        static void SystemIdleStatusChanged_Callback();

        static winrt::Microsoft::ProjectReunion::PowerSchemePersonality PowerSchemePersonality();
        static EventToken PowerSchemePersonalityChanged(PowerEventHandle const&);
        static void PowerSchemePersonalityChanged(EventToken const&);
        static void PowerSchemePersonalityChanged_Callback(GUID);

        static winrt::Microsoft::ProjectReunion::UserPresenceStatus UserPresenceStatus();
        static EventToken UserPresenceStatusChanged(PowerEventHandle const&);
        static void UserPresenceStatusChanged(EventToken const&);
        static void UserPresenceStatusChanged_Callback(DWORD);

        static winrt::Microsoft::ProjectReunion::SystemAwayModeStatus SystemAwayModeStatus();
        static EventToken SystemAwayModeStatusChanged(PowerEventHandle const&);
        static void SystemAwayModeStatusChanged(EventToken const&);
        static void SystemAwayModeStatusChanged_Callback(DWORD);

        enum PowerFunction
        {
            EnergySaverStatusFn = 0,
            BatteryStatusFn,
            PowerSupplyStatusFn,
            RemainingChargePercentFn,
            RemainingDischargeTimeFn,
            PowerSourceStatusFn,
            DisplayStatusFn,
            SystemIdleStatusFn,
            PowerSchemePersonalityFn,
            UserPresenceStatusFn,
            SystemAwayModeStatusFn
        };

    private:
        // REVIEW: leaks during ExitProcess, to avoid making cross-binary calls. Probably insufficient if we need to tolerate final CoUninitialize scenarios.
        // Ultimately depends on whether Reunion binaries are persistently kept loaded by something other than COM.        

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

        static CompositeBatteryStatusRegistration m_batteryStatusHandle;
        static EnergySaverStatusRegistration      m_energySaverStatusHandle;
        static PowerConditionRegistration         m_powerConditionHandle;
        static DischargeTimeRegistration          m_dischargeTimeHandle;
        static DisplayStatusRegistration          m_displayStatusHandle;
        static SystemIdleStatusRegistration       m_systemIdleStatusHandle;
        static PowerSchemePersonalityRegistration m_powerSchemePersonalityHandle;
        static UserPresenceStatusRegistration     m_userPresenceStatusHandle;
        static SystemAwayModeStatusRegistration   m_systemAwayModeStatusHandle;

        static std::mutex m_mutex;
        static CompositeBatteryStats m_stats;

        static int   m_batteryChargePercent, m_oldBatteryChargePercent;
        static DWORD m_cachedDisplayStatus;
        static DWORD m_cachedUserPresenceStatus;
        static DWORD m_cachedSystemAwayModeStatus;
        static DWORD m_cachedPowerCondition;
        static GUID  m_cachedPowerSchemePersonality;
        static ULONGLONG              m_cachedDischargeTime;
        static ::EnergySaverStatus    m_cachedEnergySaverStatus;
        static CompositeBatteryStatus *m_cachedCompositeBatteryStatus;
        static winrt::Microsoft::ProjectReunion::BatteryStatus     m_batteryStatus, m_oldBatteryStatus;
        static winrt::Microsoft::ProjectReunion::PowerSupplyStatus m_powerSupplyStatus, m_oldPowerSupplyStatus;

        static bool       NotAlreadyRegisteredForEvents(eventType);
        static eventType  GetEventObj(PowerFunction const&);        
        static EventToken AddCallback(PowerFunction const&, PowerEventHandle const&);
        static void RegisterListener (PowerFunction const&);
        static void RemoveCallback   (PowerFunction const&, EventToken const&);
        static void UnregisterListener(PowerFunction const&);
        static void CheckRegistrationAndOrUpdateValue(PowerFunction const&);
        static void FireEvent(PowerFunction const&);
        static void FireCorrespondingBatteryEvent();
        static void ProcessCompositeBatteryStatus(CompositeBatteryStatus const&);
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PowerManager : PowerManagerT<PowerManager, implementation::PowerManager>
    {
    };
}
