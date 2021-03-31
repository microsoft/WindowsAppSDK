#include "pch.h"
#include "PushNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.cpp"
#include "PushNotificationCreateChannelResult.h"
#include <winrt\windows.networking.pushnotifications.h>
#include <winerror.h>
#include <algorithm>
#include <iostream>
#include "PushNotificationChannel.h"
#include <wil/resource.h>

using namespace winrt::Windows::Networking::PushNotifications;
using namespace winrt;

namespace winrt::Microsoft::Windows::PushNotifications::implementation
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
        wchar_t packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1] = {};

        UINT32 packageFullNameLength = static_cast<UINT32>(ARRAYSIZE(packageFullName));

        const auto packagedProcessHResult = ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName);

        if (packagedProcessHResult == APPMODEL_ERROR_NO_PACKAGE)
        {
            return false;
        }
        else if(packagedProcessHResult != S_OK)
        {
            winrt::throw_hresult(packagedProcessHResult);
        }

        return true;
    }

    winrt::Windows::Foundation::IAsyncOperationWithProgress<Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> PushNotificationManager::CreateChannelAsync(winrt::guid remoteId)
    {
        static bool s_remoteIdInProgress;
        static wil::critical_section s_lock;

        if (remoteId == winrt::guid())
        {
            throw_hresult(E_INVALIDARG);
        }

        // API supports channel requests only for packaged applications for v0.8 version
        bool isPackagedProcess = IsPackagedProcess();

        if (!isPackagedProcess)
        {
            throw_hresult(E_NOTIMPL);
        }

        bool remoteIdInProgress = false;
        {
            auto lock = s_lock.lock();
            if (s_remoteIdInProgress == false)
            {
                s_remoteIdInProgress = (!remoteIdInProgress);
            }
            else
            {
                remoteIdInProgress = true;
            }
        }

        winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult channelResult{ nullptr };

        if (remoteIdInProgress)
        {
            channelResult = winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationCreateChannelResult>(
                nullptr, WPN_E_OUTSTANDING_CHANNEL_REQUEST, PushNotificationChannelStatus::CompletedFailure);
            co_return channelResult;;
        }

        auto scopeExit = wil::scope_exit([&]()
            {
                auto lock = s_lock.lock();
                s_remoteIdInProgress = false;
            });

        auto cancellation{ co_await winrt::get_cancellation_token() };

        cancellation.enable_propagation(true);

        // Allow to register the progress and complete handler
        co_await resume_background();

        auto progress{ co_await winrt::get_progress_token() };

        uint8_t retryCount = 0;
        winrt::hresult channelRequestResult = E_PENDING;
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus status = PushNotificationChannelStatus::InProgress;

        winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus
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

        
        if (status == PushNotificationChannelStatus::CompletedSuccess)
        {
            // Returns a com_ptr to the implementation type
            auto pushChannel =
                winrt::make_self<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationChannel>(pushChannelReceived);

            channelResult = winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationCreateChannelResult>(
                *(pushChannel.get()),
                channelRequestResult,
                status);
        }
        else if(status == PushNotificationChannelStatus::CompletedFailure)
        {
            channelResult = winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationCreateChannelResult>(
                nullptr,
                channelRequestResult,
                status);
        }

        co_return channelResult;
    }
}
