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
    winrt::TypedEventHandler<
        Microsoft::Windows::PushNotifications::PushNotificationChannel,
        Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> s_typedEventHandler;
    wil::srwlock s_lock;

    PushNotificationChannel::PushNotificationChannel(winrt::PushNotificationChannel const& channel)
    {
        m_channel = channel;
    }
    winrt::Uri PushNotificationChannel::Uri()
    {
        auto lock = s_lock.lock_shared();
        return winrt::Uri{ m_channel.Uri() };
    }
    winrt::DateTime PushNotificationChannel::ExpirationTime()
    {
        auto lock = s_lock.lock_shared();
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        auto lock = s_lock.lock_exclusive();
        m_channel.Close();
    }

    winrt::event_token PushNotificationChannel::PushReceived(winrt::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> const& handler)
    {

        winrt::TypedEventHandler<
            winrt::PushNotificationChannel,
            winrt::PushNotificationReceivedEventArgs> typedEventHandler
            ([&](
                winrt::PushNotificationChannel channel,
                winrt::PushNotificationReceivedEventArgs args)
                {
                    PushNotificationReceivedEventArgs pushArgs =
                        PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(args);
                    auto lock = s_lock.lock_shared();
                    s_typedEventHandler(*this, pushArgs);
                });

        auto lock = s_lock.lock_exclusive();
        s_typedEventHandler = handler;
        return m_channel.PushNotificationReceived(typedEventHandler);
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        auto lock = s_lock.lock_exclusive();
        s_typedEventHandler = nullptr;
        m_channel.PushNotificationReceived(token);
    }
}
