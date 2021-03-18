#include "pch.h"
#include "PushNotificationCreateChannelResult.h"
#include "PushNotificationCreateChannelResult.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushNotificationCreateChannelResult::PushNotificationCreateChannelResult(Microsoft::ProjectReunion::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::ProjectReunion::PushNotificationChannelStatus const& status)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ProjectReunion::PushNotificationChannel PushNotificationCreateChannelResult::Channel()
    {
        throw hresult_not_implemented();
    }
    winrt::hresult PushNotificationCreateChannelResult::ExtendedError()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ProjectReunion::PushNotificationChannelStatus PushNotificationCreateChannelResult::Status()
    {
        throw hresult_not_implemented();
    }
}
