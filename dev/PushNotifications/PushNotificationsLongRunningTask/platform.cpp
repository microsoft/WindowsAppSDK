#include "pch.h"

#include "platform.h"
#include "platformfactory.h"
#include <FrameworkUdk/PushNotifications.h>

using namespace winrt::Windows;

void NotificationsLongRunningPlatformImpl::Initialize()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    // Schedule event signaling to happen in 5 seconds.
    // This is in case we later realize there are no apps to be tracked in the LRP.
    m_lifetimeManager.Setup();

    m_rawStorage = Storage::ApplicationData::Current().LocalSettings().CreateContainer(
        L"Raw", Storage::ApplicationDataCreateDisposition::Always);

    m_toastStorage = Storage::ApplicationData::Current().LocalSettings().CreateContainer(
        L"Toast", Storage::ApplicationDataCreateDisposition::Always);

    m_foregroundSinkManager = std::make_shared<ForegroundSinkManager>();
    m_toastRegistrationManager = std::make_shared<ToastRegistrationManager>();
    for (auto pair : m_toastStorage.Values())
    {
        m_toastRegistrationManager->Add(pair.Key().c_str(), pair.Value().as<winrt::hstring>().c_str());
    }

    m_notificationListenerManager.Initialize(m_foregroundSinkManager, m_toastRegistrationManager);

    auto fullTrustApps = GetFullTrustApps();

    if (!fullTrustApps.empty())
    {
        // We have at least one app that could receive notifications.
        // Cancel the timer to persist the LRP.
        m_lifetimeManager.Cancel();
        m_notificationListenerManager.SetAppIdMapping(fullTrustApps);
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

    m_shutdown = true;
}

void NotificationsLongRunningPlatformImpl::WaitForLifetimeEvent()
{
    m_lifetimeManager.Wait();
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(
    _In_ PCWSTR processName, GUID remoteId, _Out_ PWSTR* appId) noexcept try
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    const std::wstring appIdentifier = GetAppIdentifier(processName);
    THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(appIdentifier.c_str(), remoteId));

    wil::unique_cotaskmem_string outAppId = wil::make_unique_string<wil::unique_cotaskmem_string>(appIdentifier.c_str());
    *appId = outAppId.release();

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterLongRunningActivator(_In_ PCWSTR processName) noexcept try
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    const std::wstring appId = GetAppIdentifier(processName);
    m_notificationListenerManager.AddListener(appId, processName);

    m_lifetimeManager.Cancel();

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterLongRunningActivator(_In_ PCWSTR processName) noexcept try
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    const std::wstring appId = GetAppIdentifier(processName);
    m_notificationListenerManager.RemoveListener(appId);
    m_foregroundSinkManager->Remove(appId);

    RemoveAppIdentifier(appId);
    RemoveToastRegistration(processName);

    if (m_notificationListenerManager.IsEmpty())
    {
        m_lifetimeManager.Setup();
    }

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterForegroundActivator(_In_ IWpnForegroundSink* sink, _In_ PCWSTR processName) noexcept try
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    const std::wstring appId = GetAppIdentifier(processName);

    m_notificationListenerManager.AddListener(appId, processName);
    m_foregroundSinkManager->Add(appId, sink);

    m_lifetimeManager.Cancel();

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterForegroundActivator(_In_ PCWSTR processName) noexcept try
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    const std::wstring appId = GetAppIdentifier(processName);
    m_foregroundSinkManager->Remove(appId);

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::AddToastRegistration(_In_ PCWSTR processName, _In_ PCWSTR toastGuid) noexcept try
{
    auto lock{ m_lock.lock_exclusive() };
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_toastRegistrationManager->Add(processName, toastGuid);
    m_toastStorage.Values().Insert(processName, winrt::box_value(toastGuid));
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RemoveToastRegistration(_In_ PCWSTR processName) noexcept try
{
    auto lock{ m_lock.lock_exclusive() };
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    m_toastRegistrationManager->Remove(processName);
    m_toastStorage.Values().Remove(processName);
    return S_OK;
}
CATCH_RETURN()

// Returns a map of key-value pairs, where key is appId and value is processName.
// It should only be called by Initialize(), which already acquired a lock.
std::map<std::wstring, std::wstring> NotificationsLongRunningPlatformImpl::GetFullTrustApps()
{
    std::map<std::wstring, std::wstring> mapOfFullTrustApps;

    // Get list of full trust apps with valid channels from wpncore
    wil::unique_cotaskmem_array_ptr<wil::unique_cotaskmem_string> appIds;
    PushNotifications_GetFullTrustApplicationsWithChannels(appIds.addressof(), appIds.size_address<ULONG>());

    // Get list of apps from Storage
    auto values{ m_rawStorage.Values() };

    for (size_t i = 0; i < appIds.size(); ++i)
    {
        if (values.HasKey(appIds[i]))
        {
            winrt::hstring processName{ winrt::unbox_value<winrt::hstring>(values.Lookup(appIds[i])) };
            mapOfFullTrustApps.emplace(reinterpret_cast<PWSTR>(appIds[i]), processName.c_str());
        }
    }

    return mapOfFullTrustApps;
}

const std::wstring NotificationsLongRunningPlatformImpl::GetAppIdentifier(std::wstring const& processName)
{
    auto values{ m_rawStorage.Values() };

    for (auto it = values.begin(); it != values.end(); it++)
    {
        winrt::hstring settingValue{ winrt::unbox_value<winrt::hstring>(it.Current().Value()) };
        if (processName.compare(settingValue.c_str()) == 0)
        {
            return std::wstring{ it.Current().Key().c_str() };
        }
    }

    GUID guidReference;
    THROW_IF_FAILED(CoCreateGuid(&guidReference));

    wil::unique_cotaskmem_string guidStr;
    THROW_IF_FAILED(StringFromCLSID(guidReference, &guidStr));

    m_rawStorage.Values().Insert(guidStr.get(), winrt::box_value(processName.c_str()));
    return guidStr.get();
}

void NotificationsLongRunningPlatformImpl::RemoveAppIdentifier(std::wstring const& appId)
{
    auto values{ m_rawStorage.Values() };
    values.Remove(appId);
}

void NotificationsLongRunningPlatformImpl::RemoveToastRegistration(std::wstring const& processName)
{
    m_toastRegistrationManager->Remove(processName);

    auto values{ m_toastStorage.Values() };
    values.Remove(processName);
}
