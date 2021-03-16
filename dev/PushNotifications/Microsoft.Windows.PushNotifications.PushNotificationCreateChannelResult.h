#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult.g.h"


namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult>
    {
        PushNotificationCreateChannelResult() = default;

        PushNotificationCreateChannelResult(Microsoft::Windows::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::Windows::PushNotifications::PushNotificationChannelStatus const& status);
        Microsoft::Windows::PushNotifications::PushNotificationChannel Channel();
        winrt::hresult ExtendedError();
        Microsoft::Windows::PushNotifications::PushNotificationChannelStatus Status();
        void PushNotificationCreateChannelUpdate(Microsoft::Windows::PushNotifications::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::Windows::PushNotifications::PushNotificationChannelStatus const& status);
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult, implementation::PushNotificationCreateChannelResult>
    {
    };
}
