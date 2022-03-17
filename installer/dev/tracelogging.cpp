// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "InstallActivityContext.h"

using namespace WindowsAppRuntimeInstaller::InstallActivity;

void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeInstaller_TraceLogger::IsEnabled())
    {
        auto& installActivityContext{ WindowsAppRuntimeInstaller::InstallActivity::Context::Get() };

        if (installActivityContext.GetActivity().IsRunning())
        {
            if (failure.type == wil::FailureType::Log &&
                installActivityContext.GetInstallStage() == InstallStage::ProvisionPackage)
            {
                // Failure in Provisioning package are non-blocking and the installer will continue with installation
                // wil failure type of Log indicates intention to just log failure but continue with the installation
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "ProvisioningFailed",
                    WindowsAppRuntimeInstaller_TraceLoggingWString(installActivityContext.GetCurrentResourceId(), "currentPackage"),
                    _GENERIC_PARTB_FIELDS_ENABLED, 
                    TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                    TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));
            }
            // Exceptions will be followed by Returns due to try...CATCH_RETURN() usage. Hence, avoid logging twice.
            else if (failure.type != wil::FailureType::Exception)
            {
                installActivityContext.SetLastFailure(failure);
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "FailureInfo",
                    TraceLoggingCountedWideString(installActivityContext.GetCurrentResourceId().c_str(), static_cast<ULONG>(installActivityContext.GetCurrentResourceId().size()), "currentPackage"));
            }
        }
    }
    return;
}
