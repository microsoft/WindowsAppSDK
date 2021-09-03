#pragma once

#include <map>
#include <string>
#include <vector>

class NotificationListenerManager
{
public:
    NotificationListenerManager() {};

    void Initialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::map<std::wstring, std::wstring>& appIdList);

    void AddListener(std::wstring appId, std::wstring processName);
    void RemoveListener(std::wstring appId);

    bool IsEmpty();

private:
    wil::srwlock m_lock;

    std::map<std::wstring, Microsoft::WRL::AgileRef> m_notificationListeners;
    std::shared_ptr<ForegroundSinkManager> m_foregroundSinkManager;
};
