// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

using namespace Microsoft::WRL;
using namespace ::ABI::Microsoft::Internal::PushNotifications;

void NotificationListenerManager::Initialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::shared_ptr<ToastRegistrationManager> toastRegistrationManager)
{
    m_foregroundSinkManager = foregroundSinkManager;
    m_toastRegistrationManager = toastRegistrationManager;
}

// The mapping setup here is appId -> (processName, comServerClsid)
void NotificationListenerManager::SetAppIdMapping(std::map<std::wstring, std::pair<std::wstring, winrt::guid>>& appIdList)
{
    for (auto appData : appIdList)
    {
        AddListener(appData.first /* appId */, appData.second.first /* processName */, appData.second.second /* comServerClsid */);
    }
}

void NotificationListenerManager::AddListener(std::wstring const& appId, std::wstring const& processName, winrt::guid const& comServerClsid)
{
    THROW_HR_IF(E_INVALIDARG, appId.empty());
    THROW_HR_IF(E_INVALIDARG, processName.empty());    

    // Make sure we keep the long running sink up-to-date with wpncore.
    ComPtr<INotificationListener> newListener;
    {
        auto lock{ m_lock.lock_shared() };
        THROW_IF_FAILED(MakeAndInitialize<NotificationListener>(&newListener, m_foregroundSinkManager, m_toastRegistrationManager, appId, processName, comServerClsid));
    }

    THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appId.c_str(), newListener.Get()));

    AgileRef newListenerAsAgile;
    THROW_IF_FAILED(AsAgile(newListener.Get(), &newListenerAsAgile));

    auto lock{ m_lock.lock_exclusive() };
    m_notificationListeners[appId] = newListenerAsAgile;
}

void NotificationListenerManager::RemoveListener(std::wstring appId)
{
    THROW_HR_IF(E_INVALIDARG, appId.empty());

    LOG_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appId.c_str()));

    auto lock{ m_lock.lock_exclusive() };
    m_notificationListeners.erase(appId);
}

bool NotificationListenerManager::IsEmpty()
{
    auto lock{ m_lock.lock_shared() };
    return m_notificationListeners.empty();
}
