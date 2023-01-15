// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include <WindowsAppRuntimeInsights.h>

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

//namespace Microsoft::Kozani
//{
GUID& GetLifetimeActivityId() noexcept;

class Microsoft_Kozani_RemoteManager_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_RemoteManager_TraceLogger,
        "Microsoft.Kozani.RemoteManager",
        // 7b5cabb7-8c65-4315-afad-be1d9810d1e2
        (0x7b5cabb7, 0x8c65, 0x4315, 0xaf, 0xad, 0xbe, 0x1d, 0x98, 0x10, 0xd1, 0xe2));

public:
};
//}

#define _MICROSOFT_KOZANI_REMOTEMANAGER_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniRemoteManager_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_RemoteManager_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_REMOTEMANAGER_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
