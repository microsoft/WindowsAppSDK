// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

namespace Microsoft::Kozani
{
GUID& GetLifetimeActivityId() noexcept;

class Manager_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_Manager_TraceLogger,
        "Microsoft.Kozani.Manager",
        // 43d44131-26c8-471e-b9d6-fba649e59cfa
        (0x43d44131, 0x26c8, 0x471e, 0xb9, 0xd6, 0xfb, 0xa6, 0x49, 0xe5, 0x9c, 0xfa));

public:
};
}

#define _MICROSOFT_KOZANI_MANAGER_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniManager_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_Manager_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_MANAGER_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
