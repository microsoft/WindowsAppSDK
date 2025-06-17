// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

#if __has_include("WindowsAppSDK-VersionInfo.h")
#include "WindowsAppSDK-VersionInfo.h"
#endif

#if defined(__WINDOWSAPPSDK_VERSIONINFO_H__)
#define TOSTRING_HELPER(x) #x
#define TOSTRING(x) TOSTRING_HELPER(x)
#define WINDOWSAPPSDK_RELEASE_VERSION TOSTRING(WINDOWSAPPSDK_RELEASE_MAJOR.WINDOWSAPPSDK_RELEASE_MINOR.WINDOWSAPPSDK_RELEASE_PATCH)
#else
#define WINDOWSAPPSDK_RELEASE_VERSION "0.0.0"
#define WINDOWSAPPSDK_RELEASE_CHANNEL "dev"
#define WINDOWSAPPSDK_RELEASE_CHANNEL_W L"dev"
#endif
_GENERIC_PARTB_FIELDS_ENABLED
#define _GENERIC_PARTB_FIELDS_ENABLED \
            TraceLoggingStruct(4, "COMMON_WINDOWSAPPSDK_PARAMS"), \
            TraceLoggingString(WINDOWSAPPSDK_RELEASE_VERSION, "Version"), \
            TraceLoggingString(WINDOWSAPPSDK_RELEASE_CHANNEL, "WindowsAppSDKChannel"), \
            TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging"), \
            TraceLoggingBool(true, "UTCReplace_AppSessionGuid")

bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept;

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
        PACKAGE_VERSION minVersion,
        UINT32 mddInitializeOptions,
        UINT32 initializationCount)
    {
        // Set lifetime activity Id that helps in corelating all sub-activities/telemetry from a single Mdd Bootstrap lifetime
        SetRelatedActivityId(GetLifetimeActivityId());

        TraceLoggingClassWriteStart(Initialize,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(majorMinorVersion, "majorMinorVersion"),
            TraceLoggingValue(!versionTag ? L"": versionTag, "versionTag"),
            TraceLoggingValue(minVersion.Version, "minVersion"),
            TraceLoggingValue(mddInitializeOptions, "mddInitializeOptions"),
            TraceLoggingValue(initializationCount, "initializationCount"),
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
    }
    void StopWithResult(
        const HRESULT hresult,
        UINT32 initializationCount,
        UINT32 IntegrityFlags,
        PCWSTR resolvedFrameworkPackageFullName,
        UINT32 failureType,
        PCSTR failureFile,
        unsigned int failureLineNumber,
        PCWSTR failureMessage,
        PCSTR failureModule)
    {
        SetStopResult(hresult);

        if (FAILED(hresult))
        {
            TraceLoggingClassWriteStop(Initialize,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingValue(initializationCount, "initializationCount"),
                TraceLoggingValue(IntegrityFlags, "IntegrityFlags"),
                TraceLoggingValue(resolvedFrameworkPackageFullName, "resolvedFrameworkPackageFullName"),
                TraceLoggingValue(failureType, "wilFailureType"),
                TraceLoggingValue(failureFile, "failureFile"),
                TraceLoggingValue(failureLineNumber, "failureLineNumber"),
                TraceLoggingValue(failureMessage, "failureMessage"),
                TraceLoggingValue(failureModule, "failureModule"),
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
        }
        else
        {
            TraceLoggingClassWriteStop(Initialize,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingValue(initializationCount, "initializationCount"),
                TraceLoggingValue(IntegrityFlags, "IntegrityFlags"),
                TraceLoggingValue(resolvedFrameworkPackageFullName, "resolvedFrameworkPackageFullName"),
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
        }
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
            TraceLoggingValue(resolvedFrameworkPackageFullName, "resolvedFrameworkPackageFullName"),
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
    }
    void StopWithResult(
        HRESULT hresult,
        UINT32 initializationCount,
        UINT32 failureType,
        PCSTR failureFile,
        unsigned int failureLineNumber,
        PCWSTR failureMessage,
        PCSTR failureModule)
    {
        SetStopResult(hresult);

        if (FAILED(hresult))
        {
            TraceLoggingClassWriteStop(Shutdown,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingValue(initializationCount, "initializationCount"),
                TraceLoggingValue(failureType, "WilFailureType"),
                TraceLoggingValue(failureFile, "FailureFile"),
                TraceLoggingValue(failureLineNumber, "FailureLineNumber"),
                TraceLoggingValue(failureMessage, "FailureMessage"),
                TraceLoggingValue(failureModule, "FailureModule"),
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
        }
        else
        {
            TraceLoggingClassWriteStop(Shutdown,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingValue(initializationCount, "initializationCount"),
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
        }
    }
    END_ACTIVITY_CLASS();
};

#define MddBootstrap_TraceLoggingWString(_wstring_, _name_) TraceLoggingCountedWideString(_wstring_.c_str(),\
     static_cast<ULONG>(_wstring_.size()), _name_)

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define MddBootstrap_WriteEventWithActivity(_eventname_,_activityId_,...) TraceLoggingWriteActivity(\
        WindowsAppRuntimeBootstrap_TraceLogger::Provider(),\
        _eventname_,\
        _activityId_,\
        nullptr,\
        TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
        TraceLoggingValue(failure.hr, "HResult"),\
        TraceLoggingValue(failure.pszFile, "File"),\
        TraceLoggingValue(failure.uLineNumber,"Line"),\
        TraceLoggingValue(failure.pszModule, "Module"),\
        TraceLoggingValue(failure.pszMessage,"Message"),\
        _GENERIC_PARTB_FIELDS_ENABLED,\
        __VA_ARGS__)
