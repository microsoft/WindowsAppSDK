// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BaseNotification.h"

using namespace winrt::Windows::Data::Xml::Dom;

namespace Microsoft::Windows::BaseNotifications {
    BaseNotification::BaseNotification(winrt::hstring const& payload)
    {
        XmlDocument xmlDocument{};

        // We call LoadXml to verify the payload is xml
        xmlDocument.LoadXml(payload);
        m_payload = payload;
    }

    winrt::hstring BaseNotification::Tag()
    {
        auto lock{ m_lock.lock_shared() };
        return m_tag;
    }

    void BaseNotification::Tag(winrt::hstring const& tag)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_tag = tag;
    }

    winrt::hstring BaseNotification::Group()
    {
        auto lock{ m_lock.lock_shared() };
        return m_group;
    }

    void BaseNotification::Group(winrt::hstring const& group)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_group = group;
    }

    uint32_t BaseNotification::Id()
    {
        auto lock{ m_lock.lock_shared() };
        return m_notificationId;
    }

    winrt::hstring BaseNotification::Payload()
    {
        auto lock{ m_lock.lock_shared() };
        return m_payload;
    }

    winrt::Windows::Foundation::DateTime BaseNotification::Expiration()
    {
        auto lock{ m_lock.lock_shared() };
        return m_expirationTime;
    }

    void BaseNotification::Expiration(winrt::Windows::Foundation::DateTime const& expirationTime)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_expirationTime = expirationTime;
    }

    bool BaseNotification::ExpiresOnReboot()
    {
        auto lock{ m_lock.lock_shared() };
        return m_expiresOnReboot;
    }

    void BaseNotification::ExpiresOnReboot(bool expiresOnReboot)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_expiresOnReboot = expiresOnReboot;
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority BaseNotification::Priority()
    {
        auto lock{ m_lock.lock_shared() };
        return m_priority;
    }

    void BaseNotification::Priority(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority const& priority)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_priority = priority;
    }

    bool BaseNotification::SuppressDisplay()
    {
        auto lock{ m_lock.lock_shared() };
        return m_suppressDisplay;
    }

    void BaseNotification::SuppressDisplay(bool suppressDisplay)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_suppressDisplay = suppressDisplay;
    }

    void BaseNotification::Id(uint32_t id)
    {
        auto lock{ m_lock.lock_shared() };
        m_notificationId = id;
    }

    ::ABI::Microsoft::Internal::ToastNotifications::NotificationType BaseNotification::NotificationType()
    {
        auto lock{ m_lock.lock_shared() };
        return m_notificationType;
    }

    void BaseNotification::NotificationType(::ABI::Microsoft::Internal::ToastNotifications::NotificationType value)
    {
        auto lock{ m_lock.lock_exclusive() };
        m_notificationType = value;
    }
}
