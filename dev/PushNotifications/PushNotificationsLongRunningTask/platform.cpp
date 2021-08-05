#include "pch.h"

#include <PushNotificationsLRP_h.h>

#include "platform.h"

wil::unique_event g_winmainEvent(wil::EventOptions::None);

Microsoft::WRL::ComPtr<WpnLrpPlatformImpl> g_platform;

std::once_flag m_isPlatformInitialized;

WpnLrpPlatformImpl* GetPlatform()
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
            g_platform = Microsoft::WRL::Make<WpnLrpPlatformImpl>();
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

WpnLrpPlatformImpl::WpnLrpPlatformImpl()
{
    m_lock.create();
}

void WpnLrpPlatformImpl::InitializePlatform()
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    auto lock = m_lock.acquire();

    if (m_initialized)
    {
        return;
    }

    /* Load your components */

    m_initialized = true;
}

void WpnLrpPlatformImpl::ShutdownPlatform()
{
    if (m_shutdown)
    {
        return;
    }

    auto lock = m_lock.acquire();

    /* Shut down your components */

    m_shutdown = true;
}

bool WpnLrpPlatformImpl::IsPlatformShutdown()
{
    auto lock = m_lock.acquire();
    return m_shutdown;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::RegisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::UnregisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::RegisterForegroundActivator(/*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::UnregisterForegroundActivator(/*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::RegisterFullTrustApplication(/*[in]*/ PCWSTR /*processName*/, /*[out]*/ GUID* /*appId*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}
