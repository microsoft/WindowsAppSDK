#include "pch.h"

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>

#include "PushNotificationReceivedEventArgs.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.cpp"

using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Networking::PushNotifications;

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask)
    {
        m_backgroundTaskInstance = backgroundTask;
    }

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args)
    {
        m_handled = args.Cancel();
        m_args = args;
    }

    Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(backgroundTask);
    }

    Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(winrt::Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(args);
    }

    winrt::com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        auto lock = m_lock.lock();
        return winrt::com_array<uint8_t>(m_payload.begin(), m_payload.end());
    }

    winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        auto lock = m_lock.lock();
        return m_backgroundTaskInstance.GetDeferral();
    }

    winrt::event_token PushNotificationReceivedEventArgs::Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler)
    {
        {
            auto lock = m_lock.lock();
            if (m_backgroundTaskInstance != nullptr)
            {
                return m_backgroundTaskInstance.Canceled(handler);
            }
        }

        return winrt::event_token{};
    }
    void PushNotificationReceivedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
        auto lock = m_lock.lock();
        if (m_backgroundTaskInstance != nullptr)
        {
            return m_backgroundTaskInstance.Canceled(token);
        }
    }
    bool PushNotificationReceivedEventArgs::Handled()
    {
        auto lock = m_lock.lock();
        return m_handled;
    }
    void PushNotificationReceivedEventArgs::Handled(bool value)
    {
        auto lock = m_lock.lock();
        m_handled = value;
        m_args.Cancel(m_handled);
    }
}
