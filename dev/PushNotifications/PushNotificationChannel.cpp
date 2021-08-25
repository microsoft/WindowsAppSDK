// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"
#include <FrameworkUdk/PushNotifications.h>

namespace winrt::Windows
{
    using namespace winrt::Windows::Networking::PushNotifications;
    using namespace winrt::Windows::Foundation;
}
namespace winrt::Microsoft
{
    using namespace winrt::Microsoft::Windows::PushNotifications;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationChannel::PushNotificationChannel(winrt::Windows::PushNotificationChannel const& channel): m_channel(channel) {}

    PushNotificationChannel::PushNotificationChannel(hstring const& channelUri,
        hstring const& channelId,
        hstring const& appUserModelId,
        winrt::Windows::Foundation::DateTime const& channelExpirationTime)
    {
        m_channelUri = winrt::Windows::Uri{ channelUri };
        m_channelExpirationTime = channelExpirationTime;
        m_channelId = channelId;
        m_appUserModelId = appUserModelId;
    }

    winrt::Windows::Uri PushNotificationChannel::Uri()
    {
        if (m_channel)
        {
            return winrt::Windows::Uri{ m_channel.Uri() };
        }
        else
        {
            return m_channelUri;
        }
    }
    winrt::Windows::DateTime PushNotificationChannel::ExpirationTime()
    {
        if (m_channel)
        {
            return m_channel.ExpirationTime();
        }
        else
        {
            return m_channelExpirationTime;
        }
    }
    void PushNotificationChannel::Close()
    {
        try
        {
            if (m_channel)
            {
                m_channel.Close();
            }
            else
            {
               PushNotifications_CloseChannel(m_appUserModelId.c_str(), m_channelId.c_str());
            }
        }
        catch (...)
        {
            auto channelCloseException = hresult_error(to_hresult());
            if (channelCloseException.code() != HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
            {
                throw hresult_error(to_hresult());
            }
        }
    }

    winrt::event_token PushNotificationChannel::PushReceived(winrt::Windows::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler)
    {
        return m_channel.PushNotificationReceived([weak_self = get_weak(), handler](auto&&, auto&& args)
        {
            auto strong = weak_self.get();
            if (strong)
            {
                handler(*strong, winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(args));
            };
        });
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        m_channel.PushNotificationReceived(token);
    }
}
