// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.h"
#include <NotificationsLongRunningProcess_h.h>
#include <winrt\Windows.Networking.PushNotifications.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationReceivedEventArgs : PushNotificationReceivedEventArgsT<PushNotificationReceivedEventArgs>
    {
        PushNotificationReceivedEventArgs() = delete;

        PushNotificationReceivedEventArgs(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        PushNotificationReceivedEventArgs(byte* const& payload, ULONG const& length);

        com_array<uint8_t> Payload();
        winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral GetDeferral();
        winrt::event_token Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
        void Canceled(winrt::event_token const& token) noexcept;

    private:
        std::vector<uint8_t> BuildPayload(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        std::vector<uint8_t> BuildPayload(byte* const& payload, ULONG const& length);

        std::vector<uint8_t> m_rawNotificationPayload;
        const winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance m_backgroundTaskInstance{};
        bool m_isForegroundActivation;
    };
}
