#pragma once

#include "../PushNotifications-Constants.h"

#include "PlatformLifetimeTimerManager.h"
#include "ForegroundSinkManager.h"

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

    STDMETHOD(RegisterForegroundActivator)(/*[in]*/ IWpnForegroundSink* sink, /*[in]*/ LPCSTR processName);

    STDMETHOD(UnregisterForegroundActivator)(/*[out]*/ IWpnForegroundSink* sink, /*[in]*/ LPCSTR processName);

    /* Add your functions to retrieve the platform components */

private:

    // Extra stuff for testing
    void SendForegroundNotification();
    void SetForegroundTimer();
    wil::unique_threadpool_timer m_foregroundTimer;

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    // Here we will define the Platform components i.e. the map wrappings
    std::unique_ptr<PlatformLifetimeTimerManager> m_shutdownTimerManager;
    ForegroundSinkManager m_foregroundSinkManager;
};
