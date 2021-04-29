#include "pch.h"
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>

namespace ReunionPushNotifications = winrt::Microsoft::Windows::PushNotifications;

namespace winrt
{
    using namespace Windows::Networking::PushNotifications;
    using namespace Windows::Foundation;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationChannel::PushNotificationChannel(winrt::PushNotificationChannel const& channel)
    {
        m_channel = channel;
    }
    winrt::Uri PushNotificationChannel::Uri()
    {
        auto lock = m_lock.lock_shared();
        winrt::Uri pushChannelUri{ m_channel.Uri() };
        return pushChannelUri;
    }
    winrt::DateTime PushNotificationChannel::ExpirationTime()
    {
        auto lock = m_lock.lock_shared();
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        auto lock = m_lock.lock_exclusive();
        m_channel.Close();
    }

    winrt::event_token PushNotificationChannel::PushReceived(winrt::TypedEventHandler<ReunionPushNotifications::PushNotificationChannel, ReunionPushNotifications::PushNotificationReceivedEventArgs> const& handler)
    {
        winrt::TypedEventHandler<
            winrt::PushNotificationChannel,
            winrt::PushNotificationReceivedEventArgs> typedEventHandler
            ([&](
                winrt::PushNotificationChannel channel,
                winrt::PushNotificationReceivedEventArgs args)
                {
                    ReunionPushNotifications::PushNotificationReceivedEventArgs reunionPushArgs =
                        ReunionPushNotifications::PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(args);

                    m_typedEventHandler(*this, reunionPushArgs);
                });

        auto lock = m_lock.lock_exclusive();
        m_typedEventHandler = handler;
        return m_channel.PushNotificationReceived(typedEventHandler);
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        auto lock = m_lock.lock_exclusive();
        m_typedEventHandler = nullptr;
        m_channel.PushNotificationReceived(token);
    }
}
