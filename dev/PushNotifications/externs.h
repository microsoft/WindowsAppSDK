// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"

wil::unique_event& GetWaitHandleForArgs();

inline const winrt::hstring ACTIVATED_EVENT_ARGS_KEY = L"GlobalActivatedEventArgs";

struct ChannelDetails
{
    wil::unique_cotaskmem_string channelUri;
    wil::unique_cotaskmem_string channelId;
    wil::unique_cotaskmem_string appUserModelId;
    winrt::Windows::Foundation::DateTime channelExpiryTime;
    winrt::hresult hr;
};

inline HRESULT GetCurrentProcessPath(wil::unique_cotaskmem_string& processName)
{
    return wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, processName);
};

