#pragma once
#include "PushNotificationChannel.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel() = default;

        PushNotificationChannel(Windows::Networking::PushNotifications::PushNotificationChannel const& channel);
        hstring Uri();
        Windows::Foundation::DateTime ExpirationTime();
        void Close();

        winrt::event_token PushReceived(Windows::Foundation::TypedEventHandler<Microsoft::ProjectReunion::PushNotificationChannel, Microsoft::ProjectReunion::PushNotificationReceivedEventArgs> const& handler);
        void PushReceived(winrt::event_token const& token) noexcept;

    private:
        winrt::Windows::Networking::PushNotifications::PushNotificationChannel m_channel{ nullptr };
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, implementation::PushNotificationChannel>
    {
    };
}
