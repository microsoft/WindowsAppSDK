#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"

wil::unique_event g_winmainEvent(wil::EventOptions::None);

Microsoft::WRL::ComPtr<NotificationsLongRunningPlatformImpl> g_platform;

std::once_flag m_isPlatformInitialized;

NotificationsLongRunningPlatformImpl* GetPlatform()
{
    // We have to call InitializePlatform() before retrieving the platform on the factory.
    // Throw if Platform is already reset or was shut down.
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, !g_platform || g_platform->IsPlatformShutdown());
    return g_platform.Get();
}

void CleanPlatform()
{
    g_platform = nullptr;
}

HRESULT InitializePlatform()
{
    std::call_once(m_isPlatformInitialized,
        [&] {
            g_platform = Microsoft::WRL::Make<NotificationsLongRunningPlatformImpl>();
            g_platform->InitializePlatform();

            // Prevent scenario where if the first client goes out of scope,
            // then triggers WpnLrpPlatformImpl dtor.
            g_platform->AddRef();
        });

    return S_OK;
}

HRESULT ShutdownPlatform()
{
    if (g_platform)
    {
        g_platform->ShutdownPlatform();
    }

    return S_OK;
}

bool IsPlatformShutdown()
{
    return g_platform->IsPlatformShutdown();
}

wil::unique_event& GetWinMainEvent()
{
    return g_winmainEvent;
}

void NotificationsLongRunningPlatformImpl::InitializePlatform()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    /* Load your components */

    m_initialized = true;
}

void NotificationsLongRunningPlatformImpl::ShutdownPlatform()
{
    auto lock = m_lock.lock_exclusive();
    if (m_shutdown)
    {
        return;
    }

    /* Shut down your components */

    m_shutdown = true;
}

bool NotificationsLongRunningPlatformImpl::IsPlatformShutdown()
{
    auto lock = m_lock.lock_shared();
    return m_shutdown;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterForegroundActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterForegroundActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(/*[in]*/ PCWSTR /*processName*/, /*[out]*/ GUID* /*appId*/)
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}
