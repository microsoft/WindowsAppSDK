#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include "platformfactory.h"

void NotificationsLongRunningPlatformImpl::Initialize()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    // Schedule event signaling after 5 seconds.
    // This is in case we later realize there are no apps to be tracked in the LRP.
    m_lifetimeManager.Setup();

    /* TODO: Verify registry and UDK list and make sure we have apps to be tracked */

    /* TODO: Load platform components */

    m_initialized = true;
}

void NotificationsLongRunningPlatformImpl::Shutdown() noexcept
{
    auto lock = m_lock.lock_exclusive();
    if (m_shutdown)
    {
        return;
    }

    /* TODO: Shut down your components */

    m_shutdown = true;
}

void NotificationsLongRunningPlatformImpl::WaitForLifetimeEvent()
{
    m_lifetimeManager.Wait();
}

// Example of one function. We will add more as we need them.
STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(_In_ PCWSTR /*processName*/, _In_ GUID /*remoteId*/, _Out_ GUID* /*appId*/) noexcept
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterForegroundActivator(_In_ IWpnForegroundSink* sink, _In_ PCWSTR processName)
{
    auto lock = m_lock.lock_exclusive();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_foregroundSinkManager.Add(processName, sink);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterForegroundActivator(_In_ PCWSTR processName)
{
    auto lock = m_lock.lock_exclusive();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_foregroundSinkManager.Remove(processName);
    return S_OK;
}
