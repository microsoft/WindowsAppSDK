// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.h"
#include "PushNotifications-Constants.h"
#include "PushNotificationsLongRunningTask.ProxyStub\x64\Debug\NotificationsLongRunningProcess_h.h"
#include <wil/resource.h>
namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel(winrt::Windows::Networking::PushNotifications::PushNotificationChannel const& channel);
        winrt::Windows::Foundation::Uri Uri();
        winrt::Windows::Foundation::DateTime ExpirationTime();
        void Close();

        winrt::event_token PushReceived(winrt::Windows::Foundation::TypedEventHandler<Microsoft::Windows::PushNotifications::PushNotificationChannel, Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler);
        void PushReceived(winrt::event_token const& token) noexcept;

    private:
        const winrt::Windows::Networking::PushNotifications::PushNotificationChannel m_channel{ nullptr };
        wil::com_ptr<IWpnForegroundSink> m_sink;
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, implementation::PushNotificationChannel>
    {
    };
}
