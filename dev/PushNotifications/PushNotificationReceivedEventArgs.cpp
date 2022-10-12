// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>
#include "PushNotificationReceivedEventArgs.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.cpp"
#include <iostream>
#include <string>
#include <externs.h>
#include <PushNotificationDummyDeferral.h>
#include "ValueMarshaling.h"
#include "PushNotificationUtility.h"

namespace winrt
{
    using namespace Windows::ApplicationModel::Background;
    using namespace Windows::Storage::Streams;
    using namespace Windows::Storage;
    using namespace Windows::Networking::PushNotifications;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::IBackgroundTaskInstance const& backgroundTask):
        m_backgroundTaskInstance(backgroundTask),
        m_rawNotificationPayload(BuildPayload(backgroundTask.TriggerDetails().as<RawNotification>().ContentBytes())),
        m_isForegroundActivation(false)
    {
    }

    // Only foreground activation uses byte array for payload delivery
    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(byte* const& payload, ULONG const& length) :
        m_rawNotificationPayload(BuildPayload(payload, length)),
        m_isForegroundActivation(true)
    {
    }

    std::vector<uint8_t> PushNotificationReceivedEventArgs::BuildPayload(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        return { buffer.data(), buffer.data() + (buffer.Length() * sizeof(uint8_t)) };
    }

    std::vector<uint8_t> PushNotificationReceivedEventArgs::BuildPayload(byte* const& payload, ULONG const& length)
    {
        return { payload, payload + (length * sizeof(uint8_t)) };
    }

    winrt::com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        return { m_rawNotificationPayload.data(), m_rawNotificationPayload.data() + (m_rawNotificationPayload.size() * sizeof(uint8_t)) };
    }

    winrt::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        if (!PushNotificationHelpers::IsPackagedAppScenario())
        {
            return winrt::make<PushNotificationDummyDeferral>().as<BackgroundTaskDeferral>();
        }

        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, m_isForegroundActivation, "Foreground activation cannot call this.");

        return m_backgroundTaskInstance.GetDeferral();
    }

    winrt::event_token PushNotificationReceivedEventArgs::Canceled(winrt::BackgroundTaskCanceledEventHandler const& handler)
    {
        if (PushNotificationHelpers::IsPackagedAppScenario())
        {
            THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, m_isForegroundActivation, "Foreground activation cannot call this.");

            return m_backgroundTaskInstance.Canceled(handler);
        }

        return winrt::event_token{};
    }

    void PushNotificationReceivedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
        if (PushNotificationHelpers::IsPackagedAppScenario())
        {
            THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, m_isForegroundActivation, "Foreground activation cannot call this.");

            m_backgroundTaskInstance.Canceled(token);
        }
    }
}

