#pragma once
#include "PushNotificationRegistrationToken.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationRegistrationToken : PushNotificationRegistrationTokenT<PushNotificationRegistrationToken>
    {
        PushNotificationRegistrationToken() = default;

        PushNotificationRegistrationToken(uint64_t cookie, Windows::ApplicationModel::Background::BackgroundTaskRegistration const& taskRegistration);
        uint64_t Cookie();
        Windows::ApplicationModel::Background::BackgroundTaskRegistration TaskRegistration();

    private:
        uint64_t m_cookie;
        Windows::ApplicationModel::Background::BackgroundTaskRegistration m_taskRegistration = nullptr;

        wil::critical_section m_lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationRegistrationToken : PushNotificationRegistrationTokenT<PushNotificationRegistrationToken, implementation::PushNotificationRegistrationToken>
    {
    };
}
