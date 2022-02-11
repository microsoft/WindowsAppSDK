// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "InstallActivityContext.h"

void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeInstaller_TraceLogger::IsEnabled())
    {
        if (InstallActivityContext::Get().GetActivity().IsRunning())
        {
            if (failure.type == wil::FailureType::Log &&
                InstallActivityContext::Get().GetInstallStage() == InstallStage::ProvisionPackage)
            {
                // Failure in Provisioning package are non-blocking and the installer will continue with installation
                // wil failure type of Log indicates intention to just log failure but continue with the installation
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "ProvisioningFailed",
                    WindowsAppRuntimeInstaller_TraceLoggingWString(InstallActivityContext::Get().GetCurrentResourceId(), "currentPackage"),
                    _GENERIC_PARTB_FIELDS_ENABLED, 
                    TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                    TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));
            }
            // Exceptions will be followed by Returns due to try...CATCH_RETURN() usage. Hence, avoid logging twice.
            else if (failure.type != wil::FailureType::Exception)
            {
                InstallActivityContext::Get().SetLastFailure(failure);
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "FailureInfo",
                    TraceLoggingCountedWideString(InstallActivityContext::Get().GetCurrentResourceId().c_str(), static_cast<ULONG>(InstallActivityContext::Get().GetCurrentResourceId().size()), "currentPackage"));
            }
        }
    }
    return;
}
