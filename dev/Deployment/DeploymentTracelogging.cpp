// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <pch.h>
#include "DeploymentActivityContext.h"
#include <winrt\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h>

using namespace WindowsAppRuntime::Deployment::Activity;

#define DeploymentActivity_ExceptionFailFast_StopWithResult() \
DeploymentActivityContext.GetActivity().StopWithResult( \
    failure.hr,\
    static_cast<UINT32>(failure.type),\
    failure.pszFile,\
    failure.uLineNumber,\
    failure.pszMessage,\
    failure.pszModule,\
    static_cast<UINT32>(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::PackageInstallRequired),\
    static_cast<UINT32>(DeploymentActivityContext.GetInstallStage()),\
    DeploymentActivityContext.GetCurrentResourceId().c_str(),\
    DeploymentActivityContext.GetDeploymentErrorExtendedHResult(),\
    DeploymentActivityContext.GetDeploymentErrorText().c_str(),\
    DeploymentActivityContext.GetDeploymentErrorActivityId())

// A process-wide callback function for WIL Error Handlers
void __stdcall wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeDeployment_TraceLogger::IsEnabled())
    {
        auto& DeploymentActivityContext{ WindowsAppRuntime::Deployment::Activity::Context::Get() };

        if (DeploymentActivityContext.GetActivity().IsRunning())
        {
            switch (failure.type)
            {
            case wil::FailureType::Log:
            {
                if (DeploymentActivityContext.GetInstallStage() == DeploymentStage::RestartPushNotificationsLRP)
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
                    WindowsAppRuntimeDeployment_WriteEventWithActivity("FailureLog");
                }
                break;
            }
            case wil::FailureType::Exception:
            {
                WindowsAppRuntimeDeployment_WriteEventWithActivity(
                    "Exception",
                    TraceLoggingCountedWideString(
                        DeploymentActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(DeploymentActivityContext.GetCurrentResourceId().size()), "currentResource"));

                DeploymentActivity_ExceptionFailFast_StopWithResult();
                break;
            }
            case wil::FailureType::FailFast:
            {
                WindowsAppRuntimeDeployment_WriteEventWithActivity(
                    "FailFast",
                    TraceLoggingCountedWideString(
                        DeploymentActivityContext.GetCurrentResourceId().c_str(),
                        static_cast<ULONG>(DeploymentActivityContext.GetCurrentResourceId().size()), "currentResource"));

                DeploymentActivity_ExceptionFailFast_StopWithResult();
                break;
            }
            case wil::FailureType::Return:
            {
                // THROW_*** error handling combined with CATCH_RETURN in the code may log the same failure twice.
                // That's ok and we can live with that redundancy but don't want to lose failure info from RETURN_*** wil macros.
                WindowsAppRuntimeDeployment_WriteEventWithActivity("FailureReturn");

                // Don't stop the Deployment activity here. Instead, give the failing API a chance to Stop the Activity before returning error to the caller.
                // Hence, save the wil failure info here for later use.
                DeploymentActivityContext.SetLastFailure(failure);

                break;
            }
            default:
                break;
            }
        }
        return;
    }
}
