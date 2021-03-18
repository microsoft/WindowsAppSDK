#pragma once
#include "PushNotificationCreateChannelResult.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult>
    {
        PushNotificationCreateChannelResult() = default;

        PushNotificationCreateChannelResult(Microsoft::ProjectReunion::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::ProjectReunion::PushNotificationChannelStatus const& status);
        Microsoft::ProjectReunion::PushNotificationChannel Channel();
        winrt::hresult ExtendedError();
        Microsoft::ProjectReunion::PushNotificationChannelStatus Status();
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult, implementation::PushNotificationCreateChannelResult>
    {
    };
}
