// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <PowerNotificationsPal.h>


HRESULT GetCompositeBatteryStatus(CompositeBatteryStatus** compositeBatteryStatusOut)
{
    return S_OK;
}

HRESULT RegisterCompositeBatteryStatusChangedListener(OnCompositeBatteryStatusChanged listener, CompositeBatteryStatusRegistration* registration)
{
    return S_OK;
}

HRESULT UnregisterCompositeBatteryStatusChangedListener(CompositeBatteryStatusRegistration registration)
{
    return S_OK;
}

HRESULT GetDischargeTime(ULONGLONG* DischargeTimeOut) {
    *DischargeTimeOut = 7;
    return S_OK;
}
HRESULT RegisterDischargeTimeChangedListener(OnDischargeTimeChanged listener, DischargeTimeRegistration* registration) { return S_OK; }
HRESULT UnregisterDischargeTimeChangedListener(DischargeTimeRegistration registration) { return S_OK; }

HRESULT GetEnergySaverStatus(EnergySaverStatus* energySaverStatusOut) { return S_OK; }
HRESULT RegisterEnergySaverStatusChangedListener(OnEnergySaverStatusChanged listener, EnergySaverStatusRegistration* registration) { return S_OK; }
HRESULT UnregisterEnergySaverStatusChangedListener(EnergySaverStatusRegistration registration) { return S_OK; }

HRESULT GetPowerCondition(DWORD* powerConditionOut) { return S_OK; }
HRESULT RegisterPowerConditionChangedListener(OnPowerConditionChanged listener, PowerConditionRegistration* registration) { return S_OK; }
HRESULT UnregisterPowerConditionChangedListener(PowerConditionRegistration registration) { return S_OK; }

HRESULT GetDisplayStatus(DWORD* displayStatusOut) {
    *displayStatusOut = 5;
    return S_OK;
}
HRESULT RegisterDisplayStatusChangedListener(OnDisplayStatusChanged listener, DisplayStatusRegistration* registration) { return S_OK; }
HRESULT UnregisterDisplayStatusChangedListener(DisplayStatusRegistration registration) { return S_OK; }

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
