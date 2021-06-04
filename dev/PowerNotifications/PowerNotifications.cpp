// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <PowerNotifications.h>
#include <PowerNotificationsPal.h>
#include <PowerManager.g.cpp>
#include <powrprof.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{

    // EnergySaverStatus Functions
    EventType& EnergySaverStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_EnergySaverStatusChangedEvent;
    }

    void EnergySaverStatus_Register()
    {
        check_hresult(RegisterEnergySaverStatusChangedListener(
            &PowerManager::EnergySaverStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_EnergySaverStatusHandle));
    }

    void EnergySaverStatus_Unregister()
    {
        check_hresult(UnregisterEnergySaverStatusChangedListener(
            make_self<factory_implementation::PowerManager>()->m_EnergySaverStatusHandle));
    }

    void EnergySaverStatus_Update()
    {
        check_hresult(GetEnergySaverStatus(
            &make_self<factory_implementation::PowerManager>()->m_cachedEnergySaverStatus));
    }

    // BatteryStatus Functions
    EventType& BatteryStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_batteryStatusChangedEvent;
    }

    void BatteryStatus_Register()
    {
        check_hresult(RegisterCompositeBatteryStatusChangedListener(
            &PowerManager::CompositeBatteryStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_batteryStatusHandle));
    }

    void BatteryStatus_Unregister()
    {
        check_hresult(UnregisterCompositeBatteryStatusChangedListener(
            make_self<factory_implementation::PowerManager>()->m_batteryStatusHandle));
    }

    void BatteryStatus_Update()
    {
        check_hresult(GetCompositeBatteryStatus(
            &make_self<factory_implementation::PowerManager>()->m_cachedCompositeBatteryStatus));
        make_self<factory_implementation::PowerManager>()->ProcessCompositeBatteryStatus(
            make_self<factory_implementation::PowerManager>()->m_cachedCompositeBatteryStatus);
    }

    // PowerSupplyStatus Functions
    EventType& PowerSupplyStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_powerSupplyStatusChangedEvent;
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
        return make_self<factory_implementation::PowerManager>()->m_remainingChargePercentChangedEvent;
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
        return make_self<factory_implementation::PowerManager>()->m_remainingDischargeTimeChangedEvent;
    }

    void RemainingDischargeTime_Register()
    {
        check_hresult(RegisterDischargeTimeChangedListener(
            &PowerManager::RemainingDischargeTimeChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_dischargeTimeHandle));
    }

    void RemainingDischargeTime_Unregister()
    {
        check_hresult(UnregisterDischargeTimeChangedListener(
            make_self<factory_implementation::PowerManager>()->m_dischargeTimeHandle));
    }

    void RemainingDischargeTime_Update()
    {
        check_hresult(GetDischargeTime(
            &make_self<factory_implementation::PowerManager>()->m_cachedDischargeTime));
    }

    // PowerSourceStatus Functions
    EventType& PowerSourceStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_powerSourceStatusChangedEvent;
    }

    void PowerSourceStatus_Register()
    {
        check_hresult(RegisterPowerConditionChangedListener(
            &PowerManager::PowerSourceStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_powerSourceStatusHandle));
    }

    void PowerSourceStatus_Unregister()
    {
        check_hresult(UnregisterPowerConditionChangedListener(
            make_self<factory_implementation::PowerManager>()->m_powerSourceStatusHandle));
    }

    void PowerSourceStatus_Update()
    {
        check_hresult(GetPowerCondition(
            &make_self<factory_implementation::PowerManager>()->m_cachedPowerSourceStatus));
    }

    // DisplayStatus Functions
    EventType& DisplayStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_displayStatusChangedEvent;
    }

    void DisplayStatus_Register()
    {
        check_hresult(RegisterDisplayStatusChangedListener(
            &PowerManager::DisplayStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_displayStatusHandle));
    }

    void DisplayStatus_Unregister()
    {
        check_hresult(UnregisterDisplayStatusChangedListener
        (make_self<factory_implementation::PowerManager>()->m_displayStatusHandle));
    }

    void DisplayStatus_Update()
    {
        check_hresult(GetDisplayStatus(
            &make_self<factory_implementation::PowerManager>()->m_cachedDisplayStatus));
    }

    // SystemIdleStatus Functions
    EventType& SystemIdleStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_systemIdleStatusChangedEvent;
    }

    void SystemIdleStatus_Register()
    {
        check_hresult(RegisterSystemIdleStatusChangedListener(
            &PowerManager::SystemIdleStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_systemIdleStatusHandle));
    }

    void SystemIdleStatus_Unregister()
    {
        check_hresult(UnregisterSystemIdleStatusChangedListener(
            make_self<factory_implementation::PowerManager>()->m_systemIdleStatusHandle));
    }

    // PowerSchemePersonality V1 Functions
    EventType& PowerSchemePersonalityV1_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_powerSchemePersonalityV1ChangedEvent;
    }

    void PowerSchemePersonalityV1_Register()
    {
        check_hresult(PowerNotifications_RegisterPowerSchemePersonalityChangedListener(
            EFFECTIVE_POWER_MODE_V1,
            &PowerManager::PowerSchemePersonalityV1Changed_Callback,
            &make_self<factory_implementation::PowerManager>()->m_powerSchemePersonalityV1Handle));
    }

    void PowerSchemePersonalityV1_Unregister()
    {
        check_hresult(PowerNotifications_UnregisterPowerSchemePersonalityChangedListener(
            make_self<factory_implementation::PowerManager>()->m_powerSchemePersonalityV1Handle));
    }

    void PowerSchemePersonalityV1_Update()
    {
        check_hresult(PowerNotifications_GetPowerSchemePersonality(
            EFFECTIVE_POWER_MODE_V1,
            &make_self<factory_implementation::PowerManager>()->m_cachedPowerSchemePersonalityV1));
    }

    // PowerSchemePersonality V2 Functions
    EventType& PowerSchemePersonalityV2_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_powerSchemePersonalityv2ChangedEvent;
    }

    void PowerSchemePersonalityV2_Register()
    {
        check_hresult(PowerNotifications_RegisterPowerSchemePersonalityChangedListener(
            EFFECTIVE_POWER_MODE_V2,
            &PowerManager::PowerSchemePersonalityV2Changed_Callback,
            &make_self<factory_implementation::PowerManager>()->m_powerSchemePersonalityV2Handle));
    }

    void PowerSchemePersonalityV2_Unregister()
    {
        check_hresult(PowerNotifications_UnregisterPowerSchemePersonalityChangedListener(
            make_self<factory_implementation::PowerManager>()->m_powerSchemePersonalityV2Handle));
    }

    void PowerSchemePersonalityV2_Update()
    {
        check_hresult(PowerNotifications_GetPowerSchemePersonality(
            EFFECTIVE_POWER_MODE_V2,
            &make_self<factory_implementation::PowerManager>()->m_cachedPowerSchemePersonalityV2));
    }

    // UserPresenceStatus Functions
    EventType& UserPresenceStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_userPresenceStatusChangedEvent;
    }

    void UserPresenceStatus_Register()
    {
        check_hresult(RegisterUserPresenceStatusChangedListener(
            &PowerManager::UserPresenceStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_userPresenceStatusHandle));
    }

    void UserPresenceStatus_Unregister()
    {
        check_hresult(UnregisterUserPresenceStatusChangedListener(
            make_self<factory_implementation::PowerManager>()->m_userPresenceStatusHandle));
    }

    void UserPresenceStatus_Update()
    {
        check_hresult(GetUserPresenceStatus(
            &make_self<factory_implementation::PowerManager>()->m_cachedUserPresenceStatus));
    }

    // SystemSuspendStatus Functions
    EventType& SystemSuspendStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_systemSuspendStatusChangedEvent;
    }

    ULONG SuspendResumeCallback(PVOID, ULONG powerEvent, PVOID)
    {
        make_self<factory_implementation::PowerManager>()->SystemSuspendStatusChanged_Callback(powerEvent);
        return S_OK;
    }

    void SystemSuspendStatus_Register()
    {
        DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS powerParams = { 0 };
        powerParams.Callback = SuspendResumeCallback;

        check_win32(PowerRegisterSuspendResumeNotification(
            DEVICE_NOTIFY_CALLBACK,
            &powerParams,
            &make_self<factory_implementation::PowerManager>()->m_systemSuspendHandle));
    }

    void SystemSuspendStatus_Unregister()
    {
        check_win32(PowerUnregisterSuspendResumeNotification(
            make_self<factory_implementation::PowerManager>()->m_systemSuspendHandle));
    }
}
