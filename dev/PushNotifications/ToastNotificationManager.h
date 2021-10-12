#pragma once
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct ToastNotificationManager
    {
        ToastNotificationManager() = default;

        static void RegisterActivator(winrt::guid const& taskClsid);
        static void UnRegisterActivator();
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct ToastNotificationManager : ToastNotificationManagerT<ToastNotificationManager, implementation::ToastNotificationManager>
    {
    };
}
