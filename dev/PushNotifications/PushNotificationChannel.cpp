#include "pch.h"
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>

namespace winrt
{
    using namespace Windows::Networking::PushNotifications;
    using namespace Windows::Foundation;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationChannel::PushNotificationChannel(winrt::PushNotificationChannel const& channel): m_channel(channel) {}

    winrt::Uri PushNotificationChannel::Uri()
    {
        return winrt::Uri{ m_channel.Uri() };
    }
    winrt::DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        m_channel.Close();
    }

    winrt::event_token PushNotificationChannel::PushReceived(winrt::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> const& handler)
    {
        return m_channel.PushNotificationReceived([weak_self = get_weak(), handler](auto&&, auto&& args)
        {
            auto strong = weak_self.get();
            if (strong) handler(*strong, PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(args));
        });
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        m_channel.PushNotificationReceived(token);
    }
}
