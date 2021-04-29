#include "pch.h"

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>

#include "PushNotificationReceivedEventArgs.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.cpp"
#include <iostream>

namespace ReunionPushNotifications = winrt::Microsoft::Windows::PushNotifications;

namespace winrt
{
    using namespace Windows::ApplicationModel::Background;
    using namespace Windows::Storage::Streams;
    using namespace Windows::Networking::PushNotifications;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::IBackgroundTaskInstance const& backgroundTask)
    {
        m_backgroundTaskInstance = backgroundTask;

        // Need to process the RawNotification payload here because TriggerDetails is set to nullptr leaving IBackgroundTaskInstance::Run 
        auto triggerDetails = m_backgroundTaskInstance.TriggerDetails();
        RawNotification rawNotification = triggerDetails.as<RawNotification>();

        IBuffer rawContentAsBuffer = rawNotification.ContentBytes();
        DataReader dataReader = DataReader::FromBuffer(rawContentAsBuffer);

        m_backgroundPayload = winrt::com_array<uint8_t>(rawContentAsBuffer.Length());
        dataReader.ReadBytes(m_backgroundPayload);
    }

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::PushNotificationReceivedEventArgs const& args)
    {
        m_args = args;
    }

    ReunionPushNotifications::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(winrt::IBackgroundTaskInstance const& backgroundTask)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(backgroundTask);
    }

    ReunionPushNotifications::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(winrt::PushNotificationReceivedEventArgs const& args)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(args);
    }

    winrt::com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        auto lock = m_lock.lock_shared();
        winrt::com_array<uint8_t> payload{};
        if (m_args)
        {
            RawNotification rawNotification = m_args.RawNotification();

            IBuffer rawContentAsBuffer = rawNotification.ContentBytes();
            DataReader dataReader = DataReader::FromBuffer(rawContentAsBuffer);

            payload = winrt::com_array<uint8_t>(rawContentAsBuffer.Length());
            dataReader.ReadBytes(payload);
        }
        else if (m_backgroundTaskInstance)
        {
            return winrt::com_array<uint8_t>(m_backgroundPayload.begin(), m_backgroundPayload.end());
        }
        return payload;
    }

    winrt::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        auto lock = m_lock.lock_shared();
        if (m_backgroundTaskInstance != nullptr)
        {
            return m_backgroundTaskInstance.GetDeferral();
        }
        return nullptr;
    }

    winrt::event_token PushNotificationReceivedEventArgs::Canceled(winrt::BackgroundTaskCanceledEventHandler const& handler)
    {
        {
            auto lock = m_lock.lock_exclusive();
            if (m_backgroundTaskInstance != nullptr)
            {
                return m_backgroundTaskInstance.Canceled(handler);
            }
        }

        return winrt::event_token{};
    }
    void PushNotificationReceivedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
        auto lock = m_lock.lock_exclusive();
        if (m_backgroundTaskInstance != nullptr)
        {
            m_backgroundTaskInstance.Canceled(token);
        }
    }
    bool PushNotificationReceivedEventArgs::Handled()
    {
        auto lock = m_lock.lock_shared();
        if (m_args)
        {
            return m_args.Cancel();
        }
        return false;
    }
    void PushNotificationReceivedEventArgs::Handled(bool value)
    {
        auto lock = m_lock.lock_exclusive();
        if (m_args)
        {
            m_args.Cancel(value);
        }
    }
}
