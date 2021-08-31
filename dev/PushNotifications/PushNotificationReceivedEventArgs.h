#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.h"
#include <NotificationsLongRunningProcess_h.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationReceivedEventArgs : PushNotificationReceivedEventArgsT<PushNotificationReceivedEventArgs>
    {
        PushNotificationReceivedEventArgs() = delete;

        PushNotificationReceivedEventArgs(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        PushNotificationReceivedEventArgs(winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args);
        PushNotificationReceivedEventArgs(byte* payload, ULONG length);

        com_array<uint8_t> Payload();
        winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral();
        winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
        void Canceled(winrt::event_token const& token) noexcept;
        bool Handled();
        void Handled(bool value);

        std::vector<byte> BuildPayload(uint8_t* payload, ULONG payloadLength);

    private:

        std::vector<byte> m_rawNotificationPayload;

        const winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance m_backgroundTaskInstance{};
        const winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs m_args = nullptr;

        bool m_isUnpackagedApp;
        bool m_handledUnpackaged = false;
    };
}
