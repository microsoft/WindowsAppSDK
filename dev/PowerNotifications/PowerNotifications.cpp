// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <PowerNotifications.h>
#include <PowerNotificationsPal.h>
#include <PowerManager.g.cpp>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    auto factory = make_self<factory_implementation::PowerManager>();

    // EnergySaverStatus Functions
    EventType& EnergySaverStatus_Event()
    {
        return factory->m_EnergySaverStatusChangedEvent;
    }

    void EnergySaverStatus_Register()
    {
        check_hresult(RegisterEnergySaverStatusChangedListener(&PowerManager::EnergySaverStatusChanged_Callback, &factory->m_EnergySaverStatusHandle));
    }

    void EnergySaverStatus_Unregister()
    {
        check_hresult(UnregisterEnergySaverStatusChangedListener(factory->m_EnergySaverStatusHandle));
    }

    void EnergySaverStatus_Update()
    {
        check_hresult(GetEnergySaverStatus(&factory->m_cachedEnergySaverStatus));
    }

    // BatteryStatus Functions
    EventType& BatteryStatus_Event()
    {
        return factory->m_batteryStatusChangedEvent;
    }

    void BatteryStatus_Register()
    {
        check_hresult(RegisterCompositeBatteryStatusChangedListener(&PowerManager::CompositeBatteryStatusChanged_Callback, &factory->m_batteryStatusHandle));
    }

    void BatteryStatus_Unregister()
    {
        check_hresult(UnregisterCompositeBatteryStatusChangedListener(factory->m_batteryStatusHandle));
    }

    void BatteryStatus_Update()
    {
        check_hresult(GetCompositeBatteryStatus(&factory->m_cachedCompositeBatteryStatus));
        factory->ProcessCompositeBatteryStatus(*factory->m_cachedCompositeBatteryStatus);
    }
   
    // PowerSupplyStatus Functions
    EventType& PowerSupplyStatus_Event()
    {
        return factory->m_powerSupplyStatusChangedEvent;
    }

    void PowerSupplyStatus_Register()
    {
        BatteryStatus_Register();
    }

    void PowerSupplyStatus_Unregister()
    {
        BatteryStatus_Unregister();
    }

    void PowerSupplyStatus_Update()
    {
        BatteryStatus_Update();
    }
   
    // RemainingChargePercent Functions
    EventType& RemainingChargePercent_Event()
    {
        return factory->m_remainingChargePercentChangedEvent;
    }

    void RemainingChargePercent_Register()
    {
        BatteryStatus_Register();
    }

    void RemainingChargePercent_Unregister()
    {
        BatteryStatus_Unregister();
    }

    void RemainingChargePercent_Update()
    {
        BatteryStatus_Update();
    }

    // RemainingDischargeTime Functions
    EventType& RemainingDischargeTime_Event()
    {
        return factory->m_remainingDischargeTimeChangedEvent;
    }

    void RemainingDischargeTime_Register()
    {
        check_hresult(RegisterDischargeTimeChangedListener(&PowerManager::RemainingDischargeTimeChanged_Callback, &factory->m_dischargeTimeHandle));
    }

    void RemainingDischargeTime_Unregister()
    {
        check_hresult(UnregisterDischargeTimeChangedListener(factory->m_dischargeTimeHandle));
    }

    void RemainingDischargeTime_Update()
    {
        check_hresult(GetDischargeTime(&factory->m_cachedDischargeTime));
    }
   
    // PowerSourceStatus Functions
    EventType& PowerSourceStatus_Event()
    {
        return factory->m_powerSourceStatusChangedEvent;
    }

    void PowerSourceStatus_Register()
    {
        check_hresult(RegisterPowerConditionChangedListener(&PowerManager::PowerSourceStatusChanged_Callback, &factory->m_powerSourceStatusHandle));
    }

    void PowerSourceStatus_Unregister()
    {
        check_hresult(UnregisterPowerConditionChangedListener(factory->m_powerSourceStatusHandle));
    }

    void PowerSourceStatus_Update()
    {
        check_hresult(GetPowerCondition(&factory->m_cachedPowerSourceStatus));
    }
   
    // DisplayStatus Functions
    EventType& DisplayStatus_Event()
    {
        return factory->m_displayStatusChangedEvent;
    }

    void DisplayStatus_Register()
    {
        check_hresult(RegisterDisplayStatusChangedListener(&PowerManager::DisplayStatusChanged_Callback, &factory->m_displayStatusHandle));
    }

    void DisplayStatus_Unregister()
    {
        check_hresult(UnregisterDisplayStatusChangedListener(factory->m_displayStatusHandle));
    }

    void DisplayStatus_Update()
    {
        check_hresult(GetDisplayStatus(&factory->m_cachedDisplayStatus));
    }
   
    // SystemIdleStatus Functions
    EventType& SystemIdleStatus_Event()
    {
        return factory->m_systemIdleStatusChangedEvent;
    }

    void SystemIdleStatus_Register()
    {
        check_hresult(RegisterSystemIdleStatusChangedListener(&PowerManager::SystemIdleStatusChanged_Callback, &factory->m_systemIdleStatusHandle));
    }

    void SystemIdleStatus_Unregister()
    {
        check_hresult(UnregisterSystemIdleStatusChangedListener(factory->m_systemIdleStatusHandle));
    }
   
    // PowerSchemePersonality Functions
    EventType& PowerSchemePersonality_Event()
    {
        return factory->m_powerSchemePersonalityChangedEvent;
    }

    void PowerSchemePersonality_Register()
    {
        check_hresult(RegisterPowerSchemePersonalityChangedListener(&PowerManager::PowerSchemePersonalityChanged_Callback, &factory->m_powerSchemePersonalityHandle));
    }

    void PowerSchemePersonality_Unregister()
    {
        check_hresult(UnregisterPowerSchemePersonalityChangedListener(factory->m_powerSchemePersonalityHandle));
    }

    void PowerSchemePersonality_Update()
    {
        check_hresult(GetPowerSchemePersonality(&factory->m_cachedPowerSchemePersonality));
    }
   
    // UserPresenceStatus Functions
    EventType& UserPresenceStatus_Event()
    {
        return factory->m_userPresenceStatusChangedEvent;
    }

    void UserPresenceStatus_Register()
    {
        check_hresult(RegisterUserPresenceStatusChangedListener(&PowerManager::UserPresenceStatusChanged_Callback, &factory->m_userPresenceStatusHandle));
    }

    void UserPresenceStatus_Unregister()
    {
        check_hresult(UnregisterUserPresenceStatusChangedListener(factory->m_userPresenceStatusHandle));
    }

    void UserPresenceStatus_Update()
    {
        check_hresult(GetUserPresenceStatus(&factory->m_cachedUserPresenceStatus));
    }

    // SystemAwayModeStatus Functions
    EventType& SystemAwayModeStatus_Event()
    {
        return factory->m_systemAwayModeStatusChangedEvent;
    }

    void SystemAwayModeStatus_Register()
    {
        check_hresult(RegisterSystemAwayModeStatusChangedListener(&PowerManager::SystemAwayModeStatusChanged_Callback, &factory->m_systemAwayModeStatusHandle));
    }

    void SystemAwayModeStatus_Unregister()
    {
        check_hresult(UnregisterSystemAwayModeStatusChangedListener(factory->m_systemAwayModeStatusHandle));
    }

    void SystemAwayModeStatus_Update()
    {
        check_hresult(GetSystemAwayModeStatus(&factory->m_cachedSystemAwayModeStatus));
    }

}
