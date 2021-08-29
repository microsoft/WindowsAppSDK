#pragma once

#include <map>
#include <string>

class NotificationListenerManager
{
public:
    NotificationListenerManager();

private:
    std::map<std::wstring, NotificationListener> m_notificationListeners;
};
