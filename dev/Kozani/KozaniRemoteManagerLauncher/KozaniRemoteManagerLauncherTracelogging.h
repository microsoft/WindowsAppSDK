// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

GUID& GetLifetimeActivityId() noexcept;

class Microsoft_Kozani_RemoteManagerLauncher_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_RemoteManagerLauncher_TraceLogger,
        "Microsoft.Kozani.RemoteManagerLauncher",
        // 66e9cc70-6a58-48f6-831f-521204545ede
        (0x66e9cc70, 0x6a58, 0x48f6, 0x83, 0x1f, 0x52, 0x12, 0x04, 0x54, 0x5e, 0xde));

public:
};

#define _MICROSOFT_KOZANI_REMOTEMANAGERLAUNCHER_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniRemoteManagerLauncher_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_RemoteManagerLauncher_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_REMOTEMANAGERLAUNCHER_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
