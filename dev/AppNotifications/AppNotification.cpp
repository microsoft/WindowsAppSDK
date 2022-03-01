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
        return m_tag;
    }

    void AppNotification::Tag(hstring const& tag)
    {
        m_tag = tag;
    }

    hstring AppNotification::Group()
    {
        return m_group;
    }

    void AppNotification::Group(hstring const& group)
    {
        m_group = group;
    }

    uint32_t AppNotification::Id()
    {
        return m_notificationId;
    }

    hstring AppNotification::Payload()
    {
        return m_payload;
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData AppNotification::Progress()
    {
        return m_progressData;
    }

    void AppNotification::Progress(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const& progressData)
    {
        m_progressData = progressData;
    }

    winrt::Windows::Foundation::DateTime AppNotification::Expiration()
    {
        return m_expirationTime;
    }

    void AppNotification::Expiration(winrt::Windows::Foundation::DateTime const& expirationTime)
    {
        m_expirationTime = expirationTime;
    }

    bool AppNotification::ExpiresOnReboot()
    {
        return m_expiresOnReboot;
    }

    void AppNotification::ExpiresOnReboot(bool expiresOnReboot)
    {
        m_expiresOnReboot = expiresOnReboot;
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority AppNotification::Priority()
    {
        return m_priority;
    }

    void AppNotification::Priority(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority const& priority)
    {
        m_priority = priority;
    }

    bool AppNotification::SuppressDisplay()
    {
        return m_suppressDisplay;
    }

    void AppNotification::SuppressDisplay(bool suppressDisplay)
    {
        m_suppressDisplay = suppressDisplay;
    }

    void AppNotification::SetNotificationId(uint32_t id)
    {
        m_notificationId = id;
    }
}
