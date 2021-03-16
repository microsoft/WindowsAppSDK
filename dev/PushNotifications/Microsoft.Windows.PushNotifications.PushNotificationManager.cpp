#include "pch.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.cpp"


namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> PushNotificationManager::CreateChannelAsync(winrt::guid remoteId)
    {
        throw hresult_not_implemented();
    }
}
