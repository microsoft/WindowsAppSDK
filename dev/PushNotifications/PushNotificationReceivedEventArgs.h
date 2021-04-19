#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationReceivedEventArgs : PushNotificationReceivedEventArgsT<PushNotificationReceivedEventArgs>
    {
        PushNotificationReceivedEventArgs(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        PushNotificationReceivedEventArgs(winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args);

        static Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs CreateFromBackgroundTaskInstance(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        static Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs CreateFromPushNotificationReceivedEventArgs(winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args);
        winrt::com_array<uint8_t> Payload();
        winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral();
        winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
        void Canceled(winrt::event_token const& token) noexcept;
        bool Handled();
        void Handled(bool value);

    private:
        bool m_handled = false;
        winrt::com_array<uint8_t> m_payload{};
        winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance m_backgroundTaskInstance = nullptr;
        winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs m_args = nullptr;
        wil::critical_section m_lock;
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationReceivedEventArgs : PushNotificationReceivedEventArgsT<PushNotificationReceivedEventArgs, implementation::PushNotificationReceivedEventArgs>
    {
    };
}
