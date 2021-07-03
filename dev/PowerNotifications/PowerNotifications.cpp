// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <future>
#include <PowerNotifications.h>
#include <frameworkudk\PowerNotificationsPal.h>
#include <Microsoft.Windows.System.Power.PowerManager.g.cpp>
#include <powrprof.h>

namespace winrt::Microsoft::Windows::System::Power::implementation
{

    // EnergySaverStatus Functions
    EventType& EnergySaverStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_EnergySaverStatusChangedEvent;
    }

    void EnergySaverStatus_Register()
    {
        check_hresult(PowerNotifications_RegisterEnergySaverStatusChangedListener(
            &PowerManager::EnergySaverStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_EnergySaverStatusHandle));
    }

    void EnergySaverStatus_Unregister()
    {
        auto& handle = make_self<factory_implementation::PowerManager>()->m_EnergySaverStatusHandle;
		check_hresult(PowerNotifications_UnregisterEnergySaverStatusChangedListener(handle));
		handle = 0;
    }

    void EnergySaverStatus_Update()
    {
        check_hresult(PowerNotifications_GetEnergySaverStatus(
            &make_self<factory_implementation::PowerManager>()->m_cachedEnergySaverStatus));
    }

    // BatteryStatus Functions
    EventType& BatteryStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_batteryStatusChangedEvent;
    }

    void BatteryStatus_Register()
    {
        check_hresult(PowerNotifications_RegisterCompositeBatteryStatusChangedListener(
            &PowerManager::CompositeBatteryStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_batteryStatusHandle));
    }

    void BatteryStatus_Unregister()
    {
        auto& handle = make_self<factory_implementation::PowerManager>()->m_batteryStatusHandle;
		check_hresult(PowerNotifications_UnregisterCompositeBatteryStatusChangedListener(handle));
		handle = 0;
    }

    void BatteryStatus_Update()
    {
        auto ref = &make_self<factory_implementation::PowerManager>()->m_cachedCompositeBatteryStatus;
        auto res = PowerNotifications_GetCompositeBatteryStatus(ref);
        if (res == S_OK)
        {
            make_self<factory_implementation::PowerManager>()->ProcessCompositeBatteryStatus(*ref);
        }
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
        check_hresult(PowerNotifications_RegisterDischargeTimeChangedListener(
            &PowerManager::RemainingDischargeTimeChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_dischargeTimeHandle));
    }

    void RemainingDischargeTime_Unregister()
    {
        auto& handle = make_self<factory_implementation::PowerManager>()->m_dischargeTimeHandle;
		check_hresult(PowerNotifications_UnregisterDischargeTimeChangedListener(handle));
		handle = 0;
    }

    void RemainingDischargeTime_Update()
    {
        check_hresult(PowerNotifications_GetDischargeTime(
            &make_self<factory_implementation::PowerManager>()->m_cachedDischargeTime));
    }

    // PowerSourceKind Functions
    EventType& PowerSourceKind_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_PowerSourceKindChangedEvent;
    }

    void PowerSourceKind_Register()
    {
        check_hresult(PowerNotifications_RegisterPowerConditionChangedListener(
            &PowerManager::PowerSourceKindChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_PowerSourceKindHandle));
    }

    void PowerSourceKind_Unregister()
    {
        auto& handle = make_self<factory_implementation::PowerManager>()->m_PowerSourceKindHandle;
		check_hresult(PowerNotifications_UnregisterPowerConditionChangedListener(handle));
		handle = 0;
    }

    void PowerSourceKind_Update()
    {
        check_hresult(PowerNotifications_GetPowerCondition(
            &make_self<factory_implementation::PowerManager>()->m_cachedPowerSourceKind));
    }

    // DisplayStatus Functions
    EventType& DisplayStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_displayStatusChangedEvent;
    }

    void DisplayStatus_Register()
    {
        check_hresult(PowerNotifications_RegisterDisplayStatusChangedListener(
            &PowerManager::DisplayStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_displayStatusHandle));
    }

    void DisplayStatus_Unregister()
    {
        auto& handle = make_self<factory_implementation::PowerManager>()->m_displayStatusHandle;
		check_hresult(PowerNotifications_UnregisterDisplayStatusChangedListener(handle));
		handle = 0;
    }

    void DisplayStatus_Update()
    {
        check_hresult(PowerNotifications_GetDisplayStatus(
            &make_self<factory_implementation::PowerManager>()->m_cachedDisplayStatus));
    }

    // SystemIdleStatus Functions
    EventType& SystemIdleStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_systemIdleStatusChangedEvent;
    }

    void SystemIdleStatus_Register()
    {
        check_hresult(PowerNotifications_RegisterSystemIdleStatusChangedListener(
            &PowerManager::SystemIdleStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_systemIdleStatusHandle));
    }

    void SystemIdleStatus_Unregister()
    {
        auto& handle = make_self<factory_implementation::PowerManager>()->m_systemIdleStatusHandle;
		check_hresult(PowerNotifications_UnregisterSystemIdleStatusChangedListener(handle));
		handle = 0;
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

        struct notify_callback {
            EFFECTIVE_POWER_MODE mode;
            wil::slim_event done;
        } context;

        PVOID handle;
        ULONG version = GetEffectivePowerModeVersion();
        auto handler = [](EFFECTIVE_POWER_MODE mode, PVOID rawContext) {
            auto context = reinterpret_cast<notify_callback*>(rawContext);
            context->mode = mode;
            context->done.SetEvent();
        };

        check_hresult(PowerRegisterForEffectivePowerModeNotifications(version, handler, &context, &handle));
        context.done.wait();
        make_self<factory_implementation::PowerManager>()->m_cachedPowerMode = context.mode;
        check_hresult(PowerUnregisterFromEffectivePowerModeNotifications(handle));
    }

    // UserPresenceStatus Functions
    EventType& UserPresenceStatus_Event()
    {
        return make_self<factory_implementation::PowerManager>()->m_userPresenceStatusChangedEvent;
    }

    void UserPresenceStatus_Register()
    {
        check_hresult(PowerNotifications_RegisterUserPresenceStatusChangedListener(
            &PowerManager::UserPresenceStatusChanged_Callback,
            &make_self<factory_implementation::PowerManager>()->m_userPresenceStatusHandle));
    }

    void UserPresenceStatus_Unregister()
    {
        auto& handle = make_self<factory_implementation::PowerManager>()->m_userPresenceStatusHandle;
		check_hresult(PowerNotifications_UnregisterUserPresenceStatusChangedListener(handle));
		handle = 0;
    }

    void UserPresenceStatus_Update()
    {
        check_hresult(PowerNotifications_GetUserPresenceStatus(
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
        auto& handle = make_self<factory_implementation::PowerManager>()->m_systemSuspendHandle;
		check_win32(PowerUnregisterSuspendResumeNotification(handle));
		handle = 0;
    }
}
