#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationManager.g.h"

typedef winrt::Windows::Foundation::TypedEventHandler<
    winrt::Microsoft::Windows::AppNotifications::AppNotificationManager,
    winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs> NotificationActivationEventHandler;

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    class IAppNotificationManagerInternal
    {
    public:
        virtual void InvokeHandler(const AppNotificationActivatedEventArgs& args) = 0;
        virtual bool ContainsInvokeHandler() = 0;
    };

    struct AppNotificationManager : AppNotificationManagerT<AppNotificationManager, IAppNotificationManagerInternal>
    {
        AppNotificationManager() = default;

        static winrt::Microsoft::Windows::AppNotifications::AppNotificationManager Default();
        void Register();
        void Register(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivationInfo const& details);
        void Unregister();
        void UnregisterAll();
        winrt::event_token NotificationInvoked(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::AppNotifications::AppNotificationManager, winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs> const& handler);
        void NotificationInvoked(winrt::event_token const& token) noexcept;
        void Show(winrt::Microsoft::Windows::AppNotifications::AppNotification const& notification);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> UpdateAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag, hstring const group);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> UpdateAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag);
        winrt::Microsoft::Windows::AppNotifications::AppNotificationSetting Setting();
        winrt::Windows::Foundation::IAsyncAction RemoveByIdAsync(uint32_t notificationId);
        winrt::Windows::Foundation::IAsyncAction RemoveByTagAsync(hstring tag);
        winrt::Windows::Foundation::IAsyncAction RemoveByTagAndGroupAsync(hstring tag, hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveByGroupAsync(hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveAllAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::AppNotifications::AppNotification>> GetAllAsync();

        // IAppNotificationManagerInternal
        bool ContainsInvokeHandler();
        void InvokeHandler(const winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs& args);

    private:
        wil::unique_com_class_object_cookie m_notificationComActivatorRegistration;
        wil::srwlock m_registrationLock;
        winrt::event<NotificationActivationEventHandler> m_notificationHandlers;
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationManager : AppNotificationManagerT<AppNotificationManager, implementation::AppNotificationManager>
    {
    };
}
