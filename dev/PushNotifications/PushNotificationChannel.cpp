#include "pch.h"
#include "PushNotificationChannel.h"
#include "PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Windows::Foundation::TypedEventHandler<
        Microsoft::ProjectReunion::PushNotificationChannel,
        Microsoft::ProjectReunion::PushNotificationReceivedEventArgs> s_typedEventHandler;

    PushNotificationChannel::PushNotificationChannel(Windows::Networking::PushNotifications::PushNotificationChannel const& channel)
    {
        m_channel = channel;
    }
    Windows::Foundation::Uri PushNotificationChannel::Uri()
    {
        auto lock = m_lock.lock();
        Windows::Foundation::Uri pushChannelUri{ m_channel.Uri() };
        return pushChannelUri;
    }
    Windows::Foundation::DateTime PushNotificationChannel::ExpirationTime()
    {
        auto lock = m_lock.lock();
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        auto lock = m_lock.lock();
        m_channel.Close();
    }

    winrt::event_token PushNotificationChannel::PushReceived(Windows::Foundation::TypedEventHandler<Microsoft::ProjectReunion::PushNotificationChannel, Microsoft::ProjectReunion::PushNotificationReceivedEventArgs> const& handler)
    {
        Windows::Foundation::TypedEventHandler<
            winrt::Windows::Networking::PushNotifications::PushNotificationChannel,
            winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs> typedEventHandler
            (this, &winrt::Microsoft::ProjectReunion::implementation::PushNotificationChannel::LambdaWrapper);

        auto lock = m_lock.lock();
        s_typedEventHandler = handler;
        return m_channel.PushNotificationReceived(typedEventHandler);
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        s_typedEventHandler = nullptr;

        auto lock = m_lock.lock();
        m_channel.PushNotificationReceived(token);
    }

    void PushNotificationChannel::LambdaWrapper(
        winrt::Windows::Networking::PushNotifications::PushNotificationChannel channel,
        winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs args)
    {
        Microsoft::ProjectReunion::PushNotificationReceivedEventArgs reunionPushArgs =
            Microsoft::ProjectReunion::PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(args);

        s_typedEventHandler(*this, reunionPushArgs);
    }
}
