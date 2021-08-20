#pragma once

#include "../PushNotifications-Constants.h"

struct __declspec(uuid(PUSHNOTIFICATIONS_IMPL_CLSID_STRING)) NotificationsLongRunningPlatformImpl WrlFinal :
Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    INotificationsLongRunningPlatform,
    Microsoft::WRL::FtmBase>
{
    void Initialize();

    void Shutdown() noexcept;

    void SignalWinMainEvent();

    void WaitForWinMainEvent();

    /* IWpnLrpPlatform functions */

    STDMETHOD(RegisterFullTrustApplication)(_In_ PCWSTR processName, _In_ GUID remoteId, _Out_ GUID* appId) noexcept;

    /* Add your functions to retrieve the platform components */

private:

    void SetupShutdownTimer();

    void CancelShutdownTimer();

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    wil::unique_event m_event{ wil::EventOptions::None };
    wil::unique_threadpool_timer m_timer;

    // Here we will define the Platform components i.e. the map wrappings
};
