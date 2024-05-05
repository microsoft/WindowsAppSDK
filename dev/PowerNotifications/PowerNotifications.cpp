// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <future>
#include <PowerNotifications.h>
#include <frameworkudk\PowerNotificationsPal.h>
#include <Microsoft.Windows.System.Power.PowerManager.g.cpp>
#include <powrprof.h>

namespace winrt::Microsoft::Windows::System::Power::implementation
{
    auto Factory()
    {
        return make_self<factory_implementation::PowerManager>();
    }

    // EnergySaverStatus Functions
    EventType& EnergySaverStatus_Event()
    {
        return Factory()->m_energySaverStatusChangedEvent;
    }

    void EnergySaverStatus_Register()
    {
        THROW_IF_FAILED(PowerNotifications_RegisterEnergySaverStatusChangedListener(
            &PowerManager::EnergySaverStatusChanged_Callback,
            &Factory()->m_energySaverStatusHandle));
    }

    void EnergySaverStatus_Unregister()
    {
        THROW_IF_FAILED(PowerNotifications_UnregisterEnergySaverStatusChangedListener(
            Factory()->m_energySaverStatusHandle));
    }

    void EnergySaverStatus_Update()
    {
        THROW_IF_FAILED(PowerNotifications_GetEnergySaverStatus(
            &Factory()->m_cachedEnergySaverStatus));
    }

    // BatteryStatus Functions
    EventType& BatteryStatus_Event()
    {
        return Factory()->m_batteryStatusChangedEvent;
    }

    void BatteryStatus_Register()
    {
        THROW_IF_FAILED(PowerNotifications_RegisterCompositeBatteryStatusChangedListener(
            &PowerManager::CompositeBatteryStatusChanged_Callback,
            &Factory()->m_batteryStatusHandle));
    }

    void BatteryStatus_Unregister()
    {
        THROW_IF_FAILED(PowerNotifications_UnregisterCompositeBatteryStatusChangedListener(
            Factory()->m_batteryStatusHandle));
    }

    void BatteryStatus_Update()
    {
        auto status{ &Factory()->m_cachedCompositeBatteryStatus };
        if (SUCCEEDED(PowerNotifications_GetCompositeBatteryStatus(status)))
        {
            Factory()->ProcessCompositeBatteryStatus(*status);
        }
    }

    // PowerSupplyStatus Functions
    EventType& PowerSupplyStatus_Event()
    {
        return Factory()->m_powerSupplyStatusChangedEvent;
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
        return Factory()->m_remainingChargePercentChangedEvent;
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
        return Factory()->m_remainingDischargeTimeChangedEvent;
    }

    void RemainingDischargeTime_Register()
    {
        THROW_IF_FAILED(PowerNotifications_RegisterDischargeTimeChangedListener(
            &PowerManager::RemainingDischargeTimeChanged_Callback,
            &Factory()->m_dischargeTimeHandle));
    }

    void RemainingDischargeTime_Unregister()
    {
        THROW_IF_FAILED(PowerNotifications_UnregisterDischargeTimeChangedListener(
            Factory()->m_dischargeTimeHandle));
    }

    void RemainingDischargeTime_Update()
    {
        THROW_IF_FAILED(PowerNotifications_GetDischargeTime(
            &Factory()->m_cachedDischargeTime));
    }

    // PowerSourceKind Functions
    EventType& PowerSourceKind_Event()
    {
        return Factory()->m_powerSourceKindChangedEvent;
    }

    void PowerSourceKind_Register()
    {
        THROW_IF_FAILED(PowerNotifications_RegisterPowerConditionChangedListener(
            &PowerManager::PowerSourceKindChanged_Callback,
            &Factory()->m_powerSourceKindHandle));
    }

    void PowerSourceKind_Unregister()
    {
        THROW_IF_FAILED(PowerNotifications_UnregisterPowerConditionChangedListener(
            Factory()->m_powerSourceKindHandle));
    }

    void PowerSourceKind_Update()
    {
        THROW_IF_FAILED(PowerNotifications_GetPowerCondition(
            &Factory()->m_cachedPowerSourceKind));
    }

    // DisplayStatus Functions
    EventType& DisplayStatus_Event()
    {
        return Factory()->m_displayStatusChangedEvent;
    }

    void DisplayStatus_Register()
    {
        THROW_IF_FAILED(PowerNotifications_RegisterDisplayStatusChangedListener(
            &PowerManager::DisplayStatusChanged_Callback,
            &Factory()->m_displayStatusHandle));
    }

    void DisplayStatus_Unregister()
    {
        THROW_IF_FAILED(PowerNotifications_UnregisterDisplayStatusChangedListener
        (Factory()->m_displayStatusHandle));
    }

    void DisplayStatus_Update()
    {
        THROW_IF_FAILED(PowerNotifications_GetDisplayStatus(
            &Factory()->m_cachedDisplayStatus));
    }

    // SystemIdleStatus Functions
    EventType& SystemIdleStatus_Event()
    {
        return Factory()->m_systemIdleStatusChangedEvent;
    }

    void SystemIdleStatus_Register()
    {
        THROW_IF_FAILED(PowerNotifications_RegisterSystemIdleStatusChangedListener(
            &PowerManager::SystemIdleStatusChanged_Callback,
            &Factory()->m_systemIdleStatusHandle));
    }

    void SystemIdleStatus_Unregister()
    {
        THROW_IF_FAILED(PowerNotifications_UnregisterSystemIdleStatusChangedListener(
            Factory()->m_systemIdleStatusHandle));
    }

    ULONG GetEffectivePowerModeVersion()
    {
        // We check for the version supported by checking if the feature is supported
        // Using NULL as an indicator for uninitialized cache value
        auto& version{ Factory()->m_powerModeVersion };
        if (!version)
        {
            void* handle{};
            auto hr{ PowerRegisterForEffectivePowerModeNotifications(
                EFFECTIVE_POWER_MODE_V2, [](EFFECTIVE_POWER_MODE, void*) {}, nullptr, &handle) };
            version = SUCCEEDED(hr) ? EFFECTIVE_POWER_MODE_V2 : EFFECTIVE_POWER_MODE_V1;
            THROW_IF_FAILED(PowerUnregisterFromEffectivePowerModeNotifications(handle));
        }
        return version;
    }

    EventType& EffectivePowerMode_Event()
    {
        return Factory()->m_powerModeChangedEvent;
    }

    void EffectivePowerMode_Register()
    {
        ULONG version{ GetEffectivePowerModeVersion() };
        auto& powerModeHandle{ Factory()->m_powerModeHandle };
        THROW_IF_FAILED(PowerRegisterForEffectivePowerModeNotifications(
            version, [](EFFECTIVE_POWER_MODE mode, void*)
            {
                PowerManager::EffectivePowerModeChanged_Callback(mode);
            }, nullptr, &powerModeHandle));
    }

    void EffectivePowerMode_Unregister()
    {
        auto& powerModeHandle{ Factory()->m_powerModeHandle };
        THROW_IF_FAILED(PowerUnregisterFromEffectivePowerModeNotifications(powerModeHandle));
        powerModeHandle = nullptr;
    }

    void EffectivePowerMode_Update()
    {
        // Effectively the Get() for PowerMode
        // Needs to get a temporary subscription to get most recent value

        struct notify_callback {
            EFFECTIVE_POWER_MODE mode{ EffectivePowerModeBatterySaver };
            wil::slim_event done;
        } context;

        auto handler{ [](EFFECTIVE_POWER_MODE mode, void* rawContext) {
            auto context{ reinterpret_cast<notify_callback*>(rawContext) };
            context->mode = mode;
            context->done.SetEvent();
        } };

        void* handle{};
        ULONG version{ GetEffectivePowerModeVersion() };

        THROW_IF_FAILED(PowerRegisterForEffectivePowerModeNotifications(version, handler, &context, &handle));
        context.done.wait();
        Factory()->m_cachedPowerMode = context.mode;
        THROW_IF_FAILED(PowerUnregisterFromEffectivePowerModeNotifications(handle));
    }

    // UserPresenceStatus Functions
    EventType& UserPresenceStatus_Event()
    {
        return Factory()->m_userPresenceStatusChangedEvent;
    }

    void UserPresenceStatus_Register()
    {
        THROW_IF_FAILED(PowerNotifications_RegisterUserPresenceStatusChangedListener(
            &PowerManager::UserPresenceStatusChanged_Callback,
            &Factory()->m_userPresenceStatusHandle));
    }

    void UserPresenceStatus_Unregister()
    {
        THROW_IF_FAILED(PowerNotifications_UnregisterUserPresenceStatusChangedListener(
            Factory()->m_userPresenceStatusHandle));
    }

    void UserPresenceStatus_Update()
    {
        THROW_IF_FAILED(PowerNotifications_GetUserPresenceStatus(
            &Factory()->m_cachedUserPresenceStatus));
    }

    // SystemSuspendStatus Functions
    EventType& SystemSuspendStatus_Event()
    {
        return Factory()->m_systemSuspendStatusChangedEvent;
    }

    // Using PVOID as per the actual typedef
    ULONG CALLBACK SuspendResumeCallback(PVOID context, ULONG powerEvent, PVOID setting)
    {
        UNREFERENCED_PARAMETER(context);
        UNREFERENCED_PARAMETER(setting);
        Factory()->SystemSuspendStatusChanged_Callback(powerEvent);
        return ERROR_SUCCESS;
    }

    void SystemSuspendStatus_Register()
    {
        DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS powerParams{};
        powerParams.Callback = SuspendResumeCallback;

        check_win32(PowerRegisterSuspendResumeNotification(
            DEVICE_NOTIFY_CALLBACK,
            &powerParams,
            &Factory()->m_systemSuspendHandle));
    }

    void SystemSuspendStatus_Unregister()
    {
        check_win32(PowerUnregisterSuspendResumeNotification(
            Factory()->m_systemSuspendHandle));
    }
}
