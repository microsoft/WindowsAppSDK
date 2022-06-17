// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

void MddBootstrap_StopActivity(
    const std::string failureType,
    const bool isActivityRunning,
    const GUID *activityId,
    const WindowsAppRuntime::MddBootstrap::Activity::Context& activityContext,
    const wil::FailureInfo& failure)
{
    MddBootstrap_WriteEventWithActivity(*failureType.c_str(), activityId);

    if (isActivityRunning)
    {
        PWSTR initializationFrameworkPackageFullName{};
        auto initializationCount{ WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeData(initializationFrameworkPackageFullName) };

        if (activityContext.GetMddBootstrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Initialize)
        {
            WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().StopWithResult(
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
            WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetShutdownActivity().StopWithResult(
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
        auto IsActivityRunning = []()
        {
            if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetMddBootstrapAPI() ==
                WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Initialize)
            {
                return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().IsRunning();
            }
            else if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetMddBootstrapAPI() ==
                WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
            {
                return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetShutdownActivity().IsRunning();
            }
            return false;
        };

        auto isActivityRunning = IsActivityRunning();

        auto GetActivityId = [isActivityRunning]()
        {
            if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetMddBootstrapAPI() ==
                WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Initialize)
            {
                if (isActivityRunning)
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().Id();
                }
                else
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetSavedInitializeActivityId();
                }
            }
            else if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetMddBootstrapAPI() ==
                WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
            {
                if (isActivityRunning)
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetShutdownActivity().Id();

                }
                else
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetSavedShutdownActivityId();
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
            if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetMddBootstrapAPI() ==
                WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
            {
                MddBootstrap_WriteEventWithActivity("Exception", activityId);
            }
            else
            {
                MddBootstrap_StopActivity("Exception", isActivityRunning, activityId, WindowsAppRuntime::MddBootstrap::Activity::Context::Get(), failure);
            }
        }
        else if (failure.type == wil::FailureType::FailFast)
        {
            MddBootstrap_StopActivity("FailFast", isActivityRunning, activityId, WindowsAppRuntime::MddBootstrap::Activity::Context::Get(), failure);
        }
        else if (failure.type == wil::FailureType::Return)
        {
            // For the RETURN_ macro that returns from the Bootstrap API, WindowsAppRuntime::MddBootstrap::Activity::Context::
            // m_stopActivityForWilReturnHR need to be set to indicate to this callback that the activity should be stopped.
            // When it is set, stop the activity.
            if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().ShouldStopActivityForWilReturnHR())
            {
                MddBootstrap_StopActivity("Return", isActivityRunning, activityId, WindowsAppRuntime::MddBootstrap::Activity::Context::Get(), failure);
                WindowsAppRuntime::MddBootstrap::Activity::Context::Get().StopActivityForWilReturnHR(false);
            }
            else
            {
                MddBootstrap_WriteEventWithActivity("Return", activityId);
                WindowsAppRuntime::MddBootstrap::Activity::Context::Get().SetLastFailure(failure);
            }
        }
    }
    // Returning true indicates to wil that the error is reported in Telemetry by this callback.
    return true;
}

GUID& GetLifetimeActivityId() noexcept
{
    static GUID lifetimeActivityId{};

    if (IsEqualGUID(lifetimeActivityId, GUID_NULL))
    {
        std::ignore = CoCreateGuid(&lifetimeActivityId);
    }

    return lifetimeActivityId;
}
