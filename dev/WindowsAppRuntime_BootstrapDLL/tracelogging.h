// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#if defined(_XSTRING_) && defined(_STRSAFE_H_INCLUDED_) && defined(WI_VERIFY)
static std::wstring ConvertPackagVersionToString(PACKAGE_VERSION packageVersion) //uint16_t major, uint16_t minor, uint16_t build, uint16_t revision)
{
    wchar_t formattedVersion[5 + 1 + 5 + 1 + 5 + 1 + 5 + 1]{};  // "12345.12345.12345.12345" + null-terminator
    WI_VERIFY(SUCCEEDED(StringCchPrintfW(formattedVersion, ARRAYSIZE(formattedVersion), L"%hu.%hu.%hu.%hu", packageVersion.Major, packageVersion.Minor, packageVersion.Build, packageVersion.Revision)));
    return std::wstring(formattedVersion);
}
#else
static std::wstring ConvertPackagVersionToString(PACKAGE_VERSION packageVersion) //uint16_t major, uint16_t minor, uint16_t build, uint16_t revision)
{
    std::wstring dummy{ L"0.0.0.0" }; return dummy;
}
#endif

void __stdcall initialize_wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept;

GUID& GetLifetimeActivityId() noexcept;

class WindowsAppRuntimeBootstrap_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntimeBootstrap_TraceLogger,
        "Microsoft.WindowsAppRuntime.MddBootstrap",
        // {d71ecd75-2924-589c-16dd-68208d1b4015}
        (0xd71ecd75, 0x2924, 0x589c, 0x16, 0xdd, 0x68, 0x20, 0x8d, 0x1b, 0x40, 0x15));

public:
    BEGIN_COMPLIANT_CRITICAL_DATA_ACTIVITY_CLASS(Initialize, PDT_ProductAndServicePerformance);
    void StartActivity(
        UINT32 majorMinorVersion,
        PCWSTR versionTag,
        PACKAGE_VERSION &minFrameworkPackageVersion,
        UINT32 initializationCount)
    {
        // First, clear any previously set process-wide callback, because changing the callback pointer
        // from one non-null value directly to another is not allowed.
        wil::SetResultLoggingCallback(nullptr);

        // Set a process-wide callback function for WIL to call each time it logs a failure.
        wil::SetResultLoggingCallback(initialize_wilResultLoggingCallback);

        // Set lifetime activity Id that helps in corelating all sub-activities/telemetry from a single Mdd Bootstrap lifetime
        SetRelatedActivityId(GetLifetimeActivityId());

        TraceLoggingClassWriteStart(Initialize,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(majorMinorVersion, "majorMinorVersion"),
            TraceLoggingValue(!versionTag ? L"": versionTag, "versionTag"),
            TraceLoggingValue(
                ConvertPackagVersionToString(minFrameworkPackageVersion).c_str(),
                "minFrameworkPackageVersion"),
            TraceLoggingValue(initializationCount, "initializationCount"));
    }
    void StopWithResult(
        const HRESULT hresult,
        UINT32 initializationCount,
        UINT16 ddlmFindMethodUsed,
        PCWSTR resolvedFrameworkPackageFullName)
    {
        // Clear the process-wide callback set in Start
        wil::SetResultLoggingCallback(nullptr);

        SetStopResult(hresult);

        TraceLoggingClassWriteStop(Initialize,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(initializationCount, "initializationCount"),
            TraceLoggingValue(ddlmFindMethodUsed, "ddlmFindMethodUsed"),
            TraceLoggingValue(resolvedFrameworkPackageFullName, "resolvedFrameworkPackageFullName"));
    }
    END_ACTIVITY_CLASS();


    BEGIN_COMPLIANT_CRITICAL_DATA_ACTIVITY_CLASS(Shutdown, PDT_ProductAndServicePerformance);
    void StartActivity(
        UINT32 initializationCount,
        PCWSTR resolvedFrameworkPackageFullName)
    {
        // Set lifetime activity Id that helps in corelating all sub-activities/telemetry from a single Mdd Bootstrap lifetime
        SetRelatedActivityId(GetLifetimeActivityId());

        TraceLoggingClassWriteStart(Shutdown,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(initializationCount, "initializationCount"),
            TraceLoggingValue(resolvedFrameworkPackageFullName, "resolvedFrameworkPackageFullName"));
    }
    void StopWithResult(
        HRESULT hr,
        UINT32 majorMinorVersion,
        PCWSTR versionTag,
        //PACKAGE_VERSION& frameworkPackageVersion,
        UINT32 initializationCount)
    {
        SetStopResult(hr);

        TraceLoggingClassWriteStop(Shutdown,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(majorMinorVersion, "majorMinorVersion"),
            TraceLoggingValue(versionTag, "versionTag"),
            //TraceLoggingValue(
               // ConvertPackagVersionToString(frameworkPackageVersion).c_str(),
               // "frameworkPackageVersion"),
            TraceLoggingValue(initializationCount, "initializationCount"));
    }
    END_ACTIVITY_CLASS();
};

#define WindowsAppRuntimeBootstrap_TraceLoggingWString(_wstring_, _name_) TraceLoggingCountedWideString(_wstring_.c_str(),\
     static_cast<ULONG>(_wstring_.size()), _name_)

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define WindowsAppRuntimeBootstrapInitialize_WriteEventWithActivity(_eventname_,...) TraceLoggingWriteActivity(\
        WindowsAppRuntimeBootstrap_TraceLogger::Provider(),\
        _eventname_,\
        WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().Id(),\
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
