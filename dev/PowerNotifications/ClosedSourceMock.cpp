// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// This is a temporary test file, which is only in place until the actual cross - binary ABI is available for mocking
// This will not and should not be checked into main

#include <pch.h>
#include <unordered_map>
#include <PowerManager.g.h>
#include <PowerNotificationsPal.h>

using namespace std;
using index = ULONGLONG;
index g_idx;

unordered_map<index, OnCompositeBatteryStatusChanged> onCompositeBatteryStatusChanged_callbacks;
unordered_map<index, OnDischargeTimeChanged> onDischargeTimeChanged_callbacks;
unordered_map<index, OnEnergySaverStatusChanged> onEnergySaverStatusChanged_callbacks;
unordered_map<index, OnPowerConditionChanged> onPowerConditionChanged_callbacks;
unordered_map<index, OnDisplayStatusChanged> onDisplayStatusChanged_callbacks;
unordered_map<index, OnSystemIdleStatusChanged> onSystemIdleStatusChanged_callbacks;
unordered_map<index, OnPowerSchemePersonalityChanged> onPowerSchemePersonalityChanged_callbacks;
unordered_map<index, OnUserPresenceStatusChanged> onUserPresenceStatusChanged_callbacks;
unordered_map<index, OnSystemAwayModeStatusChanged> onSystemAwayModeStatusChanged_callbacks;

HRESULT GetCompositeBatteryStatus(CompositeBatteryStatus* status)
{
    status->ActiveBatteryCount = 1;
    status->Status.PowerState |= BATTERY_DISCHARGING;
    status->Status.PowerState |= BATTERY_POWER_ON_LINE;
    status->Information.FullChargedCapacity = 100;
    status->Status.Capacity = 77;
    return S_OK;
}

HRESULT RegisterCompositeBatteryStatusChangedListener(OnCompositeBatteryStatusChanged listener, CompositeBatteryStatusRegistration* registration)
{
    *registration = reinterpret_cast<CompositeBatteryStatusRegistration>(g_idx++);
    onCompositeBatteryStatusChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (const auto& [key, callbackFn] : onCompositeBatteryStatusChanged_callbacks)
        {
            CompositeBatteryStatus status;
            status.ActiveBatteryCount = 1;
            status.Status.PowerState |= BATTERY_CHARGING;
            status.Status.PowerState |= BATTERY_POWER_ON_LINE;
            status.Information.FullChargedCapacity = 100;
            status.Status.Capacity = 57;
            callbackFn(status);
        }
    });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterCompositeBatteryStatusChangedListener(CompositeBatteryStatusRegistration registration)
{
    onCompositeBatteryStatusChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT GetDischargeTime(ULONGLONG* dischargeTimeOut)
{
    *dischargeTimeOut = 3;
    return S_OK;
}

HRESULT RegisterDischargeTimeChangedListener(OnDischargeTimeChanged listener, DischargeTimeRegistration* registration)
{
    *registration = reinterpret_cast<DischargeTimeRegistration>(g_idx++);
    onDischargeTimeChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (const auto& [key, callbackFn] : onDischargeTimeChanged_callbacks)
        {
            callbackFn(5);
        }
    });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterDischargeTimeChangedListener(DischargeTimeRegistration registration)
{
    onDischargeTimeChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT GetEnergySaverStatus(EnergySaverStatus* energySaverStatusOut)
{
    *energySaverStatusOut = EnergySaverStatus::On;
    return S_OK;
}

HRESULT RegisterEnergySaverStatusChangedListener(OnEnergySaverStatusChanged listener, EnergySaverStatusRegistration* registration)
{
    *registration = reinterpret_cast<EnergySaverStatusRegistration>(g_idx++);
    onEnergySaverStatusChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (const auto& [key, callbackFn] : onEnergySaverStatusChanged_callbacks)
        {
            callbackFn(EnergySaverStatus::Off);
        }
    });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterEnergySaverStatusChangedListener(EnergySaverStatusRegistration registration)
{
    onEnergySaverStatusChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT GetPowerCondition(DWORD* powerConditionOut)
{
    *powerConditionOut = static_cast<DWORD>(winrt::Microsoft::ProjectReunion::PowerSourceStatus::AC);
    return S_OK;
}

HRESULT RegisterPowerConditionChangedListener(OnPowerConditionChanged listener, PowerConditionRegistration* registration)
{
    *registration = reinterpret_cast<PowerConditionRegistration>(g_idx++);
    onPowerConditionChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (const auto& [key, callbackFn] : onPowerConditionChanged_callbacks)
        {
            callbackFn(static_cast<DWORD>(winrt::Microsoft::ProjectReunion::PowerSourceStatus::DC));
        }
    });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterPowerConditionChangedListener(PowerConditionRegistration registration)
{
    onPowerConditionChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT GetDisplayStatus(DWORD* displayStatusOut)
{
    *displayStatusOut = static_cast<DWORD>(winrt::Microsoft::ProjectReunion::DisplayStatus::Dimmed);
    return S_OK;
}

HRESULT RegisterDisplayStatusChangedListener(OnDisplayStatusChanged listener, DisplayStatusRegistration* registration)
{
    *registration = reinterpret_cast<DisplayStatusRegistration>(g_idx++);
    onDisplayStatusChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            for (const auto& [key, callbackFn] : onDisplayStatusChanged_callbacks)
            {
                callbackFn(static_cast<DWORD>(winrt::Microsoft::ProjectReunion::DisplayStatus::On));
            }
     });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterDisplayStatusChangedListener(DisplayStatusRegistration registration)
{
    onDisplayStatusChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT RegisterSystemIdleStatusChangedListener(OnSystemIdleStatusChanged listener, SystemIdleStatusRegistration* registration)
{
    *registration = reinterpret_cast<SystemIdleStatusRegistration>(g_idx++);
    onSystemIdleStatusChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (const auto& [key, callbackFn] : onSystemIdleStatusChanged_callbacks)
        {
            callbackFn();
        }
    });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterSystemIdleStatusChangedListener(SystemIdleStatusRegistration registration)
{
    onSystemIdleStatusChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT GetPowerSchemePersonality(GUID* powerSchemePersonalityOut)
{
    *powerSchemePersonalityOut = GUID_MIN_POWER_SAVINGS;
    return S_OK;
}

HRESULT RegisterPowerSchemePersonalityChangedListener(OnPowerSchemePersonalityChanged listener, PowerSchemePersonalityRegistration* registration)
{
    *registration = reinterpret_cast<PowerSchemePersonalityRegistration>(g_idx++);
    onPowerSchemePersonalityChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (const auto& [key, callbackFn] : onPowerSchemePersonalityChanged_callbacks)
        {
            callbackFn(GUID_MAX_POWER_SAVINGS);
        }
    });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterPowerSchemePersonalityChangedListener(PowerSchemePersonalityRegistration registration)
{
    onPowerSchemePersonalityChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT GetUserPresenceStatus(DWORD* userPresenceStatusOut)
{
    *userPresenceStatusOut = static_cast<DWORD>(winrt::Microsoft::ProjectReunion::UserPresenceStatus::Present);
    return S_OK;
}

HRESULT RegisterUserPresenceStatusChangedListener(OnUserPresenceStatusChanged listener, UserPresenceStatusRegistration* registration)
{
    *registration = reinterpret_cast<UserPresenceStatusRegistration>(g_idx++);
    onUserPresenceStatusChanged_callbacks[g_idx] = listener;
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (const auto& [key, callbackFn] : onUserPresenceStatusChanged_callbacks)
        {
            callbackFn(static_cast<DWORD>(winrt::Microsoft::ProjectReunion::UserPresenceStatus::Absent));
        }
        });
    thread.detach();
    return S_OK;
}

HRESULT UnregisterUserPresenceStatusChangedListener(UserPresenceStatusRegistration registration)
{
    onUserPresenceStatusChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}
