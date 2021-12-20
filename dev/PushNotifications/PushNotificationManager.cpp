// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "PushNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.cpp"
#include "PushNotificationTelemetry.h"
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
#include <TerminalVelocityFeatures-PushNotifications.h>
#include "PushNotificationUtility.h"
#include "ToastNotificationUtility.h"

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

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}
namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    static winrt::Windows::ApplicationModel::Background::IBackgroundTaskRegistration s_pushTriggerRegistration{ nullptr };
    static wil::unique_com_class_object_cookie s_comActivatorRegistration;
    static bool s_protocolRegistration{ false };
    static wil::srwlock s_activatorInfoLock;

    inline constexpr auto c_maxBackoff{ 5min };
    inline constexpr auto c_initialBackoff{ 60s };
    inline constexpr auto c_backoffIncrement{ 60s };

    const HRESULT WNP_E_NOT_CONNECTED = static_cast<HRESULT>(0x880403E8L);
    const HRESULT WNP_E_RECONNECTING = static_cast<HRESULT>(0x880403E9L);
    const HRESULT WNP_E_BIND_USER_BUSY = static_cast<HRESULT>(0x880403FEL);

    bool IsChannelRequestRetryable(const hresult& hr)
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

    void RegisterUnpackagedApplicationHelper(
        const winrt::guid& remoteId,
        _Out_ wil::unique_cotaskmem_string &unpackagedAppUserModelId)
    {
        auto coInitialize = wil::CoInitializeEx();

        auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));

        THROW_IF_FAILED(notificationPlatform->RegisterFullTrustApplication(processName.get(), remoteId, &unpackagedAppUserModelId));
    }

    winrt::hresult CreateChannelWithRemoteIdHelper(const winrt::guid& remoteId, ChannelDetails& channelInfo) noexcept try
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };

        THROW_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));

        THROW_HR_IF(E_INVALIDARG, (appUserModelIdSize > APPLICATION_USER_MODEL_ID_MAX_LENGTH) || (appUserModelIdSize == 0));

        HRESULT operationalCode{};
        ABI::Windows::Foundation::DateTime channelExpiryTime{};
        wil::unique_cotaskmem_string channelId;
        wil::unique_cotaskmem_string channelUri;

        THROW_IF_FAILED(PushNotifications_CreateChannelWithRemoteIdentifier(
            appUserModelId,
            remoteId,
            &operationalCode,
            &channelId,
            &channelUri,
            &channelExpiryTime));

        THROW_IF_FAILED(operationalCode);

        winrt::copy_from_abi(channelInfo.channelExpiryTime, &channelExpiryTime);
        channelInfo.appUserModelId = winrt::hstring{ appUserModelId };
        channelInfo.channelId = winrt::hstring{ channelId.get() };
        channelInfo.channelUri = winrt::hstring{ channelUri.get() };

        return S_OK;
    }
    CATCH_RETURN()

    winrt::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> PushNotificationManager::CreateChannelAsync(const winrt::guid remoteId)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        wil::winrt_module_reference moduleRef{};
        bool usingLegacyImplementation{ false };

        try
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
                    if (IsActivatorSupported(PushNotificationRegistrationActivators::PushTrigger))
                    {
                        ChannelDetails channelInfo{};
                        winrt::hresult hr = CreateChannelWithRemoteIdHelper(remoteId, channelInfo);

                        // RemoteId APIs are not applicable for downlevel OS versions.
                        // So we get error E_NOTIMPL and we fallback to calling into
                        // public WinRT API CreatePushNotificationChannelForApplicationAsync
                        // to request a channel.
                        if (SUCCEEDED(hr))
                        {
                            PushNotificationTelemetry::ChannelRequestedByApi(S_OK, remoteId, usingLegacyImplementation);

                            co_return winrt::make<PushNotificationCreateChannelResult>(
                                winrt::make<PushNotificationChannel>(channelInfo),
                                S_OK,
                                PushNotificationChannelStatus::CompletedSuccess);
                        }
                        else if (hr == E_NOTIMPL)
                        {
                            usingLegacyImplementation = true;

                            PushNotificationChannelManager channelManager{};
                            winrt::PushNotificationChannel pushChannelReceived{ nullptr };

                            pushChannelReceived = co_await channelManager.CreatePushNotificationChannelForApplicationAsync();

                            PushNotificationTelemetry::ChannelRequestedByApi(S_OK, remoteId, usingLegacyImplementation);

                            co_return winrt::make<PushNotificationCreateChannelResult>(
                                winrt::make<PushNotificationChannel>(pushChannelReceived),
                                S_OK,
                                PushNotificationChannelStatus::CompletedSuccess);
                        }
                        else
                        {
                            winrt::check_hresult(hr);
                        }
                    }
                    else
                    {
                        wil::unique_cotaskmem_string unpackagedAppUserModelId;
                        RegisterUnpackagedApplicationHelper(remoteId, unpackagedAppUserModelId);
                        PushNotificationChannelManager channelManager{};
                        winrt::PushNotificationChannel pushChannelReceived{ co_await channelManager.CreatePushNotificationChannelForApplicationAsync(unpackagedAppUserModelId.get()) };

                        auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                        wil::unique_cotaskmem_string processName;
                        THROW_IF_FAILED(GetCurrentProcessPath(processName));
                        std::wstring appId{ RetrieveAppId() };
                        THROW_IF_FAILED(notificationPlatform->AddToastRegistration(processName.get(), appId.c_str()));
                        THROW_IF_FAILED(notificationPlatform->RegisterLongRunningActivator(processName.get()));
                        
                        PushNotificationTelemetry::ChannelRequestedByApi(S_OK, remoteId, usingLegacyImplementation);

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
                        PushNotificationTelemetry::ChannelRequestedByApi(channelRequestException.code(), remoteId, usingLegacyImplementation);

                        co_return winrt::make<PushNotificationCreateChannelResult>(
                            nullptr,
                            channelRequestException.code(),
                            PushNotificationChannelStatus::CompletedFailure);
                    }
                }

                co_await winrt::resume_after(backOffTime);
            }
        }
        catch (...)
        {
            PushNotificationTelemetry::ChannelRequestedByApi(wil::ResultFromCaughtException(), remoteId, usingLegacyImplementation);
            throw;
        }
    }

    void PushNotificationManager::RegisterActivator(PushNotificationActivationInfo const& details)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        try
        {
            THROW_HR_IF_NULL(E_INVALIDARG, details);

            auto registrationActivators{ details.Activators() };

            auto isBackgroundTaskFlagSet{ WI_IsAnyFlagSet(registrationActivators, PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator) };
            THROW_HR_IF(E_INVALIDARG, isBackgroundTaskFlagSet && !IsActivatorSupported(registrationActivators));

            auto isProtocolActivatorSet{ WI_IsFlagSet(registrationActivators, PushNotificationRegistrationActivators::ProtocolActivator) };
            THROW_HR_IF(E_INVALIDARG, isProtocolActivatorSet && !IsActivatorSupported(registrationActivators));

            if (isProtocolActivatorSet)
            {
                {
                    auto lock = s_activatorInfoLock.lock_shared();
                    THROW_HR_IF(E_INVALIDARG, s_protocolRegistration);
                }

                wil::unique_cotaskmem_string unpackagedAppUserModelId;
                RegisterUnpackagedApplicationHelper(GUID_NULL, unpackagedAppUserModelId); // create default registration for app

                {
                    auto lock = s_activatorInfoLock.lock_exclusive();
                    s_protocolRegistration = true;
                }
            }

            BackgroundTaskBuilder builder{ nullptr };

            if (WI_IsFlagSet(registrationActivators, PushNotificationRegistrationActivators::PushTrigger))
            {
                GUID taskClsid = details.TaskClsid();
                THROW_HR_IF(E_INVALIDARG, taskClsid == GUID_NULL);

                {
                    auto lock = s_activatorInfoLock.lock_shared();
                    THROW_HR_IF(E_INVALIDARG, s_pushTriggerRegistration);
                }

                winrt::hstring taskClsidStr{ winrt::to_hstring(taskClsid) };
                winrt::hstring backgroundTaskFullName{ backgroundTaskName + taskClsidStr };

                auto tasks{ BackgroundTaskRegistration::AllTasks() };
                bool isTaskRegistered{ std::any_of(std::begin(tasks), std::end(tasks),
                    [&](auto&& task)
                    {
                        auto name{ task.Value().Name() };

                        if (std::wstring_view(name).substr(0, backgroundTaskName.size()) != backgroundTaskName)
                        {
                            return false;
                        }

                        if (name == backgroundTaskFullName)
                        {
                            s_pushTriggerRegistration = task.Value();
                            return true;
                        }

                        throw winrt::hresult_invalid_argument(L"RegisterActivator has different clsid registered.");
                    }) };

                if (!isTaskRegistered)
                {
                    builder = BackgroundTaskBuilder();
                    builder.Name(backgroundTaskFullName);

                    PushNotificationTrigger trigger{};
                    builder.SetTrigger(trigger);

                    THROW_HR_IF(E_NOTIMPL, !AppModel::Identity::IsPackagedProcess());

                    // In case the interface is not supported, let it throw.
                    auto builder5{ builder.as<winrt::IBackgroundTaskBuilder5>() };
                    builder5.SetTaskEntryPointClsid(taskClsid);
                    winrt::com_array<winrt::IBackgroundCondition> conditions = details.GetConditions();
                    for (auto condition : conditions)
                    {
                        builder.AddCondition(condition);
                    }
                }
            }

            BackgroundTaskRegistration registeredTaskFromBuilder{ nullptr };

            auto scopeExitToCleanRegistrations{ wil::scope_exit(
                [&]()
                {
                    s_comActivatorRegistration.reset();

                    // Clean the task registration only if it was created during this call
                    if (registeredTaskFromBuilder)
                    {
                        registeredTaskFromBuilder.Unregister(true);
                    }
                }
            ) };

            if (WI_IsFlagSet(registrationActivators, PushNotificationRegistrationActivators::ComActivator))
            {
                GUID taskClsid = details.TaskClsid();
                THROW_HR_IF(E_INVALIDARG, taskClsid == GUID_NULL);

                {
                    auto lock = s_activatorInfoLock.lock_shared();
                    THROW_HR_IF_MSG(E_INVALIDARG, s_comActivatorRegistration, "ComActivator already registered.");
                }

                GetWaitHandleForArgs().create();

                THROW_IF_FAILED(::CoRegisterClassObject(
                    taskClsid,
                    winrt::make<PushNotificationBackgroundTaskFactory>().get(),
                    CLSCTX_LOCAL_SERVER,
                    REGCLS_MULTIPLEUSE,
                    &s_comActivatorRegistration));
            }

            if (builder)
            {
                registeredTaskFromBuilder = builder.Register();
            }

            scopeExitToCleanRegistrations.release();
            auto lock{ s_activatorInfoLock.lock_exclusive() };
            s_pushTriggerRegistration = registeredTaskFromBuilder;
            PushNotificationTelemetry::ActivatorRegisteredByApi(S_OK, details.Activators());
        }

        catch(...)
        {
            PushNotificationTelemetry::ActivatorRegisteredByApi(wil::ResultFromCaughtException(),
                details == nullptr ? PushNotificationRegistrationActivators::Undefined : details.Activators());
            throw;
        }
    }

    void PushNotificationManager::UnregisterActivator(PushNotificationRegistrationActivators const& activators)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        try
        {
            auto lock{ s_activatorInfoLock.lock_exclusive() };
            if (WI_IsFlagSet(activators, PushNotificationRegistrationActivators::PushTrigger))
            {
                THROW_HR_IF_NULL_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), s_pushTriggerRegistration, "PushTrigger not registered.");
                s_pushTriggerRegistration.Unregister(true);
                s_pushTriggerRegistration = nullptr;
            }

            // Check for COM flag, a valid cookie
            if (WI_IsFlagSet(activators, PushNotificationRegistrationActivators::ComActivator))
            {
                THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !s_comActivatorRegistration, "ComActivator not registered.");
                s_comActivatorRegistration.reset();
            }

            if (WI_IsFlagSet(activators, PushNotificationRegistrationActivators::ProtocolActivator))
            {
                THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !s_protocolRegistration);
                auto coInitialize = wil::CoInitializeEx();

                auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));
                LOG_IF_FAILED(notificationPlatform->UnregisterLongRunningActivator(processName.get()));

                s_protocolRegistration = false;
            }
        }
        catch (...)
        {
            PushNotificationTelemetry::ActivatorUnregisteredByApi(wil::ResultFromCaughtException(), activators);
            throw;
        }

        PushNotificationTelemetry::ActivatorUnregisteredByApi(S_OK, activators);
    }

    void PushNotificationManager::UnregisterAllActivators()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        try
        {
            auto lock{ s_activatorInfoLock.lock_exclusive() };
            if (s_pushTriggerRegistration)
            {
                s_pushTriggerRegistration.Unregister(true);
                s_pushTriggerRegistration = nullptr;
            }

            s_comActivatorRegistration.reset();

            if (s_protocolRegistration)
            {
                auto coInitialize = wil::CoInitializeEx();

                auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));
                LOG_IF_FAILED(notificationPlatform->UnregisterLongRunningActivator(processName.get()));

                s_protocolRegistration = false;
            }
        }
        catch(...)
        {
            PushNotificationTelemetry::ActivatorUnregisteredByApi(wil::ResultFromCaughtException(),
                PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator);
            throw;
        }
        PushNotificationTelemetry::ActivatorUnregisteredByApi(S_OK, PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator);
    }

    static bool HasBackgroundTaskEntryPointClsid() {
        return Metadata::ApiInformation::IsMethodPresent(L"Windows.ApplicationModel.Background.BackgroundTaskBuilder", L"SetTaskEntryPointClsid");
    }

    bool IsBackgroundTaskBuilderAvailable()
    {
        static bool hasSetTaskEntrypoint{ HasBackgroundTaskEntryPointClsid() };
        return hasSetTaskEntrypoint;
    }

    bool PushNotificationManager::IsActivatorSupported(PushNotificationRegistrationActivators const& activators)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        THROW_HR_IF(E_INVALIDARG, activators == PushNotificationRegistrationActivators::Undefined);

        auto isBackgroundTaskFlagSet{ WI_IsAnyFlagSet(activators, PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator) };
        auto isProtocolActivatorSet{ WI_IsFlagSet(activators, PushNotificationRegistrationActivators::ProtocolActivator) };

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
