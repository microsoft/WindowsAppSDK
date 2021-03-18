#include "pch.h"

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>

#include "PushNotificationReceivedEventArgs.h"
#include "PushNotificationReceivedEventArgs.g.cpp"

using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Networking::PushNotifications;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::mutex PushNotificationReceivedEventArgs::s_mutex;
    std::unique_lock<std::mutex> PushNotificationReceivedEventArgs::s_lock(s_mutex, std::defer_lock);

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask)
    {
        m_backgroundTaskInstance = backgroundTask;

        // Extract payload
        auto triggerDetails = m_backgroundTaskInstance.TriggerDetails();
        RawNotification rawNotification = triggerDetails.as<RawNotification>();

        IBuffer rawContentAsBuffer = rawNotification.ContentBytes();
        DataReader dataReader = DataReader::FromBuffer(rawContentAsBuffer);

        m_payload = winrt::com_array<uint8_t>(rawContentAsBuffer.Length());
        dataReader.ReadBytes(m_payload);
    }

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args)
    {
        m_handled = args.Cancel();

        // Extract payload
        RawNotification rawNotification = args.RawNotification();

        IBuffer rawContentAsBuffer = rawNotification.ContentBytes();
        DataReader dataReader = DataReader::FromBuffer(rawContentAsBuffer);

        m_payload = winrt::com_array<uint8_t>(rawContentAsBuffer.Length());
        dataReader.ReadBytes(m_payload);
    }

    Microsoft::ProjectReunion::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(backgroundTask);
    }

    Microsoft::ProjectReunion::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(Windows::Networking::PushNotifications::PushNotificationReceivedEventArgs const& args)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(args);
    }

    com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        s_lock.lock();
        return winrt::com_array<uint8_t>(m_payload.begin(), m_payload.end());
    }
    Windows::ApplicationModel::Background::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        s_lock.lock();
        throw hresult_not_implemented();
    }
    winrt::event_token PushNotificationReceivedEventArgs::Canceled(Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler)
    {
        if (m_backgroundTaskInstance != nullptr)
        {
            return m_backgroundTaskInstance.Canceled(handler);
        }

        return winrt::event_token{};
    }
    void PushNotificationReceivedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
        if (m_backgroundTaskInstance != nullptr)
        {
            return m_backgroundTaskInstance.Canceled(token);
        }
    }
    bool PushNotificationReceivedEventArgs::Handled()
    {
        s_lock.lock();
        return m_handled;
    }
    void PushNotificationReceivedEventArgs::Handled(bool value)
    {
        s_lock.lock();
        m_handled = value;
    }
}
