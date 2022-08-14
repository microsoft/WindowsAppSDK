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
                TraceLoggingWideString(correlationVector.c_str(), "CorrelationVector"),
                TraceLoggingBool(IsPackagedApp(), "IsAppPackaged"));
//                TraceLoggingWideString(GetAppName().c_str(), "AppName"));
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
#if 0
    inline const std::wstring& GetAppName() const
    {
        static const std::wstring appName{ IsPackagedApp() ? GetAppNamePackaged() : GetAppNameUnpackaged() };

        return appName;
    }
#endif
    std::wstring GetAppNamePackaged() const
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH]{};

        UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };
        THROW_IF_WIN32_ERROR(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));

        return appUserModelId;
    }
#if 0
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
#endif
};
