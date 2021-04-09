#include "pch.h"
#include "PushNotificationCreateChannelResult.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult.g.cpp"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationCreateChannelResult::PushNotificationCreateChannelResult(winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, winrt::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus const& status)
    {
        m_channel = channel;
        m_extendedError = extendedError;
        m_status = status;
    }
    winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel PushNotificationCreateChannelResult::Channel()
    {
        return m_channel;
    }
    winrt::hresult PushNotificationCreateChannelResult::ExtendedError()
    {
        return m_extendedError;
    }
    winrt::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus PushNotificationCreateChannelResult::Status()
    {
        return m_status;
    }
}
