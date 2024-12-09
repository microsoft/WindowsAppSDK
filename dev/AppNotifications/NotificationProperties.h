// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <frameworkUdk/ToastNotificationsRT.h>
#include "BadgeNotification.h"

struct NotificationProperties : winrt::implements<NotificationProperties, ::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties, ::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties2, 
    ::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties3>
{
    NotificationProperties(winrt::Microsoft::Windows::AppNotifications::AppNotification const& toastNotification);

    NotificationProperties(Microsoft::Windows::BadgeNotifications::BadgeNotification &badgeNotification);

    STDMETHOD(get_NotificationId)(_Out_ unsigned int* notificationId) noexcept;

    STDMETHOD(get_Payload)(_Out_ unsigned int* payloadSize, _Out_ byte** payload) noexcept;

    STDMETHOD(get_PayloadSize)(_Out_ unsigned int* payloadSize) noexcept;

    STDMETHOD(get_Tag)(_Out_ HSTRING* tag) noexcept;

    STDMETHOD(get_Group)(_Out_ HSTRING* group) noexcept;

    STDMETHOD(get_Expiry)(_Out_ unsigned long long* expiry) noexcept;

    STDMETHOD(get_ArrivalTime)(_Out_ unsigned long long* arrivalTime) noexcept;

    STDMETHOD(get_BootId)(_Out_ unsigned long long* bootId) noexcept;

    STDMETHOD(get_ExpiresOnReboot)(_Out_ boolean* expiresOnReboot) noexcept;

    STDMETHOD(get_ToastProgressData)(_Out_ ABI::Microsoft::Internal::ToastNotifications::IToastProgressData** progressData) noexcept;

    STDMETHOD(get_ActivityId)(_Out_ GUID* activityId) noexcept;

    STDMETHOD(get_ToastConferencingConfig)(_Out_ ABI::Microsoft::Internal::ToastNotifications::IToastConferencingConfig** conferencingConfig) noexcept;

    STDMETHOD(get_NotificationType)(_Out_ ABI::Microsoft::Internal::ToastNotifications::NotificationType* notificationType) noexcept;

private:
    wil::srwlock m_lock;

    unsigned long m_notificationId = 0;

    wil::unique_cotaskmem_array_ptr<byte> m_payload;

    std::wstring m_tag;
    std::wstring m_group;

    FILETIME m_expiry;
    FILETIME m_arrivalTime;

    unsigned long long m_bootId = 0;

    bool m_expiresOnReboot = false;

    winrt::com_ptr<ABI::Microsoft::Internal::ToastNotifications::IToastProgressData> m_toastProgressData{ nullptr };
    winrt::com_ptr<ABI::Microsoft::Internal::ToastNotifications::IToastConferencingConfig> m_toastConferencingConfig{ nullptr };

    ABI::Microsoft::Internal::ToastNotifications::NotificationType m_notificationType;
};
