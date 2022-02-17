// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.h"
#include <windows.foundation.h>
#include <NotificationsLongRunningProcess_h.h>
#include <frameworkudk/pushnotificationsRT.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    typedef winrt::Windows::Foundation::TypedEventHandler<
        winrt::Microsoft::Windows::PushNotifications::PushNotificationManager,
        winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> PushNotificationEventHandler;

    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, IWpnForegroundSink, ABI::Microsoft::Internal::PushNotifications::INotificationListener>
    {
        PushNotificationManager() = default;

        static winrt::Microsoft::Windows::PushNotifications::PushNotificationManager Default();
        void RegisterActivator(Microsoft::Windows::PushNotifications::PushNotificationActivationInfo const& details);
        void UnregisterActivator(Microsoft::Windows::PushNotifications::PushNotificationRegistrationActivators const& activators);
        void UnregisterAllActivators();

        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid const remoteId);

        static bool IsActivatorSupported(Microsoft::Windows::PushNotifications::PushNotificationRegistrationActivators const& activators);

        winrt::event_token PushReceived(winrt::Windows::Foundation::TypedEventHandler<Microsoft::Windows::PushNotifications::PushNotificationManager, Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler);
        void PushReceived(winrt::event_token const& token) noexcept;

        // IWpnForegroundSink
        HRESULT __stdcall InvokeAll(_In_ ULONG length, _In_ byte* payload, _Out_ BOOL* foregroundHandled) noexcept;

        // INotificationHandler
        HRESULT __stdcall OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector */) noexcept;
    private:
        winrt::event<PushNotificationEventHandler> m_foregroundHandlers;
        wil::srwlock m_lock;
    };
}

namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
