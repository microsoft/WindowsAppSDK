#pragma once

#include <PushNotificationsLRP_h.h>
#include "pch.h"
#include "wrl.h"
#include "PushNotificationChannel.h"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"
#include <objidl.h>

const IID WpnForegroundSinkId = winrt::guid("25604D55-9B17-426F-9D67-2B11B3A65598");

using namespace winrt::Microsoft::Windows::PushNotifications;

struct WpnForegroundSink : IWpnForegroundSink, IAgileObject
{

    typedef winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> PushNotificationHandler;

    private:
        wil::unique_mutex m_lock;
        ULONG* m_ref = 0;
        winrt::event<PushNotificationHandler> m_event;
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel * m_channel;

    public:

        WpnForegroundSink() {};
        ~WpnForegroundSink() {};
        winrt::event_token AddEvent(PushNotificationHandler handler)
        {
            return m_event.add(handler);
        }

        void SetChannel(winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel& channel)
        {
            m_channel = &channel;
        }

        bool IsChannelSet()
        {
            return m_channel != nullptr;
        }

        //void SetChannel

        HRESULT InvokeAll()
        {
            winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs args = nullptr;
            m_event(*m_channel, nullptr);
            return S_OK;
        }

        HRESULT QueryInterface(const IID& iid, void** ptr)
        {
            if (!ptr)
            {
                return E_INVALIDARG;
            }
            *ptr = nullptr;
            if (iid == IID_IUnknown || iid == WpnForegroundSinkId || iid == IID_IAgileObject)
            {
                *ptr = (void*)this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }

        ULONG AddRef()
        {
            //InterlockedIncrement(m_ref);
            //return *m_ref;
            return 1;
        }

        ULONG Release()
        {
            /*ULONG ulRefCount = InterlockedDecrement(m_ref);
            if (0 == *m_ref)
            {
                this->~WpnForegroundSink();
            }
            */
            return 1;
        }
};
