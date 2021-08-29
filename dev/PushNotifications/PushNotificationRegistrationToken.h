// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "winrt/Windows.ApplicationModel.Background.h"

struct PushNotificationRegistrationToken
{
    PushNotificationRegistrationToken() {}

    void SetCookie(uint32_t const& cookie)
    {
        m_cookie = cookie;
    }

    void SetBackgroundTaskRegistration(winrt::Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& taskRegistration)
    {
        m_taskRegistration = taskRegistration;
    }

    uint32_t GetCookie()
    {
        return m_cookie;
    }

    winrt::Windows::ApplicationModel::Background::IBackgroundTaskRegistration GetBackgroundTaskRegistration()
    {
        return m_taskRegistration;
    }

    private:
        uint32_t m_cookie = 0;
        winrt::Windows::ApplicationModel::Background::IBackgroundTaskRegistration m_taskRegistration = nullptr;
};

