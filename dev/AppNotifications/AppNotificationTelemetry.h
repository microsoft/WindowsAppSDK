// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

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
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "Register",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregister)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "Unregister",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregisterAll)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "UnregisterAll",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogShow)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "Show",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUpdateAsync)(
            winrt::hresult hr,
            std::wstring const& appId,
            winrt::hstring const& tag,
            winrt::hstring const& group) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "UpdateAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagLength"),
                TraceLoggingUInt32(group.size(), "GroupLength"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogSetting)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "Setting",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByIdAsync)(
        winrt::hresult hr,
        std::wstring const& appId,
        uint32_t notificationId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByIdAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingHexUInt32(notificationId, "NotificationId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByTagAsync)(
        winrt::hresult hr,
        std::wstring const& appId,
        winrt::hstring const& tag) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByTagAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagLength"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByTagAndGroupAsync)(
        winrt::hresult hr,
        std::wstring const& appId,
        winrt::hstring const& tag,
        winrt::hstring const& group) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByTagAndGroupAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingUInt32(tag.size(), "TagLength"),
                TraceLoggingUInt32(group.size(), "GroupLength"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveByGroupAsync)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByGroupAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRemoveAllAsync)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveAllAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogGetAllAsync)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "GetAllAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

private:
    wil::srwlock m_lock;
    ULONGLONG m_lastFiredTick = 0;
    UINT m_eventCount = 0;

    static constexpr ULONGLONG c_logPeriod = 1000; // One second
    static constexpr UINT c_maxEventLimit = 10;

    UINT UpdateLogEventCount()
    {
        ULONGLONG currentTick = GetTickCount64();

        auto lock{ m_lock.lock_exclusive() };

        // Only fire limiting events every log period to prevent too many events from being fired
        if ((currentTick - m_lastFiredTick) > c_logPeriod)
        {
            m_eventCount = 0;
            m_lastFiredTick = currentTick;
        }

        m_eventCount++;

        return m_eventCount;
    }

    inline bool IsPackagedApp() const
    {
        static const bool isPackagedApp{ AppModel::Identity::IsPackagedProcess() };

        return isPackagedApp;
    }

    inline const std::wstring& GetAppName() const
    {
        static const std::wstring appName{ IsPackagedApp() ? GetAppNamePackaged() : GetAppNameUnpackaged() };

        return appName;
    }

    std::wstring GetAppNamePackaged() const
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH]{};

        UINT32 appUserModelIdSize = ARRAYSIZE(appUserModelId);
        auto result = GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId);
        if (result != ERROR_SUCCESS)
        {
            wcscpy_s(appUserModelId, L"AppUserModelId not found");
            LOG_WIN32(result);
        }

        return appUserModelId;
    }

    std::wstring CensorFilePath(const std::wstring& filepath) const
    {
        return { !PathIsFileSpecW(filepath.c_str()) ? PathFindFileNameW(filepath.c_str()) : filepath };
    }

    std::wstring GetAppNameUnpackaged() const
    {
        std::wstring appName;

        wil::unique_cotaskmem_string processName;
        auto result = wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, processName);
        if (result == ERROR_SUCCESS)
        {
            appName = CensorFilePath(processName.get());
        }
        else
        {
            appName = L"ModuleFileName not found";
            LOG_WIN32(result);
        }

        return appName;
    }
};
