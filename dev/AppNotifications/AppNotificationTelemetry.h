// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>
#include <NotificationTelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(AppNotificationTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.AppNotificationTelemetry",
    // {1825c850-a487-537d-b768-f0ab298d2565}
    (0x1825c850, 0xa487, 0x537d, 0xb7, 0x68, 0xf0, 0xab, 0x29, 0x8d, 0x25, 0x65));

class AppNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(AppNotificationTelemetry, AppNotificationTelemetryProvider);

public:

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Register, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper, std::wstring const& appId) noexcept try
        {
            TraceLoggingClassWriteStart(
                Register,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Unregister, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper, std::wstring const& appId) noexcept try
        {
            TraceLoggingClassWriteStart(
                Unregister,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(UnregisterAll, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(NotificationTelemetryHelper& notificationTelemetryHelper, std::wstring const& appId) noexcept try
        {
            TraceLoggingClassWriteStart(
                UnregisterAll,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Show, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId,
            winrt::hstring const& payload,
            winrt::hstring const& tag,
            winrt::hstring const& group,
            bool isCallingPreviewSupported) noexcept try
        {
            TraceLoggingClassWriteStart(
                Show,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(payload.size(), "PayloadSize"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingUInt32(group.size(), "GroupSize"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"),
                TraceLoggingBool(isCallingPreviewSupported, "IsCallingPreviewSupported"));
        }
        CATCH_LOG() 
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(UpdateAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId,
            winrt::hstring const& tag,
            winrt::hstring const& group) noexcept try
        {
            TraceLoggingClassWriteStart(
                UpdateAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingUInt32(group.size(), "GroupSize"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Setting, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId) noexcept try
        {
            TraceLoggingClassWriteStart(
                Setting,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemoveByIdAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId,
            uint32_t notificationId) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemoveByIdAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingHexUInt32(notificationId, "NotificationId"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemoveByTagAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId,
            winrt::hstring const& tag) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemoveByTagAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemoveByTagAndGroupAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId,
            winrt::hstring const& tag,
            winrt::hstring const& group) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemoveByTagAndGroupAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingUInt32(group.size(), "GroupSize"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemoveByGroupAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId,
            winrt::hstring const& group) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemoveByGroupAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(group.size(), "GroupSize"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemoveAllAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemoveAllAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(GetAllAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId) noexcept try
        {
            TraceLoggingClassWriteStart(
                GetAllAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Activated, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(
            NotificationTelemetryHelper& notificationTelemetryHelper,
            std::wstring const& appId,
            winrt::hstring const& arguments,
            bool firstNotificationReceived,
            bool hasNotificationHandlers) noexcept try
        {
            TraceLoggingClassWriteStart(
                Activated,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(arguments.size(), "ArgumentsSize"),
                TraceLoggingBool(firstNotificationReceived, "FirstNotificationReceived"),
                TraceLoggingBool(hasNotificationHandlers, "HasNotificationHandlers"),
                TraceLoggingBool(notificationTelemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(notificationTelemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
