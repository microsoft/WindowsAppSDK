#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel() = default;

        PushNotificationChannel(hstring const& uri, Windows::Foundation::DateTime const& expiration);
        hstring Uri();
        Windows::Foundation::DateTime ExpirationTime();
        void Close();
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, implementation::PushNotificationChannel>
    {
    };
}
