#include "pch.h"
#include <PushNotificationsLRP_h.h>

#include "platform.h"

wil::unique_event g_winmainEvent(wil::EventOptions::None);

Microsoft::WRL::ComPtr<WpnLrpPlatformImpl> g_platform;

WpnLrpPlatformImpl* GetPlatform()
{
    if (!g_platform)
    {
        g_platform = Microsoft::WRL::Make<WpnLrpPlatformImpl>();
    }

    g_platform->AddRef();
    return g_platform.Get();
}

// create void function for copying com ptr to iinspectable

void CleanPlatform()
{
    g_platform = nullptr;
}

HRESULT InitializePlatform()
{
    if (!g_platform)
    {
        g_platform = Microsoft::WRL::Make<WpnLrpPlatformImpl>();
    }
    g_platform->InitializePlatform();
    return S_OK;
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

bool WpnLrpPlatformImpl::IsPlatformInitialized()
{
    return m_initialized;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::RegisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::UnregisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::RegisterForegroundActivator(/*[in]*/ IWpnForegroundSink*, /*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::UnregisterForegroundActivator(/*[in]*/ PCWSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::RegisterFullTrustApplication(/*[in]*/ PCWSTR /*processName*/, /*[out]*/ GUID* /*appId*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::GetStringLength(/*[in]*/ PCWSTR string, /*[out]*/ ULONG* length)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    // working too hard?
    size_t theLength = wcslen(string);
    *length = theLength;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::ManualShutdown()
{
    ShutdownPlatform();
    GetWinMainEvent().SetEvent();
    return S_OK;
}
