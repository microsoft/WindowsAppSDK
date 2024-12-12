// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "..\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"
#include <TelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(StoragePickersTelemetryProvider,
    "Microsoft.WindowsAppSDK.StoragePickersTelemetry",
    // {3be0d45f-3a9d-46be-a1cf-b08465473cc4}
    (0x3be0d45f, 0x3a9d, 0x46be, 0xa1, 0xcf, 0xb0, 0x84, 0x65, 0x47, 0x3c, 0xc4));

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