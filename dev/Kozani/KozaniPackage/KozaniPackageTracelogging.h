// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

GUID& GetLifetimeActivityId() noexcept;

class WindowsAppRuntimeKozaniPackage_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntimeKozaniPackage_TraceLogger,
        "Microsoft.WindowsAppRuntime.KozaniPackage",
        // {75f3d43c-eca9-420b-8600-320ad7e8cc97}
        (0x75f3d43c, 0xeca9, 0x420b, 0x86, 0x00, 0x32, 0x0a, 0xd7, 0xe8, 0xcc, 0x97));

public:
};

#define KozaniPackage_TraceLoggingWString(_wstring_, _name_) TraceLoggingCountedWideString(_wstring_.c_str(),\
     static_cast<ULONG>(_wstring_.size()), _name_)

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define KozaniPackage_WriteEventWithActivity(_eventname_,_activityId_,...) TraceLoggingWriteActivity(\
        WindowsAppRuntimeKozaniPackage_TraceLogger::Provider(),\
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

