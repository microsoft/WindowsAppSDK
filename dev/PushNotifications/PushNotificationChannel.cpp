// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <winrt/Windows.Foundation.Metadata.h>
#include "PushNotificationChannel.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationChannel.g.cpp"
#include <winrt\Windows.Foundation.h>
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
    PushNotificationChannel::PushNotificationChannel(struct ChannelDetails channelInfo)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        std::swap(m_channelInfo, channelInfo);
    }

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
}
