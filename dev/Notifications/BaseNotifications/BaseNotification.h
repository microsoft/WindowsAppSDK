// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <wil/resource.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include <frameworkUdk/ToastNotificationsRT.h>

namespace Microsoft::Windows::BaseNotifications {
    struct BaseNotification
    {
        BaseNotification() = default;

        BaseNotification(winrt::hstring const& payload);
        winrt::hstring Tag();
        void Tag(winrt::hstring const& value);
        winrt::hstring Group();
        void Group(winrt::hstring const& value);
        uint32_t Id();
        void Id(uint32_t id);
        winrt::hstring Payload() ;
        winrt::Windows::Foundation::DateTime Expiration();
        void Expiration(winrt::Windows::Foundation::DateTime const& value);
        bool ExpiresOnReboot();
        void ExpiresOnReboot(bool value);
        winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority Priority();
        void Priority(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority const& value);
        bool SuppressDisplay();
        void SuppressDisplay(bool value);
        ::ABI::Microsoft::Internal::ToastNotifications::NotificationType NotificationType() ;
        void NotificationType(::ABI::Microsoft::Internal::ToastNotifications::NotificationType value);

    protected:
        winrt::hstring m_tag{};
        winrt::hstring m_group{};
        uint32_t m_notificationId{ 0 };
        winrt::hstring m_payload{};
        winrt::Windows::Foundation::DateTime m_expirationTime{};
        bool m_expiresOnReboot{ false };
        winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority m_priority
        { winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority::Default };
        ::ABI::Microsoft::Internal::ToastNotifications::NotificationType m_notificationType;
        bool m_suppressDisplay{ false };

        wil::srwlock m_lock;
    };
}
