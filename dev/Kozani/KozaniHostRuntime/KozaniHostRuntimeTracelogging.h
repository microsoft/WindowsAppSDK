// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

namespace Microsoft::Kozani
{
GUID& GetLifetimeActivityId() noexcept;

class HostRuntime_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_HostRuntime_TraceLogger,
        "Microsoft.Kozani.HostRuntime",
        // 7896ccbc-b8cd-41fe-a506-5f4e7c60a97f
        (0x7896ccbc, 0xb8cd, 0x41fe, 0xa5, 0x06, 0x5f, 0x4e, 0x7c, 0x60, 0xa9, 0x7f));

public:
};
}

#define _MICROSOFT_KOZANI_HOSTRUNTIME_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniHostRuntime_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_HostRuntime_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_HOSTRUNTIME_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
