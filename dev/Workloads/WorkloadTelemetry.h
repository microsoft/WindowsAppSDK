// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(WorkloadTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.WorkloadTelemetry",
    // {a7dba7ed-49f0-4e6d-9019-4e3f2ed782d3}
    (0xa7dba7ed, 0x49f0, 0x4e6d, 0x90, 0x19, 0x4e, 0x3f, 0x2e, 0xd7, 0x82, 0xd3));

class WorkloadTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(WorkloadTelemetry, WorkloadTelemetryProvider);

public:

    DEFINE_COMPLIANT_MEASURES_EVENT(FindIds, PDT_ProductAndServiceUsage);
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(GetWorkload, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& id) noexcept try
        {
            TraceLoggingClassWriteStart(
                GetWorkload,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(id.c_str(), "Id"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemoveWorkloadAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& id, winrt::hstring const& activatableClassId) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemoveWorkloadAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(id.c_str(), "Id"),
                TraceLoggingWideString(activatableClassId.c_str(), "Handler.ActivatableClassId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemoveWorkloadAsync_Handler, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& id, winrt::hstring const& activatableClassId) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemoveWorkloadAsync_Handler,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(id.c_str(), "Id"),
                TraceLoggingWideString(activatableClassId.c_str(), "Handler.ActivatableClassId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
