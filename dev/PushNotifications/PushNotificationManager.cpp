// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "PushNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.cpp"

#include "PushNotificationCreateChannelResult.h"
#include "PushNotifications-Constants.h"
#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Networking.PushNotifications.h>
#include "PushNotificationBackgroundTask.h"
#include <winrt/Windows.Foundation.Metadata.h>
#include <winerror.h>
#include <algorithm>
#include "PushNotificationChannel.h"
#include "externs.h"
#include <string_view>
#include <frameworkudk/pushnotifications.h>
#include "NotificationsLongRunningProcess_h.h"

using namespace std::literals;

constexpr std::wstring_view backgroundTaskName = L"PushBackgroundTaskName"sv;

static wil::unique_event g_waitHandleForArgs;

wil::unique_event& GetWaitHandleForArgs()
{
    return g_waitHandleForArgs;
}

namespace winrt
{
    using namespace Windows::ApplicationModel::Background;
    using namespace Windows::Networking::PushNotifications;
    using namespace Windows::Foundation;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    inline constexpr auto c_maxBackoff{ 5min };
    inline constexpr auto c_initialBackoff{ 60s };
    inline constexpr auto c_backoffIncrement{ 60s };

    const HRESULT WNP_E_NOT_CONNECTED = static_cast<HRESULT>(0x880403E8L);
    const HRESULT WNP_E_RECONNECTING = static_cast<HRESULT>(0x880403E9L);
    const HRESULT WNP_E_BIND_USER_BUSY = static_cast<HRESULT>(0x880403FEL);

    bool PushNotificationManager::IsChannelRequestRetryable(const hresult& hr)
    {
        switch (hr)
        {
        case HRESULT_FROM_WIN32(ERROR_TIMEOUT):
        case WNP_E_NOT_CONNECTED:
        case WPN_E_OUTSTANDING_CHANNEL_REQUEST:
        case WNP_E_RECONNECTING:
        case WNP_E_BIND_USER_BUSY:
        case HRESULT_FROM_WIN32(RPC_S_SERVER_UNAVAILABLE):
            return true;
        default:
            return false;
        }
    }

    void PushNotificationManager::RegisterUnpackagedApplicationHelper(
        const winrt::guid& remoteId,
        _Out_ wil::unique_cotaskmem_string &unpackagedAppUserModelId)
    {
        wchar_t processName[1024];
        THROW_HR_IF(ERROR_FILE_NOT_FOUND, GetModuleFileNameExW(GetCurrentProcess(), NULL, processName, sizeof(processName) / sizeof(processName[0])) == 0);

        THROW_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

        auto scopeExit = wil::scope_exit(
            [&]() { CoUninitialize(); });

        wil::com_ptr<INotificationsLongRunningPlatform> notificationPlatform{
            wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

        winrt::check_hresult(notificationPlatform->RegisterFullTrustApplication(processName, remoteId, &unpackagedAppUserModelId));
    }

    winrt::hresult PushNotificationManager::CreateChannelWithRemoteIdHelper(const winrt::guid& remoteId, ChannelDetails& channelInfo)
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appUserModelIdSize = ARRAYSIZE(appUserModelId);

        THROW_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));

        THROW_HR_IF(E_INVALIDARG, (appUserModelIdSize > APPLICATION_USER_MODEL_ID_MAX_LENGTH) || (appUserModelIdSize == 0));

        HRESULT operationalCode;
        ABI::Windows::Foundation::DateTime channelexpirytime{};

        HRESULT hr = PushNotifications_CreateChannelWithRemoteIdentifier(
            appUserModelId,
            remoteId,
            &operationalCode,
            &channelInfo.channelId,
            &channelInfo.channelUri,
            &channelexpirytime);

        /*
           RemoteId APIs are not applicable for downlevel OS versions.
           So we get error E_NOTIMPL and we fallback to calling into
           Public WinRT API CreatePushNotificationChannelForApplicationAsync
           to request for channels
        */
        THROW_HR_IF(hr, (hr != E_NOTIMPL) && (hr != S_OK));
        THROW_HR_IF(operationalCode, (hr == S_OK) && (operationalCode != S_OK));

        winrt::copy_from_abi(channelInfo.channelExpiryTime, &channelexpirytime);
        channelInfo.appUserModelId = wil::make_cotaskmem_string(appUserModelId);

        return hr;
    }

    winrt::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> PushNotificationManager::CreateChannelAsync(const winrt::guid &remoteId)
    {
        THROW_HR_IF(E_INVALIDARG, (remoteId == winrt::guid()));

        auto cancellation{ co_await winrt::get_cancellation_token() };

        cancellation.enable_propagation(true);

        // Allow to register the progress and complete handler
        co_await resume_background();

        auto progress{ co_await winrt::get_progress_token() };

        uint8_t retryCount = 0;
        winrt::hresult channelRequestResult = E_PENDING;
        PushNotificationChannelStatus status = PushNotificationChannelStatus::InProgress;

        PushNotificationCreateChannelStatus
            channelStatus = { status, channelRequestResult, retryCount };

        progress(channelStatus);

        for (auto backOffTime = c_initialBackoff; ; backOffTime += c_backoffIncrement)
        {
            try
            {
                if (IsActivatorSupported(PushNotificationRegistrationOptions::PushTrigger))
                {
                    ChannelDetails channelInfo{};
                    hresult hr = CreateChannelWithRemoteIdHelper(remoteId, channelInfo);

                    if (SUCCEEDED(hr))
                    {
                        co_return winrt::make<PushNotificationCreateChannelResult>(
                            winrt::make<PushNotificationChannel>(channelInfo.channelUri.get(), channelInfo.channelId.get(),  channelInfo.appUserModelId.get(), channelInfo.channelExpiryTime),
                            hr,
                            PushNotificationChannelStatus::CompletedSuccess);
                    }
                    else if (hr == E_NOTIMPL)
                    {
                        PushNotificationChannelManager channelManager{};
                        winrt::PushNotificationChannel pushChannelReceived{ nullptr };

                        pushChannelReceived = co_await channelManager.CreatePushNotificationChannelForApplicationAsync();

                        co_return winrt::make<PushNotificationCreateChannelResult>(
                            winrt::make<PushNotificationChannel>(pushChannelReceived),
                            S_OK,
                            PushNotificationChannelStatus::CompletedSuccess);
                    }
                }
                else
                {
                    wil::unique_cotaskmem_string unpackagedAppUserModelId;
                    RegisterUnpackagedApplicationHelper(remoteId, unpackagedAppUserModelId);

                    PushNotificationChannelManager channelManager{};
                    winrt::PushNotificationChannel pushChannelReceived{ nullptr };

                    pushChannelReceived = co_await channelManager.CreatePushNotificationChannelForApplicationAsync(unpackagedAppUserModelId.get());

                    co_return winrt::make<PushNotificationCreateChannelResult>(
                        winrt::make<PushNotificationChannel>(pushChannelReceived),
                        S_OK,
                        PushNotificationChannelStatus::CompletedSuccess);
                }
            }
            catch (...)
            {
                auto channelRequestException = hresult_error(to_hresult(), take_ownership_from_abi);

                if ((backOffTime <= c_maxBackoff) && IsChannelRequestRetryable(channelRequestException.code()))
                {
                    channelStatus.extendedError = channelRequestException.code();
                    channelStatus.status = PushNotificationChannelStatus::InProgressRetry;
                    channelStatus.retryCount = ++retryCount;

                    progress(channelStatus);
                }
                else
                {
                    co_return winrt::make<PushNotificationCreateChannelResult>(
                        nullptr,
                        channelRequestException.code(),
                        PushNotificationChannelStatus::CompletedFailure);
                }
            }

            co_await winrt::resume_after(backOffTime);
        }
    }

    PushNotificationRegistrationToken PushNotificationManager::RegisterActivator(PushNotificationActivationInfo const& details)
    {
        THROW_HR_IF_NULL(E_INVALIDARG, details);

        GUID taskClsid = details.TaskClsid();
        THROW_HR_IF(E_INVALIDARG, taskClsid == GUID_NULL);

        auto registrationOptions = details.Options();
        THROW_HR_IF(E_INVALIDARG, WI_AreAllFlagsClear(registrationOptions, PushNotificationRegistrationOptions::PushTrigger | PushNotificationRegistrationOptions::ComActivator));

        DWORD cookie = 0;
        IBackgroundTaskRegistration registeredTask = nullptr;
        BackgroundTaskBuilder builder = nullptr;

        if (WI_IsFlagSet(registrationOptions, PushNotificationRegistrationOptions::PushTrigger))
        {
            winrt::hstring taskClsidStr = winrt::to_hstring(taskClsid);
            winrt::hstring backgroundTaskFullName = backgroundTaskName + taskClsidStr;

            auto tasks = BackgroundTaskRegistration::AllTasks();
            bool isTaskRegistered = std::any_of(std::begin(tasks), std::end(tasks),
                [&](auto&& task)
                {
                    auto name = task.Value().Name();

                    if (std::wstring_view(name).substr(0, backgroundTaskName.size()) != backgroundTaskName)
                    {
                        return false;
                    }

                    if (name == backgroundTaskFullName)
                    {
                        registeredTask = task.Value();
                        return true;
                    }

                    throw winrt::hresult_invalid_argument(L"RegisterActivator has different clsid registered.");
                });

            if (!isTaskRegistered)
            {
                builder = BackgroundTaskBuilder();
                builder.Name(backgroundTaskFullName);

                PushNotificationTrigger trigger{};
                builder.SetTrigger(trigger);

                THROW_HR_IF(E_NOTIMPL, !AppModel::Identity::IsPackagedProcess());

                // In case the interface is not supported, let it throw.
                auto builder5 = builder.as<winrt::IBackgroundTaskBuilder5>();
                builder5.SetTaskEntryPointClsid(taskClsid);
                winrt::com_array<winrt::IBackgroundCondition> conditions = details.GetConditions();
                for (auto condition : conditions)
                {
                    builder.AddCondition(condition);
                }
            }
        }

        BackgroundTaskRegistration registeredTaskFromBuilder = nullptr;

        auto scopeExitToCleanRegistrations = wil::scope_exit(
            [&]()
            {
                if (cookie > 0)
                {
                    LOG_IF_FAILED(::CoRevokeClassObject(cookie));
                }

                // Clean the task registration only if it was created during this call
                if (registeredTaskFromBuilder)
                {
                    registeredTask.Unregister(true);
                }
            }
        );

        if (WI_IsFlagSet(registrationOptions, PushNotificationRegistrationOptions::ComActivator))
        {
            GetWaitHandleForArgs().create();

            THROW_IF_FAILED(::CoRegisterClassObject(
                taskClsid,
                winrt::make<PushNotificationBackgroundTaskFactory>().get(),
                CLSCTX_LOCAL_SERVER,
                REGCLS_MULTIPLEUSE,
                &cookie));
        }

        if (builder)
        {
            registeredTaskFromBuilder = builder.Register();
        }

        PushNotificationRegistrationToken token = { cookie, registeredTaskFromBuilder };
        scopeExitToCleanRegistrations.release();

        return token;
    }

    void PushNotificationManager::UnregisterActivator(PushNotificationRegistrationToken const& token, PushNotificationRegistrationOptions const& options)
    {
        THROW_HR_IF_NULL(E_INVALIDARG, token);
        if (WI_IsFlagSet(options, PushNotificationRegistrationOptions::PushTrigger))
        {
            auto taskRegistration = token.TaskRegistration();
            THROW_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), taskRegistration);
            taskRegistration.Unregister(true);
        }

        // Check for COM flag, a valid cookie and if there are outstanding locks on the PushNotificationBackgroundTask class factory
        if (WI_IsFlagSet(options, PushNotificationRegistrationOptions::ComActivator) && token.Cookie() && winrt::get_module_lock() == 0)
        {
            LOG_IF_FAILED(::CoRevokeClassObject(static_cast<DWORD>(token.Cookie())));
        }
    }

    static bool HasBackgroundTaskEntryPointClsid() {
        return Metadata::ApiInformation::IsMethodPresent(L"Windows.ApplicationModel.Background.BackgroundTaskBuilder", L"SetTaskEntryPointClsid");
    }

    bool PushNotificationManager::IsBackgroundTaskBuilderAvailable()
    {
        static bool hasSetTaskEntrypoint = HasBackgroundTaskEntryPointClsid();
        return hasSetTaskEntrypoint;
    }

    bool PushNotificationManager::IsActivatorSupported(PushNotificationRegistrationOptions const& options)
    {
        THROW_HR_IF(E_INVALIDARG, options == PushNotificationRegistrationOptions::Undefined);

        auto isBackgroundTaskFlagSet{ WI_IsAnyFlagSet(options, PushNotificationRegistrationOptions::PushTrigger | PushNotificationRegistrationOptions::ComActivator) };
        auto isProtocolActivatorSet{ WI_IsFlagSet(options, PushNotificationRegistrationOptions::ProtocolActivator) };

        THROW_HR_IF(E_INVALIDARG, isBackgroundTaskFlagSet && isProtocolActivatorSet); // Invalid flag combination
        if (AppModel::Identity::IsPackagedProcess() && IsBackgroundTaskBuilderAvailable())
        {
            if (isProtocolActivatorSet) // ProtocolActivator unsupported if COM activation is available
            {
                return false;
            }
            return isBackgroundTaskFlagSet;
        }
        else
        {
            return isProtocolActivatorSet;
        }
    }
}
