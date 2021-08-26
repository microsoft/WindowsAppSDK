// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "WindowsAppSDKInsights.h"
#include <wrl\wrappers\corewrappers.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationTelemetryProvider, "Microsoft.WindowsAppSDK.Notifications.PushNotificationTelemetry", (0x7c1b07ef, 0xa7c0, 0x56d1, 0x54, 0x56, 0x38, 0x5e, 0xbd, 0x44, 0x12, 0xb2));
// {7c1b07ef-a7c0-56d1-5456-385ebd4412b2}

class PushNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationTelemetry, PushNotificationTelemetryProvider);

public:
#if 0
    static void GetCorrelationVector(std::string& cv) noexcept try
    {
        char correlationVector[CORRELATION_VECTOR_STRING_LENGTH]{ '\0' };
        TraceLoggingCorrelationVector cvGenerated;

        // Increment and fetch the correlation vector.
        bool cvFetchSucceeded = cvGenerated.Increment(correlationVector);
        THROW_HR_IF(E_UNEXPECTED, !cvFetchSucceeded);
        cv = correlationVector;
    }
    CATCH_LOG();
#endif
    DEFINE_EVENT_METHOD(ToastActivationStart)(
        _In_ PCWSTR appUserModelId,
        _In_ PCWSTR activationType,
        std::string& correlationVector) noexcept
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            ToastActivationStart(CensorFilePath(appUserModelId), activationType, correlationVector.c_str());
        }
    }

    DEFINE_EVENT_METHOD(ToastActivationStop)(
        _In_ PCWSTR appUserModelId,
        _In_ PCWSTR activationType,
        _In_ winrt::hstring argument,
        ULONG inputCount,
        HRESULT hr,
        std::string& correlationVector) noexcept
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            ToastActivationStop(CensorFilePath(appUserModelId), activationType, argument.size(), inputCount, hr, correlationVector.c_str());
        }
    }

    DEFINE_EVENT_METHOD(ChannelRequestedByApi)(
        HRESULT hr,
        bool appIdProvided,
        const std::wstring pkgFullName,
        const std::wstring appUserModelId,
        const std::wstring remoteId) noexcept try
        {
            if (c_maxEventLimit >= UpdateLogEventCount())
            {
                ChannelRequestedByApi_(hr, appIdProvided, pkgFullName.c_str(), CensorFilePath(appUserModelId.c_str()), remoteId.c_str());
            }
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

private:
    //Microsoft::WRL::Wrappers::CriticalSection m_lock;
    ULONGLONG m_lastFiredTick = 0;
    UINT m_eventCount = 0;

    static constexpr ULONGLONG c_logPeriod = 1000; // One second
    static constexpr UINT c_maxEventLimit = 10;

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM2_CV(ToastActivationStart,
        PDT_ProductAndServicePerformance,
        PCWSTR, AppUserModelId,
        PCWSTR, ActivationType);

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM5_CV(ToastActivationStop,
        PDT_ProductAndServicePerformance,
        PCWSTR, AppUserModelId,
        PCWSTR, ActivationType,
        UINT64, ArgumentLength,
        UINT32, InputCount,
        UINT32, OperationResult);

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM5(ChannelRequestedByApi_,
        PDT_ProductAndServicePerformance,
        UINT32, OperationResult,
        BOOL,   AppIdProvided,
        PCWSTR, PackageName,
        PCWSTR, AppUserModelId,
        PCWSTR, RemoteId);

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
