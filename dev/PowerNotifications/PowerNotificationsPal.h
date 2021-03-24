// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <poclass.h>

struct CompositeBatteryStatus
{
    BATTERY_INFORMATION Information;
    BATTERY_STATUS Status;
    ULONG ActiveBatteryCount;
};

DECLARE_HANDLE(CompositeBatteryStatusRegistration);
HRESULT GetCompositeBatteryStatus(CompositeBatteryStatus* compositeBatteryStatusOut);
typedef void (*OnCompositeBatteryStatusChanged)(const CompositeBatteryStatus& compositeBatteryStatus);
HRESULT RegisterCompositeBatteryStatusChangedListener(OnCompositeBatteryStatusChanged listener, CompositeBatteryStatusRegistration* registration);
HRESULT UnregisterCompositeBatteryStatusChangedListener(CompositeBatteryStatusRegistration registration);

DECLARE_HANDLE(DischargeTimeRegistration);
HRESULT GetDischargeTime(ULONGLONG* DischargeTimeOut);
typedef void (*OnDischargeTimeChanged)(ULONGLONG DischargeTime);
HRESULT RegisterDischargeTimeChangedListener(OnDischargeTimeChanged listener, DischargeTimeRegistration* registration);
HRESULT UnregisterDischargeTimeChangedListener(DischargeTimeRegistration registration);

// REVIEW: EnergySaverStatus isn't the raw low-level data, unlike other types. Calculating it involves blending 2 separate WNF events (one describes whether EnergySaver is on, and the other describes why).
// Currently plan to keep those details below the closed-source boundary, for simplicity.
enum EnergySaverStatus
{
    Disabled = 0,
    Off,
    On
};

DECLARE_HANDLE(EnergySaverStatusRegistration);
HRESULT GetEnergySaverStatus(EnergySaverStatus* energySaverStatusOut);
typedef void (*OnEnergySaverStatusChanged)(EnergySaverStatus energySaverStatus);
HRESULT RegisterEnergySaverStatusChangedListener(OnEnergySaverStatusChanged listener, EnergySaverStatusRegistration* registration);
HRESULT UnregisterEnergySaverStatusChangedListener(EnergySaverStatusRegistration registration);

// REVIEW: All the data below comes from NtPowerInformation, and the raw ABI of the state we get back from the low-level APIs is described at https://docs.microsoft.com/en-us/windows/win32/power/power-setting-guids.
// We may consider defining proper enums to represent the possible values, instead of "it's a DWORD with these enumerated possible values".

DECLARE_HANDLE(PowerConditionRegistration);
HRESULT GetPowerCondition(DWORD* powerConditionOut);
typedef void (*OnPowerConditionChanged)(DWORD powerCondition);
HRESULT RegisterPowerConditionChangedListener(OnPowerConditionChanged listener, PowerConditionRegistration* registration);
HRESULT UnregisterPowerConditionChangedListener(PowerConditionRegistration registration);

DECLARE_HANDLE(DisplayStatusRegistration);
HRESULT GetDisplayStatus(DWORD* displayStatusOut);
typedef void (*OnDisplayStatusChanged)(DWORD displayStatus);
HRESULT RegisterDisplayStatusChangedListener(OnDisplayStatusChanged listener, DisplayStatusRegistration* registration);
HRESULT UnregisterDisplayStatusChangedListener(DisplayStatusRegistration registration);

DECLARE_HANDLE(SystemIdleStatusRegistration);
typedef void (*OnSystemIdleStatusChanged)();
HRESULT RegisterSystemIdleStatusChangedListener(OnSystemIdleStatusChanged listener, SystemIdleStatusRegistration* registration);
HRESULT UnregisterSystemIdleStatusChangedListener(SystemIdleStatusRegistration registration);

DECLARE_HANDLE(PowerSchemePersonalityRegistration);
HRESULT GetPowerSchemePersonality(GUID* powerSchemePersonalityOut);
typedef void (*OnPowerSchemePersonalityChanged)(GUID powerSchemePersonality);
HRESULT RegisterPowerSchemePersonalityChangedListener(OnPowerSchemePersonalityChanged listener, PowerSchemePersonalityRegistration* registration);
HRESULT UnregisterPowerSchemePersonalityChangedListener(PowerSchemePersonalityRegistration registration);

DECLARE_HANDLE(UserPresenceStatusRegistration);
HRESULT GetUserPresenceStatus(DWORD* userPresenceStatusOut);
typedef void (*OnUserPresenceStatusChanged)(DWORD userPresenceStatus);
HRESULT RegisterUserPresenceStatusChangedListener(OnUserPresenceStatusChanged listener, UserPresenceStatusRegistration* registration);
HRESULT UnregisterUserPresenceStatusChangedListener(UserPresenceStatusRegistration registration);

DECLARE_HANDLE(SystemAwayModeStatusRegistration);
HRESULT GetSystemAwayModeStatus(DWORD* systemAwayModeStatusOut);
typedef void (*OnSystemAwayModeStatusChanged)(DWORD systemAwayModeStatus);
HRESULT RegisterSystemAwayModeStatusChangedListener(OnSystemAwayModeStatusChanged listener, SystemAwayModeStatusRegistration* registration);
HRESULT UnregisterSystemAwayModeStatusChangedListener(SystemAwayModeStatusRegistration registration);
