#pragma once
#include "pch.h"
#include "Windows.Foundation.h"

typedef winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Networking::PushNotifications::PushNotificationChannel, winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs> PushNotificationHandler;

struct __declspec(uuid("FC6CF6F3-C308-4C4D-B157-8B56E0E94505")) WpnForegroundSinkImpl WrlFinal :
    Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IWpnForegroundSink, Microsoft::WRL::FtmBase>
{
    WpnForegroundSinkImpl();

    HRESULT AddEvent(winrt::Windows::Foundation::IUnknown handler);

private:
    mutable Microsoft::WRL::Wrappers::SRWLock m_lock;
    Microsoft::WRL::EventSource<PushNotificationHandler> m_event;
    // Here we also define the Platform components i.e. the map wrappings
};
