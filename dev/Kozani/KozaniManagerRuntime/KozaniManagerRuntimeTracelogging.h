// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

GUID& GetLifetimeActivityId() noexcept;

class Microsoft_Kozani_ManagerRuntime_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_ManagerRuntime_TraceLogger,
        "Microsoft.Kozani.ManagerRuntime",
        // 24ccf6d3-5878-4a9f-82e3-fadbac2515e7
        (0x24ccf6d3, 0x5878, 0x4a9f, 0x82, 0xe3, 0xfa, 0xdb, 0xac, 0x25, 0x15, 0xe7));

public:
};

#define _MICROSOFT_KOZANI_MANAGERRUNTIME_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniManagerRuntime_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_ManagerRuntime_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_MANAGERRUNTIME_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
