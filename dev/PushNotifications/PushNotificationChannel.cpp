// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"
#include <PushNotificationsLRP_h.h>
#include <iostream>
#include <PushNotificationManager.h>

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
    PushNotificationChannel::PushNotificationChannel(winrt::Windows::PushNotificationChannel const& channel) : m_channel(channel), m_isBIAvailable(PushNotificationManager::IsActivatorSupported(PushNotificationRegistrationOptions::PushTrigger)) {}

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

        char processName[1024];
        GetModuleFileNameExA(GetCurrentProcess(), NULL, processName, sizeof(processName) / sizeof(processName[0]));

        reunionEndpoint->InvokeForegroundHandlers(processName);

    }

    void PushNotificationChannel::WpnForegroundInvoke(byte* payload, ULONG length)
    {
        m_foregroundHandlers(*this, winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payload, length));
    }

    winrt::event_token PushNotificationChannel::PushReceived(winrt::Windows::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler)
    {
        if (m_isBIAvailable) // Should be !m_isBIAvailable <- just for testing
        {
            wil::com_ptr<IWpnLrpPlatform> reunionEndpoint{
                wil::CoCreateInstance<WpnLrpPlatform,
                IWpnLrpPlatform>(CLSCTX_LOCAL_SERVER) };

            winrt::event_token token = m_foregroundHandlers.add(handler);

            char processName[1024];
            GetModuleFileNameExA(GetCurrentProcess(), NULL, processName, sizeof(processName) / sizeof(processName[0]));

            THROW_IF_FAILED(reunionEndpoint->RegisterForegroundActivator(this, processName));
            return token;
        }
        else
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
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        if (!m_isBIAvailable)
        {
            m_foregroundHandlers.remove(token);
        }
        else
        {
            m_channel.PushNotificationReceived(token);
        }
    }

    PushNotificationChannel::~PushNotificationChannel() noexcept
    {
        if (m_isBIAvailable)
        {
            wil::com_ptr<IWpnLrpPlatform> reunionEndpoint{
            wil::CoCreateInstance<WpnLrpPlatform,
            IWpnLrpPlatform>(CLSCTX_LOCAL_SERVER) };

            char processName[1024];
            GetModuleFileNameExA(GetCurrentProcess(), NULL, processName, sizeof(processName) / sizeof(processName[0]));

            reunionEndpoint->UnregisterForegroundActivator(this, processName);
        }
    }
}
