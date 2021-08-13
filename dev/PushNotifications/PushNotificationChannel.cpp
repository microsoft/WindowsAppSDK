// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"
#include <PushNotificationsLRP_h.h>
#include "WpnForegroundSink.h"
#include <iostream>
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
    PushNotificationChannel::PushNotificationChannel(winrt::Windows::PushNotificationChannel const& channel): m_channel(channel), m_sink() {}

    winrt::Windows::Uri PushNotificationChannel::Uri()
    {
        return winrt::Windows::Uri{ m_channel.Uri() };
    }
    winrt::Windows::DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_channel.ExpirationTime();
    }
    void PushNotificationChannel::Close()
    {
        try
        {
            m_channel.Close();
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
    void PushNotificationChannel::TriggerForeground()
    {
        wil::com_ptr<IWpnLrpPlatform> reunionEndpoint{
            wil::CoCreateInstance<WpnLrpPlatform,
            IWpnLrpPlatform>(CLSCTX_LOCAL_SERVER) };

        std::cout << "Calling TriggerForeground" << std::endl;
        m_sink.InvokeAll();
        reunionEndpoint->UnregisterForegroundActivator(&m_sink, L"TestName");

    }
    winrt::event_token PushNotificationChannel::PushReceived(winrt::Windows::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler)
    {
        wil::com_ptr<IWpnLrpPlatform> reunionEndpoint{
            wil::CoCreateInstance<WpnLrpPlatform,
            IWpnLrpPlatform>(CLSCTX_LOCAL_SERVER) };
                
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel selfRef = *this;
        m_sink.SetChannel(selfRef);
        winrt::event_token token = m_sink.AddEvent(handler);

        reunionEndpoint->RegisterForegroundActivator(&m_sink, L"TestName");

        

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
        // if protocol registered, call WpnForegorundSink.Remove(token);
        m_channel.PushNotificationReceived(token);
    }
}
