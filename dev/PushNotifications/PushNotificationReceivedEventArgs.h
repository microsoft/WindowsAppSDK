#pragma once
#include "PushNotificationReceivedEventArgs.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationReceivedEventArgs : PushNotificationReceivedEventArgsT<PushNotificationReceivedEventArgs>
    {
        PushNotificationReceivedEventArgs(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        PushNotificationReceivedEventArgs(Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args);

        static Microsoft::ProjectReunion::PushNotificationReceivedEventArgs CreateFromBackgroundTaskInstance(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        static Microsoft::ProjectReunion::PushNotificationReceivedEventArgs CreateFromPushNotificationReceivedEventArgs(Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args);
        com_array<uint8_t> Payload();
        Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral();
        winrt::event_token Canceled(Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
        void Canceled(winrt::event_token const& token) noexcept;
        bool Handled();
        void Handled(bool value);

        private:
            bool m_handled = false;
            winrt::com_array<uint8_t> m_payload{};
            winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance m_backgroundTaskInstance = nullptr;

            static std::mutex s_mutex;
            static std::unique_lock<std::mutex> s_lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationReceivedEventArgs : PushNotificationReceivedEventArgsT<PushNotificationReceivedEventArgs, implementation::PushNotificationReceivedEventArgs>
    {
    };
}
