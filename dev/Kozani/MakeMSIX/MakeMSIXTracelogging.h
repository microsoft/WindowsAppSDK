// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

GUID& GetLifetimeActivityId() noexcept;

class Microsoft_Kozani_MakeMSIX_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_MakeMSIX_TraceLogger,
        "Microsoft.Kozani.MakeMSIX",
        // aadd42f7-8804-4986-82da-c7517747634e
        (0xaadd42f7, 0x8804, 0x4986, 0x82, 0xda, 0xc7, 0x51, 0x77, 0x47, 0x63, 0x4e));

public:
};

#define _MICROSOFT_KOZANI_MAKEMSIX_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define MakeMSIX_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_MakeMSIX_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_MAKEMSIX_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
