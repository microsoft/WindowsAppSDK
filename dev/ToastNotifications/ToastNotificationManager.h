#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastNotificationManager.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastNotificationManager : ToastNotificationManagerT<ToastNotificationManager>
    {
        ToastNotificationManager() = default;

        static winrt::Microsoft::Windows::ToastNotifications::ToastNotificationManager Default();

        void RegisterActivator(winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo const& details);

        void UnregisterActivator();

        winrt::event_token ToastActivated(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs> const& handler);

        void ToastActivated(winrt::event_token const& token);

        void ShowToast(winrt::Microsoft::Windows::ToastNotifications::ToastNotification const& toast);

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::ToastNotifications::ToastProgressResult> UpdateToastProgressDataAsync(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData const data, hstring const tag, hstring const group);

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::ToastNotifications::ToastProgressResult> UpdateToastProgressDataAsync(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData const data, hstring const tag);

        winrt::Microsoft::Windows::ToastNotifications::ToastNotificationSetting Setting();

        winrt::Microsoft::Windows::ToastNotifications::ToastNotificationHistory History();

        winrt::Windows::Data::Xml::Dom::XmlDocument GetXmlTemplateContent(winrt::Microsoft::Windows::ToastNotifications::ToastTemplateType const& type);
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastNotificationManager : ToastNotificationManagerT<ToastNotificationManager, implementation::ToastNotificationManager>
    {
    };
}
