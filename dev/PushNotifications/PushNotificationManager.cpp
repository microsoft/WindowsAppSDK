#include "pch.h"
#include "PushNotificationManager.h"
#include "PushNotificationManager.g.cpp"
#include "PushNotificationCreateChannelResult.h"
#include <winrt\windows.networking.pushnotifications.h>
#include <winerror.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "PushNotificationChannel.h"
#include <wil/resource.h>

using namespace winrt::Windows::Networking::PushNotifications;
using namespace winrt;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    inline constexpr std::uint32_t c_maxBackoffSeconds{ 960 };
    inline constexpr std::uint32_t c_minBackoffSeconds{ 30 };

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

    inline bool IsPackagedProcess()
    {
        uint32_t packageFullNameLength = 0;
        // Have a package full name pointer
        // use it on the stack
        // Check with reunion discussion - reunion API for packaged process which checks for error codes
        auto packagedProcessHResult = GetCurrentPackageFullName(&packageFullNameLength, nullptr);

        if (packagedProcessHResult == ERROR_INSUFFICIENT_BUFFER)
        {
            return true;
        }
        else if (packagedProcessHResult == APPMODEL_ERROR_NO_PACKAGE)
        {
            return false;
        }
        else
        {
            winrt::throw_hresult(packagedProcessHResult);
        }
    }

    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushNotificationCreateChannelResult, Microsoft::ProjectReunion::PushNotificationCreateChannelStatus> PushNotificationManager::CreateChannelAsync(winrt::guid remoteId)
    {
        static bool s_remoteIdInProgress;
        static wil::critical_section s_lock;

        uint8_t retryCount = 0;
        winrt::hresult channelRequestResult = E_PENDING;
        winrt::Microsoft::ProjectReunion::PushNotificationChannelStatus status = PushNotificationChannelStatus::InProgress;

        auto scopeExit = wil::scope_exit([&]()
            {
                std::cout << "status: " << static_cast<int>(status) << std::endl;
                auto lock = s_lock.lock();
                if (status == PushNotificationChannelStatus::CompletedSuccess || status == PushNotificationChannelStatus::CompletedFailure)
                {
                    s_remoteIdInProgress = false;
                    std::cout << "Release the remoteId" << std::endl;
                }
            });

        if (remoteId == winrt::guid())
        {
            throw_hresult(E_INVALIDARG);
        }

        // API supports channel requests only for packaged applications
        bool isPackagedProcess = IsPackagedProcess();

        // More efficient way - isAPISupported pattern - refer reunion discussion today
        if (!isPackagedProcess)
        {
            // Need to find the right value to throw
            throw_hresult(E_NOTIMPL);
        }

        // Allow to register the progress and complete handler
        // co_await resume_background();

        auto progress{ co_await winrt::get_progress_token() };

        winrt::Microsoft::ProjectReunion::PushNotificationCreateChannelResult channelResult{ nullptr };
        {
            auto lock = s_lock.lock();

            if (s_remoteIdInProgress == false)
            {
                s_remoteIdInProgress = true;
            }
            else
            {
                channelRequestResult = WPN_E_OUTSTANDING_CHANNEL_REQUEST;
                status = PushNotificationChannelStatus::CompletedThrottled;
                channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushNotificationCreateChannelResult>(
                    nullptr, channelRequestResult, status);

                co_return channelResult;;
            }
        }

        Microsoft::ProjectReunion::PushNotificationCreateChannelStatus
            channelStatus = { channelRequestResult, status, retryCount };

        progress(channelStatus);

        PushNotificationChannelManager channelManager{};
        winrt::Windows::Networking::PushNotifications::PushNotificationChannel pushChannelReceived{ nullptr };

        for (auto backOffTimeInSeconds = c_minBackoffSeconds; backOffTimeInSeconds <= c_maxBackoffSeconds * 2; backOffTimeInSeconds *= 2)
        {
            try
            {
                pushChannelReceived = co_await channelManager.CreatePushNotificationChannelForApplicationAsync();
                channelRequestResult = S_OK;
                status = PushNotificationChannelStatus::CompletedSuccess;
                break;
            }
            catch (...)
            {

                auto channelRequestException = hresult_error(to_hresult(), take_ownership_from_abi);

                if ((backOffTimeInSeconds <= c_maxBackoffSeconds) && isChannelRequestRetryable(channelRequestException.code()))
                {
                    channelStatus.extendedError = channelRequestException.code();
                    channelStatus.status = PushNotificationChannelStatus::InProgressRetry;
                    channelStatus.retryCount = ++retryCount;

                    progress(channelStatus);
                }
                else
                {
                    channelRequestResult = channelRequestException.code();
                    status = PushNotificationChannelStatus::CompletedFailure;
                    break;
                }
            }

            co_await winrt::resume_after(std::chrono::seconds(backOffTimeInSeconds));
        }

        // Returns a com_ptr returning the implementation type
        auto pushChannel =
            winrt::make_self<winrt::Microsoft::ProjectReunion::implementation::PushNotificationChannel>(((status == PushNotificationChannelStatus::CompletedSuccess) ? pushChannelReceived : nullptr));

        channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushNotificationCreateChannelResult>(
            *(pushChannel.get()),
            channelRequestResult,
            status);

        std::cout << "New design works" << std::endl;

        co_return channelResult;
    }
}
