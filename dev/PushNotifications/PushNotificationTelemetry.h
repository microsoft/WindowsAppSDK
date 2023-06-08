// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>
#include <NotificationTelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.PushNotificationTelemetry",
    // {7c1b07ef-a7c0-56d1-5456-385ebd4412b2}
    (0x7c1b07ef, 0xa7c0, 0x56d1, 0x54, 0x56, 0x38, 0x5e, 0xbd, 0x44, 0x12, 0xb2));


class PushNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationTelemetry, PushNotificationTelemetryProvider);

public:

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(CreateChannelAsync, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper, const winrt::guid& remoteId) noexcept try
    {
        TraceLoggingClassWriteStart(
            CreateChannelAsync,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingGuid(remoteId, "RemoteId"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(CloseChannel, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
    {
        TraceLoggingClassWriteStart(
            CloseChannel,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Register, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
    {
        TraceLoggingClassWriteStart(
            Register,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Unregister, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
    {
        TraceLoggingClassWriteStart(
            Unregister,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(UnregisterAll, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper) noexcept try
    {
        TraceLoggingClassWriteStart(
            UnregisterAll,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(OnRawNotificationReceived, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper, std::wstring const& correlationVector) noexcept try
    {
        TraceLoggingClassWriteStart(
            OnRawNotificationReceived,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(correlationVector.c_str(), "CorrelationVector"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(InvokeAll, PDT_ProductAndServicePerformance);
    DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper, _In_ PCWSTR correlationVector) noexcept try
    {
        TraceLoggingClassWriteStart(
            InvokeAll,
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(correlationVector ? correlationVector : L"", "CorrelationVector"),
            TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
            TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
    }
    CATCH_LOG()
    END_ACTIVITY_CLASS();
};
