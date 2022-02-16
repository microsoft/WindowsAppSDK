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

inline winrt::Windows::Foundation::IInspectable GetArgsFromComStore()
{
    const DWORD receiveArgsTimeoutInMSec{ 2000 };
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_TIMEOUT), !GetWaitHandleForArgs().wait(receiveArgsTimeoutInMSec));

    // If COM static store was uninit, let it throw
    if (PushNotificationHelpers::IsPackagedAppScenario())
    {
        return winrt::Windows::ApplicationModel::Core::CoreApplication::Properties().Lookup(ACTIVATED_EVENT_ARGS_KEY);
    }
    else
    {
        return winrt::Windows::ApplicationModel::Core::CoreApplication::Properties().Lookup(LRP_ACTIVATED_EVENT_ARGS_KEY);
    }
}
