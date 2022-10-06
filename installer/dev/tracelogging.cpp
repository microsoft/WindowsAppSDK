// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "InstallActivityContext.h"

using namespace WindowsAppRuntimeInstaller::InstallActivity;

// A process-wide callback function for WIL Error Handlers
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
                        TraceLoggingKeyword(MICROSOFT_KEYWORD_CRITICAL_DATA));
                }
                else if (installActivityContext.GetInstallStage() == InstallStage::RestartPushNotificationsLRP)
                {
                    // Failure in restarting PushNotificationsLRP is non-blocking to the installer functionality
                    WindowsAppRuntimeInstaller_WriteEventWithActivity(
                        "RestartPushNotificationsLRPFailed",
                        _GENERIC_PARTB_FIELDS_ENABLED,
                        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                        TraceLoggingKeyword(MICROSOFT_KEYWORD_CRITICAL_DATA));
                }
                else
                {
                    WindowsAppRuntimeInstaller_WriteEventWithActivity("FailureLog");
                }
                installActivityContext.LogInstallerFailureEvent(failure.hr);
                break;
            }
            case wil::FailureType::Exception:
            {
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "Exception",
                    TraceLoggingCountedWideString(
                        installActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(installActivityContext.GetCurrentResourceId().size()), "currentResource"));

                // Don't stop the Install activity here. Instead, give the Installer main a chance to Stop the Activity before returning error to the caller.
                // Hence, save the wil failure info here for later use.
                installActivityContext.SetLastFailure(failure);
                break;
            }
            case wil::FailureType::FailFast:
            {
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "FailFast",
                    TraceLoggingCountedWideString(
                        installActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(installActivityContext.GetCurrentResourceId().size()), "currentResource"));

                installActivityContext.GetActivity().StopWithResult(
                    failure.hr,
                    static_cast<UINT32>(failure.type),
                    failure.pszFile,
                    failure.uLineNumber,
                    failure.pszMessage,
                    static_cast<UINT32>(installActivityContext.GetInstallStage()),
                    installActivityContext.GetCurrentResourceId().c_str(),
                    installActivityContext.GetDeploymentErrorHresult(),
                    installActivityContext.GetDeploymentErrorText().c_str(),
                    installActivityContext.GetDeploymentErrorActivityId(),
                    installActivityContext.GetExistingPackageIfHigherVersion().c_str());

                installActivityContext.LogInstallerFailureEvent(failure.hr);
                break;
            }
            case wil::FailureType::Return:
            {
                WindowsAppRuntimeInstaller_WriteEventWithActivity(
                    "FailureReturn",
                    TraceLoggingCountedWideString(
                        installActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(installActivityContext.GetCurrentResourceId().size()), "currentResource"));

                // If this is due to CATCH_RETURN(), we want to keep the failure info from THROW* and not overwrite that from RETURN*
                if (!(installActivityContext.GetLastFailure().type == wil::FailureType::Exception &&
                    FAILED(installActivityContext.GetLastFailure().hr)))
                {
                    // Don't stop the Install activity here. Instead, give the Installer main a chance to Stop the Activity before returning error to the caller.
                    // Hence, save the wil failure info here for later use.
                    installActivityContext.SetLastFailure(failure);
                }
                break;
            }
            default:
                break;
            }
        }
        return;
    }
}
