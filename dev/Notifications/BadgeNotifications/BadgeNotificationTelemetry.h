// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

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
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(SetBadgeAsCount, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(
        NotificationTelemetryHelper& notificationTelemetryHelper,
        std::wstring const& appId) noexcept try
    {
        TraceLoggingClassWriteStart(
            SetBadgeAsCount,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(appId.c_str(), "AppId"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
        END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(SetBadgeAsCountWithExpiration, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(
        NotificationTelemetryHelper& notificationTelemetryHelper,
        std::wstring const& appId) noexcept try
    {
        TraceLoggingClassWriteStart(
            SetBadgeAsCountWithExpiration,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(appId.c_str(), "AppId"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
        END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(SetBadgeAsGlyph, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(
        NotificationTelemetryHelper& notificationTelemetryHelper,
        std::wstring const& appId) noexcept try
    {
        TraceLoggingClassWriteStart(
            SetBadgeAsGlyph,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(appId.c_str(), "AppId"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
        END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(SetBadgeAsGlyphWithExpiration, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(
        NotificationTelemetryHelper& notificationTelemetryHelper,
        std::wstring const& appId) noexcept try
    {
        TraceLoggingClassWriteStart(
            SetBadgeAsGlyphWithExpiration,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(appId.c_str(), "AppId"),
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
