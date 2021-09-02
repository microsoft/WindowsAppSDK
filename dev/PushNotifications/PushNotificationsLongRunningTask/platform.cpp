#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include "platformfactory.h"
#include <FrameworkUdk/PushNotifications.h>

void NotificationsLongRunningPlatformImpl::Initialize()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    // Schedule event signaling after 5 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer should be canceled.
    m_shutdownTimerManager = std::make_unique<PlatformLifetimeTimerManager>();
    m_shutdownTimerManager->Setup();

    // Creates storage if needed otherwise looks up container.
    m_storage = winrt::Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LRP", winrt::Windows::Storage::ApplicationDataCreateDisposition::Always);

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

void NotificationsLongRunningPlatformImpl::WaitForWinMainEvent()
{
    THROW_HR_IF_NULL(E_UNEXPECTED, m_shutdownTimerManager.get());
    m_shutdownTimerManager->Wait();
}

wil::unique_cotaskmem_string NotificationsLongRunningPlatformImpl::GetAppIdentifier(const std::wstring& processName)
{
    auto values{ m_storage.Values() };

    for (auto it = values.begin(); it != values.end(); it++)
    {
        winrt::hstring settingValue{ winrt::unbox_value<winrt::hstring>(it.Current().Value()) };

        if (processName.compare(settingValue.c_str()) == 0)
        {
            return wil::make_unique_string<wil::unique_cotaskmem_string>(it.Current().Key().c_str());
        }
    }

    GUID guidReference;
    THROW_IF_FAILED(CoCreateGuid(&guidReference));

    wil::unique_cotaskmem_string guidStr;
    THROW_IF_FAILED(StringFromCLSID(guidReference, &guidStr));

    m_storage.Values().Insert(guidStr.get(), winrt::box_value(processName.c_str()));
    return guidStr;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(
    _In_ PCWSTR processName, GUID remoteId, _Out_ PWSTR* appId) noexcept try
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    wil::unique_cotaskmem_string appIdentifier = GetAppIdentifier(processName);

    THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(appIdentifier.get(), remoteId));

    *appId = appIdentifier.get();

    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterForegroundActivator(_In_ IWpnForegroundSink* sink, _In_ PCWSTR processName)
{
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.lock_exclusive();

    m_foregroundSinkManager.Add(processName, sink);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterForegroundActivator(_In_ PCWSTR processName)
{
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.lock_exclusive();

    m_foregroundSinkManager.Remove(processName);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::SendBackgroundNotification(_In_ PCWSTR processName, _In_ ULONG payloadSize, _In_ byte* payload)
{
    return S_OK;
}
