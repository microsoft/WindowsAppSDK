// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "..\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"
#include <TelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(CameraCaptureUITelemetryProvider,
    "Microsoft.WindowsAppSDK.CameraCaptureUITelemetry",
    // {8ab25b76-fe88-4887-b908-24f8ca382b9d}
    (0x8ab25b76, 0xfe88, 0x4887, 0xb9, 0x08, 0x24, 0xf8, 0xca, 0x38, 0x2b, 0x9d));

class CameraCaptureUITelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(CameraCaptureUITelemetry, CameraCaptureUITelemetryProvider);

public:
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(CameraCaptureOperation, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(bool isAppPackaged, PCWSTR appName, PCWSTR captureMode) noexcept try
        {
            TraceLoggingClassWriteStart(
                CameraCaptureOperation,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(isAppPackaged, "IsAppPackaged"),
                TraceLoggingWideString(appName, "AppName"),
                TraceLoggingWideString(captureMode, "CaptureMode"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
