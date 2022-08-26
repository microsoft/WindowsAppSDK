// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult>
    {
        PushNotificationCreateChannelResult() = default;
        PushNotificationCreateChannelResult(Microsoft::Windows::PushNotifications::PushNotificationChannel const& channel, hresult const& extendedError, Microsoft::Windows::PushNotifications::PushNotificationChannelStatus const& status);
        Microsoft::Windows::PushNotifications::PushNotificationChannel Channel();
        winrt::hresult ExtendedError();
        Microsoft::Windows::PushNotifications::PushNotificationChannelStatus Status();

    private:
        const Microsoft::Windows::PushNotifications::PushNotificationChannel m_channel{ nullptr };
        const winrt::hresult m_extendedError;
        const Microsoft::Windows::PushNotifications::PushNotificationChannelStatus m_status;
    };
}
