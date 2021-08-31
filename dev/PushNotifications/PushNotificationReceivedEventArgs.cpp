// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>

#include "PushNotificationReceivedEventArgs.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs.g.cpp"
#include <iostream>
#include <externs.h>
#include "ValueMarshaling.h"

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
        m_rawNotificationPayload(BuildPayload(backgroundTask.TriggerDetails().as<RawNotification>().ContentBytes().data(), backgroundTask.TriggerDetails().as<RawNotification>().ContentBytes().Length())),
        m_isUnpackagedApp(true) {}

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::PushNotificationReceivedEventArgs const& args):
        m_args(args),
        m_rawNotificationPayload(BuildPayload(args.RawNotification().ContentBytes().data(), args.RawNotification().ContentBytes().Length())),
        m_isUnpackagedApp(true) {}

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(byte* payload, ULONG length):
        m_rawNotificationPayload(BuildPayload(payload, length)),
        m_isUnpackagedApp(false) {}

    std::vector<uint8_t> PushNotificationReceivedEventArgs::BuildPayload(uint8_t* payload, ULONG payloadLength)
    {
        return { payload, payload + (payloadLength * sizeof(uint8_t)) };
    }

    winrt::com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        return { m_rawNotificationPayload.data(), m_rawNotificationPayload.data() + (m_rawNotificationPayload.size() * sizeof(uint8_t)) };
    }

    winrt::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        if (m_isUnpackagedApp)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_backgroundTaskInstance, "Foreground activation cannot call this.");

            return m_backgroundTaskInstance.GetDeferral();
        }
        else
        {
            return nullptr;
        }
    }

    winrt::event_token PushNotificationReceivedEventArgs::Canceled(winrt::BackgroundTaskCanceledEventHandler const& handler)
    {
        if (m_isUnpackagedApp)
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
        if (m_isUnpackagedApp)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_backgroundTaskInstance, "Foreground activation cannot call this.");

            m_backgroundTaskInstance.Canceled(token);
        }
    }

    bool PushNotificationReceivedEventArgs::Handled()
    {
        if (m_isUnpackagedApp)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_args, "Background activation cannot call this.");

            return m_args.Cancel();
        }
        else
        {
            return m_handledUnpackaged;
        }
    }

    void PushNotificationReceivedEventArgs::Handled(bool value)
    {
        if (m_isUnpackagedApp)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_args, "Background activation cannot call this.");

            m_args.Cancel(value);
        }
        else
        {
            if (!value)
            {
                wchar_t processName[MAX_PATH];
                THROW_HR_IF(ERROR_FILE_NOT_FOUND, GetModuleFileNameExW(GetCurrentProcess(), NULL, processName, sizeof(processName) / sizeof(processName[0])) == 0);

                wil::com_ptr<INotificationsLongRunningPlatform> notificationsLongRunningPlatform{
                    wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

                THROW_IF_FAILED(notificationsLongRunningPlatform->SendBackgroundNotification(processName, m_rawNotificationPayload.data(), m_rawNotificationPayload.size()));
            }

            m_handledUnpackaged = value;
        }
    }
}

