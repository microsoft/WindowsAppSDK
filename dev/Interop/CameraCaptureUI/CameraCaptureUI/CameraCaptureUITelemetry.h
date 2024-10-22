// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "..\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"
#include <TelemetryHelper.h>

class CameraCaptureUITelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS_WITH_MICROSOFT_TELEMETRY(CameraCaptureUITelemetry, "Microsoft.WindowsAppSDK.CameraCaptureUITelemetry",
        (0x8ab25b76, 0xfe88, 0x4887, 0xb9, 0x08, 0x24, 0xf8, 0xca, 0x38, 0x2b, 0x9d));
    //{ 8ab25b76-fe88-4887-b908-24f8ca382b9d }
public:
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(CaptureInitiated, PDT_ProductAndServicePerformance,
      bool, IsAppPackaged, PCWSTR, AppName, PCWSTR, CaptureMode);

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(CaptureSuccessful, PDT_ProductAndServicePerformance,
        bool, IsAppPackaged, PCWSTR, AppName, PCWSTR, CaptureMode);

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM5(CaptureError, PDT_ProductAndServiceUsage,
        bool, IsAppPackaged, PCWSTR, AppName, PCWSTR, CaptureMode, HRESULT, hResult, PCWSTR, message);
};
