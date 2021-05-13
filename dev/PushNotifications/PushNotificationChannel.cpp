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
        winrt::Windows::Foundation::Uri pushChannelUri{ m_channel.Uri() };
        return pushChannelUri;
    }
    winrt::Windows::Foundation::DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        m_channel.Close();
    }
}
