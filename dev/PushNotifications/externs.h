// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include "PushNotificationUtility.h"

wil::unique_event& GetWaitHandleForArgs();
winrt::guid& GetComServerClsid();

inline const winrt::hstring ACTIVATED_EVENT_ARGS_KEY = L"GlobalActivatedEventArgs";
inline const winrt::hstring LRP_ACTIVATED_EVENT_ARGS_KEY = L"LRPActivatedEventArgs";

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

struct ChannelDetails
{
    winrt::hstring channelUri;
    winrt::hstring channelId;
    winrt::hstring appId;
    winrt::Windows::Foundation::DateTime channelExpiryTime;
};

inline HRESULT GetCurrentProcessPath(wil::unique_cotaskmem_string& processName)
{
    return wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, processName);
};
