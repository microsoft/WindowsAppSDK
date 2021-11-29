// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"
#include "ToastActivatedEventArgs.h"

wil::unique_event& GetWaitHandleForArgs();
winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::PushNotifications::ToastActivatedEventArgs>>& GetToastHandlers();
int& GetToastHandleCount();

inline const winrt::hstring ACTIVATED_EVENT_ARGS_KEY = L"GlobalActivatedEventArgs";
inline const winrt::hstring COM_ACTIVATOR_KEY = L"ComActivatorKey";

inline const int GUID_LENGTH = 36;

struct ChannelDetails
{
    winrt::hstring channelUri;
    winrt::hstring channelId;
    winrt::hstring appUserModelId;
    winrt::Windows::Foundation::DateTime channelExpiryTime;
};

inline HRESULT GetCurrentProcessPath(wil::unique_cotaskmem_string& processName)
{
    return wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, processName);
};

inline void RegisterValue(wil::unique_hkey const& hKey, PCWSTR const& key, const BYTE* value, DWORD const& valueType, DWORD const& size)
{
    THROW_IF_FAILED(RegSetValueExW(hKey.get(), key, 0, valueType, value, size));
}

inline std::wstring ConvertPathToKey(std::wstring path)
{
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '\\')
        {
            path[i] = '.';
        }
    }
    return path;
}

inline std::wstring RetrieveUnpackagedToastGuid()
{
    wil::unique_cotaskmem_string processName;
    THROW_IF_FAILED(GetCurrentProcessPath(processName));

    std::wstring wideStringProcessName{ processName.get() };
    std::wstring subKey{ L"Software\\Classes\\AppUserModelId\\" + ConvertPathToKey(wideStringProcessName) };

    wil::unique_hkey hKey;
    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr,
        &hKey,
        nullptr));

    WCHAR registeredGuidBuffer[GUID_LENGTH + 4]; // GUID length + '{' + '}' + '\0'
    DWORD bufferLength = sizeof(registeredGuidBuffer);
    HRESULT status = RegGetValueW(
        hKey.get(),
        nullptr,
        L"ToastGUID",
        RRF_RT_REG_SZ,
        nullptr,
        &registeredGuidBuffer,
        &bufferLength);

    if (status == ERROR_FILE_NOT_FOUND)
    {
        GUID guidReference;
        THROW_IF_FAILED(CoCreateGuid(&guidReference));

        wil::unique_cotaskmem_string guidStr;
        THROW_IF_FAILED(StringFromCLSID(guidReference, &guidStr));

        std::wstring guidWideStr{ guidStr.get() };
        RegisterValue(hKey, L"ToastGUID", reinterpret_cast<const BYTE*>(guidWideStr.c_str()), REG_SZ, guidWideStr.size() * sizeof(wchar_t));
        return guidWideStr;
    }
    else
    {
        THROW_HR_IF(status, FAILED_WIN32(status));
    }
    return registeredGuidBuffer;
}

inline std::wstring RetrieveToastGuid()
{
    if (AppModel::Identity::IsPackagedProcess())
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };

        THROW_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));
        return appUserModelId;
    }
    else
    {
        return RetrieveUnpackagedToastGuid();
    }
}
