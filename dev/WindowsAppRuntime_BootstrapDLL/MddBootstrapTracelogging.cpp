// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

void MddBootstrap_StopActivity(
    const std::string failureType,
    const GUID *activityId,
    const WindowsAppRuntime::MddBootstrap::Activity::Context& activityContext,
    const wil::FailureInfo& failure)
{
    MddBootstrap_WriteEventWithActivity(*failureType.c_str(), activityId);

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
            activityContext.GetLastFailure().lineNumer,
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
            activityContext.GetLastFailure().lineNumer,
            activityContext.GetLastFailure().message.c_str(),
            activityContext.GetLastFailure().module.c_str());
    }
}

// Set thread callback for wil error handlers.
// If a process-wide callback is set, then that will also be called after thread callback is called.
bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeBootstrap_TraceLogger::IsEnabled())
    {
        auto activityIsRunning = []()
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

        if (activityIsRunning())
        {
            auto GetActivityId = []()
            {
                if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetMddBootstrapAPI() ==
                    WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Initialize)
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().Id();
                }
                else if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetMddBootstrapAPI() ==
                    WindowsAppRuntime::MddBootstrap::Activity::MddBootstrapAPI::Shutdown)
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetShutdownActivity().Id();
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
                MddBootstrap_StopActivity("Exception", activityId, WindowsAppRuntime::MddBootstrap::Activity::Context::Get(), failure);
            }
            else if (failure.type == wil::FailureType::FailFast)
            {
                MddBootstrap_StopActivity("FailFast", activityId, WindowsAppRuntime::MddBootstrap::Activity::Context::Get(), failure);
            }
            else if (failure.type == wil::FailureType::Return)
            {
                if (WindowsAppRuntime::MddBootstrap::Activity::Context::Get().ShouldStopActivityForWilReturnHR())
                {
                    MddBootstrap_StopActivity("Return", activityId, WindowsAppRuntime::MddBootstrap::Activity::Context::Get(), failure);
                    WindowsAppRuntime::MddBootstrap::Activity::Context::Get().StopActivityForWilReturnHR(false);
                }
                else
                {
                    MddBootstrap_WriteEventWithActivity("Return", activityId);
                    WindowsAppRuntime::MddBootstrap::Activity::Context::Get().SetLastFailure(failure);
                }
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
