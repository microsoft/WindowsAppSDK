// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

void MddBootstrap_StopActivity(
    const bool isActivityRunning,
    WindowsAppRuntime::MddBootstrap::Activity::Context& activityContext,
    const wil::FailureInfo& failure)
{
    if (isActivityRunning)
    {
        PCWSTR initializationFrameworkPackageFullName{};
        auto initializationCount{ activityContext.GetInitializeData(initializationFrameworkPackageFullName) };

        if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Initialize)
        {
            activityContext.GetInitializeActivity().StopWithResult(
                failure.hr,
                static_cast<UINT32>(initializationCount),
                static_cast<UINT32>(WindowsAppRuntime::MddBootstrap::Activity::Context::GetIntegrityFlags()),
                initializationFrameworkPackageFullName,
                static_cast<UINT32>(activityContext.GetLastFailure().type),
                activityContext.GetLastFailure().file.c_str(),
                activityContext.GetLastFailure().lineNumber,
                activityContext.GetLastFailure().message.c_str(),
                activityContext.GetLastFailure().module.c_str());
        }
        else if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
        {
            activityContext.GetShutdownActivity().StopWithResult(
                failure.hr,
                static_cast<UINT32>(initializationCount),
                static_cast<UINT32>(activityContext.GetLastFailure().type),
                activityContext.GetLastFailure().file.c_str(),
                activityContext.GetLastFailure().lineNumber,
                activityContext.GetLastFailure().message.c_str(),
                activityContext.GetLastFailure().module.c_str());
        }
    }
}

// Set thread callback for wil error handlers.
// If a process-wide callback is set, then that will also be called after thread callback is called.
bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeBootstrap_TraceLogger::IsEnabled())
    {
        auto& activityContext{ WindowsAppRuntime::MddBootstrap::Activity::Context::Get() };

        auto IsActivityRunning = [&activityContext]()
        {
            if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Initialize)
            {
                return activityContext.GetInitializeActivity().IsRunning();
            }
            else if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
            {
                return activityContext.GetShutdownActivity().IsRunning();
            }
            return false;
        };

        auto isActivityRunning = IsActivityRunning();

        auto GetActivityId = [&activityContext, isActivityRunning]()
        {
            if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Initialize)
            {
                if (isActivityRunning)
                {
                    return activityContext.GetInitializeActivity().Id();
                }
                else
                {
                    return activityContext.GetSavedInitializeActivityId();
                }
            }
            else if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
            {
                if (isActivityRunning)
                {
                    return activityContext.GetShutdownActivity().Id();

                }
                else
                {
                    return activityContext.GetSavedShutdownActivityId();
                }
            }
            return static_cast<const GUID*>(nullptr);
        };

        auto activityId = GetActivityId();

        if (failure.type == wil::FailureType::Log)
        {
            MddBootstrap_WriteEventWithActivity("Log", activityId);
        }
        else if (failure.type == wil::FailureType::Exception)
        {
            // Bootstrap shutdown API is a best effort API. Hence, don't stop bootstrap activity on an Exception
            if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
            {
                MddBootstrap_WriteEventWithActivity("Exception", activityId);
            }
            else
            {
                MddBootstrap_WriteEventWithActivity("Exception", activityId);
                MddBootstrap_StopActivity(isActivityRunning, activityContext, failure);
            }
        }
        else if (failure.type == wil::FailureType::FailFast)
        {
            MddBootstrap_WriteEventWithActivity("FailFast", activityId);
            MddBootstrap_StopActivity(isActivityRunning, activityContext, failure);
        }
        else if (failure.type == wil::FailureType::Return)
        {
            // For the RETURN_ macro that returns from the Bootstrap API, WindowsAppRuntime::MddBootstrap::Activity::Context::
            // m_stopActivityForWilReturnHR need to be set to indicate to this callback that the activity should be stopped.
            // When it is set, stop the activity.
            if (activityContext.ShouldStopActivityForWilReturnHR())
            {
                MddBootstrap_WriteEventWithActivity("Return", activityId);
                MddBootstrap_StopActivity(isActivityRunning, activityContext, failure);
                activityContext.StopActivityForWilReturnHR(false);
            }
            else
            {
                MddBootstrap_WriteEventWithActivity("Return", activityId);
                activityContext.SetLastFailure(failure);
            }
        }
    }

    // Returning true indicates to wil that the error is reported in Telemetry by this callback
    return true;
}

GUID& GetLifetimeActivityId() noexcept
{
    static GUID s_lifetimeActivityId{};
    if (IsEqualGUID(s_lifetimeActivityId, GUID{}))
    {
        std::ignore = CoCreateGuid(&s_lifetimeActivityId);
    }
    return s_lifetimeActivityId;
}
