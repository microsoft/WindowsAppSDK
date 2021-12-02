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
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastNotification : ToastNotificationT<ToastNotification, implementation::ToastNotification>
    {
    };
}
