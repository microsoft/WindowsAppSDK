// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

GUID& GetLifetimeActivityId() noexcept;

class Microsoft_Kozani_AppGraph_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_AppGraph_TraceLogger,
        "Microsoft.Kozani.AppGraph",
        // 6b731824-91e7-47ae-ae99-e9dd6c6379dc
        (0x6b731824, 0x91e7, 0x47ae, 0xae, 0x99, 0xe9, 0xdd, 0x6c, 0x63, 0x79, 0xdc));

public:
};

#define _MICROSOFT_KOZANI_APPGRAPH_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniAppGraph_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_AppGraph_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_APPGRAPH_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
