// Copyright (c) Microsoft Corporation.
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
        m_unpackagedAppScenario(false)
    {
    }

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::PushNotificationReceivedEventArgs const& args):
        m_rawNotificationPayload(BuildPayload(args.RawNotification().ContentBytes())),
        m_unpackagedAppScenario(false)
    {
    }

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(byte* const& payload, ULONG const& length) :
        m_rawNotificationPayload(BuildPayload(payload, length)),
        m_unpackagedAppScenario(true)
    {
    }

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::hstring const& payload) :
        m_rawNotificationPayload(BuildPayload(payload)),
        m_unpackagedAppScenario(true)
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

    std::vector<uint8_t> PushNotificationReceivedEventArgs::BuildPayload(winrt::hstring const& payload)
    {
        std::string payloadToSimpleString{ ::winrt::Microsoft::Windows::PushNotifications::Helpers::WideStringToUtf8String(payload) };
        return { payloadToSimpleString.c_str(), payloadToSimpleString.c_str() + (payloadToSimpleString.length() * sizeof(uint8_t)) };
    }

    winrt::com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        return { m_rawNotificationPayload.data(), m_rawNotificationPayload.data() + (m_rawNotificationPayload.size() * sizeof(uint8_t)) };
    }

    winrt::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        if (!m_unpackagedAppScenario)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_backgroundTaskInstance, "Foreground activation cannot call this.");

            return m_backgroundTaskInstance.GetDeferral();
        }
        else
        {
            auto dummyDeferral = winrt::make<PushNotificationDummyDeferral>();
            return dummyDeferral.as<winrt::BackgroundTaskDeferral>();
        }
    }

    winrt::event_token PushNotificationReceivedEventArgs::Canceled(winrt::BackgroundTaskCanceledEventHandler const& handler)
    {
        if (!m_unpackagedAppScenario)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_backgroundTaskInstance, "Foreground activation cannot call this.");

            return m_backgroundTaskInstance.Canceled(handler);
        }
        else
        {
            return { 0 };
        }
    }

    void PushNotificationReceivedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
        if (!m_unpackagedAppScenario)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_backgroundTaskInstance, "Foreground activation cannot call this.");

            m_backgroundTaskInstance.Canceled(token);
        }
    }
}

