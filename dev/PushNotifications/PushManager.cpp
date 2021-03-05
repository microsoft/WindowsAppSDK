// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushManager.h"
#include "PushManager.g.cpp"
#include <winrt\windows.networking.pushnotifications.h>
#include <winerror.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ChannelResult.h>
#include <winerror.h>
#include <PushNotificationErrorCodes.h>

using namespace winrt::Windows::Networking::PushNotifications;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::vector<winrt::guid> PushManager::s_remoteIdList;
    std::mutex PushManager::s_mutex;
    std::unique_lock<std::mutex> PushManager::s_lock (s_mutex, std::defer_lock); // Avoid locking during the constructor call
    inline constexpr std::uint32_t c_maxBackoffSeconds{ 960 };

    bool PushManager::isChannelRequestRetryable(const winrt::hresult& hrException)
    {
        switch (hrException)
        {
        case HRESULT_FROM_WIN32(ERROR_TIMEOUT):
        case WnpErrors::WNP_E_NOT_CONNECTED:
        case WPN_E_OUTSTANDING_CHANNEL_REQUEST:
        case WnpErrors:: WNP_E_RECONNECTING:
        case WnpErrors::WNP_E_BIND_USER_BUSY:
        case RPC_S_SERVER_UNAVAILABLE:
            return true;
        default:
            return false;
        }
    }

    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::ChannelResult, Microsoft::ProjectReunion::ChannelResult> PushManager::CreateChannelAsync(winrt::guid remoteId)
    {
        winrt::Microsoft::ProjectReunion::ChannelResult channelResult{ nullptr };
        auto progress{ co_await winrt::get_progress_token() };

        winrt::check_pointer(&remoteId);
      
        s_lock.lock();
        if (std::find(s_remoteIdList.begin(), s_remoteIdList.end(), remoteId) != s_remoteIdList.end())
        {
            progress(winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, ChannelStatus::InProgress));
            channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, ChannelStatus::CompletedFailure);
            co_return channelResult;
        }
        else
        {
            s_remoteIdList.push_back(remoteId);
        }
        s_lock.unlock();

        PushNotificationChannelManager channelManager{};

        for (auto backOffTimeInSeconds = 30; backOffTimeInSeconds <= c_maxBackoffSeconds * 2; backOffTimeInSeconds *= 2)
        {
            try
            {
                auto pushChannel = co_await channelManager.CreatePushNotificationChannelForApplicationAsync();

                if (pushChannel != nullptr)
                {
                    channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(pushChannel, S_OK, ChannelStatus::CompletedSuccess);
                    break;
                }
            }
            catch (...)
            {
                auto ex = hresult_error(to_hresult(), take_ownership_from_abi);

                if ((backOffTimeInSeconds <= c_maxBackoffSeconds) && isChannelRequestRetryable(ex.code()))
                {
                    progress(winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, ex.code(), ChannelStatus::InProgressRetry));
                }
                else
                {
                    channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, ex.code(), ChannelStatus::CompletedFailure);
                    break;
                }
            }

            co_await winrt::resume_after(std::chrono::seconds(backOffTimeInSeconds));
        }

        s_lock.lock();
        std::remove(s_remoteIdList.begin(), s_remoteIdList.end(), remoteId);
        s_lock.unlock();

        co_return channelResult;

    }
}
