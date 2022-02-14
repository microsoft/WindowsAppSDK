// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <winrt/Windows.Foundation.Metadata.h>
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Foundation.h>
#include "PushNotificationReceivedEventArgs.h"
#include <FrameworkUdk/PushNotifications.h>
#include "externs.h"
#include "PushNotificationTelemetry.h"
#include "PushNotificationUtility.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::Windows::PushNotifications;


namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    Uri PushNotificationChannel::Uri()
    {
        return winrt::Windows::Foundation::Uri{ m_channelInfo.channelUri };
    }

    DateTime PushNotificationChannel::ExpirationTime()
    {
        return m_channelInfo.channelExpiryTime;
    }

    void PushNotificationChannel::Close()
    {
        try
        {
            THROW_IF_FAILED(PushNotifications_CloseChannel(m_channelInfo.appId.c_str(), m_channelInfo.channelId.c_str()));
            PushNotificationTelemetry::ChannelClosedByApi(S_OK);
        }

        catch (...)
        {
            auto channelCloseException { hresult_error(to_hresult()) };

            PushNotificationTelemetry::ChannelClosedByApi(channelCloseException.code());

            if (channelCloseException.code() != HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
            {
                throw channelCloseException;
            }
        }
    }

    winrt::event_token PushNotificationChannel::PushReceived(TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler)
    {
        bool registeredEvent { false };
        {
            auto lock { m_lock.lock_shared() };
            registeredEvent = bool(m_foregroundHandlers);
        }

        if(!registeredEvent)
        {
            if(PushNotificationHelpers::IsPackagedAppScenario())
            {
                auto appUserModelId{ PushNotificationHelpers::GetAppUserModelId() };

                // Register a sink with platform which is initialized in the current process
                THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appUserModelId.get(), this));
            }
            else
            {
                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));

                // Register a sink with platform brokered through PushNotificationsLongRunningProcess
                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterForegroundActivator(this, processName.get()));
            }
        }

        auto lock { m_lock.lock_exclusive() };
        return m_foregroundHandlers.add(handler);
    }

    void PushNotificationChannel::PushReceived(winrt::event_token const& token) noexcept
    {
        bool registeredEvent { false };
        {
            auto lock { m_lock.lock_exclusive() };
            m_foregroundHandlers.remove(token);
            registeredEvent = bool(m_foregroundHandlers);
        }

        if(!registeredEvent)
        {
            // Packaged apps with BI available will remove their handlers from the platform.
            // Unpackaged apps / Packaged apps treated as unpackaged will unregister from Long Running process.
            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                auto appUserModelId{ PushNotificationHelpers::GetAppUserModelId() };

                THROW_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appUserModelId.get()));
            }
            else
            {
                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

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
            if (!AppModel::Identity::IsPackagedProcess())
            {
                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));
                THROW_IF_FAILED(PushNotificationHelpers::ProtocolLaunchHelper(processName.get(), payloadLength, payload));
            }
        }

        return S_OK;
    }
    CATCH_RETURN();
}
