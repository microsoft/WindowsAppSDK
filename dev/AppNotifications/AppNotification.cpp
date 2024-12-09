// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AppNotification.h"
#include "Microsoft.Windows.AppNotifications.AppNotification.g.cpp"
#include <frameworkUdk/ToastNotificationsRT.h>

using namespace winrt::Windows::Data::Xml::Dom;
using namespace Microsoft::Windows::BaseNotifications;

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    AppNotification::AppNotification() : BaseNotification()
    {
        BaseNotification::NotificationType(ToastABI::NotificationType::NotificationType_Toast);
    }

    AppNotification::AppNotification(hstring const& payload) : BaseNotification(payload)
    {
        BaseNotification::NotificationType(ToastABI::NotificationType::NotificationType_Toast);
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData AppNotification::Progress()
    {
        auto lock{ m_lock.lock_shared() };
        return m_progressData;
    }

    void AppNotification::Progress(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const& progressData)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_progressData = progressData;
    }

    void AppNotification::SetNotificationId(uint32_t id)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_notificationId = id;
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationConferencingConfig AppNotification::ConferencingConfig()
    {
        auto lock{ m_lock.lock_shared() };
        return m_conferencingConfig;
    }

    void AppNotification::ConferencingConfig(winrt::Microsoft::Windows::AppNotifications::AppNotificationConferencingConfig const& conferencingConfig)
    {
        THROW_HR_IF(E_NOTIMPL, !AppNotificationConferencingConfig::IsCallingPreviewSupported());
        auto lock{ m_lock.lock_exclusive() };
        m_conferencingConfig = conferencingConfig;
    }
}
