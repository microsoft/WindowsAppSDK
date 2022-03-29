// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
#define WINDOWSAPPSDK_RELEASE_CHANNEL "-dev"
#endif

#define _GENERIC_PARTB_FIELDS_ENABLED \
            TraceLoggingStruct(4, "COMMON_WINDOWSAPPSDK_PARAMS"), \
            TraceLoggingString(WINDOWSAPPSDK_RELEASE_VERSION, "Version"), \
            TraceLoggingString(WINDOWSAPPSDK_RELEASE_CHANNEL, "WindowsAppSDKChannel"), \
            TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging"), \
            TraceLoggingBool(true, "UTCReplace_AppSessionGuid")

void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept;

class WindowsAppRuntimeInstaller_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntimeInstaller_TraceLogger,
        "Microsoft.WindowsAppRuntimeInstaller",
        // {7028b782-2ccf-5a66-0008-9b040616d425}
        (0x7028b782, 0x2ccf, 0x5a66, 0x00, 0x08, 0x9b, 0x04, 0x06, 0x16, 0xd4, 0x25));

public:

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Install, PDT_ProductAndServicePerformance);
    void StartActivity(PCWSTR args, UINT32 options)
    {
        TraceLoggingClassWriteStart(Install,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(args, "cmdLineArgs"),
            TraceLoggingValue(options, "options"));
    }
    
    void StopWithResult(
        HRESULT hresult,
        UINT32 installStage,
        PCWSTR currentResourceId,
        HRESULT deploymentErrorExtendedHResult,
        PCWSTR deploymentErrorText,
        GUID deploymentErrorActivityId)
    {
        SetStopResult(hresult);

        TraceLoggingClassWriteStop(Install,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(installStage, "FailedInstallStage"),
            TraceLoggingValue(currentResourceId, "CurrentResourceId"),
            TraceLoggingValue(deploymentErrorExtendedHResult, "DeploymentErrorExtendedHResult"),
            TraceLoggingValue(deploymentErrorText, "DeploymentErrorText"),
            TraceLoggingValue(deploymentErrorActivityId, "DeploymentErrorActivityId"));
    }
    END_ACTIVITY_CLASS();
};

#define WindowsAppRuntimeInstaller_TraceLoggingWString(_wstring_, _name_) \
    TraceLoggingCountedWideString(\
    _wstring_.c_str(),\
    static_cast<ULONG>(_wstring_.size()), _name_)

#define WindowsAppRuntimeInstaller_WriteEventWithActivity(_eventname_,...) TraceLoggingWriteActivity(\
    WindowsAppRuntimeInstaller_TraceLogger::Provider(),\
    _eventname_,\
    WindowsAppRuntimeInstaller::InstallActivity::Context::Get().GetActivity().Id(),\
    nullptr,\
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber,"Line"),\
    TraceLoggingValue(failure.pszMessage,"Message"),\
    __VA_ARGS__)
