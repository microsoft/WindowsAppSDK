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
        // f10daf50-e063-47ac-a2f5-74e1003478d7
        (0xf10daf50, 0xe063, 0x47ac, 0xa2, 0xf5, 0x74, 0xe1, 0x00, 0x34, 0x78, 0xd7));

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
