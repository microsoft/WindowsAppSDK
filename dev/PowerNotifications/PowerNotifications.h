// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <mutex>
#include <PowerManager.g.h>
#include <PowerNotificationsPal.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

using PowerEventHandle =
    winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>;
using EventType = winrt::event<PowerEventHandle>;

// Forward-declarations
namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PowerManager;

    EventType& EnergySaverStatus_Event();
    void EnergySaverStatus_Register();
    void EnergySaverStatus_Unregister();
    void EnergySaverStatus_Update();

    EventType& BatteryStatus_Event();
    void BatteryStatus_Register();
    void BatteryStatus_Unregister();
    void BatteryStatus_Update();

    EventType& PowerSupplyStatus_Event();
    void PowerSupplyStatus_Register();
    void PowerSupplyStatus_Unregister();
    void PowerSupplyStatus_Update();

    EventType& RemainingChargePercent_Event();
    void RemainingChargePercent_Register();
    void RemainingChargePercent_Unregister();
    void RemainingChargePercent_Update();

    EventType& RemainingDischargeTime_Event();
    void RemainingDischargeTime_Register();
    void RemainingDischargeTime_Unregister();
    void RemainingDischargeTime_Update();

    EventType& PowerSourceStatus_Event();
    void PowerSourceStatus_Register();
    void PowerSourceStatus_Unregister();
    void PowerSourceStatus_Update();

    EventType& DisplayStatus_Event();
    void DisplayStatus_Register();
    void DisplayStatus_Unregister();
    void DisplayStatus_Update();

    EventType& SystemIdleStatus_Event();
    void SystemIdleStatus_Register();
    void SystemIdleStatus_Unregister();

    EventType& PowerSchemePersonality_Event();
    void PowerSchemePersonality_Register();
    void PowerSchemePersonality_Unregister();
    void PowerSchemePersonality_Update();
	
    EventType& UserPresenceStatus_Event();
    void UserPresenceStatus_Register();
    void UserPresenceStatus_Unregister();
    void UserPresenceStatus_Update();
	
    EventType& SystemAwayModeStatus_Event();
    void SystemAwayModeStatus_Register();
    void SystemAwayModeStatus_Unregister();
    void SystemAwayModeStatus_Update();

    EventType& SystemSuspendStatus_Event();
    void SystemSuspendStatus_Register();
    void SystemSuspendStatus_Unregister();

    // A place holder for an empty function, since not all events have every function defined
    void NoOperation() {}

    struct PowerFunctionDetails
    {
        EventType& (*event)();
        void (*registerListener)();
        void (*unregisterListener)();
        void (*getStatus)();
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    using PowerFunctionDetails = winrt::Microsoft::ProjectReunion::implementation::PowerFunctionDetails;

    struct PowerManager : PowerManagerT<PowerManager, implementation::PowerManager, static_lifetime>
    {
        std::mutex m_mutex;
        int m_batteryChargePercent;
        int m_oldBatteryChargePercent;
        DWORD m_cachedDisplayStatus;
        DWORD m_cachedUserPresenceStatus;
        DWORD m_cachedSystemAwayModeStatus;
        DWORD m_cachedPowerSourceStatus;
        GUID  m_cachedPowerSchemePersonality;
        ULONGLONG m_cachedDischargeTime;
        winrt::Microsoft::ProjectReunion::SystemSuspendStatus m_systemSuspendStatus;
        ::EnergySaverStatus m_cachedEnergySaverStatus;
        CompositeBatteryStatus m_cachedCompositeBatteryStatus;
        winrt::Microsoft::ProjectReunion::BatteryStatus m_batteryStatus;
        winrt::Microsoft::ProjectReunion::BatteryStatus m_oldBatteryStatus { winrt::Microsoft::ProjectReunion::BatteryStatus::NotPresent };
        winrt::Microsoft::ProjectReunion::PowerSupplyStatus m_powerSupplyStatus;
        winrt::Microsoft::ProjectReunion::PowerSupplyStatus m_oldPowerSupplyStatus { winrt::Microsoft::ProjectReunion::PowerSupplyStatus::NotPresent };

        EventType m_EnergySaverStatusChangedEvent;
        EventType m_batteryStatusChangedEvent;
        EventType m_powerSupplyStatusChangedEvent;
        EventType m_remainingChargePercentChangedEvent;
        EventType m_remainingDischargeTimeChangedEvent;
        EventType m_powerSourceStatusChangedEvent;
        EventType m_displayStatusChangedEvent;
        EventType m_systemIdleStatusChangedEvent;
        EventType m_powerSchemePersonalityChangedEvent;
        EventType m_userPresenceStatusChangedEvent;
        EventType m_systemAwayModeStatusChangedEvent;
        EventType m_systemSuspendStatusChangedEvent;

        EnergySaverStatusRegistration m_EnergySaverStatusHandle;
        CompositeBatteryStatusRegistration m_batteryStatusHandle;
        PowerConditionRegistration m_powerSourceStatusHandle;
        DischargeTimeRegistration m_dischargeTimeHandle;
        DisplayStatusRegistration m_displayStatusHandle;
        SystemIdleStatusRegistration m_systemIdleStatusHandle;
        PowerSchemePersonalityRegistration m_powerSchemePersonalityHandle;
        UserPresenceStatusRegistration m_userPresenceStatusHandle;
        SystemAwayModeStatusRegistration m_systemAwayModeStatusHandle;
        HPOWERNOTIFY m_systemSuspendHandle;

        PowerFunctionDetails energySaverStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::EnergySaverStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::EnergySaverStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::EnergySaverStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::EnergySaverStatus_Update };

        PowerFunctionDetails compositeBatteryStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::BatteryStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::BatteryStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::BatteryStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::BatteryStatus_Update };

        PowerFunctionDetails powerSupplyStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::PowerSupplyStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSupplyStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSupplyStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSupplyStatus_Update };

        PowerFunctionDetails remainingChargePercentFunc{
            &winrt::Microsoft::ProjectReunion::implementation::RemainingChargePercent_Event,
            &winrt::Microsoft::ProjectReunion::implementation::RemainingChargePercent_Register,
            &winrt::Microsoft::ProjectReunion::implementation::RemainingChargePercent_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::RemainingChargePercent_Update };

        PowerFunctionDetails remainingDischargeTimeFunc{
            &winrt::Microsoft::ProjectReunion::implementation::RemainingDischargeTime_Event,
            &winrt::Microsoft::ProjectReunion::implementation::RemainingDischargeTime_Register,
            &winrt::Microsoft::ProjectReunion::implementation::RemainingDischargeTime_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::RemainingDischargeTime_Update };

        PowerFunctionDetails powerSourceStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::PowerSourceStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSourceStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSourceStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSourceStatus_Update };

        PowerFunctionDetails displayStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::DisplayStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::DisplayStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::DisplayStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::DisplayStatus_Update };

        PowerFunctionDetails systemIdleStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::SystemIdleStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::SystemIdleStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::SystemIdleStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::NoOperation };

        PowerFunctionDetails powerSchemePersonalityFunc{
            &winrt::Microsoft::ProjectReunion::implementation::PowerSchemePersonality_Event,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSchemePersonality_Register,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSchemePersonality_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::PowerSchemePersonality_Update };

        PowerFunctionDetails userPresenceStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::UserPresenceStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::UserPresenceStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::UserPresenceStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::UserPresenceStatus_Update };

        PowerFunctionDetails systemAwayModeStatusFunc{
            &winrt::Microsoft::ProjectReunion::implementation::SystemAwayModeStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::SystemAwayModeStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::SystemAwayModeStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::SystemAwayModeStatus_Update };

        PowerFunctionDetails systemSuspendFunc{
            &winrt::Microsoft::ProjectReunion::implementation::SystemSuspendStatus_Event,
            &winrt::Microsoft::ProjectReunion::implementation::SystemSuspendStatus_Register,
            &winrt::Microsoft::ProjectReunion::implementation::SystemSuspendStatus_Unregister,
            &winrt::Microsoft::ProjectReunion::implementation::NoOperation };

        bool RegisteredForEvents(const EventType& eventObj)
        {
            return eventObj ? true : false;
        }

        event_token AddCallback(PowerFunctionDetails fn, const PowerEventHandle& handler)
        {
            auto& eventObj = fn.event();
            std::scoped_lock<std::mutex> lock(m_mutex);
            if (!RegisteredForEvents(eventObj))
            {
                fn.registerListener();
            }
            return eventObj.add(handler);
        }

        void RemoveCallback(PowerFunctionDetails fn, const event_token& token)
        {
            auto& eventObj = fn.event();
            eventObj.remove(token);
            std::scoped_lock<std::mutex> lock(m_mutex);
            if (RegisteredForEvents(eventObj))
            {
                fn.unregisterListener();
            }
        }

        void RaiseEvent(PowerFunctionDetails fn)
        {
            fn.event()(nullptr, nullptr);
        }

        // Checks if an event is already registered. If none are, then gets the status
        void CheckRegistrationAndOrUpdateValue(PowerFunctionDetails fn)
        {
            auto& eventObj = fn.event();
            if (!RegisteredForEvents(eventObj))
            {
                fn.getStatus();
            }
        }


        // EnergySaverStatus Functions
        winrt::Microsoft::ProjectReunion::EnergySaverStatus EnergySaverStatus()
        {
            CheckRegistrationAndOrUpdateValue(energySaverStatusFunc);
            return static_cast<winrt::Microsoft::ProjectReunion::EnergySaverStatus>(m_cachedEnergySaverStatus);
        }

        event_token EnergySaverStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(energySaverStatusFunc, handler);
        }

        void EnergySaverStatusChanged(const event_token& token)
        {
            RemoveCallback(energySaverStatusFunc, token);
        }

        void EnergySaverStatusChanged_Callback(::EnergySaverStatus energySaverStatus)
        {
            m_cachedEnergySaverStatus = energySaverStatus;
            RaiseEvent(energySaverStatusFunc);
        }

        // BatteryStatus Functions        
        void ProcessCompositeBatteryStatus(const CompositeBatteryStatus& compositeBatteryStatus)
        {
            // Calculate the remaining charge capacity based on the maximum charge
            // as an integer percentage value from 0 to 100.
            auto fullChargedCapacity = compositeBatteryStatus.Information.FullChargedCapacity;
            auto remainingCapacity = compositeBatteryStatus.Status.Capacity;
            if (fullChargedCapacity == BATTERY_UNKNOWN_CAPACITY ||
                fullChargedCapacity == 0)
            {
                throw winrt::hresult_error(E_FAIL, L"Unknown charge ratio: FullChargedCapacity Unknown");
            }
            else if (remainingCapacity == BATTERY_UNKNOWN_CAPACITY)
            {
                throw winrt::hresult_error(E_FAIL, L"Unknown charge ratio: RemainingCapacity Unknown");
            }
            else if (remainingCapacity > fullChargedCapacity) {
                std::wstring message = L"High charge ratio: RemainingCapacity " + std::to_wstring(remainingCapacity)
                    + L" FullChargedCapacity " + std::to_wstring(fullChargedCapacity);
                throw winrt::hresult_error(E_FAIL, message);

            }
            else if (remainingCapacity > (INT_MAX / 200))
            {
                std::wstring message = L"Absurd capacity:: RemainingCapacity " + std::to_wstring(remainingCapacity)
                    + L" FullChargedCapacity " + std::to_wstring(fullChargedCapacity);
                throw winrt::hresult_error(E_FAIL, message);
            }
            else
            {
                auto newRemainingChargePercent = static_cast<int>((remainingCapacity * 200) / fullChargedCapacity);
                newRemainingChargePercent += 1;
                newRemainingChargePercent /= 2;
                m_batteryChargePercent = newRemainingChargePercent;
            }

            auto powerState = compositeBatteryStatus.Status.PowerState;

            // Set battery status
            if (compositeBatteryStatus.ActiveBatteryCount == 0)
            {
                m_batteryStatus = BatteryStatus::NotPresent;
            }
            else if (WI_IsFlagSet(powerState, BATTERY_DISCHARGING))
            {
                m_batteryStatus = BatteryStatus::Discharging;
            }
            else if (WI_IsFlagSet(powerState, BATTERY_CHARGING))
            {
                m_batteryStatus = BatteryStatus::Charging;
            }
            else
            {
                m_batteryStatus = BatteryStatus::Idle;
            }

            // Set power supply state
            if (WI_IsFlagClear(powerState, BATTERY_POWER_ON_LINE))
            {
                m_powerSupplyStatus = PowerSupplyStatus::NotPresent;
            }
            else if (WI_IsFlagSet(powerState, BATTERY_DISCHARGING))
            {
                m_powerSupplyStatus = PowerSupplyStatus::Inadequate;
            }
            else
            {
                m_powerSupplyStatus = PowerSupplyStatus::Adequate;
            }
        }

        void FireCorrespondingCompositeBatteryEvent()
        {
            if (m_oldBatteryChargePercent != m_batteryChargePercent)
            {
                m_oldBatteryChargePercent = m_batteryChargePercent;
                RaiseEvent(remainingChargePercentFunc);
            }

            if (m_oldBatteryStatus != m_batteryStatus)
            {
                m_oldBatteryStatus = m_batteryStatus;
                RaiseEvent(compositeBatteryStatusFunc);
            }

            if (m_oldPowerSupplyStatus != m_powerSupplyStatus)
            {
                m_oldPowerSupplyStatus = m_powerSupplyStatus;
                RaiseEvent(powerSupplyStatusFunc);
            }
        }

        winrt::Microsoft::ProjectReunion::BatteryStatus BatteryStatus()
        {
            CheckRegistrationAndOrUpdateValue(compositeBatteryStatusFunc);
            return m_batteryStatus;
        }

        event_token BatteryStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(compositeBatteryStatusFunc, handler);
        }

        void BatteryStatusChanged(const event_token& token)
        {
            RemoveCallback(compositeBatteryStatusFunc, token);
        }

        void CompositeBatteryStatusChanged_Callback(const CompositeBatteryStatus& compositeBatteryStatus)
        {
            ProcessCompositeBatteryStatus(compositeBatteryStatus);
            FireCorrespondingCompositeBatteryEvent();
        }


        // PowerSupplyStatus Functions
        winrt::Microsoft::ProjectReunion::PowerSupplyStatus PowerSupplyStatus()
        {
            CheckRegistrationAndOrUpdateValue(compositeBatteryStatusFunc);
            return m_powerSupplyStatus;
        }

        event_token PowerSupplyStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(powerSupplyStatusFunc, handler);
        }

        void PowerSupplyStatusChanged(const event_token& token)
        {
            RemoveCallback(powerSupplyStatusFunc, token);
        }


        // RemainingChargePercent Functions
        int RemainingChargePercent()
        {
            CheckRegistrationAndOrUpdateValue(compositeBatteryStatusFunc);
            return m_batteryChargePercent;
        }

        event_token RemainingChargePercentChanged(const PowerEventHandle& handler)
        {
            return AddCallback(remainingChargePercentFunc, handler);
        }

        void RemainingChargePercentChanged(const event_token& token)
        {
            RemoveCallback(remainingChargePercentFunc, token);
        }


        // RemainingDischargeTime Functions        
        Windows::Foundation::TimeSpan RemainingDischargeTime()
        {
            CheckRegistrationAndOrUpdateValue(remainingDischargeTimeFunc);
            return Windows::Foundation::TimeSpan(std::chrono::seconds(m_cachedDischargeTime));
        }

        event_token RemainingDischargeTimeChanged(const PowerEventHandle& handler)
        {
            return AddCallback(remainingDischargeTimeFunc, handler);
        }

        void RemainingDischargeTimeChanged(const event_token& token)
        {
            RemoveCallback(remainingDischargeTimeFunc, token);
        }

        void RemainingDischargeTimeChanged_Callback(ULONGLONG remainingDischargeTime)
        {
            m_cachedDischargeTime = remainingDischargeTime;
            RaiseEvent(remainingDischargeTimeFunc);
        }


        // PowerSourceStatus Functions
        winrt::Microsoft::ProjectReunion::PowerSourceStatus PowerSourceStatus()
        {
            CheckRegistrationAndOrUpdateValue(powerSourceStatusFunc);
            return static_cast<winrt::Microsoft::ProjectReunion::PowerSourceStatus>(m_cachedPowerSourceStatus);
        }

        event_token PowerSourceStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(powerSourceStatusFunc, handler);
        }

        void PowerSourceStatusChanged(const event_token& token)
        {
            RemoveCallback(powerSourceStatusFunc, token);
        }

        void PowerSourceStatusChanged_Callback(DWORD powerCondition)
        {
            m_cachedPowerSourceStatus = powerCondition;
            RaiseEvent(powerSourceStatusFunc);
        }


        // DisplayStatus Functions
        winrt::Microsoft::ProjectReunion::DisplayStatus DisplayStatus()
        {
            CheckRegistrationAndOrUpdateValue(displayStatusFunc);
            return static_cast<winrt::Microsoft::ProjectReunion::DisplayStatus>(m_cachedDisplayStatus);
        }

        event_token DisplayStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(displayStatusFunc, handler);
        }

        void DisplayStatusChanged(const event_token& token)
        {
            RemoveCallback(displayStatusFunc, token);
        }

        void DisplayStatusChanged_Callback(DWORD displayStatus)
        {
            m_cachedDisplayStatus = displayStatus;
            RaiseEvent(displayStatusFunc);
        }


        // SystemIdleStatus Functions
        winrt::Microsoft::ProjectReunion::SystemIdleStatus SystemIdleStatus()
        {
            // PReview: Should this be the default value?
            // We expect a persistently-queryable value, but
            // low-level APIs provide an idle->non-idle pulse event
 
            return SystemIdleStatus::Busy;
        }

        event_token SystemIdleStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(systemIdleStatusFunc, handler);
        }

        void SystemIdleStatusChanged(const event_token& token)
        {
            RemoveCallback(systemIdleStatusFunc, token);
        }

        void SystemIdleStatusChanged_Callback()
        {
            RaiseEvent(systemIdleStatusFunc);
        }


        // PowerSchemePersonality Functions
        winrt::Microsoft::ProjectReunion::PowerSchemePersonality PowerSchemePersonality()
        {
            CheckRegistrationAndOrUpdateValue(powerSchemePersonalityFunc);
            if (m_cachedPowerSchemePersonality == GUID_MAX_POWER_SAVINGS)
            {
                return PowerSchemePersonality::PowerSaver;
            }
            else if (m_cachedPowerSchemePersonality == GUID_MIN_POWER_SAVINGS)
            {
                return PowerSchemePersonality::HighPerformance;
            }
            else
            {
                return PowerSchemePersonality::Balanced;
            }

        }

        event_token PowerSchemePersonalityChanged(const PowerEventHandle& handler)
        {
            return AddCallback(powerSchemePersonalityFunc, handler);
        }

        void PowerSchemePersonalityChanged(const event_token& token)
        {
            RemoveCallback(powerSchemePersonalityFunc, token);
        }

        void PowerSchemePersonalityChanged_Callback(GUID powerSchemePersonality)
        {
            m_cachedPowerSchemePersonality = powerSchemePersonality;
            RaiseEvent(powerSchemePersonalityFunc);
        }


        // UserPresenceStatus Functions
        winrt::Microsoft::ProjectReunion::UserPresenceStatus UserPresenceStatus()
        {
            CheckRegistrationAndOrUpdateValue(userPresenceStatusFunc);
            return static_cast<winrt::Microsoft::ProjectReunion::UserPresenceStatus>(m_cachedUserPresenceStatus);
        }

        event_token UserPresenceStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(userPresenceStatusFunc, handler);
        }

        void UserPresenceStatusChanged(const event_token& token)
        {
            RemoveCallback(userPresenceStatusFunc, token);
        }

        void UserPresenceStatusChanged_Callback(DWORD userPresenceStatus)
        {
            m_cachedUserPresenceStatus = userPresenceStatus;
            RaiseEvent(userPresenceStatusFunc);
        }


        // SystemAwayModeStatus Functions
        winrt::Microsoft::ProjectReunion::SystemAwayModeStatus SystemAwayModeStatus()
        {
            CheckRegistrationAndOrUpdateValue(systemAwayModeStatusFunc);
            return static_cast<winrt::Microsoft::ProjectReunion::SystemAwayModeStatus>(m_cachedSystemAwayModeStatus);
        }

        event_token SystemAwayModeStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(systemAwayModeStatusFunc, handler);
        }

        void SystemAwayModeStatusChanged(const event_token& token)
        {
            RemoveCallback(systemAwayModeStatusFunc, token);
        }

        void SystemAwayModeStatusChanged_Callback(DWORD systemAwayModeStatus)
        {
            m_cachedSystemAwayModeStatus = systemAwayModeStatus;
            RaiseEvent(systemAwayModeStatusFunc);
        }

        //SystemSuspend Functions
        winrt::Microsoft::ProjectReunion::SystemSuspendStatus SystemSuspendStatus()
        {
            // Review: Agree with this "only callable during SystemSuspendStatusChanged callback" enforcement?
            if (m_systemSuspendStatus == SystemSuspendStatus::Uninitialized)
            {
                throw winrt::hresult_error(E_FAIL, L"There are no active subscriptions on SystemSuspendStatus");
            }
            return static_cast<winrt::Microsoft::ProjectReunion::SystemSuspendStatus>(m_systemSuspendStatus);
        }

        event_token SystemSuspendStatusChanged(const PowerEventHandle& handler)
        {
            return AddCallback(systemSuspendFunc, handler);
        }

        void SystemSuspendStatusChanged(const event_token& token)
        {
            RemoveCallback(systemSuspendFunc, token);
        }

        void SystemSuspendStatusChanged_Callback(ULONG PowerEvent)
        {
            using namespace winrt::Microsoft::ProjectReunion;
            if (PowerEvent == PBT_APMSUSPEND)
            {
                m_systemSuspendStatus = SystemSuspendStatus::Entering;
                RaiseEvent(systemSuspendFunc);
            }
            else if (PowerEvent == PBT_APMRESUMEAUTOMATIC)
            {
                m_systemSuspendStatus = SystemSuspendStatus::AutoResume;
                RaiseEvent(systemSuspendFunc);
            }
            else if (PowerEvent == PBT_APMRESUMESUSPEND)
            {
                m_systemSuspendStatus = SystemSuspendStatus::ManualResume;
                RaiseEvent(systemSuspendFunc);
            }
            // Resetting the value after the callback
            m_systemSuspendStatus = SystemSuspendStatus::Uninitialized;
        }

    };

};

namespace winrt::Microsoft::ProjectReunion::implementation
{

     struct PowerManager
     {
        PowerManager() = default;

        //Get function forwards
        static winrt::Microsoft::ProjectReunion::EnergySaverStatus EnergySaverStatus()
        {
            return make_self<factory_implementation::PowerManager>()->EnergySaverStatus();
        }

        static winrt::Microsoft::ProjectReunion::BatteryStatus BatteryStatus()
        {
            return make_self<factory_implementation::PowerManager>()->BatteryStatus();
        }

        static winrt::Microsoft::ProjectReunion::PowerSupplyStatus PowerSupplyStatus()
        {
            return make_self<factory_implementation::PowerManager>()->PowerSupplyStatus();
        }

        static int RemainingChargePercent()
        {
            return make_self<factory_implementation::PowerManager>()->RemainingChargePercent();
        }

        static Windows::Foundation::TimeSpan RemainingDischargeTime()
        {
            return make_self<factory_implementation::PowerManager>()->RemainingDischargeTime();
        }

        static winrt::Microsoft::ProjectReunion::PowerSourceStatus PowerSourceStatus()
        {
            return make_self<factory_implementation::PowerManager>()->PowerSourceStatus();
        }

        static winrt::Microsoft::ProjectReunion::DisplayStatus DisplayStatus()
        {
            return make_self<factory_implementation::PowerManager>()->DisplayStatus();
        }

        static winrt::Microsoft::ProjectReunion::SystemIdleStatus SystemIdleStatus()
        {
            return make_self<factory_implementation::PowerManager>()->SystemIdleStatus();
        }

        static winrt::Microsoft::ProjectReunion::PowerSchemePersonality PowerSchemePersonality()
        {
            return make_self<factory_implementation::PowerManager>()->PowerSchemePersonality();
        }

        static winrt::Microsoft::ProjectReunion::UserPresenceStatus UserPresenceStatus()
        {
            return make_self<factory_implementation::PowerManager>()->UserPresenceStatus();
        }

        static winrt::Microsoft::ProjectReunion::SystemAwayModeStatus SystemAwayModeStatus()
        {
            return make_self<factory_implementation::PowerManager>()->SystemAwayModeStatus();
        }

        static winrt::Microsoft::ProjectReunion::SystemSuspendStatus SystemSuspendStatus()
        {
            return make_self<factory_implementation::PowerManager>()->SystemSuspendStatus();
        }

        //Callback forwards
        static void EnergySaverStatusChanged_Callback(::EnergySaverStatus energySaverStatus)
        {
            return make_self<factory_implementation::PowerManager>()->EnergySaverStatusChanged_Callback(energySaverStatus);
        }

        static void CompositeBatteryStatusChanged_Callback(const CompositeBatteryStatus& compositeBatteryStatus)
        {
            return make_self<factory_implementation::PowerManager>()->CompositeBatteryStatusChanged_Callback(compositeBatteryStatus);
        }

        static void RemainingDischargeTimeChanged_Callback(ULONGLONG remainingDischargeTime)
        {
            return make_self<factory_implementation::PowerManager>()->RemainingDischargeTimeChanged_Callback(remainingDischargeTime);
        }

        static void PowerSourceStatusChanged_Callback(DWORD powerCondition)
        {
            return make_self<factory_implementation::PowerManager>()->PowerSourceStatusChanged_Callback(powerCondition);
        }

        static void DisplayStatusChanged_Callback(DWORD displayStatus)
        {
            return make_self<factory_implementation::PowerManager>()->DisplayStatusChanged_Callback(displayStatus);
        }

        static void SystemIdleStatusChanged_Callback()
        {
            return make_self<factory_implementation::PowerManager>()->SystemIdleStatusChanged_Callback();
        }

        static void PowerSchemePersonalityChanged_Callback(GUID powerSchemePersonality)
        {
            return make_self<factory_implementation::PowerManager>()->PowerSchemePersonalityChanged_Callback(powerSchemePersonality);
        }

        static void UserPresenceStatusChanged_Callback(DWORD userPresenceStatus)
        {
            return make_self<factory_implementation::PowerManager>()->UserPresenceStatusChanged_Callback(userPresenceStatus);
        }

        static void SystemAwayModeStatusChanged_Callback(DWORD systemAwayModeStatus)
        {
            return make_self<factory_implementation::PowerManager>()->SystemAwayModeStatusChanged_Callback(systemAwayModeStatus);
        }
    };
}
