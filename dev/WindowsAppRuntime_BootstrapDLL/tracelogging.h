// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include <WindowsAppRuntimeInsights.h>

#if defined(_XSTRING_) && defined(_STRSAFE_H_INCLUDED_) && defined(WI_VERIFY)
static std::wstring ConvertPackagVersionToString(PACKAGE_VERSION packageVersion) //uint16_t major, uint16_t minor, uint16_t build, uint16_t revision)
{
    wchar_t formattedVersion[5 + 1 + 5 + 1 + 5 + 1 + 5 + 1]{};  // "12345.12345.12345.12345" + null-terminator
    WI_VERIFY(SUCCEEDED(StringCchPrintfW(formattedVersion, ARRAYSIZE(formattedVersion), L"%hu.%hu.%hu.%hu", packageVersion.Major, packageVersion.Minor, packageVersion.Build, packageVersion.Revision)));
    return std::wstring(formattedVersion);
}
#endif

#define _WRITE_FAILURE_INFO \
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszMessage,"Message")

void __stdcall initialize_wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept;

class WindowsAppRuntimeBootStrap_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntimeBootStrap_TraceLogger,
        "Microsoft.WindowsAppRuntime.Bootstrap",
        // {2fe5b24f-404b-52d8-52c1-8cf409c5e43f}
        (0x2fe5b24f, 0x404b, 0x52d8, 0x52, 0xc1, 0x8c, 0xf4, 0x09, 0xc5, 0xe4, 0x3f));

public:
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Initialize, PDT_ProductAndServicePerformance);
    void StartActivity(
        UINT32 majorMinorVersion,
        PCWSTR versionTag,
        PACKAGE_VERSION &requestedMinFrameworkPackageVersion,
        UINT32 initializationCount)
    {
        // First, clear any previously set process-wide callback, because changing the callback pointer
        // from one non-null value directly to another is not allowed.
        wil::SetResultLoggingCallback(nullptr);

        // Set a process-wide callback function for WIL to call each time it logs a failure.
        wil::SetResultLoggingCallback(initialize_wilResultLoggingCallback);

        TraceLoggingClassWriteStart(Initialize,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(majorMinorVersion, "majorMinorVersion"),
            TraceLoggingValue(versionTag, "majorMinorVersion"),
            TraceLoggingValue(
                ConvertPackagVersionToString(requestedMinFrameworkPackageVersion).c_str(),
                "requestedMinFrameworkPackageVersion"),
            TraceLoggingValue(initializationCount, "initializationCount"));
    }
    void StopWithResult(
        HRESULT hresult,
        UINT32 majorMinorVersion,
        PCWSTR versionTag,
        PACKAGE_VERSION &resolvedMinFrameworkPackageVersion,
        UINT32 initializationCount)
    {
        SetStopResult(hresult);

        wil::FailureInfo* pFailure{};
        if (pFailure)
        {
            wil::FailureInfo& failure{ *pFailure };
            TraceLoggingClassWriteStop(Initialize,
                _GENERIC_PARTB_FIELDS_ENABLED,
                _WRITE_FAILURE_INFO,
                TraceLoggingValue(
                    ConvertPackagVersionToString(resolvedMinFrameworkPackageVersion).c_str(),
                    "requestedMinFrameworkPackageVersion"),
                TraceLoggingValue(initializationCount, "initializationCount"));
        }
        else
        {
            wil::FailureInfo failure{};
            TraceLoggingClassWriteStop(Initialize,
                _GENERIC_PARTB_FIELDS_ENABLED,
                _WRITE_FAILURE_INFO,
                TraceLoggingValue(
                    ConvertPackagVersionToString(resolvedMinFrameworkPackageVersion).c_str(),
                    "requestedMinFrameworkPackageVersion"),
                TraceLoggingValue(initializationCount, "initializationCount"));
        }
    }
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Shutdown, PDT_ProductAndServicePerformance);
    void StartActivity(
        UINT32 initializationCount)
    {
        TraceLoggingClassWriteStart(Shutdown,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(initializationCount, "initializationCount"));
    }
    void StopWithResult(
        HRESULT hr,
        UINT32 majorMinorVersion,
        PCWSTR versionTag,
        PACKAGE_VERSION& frameworkPackageVersion,
        UINT32 initializationCount)
    {
        SetStopResult(hr);

        TraceLoggingClassWriteStop(Shutdown,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(majorMinorVersion, "majorMinorVersion"),
            TraceLoggingValue(versionTag, "versionTag"),
            TraceLoggingValue(
                ConvertPackagVersionToString(frameworkPackageVersion).c_str(),
                "frameworkPackageVersion"),
            TraceLoggingValue(initializationCount, "initializationCount"));

        // Being a good citizen and clearing the previously set process-wide callback in the Start method of this Shutdown Activity.
        wil::SetResultLoggingCallback(nullptr);
    }
    END_ACTIVITY_CLASS();
};

#define WindowsAppRuntimeBootStrap_TraceLoggingWString(_wstring_, _name_) TraceLoggingCountedWideString(_wstring_.c_str(),static_cast<ULONG>(_wstring_.size()), _name_)

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define WindowsAppRuntimeBootStrapInitialize_WriteEventWithActivity(_eventname_,...) TraceLoggingWriteActivity(\
    WindowsAppRuntimeBootStrap_TraceLogger::Provider(),\
    _eventname_,\
    WindowsAppRuntime::Bootstrap::Activity::Context::Get().GetInitializeActivity().Id(),\
    nullptr,\
    _WRITE_FAILURE_INFO,\
    __VA_ARGS__)
