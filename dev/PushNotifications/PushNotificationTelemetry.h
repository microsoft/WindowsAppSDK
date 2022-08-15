// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.PushNotificationTelemetry",
    // {7c1b07ef-a7c0-56d1-5456-385ebd4412b2}
    (0x7c1b07ef, 0xa7c0, 0x56d1, 0x54, 0x56, 0x38, 0x5e, 0xbd, 0x44, 0x12, 0xb2));


class PushNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationTelemetry, PushNotificationTelemetryProvider);

public:
    DEFINE_EVENT_METHOD(LogCreateChannelAsync)(
        winrt::hresult hr,
        const winrt::guid& remoteId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "CreateChannelAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingGuid(remoteId, "RemoteId"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogCloseChannel)(
        winrt::hresult hr) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "CloseChannel",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRegister)(
        winrt::hresult hr) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "Register",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance), 
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregister)(
        winrt::hresult hr) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "Unregister",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregisterAll)(
        winrt::hresult hr) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "UnregisterAll",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogOnRawNotificationReceived)(
            winrt::hresult hr,
            std::wstring const& correlationVector) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "OnRawNotificationReceived",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(correlationVector.c_str(), "CorrelationVector"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

        DEFINE_EVENT_METHOD(LogInvokeAll)(
            winrt::hresult hr,
            std::wstring const& correlationVector) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "InvokeAll",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(correlationVector.c_str(), "CorrelationVector"),
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

        UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };
        THROW_IF_WIN32_ERROR(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));

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
        THROW_IF_FAILED(wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, processName));

        return CensorFilePath(processName.get());
    }
};
