// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

GUID& GetLifetimeActivityId() noexcept;

class WindowsAppRuntimePurojekutoTenpuret_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntimePurojekutoTenpuret_TraceLogger,
        "Microsoft.WindowsAppRuntime.PurojekutoTenpuret",
        // PROVIDER-{00000000-0000-0000-0000-000000000000}
        PROVIDER-(0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00));

public:
};

#define PurojekutoTenpuret_TraceLoggingWString(_wstring_, _name_) TraceLoggingCountedWideString(_wstring_.c_str(),\
     static_cast<ULONG>(_wstring_.size()), _name_)

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define PurojekutoTenpuret_WriteEventWithActivity(_eventname_,_activityId_,...) TraceLoggingWriteActivity(\
        WindowsAppRuntimePurojekutoTenpuret_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _WRITE_FAILURE_INFO,\
        __VA_ARGS__)

#define _WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")
