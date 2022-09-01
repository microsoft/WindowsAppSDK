// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationLongRunningTaskTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.PushNotificationLongRunningTaskTelemetry",
    // {76c12936-0ba7-46ba-be2b-ce492e4bcf01}
    (0x76c12936, 0x0ba7, 0x46ba, 0xbe, 0x2b, 0xce, 0x49, 0x2e, 0x4b, 0xcf, 0x01));

class PushNotificationLongRunningTaskTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationLongRunningTaskTelemetry, PushNotificationLongRunningTaskTelemetryProvider);

public:
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
                TraceLoggingWideString(correlationVector.c_str(), "CorrelationVector"));
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
};
