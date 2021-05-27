// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationRegistrationToken.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationRegistrationToken : PushNotificationRegistrationTokenT<PushNotificationRegistrationToken>
    {
        PushNotificationRegistrationToken(uint64_t const& cookie, winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration const& taskRegistration);
        uint64_t Cookie();
        winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration TaskRegistration();

    private:
        const uint64_t m_cookie;
        const winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration m_taskRegistration;
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationRegistrationToken : PushNotificationRegistrationTokenT<PushNotificationRegistrationToken, implementation::PushNotificationRegistrationToken>
    {
    };
}
