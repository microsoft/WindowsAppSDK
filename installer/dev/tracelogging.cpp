// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "tracelogging.h"

void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeInstaller_TraceLogger::IsEnabled())
    {
        if (activity.IsRunning())
        {
            if (failure.type == wil::FailureType::Log &&
                g_installStage == InstallStage::ProvisionPackage)
            {
                // Failure in Provisioning package are non-blocking and the installer will continue with installation
                // wil failure type of Log indicates intention to just log failure but continue with the installation
                WindowsAppRuntimeInstaller_TraceLogger::ProvisioningFailed(
                    failure.hr,
                    g_currentPackageFullName,
                    g_deploymentErrorActivityId,
                    static_cast<UINT32>(g_installStage),
                    static_cast<UINT32>(failure.type),
                    failure.pszFile,
                    failure.uLineNumber);
            }
            else
            {
                WindowsAppRuntimeInstaller_TraceLogger::FallbackTelemetryCallback(false, failure);
            }
        }
    }
    return;
}
