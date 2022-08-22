// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include <WindowsAppRuntimeInsights.h>
#include <NotificationTelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(AppNotificationBuilderTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.AppNotificationBuilderTelemetry",
    // {6f23f3a8-1420-4814-83c7-c752565aad22}
    (0x6f23f3a8, 0x1420, 0x4814, 0x83, 0xc7, 0xc7, 0x52, 0x56, 0x5a, 0xad, 0x22));

class AppNotificationBuilderTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(AppNotificationBuilderTelemetry, AppNotificationBuilderTelemetryProvider);

public:
    DEFINE_EVENT_METHOD(LogBuildNotification)(
        winrt::hresult hr) noexcept try
    {
        if (m_helper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "BuildNotification",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(m_helper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_helper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

private:
    NotificationTelemetryHelper m_helper;
};
