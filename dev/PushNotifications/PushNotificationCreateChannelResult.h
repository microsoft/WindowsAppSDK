#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult>
    {
        PushNotificationCreateChannelResult() = default;

        PushNotificationCreateChannelResult(winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel const& channel, hresult const& extendedError, winrt::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus const& status);
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel Channel();
        winrt::hresult ExtendedError();
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus Status();

    private:
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel m_channel{ nullptr };
        winrt::hresult m_extendedError;
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus m_status;
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationCreateChannelResult : PushNotificationCreateChannelResultT<PushNotificationCreateChannelResult, implementation::PushNotificationCreateChannelResult>
    {
    };
}
