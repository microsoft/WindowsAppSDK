#pragma once

struct NotificationsLongRunningProcessFactory WrlFinal : public Microsoft::WRL::ClassFactory<>
{
    HRESULT RuntimeClassInitialize() noexcept;

    IFACEMETHODIMP CreateInstance(
        _In_opt_ IUnknown* outer,
        _In_ REFIID riid,
        _COM_Outptr_ void** ppvObject) override;

private:
    Microsoft::WRL::ComPtr<NotificationsLongRunningPlatformImpl> m_platform;
};
