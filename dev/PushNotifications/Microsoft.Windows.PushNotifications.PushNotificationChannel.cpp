#include "pch.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationChannel::PushNotificationChannel(hstring const& uri, Windows::Foundation::DateTime const& expiration)
    {
        throw hresult_not_implemented();
    }
    hstring PushNotificationChannel::Uri()
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::DateTime PushNotificationChannel::ExpirationTime()
    {
        throw hresult_not_implemented();
    }
    void PushNotificationChannel::Close()
    {
        throw hresult_not_implemented();
    }
}
