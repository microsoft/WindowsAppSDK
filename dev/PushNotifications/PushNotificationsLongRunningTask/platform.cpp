#include "pch.h"
#include <PushNotificationsLRP_h.h>

#include "platform.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

wil::unique_event g_winmainEvent(wil::EventOptions::None);

Microsoft::WRL::ComPtr<WpnLrpPlatformImpl> g_platform;
IWpnForegroundSink* g_sink;

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

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::RegisterForegroundActivator(/*[in]*/ IWpnForegroundSink* sink, /*[in]*/ LPCSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    // std::unordered_map<processName, std::unordered_set<IWpnForegroundSink*>> map;
    // if(map.contains(processName)) { map[processName].insert(std::unordered_set<IWpnForegroundSink*>()); }
    // map[processName].insert(sink);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::UnregisterForegroundActivator(/*[out]*/ IWpnForegroundSink* sink, /*[in]*/ LPCSTR /*processName*/)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();
    // std::unordered_set<IWpnForegroundSink*> sinks = map[processName];
    // if(sinks == nullptr) { return error };
    // sinks.erase(sink);
    // if(sink.empty()) { map.erase(processName) };
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) WpnLrpPlatformImpl::InvokeForegroundHandlers(/*[in]*/ IWpnForegroundSink* sink)
{
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.acquire();

    byte payload[] = { 0x50, 0x61, 0x79, 0x6c, 0x6f, 0x61, 0x64, 0x20,
                        0x66, 0x72, 0x6f, 0x6d, 0x20, 0x74, 0x68, 0x65,
                            0x20, 0x4c, 0x52, 0x50, 0x21}; // Payload from the LRP!
    sink->InvokeAll(payload, sizeof(payload));

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
