// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AppNotification.h"
#include "Microsoft.Windows.AppNotifications.AppNotification.g.cpp"

using namespace winrt::Windows::Data::Xml::Dom;

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    AppNotification::AppNotification(hstring const& payload)
    {
        XmlDocument xmlDocument{};

        // We call LoadXml to verify the payload is xml
        xmlDocument.LoadXml(payload);
        m_payload = payload;
    }

    hstring AppNotification::Tag()
    {
        auto lock{ m_lock.lock_shared() };
        return m_tag;
    }

    void AppNotification::Tag(hstring const& tag)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_tag = tag;
    }

    hstring AppNotification::Group()
    {
        auto lock{ m_lock.lock_shared() };
        return m_group;
    }

    void AppNotification::Group(hstring const& group)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_group = group;
    }

    uint32_t AppNotification::Id()
    {
        auto lock{ m_lock.lock_shared() };
        return m_notificationId;
    }

    hstring AppNotification::Payload()
    {
        auto lock{ m_lock.lock_shared() };
        return m_payload;
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

    winrt::Windows::Foundation::DateTime AppNotification::Expiration()
    {
        auto lock{ m_lock.lock_shared() };
        return m_expirationTime;
    }

    void AppNotification::Expiration(winrt::Windows::Foundation::DateTime const& expirationTime)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_expirationTime = expirationTime;
    }

    bool AppNotification::ExpiresOnReboot()
    {
        auto lock{ m_lock.lock_shared() };
        return m_expiresOnReboot;
    }

    void AppNotification::ExpiresOnReboot(bool expiresOnReboot)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_expiresOnReboot = expiresOnReboot;
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority AppNotification::Priority()
    {
        auto lock{ m_lock.lock_shared() };
        return m_priority;
    }

    void AppNotification::Priority(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority const& priority)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_priority = priority;
    }

    bool AppNotification::SuppressDisplay()
    {
        auto lock{ m_lock.lock_shared() };
        return m_suppressDisplay;
    }

    void AppNotification::SuppressDisplay(bool suppressDisplay)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_suppressDisplay = suppressDisplay;
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
