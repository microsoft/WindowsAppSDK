// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(AppNotificationBuilderTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.AppNotificationBuilderTelemetry",
    // {6f23f3a8-1420-4814-83c7-c752565aad22}
    (0x6f23f3a8, 0x1420, 0x4814, 0x83, 0xc7, 0xc7, 0x52, 0x56, 0x5a, 0xad, 0x22));

class AppNotificationBuilderTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(AppNotificationBuilderTelemetry, AppNotificationBuilderTelemetryProvider);

public:
    DEFINE_EVENT_METHOD(LogBuildNotification)(
        winrt::hresult hr) noexcept try
    {
        if (c_maxEventLimit >= UpdateLogEventCount())
        {
            TraceLoggingClassWriteMeasure(
                "BuildNotification",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
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
