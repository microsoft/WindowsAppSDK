#include "pch.h"

using namespace Microsoft::WRL;
using namespace ::ABI::Microsoft::Internal::PushNotifications;

void NotificationListenerManager::Initialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::shared_ptr<ToastRegistrationManager> toastRegistrationManager)
{
    m_foregroundSinkManager = foregroundSinkManager;
    m_toastRegistrationManager = toastRegistrationManager;
}

void NotificationListenerManager::SetAppIdMapping(std::map<std::wstring, std::wstring>& appIdList)
{
    for (auto appData : appIdList)
    {
        AddListener(appData.first, appData.second);
    }
}

void NotificationListenerManager::AddListener(std::wstring const& appId, std::wstring const& processName)
{
    THROW_HR_IF(E_INVALIDARG, appId.empty());
    THROW_HR_IF(E_INVALIDARG, processName.empty());

    auto lock{ m_lock.lock_exclusive() };

    // Make sure we keep the long running sink up-to-date with wpncore.
    ComPtr<INotificationListener> newListener;
    THROW_IF_FAILED(MakeAndInitialize<NotificationListener>(&newListener, m_foregroundSinkManager, m_toastRegistrationManager, appId, processName));
    THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appId.c_str(), newListener.Get()));

    AgileRef newListenerAsAgile;
    THROW_IF_FAILED(AsAgile(newListener.Get(), &newListenerAsAgile));
    m_notificationListeners[appId] = newListenerAsAgile;
    m_processNameAppIdMapping[processName] = appId;
}

void NotificationListenerManager::RemoveListener(std::wstring appId)
{
    THROW_HR_IF(E_INVALIDARG, appId.empty());

    auto lock{ m_lock.lock_exclusive() };

    LOG_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appId.c_str()));

    m_notificationListeners.erase(appId);
}

bool NotificationListenerManager::HasSinkForProcessName(std::wstring const& processName)
{
    auto lock{ m_lock.lock_shared() };

    auto it = m_processNameAppIdMapping.find(processName);
    return it != m_processNameAppIdMapping.end();
}

bool NotificationListenerManager::IsEmpty()
{
    auto lock{ m_lock.lock_shared() };
    return m_notificationListeners.empty();
}
