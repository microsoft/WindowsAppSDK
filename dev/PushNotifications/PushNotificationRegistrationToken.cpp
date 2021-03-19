#include "pch.h"
#include "PushNotificationRegistrationToken.h"
#include "PushNotificationRegistrationToken.g.cpp"

#include <Windows.ApplicationModel.background.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::mutex PushNotificationRegistrationToken::s_mutex;
    std::unique_lock<std::mutex> PushNotificationRegistrationToken::s_lock(s_mutex, std::defer_lock);

    PushNotificationRegistrationToken::PushNotificationRegistrationToken(uint64_t cookie, Windows::ApplicationModel::Background::BackgroundTaskRegistration const& taskRegistration)
    {
        m_cookie = cookie;
        m_taskRegistration = taskRegistration;
    }
    uint64_t PushNotificationRegistrationToken::Cookie()
    {
        s_lock.lock();
        return m_cookie;
    }
    Windows::ApplicationModel::Background::BackgroundTaskRegistration PushNotificationRegistrationToken::TaskRegistration()
    {
        s_lock.lock();
        return m_taskRegistration;
    }
}
