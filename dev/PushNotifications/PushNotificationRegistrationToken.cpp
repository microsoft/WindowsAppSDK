#include "pch.h"
#include "PushNotificationRegistrationToken.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationRegistrationToken.g.cpp"

#include <Windows.ApplicationModel.background.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationRegistrationToken::PushNotificationRegistrationToken(uint64_t const& cookie, winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration const& taskRegistration): m_cookie(cookie), m_taskRegistration(taskRegistration) { }

    uint64_t PushNotificationRegistrationToken::Cookie()
    {
        return m_cookie;
    }

    winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration PushNotificationRegistrationToken::TaskRegistration()
    {
        return m_taskRegistration;
    }
}
