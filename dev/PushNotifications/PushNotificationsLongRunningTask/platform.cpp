#include "pch.h"

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

    m_foregroundSinkManager = std::make_shared<ForegroundSinkManager>();

    std::vector<std::wstring> listOfFullTrustApps = GetListOfFullTrustApps();

    if (listOfFullTrustApps.size() > 0)
    {
        // We have at least one app that could receive notifications.
        // Cancel the timer to persist the LRP.
        m_shutdownTimerManager->Cancel();
        m_notificationListenerManager.Initialize(m_foregroundSinkManager, listOfFullTrustApps);
    }

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

    // To be completed after Sharath's PR

    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterActivator(_In_ PCWSTR processName) noexcept
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_notificationListenerManager.AddListener(processName);

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterActivator(_In_ PCWSTR processName) noexcept
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_notificationListenerManager.RemoveListener(processName);
    m_foregroundSinkManager->Remove(processName);

    // TODO: Cleanup storage app entry after Sharath's PR

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterForegroundActivator(_In_ IWpnForegroundSink* sink, _In_ PCWSTR processName)
{
    auto lock = m_lock.lock_exclusive();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_notificationListenerManager.AddListener(processName);
    m_foregroundSinkManager->Add(processName, sink);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterForegroundActivator(_In_ PCWSTR processName)
{
    auto lock = m_lock.lock_exclusive();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_foregroundSinkManager->Remove(processName);
    return S_OK;
}

std::vector<std::wstring> NotificationsLongRunningPlatformImpl::GetListOfFullTrustApps()
{
    std::vector<std::wstring> listOfFullTrustApps;

    // Get list of full trust apps with valid channels from wpncore
    wil::unique_cotaskmem_array_ptr<PWSTR> appIds;
    PushNotifications_GetFullTrustApplicationsWithChannels(appIds.addressof(), appIds.size_address<ULONG>());

    for (size_t i = 0; i < appIds.size(); ++i)
    {
        // TODO: Once Storage changes come in, double check if each app is tracked on the storage.
        // Get its process name from Storage and insert it in the vector.
        // If not present in the Storage, it means there is no associated activator and we shouldn't add the app to the resulting vector.
        listOfFullTrustApps.push_back(reinterpret_cast<PWSTR>(appIds[i]));
    }

    return listOfFullTrustApps;
}
