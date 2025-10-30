// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <mutex>
#include <powersetting.h>
#include <Microsoft.Windows.System.Power.PowerManager.g.h>
#include <frameworkudk\PowerNotificationsPal.h>
#include <WindowsAppRuntimeInsights.h>

class PowerNotificationsTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(PowerNotificationsTelemetry, "Microsoft.WindowsAppSDK.System.PowerNotifications",
        // {a1b12e2c-12d9-564e-2ea1-2894ffcc7cc5}
        (0xa1b12e2c, 0x12d9, 0x564e, 0x2e, 0xa1, 0x28, 0x94, 0xff, 0xcc, 0x7c, 0xc5));

public:

    DEFINE_COMPLIANT_MEASURES_EVENT_STRING(AddCallbackTrace, PDT_ProductAndServiceUsage, eventName);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(FailureTrace, PDT_ProductAndServiceUsage,
        PCWSTR, eventName, PCWSTR, APIName, PCSTR, exceptionString);
};

namespace winrt::Microsoft::Windows::System::Power
{
    using PowerEventHandler =
        winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>;
    using EventType = winrt::event<PowerEventHandler>;

    // Forward-declarations
    namespace implementation
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

        EventType& PowerSourceKind_Event();
        void PowerSourceKind_Register();
        void PowerSourceKind_Unregister();
        void PowerSourceKind_Update();

        EventType& DisplayStatus_Event();
        void DisplayStatus_Register();
        void DisplayStatus_Unregister();
        void DisplayStatus_Update();

        EventType& SystemIdleStatus_Event();
        void SystemIdleStatus_Register();
        void SystemIdleStatus_Unregister();


        EventType& UserPresenceStatus_Event();
        void UserPresenceStatus_Register();
        void UserPresenceStatus_Unregister();
        void UserPresenceStatus_Update();

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
            void (*updateValue)();
            std::wstring name;
        };
    }

    namespace factory_implementation
    {
        using PowerFunctionDetails = implementation::PowerFunctionDetails;

        struct PowerManager : PowerManagerT<PowerManager, implementation::PowerManager, static_lifetime>
        {
            std::mutex m_mutex;
            int m_batteryChargePercent{ 100 };
            int m_oldBatteryChargePercent{ 0 };
            DWORD m_cachedDisplayStatus{ 0 };
            DWORD m_cachedUserPresenceStatus{ 0 };
            DWORD m_cachedSystemAwayModeStatus{ 0 };
            DWORD m_cachedPowerSourceKind{ 0 };
            EFFECTIVE_POWER_MODE m_cachedPowerMode{ EffectivePowerModeBatterySaver };
            ULONGLONG m_cachedDischargeTime{ 0 };
            std::atomic<ULONG> m_powerModeVersion;
            Power::SystemSuspendStatus m_systemSuspendStatus{ SystemSuspendStatus::Uninitialized };
            ::EnergySaverStatus m_cachedEnergySaverStatus{ Uninitalized };
            CompositeBatteryStatus m_cachedCompositeBatteryStatus{};
            Power::BatteryStatus m_batteryStatus{ Power::BatteryStatus::NotPresent };
            Power::BatteryStatus m_oldBatteryStatus{ Power::BatteryStatus::NotPresent };
            Power::PowerSupplyStatus m_powerSupplyStatus{ Power::PowerSupplyStatus::Adequate };
            Power::PowerSupplyStatus m_oldPowerSupplyStatus{ Power::PowerSupplyStatus::Adequate };

            EventType m_energySaverStatusChangedEvent;
            EventType m_batteryStatusChangedEvent;
            EventType m_powerSupplyStatusChangedEvent;
            EventType m_remainingChargePercentChangedEvent;
            EventType m_remainingDischargeTimeChangedEvent;
            EventType m_powerSourceKindChangedEvent;
            EventType m_displayStatusChangedEvent;
            EventType m_systemIdleStatusChangedEvent;
            EventType m_powerModeChangedEvent;
            EventType m_userPresenceStatusChangedEvent;
            EventType m_systemAwayModeStatusChangedEvent;
            EventType m_systemSuspendStatusChangedEvent;

            EnergySaverStatusRegistration m_energySaverStatusHandle{};
            CompositeBatteryStatusRegistration m_batteryStatusHandle{};
            PowerConditionRegistration m_powerSourceKindHandle{};
            DischargeTimeRegistration m_dischargeTimeHandle{};
            DisplayStatusRegistration m_displayStatusHandle{};
            SystemIdleStatusRegistration m_systemIdleStatusHandle{};
            UserPresenceStatusRegistration m_userPresenceStatusHandle{};
            HPOWERNOTIFY m_systemSuspendHandle{};
            void* m_powerModeHandle{};

            PowerFunctionDetails energySaverStatusFunc{
                &Power::implementation::EnergySaverStatus_Event,
                &Power::implementation::EnergySaverStatus_Register,
                &Power::implementation::EnergySaverStatus_Unregister,
                &Power::implementation::EnergySaverStatus_Update,
                L"EnergySaverStatus" };

            PowerFunctionDetails compositeBatteryStatusFunc{
                &Power::implementation::BatteryStatus_Event,
                &Power::implementation::BatteryStatus_Register,
                &Power::implementation::BatteryStatus_Unregister,
                &Power::implementation::BatteryStatus_Update,
                L"BatteryStatus" };

            PowerFunctionDetails powerSupplyStatusFunc{
                &Power::implementation::PowerSupplyStatus_Event,
                &Power::implementation::PowerSupplyStatus_Register,
                &Power::implementation::PowerSupplyStatus_Unregister,
                &Power::implementation::PowerSupplyStatus_Update,
                L"PowerSupplyStatus" };

            PowerFunctionDetails remainingChargePercentFunc{
                &Power::implementation::RemainingChargePercent_Event,
                &Power::implementation::RemainingChargePercent_Register,
                &Power::implementation::RemainingChargePercent_Unregister,
                &Power::implementation::RemainingChargePercent_Update,
                L"RemainingChargePercent" };

            PowerFunctionDetails remainingDischargeTimeFunc{
                &Power::implementation::RemainingDischargeTime_Event,
                &Power::implementation::RemainingDischargeTime_Register,
                &Power::implementation::RemainingDischargeTime_Unregister,
                &Power::implementation::RemainingDischargeTime_Update,
                L"RemainingDischargeTime" };

            PowerFunctionDetails powerSourceKindFunc{
                &Power::implementation::PowerSourceKind_Event,
                &Power::implementation::PowerSourceKind_Register,
                &Power::implementation::PowerSourceKind_Unregister,
                &Power::implementation::PowerSourceKind_Update,
                L"PowerSourceKind" };

            PowerFunctionDetails displayStatusFunc{
                &Power::implementation::DisplayStatus_Event,
                &Power::implementation::DisplayStatus_Register,
                &Power::implementation::DisplayStatus_Unregister,
                &Power::implementation::DisplayStatus_Update,
                L"DisplayStatus" };

            PowerFunctionDetails systemIdleStatusFunc{
                &Power::implementation::SystemIdleStatus_Event,
                &Power::implementation::SystemIdleStatus_Register,
                &Power::implementation::SystemIdleStatus_Unregister,
                &Power::implementation::NoOperation,
                L"SystemIdleStatus" };


            PowerFunctionDetails userPresenceStatusFunc{
                &Power::implementation::UserPresenceStatus_Event,
                &Power::implementation::UserPresenceStatus_Register,
                &Power::implementation::UserPresenceStatus_Unregister,
                &Power::implementation::UserPresenceStatus_Update,
                L"UserPresenceStatus" };

            PowerFunctionDetails systemSuspendFunc{
                &Power::implementation::SystemSuspendStatus_Event,
                &Power::implementation::SystemSuspendStatus_Register,
                &Power::implementation::SystemSuspendStatus_Unregister,
                &Power::implementation::NoOperation,
                L"SystemSuspendStatus" };

            bool RegisteredForEvents(const EventType& eventObj)
            {
                return eventObj ? true : false;
            }

            event_token AddCallback(PowerFunctionDetails fn, const PowerEventHandler& handler)
            {
                try
                {
                    PowerNotificationsTelemetry::AddCallbackTrace(fn.name.c_str());
                    auto& eventObj{ fn.event() };
                    std::scoped_lock<std::mutex> lock(m_mutex);
                    if (!RegisteredForEvents(eventObj))
                    {
                        fn.registerListener();
                    }
                    return eventObj.add(handler);
                }
                catch (std::exception& ex)
                {
                    PowerNotificationsTelemetry::FailureTrace(fn.name.c_str(), L"AddCallback", ex.what());
                    throw ex;
                }
            }

            void RemoveCallback(PowerFunctionDetails fn, const event_token& token)
            {
                auto& eventObj{ fn.event() };
                std::scoped_lock<std::mutex> lock(m_mutex);
                eventObj.remove(token);
                // If that was the last registration, remove the OS registration
                if (!RegisteredForEvents(eventObj))
                {
                    fn.unregisterListener();
                }
            }

            winrt::fire_and_forget RaiseEvent(PowerFunctionDetails fn)
            {
                auto lifetime = get_strong();
                co_await winrt::resume_background();
                fn.event()(nullptr, nullptr);
            }

            // Checks if an event is already registered. If none are, then gets the status
            void UpdateValuesIfNecessary(PowerFunctionDetails fn)
            {
                auto& eventObj{ fn.event() };
                std::scoped_lock<std::mutex> lock(m_mutex);
                if (!RegisteredForEvents(eventObj))
                {
                    fn.updateValue();
                }
            }


            // EnergySaverStatus Functions
            Power::EnergySaverStatus EnergySaverStatus()
            {
                UpdateValuesIfNecessary(energySaverStatusFunc);
                return static_cast<Power::EnergySaverStatus>(m_cachedEnergySaverStatus);
            }

            event_token EnergySaverStatusChanged(const PowerEventHandler& handler)
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
                auto fullChargedCapacity{ compositeBatteryStatus.Information.FullChargedCapacity };
                auto remainingCapacity{ compositeBatteryStatus.Status.Capacity };
                if (fullChargedCapacity == BATTERY_UNKNOWN_CAPACITY ||
                    fullChargedCapacity == 0)
                {
                    LOG_HR_MSG(E_FAIL, "Unknown charge ratio: FullChargedCapacity Unknown");
                }
                else if (remainingCapacity == BATTERY_UNKNOWN_CAPACITY)
                {
                    LOG_HR_MSG(E_FAIL, "Unknown charge ratio: RemainingCapacity Unknown");
                }
                else if (remainingCapacity > fullChargedCapacity)
                {
                    LOG_HR_MSG(E_FAIL, "High charge ratio: %d/%d", remainingCapacity, fullChargedCapacity);
                }
                else if (remainingCapacity > (INT_MAX / 200))
                {
                    LOG_HR_MSG(E_FAIL, "Absurd capacity: %d/%d", remainingCapacity, fullChargedCapacity);
                }
                else
                {
                    auto newRemainingChargePercent{ static_cast<int>((remainingCapacity * 200) / fullChargedCapacity) };
                    newRemainingChargePercent += 1;
                    newRemainingChargePercent /= 2;
                    m_batteryChargePercent = newRemainingChargePercent;
                }

                auto powerState{ compositeBatteryStatus.Status.PowerState };

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

            Power::BatteryStatus BatteryStatus()
            {
                UpdateValuesIfNecessary(compositeBatteryStatusFunc);
                return m_batteryStatus;
            }

            event_token BatteryStatusChanged(const PowerEventHandler& handler)
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
            Power::PowerSupplyStatus PowerSupplyStatus()
            {
                UpdateValuesIfNecessary(compositeBatteryStatusFunc);
                return m_powerSupplyStatus;
            }

            event_token PowerSupplyStatusChanged(const PowerEventHandler& handler)
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
                UpdateValuesIfNecessary(compositeBatteryStatusFunc);
                return m_batteryChargePercent;
            }

            event_token RemainingChargePercentChanged(const PowerEventHandler& handler)
            {
                return AddCallback(remainingChargePercentFunc, handler);
            }

            void RemainingChargePercentChanged(const event_token& token)
            {
                RemoveCallback(remainingChargePercentFunc, token);
            }


            // RemainingDischargeTime Functions
            winrt::Windows::Foundation::TimeSpan RemainingDischargeTime()
            {
                UpdateValuesIfNecessary(remainingDischargeTimeFunc);
                return winrt::Windows::Foundation::TimeSpan(std::chrono::seconds(m_cachedDischargeTime));
            }

            event_token RemainingDischargeTimeChanged(const PowerEventHandler& handler)
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


            // PowerSourceKind Functions
            Power::PowerSourceKind PowerSourceKind()
            {
                UpdateValuesIfNecessary(powerSourceKindFunc);
                return static_cast<Power::PowerSourceKind>(m_cachedPowerSourceKind);
            }

            event_token PowerSourceKindChanged(const PowerEventHandler& handler)
            {
                return AddCallback(powerSourceKindFunc, handler);
            }

            void PowerSourceKindChanged(const event_token& token)
            {
                RemoveCallback(powerSourceKindFunc, token);
            }

            void PowerSourceKindChanged_Callback(DWORD powerCondition)
            {
                m_cachedPowerSourceKind = powerCondition;
                RaiseEvent(powerSourceKindFunc);
            }


            // DisplayStatus Functions
            Power::DisplayStatus DisplayStatus()
            {
                UpdateValuesIfNecessary(displayStatusFunc);
                return static_cast<Power::DisplayStatus>(m_cachedDisplayStatus);
            }

            event_token DisplayStatusChanged(const PowerEventHandler& handler)
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
            // There is no get function as there is no data to be returned
            event_token SystemIdleStatusChanged(const PowerEventHandler& handler)
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



            Power::EffectivePowerMode EffectivePowerMode2()
            {
                UpdateValuesIfNecessary(effectivePowerModeFunc);
                return static_cast<Power::EffectivePowerMode>(m_cachedPowerMode);
            }

            event_token EffectivePowerModeChanged(const PowerEventHandler& handler)
            {
                return AddCallback(effectivePowerModeFunc, handler);
            }

            void EffectivePowerModeChanged(const event_token& token)
            {
                RemoveCallback(effectivePowerModeFunc, token);
            }

            void EffectivePowerModeChanged_Callback(EFFECTIVE_POWER_MODE mode)
            {
                m_cachedPowerMode = mode;
                RaiseEvent(effectivePowerModeFunc);
            }


            // UserPresenceStatus Functions
            Power::UserPresenceStatus UserPresenceStatus()
            {
                UpdateValuesIfNecessary(userPresenceStatusFunc);
                return static_cast<Power::UserPresenceStatus>(m_cachedUserPresenceStatus);
            }

            event_token UserPresenceStatusChanged(const PowerEventHandler& handler)
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


            //SystemSuspend Functions
            Power::SystemSuspendStatus SystemSuspendStatus()
            {
                if (m_systemSuspendStatus == SystemSuspendStatus::Uninitialized)
                {
                    throw winrt::hresult_error(E_FAIL, L"API only callable after a SystemSuspendStatusChanged callback");
                }
                return static_cast<Power::SystemSuspendStatus>(m_systemSuspendStatus);
            }

            event_token SystemSuspendStatusChanged(const PowerEventHandler& handler)
            {
                return AddCallback(systemSuspendFunc, handler);
            }

            void SystemSuspendStatusChanged(const event_token& token)
            {
                RemoveCallback(systemSuspendFunc, token);
            }

            void SystemSuspendStatusChanged_Callback(ULONG PowerEvent)
            {
                using namespace Power;
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
            }

        };
    };

    namespace implementation
    {
        struct PowerManager
        {
            PowerManager() = delete;

            static auto Factory()
            {
                return make_self<factory_implementation::PowerManager>();
            }

            //Get function forwards
            static Power::EnergySaverStatus EnergySaverStatus()
            {
                return Factory()->EnergySaverStatus();
            }

            static Power::BatteryStatus BatteryStatus()
            {
                return Factory()->BatteryStatus();
            }

            static Power::PowerSupplyStatus PowerSupplyStatus()
            {
                return Factory()->PowerSupplyStatus();
            }

            static int RemainingChargePercent()
            {
                return Factory()->RemainingChargePercent();
            }

            static winrt::Windows::Foundation::TimeSpan RemainingDischargeTime()
            {
                return Factory()->RemainingDischargeTime();
            }

            static Power::PowerSourceKind PowerSourceKind()
            {
                return Factory()->PowerSourceKind();
            }

            static Power::DisplayStatus DisplayStatus()
            {
                return Factory()->DisplayStatus();
            }

            static winrt::Windows::Foundation::IAsyncOperation<Power::EffectivePowerMode> EffectivePowerMode()
            {
                return Factory()->EffectivePowerMode();
            }

            static Power::EffectivePowerMode EffectivePowerMode2()
            {
                return Factory()->EffectivePowerMode2();
            }

            static Power::UserPresenceStatus UserPresenceStatus()
            {
                return Factory()->UserPresenceStatus();
            }

            static Power::SystemSuspendStatus SystemSuspendStatus()
            {
                return Factory()->SystemSuspendStatus();
            }

            //Callback forwards
            static void EnergySaverStatusChanged_Callback(::EnergySaverStatus energySaverStatus)
            {
                return Factory()->EnergySaverStatusChanged_Callback(energySaverStatus);
            }

            static void CompositeBatteryStatusChanged_Callback(CompositeBatteryStatus compositeBatteryStatus)
            {
                return Factory()->CompositeBatteryStatusChanged_Callback(compositeBatteryStatus);
            }

            static void RemainingDischargeTimeChanged_Callback(ULONGLONG remainingDischargeTime)
            {
                return Factory()->RemainingDischargeTimeChanged_Callback(remainingDischargeTime);
            }

            static void PowerSourceKindChanged_Callback(DWORD powerCondition)
            {
                return Factory()->PowerSourceKindChanged_Callback(powerCondition);
            }

            static void DisplayStatusChanged_Callback(DWORD displayStatus)
            {
                return Factory()->DisplayStatusChanged_Callback(displayStatus);
            }

            static void SystemIdleStatusChanged_Callback()
            {
                return Factory()->SystemIdleStatusChanged_Callback();
            }

            static void EffectivePowerModeChanged_Callback(EFFECTIVE_POWER_MODE mode)
            {
                return Factory()->EffectivePowerModeChanged_Callback(mode);
            }

            static void UserPresenceStatusChanged_Callback(DWORD userPresenceStatus)
            {
                return Factory()->UserPresenceStatusChanged_Callback(userPresenceStatus);
            }

        };
    }
}
