// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

extern std::atomic<uint32_t> g_initializationCount{};
static wil::unique_cotaskmem_string g_initializationFrameworkPackageFullName{};


void MddBootstrap_StopActivity(
    const std::string failureType,
    const GUID *activityId,
    const WindowsAppRuntime::MddBootstrap::Activity::Context& activityContext,
    const wil::FailureInfo& failure)
{
    MddBootstrap_WriteEventWithActivity(*failureType.c_str(), activityId);

    if (activityContext.GetMddBootStrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootStrapAPI::Initialize)
    {
        WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().StopWithResult(
            failure.hr,
            static_cast<UINT32>(g_initializationCount),
            static_cast<UINT16>(WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetDDLMFindMethodUsed()),
            static_cast<PCWSTR>(g_initializationFrameworkPackageFullName.get()),
            static_cast<UINT32>(activityContext.GetLastFailure().type),
            activityContext.GetLastFailure().file.c_str(),
            activityContext.GetLastFailure().lineNumer,
            activityContext.GetLastFailure().message.c_str(),
            activityContext.GetLastFailure().module.c_str());

    }
    else if (activityContext.GetMddBootStrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootStrapAPI::Shutdown)
    {
        WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetShutdownActivity().StopWithResult(
            failure.hr,
            static_cast<UINT32>(g_initializationCount),
            static_cast<UINT32>(activityContext.GetLastFailure().type),
            activityContext.GetLastFailure().file.c_str(),
            activityContext.GetLastFailure().lineNumer,
            activityContext.GetLastFailure().message.c_str(),
            activityContext.GetLastFailure().module.c_str());
    }
}

// Set a process-wide callback for wil error handlers. This callback is specific to MddBootstrap initialize
bool __stdcall wilResultLoggingThreadCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeBootstrap_TraceLogger::IsEnabled())
    {
        auto activityContext { WindowsAppRuntime::MddBootstrap::Activity::Context::Get() };

        auto activityIsRunning = [](WindowsAppRuntime::MddBootstrap::Activity::Context& activityContext)
        {
            if (activityContext.GetMddBootStrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootStrapAPI::Initialize)
            {
                return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().IsRunning();
            }
            else if (activityContext.GetMddBootStrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootStrapAPI::Shutdown)
            {
                return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetShutdownActivity().IsRunning();
            }
        };

        if (activityIsRunning(activityContext))
        {
            auto GetActivityId = [](WindowsAppRuntime::MddBootstrap::Activity::Context& activityContext)
            {
                if (activityContext.GetMddBootStrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootStrapAPI::Initialize)
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().Id();
                }
                else if (activityContext.GetMddBootStrapAPI() == WindowsAppRuntime::MddBootstrap::Activity::MddBootStrapAPI::Shutdown)
                {
                    return WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetShutdownActivity().Id();
                }
            };

            auto activityId = GetActivityId(activityContext);

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
                MddBootstrap_WriteEventWithActivity("Return", activityId);

                WindowsAppRuntime::MddBootstrap::Activity::Context::Get().SetLastFailure(failure);
            }
        }
    }
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
