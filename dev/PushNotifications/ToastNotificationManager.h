#pragma once
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct ToastNotificationManager
    {
        ToastNotificationManager() = default;

        static void RegisterActivator(winrt::guid const& taskClsid);
        static void UnRegisterActivator();
        static winrt::event_token ToastActivated(winrt::Windows::Foundation::EventHandler<Microsoft::Windows::PushNotifications::ToastActivatedEventArgs> handler);
        static void ToastActivated(winrt::event_token const& token) noexcept;

    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct ToastNotificationManager : ToastNotificationManagerT<ToastNotificationManager, implementation::ToastNotificationManager>
    {
    };
}
