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

using namespace winrt::Windows::Networking::PushNotifications;
using namespace winrt;

// MAX BACKOFF TIME IS 16MINUTES 
#define MAX_BACKOFF_SECONDS 960

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
        case 0x880403E8L:
            // WNP_E_NOT_CONNECTED
        case 0x803E0103L:
            // WPN_E_OUTSTANDING_CHANNEL_REQUEST
        case 0x880403E9L:
            // WNP_E_RECONNECTING
        case 0x880403FEL:
            // WNP_E_BIND_USER_BUSY
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
           progress(winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, S_FALSE, ChannelStatus::InProgress));
           // Pending: WPN_E_THROTTLED
           channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::ChannelResult>(nullptr, E_INVALIDARG, ChannelStatus::CompletedFailure);
           co_return channelResult;
       }
       else
       {
           remoteIdList.push_back(remoteId);
       }
       lock.unlock();

       std::cout << "Add the remoteId" << std::endl;

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
       std::cout << "Remove the remoteId" << std::endl;

       co_return channelResult;

    }
}
