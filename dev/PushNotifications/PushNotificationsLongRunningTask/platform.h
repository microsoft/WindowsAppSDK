#pragma once

#include "../PushNotifications-Constants.h"

struct __declspec(uuid(PUSHNOTIFICATIONS_IMPL_CLSID_STRING)) NotificationsLongRunningPlatformImpl:
    winrt::implements<NotificationsLongRunningPlatformImpl, INotificationsLongRunningPlatform>
{
    void Initialize();

    void Shutdown() noexcept;

    void WaitForLifetimeEvent();

    /* INotificationsLongRunningPlatform functions */

    STDMETHOD(RegisterFullTrustApplication)(_In_ PCWSTR processName, _In_ GUID remoteId, _Out_ GUID* appId) noexcept;

    STDMETHOD(RegisterActivator)(_In_ PCWSTR processName) noexcept;

    STDMETHOD(UnregisterActivator)(_In_ PCWSTR processName) noexcept;

    STDMETHOD(RegisterForegroundActivator)(_In_ IWpnForegroundSink* sink, _In_ PCWSTR processName);

    STDMETHOD(UnregisterForegroundActivator)(_In_ PCWSTR processName);

private:

    std::map<std::wstring, std::wstring> GetFullTrustApps();
    std::wstring GetAppIdentifier(const std::wstring& processName);

    winrt::Windows::Storage::ApplicationDataContainer m_storage{ nullptr };

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    // Here we will define the Platform components i.e. the map wrappings
    PlatformLifetimeManager m_lifetimeManager{};
    NotificationListenerManager m_notificationListenerManager{};
    std::shared_ptr<ForegroundSinkManager> m_foregroundSinkManager;
};
