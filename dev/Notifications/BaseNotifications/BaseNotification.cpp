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

    winrt::hstring BaseNotification::Tag() const noexcept
    {
        return m_tag;
    }

    void BaseNotification::Tag(winrt::hstring const& tag)
    {
        m_tag = tag;
    }

    winrt::hstring BaseNotification::Group() const noexcept
    {
        return m_group;
    }

    void BaseNotification::Group(winrt::hstring const& group)
    {
        m_group = group;
    }

    uint32_t BaseNotification::Id() const noexcept
    {
        return m_notificationId;
    }

    winrt::hstring BaseNotification::Payload() const noexcept
    {
        return m_payload;
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData BaseNotification::Progress() const noexcept
    {
        return m_progressData;
    }

    void BaseNotification::Progress(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const& progressData)
    {
        m_progressData = progressData;
    }

    winrt::Windows::Foundation::DateTime BaseNotification::Expiration() const noexcept
    {
        return m_expirationTime;
    }

    void BaseNotification::Expiration(winrt::Windows::Foundation::DateTime const& expirationTime)
    {
        m_expirationTime = expirationTime;
    }

    bool BaseNotification::ExpiresOnReboot() const noexcept
    {
        return m_expiresOnReboot;
    }

    void BaseNotification::ExpiresOnReboot(bool expiresOnReboot)
    {
        m_expiresOnReboot = expiresOnReboot;
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority BaseNotification::Priority() const noexcept
    {
        return m_priority;
    }

    void BaseNotification::Priority(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority const& priority)
    {
        m_priority = priority;
    }

    bool BaseNotification::SuppressDisplay() const noexcept
    {
        return m_suppressDisplay;
    }

    void BaseNotification::SuppressDisplay(bool suppressDisplay)
    {
        m_suppressDisplay = suppressDisplay;
    }

    void BaseNotification::Id(uint32_t id)
    {
        m_notificationId = id;
    }
}
