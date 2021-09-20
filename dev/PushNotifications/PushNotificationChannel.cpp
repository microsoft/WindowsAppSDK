// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <winrt/Windows.Foundation.Metadata.h>
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"
#include <FrameworkUdk/PushNotifications.h>
#include "externs.h"
#include "PushNotificationTelemetry.h"
#include <TerminalVelocityFeatures-PushNotifications.h>


namespace winrt::Windows
{
    using namespace winrt::Windows::Networking::PushNotifications;
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Metadata;
}
namespace winrt::Microsoft
{
    using namespace winrt::Microsoft::Windows::PushNotifications;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationChannel::PushNotificationChannel(winrt::Windows::PushNotificationChannel const& channel): m_channel(channel) 
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());
    }

    winrt::Windows::Uri PushNotificationChannel::Uri()
    {
        if (m_channel)
        {
            return winrt::Windows::Uri{ m_channel.Uri() };
        }
        else
        {
            return winrt::Windows::Uri{ m_channelInfo.channelUri };
        }
    }

    winrt::Windows::DateTime PushNotificationChannel::ExpirationTime()
    {
        if (m_channel)
        {
            return m_channel.ExpirationTime();
        }
        else
        {
            return m_channelInfo.channelExpiryTime;
        }
    }

    void PushNotificationChannel::Close()
    {
        try
        {
            if (m_channel)
            {
                m_channel.Close();
            }
            else
            {
                THROW_IF_FAILED(PushNotifications_CloseChannel(m_channelInfo.appUserModelId.c_str(), m_channelInfo.channelId.c_str()));
            }

            PushNotificationTelemetry::ChannelClosedByApi(S_OK);
        }

        catch (...)
        {
            auto channelCloseException = hresult_error(to_hresult());

            PushNotificationTelemetry::ChannelClosedByApi(channelCloseException.code());

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
            if (m_channel)
            {
                return m_channel.PushNotificationReceived([weak_self = get_weak(), handler](auto&&, auto&& args)
                {
                    if (auto strong = weak_self.get())
                    {
                        auto pushArgs = winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(args);
                        pushArgs.Handled(true);
                        handler(*strong, pushArgs);
                    };
                });
            }
            else
            {
                auto lock = m_lock.lock_exclusive();

                THROW_HR_IF_NULL(E_UNEXPECTED, m_channelInfo.channelUri.c_str());

                wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
                UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };

                THROW_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));

                THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appUserModelId, this));

                return m_foregroundHandlers.add(handler);
               

            }
            // One more check if channelInfo struct is null - we should throw E_UNEXPECTED
        }
        else
        {
            auto lock = m_lock.lock_exclusive();
            if (!m_foregroundHandlerCount++)
            {
                wil::com_ptr<INotificationsLongRunningPlatform> notificationsLongRunningPlatform{
                    wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));

                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterForegroundActivator(this, processName.get()));             
            }
            return m_foregroundHandlers.add(handler);
        }
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        if (IsPackagedAppScenario())
        {
            if (m_channel)
            {
                m_channel.PushNotificationReceived(token);
            }
            else
            {
                auto lock = m_lock.lock_exclusive();

                wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
                UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };

                THROW_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));

                THROW_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appUserModelId));
                m_foregroundHandlers.remove(token);

            }
        }
        else
        {
            auto lock = m_lock.lock_exclusive();
            m_foregroundHandlers.remove(token);
            if (!--m_foregroundHandlerCount)
            {
                wil::com_ptr<INotificationsLongRunningPlatform> notificationsLongRunningPlatform{
                    wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));

                THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterForegroundActivator(processName.get()));
            }
        }
    }

    HRESULT __stdcall PushNotificationChannel::InvokeAll(_In_ ULONG length, _In_ byte* payload, _Out_ BOOL* foregroundHandled) noexcept try
    {
        auto args = winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payload, length);
        m_foregroundHandlers(*this, args);
        *foregroundHandled = args.Handled();
        return S_OK;
    }
    CATCH_RETURN()

    bool PushNotificationChannel::IsBackgroundTaskBuilderAvailable()
    {
        return winrt::Windows::ApiInformation::IsMethodPresent(L"Windows.ApplicationModel.Background.BackgroundTaskBuilder", L"SetTaskEntryPointClsid");
    }

    // Determines if the caller should be treated as packaged app or not.
    bool PushNotificationChannel::IsPackagedAppScenario()
    {
        return AppModel::Identity::IsPackagedProcess() && IsBackgroundTaskBuilderAvailable();
    }
}
