// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ChannelResult.h"
#include "ChannelResult.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    ChannelResult::ChannelResult(Windows::Networking::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::ProjectReunion::ChannelStatus const& status)
    {
        throw hresult_not_implemented();
    }
    Windows::Networking::PushNotifications::PushNotificationChannel ChannelResult::Channel()
    {
        throw hresult_not_implemented();
    }
    winrt::hresult ChannelResult::ExtendedError()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ProjectReunion::ChannelStatus ChannelResult::Status()
    {
        throw hresult_not_implemented();
    }
}
