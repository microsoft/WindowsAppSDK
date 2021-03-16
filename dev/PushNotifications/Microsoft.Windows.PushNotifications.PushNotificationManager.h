#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationManager
    {
        PushNotificationManager() = default;

        static Windows::Foundation::IAsyncOperationWithProgress<Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid remoteId);
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
