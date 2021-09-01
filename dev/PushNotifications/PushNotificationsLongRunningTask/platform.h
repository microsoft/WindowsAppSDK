#pragma once

#include "../PushNotifications-Constants.h"

#include <NotificationsLongRunningProcess_h.h>

#include "PlatformLifetimeTimerManager.h"
#include "NotificationListener.h"
#include "NotificationListenerManager.h"

struct __declspec(uuid(PUSHNOTIFICATIONS_IMPL_CLSID_STRING)) NotificationsLongRunningPlatformImpl WrlFinal :
Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    INotificationsLongRunningPlatform,
    Microsoft::WRL::FtmBase>
{
    void Initialize();

    void Shutdown() noexcept;

    void WaitForWinMainEvent();

    /* IWpnLrpPlatform functions */

    STDMETHOD(RegisterFullTrustApplication)(_In_ PCWSTR processName, _In_ GUID remoteId, _Out_ GUID* appId) noexcept;

    STDMETHOD(RegisterActivator)(_In_ PCWSTR processName) noexcept;

    STDMETHOD(UnregisterActivator)(_In_ PCWSTR processName) noexcept;

    /* Add your functions to retrieve the platform components */

private:

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    std::unique_ptr<PlatformLifetimeTimerManager> m_shutdownTimerManager;

    NotificationListenerManager m_notificationListenerManager{};

    // Here we will define the Platform components i.e. the map wrappings
};
