// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

class WindowsAppRuntimeDeploymentAgent_TraceLogger final : public wil::TraceLoggingProvider
{
	IMPLEMENT_TRACELOGGING_CLASS(
		WindowsAppRuntimeDeploymentAgent_TraceLogger,
		"Microsoft.WindowsAppRuntime.DeploymentAgent",
		// {24d30cc4-c994-597a-3a2f-c0653d641b0f}
		(0x24d30cc4, 0xc994, 0x597a, 0x3a, 0x2f, 0xc0, 0x65, 0x3d, 0x64, 0x1b, 0x0f));

public:

    DEFINE_COMPLIANT_CRITICAL_DATA_EVENT_PARAM4(
        Success,
        PDT_ProductAndServicePerformance,
        bool, useExistingPackageIfHigherVersion,
        PCWSTR, path,
        bool, forceDeployment,
        GUID, callerActivityId);

    DEFINE_COMPLIANT_CRITICAL_DATA_EVENT_PARAM1(
        FailedDueToBadArguments,
        PDT_ProductAndServicePerformance,
        UINT32, argsCount);

    DEFINE_COMPLIANT_CRITICAL_DATA_EVENT_PARAM8(
        FailedInDeployment,
        PDT_ProductAndServicePerformance,
        HRESULT, hresult,
        bool, useExistingPackageIfHigherVersion,
        PCWSTR, path,
        bool, forceDeployment,
        GUID, callerActivityId,
        HRESULT, deploymentExtendedError,
        PCWSTR, deploymentErrorMessage,
        GUID, deploymentActivityId);
};
