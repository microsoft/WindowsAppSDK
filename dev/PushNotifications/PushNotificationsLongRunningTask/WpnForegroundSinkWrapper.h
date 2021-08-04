#pragma once
#include "WpnForegroundSink.h"

struct __declspec(uuid("FC6CF6F3-C308-4C4D-B157-8B56E0E94505")) WpnForegroundSinkWrapperImpl WrlFinal :
    Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IWpnForegroundSinkWrapper, Microsoft::WRL::FtmBase>
{
    WpnForegroundSinkWrapperImpl() = default;

    STDMETHOD(GetForegroundSink)(/*[out]*/ IUnknown** sink);

    private:
        Microsoft::WRL::ComPtr<WpnForegroundSink> m_sink;
};
