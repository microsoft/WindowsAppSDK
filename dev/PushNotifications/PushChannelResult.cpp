#include "pch.h"
#include "PushChannelResult.h"
#include "PushChannelResult.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushChannelResult::PushChannelResult(Windows::Networking::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::ProjectReunion::ChannelStatus const& status)
    {
        m_channel = channel;
        m_extendedError = extendedError;
        m_channelStatus = status;
    }
    Windows::Networking::PushNotifications::PushNotificationChannel PushChannelResult::Channel()
    {
        return m_channel;
    }
    winrt::hresult PushChannelResult::ExtendedError()
    {
        return m_extendedError;
    }
    Microsoft::ProjectReunion::ChannelStatus PushChannelResult::Status()
    {
        return m_channelStatus;
    }
}
