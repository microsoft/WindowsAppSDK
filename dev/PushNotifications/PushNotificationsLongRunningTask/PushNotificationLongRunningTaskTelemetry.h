// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationLongRunningTaskTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.PushNotificationLongRunningTaskTelemetry",
    // {76c12936-0ba7-46ba-be2b-ce492e4bcf01}
    (0x76c12936, 0x0ba7, 0x46ba, 0xbe, 0x2b, 0xce, 0x49, 0x2e, 0x4b, 0xcf, 0x01));

class PushNotificationLongRunningTaskTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationLongRunningTaskTelemetry, PushNotificationLongRunningTaskTelemetryProvider);

public:
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(OnRawNotificationReceived, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(_In_ HSTRING correlationVector) noexcept try
    {
        TraceLoggingClassWriteMeasure(
            "OnRawNotificationReceived",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(wil::str_raw_ptr(correlationVector), "CorrelationVector"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();

};
