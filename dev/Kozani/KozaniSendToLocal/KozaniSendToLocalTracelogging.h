// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#include "Microsoft.TraceLogging.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

namespace Microsoft::Kozani
{
GUID& GetLifetimeActivityId() noexcept;

class SendToLocal_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        Microsoft_Kozani_SendToLocal_TraceLogger,
        "Microsoft.Kozani.SendToLocal",
        // 47202135-35d6-4636-beba-8be8819519c8
        (0x47202135, 0x35d6, 0x4636, 0xbe, 0xba, 0x8b, 0xe8, 0x81, 0x95, 0x19, 0xc8));

public:
};
}

#define _MICROSOFT_KOZANI_SENDTOLOCAL_WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    TraceLoggingValue(failure.pszMessage,"Message")

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniSendToLocal_WriteEventWithActivity(_eventname_,_activityId_,...) \
    TraceLoggingWriteActivity(\
        Microsoft_Kozani_SendToLocal_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        _MICROSOFT_KOZANI_SENDTOLOCAL_WRITE_FAILURE_INFO,\
        __VA_ARGS__)
