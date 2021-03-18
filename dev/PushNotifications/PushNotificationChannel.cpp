#include "pch.h"
#include "PushNotificationChannel.h"
#include "PushNotificationChannel.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
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
    winrt::event_token PushNotificationChannel::PushReceived(Windows::Foundation::TypedEventHandler<Microsoft::ProjectReunion::PushNotificationChannel, Microsoft::ProjectReunion::PushNotificationReceivedEventArgs> const& handler)
    {
        throw hresult_not_implemented();
    }
    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        throw hresult_not_implemented();
    }
}
