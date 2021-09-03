#include "pch.h"

using namespace Microsoft::WRL;
using namespace ::ABI::Microsoft::Internal::PushNotifications;

void NotificationListenerManager::Initialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::map<std::wstring, std::wstring>& appIdList)
{
    m_foregroundSinkManager = foregroundSinkManager;

    for (auto appData : appIdList)
    {
        AddListener(appData.first, appData.second);
    }
}

void NotificationListenerManager::AddListener(std::wstring appId, std::wstring processName)
{
    auto lock = m_lock.lock_exclusive();

    THROW_HR_IF(E_INVALIDARG, appId.empty());
    THROW_HR_IF(E_INVALIDARG, processName.empty());

    if (m_notificationListeners.find(appId) == std::end(m_notificationListeners))
    {
        ComPtr<INotificationListener> listener;
        THROW_IF_FAILED(MakeAndInitialize<NotificationListener>(&listener, m_foregroundSinkManager, appId, processName));
        THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appId.c_str(), listener.Get()));

        AgileRef agileListener;
        THROW_IF_FAILED(AsAgile(listener.Get(), &agileListener));
        m_notificationListeners.insert({ appId, agileListener });
    }
}

void NotificationListenerManager::RemoveListener(std::wstring appId)
{
    auto lock = m_lock.lock_exclusive();

    THROW_HR_IF(E_INVALIDARG, appId.empty());

    LOG_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appId.c_str()));

    m_notificationListeners.erase(appId);
}

bool NotificationListenerManager::IsEmpty()
{
    auto lock = m_lock.lock_shared();
    return m_notificationListeners.empty();
}
