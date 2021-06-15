// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <future>
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

    ULONG GetEffectivePowerModeVersion()
    {
        // We check for the version supported by checking if the feature is supported
        // Using NULL as an indicator for uninitialized cache value
        if (g_powerModeVersion == NULL)
        {
            PVOID handle;
            auto hr = PowerRegisterForEffectivePowerModeNotifications(
                EFFECTIVE_POWER_MODE_V2, [](EFFECTIVE_POWER_MODE, PVOID) {}, NULL, &handle);
            g_powerModeVersion = hr == S_OK ? EFFECTIVE_POWER_MODE_V2 : EFFECTIVE_POWER_MODE_V1;
            check_hresult(PowerUnregisterFromEffectivePowerModeNotifications(handle));
        }
        return g_powerModeVersion;
    }

    EventType& EffectivePowerMode_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_powerModeChangedEvent;
    }

    void EffectivePowerMode_Register()
    {
        ULONG version = GetEffectivePowerModeVersion();
        check_hresult(PowerRegisterForEffectivePowerModeNotifications(
            version, [](EFFECTIVE_POWER_MODE mode, PVOID)
            {
                PowerManager::EffectivePowerModeChanged_Callback(mode);
            }, nullptr, &g_powerModeHandle));
    }

    void EffectivePowerMode_Unregister()
    {
        check_hresult(PowerUnregisterFromEffectivePowerModeNotifications(g_powerModeHandle));
        g_powerModeHandle = NULL;
    }

    void EffectivePowerMode_Update()
    {
        // Effectively the Get() for PowerMode
        // Needs to get a temporary subscription to get most recent value
        // Also, we need a static so that it can be accessed in the lambda below
        // since references or [&] doesn't work
        static std::promise<EFFECTIVE_POWER_MODE> promiseObj;
        static std::future<EFFECTIVE_POWER_MODE> futureObj;
        PVOID handle;
        ULONG version = GetEffectivePowerModeVersion();
        promiseObj = std::promise<EFFECTIVE_POWER_MODE>();
        futureObj = promiseObj.get_future();

        check_hresult(PowerRegisterForEffectivePowerModeNotifications(
            version, [](EFFECTIVE_POWER_MODE mode, PVOID)
            {
                promiseObj.set_value(mode);
            }, NULL, &handle));
        make_self<factory_implementation::PowerManager>()->m_cachedPowerMode = futureObj.get();
        check_hresult(PowerUnregisterFromEffectivePowerModeNotifications(handle));
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
