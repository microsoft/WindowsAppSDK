// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "InstallActivityContext.h"

using namespace WindowsAppRuntimeInstaller::InstallActivity;

// A process-wide callback function for WIL to call each time it logs a failure.
void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeInstaller_TraceLogger::IsEnabled())
    {
        auto& installActivityContext{ WindowsAppRuntimeInstaller::InstallActivity::Context::Get() };

        if (installActivityContext.GetActivity().IsRunning())
        {
            switch (failure.type)
            {
            case wil::FailureType::Log:
            {
                // wil Log failure type indicates intention to just log failure but continue with the installation

                if (installActivityContext.GetInstallStage() == InstallStage::ProvisionPackage)
                {
                    // Failure in Provisioning package are non-blocking and the installer will continue with installation
                    WindowsAppRuntimeInstaller_WriteEventWithActivity(
                        "ProvisioningFailed",
                        WindowsAppRuntimeInstaller_TraceLoggingWString(installActivityContext.GetCurrentResourceId(), "currentPackage"),
                        _GENERIC_PARTB_FIELDS_ENABLED,
                        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                        TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));
                }
                else if (installActivityContext.GetInstallStage() == InstallStage::RestartPushNotificationsLRP)
                {
                    // Failure in restarting PushNotificationsLRP is non-blocking to the installer functionality
                    WindowsAppRuntimeInstaller_WriteEventWithActivity(
                        "RestartPushNotificationsLRPFailed",
                        _GENERIC_PARTB_FIELDS_ENABLED,
                        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                        TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));
                }
                break;
            }
            case wil::FailureType::Exception:
            {
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "Exception",
                    TraceLoggingCountedWideString(
                        installActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(installActivityContext.GetCurrentResourceId().size()), "currentResource"));
                break;
            }
            case wil::FailureType::FailFast:
            {
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "FailFast",
                    TraceLoggingCountedWideString(
                        installActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(installActivityContext.GetCurrentResourceId().size()), "currentResource"));
                break;
            }
            default:
                // Exceptions will be followed by Returns due to try...CATCH_RETURN() usage. Hence, avoid logging twice by ignoring wil::FailureType::Return
                break;
            }
        }
        return;
    }
}
