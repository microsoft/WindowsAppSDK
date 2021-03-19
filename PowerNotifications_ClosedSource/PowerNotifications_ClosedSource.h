// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <Windows.h>
#include <poclass.h>

#pragma once

#ifdef POWERNOTIFICATIONS_CLOSEDSOURCE_EXPORTS
#define PAL_API __declspec(dllexport)
#else
#define PAL_API __declspec(dllimport)
#endif


struct CompositeBatteryStatus
{
    BATTERY_INFORMATION Information;
    BATTERY_STATUS Status;
    ULONG ActiveBatteryCount;
};

//extern "C" PAL_API

DECLARE_HANDLE(CompositeBatteryStatusRegistration);
extern "C" PAL_API HRESULT GetCompositeBatteryStatus(CompositeBatteryStatus * *compositeBatteryStatusOut);
typedef void (*OnCompositeBatteryStatusChanged)(CompositeBatteryStatus* compositeBatteryStatus);
extern "C" PAL_API HRESULT RegisterCompositeBatteryStatusChangedListener(OnCompositeBatteryStatusChanged listener, CompositeBatteryStatusRegistration * registration);
extern "C" PAL_API HRESULT UnregisterCompositeBatteryStatusChangedListener(CompositeBatteryStatusRegistration registration);

DECLARE_HANDLE(DischargeTimeRegistration);
extern "C" PAL_API HRESULT GetDischargeTime(ULONGLONG * DischargeTimeOut);
typedef void (*OnDischargeTimeChanged)(ULONGLONG DischargeTime);
extern "C" PAL_API HRESULT RegisterDischargeTimeChangedListener(OnDischargeTimeChanged listener, DischargeTimeRegistration * registration);
extern "C" PAL_API HRESULT UnregisterDischargeTimeChangedListener(DischargeTimeRegistration registration);

// REVIEW: EnergySaverStatus isn't the raw low-level data, unlike other types. Calculating it involves blending 2 separate WNF events (one describes whether EnergySaver is on, and the other describes why).
// Currently plan to keep those details below the closed-source boundary, for simplicity.
enum EnergySaverStatus
{
    Disabled = 0,
    Off,
    On
};

DECLARE_HANDLE(EnergySaverStatusRegistration);
extern "C" PAL_API HRESULT GetEnergySaverStatus(EnergySaverStatus * energySaverStatusOut);
typedef void (*OnEnergySaverStatusChanged)(EnergySaverStatus energySaverStatus);
extern "C" PAL_API HRESULT RegisterEnergySaverStatusChangedListener(OnEnergySaverStatusChanged listener, EnergySaverStatusRegistration * registration);
extern "C" PAL_API HRESULT UnregisterEnergySaverStatusChangedListener(EnergySaverStatusRegistration registration);

// REVIEW: All the data below comes from NtPowerInformation, and the raw ABI of the state we get back from the low-level APIs is described at https://docs.microsoft.com/en-us/windows/win32/power/power-setting-guids.
// We may consider defining proper enums to represent the possible values, instead of "it's a DWORD with these enumerated possible values".

DECLARE_HANDLE(PowerConditionRegistration);
extern "C" PAL_API HRESULT GetPowerCondition(DWORD * powerConditionOut);
typedef void (*OnPowerConditionChanged)(DWORD powerCondition);
extern "C" PAL_API HRESULT RegisterPowerConditionChangedListener(OnPowerConditionChanged listener, PowerConditionRegistration * registration);
extern "C" PAL_API HRESULT UnregisterPowerConditionChangedListener(PowerConditionRegistration registration);

DECLARE_HANDLE(DisplayStatusRegistration);
extern "C" PAL_API HRESULT GetDisplayStatus(DWORD * displayStatusOut);
typedef void (*OnDisplayStatusChanged)(DWORD displayStatus);
extern "C" PAL_API HRESULT RegisterDisplayStatusChangedListener(OnDisplayStatusChanged listener, DisplayStatusRegistration * registration);
extern "C" PAL_API HRESULT UnregisterDisplayStatusChangedListener(DisplayStatusRegistration registration);

DECLARE_HANDLE(SystemIdleStatusRegistration);
typedef void (*OnSystemIdleStatusChanged)();
extern "C" PAL_API HRESULT RegisterSystemIdleStatusChangedListener(OnSystemIdleStatusChanged listener, SystemIdleStatusRegistration * registration);
extern "C" PAL_API HRESULT UnregisterSystemIdleStatusChangedListener(SystemIdleStatusRegistration registration);

DECLARE_HANDLE(PowerSchemePersonalityRegistration);
extern "C" PAL_API HRESULT GetPowerSchemePersonality(GUID * powerSchemePersonalityOut);
typedef void (*OnPowerSchemePersonalityChanged)(GUID powerSchemePersonality);
extern "C" PAL_API HRESULT RegisterPowerSchemePersonalityChangedListener(OnPowerSchemePersonalityChanged listener, PowerSchemePersonalityRegistration * registration);
extern "C" PAL_API HRESULT UnregisterPowerSchemePersonalityChangedListener(PowerSchemePersonalityRegistration registration);

DECLARE_HANDLE(UserPresenceStatusRegistration);
extern "C" PAL_API HRESULT GetUserPresenceStatus(DWORD * userPresenceStatusOut);
typedef void (*OnUserPresenceStatusChanged)(DWORD userPresenceStatus);
extern "C" PAL_API HRESULT RegisterUserPresenceStatusChangedListener(OnUserPresenceStatusChanged listener, UserPresenceStatusRegistration * registration);
extern "C" PAL_API HRESULT UnregisterUserPresenceStatusChangedListener(UserPresenceStatusRegistration registration);

DECLARE_HANDLE(SystemAwayModeStatusRegistration);
extern "C" PAL_API HRESULT GetSystemAwayModeStatus(DWORD * systemAwayModeStatusOut);
typedef void (*OnSystemAwayModeStatusChanged)(DWORD systemAwayModeStatus);
extern "C" PAL_API HRESULT RegisterSystemAwayModeStatusChangedListener(OnSystemAwayModeStatusChanged listener, SystemAwayModeStatusRegistration * registration);
extern "C" PAL_API HRESULT UnregisterSystemAwayModeStatusChangedListener(SystemAwayModeStatusRegistration registration);
