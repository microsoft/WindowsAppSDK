// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.h"
#include <PushNotificationsLRP_h.h>
#include <pch.h>
#include <wrl.h>
using namespace Microsoft::WRL;


namespace winrt::Microsoft::Windows::PushNotifications::implementation
{

    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel(winrt::Windows::Networking::PushNotifications::PushNotificationChannel const& channel);
        winrt::Windows::Foundation::Uri Uri();
        winrt::Windows::Foundation::DateTime ExpirationTime();
        void Close();

        winrt::event_token PushReceived(winrt::Windows::Foundation::TypedEventHandler<Microsoft::Windows::PushNotifications::PushNotificationChannel, Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler);
        void PushReceived(winrt::event_token const& token) noexcept;

    private:
        const winrt::Windows::Networking::PushNotifications::PushNotificationChannel m_channel{ nullptr };

        struct WpnForegroundSink : IWpnForegroundSink
        {
            private:
                ::Microsoft::WRL::EventSource m_event;
                wil::unique_mutex m_lock;
                ULONG* m_ref = 0;

            public:
                HRESULT InvokeAll()
                {
                    return S_OK;
                }

                HRESULT IUnknown::QueryInterface(const IID& iid, void** ptr)
                {
                    if (!ptr)
                    {
                        return E_INVALIDARG;
                    }
                    *ptr = nullptr;
                    if (iid == IID_IUnknown)
                    {
                        *ptr = (void*)this;
                        AddRef();
                        return NOERROR;
                    }
                    return E_NOINTERFACE;
                }

                ULONG IUnknown::AddRef()
                {
                    InterlockedIncrement(m_ref);
                    return *m_ref;
                }

                ULONG IUnknown::Release()
                {
                    ULONG ulRefCount = InterlockedDecrement(m_ref);
                    if (0 == *m_ref)
                    {
                        delete this;
                    }
                    return ulRefCount;
                }
        };

        wil::com_ptr<WpnForegroundSink> m_sink;
        wil::com_ptr<IWpnLrpPlatform> m_platform;

    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, implementation::PushNotificationChannel>
    {
    };
}
