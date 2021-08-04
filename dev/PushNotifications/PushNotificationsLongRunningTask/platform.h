#pragma once

struct __declspec(uuid("330EC755-31F2-40A7-977D-B0ABB1E1E52E")) WpnLrpPlatformImpl WrlFinal :
Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IWpnLrpPlatform, Microsoft::WRL::FtmBase>
{
    WpnLrpPlatformImpl();

    void InitializePlatform();

    void ShutdownPlatform();

    bool IsPlatformInitialized();

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
