#pragma once

#include "../PushNotifications-Constants.h"

#include "PlatformLifetimeTimerManager.h"

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

    /* Add your functions to retrieve the platform components */

private:

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    std::unique_ptr<PlatformLifetimeTimerManager> m_shutdownTimerManager;

    // Here we will define the Platform components i.e. the map wrappings
};
