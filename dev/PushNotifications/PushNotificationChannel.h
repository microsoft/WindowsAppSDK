#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel() = default;

        PushNotificationChannel(winrt::Windows::Networking::PushNotifications::PushNotificationChannel const& channel);
        winrt::Windows::Foundation::Uri Uri();
        winrt::Windows::Foundation::DateTime ExpirationTime();
        void Close();

    private:
        winrt::Windows::Networking::PushNotifications::PushNotificationChannel m_channel{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, implementation::PushNotificationChannel>
    {
    };
}
