// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include <wil/resource.h>
#include <wil/result_macros.h>
#include "..\..\dev\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"

enum class InstallStage
{
    None                = 0x0,
    InstallLicense      = 0x1,
    GetPackageProperties= 0x2,
    CreatePackageURI    = 0x3,
    AddPackage          = 0x4,
    RegisterPackage     = 0x5,
    ProvisionPackage    = 0x6,
};

extern InstallStage g_installStage;
extern PWSTR g_currentPackageFullName;
extern HRESULT g_deploymentErrorExtendedHresult;
extern PCWSTR g_deploymentErrorText;
extern GUID g_deploymentErrorActivityId;

void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept;

class WindowsAppRuntimeInstaller_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntimeInstaller_TraceLogger,
        "Microsoft.WindowsAppRuntimeInstaller",
        // {7028b782-2ccf-5a66-0008-9b040616d425}
        (0x7028b782, 0x2ccf, 0x5a66, 0x00, 0x08, 0x9b, 0x04, 0x06, 0x16, 0xd4, 0x25));

public:

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM7(ProvisioningFailed, PDT_ProductAndServicePerformance,
        HRESULT,hr,
        PCWSTR, currentPackageFullName,
        GUID,   g_deploymentErrorActivityId,
        UINT32, installStage,
        UINT32, failureType,
        PCSTR,  fileName,
        UINT32, lineNumber);

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Install, PDT_ProductAndServicePerformance);
    void StartActivity(PCSTR args, UINT32 options)
    {
        TraceLoggingClassWriteStart(Install,
            TraceLoggingValue(args, "cmdLineArgs"),
            TraceLoggingValue(options, "options"));
    }
    void Stop(
        HRESULT hresult,
        UINT32 installStage,
        PCWSTR currentPackageFullName,
        HRESULT deploymentErrorExtendedHResult,
        PCWSTR deploymentErrorText,
        GUID deploymentErrorActivityId)
    {
        TraceLoggingClassWriteStop(Install,
            TraceLoggingValue(hresult, "hresult"),
            TraceLoggingValue(installStage, "installStage"),
            TraceLoggingValue(currentPackageFullName, "currentPackageFullName"),
            TraceLoggingValue(deploymentErrorExtendedHResult, "deploymentErrorExtendedHResult"),
            TraceLoggingValue(deploymentErrorText, "deploymentErrorText"),
            TraceLoggingValue(deploymentErrorActivityId, "deploymentErrorActivityId"));
    }
    END_ACTIVITY_CLASS();
};
extern WindowsAppRuntimeInstaller_TraceLogger::Install activity;
