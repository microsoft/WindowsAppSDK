#pragma once

#include "../PushNotifications-Constants.h"
#include <winrt/base.h>

struct AppInfo
{
    winrt::guid guid;
    std::wstring processName;
};

struct __declspec(uuid(PUSHNOTIFICATIONS_IMPL_CLSID_STRING)) NotificationsLongRunningPlatformImpl WrlFinal :
Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    INotificationsLongRunningPlatform,
    Microsoft::WRL::FtmBase>
{
    void Initialize();

    void Shutdown();

    void SignalEvent();

    void WaitForEvent();

    /* IWpnLrpPlatform functions */

    STDMETHOD(RegisterFullTrustApplication)(_In_ PCWSTR processName, _In_ GUID remoteId, _Out_ GUID* appId) noexcept;

    /* Add your functions to retrieve the platform components */

private:

    void PopulateAppList();

    void SetupTimer();

    void CancelTimer();

    wil::srwlock m_lock;

    std::vector<AppInfo> m_appList;

    bool m_initialized = false;
    bool m_shutdown = false;

    wil::unique_event m_event{ wil::EventOptions::None };
    wil::unique_threadpool_timer m_timer;

    // Here we will define the Platform components i.e. the map wrappings
};
