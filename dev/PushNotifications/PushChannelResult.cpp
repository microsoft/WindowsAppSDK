#include "pch.h"
#include "PushChannelResult.h"
#include "PushChannelResult.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushChannelResult::PushChannelResult(Windows::Networking::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::ProjectReunion::ChannelStatus const& status)
    {
        throw hresult_not_implemented();
    }
    Windows::Networking::PushNotifications::PushNotificationChannel PushChannelResult::Channel()
    {
        throw hresult_not_implemented();
    }
    winrt::hresult PushChannelResult::ExtendedError()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ProjectReunion::ChannelStatus PushChannelResult::Status()
    {
        throw hresult_not_implemented();
    }
}
