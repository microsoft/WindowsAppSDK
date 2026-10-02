// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once
class TelemetryHelper
{
public:
    TelemetryHelper()
        : m_isPackagedApp(AppModel::Identity::IsPackagedProcess()),
          m_appName(m_isPackagedApp ? GetAppNamePackaged() : GetAppNameUnpackaged())
    {
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
    const bool m_isPackagedApp{ false };
    const std::wstring m_appName;

    std::wstring GetAppNamePackaged() const
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH]{};
        UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };
        THROW_IF_WIN32_ERROR(::GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));
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
