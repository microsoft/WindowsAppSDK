#pragma once
#include "PushNotificationCreateChannelResult.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult>
    {
        PushNotificationCreateChannelResult() = default;

        PushNotificationCreateChannelResult(Microsoft::ProjectReunion::PushNotificationChannel const& channel, hresult const& extendedError, Microsoft::ProjectReunion::PushNotificationChannelStatus const& status);
        Microsoft::ProjectReunion::PushNotificationChannel Channel();
        winrt::hresult ExtendedError();
        Microsoft::ProjectReunion::PushNotificationChannelStatus Status();

    private:
        Microsoft::ProjectReunion::PushNotificationChannel m_channel{ nullptr };
        winrt::hresult m_extendedError;
        Microsoft::ProjectReunion::PushNotificationChannelStatus m_status;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult, implementation::PushNotificationCreateChannelResult>
    {
    };
}
