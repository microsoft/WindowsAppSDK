// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

class NotificationTelemetryHelper
{
public:
    NotificationTelemetryHelper()
    {
        m_isPackagedApp = AppModel::Identity::IsPackagedProcess();
        m_appName = m_isPackagedApp ? GetAppNamePackaged() : GetAppNameUnpackaged();
    }

    inline bool ShouldLogEvent()
    {
        return c_maxEventLimit >= UpdateLogEventCount();
    }

    inline bool IsPackagedApp() const
    {
        return m_isPackagedApp;
    }

    inline const std::wstring& GetAppName() const
    {
        return m_appName;
    }

private:
    wil::srwlock m_lock;
    ULONGLONG m_lastFiredTick = 0;
    UINT m_eventCount = 0;

    static constexpr ULONGLONG c_logPeriod = 1000; // One second
    static constexpr UINT c_maxEventLimit = 10;

    bool m_isPackagedApp{ false };
    std::wstring m_appName;

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
