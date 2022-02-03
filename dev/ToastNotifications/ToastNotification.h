#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastNotification.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastNotification : ToastNotificationT<ToastNotification>
    {
        ToastNotification() = default;

        ToastNotification(winrt::Windows::Data::Xml::Dom::XmlDocument const& payload);
        hstring Tag();
        void Tag(hstring const& value);
        hstring Group();
        void Group(hstring const& value);
        uint32_t ToastId();
        void ToastId(uint32_t value);
        winrt::Windows::Data::Xml::Dom::XmlDocument Payload();
        winrt::Microsoft::Windows::ToastNotifications::ToastProgressData ProgressData();
        void ProgressData(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData const& value);
        winrt::Windows::Foundation::DateTime ExpirationTime();
        void ExpirationTime(winrt::Windows::Foundation::DateTime const& value);
        bool ExpiresOnReboot();
        void ExpiresOnReboot(bool value);
        winrt::Microsoft::Windows::ToastNotifications::ToastPriority Priority();
        void Priority(winrt::Microsoft::Windows::ToastNotifications::ToastPriority const& value);
        bool SuppressDisplay();
        void SuppressDisplay(bool value);

    private:
        winrt::hstring m_tag{};

        winrt::hstring m_group{};

        uint32_t m_toastId{ 0 };

        winrt::Windows::Data::Xml::Dom::XmlDocument m_payload{};

        winrt::Microsoft::Windows::ToastNotifications::ToastProgressData m_progressData{};

        winrt::Windows::Foundation::DateTime m_expirationTime{};

        bool m_expiresOnReboot{ false };

        winrt::Microsoft::Windows::ToastNotifications::ToastPriority m_priority
            { winrt::Microsoft::Windows::ToastNotifications::ToastPriority::Default };

        bool m_suppressDisplay{ false };
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastNotification : ToastNotificationT<ToastNotification, implementation::ToastNotification>
    {
    };
}
