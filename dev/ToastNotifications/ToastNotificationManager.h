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

        winrt::Windows::Foundation::IAsyncAction RemoveWithIdentifierAsync(uint32_t toastIdentifier);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagAsync(hstring tag);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagGroupAsync(hstring tag, hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveGroupAsync(hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveAllAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ToastNotifications::ToastNotification>> GetAllAsync();

        winrt::Windows::Data::Xml::Dom::XmlDocument GetXmlTemplateContent(winrt::Microsoft::Windows::ToastNotifications::ToastTemplateType const& type);
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastNotificationManager : ToastNotificationManagerT<ToastNotificationManager, implementation::ToastNotificationManager>
    {
    };
}
