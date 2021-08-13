#pragma once

#include "../PushNotifications-Constants.h"

struct __declspec(uuid(PUSHNOTIFICATIONS_IMPL_CLSID_STRING)) NotificationsLongRunningPlatformImpl WrlFinal :
Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    INotificationsLongRunningPlatform,
    Microsoft::WRL::FtmBase>
{
    void InitializePlatform();

    void ShutdownPlatform();

    bool IsPlatformShutdown();

    /* IWpnLrpPlatform functions */

    STDMETHOD(RegisterActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(UnregisterActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(RegisterForegroundActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(UnregisterForegroundActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(RegisterFullTrustApplication)(_In_ PCSTR processName, GUID remoteId, _Out_ LPWSTR* appId);

    /* Add your functions to retrieve the platform components */

private:

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    // Here we will define the Platform components i.e. the map wrappings
};
