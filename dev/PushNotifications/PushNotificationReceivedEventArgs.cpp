#include "pch.h"

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>

#include "PushNotificationReceivedEventArgs.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.cpp"
#include <iostream>

namespace winrt
{
    using namespace Windows::ApplicationModel::Background;
    using namespace Windows::Storage::Streams;
    using namespace Windows::Networking::PushNotifications;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    winrt::com_array<uint8_t> GetRawPayload(RawNotification const& rawNotification)
    {
        IBuffer rawContentAsBuffer = rawNotification.ContentBytes();
        DataReader dataReader = DataReader::FromBuffer(rawContentAsBuffer);

        winrt::com_array<uint8_t> rawPayload = winrt::com_array<uint8_t>(rawContentAsBuffer.Length());
        dataReader.ReadBytes(rawPayload);
        
        return rawPayload;
    }

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::IBackgroundTaskInstance const& backgroundTask): m_backgroundTaskInstance(backgroundTask), m_rawNotification(GetRawPayload(backgroundTask.TriggerDetails().as<RawNotification>())) {}

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::PushNotificationReceivedEventArgs const& args): m_args(args), m_rawNotification(GetRawPayload(args.RawNotification())) {}

    winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(winrt::IBackgroundTaskInstance const& backgroundTask)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(backgroundTask);
    }

    winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs PushNotificationReceivedEventArgs::CreateFromPushNotificationReceivedEventArgs(winrt::PushNotificationReceivedEventArgs const& args)
    {
        return winrt::make<PushNotificationReceivedEventArgs>(args);
    }

    winrt::com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        return { m_rawNotification.begin(), m_rawNotification.end() };
    }

    winrt::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        if (m_backgroundTaskInstance)
        {
            return m_backgroundTaskInstance.GetDeferral();
        }
        // winrt::throw_hresult();
    }

    winrt::event_token PushNotificationReceivedEventArgs::Canceled(winrt::BackgroundTaskCanceledEventHandler const& handler)
    {
        if (m_backgroundTaskInstance)
        {
            return m_backgroundTaskInstance.Canceled(handler);
        }
        return winrt::event_token{};
    }
    void PushNotificationReceivedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
        if (m_backgroundTaskInstance)
        {
            m_backgroundTaskInstance.Canceled(token);
        }
    }
    bool PushNotificationReceivedEventArgs::Handled()
    {
        if (m_args)
        {
            return m_args.Cancel();
        }
        return false;
    }
    void PushNotificationReceivedEventArgs::Handled(bool value)
    {
        if (m_args)
        {
            m_args.Cancel(value);
        }
    }
}

