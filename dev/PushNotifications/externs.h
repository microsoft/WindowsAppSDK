// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"

wil::unique_event& GetWaitHandleForArgs();

inline const winrt::hstring ACTIVATED_EVENT_ARGS_KEY = L"GlobalActivatedEventArgs";

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

inline HRESULT GetAppUserModelId(wil::unique_cotaskmem_string& appUserModelId)
{
    wchar_t appId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
    UINT32 appIdSize{ ARRAYSIZE(appId) };

    GetCurrentApplicationUserModelId(&appIdSize, appId);

    appUserModelId = wil::make_unique_string<wil::unique_cotaskmem_string>(appId);

    return S_OK;
}

inline const std::string ConvertProcessNameToUtf8String(std::wstring processName)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, processName.c_str(), -1, NULL, 0, nullptr, nullptr);
    THROW_LAST_ERROR_IF(size_needed == 0);

    // size_needed minus the null character
    std::string utf8(size_needed - 1, 0);
    int size = WideCharToMultiByte(CP_UTF8, 0, processName.c_str(), size_needed - 1, &utf8[0], size_needed - 1, nullptr, nullptr);
    THROW_LAST_ERROR_IF(size == 0);
    return utf8;
}
