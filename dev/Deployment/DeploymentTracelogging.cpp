// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <pch.h>
#include "DeploymentActivityContext.h"
#include <winrt\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h>

using namespace WindowsAppRuntime::Deployment::Activity;

// A process-wide callback function for WIL Error Handlers
void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeDeployment_TraceLogger::IsEnabled())
    {
        auto& deploymentActivityContext{ WindowsAppRuntime::Deployment::Activity::Context::Get() };

        if (deploymentActivityContext.GetActivity().IsRunning())
        {
            switch (failure.type)
            {
            case wil::FailureType::Log:
            {
                if (deploymentActivityContext.GetInstallStage() == DeploymentStage::RestartPushNotificationsLRP)
                {
                    // Failure in restarting PushNotificationsLRP is non-blocking to the installer functionality
                    WindowsAppRuntimeDeployment_WriteEventWithActivity(
                        "RestartPushNotificationsLRPFailed",
                        _GENERIC_PARTB_FIELDS_ENABLED,
                        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                        TraceLoggingKeyword(MICROSOFT_KEYWORD_CRITICAL_DATA));
                }
                else
                {
                    WindowsAppRuntimeDeployment_WriteEventWithActivity("FailureLog",
                        TraceLoggingCountedWideString(
                            deploymentActivityContext.GetCurrentResourceId().c_str(),
                            static_cast<ULONG>(deploymentActivityContext.GetCurrentResourceId().size()), "currentResource"));
                }
                break;
            }
            case wil::FailureType::Exception:
            {
                WindowsAppRuntimeDeployment_WriteEventWithActivity(
                    "Exception",
                    TraceLoggingCountedWideString(
                        deploymentActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(deploymentActivityContext.GetCurrentResourceId().size()), "currentResource"));

                // Don't stop the Deployment activity here. Instead, give the failing API a chance to Stop the Activity before returning error to the caller.
                // Hence, save the wil failure info here for later use.
                deploymentActivityContext.SetLastFailure(failure);
                break;
            }
            case wil::FailureType::FailFast:
            {
                WindowsAppRuntimeDeployment_WriteEventWithActivity(
                    "FailFast",
                    TraceLoggingCountedWideString(
                        deploymentActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(deploymentActivityContext.GetCurrentResourceId().size()), "currentResource"));

                deploymentActivityContext.GetActivity().StopWithResult(
                    failure.hr,
                    static_cast<UINT32>(failure.type),
                    failure.pszFile,
                    failure.uLineNumber,
                    failure.pszMessage,
                    failure.pszModule,
                    static_cast<UINT32>(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::PackageInstallRequired),
                    static_cast<UINT32>(deploymentActivityContext.GetInstallStage()),
                    deploymentActivityContext.GetCurrentResourceId().c_str(),
                    deploymentActivityContext.GetDeploymentErrorExtendedHResult(),
                    deploymentActivityContext.GetDeploymentErrorText().c_str(),
                    deploymentActivityContext.GetDeploymentErrorActivityId(),
                    deploymentActivityContext.GetIsFullTrustPackage());
                break;
            }
            case wil::FailureType::Return:
            {
                // THROW_*** error handling combined with CATCH_RETURN in the code may log the same failure twice.
                // That's ok and we can live with that redundancy but don't want to lose failure info from RETURN_*** wil macros.
                WindowsAppRuntimeDeployment_WriteEventWithActivity(
                    "FailureReturn",
                    TraceLoggingCountedWideString(
                        deploymentActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(deploymentActivityContext.GetCurrentResourceId().size()), "currentResource"));

                // If this is due to CATCH_RETURN(), we want to keep the failure info from THROW* and not overwrite that from RETURN*
                if (!(deploymentActivityContext.GetLastFailure().type == wil::FailureType::Exception &&
                    FAILED(deploymentActivityContext.GetLastFailure().hr)))
                {
                    // Don't stop the Deployment activity here. Instead, give the Installer main a chance to Stop the Activity before returning error to the caller.
                    // Hence, save the wil failure info here for later use.
                    deploymentActivityContext.SetLastFailure(failure);
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
