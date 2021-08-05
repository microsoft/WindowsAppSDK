#pragma once

struct WpnLrpPlatformFactory WrlFinal : public Microsoft::WRL::ClassFactory<>
{
    IFACEMETHODIMP CreateInstance(
        _In_opt_ IUnknown* outer,
        _In_ REFIID riid,
        _COM_Outptr_ void** ppvObject) override;
};
