#include "pch.h"
#include "PushNotificationChannel.h"
#include "PushNotificationChannel.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushNotificationChannel::PushNotificationChannel(hstring const& uri, Windows::Foundation::DateTime const& expiration)
    {
        m_uri = uri;
        m_expiration = expiration;
    }
    hstring PushNotificationChannel::Uri()
    {
        return m_uri;
    }
    Windows::Foundation::DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_expiration;
    }
    void PushNotificationChannel::Close()
    {
        throw hresult_not_implemented();
    }
}
