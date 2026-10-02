// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <frameworkUdk/ToastNotificationsRT.h>
#include "BadgeNotification.h"

struct NotificationTransientProperties : winrt::implements<NotificationTransientProperties, ::ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties>
{
    NotificationTransientProperties(winrt::Microsoft::Windows::AppNotifications::AppNotification const& toastNotification) noexcept;

    NotificationTransientProperties(Microsoft::Windows::BadgeNotifications::BadgeNotification &badgeNotification) noexcept;

    STDMETHOD(get_OfflineCacheCount)(_Out_ unsigned long long* offlineCacheCount) noexcept;

    STDMETHOD(get_OfflineBundleId)(_Out_ HSTRING* offlineBundleId) noexcept;

    STDMETHOD(get_ServerCacheRollover)(_Out_ boolean* serverCacheRollover) noexcept;

    STDMETHOD(get_SuppressPopup)(_Out_ boolean* suppressPopup) noexcept;

    STDMETHOD(get_RecurrenceId)(_Out_ GUID* recurrenceId) noexcept;

    STDMETHOD(get_MessageId)(_Out_ GUID* messageId) noexcept;

    STDMETHOD(get_ToastNotificationPriority)(_Out_::ABI::Microsoft::Internal::ToastNotifications::ToastNotificationPriority* priority) noexcept;

    STDMETHOD(get_CorrelationVector)(_Out_ HSTRING* correlationVector) noexcept;

private:
    wil::srwlock m_lock;

    boolean m_suppressPopup = false;

    ::ABI::Microsoft::Internal::ToastNotifications::ToastNotificationPriority m_toastNotificationPriority =
        ::ABI::Microsoft::Internal::ToastNotifications::ToastNotificationPriority::ToastNotificationPriority_Default;
};
