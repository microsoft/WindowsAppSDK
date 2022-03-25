// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "tracelogging.h"
#include "BootstrapActivity.h"

extern PACKAGE_VERSION g_initializationFrameworkPackageVersion{};
extern std::atomic<uint32_t> g_initializationCount{};
extern UINT32 g_initializationMajorMinorVersion{};
std::wstring g_initializationVersionTag;

void __stdcall initialize_wilResultLoggingCallback(const wil::FailureInfo& failure) noexcept
{
    if (WindowsAppRuntimeBootStrap_TraceLogger::IsEnabled())
    {
        auto initializeActivity{ WindowsAppRuntime::Bootstrap::Activity::Context::Get().GetInitializeActivity() };
        if (initializeActivity.IsRunning())
        {
            if (failure.type == wil::FailureType::Log)
            {
                WindowsAppRuntimeBootStrapInitialize_WriteEventWithActivity("Log");
            }
            else if (failure.type == wil::FailureType::Exception)
            {
                WindowsAppRuntimeBootStrapInitialize_WriteEventWithActivity("Exception",
                    _GENERIC_PARTB_FIELDS_ENABLED,
                    TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                    TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));

                initializeActivity.StopWithResult(
                    failure.hr,
                    g_initializationMajorMinorVersion,
                    g_initializationVersionTag.c_str(),
                    g_initializationFrameworkPackageVersion,
                    static_cast<UINT32>(g_initializationCount));
            }
            else if (failure.type == wil::FailureType::FailFast)
            {
                WindowsAppRuntimeBootStrapInitialize_WriteEventWithActivity("FailFast",
                    _GENERIC_PARTB_FIELDS_ENABLED,
                    TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                    TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));

                initializeActivity.StopWithResult(
                    failure.hr,
                    g_initializationMajorMinorVersion,
                    g_initializationVersionTag.c_str(),
                    g_initializationFrameworkPackageVersion,
                    static_cast<UINT32>(g_initializationCount));
            }
            else
            {
                // BootStrap uses CATCH_RETURN and hence, there is no need to log anything for wil::FailureType::Return to avoid redundanct logging.
            }
        }
    }
    return;
}
