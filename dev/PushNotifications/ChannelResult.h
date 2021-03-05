// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ChannelResult.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct ChannelResult : ChannelResultT<ChannelResult>
    {
        ChannelResult() = default;

        ChannelResult(Windows::Networking::PushNotifications::PushNotificationChannel const channel, winrt::hresult const extendedError, Microsoft::ProjectReunion::ChannelStatus const status);
        Windows::Networking::PushNotifications::PushNotificationChannel Channel();
        winrt::hresult ExtendedError();
        Microsoft::ProjectReunion::ChannelStatus Status();

    private:
        Windows::Networking::PushNotifications::PushNotificationChannel m_channel{ nullptr };
        winrt::hresult m_extendedError;
        ChannelStatus m_channelStatus{};
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct ChannelResult : ChannelResultT<ChannelResult, implementation::ChannelResult>
    {
    };
}
