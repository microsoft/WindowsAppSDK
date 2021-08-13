#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "wpnforegroundsink.h"
#include "wpnforegroundsinkfactory.h"

STDMETHODIMP_(HRESULT __stdcall) WpnForegroundSinkImpl::AddEvent(_In_ IUnknown* pointer) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) WpnForegroundSinkImpl::RemoveEvent(_In_ IUnknown* pointer) noexcept
{
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) WpnForegroundSinkImpl::InvokeAll(_In_ IUnknown* pointer) noexcept
{
    return E_NOTIMPL;
}
