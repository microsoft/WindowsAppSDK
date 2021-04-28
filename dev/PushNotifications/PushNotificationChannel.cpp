#include "pch.h"
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationChannel::PushNotificationChannel(winrt::Windows::Networking::PushNotifications::PushNotificationChannel const& channel)
    {
        m_channel = channel;
    }
    winrt::Windows::Foundation::Uri PushNotificationChannel::Uri()
    {
        auto lock = m_lock.lock();
        winrt::Windows::Foundation::Uri pushChannelUri{ m_channel.Uri() };
        return pushChannelUri;
    }
    winrt::Windows::Foundation::DateTime PushNotificationChannel::ExpirationTime()
    {
        auto lock = m_lock.lock();
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        auto lock = m_lock.lock();
        m_channel.Close();
    }

    winrt::event_token PushNotificationChannel::PushReceived(winrt::Windows::Foundation::TypedEventHandler<Microsoft::Windows::PushNotifications::PushNotificationChannel, Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> const& handler)
    {
        winrt::Windows::Foundation::TypedEventHandler<
            winrt::Windows::Networking::PushNotifications::PushNotificationChannel,
            winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs> typedEventHandler
            ([&](
                winrt::Windows::Networking::PushNotifications::PushNotificationChannel channel,
                winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs args)
                {
                    Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs reunionPushArgs =
                        Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(args);

                    m_typedEventHandler(*this, reunionPushArgs);
                });

        auto lock = m_lock.lock();
        m_typedEventHandler = handler;
        return m_channel.PushNotificationReceived(typedEventHandler);
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        auto lock = m_lock.lock();
        m_typedEventHandler = nullptr;
        m_channel.PushNotificationReceived(token);
    }
}
