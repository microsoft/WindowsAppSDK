#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationManager.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationManager : AppNotificationManagerT<AppNotificationManager>
    {
        AppNotificationManager() = default;

        static winrt::Microsoft::Windows::AppNotifications::AppNotificationManager Default();
        void Register(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivationInfo const& details);
        void Unregister();
        winrt::event_token AppNotificationActivated(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::AppNotifications::AppNotificationManager, winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs> const& handler);
        void AppNotificationActivated(winrt::event_token const& token) noexcept;
        void Show(winrt::Microsoft::Windows::AppNotifications::AppNotification const& notification);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> UpdateProgressDataAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag, hstring const group);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> UpdateProgressDataAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag);
        winrt::Microsoft::Windows::AppNotifications::AppNotificationSetting Enablement();
        winrt::Windows::Foundation::IAsyncAction RemoveByIdAsync(uint32_t notificationId);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagAsync(hstring tag);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagGroupAsync(hstring tag, hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveGroupAsync(hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveAllAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::AppNotifications::AppNotification>> GetAllAsync();
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationManager : AppNotificationManagerT<AppNotificationManager, implementation::AppNotificationManager>
    {
    };
}
