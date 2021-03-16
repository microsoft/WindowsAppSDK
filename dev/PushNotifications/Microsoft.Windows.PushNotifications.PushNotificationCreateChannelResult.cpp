#include "pch.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult.g.cpp"


namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationCreateChannelResult::PushNotificationCreateChannelResult(Microsoft::Windows::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::Windows::PushNotifications::PushNotificationChannelStatus const& status)
    {
        throw hresult_not_implemented();
    }
    Microsoft::Windows::PushNotifications::PushNotificationChannel PushNotificationCreateChannelResult::Channel()
    {
        throw hresult_not_implemented();
    }
    winrt::hresult PushNotificationCreateChannelResult::ExtendedError()
    {
        throw hresult_not_implemented();
    }
    Microsoft::Windows::PushNotifications::PushNotificationChannelStatus PushNotificationCreateChannelResult::Status()
    {
        throw hresult_not_implemented();
    }
    void PushNotificationCreateChannelResult::PushNotificationCreateChannelUpdate(Microsoft::Windows::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::Windows::PushNotifications::PushNotificationChannelStatus const& status)
    {
        throw hresult_not_implemented();
    }
}
