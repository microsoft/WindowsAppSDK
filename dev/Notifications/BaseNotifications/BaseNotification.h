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
        winrt::hstring Tag() const noexcept;
        void Tag(winrt::hstring const& value);
        winrt::hstring Group() const noexcept;
        void Group(winrt::hstring const& value);
        uint32_t Id() const noexcept;
        void Id(uint32_t id);
        winrt::hstring Payload() const noexcept;
        winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData Progress() const noexcept;
        void Progress(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const& value);
        winrt::Windows::Foundation::DateTime Expiration() const noexcept;
        void Expiration(winrt::Windows::Foundation::DateTime const& value);
        bool ExpiresOnReboot() const noexcept;
        void ExpiresOnReboot(bool value);
        winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority Priority() const noexcept;
        void Priority(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority const& value);
        bool SuppressDisplay() const noexcept;
        void SuppressDisplay(bool value);
        ::ABI::Microsoft::Internal::ToastNotifications::NotificationType NotificationType() const noexcept;
        void NotificationType(::ABI::Microsoft::Internal::ToastNotifications::NotificationType value);

    protected:
        winrt::hstring m_tag{};
        winrt::hstring m_group{};
        uint32_t m_notificationId{ 0 };
        winrt::hstring m_payload{};
        winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData m_progressData{ nullptr };
        winrt::Windows::Foundation::DateTime m_expirationTime{};
        bool m_expiresOnReboot{ false };
        winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority m_priority
        { winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority::Default };
        ::ABI::Microsoft::Internal::ToastNotifications::NotificationType m_notificationType;
        bool m_suppressDisplay{ false };

        wil::srwlock m_lock;
    };
}
