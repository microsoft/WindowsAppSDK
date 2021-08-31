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
   // m_shutdownTimerManager->Setup();

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

void NotificationsLongRunningPlatformImpl::WaitForWinMainEvent()
{
    THROW_HR_IF_NULL(E_UNEXPECTED, m_shutdownTimerManager.get());
    m_shutdownTimerManager->Wait();
}

void NotificationsLongRunningPlatformImpl::GetAppIdentifier(const std::wstring processName, wil::unique_cotaskmem_string& appIdentifier)
{
    auto localSettings{
    winrt::Windows::Storage::ApplicationData::Current().LocalSettings() };

   // bool hasContainer{ localSettings.Containers().HasKey(L"LRP") };
    auto container{
        localSettings.CreateContainer(L"LRP", winrt::Windows::Storage::ApplicationDataCreateDisposition::Always) };

    auto values{ localSettings.Containers().Lookup(L"LRP").Values() };

    auto it = values.begin();
    while (it != values.end())
    {
        winrt::hstring settingValue{ winrt::unbox_value<winrt::hstring>(it.Current().Value()) };
        if (settingValue.c_str() == processName.c_str())
        {
            appIdentifier = wil::make_unique_string<wil::unique_cotaskmem_string>(it.Current().Key().c_str());
            return;
        }
    }

    GUID guidReference;
    THROW_IF_FAILED(CoCreateGuid(&guidReference));

    wil::unique_cotaskmem_string guidStr;
    THROW_IF_FAILED(StringFromCLSID(guidReference, &guidStr));

    auto container{
    localSettings.CreateContainer(L"LRP", winrt::Windows::Storage::ApplicationDataCreateDisposition::Always) };

    auto values{ localSettings.Containers().Lookup(L"LRP").Values() };
    values.Insert(guidStr.get(), winrt::box_value(processName.c_str()));

}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(
    _In_ PCWSTR processName, GUID remoteId, _Out_ PWSTR* appId) noexcept try
{
    auto lock = m_lock.lock_shared();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    wil::unique_cotaskmem_string appIdentifier;
    GetAppIdentifier(processName, appIdentifier);

    THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(appIdentifier.get(), remoteId));

    *appId = appIdentifier.get();

    return S_OK;
}
CATCH_RETURN()
