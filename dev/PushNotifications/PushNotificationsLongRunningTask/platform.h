#pragma once

#include "../PushNotifications-Constants.h"

struct __declspec(uuid(PUSHNOTIFICATIONS_IMPL_CLSID_STRING)) WpnLrpPlatformImpl WrlFinal :
Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IWpnLrpPlatform, Microsoft::WRL::FtmBase>
{
    WpnLrpPlatformImpl();

    void InitializePlatform();

    void ShutdownPlatform();

    bool IsPlatformShutdown();

    /* IWpnLrpPlatform functions */

    STDMETHOD(RegisterActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(UnregisterActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(RegisterForegroundActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(UnregisterForegroundActivator)(/*[in]*/ PCWSTR processName);

    STDMETHOD(RegisterFullTrustApplication)(/*[in]*/ PCWSTR processName, /*[out]*/ GUID* appId);

    /* Add your functions to retrieve the platform components */

private:

    wil::unique_mutex m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;

    // Here we will define the Platform components i.e. the map wrappings
};
