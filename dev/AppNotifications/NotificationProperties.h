// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <frameworkUdk/ToastNotificationsRT.h>

struct NotificationProperties : winrt::implements<NotificationProperties, ::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties>
{
    NotificationProperties(winrt::Microsoft::Windows::AppNotifications::AppNotification const& toastNotification);

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

    winrt::com_ptr<ABI::Microsoft::Internal::ToastNotifications::IToastProgressData> m_toastProgressData;
};
