// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <unordered_map>
#include <PowerManager.g.h>
#include <PowerNotificationsPal.h>

using namespace std;
using index = ULONGLONG;
index g_idx;

unordered_map<index, OnCompositeBatteryStatusChanged> onCompositeBatteryStatusChanged_callbacks;
unordered_map<index, OnDisplayStatusChanged> onDisplayStatusChanged_callbacks;

HRESULT GetCompositeBatteryStatus(CompositeBatteryStatus** compositeBatteryStatusOut)
{
    *compositeBatteryStatusOut = NULL;
    auto status = wil::make_unique_cotaskmem<CompositeBatteryStatus>();
    status.get()->ActiveBatteryCount = 1;
    status.get()->Status.PowerState |= BATTERY_DISCHARGING;
    status.get()->Status.PowerState |= BATTERY_POWER_ON_LINE;
    status.get()->Information.FullChargedCapacity = 100;
    status.get()->Status.Capacity = 77;
    *compositeBatteryStatusOut = status.release();
    return S_OK;
}

HRESULT RegisterCompositeBatteryStatusChangedListener(OnCompositeBatteryStatusChanged listener, CompositeBatteryStatusRegistration* registration)
{
    *registration = reinterpret_cast<CompositeBatteryStatusRegistration>(g_idx++);
    onCompositeBatteryStatusChanged_callbacks[g_idx] = listener;
    //This is resulting in abort by te.process.exe during test runs, event without sleep
//  std::thread thread([]() {
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
//        for (const auto& [key, callbackFn] : onCompositeBatteryStatusChanged_callbacks)
//        {
//            callbackFn();
//        }            
//  });
    return S_OK;
}

HRESULT UnregisterCompositeBatteryStatusChangedListener(CompositeBatteryStatusRegistration registration)
{
    onCompositeBatteryStatusChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT GetDischargeTime(ULONGLONG* DischargeTimeOut) { return S_OK; }
HRESULT RegisterDischargeTimeChangedListener(OnDischargeTimeChanged listener, DischargeTimeRegistration* registration) { return S_OK; }
HRESULT UnregisterDischargeTimeChangedListener(DischargeTimeRegistration registration) { return S_OK; }

HRESULT GetEnergySaverStatus(EnergySaverStatus* energySaverStatusOut) { return S_OK; }
HRESULT RegisterEnergySaverStatusChangedListener(OnEnergySaverStatusChanged listener, EnergySaverStatusRegistration* registration) { return S_OK; }
HRESULT UnregisterEnergySaverStatusChangedListener(EnergySaverStatusRegistration registration) { return S_OK; }

HRESULT GetPowerCondition(DWORD* powerConditionOut) { return S_OK; }
HRESULT RegisterPowerConditionChangedListener(OnPowerConditionChanged listener, PowerConditionRegistration* registration) { return S_OK; }
HRESULT UnregisterPowerConditionChangedListener(PowerConditionRegistration registration) { return S_OK; }

HRESULT GetDisplayStatus(DWORD* displayStatusOut)
{
    *displayStatusOut = static_cast<DWORD>(winrt::Microsoft::ProjectReunion::DisplayStatus::Dimmed);
    return S_OK;
}

HRESULT RegisterDisplayStatusChangedListener(OnDisplayStatusChanged listener, DisplayStatusRegistration* registration)
{
    *registration = reinterpret_cast<DisplayStatusRegistration>(g_idx++);
    onDisplayStatusChanged_callbacks[g_idx] = listener;

    //std::thread thread([]() {
    //        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //        for (const auto& [key, callbackFn] : onDisplayStatusChanged_callbacks)
    //        {
    //            callbackFn(static_cast<DWORD>(winrt::Microsoft::ProjectReunion::DisplayStatus::On));
    //        }            
    // });

    return S_OK;
}

HRESULT UnregisterDisplayStatusChangedListener(DisplayStatusRegistration registration)
{
    onDisplayStatusChanged_callbacks.erase(reinterpret_cast<index>(registration));
    return S_OK;
}

HRESULT RegisterSystemIdleStatusChangedListener(OnSystemIdleStatusChanged listener, SystemIdleStatusRegistration* registration) { return S_OK; }
HRESULT UnregisterSystemIdleStatusChangedListener(SystemIdleStatusRegistration registration) { return S_OK; }

HRESULT GetPowerSchemePersonality(GUID* powerSchemePersonalityOut) { return S_OK; }
HRESULT RegisterPowerSchemePersonalityChangedListener(OnPowerSchemePersonalityChanged listener, PowerSchemePersonalityRegistration* registration) { return S_OK; }
HRESULT UnregisterPowerSchemePersonalityChangedListener(PowerSchemePersonalityRegistration registration) { return S_OK; }

HRESULT GetUserPresenceStatus(DWORD* userPresenceStatusOut) { return S_OK; }
HRESULT RegisterUserPresenceStatusChangedListener(OnUserPresenceStatusChanged listener, UserPresenceStatusRegistration* registration) { return S_OK; }
HRESULT UnregisterUserPresenceStatusChangedListener(UserPresenceStatusRegistration registration) { return S_OK; }

HRESULT GetSystemAwayModeStatus(DWORD* systemAwayModeStatusOut) { return S_OK; }
HRESULT RegisterSystemAwayModeStatusChangedListener(OnSystemAwayModeStatusChanged listener, SystemAwayModeStatusRegistration* registration) { return S_OK; }
HRESULT UnregisterSystemAwayModeStatusChangedListener(SystemAwayModeStatusRegistration registration) { return S_OK; }
