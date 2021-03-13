#pragma once
#include "PushNotificationChannel.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel>
    {
        PushNotificationChannel() = default;

        PushNotificationChannel(hstring const& uri, Windows::Foundation::DateTime const& expiration);
        hstring Uri();
        Windows::Foundation::DateTime ExpirationTime();
        void Close();

    private:
        hstring m_uri;
        Windows::Foundation::DateTime m_expiration;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationChannel : PushNotificationChannelT<PushNotificationChannel, implementation::PushNotificationChannel>
    {
    };
}
