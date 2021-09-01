#include "pch.h"

using namespace Microsoft::WRL;

void NotificationListenerManager::Initialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::vector<std::wstring>& processNameList)
{
    m_foregroundSinkManager = foregroundSinkManager;

    for (std::wstring& processName : processNameList)
    {
        AddListener(processName);
    }
}

void NotificationListenerManager::AddListener(std::wstring processName)
{
    // TODO: Query the Storage to get appId, to be completed after Sharath's PR
    std::wstring appIdFromProcessName = processName;

    if (appIdFromProcessName.empty())
    {
        // TODO: Get a GUID as AppId, put it in the Storage. Pass an empty guid as remoteId.
        winrt::guid remoteId;
        THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(L"SomeAppIdentifier", remoteId));
    }

    ComPtr<NotificationListener> listener;
    THROW_IF_FAILED(MakeAndInitialize<NotificationListener>(&listener, m_foregroundSinkManager, appIdFromProcessName));
    THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appIdFromProcessName.c_str(), listener.Get()));

    if (m_notificationListeners.find(processName) == std::end(m_notificationListeners))
    {
        m_notificationListeners.insert({ processName, listener });
    }
}

void NotificationListenerManager::RemoveListener(std::wstring processName)
{
    // To be completed after Sharath's PR
    std::wstring appIdFromProcessName = L"appId";
    LOG_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(processName.c_str()));

    m_notificationListeners.erase(processName);
}
