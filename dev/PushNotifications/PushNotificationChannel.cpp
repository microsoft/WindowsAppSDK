#include "pch.h"

#include "PushNotificationChannel.h"
#include "PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushNotificationChannel::PushNotificationChannel(Windows::Networking::PushNotifications::PushNotificationChannel const& channel)
    {
        m_channel = channel;
    }
    hstring PushNotificationChannel::Uri()
    {
        return m_channel.Uri();
    }
    Windows::Foundation::DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        m_channel.Close();
    }

    winrt::event_token PushNotificationChannel::PushReceived(Windows::Foundation::TypedEventHandler<Microsoft::ProjectReunion::PushNotificationChannel, Microsoft::ProjectReunion::PushNotificationReceivedEventArgs> const& handler)
    {
        s_typedEventHandler = handler;

        Windows::Foundation::TypedEventHandler<
            winrt::Windows::Networking::PushNotifications::PushNotificationChannel,
            winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs> typedEventHandler
            (this, &winrt::Microsoft::ProjectReunion::implementation::PushNotificationChannel::LambdaWrapper);
        
        return m_channel.PushNotificationReceived(typedEventHandler);
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        m_channel.PushNotificationReceived(token);
        s_typedEventHandler = nullptr;
    }

    void PushNotificationChannel::LambdaWrapper(
        winrt::Windows::Networking::PushNotifications::PushNotificationChannel /*channel*/,
        winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs args)
    {
        Microsoft::ProjectReunion::PushNotificationReceivedEventArgs reunionPushArgs = 
            Microsoft::ProjectReunion::PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(args);
        s_typedEventHandler(nullptr, reunionPushArgs);
    }
}
