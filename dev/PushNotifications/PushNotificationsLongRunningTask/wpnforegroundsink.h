#pragma once

#include "../PushNotifications-Constants.h"

struct __declspec(uuid(PUSHNOTIFICATIONS_FGSINK_CLSID_STRING)) WpnForegroundSinkImpl WrlFinal :
Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    IWpnForegroundSink,
    Microsoft::WRL::FtmBase>
{
    /* IWpnForegroundSink functions */
    STDMETHOD(AddEvent)(_In_ IUnknown * pointer) noexcept;
    STDMETHOD(RemoveEvent)(_In_ IUnknown* pointer) noexcept;
    STDMETHOD(InvokeAll)(_In_ IUnknown* pointer) noexcept;

    /* Add your functions to retrieve the platform components */

private:

    wil::srwlock m_lock;
    wil::unique_event m_event{ wil::EventOptions::None };
    wil::unique_threadpool_timer m_timer;

    // Here we will define the Platform components i.e. the map wrappings
};
