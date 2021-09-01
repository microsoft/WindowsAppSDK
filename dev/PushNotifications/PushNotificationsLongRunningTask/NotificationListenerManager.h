#pragma once

#include <map>
#include <string>
#include <vector>

class NotificationListenerManager
{
public:
    NotificationListenerManager() {};

    void Initialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::vector<std::wstring>& processNameList);

    void AddListener(std::wstring processName);
    void RemoveListener(std::wstring processName);

private:
    std::map<std::wstring, Microsoft::WRL::ComPtr<NotificationListener>> m_notificationListeners;
    std::shared_ptr<ForegroundSinkManager> m_foregroundSinkManager;
};
