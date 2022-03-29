// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

extern std::atomic<uint32_t> g_initializationCount{};
static wil::unique_cotaskmem_string g_initializationFrameworkPackageFullName{};


void initializeActivityWilLoggingCallback_LogActivityStopEvent(const std::string failureType, const wil::FailureInfo& failure)
{

    WindowsAppRuntimeBootstrapInitialize_WriteEventWithActivity(*failureType.c_str(),
        _GENERIC_PARTB_FIELDS_ENABLED,
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_CRITICAL_DATA));

    WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity().StopWithResult(
        failure.hr,
        static_cast<UINT32>(g_initializationCount),
        static_cast<UINT16>(WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetDDLMFindMethodUsed()),
        static_cast<PCWSTR>(g_initializationFrameworkPackageFullName.get()));
}

// Set a process-wide callback for wil error handlers. This callback is specific to MddBootstrap initialize
void __stdcall initialize_wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeBootstrap_TraceLogger::IsEnabled())
    {
        auto initializeActivity{ WindowsAppRuntime::MddBootstrap::Activity::Context::Get().GetInitializeActivity() };
        if (initializeActivity.IsRunning())
        {
            if (failure.type == wil::FailureType::Log)
            {
                WindowsAppRuntimeBootstrapInitialize_WriteEventWithActivity("Log");
            }
            else if (failure.type == wil::FailureType::Exception)
            {
                initializeActivityWilLoggingCallback_LogActivityStopEvent("Exception", failure);
            }
            else if (failure.type == wil::FailureType::FailFast)
            {
                initializeActivityWilLoggingCallback_LogActivityStopEvent("FailFast", failure);
            }
        }
    }
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
