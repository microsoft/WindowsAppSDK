#include "pch.h"
#include "PushNotificationManager.h"
#include "PushNotificationManager.g.cpp"
#include <winrt\windows.networking.pushnotifications.h>
#include <winerror.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <PushNotificationCreateChannelResult.h>

using namespace winrt::Windows::Networking::PushNotifications;
using namespace winrt;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::vector<winrt::guid> PushNotificationManager::s_remoteIdList;
    std::mutex PushNotificationManager::s_mutex;
    std::unique_lock<std::mutex> PushNotificationManager::s_lock(s_mutex, std::defer_lock); // Avoid locking during the constructor call
    inline constexpr std::uint32_t c_maxBackoffSeconds{ 960 };

    const HRESULT WNP_E_NOT_CONNECTED = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x880403E8L);
    const HRESULT WNP_E_RECONNECTING = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x880403E9L);
    const HRESULT WNP_E_BIND_USER_BUSY = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x880403FEL);

    bool PushNotificationManager::isChannelRequestRetryable(const hresult& hr)
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
            winrt::throw_hresult(rc);
        }
        return rc == ERROR_INSUFFICIENT_BUFFER;
    }

    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushNotificationCreateChannelResult, Microsoft::ProjectReunion::PushNotificationCreateChannelStatus> PushNotificationManager::CreateChannelAsync(winrt::guid remoteId)
    {
        winrt::check_pointer(&remoteId);

        auto progress{ co_await winrt::get_progress_token() };

        winrt::Microsoft::ProjectReunion::PushNotificationCreateChannelResult channelResult{ nullptr };

        channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushNotificationCreateChannelResult>(
                            nullptr, E_PENDING, PushNotificationChannelStatus::InProgress);

        progress.set_result(channelResult);

        std::cout << "Hello1" << std::endl;
        s_lock.lock();

        if (std::find(s_remoteIdList.begin(), s_remoteIdList.end(), remoteId) != s_remoteIdList.end())
        {
            s_lock.unlock();
            channelResult.PushNotificationCreateChannelUpdate(nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, PushNotificationChannelStatus::CompletedFailure);
            co_return channelResult;
        }
        else
        {
            s_remoteIdList.push_back(remoteId);
            s_lock.unlock();
            channelResult.PushNotificationCreateChannelUpdate(nullptr, E_PENDING, PushNotificationChannelStatus::InProgress);
        }

        PushNotificationChannelManager channelManager{};
        winrt::Windows::Networking::PushNotifications::PushNotificationChannel pushChannel{ nullptr };
        std::cout << "Hello2" << std::endl;

        for (auto backOffTimeInSeconds = 30; backOffTimeInSeconds <= c_maxBackoffSeconds * 2; backOffTimeInSeconds *= 2)
        {
            try
            {
                if (IsPackagedProcess())
                {
                    std::cout << "Hello3" << std::endl;
                    pushChannel = co_await channelManager.CreatePushNotificationChannelForApplicationAsync();
                }

                if (pushChannel != nullptr)
                {
                  //  winrt::Microsoft::ProjectReunion::PushNotificationChannel channelReunion{ nullptr };

                    //channelReunion = winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushNotificationChannel> (
                                       //     pushChannel.Uri(), pushChannel.ExpirationTime());
                    std::cout << "Hello4" << std::endl;
                    //std::cout << winrt::to_string(pushChannel.Uri()) << std::endl;
                    channelResult.PushNotificationCreateChannelUpdate(nullptr, S_OK, PushNotificationChannelStatus::CompletedSuccess);
                    break;
                }
            }
            catch (...)
            {
                auto ex = hresult_error(to_hresult(), take_ownership_from_abi);

                std::cout << "Hello5 " << ex.code() << std::endl;
                std::getchar();
                if ((backOffTimeInSeconds <= c_maxBackoffSeconds) && isChannelRequestRetryable(ex.code()))
                {
                    channelResult.PushNotificationCreateChannelUpdate(nullptr, ex.code(), PushNotificationChannelStatus::InProgressRetry);
                }
                else
                {
                    channelResult.PushNotificationCreateChannelUpdate(nullptr, ex.code(), PushNotificationChannelStatus::CompletedFailure);
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
