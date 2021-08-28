// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "..\WindowsAppSDK_Insights\WindowsAppRuntimeInsights.h"
#include <wrl\wrappers\corewrappers.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationTelemetryProvider, "Microsoft.WindowsAppSDK.Notifications.PushNotificationTelemetry", (0x7c1b07ef, 0xa7c0, 0x56d1, 0x54, 0x56, 0x38, 0x5e, 0xbd, 0x44, 0x12, 0xb2));
// {7c1b07ef-a7c0-56d1-5456-385ebd4412b2}

class PushNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationTelemetry, PushNotificationTelemetryProvider);

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
                    TraceLoggingWideString(to_hstring(remoteId).data(), "RemoteId"));
            }
        }
        CATCH_LOG()

    DEFINE_EVENT_METHOD(RegisterActivatorByApi)() noexcept try
        {

        }
        CATCH_LOG()

    DEFINE_EVENT_METHOD(UnregisterActivatorByApi)() noexcept try
        {

        }
        CATCH_LOG()

    DEFINE_EVENT_METHOD(IsActivatorSupportedByApi)() noexcept try
        {
        }
        CATCH_LOG()

    DEFINE_EVENT_METHOD(ChannelClosedbyApi)(
        HRESULT hr,
        const std::wstring appUserModelId,
        const std::wstring channelId) noexcept try
        {
            if (c_maxEventLimit >= UpdateLogEventCount())
            {
                ChannelClosedbyApi_(hr, CensorFilePath(appUserModelId.c_str()), channelId.c_str());
            }
        }
        CATCH_LOG()

    DEFINE_EVENT_METHOD(ChannelPushReceivedbyApi)() noexcept try
        {
        }
        CATCH_LOG()
private:
    //Microsoft::WRL::Wrappers::CriticalSection m_lock;
    ULONGLONG m_lastFiredTick = 0;
    UINT m_eventCount = 0;

    static constexpr ULONGLONG c_logPeriod = 1000; // One second
    static constexpr UINT c_maxEventLimit = 10;

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM3(ChannelClosedbyApi_,
        PDT_ProductAndServicePerformance,
        UINT32, OperationResult,
        bool,   AppIdProvided,
        PCWSTR, ChannelId);

    PCWSTR CensorFilePath(_In_opt_ PCWSTR path) noexcept
    {
        if (path)
        {
            path = !PathIsFileSpecW(path) ? PathFindFileNameW(path) : path;
        }

        return path;
    }

    UINT UpdateLogEventCount() noexcept
    {
        ULONGLONG currentTick = GetTickCount64();

        //auto lock = m_lock.Lock();

        // Only fire limiting events every log period to prevent too many events from being fired
        if ((currentTick - m_lastFiredTick) > c_logPeriod)
        {
            m_eventCount = 0;
            m_lastFiredTick = currentTick;
        }

        m_eventCount++;

        return m_eventCount;
    }
};
