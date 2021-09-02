#pragma once

#include "../PushNotifications-Constants.h"

#include "PlatformLifetimeManager.h"
#include "ForegroundSinkManager.h"

struct __declspec(uuid(PUSHNOTIFICATIONS_IMPL_CLSID_STRING)) NotificationsLongRunningPlatformImpl:
    winrt::implements<NotificationsLongRunningPlatformImpl, INotificationsLongRunningPlatform>
{
    void Initialize();

    void Shutdown() noexcept;

    void WaitForLifetimeEvent();

    /* INotificationsLongRunningPlatform functions */

    STDMETHOD(RegisterFullTrustApplication)(_In_ PCWSTR processName, GUID remoteId, _Out_ PWSTR* appId) noexcept;

    STDMETHOD(RegisterForegroundActivator)(_In_ IWpnForegroundSink* sink, _In_ PCWSTR processName);

    STDMETHOD(UnregisterForegroundActivator)(_In_ PCWSTR processName);

private:

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    winrt::Windows::Storage::ApplicationDataContainer m_storage{ nullptr };

    PlatformLifetimeManager m_lifetimeManager{};
    ForegroundSinkManager m_foregroundSinkManager;

    wil::unique_cotaskmem_string GetAppIdentifier(const std::wstring& processName);
};
