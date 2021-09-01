#pragma once

#include <map>
#include <string>
#include <vector>

struct NotificationsLongRunningPlatformImpl;

class NotificationListenerManager
{
public:
    NotificationListenerManager() {};

    void Initialize(NotificationsLongRunningPlatformImpl* platform, std::vector<std::wstring>& appList);

    void AddListener(std::wstring processName);
    void RemoveListener(std::wstring processName);

private:
    std::map<std::wstring, Microsoft::WRL::ComPtr<NotificationListener>> m_notificationListeners;
    NotificationsLongRunningPlatformImpl* m_platform = nullptr;
};
