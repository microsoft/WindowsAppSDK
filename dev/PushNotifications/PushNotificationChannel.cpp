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
    Windows::Foundation::Uri PushNotificationChannel::Uri()
    {
        winrt::Windows::Foundation::Uri pushChannelUri{ m_channel.Uri() };
        return pushChannelUri;
    }
    Windows::Foundation::DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        m_channel.Close();
    }
}
