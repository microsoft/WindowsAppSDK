// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "..\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"
#include <TelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(StoragePickersTelemetryProvider,
    "Microsoft.WindowsAppSDK.StoragePickersTelemetry",
    // {6ddc5826-bf0a-522e-cc84-0e70eda439ed}
    (0x6ddc5826,0xbf0a,0x522e,0xcc,0x84,0x0e,0x70,0xed,0xa4,0x39,0xed));

class StoragePickersTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(StoragePickersTelemetry, StoragePickersTelemetryProvider);

public:
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(StoragePickersOperation, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(bool isAppPackaged, PCWSTR appName) noexcept try
        {
            TraceLoggingClassWriteStart(
                StoragePickersOperation,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(isAppPackaged, "IsAppPackaged"),
                TraceLoggingWideString(appName, "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};