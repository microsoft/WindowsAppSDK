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

using namespace winrt::Windows::Networking::PushNotifications;
using namespace winrt;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::vector<guid> PushManager::s_remoteIdList;
    std::mutex PushManager::s_mutex;
    std::unique_lock<std::mutex> PushManager::s_lock(s_mutex, std::defer_lock); // Avoid locking during the constructor call
    inline constexpr std::uint32_t c_maxBackoffSeconds{ 960 };
    inline constexpr std::uint32_t c_minBackoffSeconds{ 30 };

    const HRESULT WNP_E_NOT_CONNECTED = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WPN, 0x880403E8L);
    const HRESULT WNP_E_RECONNECTING = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WPN, 0x880403E9L);
    const HRESULT WNP_E_BIND_USER_BUSY = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WPN, 0x880403FEL);

    bool PushManager::isChannelRequestRetryable(const hresult& hr)
    {
        switch (hr)
        {
        case HRESULT_FROM_WIN32(ERROR_TIMEOUT):
        case WNP_E_NOT_CONNECTED:
        case WPN_E_OUTSTANDING_CHANNEL_REQUEST:
        case WNP_E_RECONNECTING:
        case WNP_E_BIND_USER_BUSY:
        case RPC_S_SERVER_UNAVAILABLE:
            return true;
        default:
            return false;
        }
    }

    bool IsPackagedProcess()
    {
        uint32_t packageFullNameLength = 0;
        const auto rc{ GetCurrentPackageFullName(&packageFullNameLength, nullptr) };

        if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            throw_hresult(rc);
        }

        return rc == ERROR_INSUFFICIENT_BUFFER;
    }

    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::ChannelResult, Microsoft::ProjectReunion::ChannelResult> PushManager::CreateChannelAsync(guid remoteId)
    {
        Microsoft::ProjectReunion::ChannelResult channelResult{ nullptr };
        auto progress{ co_await get_progress_token() };

        check_pointer(&remoteId);

        s_lock.lock();
        if (std::find(s_remoteIdList.begin(), s_remoteIdList.end(), remoteId) != s_remoteIdList.end())
        {
            s_lock.unlock();
            progress(make<Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, ChannelStatus::InProgress));
            channelResult = make<Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, ChannelStatus::CompletedFailure);
            co_return channelResult;
        }
        else
        {
            s_remoteIdList.push_back(remoteId);
            s_lock.unlock();
        }

        PushNotificationChannelManager channelManager{};
        PushNotificationChannel pushChannel{ nullptr };

        for (auto backOffTimeInSeconds = c_minBackoffSeconds; backOffTimeInSeconds <= c_maxBackoffSeconds * 2; backOffTimeInSeconds *= 2)
        {
            try
            {
                if (IsPackagedProcess())
                {
                    pushChannel = co_await channelManager.CreatePushNotificationChannelForApplicationAsync();
                }

                if (pushChannel != nullptr)
                {
                    channelResult = make<Microsoft::ProjectReunion::implementation::ChannelResult>(pushChannel, S_OK, ChannelStatus::CompletedSuccess);
                    break;
                }
            }
            catch (...)
            {
                auto ex = hresult_error(to_hresult(), take_ownership_from_abi);

                if ((backOffTimeInSeconds <= c_maxBackoffSeconds) && isChannelRequestRetryable(ex.code()))
                {
                    progress(make<Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, ex.code(), ChannelStatus::InProgressRetry));
                }
                else
                {
                    channelResult = make<Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, ex.code(), ChannelStatus::CompletedFailure);
                    break;
                }
            }

            co_await resume_after(std::chrono::seconds(backOffTimeInSeconds));
        }

        s_lock.lock();
        std::remove(s_remoteIdList.begin(), s_remoteIdList.end(), remoteId);
        s_lock.unlock();

        co_return channelResult;

    }
}
