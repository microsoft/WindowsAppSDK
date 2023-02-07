// Copyright (c) Microsoft Corporation and Contributors.
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

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(BuildNotification, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                BuildNotification,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ButtonToString, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                ButtonToString,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ComboBoxToString, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                ComboBoxToString,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ProgressBarToString, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                ProgressBarToString,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(TextPropertiesToString, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                TextPropertiesToString,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
