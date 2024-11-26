#pragma once

#include <WindowsAppRuntimeInsights.h>
#include <NotificationTelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(BadgeNotificationTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.BadgeNotificationTelemetry",
    // {c9002a02-1594-50ab-07e1-a1b60403db83}
    (0xc9002a02, 0x1594, 0x50ab, 0x07, 0xe1, 0xa1, 0xb6, 0x04, 0x03, 0xdb, 0x83));

class BadgeNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(BadgeNotificationTelemetry, BadgeNotificationTelemetryProvider);

public:
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(SetBadge, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(
        NotificationTelemetryHelper& notificationTelemetryHelper,
        std::wstring const& appId,
        std::wstring const& payload) noexcept try
    {
        TraceLoggingClassWriteStart(
            SetBadge,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(appId.c_str(), "AppId"),
            TraceLoggingWideString(payload.c_str(), "PayloadSize"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
        END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ClearBadge, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(
        NotificationTelemetryHelper& notificationTelemetryHelper,
        std::wstring const& appId) noexcept try
    {
        TraceLoggingClassWriteStart(
            ClearBadge,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(appId.c_str(), "AppId"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
        END_ACTIVITY_CLASS();
};
