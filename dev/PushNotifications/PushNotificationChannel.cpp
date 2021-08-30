// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <winrt/Windows.Foundation.Metadata.h>
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"

namespace winrt::Windows
{
    using namespace winrt::Windows::Networking::PushNotifications;
    using namespace winrt::Windows::Foundation;
}
namespace winrt::Microsoft
{
    using namespace winrt::Microsoft::Windows::PushNotifications;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationChannel::PushNotificationChannel(winrt::Windows::PushNotificationChannel const& channel): m_channel(channel) {}

    winrt::Windows::Uri PushNotificationChannel::Uri()
    {
        return winrt::Windows::Uri{ m_channel.Uri() };
    }

    winrt::Windows::DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_channel.ExpirationTime();
    }

    void PushNotificationChannel::Close()
    {
        try
        {
            m_channel.Close();
        }
        catch (...)
        {
            auto channelCloseException = hresult_error(to_hresult());
            if (channelCloseException.code() != HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
            {
                throw hresult_error(to_hresult());
            }
        }
    }

    winrt::event_token PushNotificationChannel::PushReceived(winrt::Windows::TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler)
    {
        if (IsPackagedAppScenario())
        {
            return m_channel.PushNotificationReceived([weak_self = get_weak(), handler](auto&&, auto&& args)
            {
                auto strong = weak_self.get();
                if (strong)
                {
                    handler(*strong, winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(args));
                };
            });
        }
        else
        {
            if (!m_isRegisteredWithLRP)
            {
                wil::com_ptr<INotificationsLongRunningPlatform> notificationsLongRunningPlatform{
                    wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

                wchar_t processName[1024];
                THROW_HR_IF(ERROR_FILE_NOT_FOUND, GetModuleFileNameExW(GetCurrentProcess(), NULL, processName, sizeof(processName) / sizeof(processName[0])) == 0);

                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterForegroundActivator(this, processName));

                m_isRegisteredWithLRP = true;
            }
            return m_foregroundHandlers.add(handler);
        }
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        if (IsPackagedAppScenario())
        {
            m_channel.PushNotificationReceived(token);
        }
        else
        {
            m_foregroundHandlers.remove(token);
        }
    }

    HRESULT __stdcall PushNotificationChannel::InvokeAll(ULONG length, _In_ byte* start) noexcept try
    {
        m_foregroundHandlers(*this, winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(start, length));
        return S_OK;
    }
    CATCH_RETURN()

    bool PushNotificationChannel::IsBackgroundTaskBuilderAvailable()
    {
        return winrt::Windows::Metadata::ApiInformation::IsMethodPresent(L"Windows.ApplicationModel.Background.BackgroundTaskBuilder", L"SetTaskEntryPointClsid");
    }

    // Determines if the caller should be treated as packaged app or not.
    bool PushNotificationChannel::IsPackagedAppScenario()
    {
        return AppModel::Identity::IsPackagedProcess() && IsBackgroundTaskBuilderAvailable();
    }
}
