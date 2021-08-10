#pragma once

struct WpnLrpPlatformFactory WrlFinal : public Microsoft::WRL::ClassFactory<>
{
    HRESULT MakeAndInitialize();

    IFACEMETHODIMP CreateInstance(
        _In_opt_ IUnknown* outer,
        _In_ REFIID riid,
        _COM_Outptr_ void** ppvObject) override;

    static void SignalEvent();

    static void WaitForEvent();

    static void SetupTimer();

    static void CancelTimer();

private:

    // WinMain is the owner of the platform reference
    Microsoft::WRL::ComPtr<NotificationsLongRunningPlatformImpl> m_platform;
    std::once_flag m_platformInitializedFlag;
    bool m_isPlatformInitialized = false;
};
