#pragma once

#include <PushNotificationsLRP_h.h>
#include "pch.h"
#include "wrl.h"
#include "PushNotificationChannel.h"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"

const IID WpnForegroundSinkId = winrt::guid("25604D55-9B17-426F-9D67-2B11B3A65598");

using namespace winrt::Microsoft::Windows::PushNotifications;

struct WpnForegroundSink : IWpnForegroundSink
{

    typedef winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> PushNotificationHandler;

    private:
        wil::unique_mutex m_lock;
        ULONG* m_ref = 0;
        PushNotificationHandler m_handlers;
        winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationChannel* m_channel;
        
    public:


    	// m_pButton->onClick = delegate(&DlgFatal::onExit);

        WpnForegroundSink() = default;

        WpnForegroundSink(winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationChannel* channel): m_channel(channel){}

        void AddEvent(PushNotificationHandler handler)
        {
            m_handlers = handler;
        }

        HRESULT InvokeAll()
        {
            winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs args = nullptr;
            m_handlers(*m_channel, winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(args));
            return S_OK;
        }

        HRESULT IUnknown::QueryInterface(const IID& iid, void** ptr)
        {
            if (!ptr)
            {
                return E_INVALIDARG;
            }
            *ptr = nullptr;
            if (iid == IID_IUnknown || iid == WpnForegroundSinkId)
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
