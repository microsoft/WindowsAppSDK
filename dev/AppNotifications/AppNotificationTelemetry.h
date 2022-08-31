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
    DEFINE_EVENT_METHOD(LogRegister)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "Register",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregister)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "Unregister",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregisterAll)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "UnregisterAll",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogShow)(
        winrt::hresult hr,
        std::wstring const& appId,
        winrt::hstring const& payload,
        winrt::hstring const& tag,
        winrt::hstring const& group) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "Show",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(payload.size(), "PayloadSize"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingUInt32(group.size(), "GroupSize"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUpdateAsync)(
            winrt::hresult hr,
            std::wstring const& appId,
            winrt::hstring const& tag,
            winrt::hstring const& group) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "UpdateAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingUInt32(group.size(), "GroupSize"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogSetting)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "Setting",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByIdAsync)(
        winrt::hresult hr,
        std::wstring const& appId,
        uint32_t notificationId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByIdAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingHexUInt32(notificationId, "NotificationId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByTagAsync)(
        winrt::hresult hr,
        std::wstring const& appId,
        winrt::hstring const& tag) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByTagAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByTagAndGroupAsync)(
        winrt::hresult hr,
        std::wstring const& appId,
        winrt::hstring const& tag,
        winrt::hstring const& group) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByTagAndGroupAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagSize"),
                TraceLoggingUInt32(group.size(), "GroupSize"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByGroupAsync)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByGroupAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveAllAsync)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveAllAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogGetAllAsync)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (m_telemetryHelper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "GetAllAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(m_telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_telemetryHelper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

private:
    NotificationTelemetryHelper m_telemetryHelper;
};
