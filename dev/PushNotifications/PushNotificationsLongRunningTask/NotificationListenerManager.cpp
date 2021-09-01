#include "pch.h"

#include "NotificationListener.h"
#include "platform.h"
#include "NotificationListenerManager.h"

#include <FrameworkUdk/PushNotifications.h>

using namespace Microsoft::WRL;

void NotificationListenerManager::Initialize(NotificationsLongRunningPlatformImpl* platform, std::vector<std::wstring>& appList)
{
    m_platform = platform;

    for (std::wstring& processName : appList)
    {
        AddListener(processName);
    }
}

void NotificationListenerManager::AddListener(std::wstring processName)
{
    // TODO: Query the Storage
    std::wstring appIdFromProcessName = processName;

    if (appIdFromProcessName.empty())
    {
        // TODO: Get a GUID for AppId, put it in the Storage
        winrt::guid appId;
        THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(L"SomeAppIdentifier", appId));
    }

    ComPtr<NotificationListener> listener;
    THROW_IF_FAILED(MakeAndInitialize<NotificationListener>(&listener, m_platform, appIdFromProcessName));
    THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appIdFromProcessName.c_str(), listener.Get()));

    if (m_notificationListeners.find(appIdFromProcessName) == std::end(m_notificationListeners))
    {
        m_notificationListeners.insert({ appIdFromProcessName, listener });
    }
}

void NotificationListenerManager::RemoveListener(std::wstring processName)
{
    // TODO: Query the Storage
    std::wstring appIdFromProcessName = processName;
    HRESULT hr = PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appIdFromProcessName.c_str());

    if (SUCCEEDED(hr))
    {
        m_notificationListeners.erase(appIdFromProcessName);
    }
}
