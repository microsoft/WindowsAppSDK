// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "..\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"
#include <wrl\wrappers\corewrappers.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.PushNotificationTelemetry",
    // {7c1b07ef-a7c0-56d1-5456-385ebd4412b2}
    (0x7c1b07ef, 0xa7c0, 0x56d1, 0x54, 0x56, 0x38, 0x5e, 0xbd, 0x44, 0x12, 0xb2));


class PushNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationTelemetry, PushNotificationTelemetryProvider);

    using RegistrationOptions = winrt::Microsoft::Windows::PushNotifications::PushNotificationRegistrationOptions;

public:
    DEFINE_EVENT_METHOD(ChannelRequestedByApi)(
        winrt::hresult hr,
        bool isAppPackaged,
        const winrt::guid& remoteId) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "ChannelRequestedByApi",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(isAppPackaged, "IsAppPackaged"),
                TraceLoggingWideString(to_hstring(remoteId).data(), "RemoteId"),
                TraceLoggingWideString(GetAppUserModelId(), "AppUserModelId"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(ChannelClosedByApi)(
        winrt::hresult hr) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "ChannelClosedByApi",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingWideString(GetAppUserModelId(), "AppUserModelId"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(ActivatorRegisteredByApi)(
        winrt::hresult hr,
        RegistrationOptions options) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "ActivatorRegisteredByApi",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingHexUInt32(static_cast<std::underlying_type_t<RegistrationOptions>>(options), "RegistrationOptions"),
                TraceLoggingWideString(GetAppUserModelId(), "AppUserModelId"));
        }
    }
    CATCH_LOG()


    DEFINE_EVENT_METHOD(ActivatorUnregisteredByApi)(
        winrt::hresult hr,
        RegistrationOptions options) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "ActivatorUnregisteredByApi",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingHexUInt32(static_cast<std::underlying_type_t<RegistrationOptions>>(options), "RegistrationOptions"),
                TraceLoggingWideString(GetAppUserModelId(), "AppUserModelId"));
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

    wchar_t m_appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};

    wchar_t* GetAppUserModelId()
    {
        if (m_appUserModelId[0] == '\0')
        {
            UINT32 appUserModelIdSize = ARRAYSIZE(m_appUserModelId);
            LOG_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, m_appUserModelId));
        }

        return m_appUserModelId;
    }
};
