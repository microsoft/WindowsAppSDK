// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <wil/resource.h>
#include <wil/result_macros.h>
#include <WindowsAppRuntimeInsights.h>

void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept;

class WindowsAppRuntimeDeployment_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntimeDeployment_TraceLogger,
        "Microsoft.WindowsAppRuntime.Deployment",
        // {838d2cc1-0efb-564a-47bf-faba17949992}
        (0x838d2cc1, 0x0efb, 0x564a, 0x47, 0xbf, 0xfa, 0xba, 0x17, 0x94, 0x99, 0x92));

public:

    BEGIN_COMPLIANT_CRITICAL_DATA_ACTIVITY_CLASS(Initialize, PDT_ProductAndServicePerformance);
    void StartActivity(bool forceDeployment, bool isElevated, bool isPackagedProcess, bool isFullTrustPackage, DWORD integrityLevel, bool isRepair)
    {
        // Clear the process-wide callback set in Start
        wil::SetResultLoggingCallback(nullptr);

        // Set a process-wide callback function for WIL to call each time it logs a failure.
        wil::SetResultLoggingCallback(wilResultLoggingCallback);

        TraceLoggingClassWriteStart(Initialize,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(forceDeployment, "forceDeployment"),
            TraceLoggingValue(isElevated, "isElevated"),
            TraceLoggingValue(isPackagedProcess, "isPackagedProcess"),
            TraceLoggingValue(isFullTrustPackage, "isFullTrustPackage"),
            TraceLoggingValue(integrityLevel, "integrityLevel"),
            TraceLoggingValue(isRepair, "isRepairAPI"));
    }
    void StopWithResult(
        HRESULT hresult,
        UINT32 failureType,
        PCSTR failureFile,
        unsigned int failureLineNumber,
        PCWSTR failureMessage,
        PCSTR failureModule,
        UINT32 preInitializeStatus,
        UINT32 installStage,
        PCWSTR currentResourceId,
        HRESULT deploymentErrorExtendedHResult,
        PCWSTR deploymentErrorText,
        GUID deploymentErrorActivityId,
        bool useExistingPackageIfHigherVersion)
    {
        // Set a process-wide callback function for WIL to call each time it logs a failure.
        wil::SetResultLoggingCallback(nullptr);

        SetStopResult(hresult);

        if (FAILED(hresult))
        {
            TraceLoggingClassWriteStop(Initialize,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingValue(failureType, "WilFailureType"),
                TraceLoggingValue(failureFile, "FailureFile"),
                TraceLoggingValue(failureLineNumber, "FailureLineNumber"),
                TraceLoggingValue(failureMessage, "FailureMessage"),
                TraceLoggingValue(failureModule, "FailureModule"),
                TraceLoggingValue(installStage, "FailedInstallStage"),
                TraceLoggingValue(currentResourceId, "CurrentResourceId"),
                TraceLoggingValue(deploymentErrorExtendedHResult, "DeploymentErrorExtendedHResult"),
                TraceLoggingValue(deploymentErrorText, "DeploymentErrorText"),
                TraceLoggingValue(deploymentErrorActivityId, "DeploymentErrorActivityId"),
                TraceLoggingValue(useExistingPackageIfHigherVersion, "useExistingPackageIfHigherVersion"));
        }
        else
        {
            TraceLoggingClassWriteStop(Initialize,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingValue(preInitializeStatus, "preInitializeStatus"));
        }
    }
    END_ACTIVITY_CLASS();
};

#define WindowsAppRuntimeDeployment_TraceLoggingWString(_wstring_, _name_) \
    TraceLoggingCountedWideString(\
    _wstring_.c_str(),\
    static_cast<ULONG>(_wstring_.size()), _name_)

// In the future, if the project includes multiple modules and threads, we could log that data as well from FailureInfo
// In the future and on need basis, we could log call stack as well
#define WindowsAppRuntimeDeployment_WriteEventWithActivity(_eventname_,...) TraceLoggingWriteActivity(\
    WindowsAppRuntimeDeployment_TraceLogger::Provider(),\
    _eventname_,\
    WindowsAppRuntime::Deployment::Activity::Context::Get().GetActivity().Id(),\
    nullptr,\
    TraceLoggingValue(static_cast<uint32_t>(failure.type), "Type"),\
    TraceLoggingValue(failure.hr, "HResult"),\
    TraceLoggingValue(failure.pszFile, "File"),\
    TraceLoggingValue(failure.uLineNumber, "Line"),\
    TraceLoggingValue(failure.pszMessage, "Message"),\
    TraceLoggingValue(failure.pszModule, "Module"),\
    __VA_ARGS__)
