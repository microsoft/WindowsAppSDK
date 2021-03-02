// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushManager.h"
#include "PushManager.g.cpp"
#include <winrt\windows.networking.pushnotifications.h>
#include <winerror.h>
#include <algorithm>
#include <list>
#include <iostream>
#include <ChannelResult.h>
#include <winerror.h>

using namespace winrt::Windows::Networking::PushNotifications;
using namespace winrt;

// MAX BACKOFF TIME IS 16MINUTES 
#define MAX_BACKOFF_SECONDS 960

// Error code - platform is not connected
#define WNP_E_NOT_CONNECTED 0x880403E8L

// Error code - platform reconnecting with wns
#define WNP_E_RECONNECTING  0x880403E9L

// Error code - Current bind operation failed because another bind operation in progress
#define WNP_E_BIND_USER_BUSY 0x880403FEL

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::list<winrt::guid> PushManager::remoteIdList;
    std::mutex PushManager::mtx;
    std::unique_lock<std::mutex> PushManager::lock (mtx, std::defer_lock); // Avoid locking during the constructor call

    bool PushManager::isChannelRequestRetryable(const winrt::hresult& hrException)
    {
        switch (hrException)
        {
        case HRESULT_FROM_WIN32(ERROR_TIMEOUT):
            // E_TIMEOUT
        case WNP_E_NOT_CONNECTED:
        case WPN_E_OUTSTANDING_CHANNEL_REQUEST:
        case WNP_E_RECONNECTING
        case WNP_E_BIND_USER_BUSY:
            return true;
        default:
            return false;
        }
    }

    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::ChannelResult, Microsoft::ProjectReunion::ChannelResult> PushManager::CreateChannelAsync(winrt::guid remoteId)
    {
        winrt::Microsoft::ProjectReunion::ChannelResult channelResult{ nullptr };
        auto progress{ co_await winrt::get_progress_token() };

       GUID remoteIdAbiGuid = reinterpret_cast<GUID&>(remoteId);
       if (remoteIdAbiGuid == GUID_NULL)
        {
            channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, E_INVALIDARG, ChannelStatus::CompletedFailure);
            co_return channelResult;
        }

       lock.lock();
       if (std::find(remoteIdList.begin(), remoteIdList.end(), remoteId) != remoteIdList.end())
       {
           progress(winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, ChannelStatus::InProgress));
           channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, ChannelStatus::CompletedFailure);
           co_return channelResult;
       }
       else
       {
           remoteIdList.push_back(remoteId);
       }
       lock.unlock();

       PushNotificationChannelManager channelManager{};

       for (auto backOffTimeInSeconds = 30; backOffTimeInSeconds <= MAX_BACKOFF_SECONDS * 2; backOffTimeInSeconds *= 2)
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
           catch (winrt::hresult_error const& ex)
           {
               if ((backOffTimeInSeconds <= MAX_BACKOFF_SECONDS) && isChannelRequestRetryable(ex.code()))
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

       lock.lock();
       remoteIdList.remove(remoteId);
       lock.unlock();

       co_return channelResult;

    }
}
