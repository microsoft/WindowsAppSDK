#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationRegistrationToken.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationRegistrationToken : PushNotificationRegistrationTokenT<PushNotificationRegistrationToken>
    {
        PushNotificationRegistrationToken() = default;

        PushNotificationRegistrationToken(uint64_t cookie, winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration const& taskRegistration);
        uint64_t Cookie();
        winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration TaskRegistration();

    private:
        uint64_t m_cookie;
        winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration m_taskRegistration = nullptr;
        wil::srwlock m_lock;
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationRegistrationToken : PushNotificationRegistrationTokenT<PushNotificationRegistrationToken, implementation::PushNotificationRegistrationToken>
    {
    };
}
