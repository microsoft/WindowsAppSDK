#include "pch.h"
#include "PushNotificationCreateChannelResult.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult.g.cpp"

namespace ReunionPushNotifications = winrt::Microsoft::Windows::PushNotifications;

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationCreateChannelResult::PushNotificationCreateChannelResult(ReunionPushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, ReunionPushNotifications::PushNotificationChannelStatus const& status)
    {
        m_channel = channel;
        m_extendedError = extendedError;
        m_status = status;
    }
    ReunionPushNotifications::PushNotificationChannel PushNotificationCreateChannelResult::Channel()
    {
        return m_channel;
    }
    winrt::hresult PushNotificationCreateChannelResult::ExtendedError()
    {
        return m_extendedError;
    }
    ReunionPushNotifications::PushNotificationChannelStatus PushNotificationCreateChannelResult::Status()
    {
        return m_status;
    }
}
