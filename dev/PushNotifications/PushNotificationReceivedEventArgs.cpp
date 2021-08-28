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
        m_rawNotification(GetByteArrayFromBuffer(backgroundTask.TriggerDetails().as<RawNotification>().ContentBytes())),
        m_isBIAvailable(true) {}

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(winrt::PushNotificationReceivedEventArgs const& args):
        m_args(args),
        m_rawNotification(GetByteArrayFromBuffer(args.RawNotification().ContentBytes())),
        m_isBIAvailable(true) {}

    PushNotificationReceivedEventArgs::PushNotificationReceivedEventArgs(byte* payload, ULONG length):
        m_rawNotification(payload),
        m_length(length),
        m_isBIAvailable(false) {}

    byte* PushNotificationReceivedEventArgs::GetByteArrayFromBuffer(winrt::Windows::Storage::Streams::IBuffer buffer)
    {
        auto rawNotificationData = buffer.data();
        m_length = buffer.Length();
        return rawNotificationData;
    }

    winrt::com_array<uint8_t> PushNotificationReceivedEventArgs::Payload()
    {
        return { m_rawNotification, m_rawNotification + (m_length * sizeof(uint8_t)) };
    }

    winrt::BackgroundTaskDeferral PushNotificationReceivedEventArgs::GetDeferral()
    {
        if (m_isBIAvailable)
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
        if (m_isBIAvailable)
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
        if (m_isBIAvailable)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_backgroundTaskInstance, "Foreground activation cannot call this.");

            m_backgroundTaskInstance.Canceled(token);
        }
    }

    bool PushNotificationReceivedEventArgs::Handled()
    {
        if (m_isBIAvailable)
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
        if (m_isBIAvailable)
        {
            THROW_HR_IF_NULL_MSG(E_ILLEGAL_METHOD_CALL, m_args, "Background activation cannot call this.");

            m_args.Cancel(value);
        }
        else
        {
            if (value)
            {
                wchar_t processName[1024];
                THROW_HR_IF(ERROR_FILE_NOT_FOUND, GetModuleFileNameExW(GetCurrentProcess(), NULL, processName, sizeof(processName) / sizeof(processName[0])) == 0);

                wil::com_ptr<INotificationsLongRunningPlatform> notificationsLongRunningPlatform{
                    wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

                notificationsLongRunningPlatform->SendBackgroundNotification(processName, m_rawNotification, m_length);
            }

            m_handledUnpackaged = value;
        }
    }
}

