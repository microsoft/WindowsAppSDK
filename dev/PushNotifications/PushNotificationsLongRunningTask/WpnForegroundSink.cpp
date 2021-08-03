#include "pch.h"
#include <PushNotificationsLRP_h.h>

#include "WpnForegroundSink.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Networking::PushNotifications;

STDMETHODIMP_(HRESULT __stdcall) WpnForegroundSinkImpl::AddEvent(/* [in] */ winrt::Windows::Foundation::IUnknown handler)
{
    PushNotificationHandler handler2 = handler.as<PushNotificationHandler>();
    handler2(nullptr, nullptr);
    return S_OK;
}
