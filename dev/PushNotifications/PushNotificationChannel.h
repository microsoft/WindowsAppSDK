// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.h"
#include <NotificationsLongRunningProcess_h.h>
#include "winrt/Windows.Networking.PushNotifications.h"
#include <frameworkudk/pushnotificationsRT.h>
#include <TerminalVelocityFeatures-PushNotifications.h>
#include "externs.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    typedef winrt::Windows::Foundation::TypedEventHandler<
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel,
        winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> PushNotificationEventHandler;

    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, IWpnForegroundSink, ABI::Microsoft::Internal::PushNotifications::INotificationListener>
    {
        PushNotificationChannel(struct ChannelDetails channelInfo)
        {
            THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

            std::swap(m_channelInfo, channelInfo);
        };

        winrt::Windows::Foundation::Uri Uri();
        winrt::Windows::Foundation::DateTime ExpirationTime();
        void Close();

        winrt::event_token PushReceived(winrt::Windows::Foundation::TypedEventHandler<Microsoft::Windows::PushNotifications::PushNotificationChannel, Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler);
        void PushReceived(winrt::event_token const& token) noexcept;

        // IWpnForegroundSink
        HRESULT __stdcall InvokeAll(_In_ ULONG length, _In_ byte* payload, _Out_ BOOL* foregroundHandled) noexcept;

        // INotificationHandler
        HRESULT __stdcall OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector */) noexcept;

    private:
        struct ChannelDetails m_channelInfo{};

        winrt::event<PushNotificationEventHandler> m_foregroundHandlers;
        wil::srwlock m_lock;
    };
}
