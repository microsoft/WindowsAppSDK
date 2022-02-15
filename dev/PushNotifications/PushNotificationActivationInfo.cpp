// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushNotificationActivationInfo.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationActivationInfo.g.cpp"
#include <TerminalVelocityFeatures-PushNotifications.h>
#include <Windows.ApplicationModel.background.h>

namespace winrt
{
    using namespace Microsoft::Windows::PushNotifications;
    using namespace Windows::ApplicationModel::Background;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationActivationInfo::PushNotificationActivationInfo(winrt::PushNotificationRegistrationActivators const& activators) : m_activators(activators)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());
    }

    winrt::PushNotificationRegistrationActivators PushNotificationActivationInfo::Activators()
    {
        return m_activators;
    }

    winrt::com_array<winrt::IBackgroundCondition> PushNotificationActivationInfo::GetConditions()
    {
        auto lock = m_lock.lock_shared();
        return { m_backgroundConditions.begin(), m_backgroundConditions.end() };
    }

    void PushNotificationActivationInfo::SetConditions(array_view<winrt::IBackgroundCondition const> conditions)
    {
        // Need to destroy old conditions outside of lock.
        auto replacement = winrt::com_array(conditions.begin(), conditions.end());
        auto lock = m_lock.lock_exclusive();
        swap(m_backgroundConditions, replacement);
    }
}
