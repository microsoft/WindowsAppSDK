// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "pch.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include "PushNotificationUtility.h"
#include <algorithm>
#include "NotificationTelemetryHelper.h"

inline const winrt::hstring STORED_PUSH_MANAGER_KEY = L"StoredPushManagerKey";
inline const winrt::hstring STORED_APPNOTIFICATION_MANAGER_KEY = L"StoredAppNotificationManagerKey";
inline const winrt::hstring STORED_BADGENOTIFICATION_MANAGER_KEY = L"StoredBadgeNotificationManagerKey";
inline const DWORD c_receiveArgsTimeoutInMSec{ 2000 };

inline NotificationTelemetryHelper g_telemetryHelper{};

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

MIDL_INTERFACE("19858C8F-4597-401D-A9A8-CB1457198C95") INotificationManagerDeserializer : IInspectable
{
    virtual winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const& uri) = 0;
};

struct ChannelDetails
{
    winrt::hstring channelUri;
    winrt::hstring channelId;
    winrt::hstring appId;
    winrt::Windows::Foundation::DateTime channelExpiryTime;
};

inline std::wstring GetCurrentProcessPath()
{
    std::wstring processPath{};
    THROW_IF_FAILED(wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, processPath));
    std::transform(processPath.begin(), processPath.end(), processPath.begin(), ::towlower);
    return processPath;
};
