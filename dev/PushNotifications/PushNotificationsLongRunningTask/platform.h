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

    STDMETHOD(RegisterFullTrustApplication)(_In_ PCWSTR processName, GUID remoteId, _Out_ PWSTR* appId) noexcept;

    /* Add your functions to retrieve the platform components */

private:

    wil::srwlock m_lock;

    bool m_initialized = false;
    bool m_shutdown = false;
    std::map<std::wstring, std::wstring> m_appIdMap;

    std::unique_ptr<PlatformLifetimeTimerManager> m_shutdownTimerManager;

    void GetAppIdentifier(std::wstring processName);

    void AddToRegistry(const std::wstring& processName, const std::wstring appId);
};
