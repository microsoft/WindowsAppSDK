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

        PushNotificationReceivedEventArgs(std::wstring& payload);

        PushNotificationReceivedEventArgs(byte* const& payload, ULONG const& length);


        com_array<uint8_t> Payload();
        winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral();
        winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
        void Canceled(winrt::event_token const& token) noexcept;
        bool Handled();
        void Handled(bool value);

    private:
        std::string Utf16ToUtf8(_In_z_ const wchar_t* utf16);

        std::string m_rawNotificationFromProtocol;
        const winrt::Windows::Storage::Streams::IBuffer m_rawNotification{};

        std::vector<uint8_t> BuildPayload(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        std::vector<uint8_t> BuildPayload(byte* const& payload, ULONG const& length);

        std::vector<uint8_t> m_rawNotificationPayload;

        const winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance m_backgroundTaskInstance{};
        const winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs m_args = nullptr;

        bool m_unpackagedAppScenario;
        bool m_handledUnpackaged = true;
    };
}
