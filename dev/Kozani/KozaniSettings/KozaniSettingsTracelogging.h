// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

namespace Microsoft::Kozani
{
GUID& GetLifetimeActivityId() noexcept;

class Settings_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_Settings_TraceLogger,
        "Microsoft.Kozani.Settings",
        // 98c3ec79-97b4-48f0-9df4-b5282c0c5a94
        (0x98c3ec79, 0x97b4, 0x48f0, 0x9d, 0xf4, 0xb5, 0x28, 0x2c, 0x0c, 0x5a, 0x94));

public:
};
}

#define _MICROSOFT_KOZANI_SETTINGS_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniSettings_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_Settings_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_SETTINGS_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
