// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.h"
#include "winrt/Windows.Networking.PushNotifications.h"
#include "externs.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel(struct ChannelDetails channelInfo);

        winrt::Windows::Foundation::Uri Uri();
        winrt::Windows::Foundation::DateTime ExpirationTime();
        void Close();

    private:
        struct ChannelDetails m_channelInfo{};
        wil::srwlock m_lock;
    };
}
