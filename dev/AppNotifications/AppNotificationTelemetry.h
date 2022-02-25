// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>
#include <wrl\wrappers\corewrappers.h>

DECLARE_TRACELOGGING_CLASS(AppNotificationTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.AppNotificationTelemetry",
    // {1825c850-a487-537d-b768-f0ab298d2565}
    (0x1825c850, 0xa487, 0x537d, 0xb7, 0x68, 0xf0, 0xab, 0x29, 0x8d, 0x25, 0x65));


class AppNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(AppNotificationTelemetry, AppNotificationTelemetryProvider);

public:
    DEFINE_EVENT_METHOD(RegisterByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RegisterByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(UnregisterByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "UnregisterByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(UnregisterAllByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "UnregisterAllByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(ShowByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "ShowByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(UpdateAsyncByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "UpdateAsyncByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(SettingByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "SettingByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(RemoveByIdAsyncByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByIdAsyncByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(RemoveByTagAsyncByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByTagAsyncByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(RemoveByTagAndGroupAsyncByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByTagAndGroupAsyncByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(RemoveByGroupAsyncByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveByGroupAsyncByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(RemoveAllAsyncByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "RemoveAllAsyncByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(GetAllAsyncByAPI)(
        winrt::hresult hr,
        std::wstring const& appId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "GetAllAsyncByAPI",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(appId.c_str(), "AppId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName(), "AppName"));
        }
    }
    CATCH_LOG()

private:
    Microsoft::WRL::Wrappers::CriticalSection m_lock;
    ULONGLONG m_lastFiredTick = 0;
    UINT m_eventCount = 0;

    static constexpr ULONGLONG c_logPeriod = 1000; // One second
    static constexpr UINT c_maxEventLimit = 10;

    UINT UpdateLogEventCount() noexcept
    {
        ULONGLONG currentTick = GetTickCount64();

        auto lock = m_lock.Lock();

        // Only fire limiting events every log period to prevent too many events from being fired
        if ((currentTick - m_lastFiredTick) > c_logPeriod)
        {
            m_eventCount = 0;
            m_lastFiredTick = currentTick;
        }

        m_eventCount++;

        return m_eventCount;
    }

    inline bool IsPackagedApp()
    {
        static const bool isPackagedApp = AppModel::Identity::IsPackagedProcess();

        return isPackagedApp;
    }

    inline const wchar_t* GetAppName()
    {
        static const std::wstring appName = IsPackagedApp() ? GetAppNamePackaged() : GetAppNameUnpackaged();

        return appName.c_str();
    }

    std::wstring GetAppNamePackaged() noexcept
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

    PCWSTR CensorFilePath(PCWSTR path) noexcept
    {
        if (path)
        {
            path = !PathIsFileSpecW(path) ? PathFindFileNameW(path) : path;
        }

        return path;
    }

    std::wstring GetAppNameUnpackaged()
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
