// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ChannelResult.h"
#include "ChannelResult.g.cpp"
#include <winrt\windows.networking.pushnotifications.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    ChannelResult::ChannelResult(winrt::Windows::Networking::PushNotifications::PushNotificationChannel const channel, winrt::hresult const extendedError, Microsoft::ProjectReunion::ChannelStatus const status)
    {
        m_channel = channel;
        m_extendedError = extendedError;
        m_channelStatus = status;
    }
    Windows::Networking::PushNotifications::PushNotificationChannel ChannelResult::Channel()
    {
        return m_channel;
    }
    winrt::hresult ChannelResult::ExtendedError()
    {
        return m_extendedError;
    }
    Microsoft::ProjectReunion::ChannelStatus ChannelResult::Status()
    {
        return m_channelStatus;
    }
}
