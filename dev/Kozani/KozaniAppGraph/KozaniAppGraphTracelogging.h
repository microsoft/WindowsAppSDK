// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#incluide "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

namespace Microsoft::Kozani
{
GUID& GetLifetimeActivityId() noexcept;

class AppGraph_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_AppGraph_TraceLogger,
        "Microsoft.Kozani.AppGraph",
        // b4599732-6ae8-402b-9c69-97689105ab0b
        (0xb4599732, 0x6ae8, 0x402b, 0x9c, 0x69, 0x97, 0x68, 0x91, 0x05, 0xab, 0x0b));

public:
};
}

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
