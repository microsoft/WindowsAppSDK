#pragma once
#include "PushNotificationChannel.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel() = default;

        PushNotificationChannel(Windows::Networking::PushNotifications::PushNotificationChannel const& channel);
        Windows::Foundation::Uri Uri();
        Windows::Foundation::DateTime ExpirationTime();
        void Close();

    private:
        winrt::Windows::Networking::PushNotifications::PushNotificationChannel m_channel{ nullptr };
        Windows::Foundation::Uri Uri{ nullptr };
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, implementation::PushNotificationChannel>
    {
    };
}
