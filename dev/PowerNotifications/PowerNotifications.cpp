// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <PowerNotifications.h>
#include <PowerNotificationsPal.h>
#include <PowerManager.g.cpp>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    
    PowerManager::eventType PowerManager::m_energySaverStatusChangedEvent;
    PowerManager::eventType PowerManager::m_batteryStatusChangedEvent;
    PowerManager::eventType PowerManager::m_powerSupplyStatusChangedEvent;
    PowerManager::eventType PowerManager::m_remainingChargePercentChangedEvent;
    PowerManager::eventType PowerManager::m_remainingDischargeTimeChangedEvent;

    PowerManager::eventType PowerManager::m_powerSourceStatusChangedEvent;
    PowerManager::eventType PowerManager::m_displayStatusChangedEvent;
    PowerManager::eventType PowerManager::m_systemIdleStatusChangedEvent;
    PowerManager::eventType PowerManager::m_powerSchemePersonalityChangedEvent;
    PowerManager::eventType PowerManager::m_userPresenceStatusChangedEvent;
    PowerManager::eventType PowerManager::m_systemAwayModeStatusChangedEvent;

    EnergySaverStatusRegistration      PowerManager::m_energySaverStatusHandle;
    CompositeBatteryStatusRegistration PowerManager::m_batteryStatusHandle;
    DischargeTimeRegistration          PowerManager::m_dischargeTimeHandle;
    PowerConditionRegistration         PowerManager::m_powerConditionHandle;
    DisplayStatusRegistration          PowerManager::m_displayStatusHandle;
    SystemIdleStatusRegistration       PowerManager::m_systemIdleStatusHandle;
    PowerSchemePersonalityRegistration PowerManager::m_powerSchemePersonalityHandle;
    UserPresenceStatusRegistration     PowerManager::m_userPresenceStatusHandle;
    SystemAwayModeStatusRegistration   PowerManager::m_systemAwayModeStatusHandle;

    std::mutex PowerManager::m_mutex;

    int   PowerManager::m_batteryChargePercent, PowerManager::m_oldBatteryChargePercent;
    DWORD PowerManager::m_cachedDisplayStatus;
    DWORD PowerManager::m_cachedUserPresenceStatus;
    DWORD PowerManager::m_cachedSystemAwayModeStatus;
    DWORD PowerManager::m_cachedPowerCondition;
    GUID  PowerManager::m_cachedPowerSchemePersonality;
    ULONGLONG               PowerManager::m_cachedDischargeTime;
    CompositeBatteryStatus *PowerManager::m_cachedCompositeBatteryStatus;
    ::EnergySaverStatus PowerManager::m_cachedEnergySaverStatus;
    winrt::Microsoft::ProjectReunion::BatteryStatus     PowerManager::m_batteryStatus;
    winrt::Microsoft::ProjectReunion::BatteryStatus     PowerManager::m_oldBatteryStatus = winrt::Microsoft::ProjectReunion::BatteryStatus::Uninitialized;
    winrt::Microsoft::ProjectReunion::PowerSupplyStatus PowerManager::m_powerSupplyStatus;
    winrt::Microsoft::ProjectReunion::PowerSupplyStatus PowerManager::m_oldPowerSupplyStatus = winrt::Microsoft::ProjectReunion::PowerSupplyStatus::Uninitialized;


    bool PowerManager::NotAlreadyRegisteredForEvents(PowerManager::eventType eventObj)
    {
        return !eventObj.get();
    }

    PowerManager::eventType PowerManager::GetEventObj(PowerFunction const& fn)
    {
        switch (fn) {
        case EnergySaverStatusFn:      return PowerManager::m_energySaverStatusChangedEvent;
        case BatteryStatusFn:          return PowerManager::m_batteryStatusChangedEvent;
        case PowerSupplyStatusFn:      return PowerManager::m_powerSupplyStatusChangedEvent;
        case RemainingChargePercentFn: return PowerManager::m_remainingChargePercentChangedEvent;
        case RemainingDischargeTimeFn: return PowerManager::m_remainingDischargeTimeChangedEvent;
        case PowerSourceStatusFn:      return PowerManager::m_powerSourceStatusChangedEvent;
        case DisplayStatusFn:          return PowerManager::m_displayStatusChangedEvent;
        case SystemIdleStatusFn:       return PowerManager::m_systemIdleStatusChangedEvent;
        case PowerSchemePersonalityFn: return PowerManager::m_powerSchemePersonalityChangedEvent;
        case UserPresenceStatusFn:     return PowerManager::m_userPresenceStatusChangedEvent;
        case SystemAwayModeStatusFn:   return PowerManager::m_systemAwayModeStatusChangedEvent;
        default: throw E_NOTIMPL;
        }
    }

    EventToken PowerManager::AddCallback(PowerFunction const& fn, PowerEventHandle const& handler)
    {
        auto eventObj = GetEventObj(fn);
        std::scoped_lock<std::mutex> lock(m_mutex);

        //Check prior registrations
        if (NotAlreadyRegisteredForEvents(eventObj))
        {
            RegisterListener(fn);
        }
        eventObj.get().add(handler);
    }

    void PowerManager::RegisterListener(PowerFunction const& fn)
    {
        switch (fn) {        
            case BatteryStatusFn:          
            case PowerSupplyStatusFn:      
            case RemainingChargePercentFn: check_hresult(RegisterCompositeBatteryStatusChangedListener(CompositeBatteryStatusChanged_Callback, &m_batteryStatusHandle)); break;
            case EnergySaverStatusFn:      check_hresult(RegisterEnergySaverStatusChangedListener(EnergySaverStatusChanged_Callback, &m_energySaverStatusHandle)); break;
            case RemainingDischargeTimeFn: check_hresult(RegisterDischargeTimeChangedListener(RemainingDischargeTimeChanged_Callback, &m_dischargeTimeHandle));    break;
            case PowerSourceStatusFn:      check_hresult(RegisterPowerConditionChangedListener(PowerSourceStatusChanged_Callback, &m_powerConditionHandle));       break;
            case DisplayStatusFn:          check_hresult(RegisterDisplayStatusChangedListener(DisplayStatusChanged_Callback, &m_displayStatusHandle));             break;
            case SystemIdleStatusFn:       check_hresult(RegisterSystemIdleStatusChangedListener(SystemIdleStatusChanged_Callback, &m_systemIdleStatusHandle));    break;
            case PowerSchemePersonalityFn: check_hresult(RegisterPowerSchemePersonalityChangedListener(PowerSchemePersonalityChanged_Callback, &m_powerSchemePersonalityHandle)); break;
            case UserPresenceStatusFn:     check_hresult(RegisterUserPresenceStatusChangedListener(UserPresenceStatusChanged_Callback, &m_userPresenceStatusHandle));             break;
            case SystemAwayModeStatusFn:   check_hresult(RegisterSystemAwayModeStatusChangedListener(SystemAwayModeStatusChanged_Callback, &m_systemAwayModeStatusHandle));       break;
            default: throw E_NOTIMPL;
        }
    }

    void PowerManager::UnregisterListener(PowerFunction const& fn)
    {
        switch (fn) {        
            case BatteryStatusFn:          
            case PowerSupplyStatusFn:      
            case RemainingChargePercentFn: check_hresult(UnregisterCompositeBatteryStatusChangedListener(m_batteryStatusHandle)); break;
            case EnergySaverStatusFn:      check_hresult(UnregisterEnergySaverStatusChangedListener(m_energySaverStatusHandle));  break;
            case RemainingDischargeTimeFn: check_hresult(UnregisterDischargeTimeChangedListener(m_dischargeTimeHandle));          break;
            case PowerSourceStatusFn:      check_hresult(UnregisterPowerConditionChangedListener(m_powerConditionHandle));        break;
            case DisplayStatusFn:          check_hresult(UnregisterDisplayStatusChangedListener(m_displayStatusHandle));          break;
            case SystemIdleStatusFn:       check_hresult(UnregisterSystemIdleStatusChangedListener(m_systemIdleStatusHandle));    break;
            case PowerSchemePersonalityFn: check_hresult(UnregisterPowerSchemePersonalityChangedListener(m_powerSchemePersonalityHandle)); break;
            case UserPresenceStatusFn:     check_hresult(UnregisterUserPresenceStatusChangedListener(m_userPresenceStatusHandle));         break;
            case SystemAwayModeStatusFn:   check_hresult(UnregisterSystemAwayModeStatusChangedListener(m_systemAwayModeStatusHandle));     break;
            default: throw E_NOTIMPL;
        }
    }

    void PowerManager::RemoveCallback(PowerFunction const& fn, EventToken const& token)
    {
        auto eventObj = GetEventObj(fn);
        eventObj.get().remove(token);
        std::scoped_lock<std::mutex> lock(m_mutex);
        //Check prior registrations
        if (NotAlreadyRegisteredForEvents(eventObj))
        {
            UnregisterListener(fn);
        }
    }

    void PowerManager::FireEvent(PowerFunction const& fn)
    {
        GetEventObj(fn).get()(nullptr, nullptr);
    }

    //Checks if an event is already registered. If none are, then gets the status and caches it
    void PowerManager::CheckRegistrationAndOrUpdateValue(PowerFunction const& fn)
    {
        auto eventObj = GetEventObj(fn);
        if (NotAlreadyRegisteredForEvents(eventObj))
        {
            switch (fn) {
                case EnergySaverStatusFn:
                    check_hresult(GetEnergySaverStatus(&m_cachedEnergySaverStatus));
                    break;

                case BatteryStatusFn:
                    check_hresult(GetCompositeBatteryStatus(&m_cachedCompositeBatteryStatus));
                    ProcessCompositeBatteryStatus(*m_cachedCompositeBatteryStatus);
                    break;

                case PowerSupplyStatusFn:
                    break;

                case RemainingChargePercentFn:
                    break;

                case RemainingDischargeTimeFn:
                    check_hresult(GetDischargeTime(&m_cachedDischargeTime));
                    break;

                case PowerSourceStatusFn:
                    check_hresult(GetPowerCondition(&m_cachedPowerCondition));
                    break;

                case DisplayStatusFn:
                    check_hresult(GetDisplayStatus(&m_cachedDisplayStatus));
                    break;

                case SystemIdleStatusFn:
                    break;

                case PowerSchemePersonalityFn:
                    check_hresult(GetPowerSchemePersonality(&m_cachedPowerSchemePersonality));
                    break;

                case UserPresenceStatusFn:
                    check_hresult(GetUserPresenceStatus(&m_cachedUserPresenceStatus));
                    break;

                case SystemAwayModeStatusFn:
                    check_hresult(GetSystemAwayModeStatus(&m_cachedSystemAwayModeStatus));
                    break;

                default: throw E_NOTIMPL;
            }
        }

    }

    EnergySaverStatus PowerManager::EnergySaverStatus()
    {
        CheckRegistrationAndOrUpdateValue(EnergySaverStatusFn);
        return static_cast<winrt::Microsoft::ProjectReunion::EnergySaverStatus>(m_cachedEnergySaverStatus);
    }

    EventToken PowerManager::EnergySaverStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(EnergySaverStatusFn, handler);
    }

    void PowerManager::EnergySaverStatusChanged(EventToken const& token)
    {
        RemoveCallback(EnergySaverStatusFn, token);
    }

    void PowerManager::EnergySaverStatusChanged_Callback(::EnergySaverStatus energySaverStatus)
    {
        m_cachedEnergySaverStatus = energySaverStatus;
        FireEvent(EnergySaverStatusFn);
    }

    void PowerManager::ProcessCompositeBatteryStatus(CompositeBatteryStatus const& compositeBatteryStatus)
    {
        //Calculate battery charge
        auto fullChargedCapacity = compositeBatteryStatus.Information.FullChargedCapacity;
        auto remainingCapacity = compositeBatteryStatus.Status.Capacity;
        auto newRemainingChargePercent = static_cast<int>((remainingCapacity * 200) / fullChargedCapacity);
        newRemainingChargePercent += 1;
        newRemainingChargePercent /= 2;
        m_batteryChargePercent = newRemainingChargePercent;

        auto powerState = compositeBatteryStatus.Status.PowerState;

        //Set battery status
        if (compositeBatteryStatus.ActiveBatteryCount == 0)
        {
            m_batteryStatus = BatteryStatus::NotPresent;
        }
        else if ((powerState & BATTERY_DISCHARGING) != FALSE)
        {
            m_batteryStatus = BatteryStatus::Discharging;
        }
        else if ((powerState & BATTERY_CHARGING) != FALSE)
        {
            m_batteryStatus = BatteryStatus::Charging;
        }
        else
        {
            m_batteryStatus = BatteryStatus::Idle;
        }
                
        //Set power supply state
        if ((powerState & BATTERY_POWER_ON_LINE) == FALSE)
        {
            m_powerSupplyStatus = PowerSupplyStatus::NotPresent;
        }
        else if ((powerState & BATTERY_DISCHARGING) != FALSE)
        {
            m_powerSupplyStatus = PowerSupplyStatus::Inadequate;
        }
        else
        {
            m_powerSupplyStatus = PowerSupplyStatus::Adequate;
        }
    }

    void PowerManager::FireCorrespondingBatteryEvent()
    {
        if (m_oldBatteryChargePercent != m_batteryChargePercent)
        {
            m_oldBatteryChargePercent = m_batteryChargePercent;
            FireEvent(RemainingChargePercentFn);
        }

        if (m_oldBatteryStatus != m_batteryStatus)
        {
            m_oldBatteryStatus = m_batteryStatus;
            FireEvent(BatteryStatusFn);
        }

        if (m_oldPowerSupplyStatus != m_powerSupplyStatus)
        {
            m_oldPowerSupplyStatus = m_powerSupplyStatus;
            FireEvent(PowerSupplyStatusFn);
        }
    }

    winrt::Microsoft::ProjectReunion::BatteryStatus PowerManager::BatteryStatus()
    {
        CheckRegistrationAndOrUpdateValue(BatteryStatusFn);
        return m_batteryStatus;        
    }

    EventToken PowerManager::BatteryStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(BatteryStatusFn, handler);
    }

    void PowerManager::BatteryStatusChanged(EventToken const& token)
    {
        RemoveCallback(BatteryStatusFn, token);
    }

    void PowerManager::CompositeBatteryStatusChanged_Callback(CompositeBatteryStatus* compositeBatteryStatus)
    {
        ProcessCompositeBatteryStatus(*compositeBatteryStatus);
        FireCorrespondingBatteryEvent();
    } 

    PowerSupplyStatus PowerManager::PowerSupplyStatus()
    {
        CheckRegistrationAndOrUpdateValue(BatteryStatusFn);
        return m_powerSupplyStatus;
    }

    EventToken PowerManager::PowerSupplyStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(PowerSupplyStatusFn, handler);
    }

    void PowerManager::PowerSupplyStatusChanged(EventToken const& token)
    {
        RemoveCallback(PowerSupplyStatusFn, token);
    }

    int PowerManager::RemainingChargePercent()
    {
        CheckRegistrationAndOrUpdateValue(BatteryStatusFn);
        return m_batteryChargePercent;
    }

    EventToken PowerManager::RemainingChargePercentChanged(PowerEventHandle const& handler)
    {
        return AddCallback(RemainingChargePercentFn, handler);
    }

    void PowerManager::RemainingChargePercentChanged(EventToken const& token)
    {
        RemoveCallback(RemainingChargePercentFn, token);
    }

    Windows::Foundation::TimeSpan PowerManager::RemainingDischargeTime()
    {
        CheckRegistrationAndOrUpdateValue(RemainingDischargeTimeFn);
        return Windows::Foundation::TimeSpan(std::chrono::seconds(m_cachedDischargeTime));
    }

    EventToken PowerManager::RemainingDischargeTimeChanged(PowerEventHandle const& handler)
    {
        return AddCallback(RemainingDischargeTimeFn, handler);
    }

    void PowerManager::RemainingDischargeTimeChanged(EventToken const& token)
    {
        RemoveCallback(RemainingDischargeTimeFn, token);
    }

    void PowerManager::RemainingDischargeTimeChanged_Callback(ULONGLONG dischargeTime)
    {
        m_cachedDischargeTime = dischargeTime;
        FireEvent(RemainingDischargeTimeFn);
    }

    PowerSourceStatus PowerManager::PowerSourceStatus()
    {
        CheckRegistrationAndOrUpdateValue(PowerSourceStatusFn);
        return  static_cast<winrt::Microsoft::ProjectReunion::PowerSourceStatus>(m_cachedPowerCondition);
    }

    EventToken PowerManager::PowerSourceStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(PowerSourceStatusFn, handler);
    }

    void PowerManager::PowerSourceStatusChanged(EventToken const& token)
    {
        RemoveCallback(PowerSourceStatusFn, token);
    }

    void PowerManager::PowerSourceStatusChanged_Callback(DWORD powerCondition)
    {
        m_cachedPowerCondition = powerCondition;
        FireEvent(PowerSourceStatusFn);
    }

    DisplayStatus PowerManager::DisplayStatus()
    {
        CheckRegistrationAndOrUpdateValue(DisplayStatusFn);
        return static_cast<winrt::Microsoft::ProjectReunion::DisplayStatus>(m_cachedDisplayStatus);
    }

    EventToken PowerManager::DisplayStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(DisplayStatusFn, handler);
    }

    void PowerManager::DisplayStatusChanged(EventToken const& token)
    {
        RemoveCallback(DisplayStatusFn, token);
    }

    void PowerManager::DisplayStatusChanged_Callback(DWORD displayStatus)
    {
        m_cachedDisplayStatus = displayStatus;
        FireEvent(DisplayStatusFn);
    }

    SystemIdleStatus PowerManager::SystemIdleStatus()
    {
        //PReview: Should this be the default value?
        return SystemIdleStatus::Busy;
    }

    EventToken PowerManager::SystemIdleStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(SystemIdleStatusFn, handler);
    }

    void PowerManager::SystemIdleStatusChanged(EventToken const& token)
    {
        RemoveCallback(SystemIdleStatusFn, token);
    }

    void PowerManager::SystemIdleStatusChanged_Callback()
    {
        FireEvent(SystemIdleStatusFn);
    }

    PowerSchemePersonality PowerManager::PowerSchemePersonality()
    {
        CheckRegistrationAndOrUpdateValue(PowerSchemePersonalityFn);
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

    EventToken PowerManager::PowerSchemePersonalityChanged(PowerEventHandle const& handler)
    {
        return AddCallback(PowerSchemePersonalityFn, handler);
    }

    void PowerManager::PowerSchemePersonalityChanged(EventToken const& token)
    {
        RemoveCallback(PowerSchemePersonalityFn, token);
    }

    void PowerManager::PowerSchemePersonalityChanged_Callback(GUID powerSchemePersonality)
    {       
        m_cachedPowerSchemePersonality = powerSchemePersonality;
        FireEvent(PowerSchemePersonalityFn);
    }

    UserPresenceStatus PowerManager::UserPresenceStatus()
    {
        CheckRegistrationAndOrUpdateValue(UserPresenceStatusFn);
        return static_cast<winrt::Microsoft::ProjectReunion::UserPresenceStatus>(m_cachedUserPresenceStatus);
    }

    EventToken PowerManager::UserPresenceStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(UserPresenceStatusFn, handler);
    }

    void PowerManager::UserPresenceStatusChanged(EventToken const& token)
    {
        RemoveCallback(UserPresenceStatusFn, token);
    }

    void PowerManager::UserPresenceStatusChanged_Callback(DWORD userPresenceStatus)
    {
        m_cachedUserPresenceStatus = userPresenceStatus;
        FireEvent(UserPresenceStatusFn);
    }

    SystemAwayModeStatus PowerManager::SystemAwayModeStatus()
    {
        CheckRegistrationAndOrUpdateValue(SystemAwayModeStatusFn);
        return static_cast<winrt::Microsoft::ProjectReunion::SystemAwayModeStatus>(m_cachedSystemAwayModeStatus);
    }

    EventToken PowerManager::SystemAwayModeStatusChanged(PowerEventHandle const& handler)
    {
        return AddCallback(SystemAwayModeStatusFn, handler); 
    }

    void PowerManager::SystemAwayModeStatusChanged(EventToken const& token)
    {
        RemoveCallback(SystemAwayModeStatusFn, token);
    }

    void PowerManager::SystemAwayModeStatusChanged_Callback(DWORD systemAwayModeStatus)
    {        
        m_cachedSystemAwayModeStatus = systemAwayModeStatus;
        FireEvent(SystemAwayModeStatusFn);
    }
}
