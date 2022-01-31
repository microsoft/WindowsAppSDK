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
#include "PushNotificationUtility.h"

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

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
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
        if (PushNotificationHelpers::IsPackagedAppScenario())
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
                // The channelUri is directly obtained when we request Channel from UDK using RemoteId
                auto lock = m_lock.lock_exclusive();

                if (!m_foregroundHandlerCount)
                {
                    auto appUserModelId{ winrt::Microsoft::Helpers::GetAppUserModelId() };

                    THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appUserModelId.get(), this));
                }

                ++m_foregroundHandlerCount;

                return m_foregroundHandlers.add(handler);
            }
        }
        else
        {
            auto lock = m_lock.lock_exclusive();
            if (!m_foregroundHandlerCount++)
            {
                auto notificationsLongRunningPlatform{ winrt::Microsoft::Helpers::GetNotificationPlatform() };

                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));

                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterForegroundActivator(this, processName.get()));             
            }
            return m_foregroundHandlers.add(handler);
        }
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        if (PushNotificationHelpers::IsPackagedAppScenario())
        {
            if (m_channel)
            {
                m_channel.PushNotificationReceived(token);
            }
            else
            {
                auto lock = m_lock.lock_exclusive();

                if (m_foregroundHandlerCount == 1)
                {
                    auto appUserModelId{ winrt::Microsoft::Helpers::GetAppUserModelId() };

                    THROW_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appUserModelId.get()));
                }

                m_foregroundHandlers.remove(token);
                --m_foregroundHandlerCount;
            }
        }
        else
        {
            auto lock = m_lock.lock_exclusive();
            m_foregroundHandlers.remove(token);
            if (!--m_foregroundHandlerCount)
            {
                auto notificationsLongRunningPlatform{ winrt::Microsoft::Helpers::GetNotificationPlatform() };

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

    HRESULT __stdcall PushNotificationChannel::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector */) noexcept try
    {
        BOOL foregroundHandled = true;
        THROW_IF_FAILED(InvokeAll(payloadLength, payload, &foregroundHandled));

        if (!foregroundHandled)
        {
            wil::unique_cotaskmem_string processName;
            THROW_IF_FAILED(GetCurrentProcessPath(processName));
            THROW_IF_FAILED(winrt::Microsoft::Helpers::ProtocolLaunchHelper(processName.get(), payloadLength, payload));
        }

        return S_OK;
    }
    CATCH_RETURN();
}
