#include "pch.h"
#include <PushNotificationsLRP_h.h>
#include <WpnForegroundSinkWrapper.h>

STDMETHODIMP_(HRESULT __stdcall) WpnForegroundSinkWrapperImpl::GetForegroundSink(/*[out]*/ IUnknown** sink)
{
    m_sink.CopyTo(sink);
    return S_OK;
}
