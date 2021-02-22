#pragma once
#include "PushChannelResult.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushChannelResult : PushChannelResultT<PushChannelResult>
    {
        PushChannelResult() = default;

        PushChannelResult(Windows::Networking::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::ProjectReunion::ChannelStatus const& status);
        Windows::Networking::PushNotifications::PushNotificationChannel Channel();
        winrt::hresult ExtendedError();
        Microsoft::ProjectReunion::ChannelStatus Status();
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushChannelResult : PushChannelResultT<PushChannelResult, implementation::PushChannelResult>
    {
    };
}
