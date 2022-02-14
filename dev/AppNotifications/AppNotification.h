#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotification.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    class IAppNotificationInternal
    {
    public:
        virtual void SetNotificationId(uint32_t id) = 0;
    };

    struct AppNotification : AppNotificationT<AppNotification, IAppNotificationInternal>
    {
        AppNotification() = default;

        AppNotification(hstring const& payload);
        hstring Tag();
        void Tag(hstring const& value);
        hstring Group();
        void Group(hstring const& value);
        uint32_t Id();
        hstring Payload();
        winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData Progress();
        void Progress(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const& value);
        winrt::Windows::Foundation::DateTime Expiration();
        void Expiration(winrt::Windows::Foundation::DateTime const& value);
        bool ExpiresOnReboot();
        void ExpiresOnReboot(bool value);
        winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority Priority();
        void Priority(winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority const& value);
        bool SuppressDisplay();
        void SuppressDisplay(bool value);

        // IAppNotificationInternal
        void SetNotificationId(uint32_t id);

    private:
        winrt::hstring m_tag{};

        winrt::hstring m_group{};

        uint32_t m_notificationId{ 0 };

        winrt::hstring m_payload{};

        winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData m_progressData{};

        winrt::Windows::Foundation::DateTime m_expirationTime{};

        bool m_expiresOnReboot{ false };

        winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority m_priority
        { winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority::Default };

        bool m_suppressDisplay{ false };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotification : AppNotificationT<AppNotification, implementation::AppNotification>
    {
    };
}
