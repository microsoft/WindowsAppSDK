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
        PushNotificationManager();

        static winrt::Microsoft::Windows::PushNotifications::PushNotificationManager Default();
        void Register();
        void Unregister();
        void UnregisterAll();

        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid const remoteId);

        winrt::event_token PushReceived(winrt::Windows::Foundation::TypedEventHandler<Microsoft::Windows::PushNotifications::PushNotificationManager, Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler);
        void PushReceived(winrt::event_token const& token) noexcept;

        // IWpnForegroundSink
        HRESULT __stdcall InvokeAll(_In_ ULONG length, _In_ byte* payload, _Out_ BOOL* foregroundHandled) noexcept;

        // INotificationHandler
        HRESULT __stdcall OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector */) noexcept;
    private:
        void RegisterSinkHelper();
        void UnregisterSinkHelper();
        bool IsBackgroundTaskRegistered(winrt::hstring const& backgroundTaskFullName);

        winrt::event<PushNotificationEventHandler> m_foregroundHandlers;
        winrt::Windows::ApplicationModel::Background::IBackgroundTaskRegistration m_pushTriggerRegistration{ nullptr };
        wil::unique_com_class_object_cookie m_comActivatorRegistration;
        bool m_singletonBackgroundRegistration{ false };   // Defines if the long running process singleton has registered a sink with the platform for a given app
        bool m_singletonForegroundRegistration{ false };   // Defines if the app has registered a foreground sink with the Long running process singleton
        bool m_registering{ false };
        wil::srwlock m_lock;
        wil::unique_cotaskmem_string m_processName;
        winrt::guid m_registeredClsid{ GUID_NULL };
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel m_channel{ nullptr };
    };
}

namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
