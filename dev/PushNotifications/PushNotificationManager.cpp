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
#include <winerror.h>
#include <algorithm>
#include "PushNotificationChannel.h"
#include "externs.h"
#include <string_view>
#include <frameworkudk/pushnotifications.h>
#include "NotificationsLongRunningProcess_h.h"
#include "PushNotificationUtility.h"
#include "AppNotificationUtility.h"
#include "PushNotificationReceivedEventArgs.h"

using namespace std::literals;
using namespace Microsoft::Windows::AppNotifications::Helpers;

static wil::unique_event g_waitHandleForArgs;
static winrt::guid g_comServerClsid{ GUID_NULL };

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
    inline constexpr auto c_maxBackoff{ 5min };
    inline constexpr auto c_initialBackoff{ 60s };
    inline constexpr auto c_backoffIncrement{ 60s };
    inline constexpr std::wstring_view c_backgroundTaskName = L"PushBackgroundTaskName"sv;
    inline constexpr std::wstring_view c_expectedPushServerArgs = L"----WindowsAppRuntimePushServer:"sv;

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

    PushNotificationManager::PushNotificationManager()
    {
        THROW_IF_FAILED(GetCurrentProcessPath(m_processName));

        if (AppModel::Identity::IsPackagedProcess())
        {
            // Returns ComActivator CLSID from registry. This CLSID provided in manifest is registered when a packaged app is installed
            THROW_IF_FAILED(PushNotificationHelpers::GetComRegistrationFromRegistry(c_expectedPushServerArgs.data(), m_registeredClsid));
        }
    }

    winrt::hresult CreateChannelWithRemoteIdHelper(wil::unique_cotaskmem_string const& appId, const winrt::guid& remoteId, ChannelDetails& channelInfo) noexcept try
    {
        HRESULT operationalCode{};
        ABI::Windows::Foundation::DateTime channelExpiryTime{};
        wil::unique_cotaskmem_string channelId;
        wil::unique_cotaskmem_string channelUri;

        THROW_IF_FAILED(PushNotifications_CreateChannelWithRemoteIdentifier(
            appId.get(),
            remoteId,
            &operationalCode,
            &channelId,
            &channelUri,
            &channelExpiryTime));

        THROW_IF_FAILED(operationalCode);

        winrt::copy_from_abi(channelInfo.channelExpiryTime, &channelExpiryTime);
        channelInfo.appId = winrt::hstring{ appId.get() };
        channelInfo.channelId = winrt::hstring{ channelId.get() };
        channelInfo.channelUri = winrt::hstring{ channelUri.get() };

        return S_OK;
    }
    CATCH_RETURN()

    winrt::Microsoft::Windows::PushNotifications::PushNotificationManager PushNotificationManager::Default()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        static auto pushNotificationManager{ winrt::make<PushNotificationManager>() };
        return pushNotificationManager;
    }

    winrt::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> PushNotificationManager::CreateChannelAsync(const winrt::guid remoteId)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::PushNotifications::Feature_PushNotifications::IsEnabled());

        wil::winrt_module_reference moduleRef{};

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
                    ChannelDetails channelInfo{};
                    if (PushNotificationHelpers::IsPackagedAppScenario())
                    {
                        auto appUserModelId{ PushNotificationHelpers::GetAppUserModelId() };
                        THROW_IF_FAILED(CreateChannelWithRemoteIdHelper(appUserModelId, remoteId, channelInfo));

                        // Register a sink with platform which is initialized in the current process
                        THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appUserModelId.get(), PushNotificationManager::Default().as<ABI::Microsoft::Internal::PushNotifications::INotificationListener>().get()));
                    }
                    else
                    {
                        auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                        // AppId is generated by PushNotificationLongRunningTask singleton
                        wil::unique_cotaskmem_string unpackagedAppUserModelId;
                        std::wstring processName;
                        {
                            auto lock{ m_lock.lock_shared() };
                            processName = m_processName.get();
                        }
                        THROW_IF_FAILED(notificationPlatform->RegisterFullTrustApplication(processName.c_str(), remoteId, &unpackagedAppUserModelId));

                        THROW_IF_FAILED(CreateChannelWithRemoteIdHelper(unpackagedAppUserModelId, remoteId, channelInfo));

                        THROW_IF_FAILED(notificationPlatform->RegisterForegroundActivator(PushNotificationManager::Default().as<IWpnForegroundSink>().get(), processName.c_str()));

                        // Need to recreate the sink in the Long Running Process Singleton
                        winrt::guid registeredClsid{ GUID_NULL };
                        {
                            auto lock{ m_lock.lock_shared() };
                            registeredClsid = m_registeredClsid;
                        }
                        // registeredClsid is set to GUID_NULL for unpackaged applications
                        THROW_IF_FAILED(notificationPlatform->RegisterLongRunningActivatorWithClsid(processName.c_str(), registeredClsid));

                        std::wstring toastAppId{ RetrieveNotificationAppId() };
                        THROW_IF_FAILED(notificationPlatform->AddToastRegistrationMapping(processName.c_str(), toastAppId.c_str()));
                    }

                    auto channel{ winrt::make<PushNotificationChannel>(channelInfo) };
                    {
                        auto lock{ m_lock.lock_exclusive() };
                        m_channel = channel;
                    }

                    PushNotificationTelemetry::ChannelRequestedByApi(S_OK, remoteId);
                    co_return winrt::make<PushNotificationCreateChannelResult>(
                        channel,
                        S_OK,
                        PushNotificationChannelStatus::CompletedSuccess);
                }
                catch (...)
                {
                    auto channelRequestException{ hresult_error(to_hresult(), take_ownership_from_abi) };

                    if ((backOffTime <= c_maxBackoff) && IsChannelRequestRetryable(channelRequestException.code()))
                    {
                        channelStatus.extendedError = channelRequestException.code();
                        channelStatus.status = PushNotificationChannelStatus::InProgressRetry;
                        channelStatus.retryCount = ++retryCount;

                        progress(channelStatus);
                    }
                    else
                    {
                        PushNotificationTelemetry::ChannelRequestedByApi(channelRequestException.code(), remoteId);

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
            PushNotificationTelemetry::ChannelRequestedByApi(wil::ResultFromCaughtException(), remoteId);
            throw;
        }
    }

    bool PushNotificationManager::IsBackgroundTaskRegistered(winrt::hstring const& backgroundTaskFullName)
    {
        auto tasks{ BackgroundTaskRegistration::AllTasks() };
        bool isTaskRegistered{ std::any_of(std::begin(tasks), std::end(tasks),
            [&](auto&& task)
            {
                auto name{ task.Value().Name() };

                return name == backgroundTaskFullName;
            }) };

        return isTaskRegistered;
    }

    IBackgroundTaskRegistration RetreiveBackgroundTaskRegistration(winrt::hstring const& backgroundTaskFullName)
    {
        auto tasks{ BackgroundTaskRegistration::AllTasks() };
        IBackgroundTaskRegistration registration{};

        // Custom version of std::find since we are looking for the name
        // of the task not the registration.
        auto first{ std::begin(tasks) };
        auto last{ std::end(tasks) };
        while (first != last)
        {
            if (first.Current().Value().Name() == backgroundTaskFullName)
            {
                return first.Current().Value();
            }
            ++first;
        }
        return nullptr;
    }

    void PushNotificationManager::Register()
    {
        winrt::hresult hr{ S_OK };
        try
        {
            {
                auto lock{ m_lock.lock_exclusive() };
                THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_OPERATION_IN_PROGRESS), m_registering, "Registration is in progress!");
                m_registering = true;
            }

            auto scopeExitToCleanRegistrations{ wil::scope_exit([&]()
            {
                auto lock { m_lock.lock_exclusive() };
                m_registering = false;
            }
            ) };

            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                {
                    auto lock{ m_lock.lock_shared() };
                    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED), m_comActivatorRegistration || m_pushTriggerRegistration);
                }

                auto scopeExitToCleanRegistrations{ wil::scope_exit([&]()
                {
                    {
                        auto lock { m_lock.lock_exclusive() };
                        m_comActivatorRegistration.reset();

                        // Clean the task registration only if it was created during this call
                        if (m_pushTriggerRegistration)
                        {
                            m_pushTriggerRegistration.Unregister(true);
                            m_pushTriggerRegistration = nullptr;
                        }
                    }
                }
                )};

                winrt::hstring backgroundTaskFullName;
                {
                    auto lock{ m_lock.lock_shared() };
                    backgroundTaskFullName = c_backgroundTaskName + winrt::to_hstring(m_registeredClsid);
                }

                // Register a PushTrigger for BI to activate the application through COM
                if (!IsBackgroundTaskRegistered(backgroundTaskFullName))
                {
                    BackgroundTaskBuilder builder{};

                    builder.Name(backgroundTaskFullName);

                    PushNotificationTrigger trigger{};
                    builder.SetTrigger(trigger);

                    auto builder5{ builder.as<winrt::IBackgroundTaskBuilder5>() };
                    {
                        auto lock{ m_lock.lock_exclusive() };
                        builder5.SetTaskEntryPointClsid(m_registeredClsid);
                        m_pushTriggerRegistration = builder.Register();
                    }
                }
                else
                {
                    auto backgroundTaskRegistration{ RetreiveBackgroundTaskRegistration(backgroundTaskFullName) };

                    auto lock{ m_lock.lock_exclusive() };
                    m_pushTriggerRegistration = backgroundTaskRegistration;
                }

                // Register a sink with platform which is initialized in the current process
                auto appUserModelId{ PushNotificationHelpers::GetAppUserModelId() };
                THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appUserModelId.get(), PushNotificationManager::Default().as<ABI::Microsoft::Internal::PushNotifications::INotificationListener>().get()));
                auto scopeExitToCleanSink{ wil::scope_exit([&]()
                {
                    THROW_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appUserModelId.get()));
                }
                ) };

                {
                    auto lock{ m_lock.lock_exclusive() };
                    // Register a PushNotificationBackgroundTask to handle background activation scenarios
                    THROW_IF_FAILED(::CoRegisterClassObject(
                        m_registeredClsid,
                        winrt::make<PushNotificationBackgroundTaskFactory>().get(),
                        CLSCTX_LOCAL_SERVER,
                        REGCLS_MULTIPLEUSE,
                        &m_comActivatorRegistration));
                }

                scopeExitToCleanSink.release();
                scopeExitToCleanRegistrations.release();
            }
            else
            {
                {
                    auto lock{ m_lock.lock_shared() };
                    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED), m_singletonForegroundRegistration || m_singletonLongRunningSinkRegistration);
                }

                auto scopeExitToCleanRegistrations{ wil::scope_exit([&]()
                {
                    {
                        auto lock { m_lock.lock_exclusive() };

                        m_comActivatorRegistration.reset();
                    }
                }) };

                auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
                wil::unique_cotaskmem_string unpackagedAppUserModelId;

                std::wstring processName;
                {
                    auto lock{ m_lock.lock_shared() };
                    processName = m_processName.get();
                }
                // Apps treated as unpackaged need to call RegisterFullTrustApplication and register with the LRP
                THROW_IF_FAILED(notificationPlatform->RegisterFullTrustApplication(processName.c_str(), GUID_NULL /* remoteId */, &unpackagedAppUserModelId));
                auto scopeExitFullTrustRegistration{ wil::scope_exit([&]()
                {
                    THROW_IF_FAILED(notificationPlatform->UnregisterFullTrustApplication(processName.c_str()));
                }) };

                // Registers a NoticicationListener and foreground delegate with the Long Running Process singleton
                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                // Register a sink with platform brokered through PushNotificationsLongRunningProcess
                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterForegroundActivator(PushNotificationManager::Default().as<IWpnForegroundSink>().get(), processName.c_str()));
                {
                    auto lock{ m_lock.lock_exclusive() };
                    m_singletonForegroundRegistration = true;
                }
                auto scopeExitToCleanForegroundSink{ wil::scope_exit([&]()
                {
                    THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterForegroundActivator(processName.c_str()));
                    m_singletonForegroundRegistration = false;
                }
                ) };

                winrt::guid registeredClsid{ GUID_NULL };
                {
                    auto lock{ m_lock.lock_shared() };
                    registeredClsid = m_registeredClsid;
                }
                // registeredClsid is set to GUID_NULL for unpackaged applications
                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterLongRunningActivatorWithClsid(processName.c_str(), registeredClsid));
                {
                    auto lock{ m_lock.lock_exclusive() };
                    m_singletonLongRunningSinkRegistration = true;
                }

                auto scopeExitToCleanLongRunningSink{ wil::scope_exit([&]()
                {
                    THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterLongRunningActivator(processName.c_str()));
                    m_singletonLongRunningSinkRegistration = false;
                }
                ) };

                // Register a COM object for the PushNotificationLongRunningProcess to CoCreate in background activation scenarios
                if (AppModel::Identity::IsPackagedProcess())
                {
                    auto lock{ m_lock.lock_exclusive() };
                    THROW_IF_FAILED(::CoRegisterClassObject(
                        registeredClsid,
                        winrt::make<PushNotificationBackgroundTaskFactory>().get(),
                        CLSCTX_LOCAL_SERVER,
                        REGCLS_MULTIPLEUSE,
                        &m_comActivatorRegistration));
                }

                scopeExitToCleanLongRunningSink.release();
                scopeExitToCleanForegroundSink.release();
                scopeExitFullTrustRegistration.release();
                scopeExitToCleanRegistrations.release();
            }
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            PushNotificationTelemetry::ActivatorRegisteredByApi(hr);
        }

        THROW_IF_FAILED(hr);
        PushNotificationTelemetry::ActivatorRegisteredByApi(hr);
    }

    void PushNotificationManager::Unregister()
    {
        hresult hr = S_OK;
        try
        {
            {
                auto lock{ m_lock.lock_exclusive() };
                THROW_HR_IF_MSG(E_FAIL, m_registering, "Register or Unregister currently in progress!");
                m_registering = true;
            }

            auto scope_exit = wil::scope_exit(
                [&] {
                    auto lock{ m_lock.lock_exclusive() };
                    m_registering = false;
                });

            if (AppModel::Identity::IsPackagedProcess())
            {
                auto lock{ m_lock.lock_exclusive() };
                THROW_HR_IF_MSG(E_UNEXPECTED, !m_comActivatorRegistration, "Need to call Register() before calling Unregister().");
                m_comActivatorRegistration.reset();
            }

            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                auto appUserModelId{ PushNotificationHelpers::GetAppUserModelId() };
                THROW_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appUserModelId.get()));
            }
            else
            {
                std::wstring processName;
                {
                    auto lock{ m_lock.lock_shared() };
                    THROW_HR_IF_MSG(E_UNEXPECTED, !m_singletonForegroundRegistration, "Need to call Register() before calling Unregister().");
                    processName = m_processName.get();
                }

                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
                // Unregister foreground sink with the Long Running Process Singleton
                THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterForegroundActivator(processName.c_str()));

                {
                    auto lock{ m_lock.lock_exclusive() };
                    m_singletonForegroundRegistration = false;
                }
            }
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            PushNotificationTelemetry::ActivatorUnregisteredByApi(hr);
        }

        THROW_IF_FAILED(hr);

        PushNotificationTelemetry::ActivatorUnregisteredByApi(hr);
    }

    void PushNotificationManager::UnregisterAll()
    {
        bool comActivatorRegistration{ false };
        bool singletonForegroundRegistration{ false };
        {
            auto lock{ m_lock.lock_shared() };
            comActivatorRegistration = bool(m_comActivatorRegistration);
            singletonForegroundRegistration = m_singletonForegroundRegistration;
        }

        if (comActivatorRegistration || singletonForegroundRegistration)
        {
            Unregister();
        }

        hresult hr = S_OK;
        try
        {
            {
                auto lock{ m_lock.lock_exclusive() };
                THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_OPERATION_IN_PROGRESS), m_registering, "Register or Unregister currently in progress!");
                m_registering = true;
            }

            auto scope_exit = wil::scope_exit(
                [&] {
                    auto lock{ m_lock.lock_exclusive() };
                    m_registering = false;
                });

            {
                auto lock{ m_lock.lock_shared() };
                if (m_channel != nullptr)
                {
                    m_channel.Close();
                }
            }       

            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                auto lock{ m_lock.lock_exclusive() };
                THROW_HR_IF_NULL(E_UNEXPECTED, m_pushTriggerRegistration);

                m_pushTriggerRegistration.Unregister(true);
                m_pushTriggerRegistration = nullptr;
            }
            else
            {
                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                std::wstring processName;
                {
                    auto lock{ m_lock.lock_shared() };
                    THROW_HR_IF(E_UNEXPECTED, !m_singletonLongRunningSinkRegistration);
                    processName = m_processName.get();
                }

                // Removes the Long Running Singleton sink registered with platform for both packaged and unpackaged applications 
                THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterLongRunningActivator(processName.c_str()));

                {
                    auto lock{ m_lock.lock_exclusive() };
                    m_singletonLongRunningSinkRegistration = false;
                }

                THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterFullTrustApplication(processName.c_str()));
            }
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            PushNotificationTelemetry::ActivatorUnregisteredByApi(hr);
        }

        THROW_IF_FAILED(hr);

        PushNotificationTelemetry::ActivatorUnregisteredByApi(hr);
    }

    winrt::event_token PushNotificationManager::PushReceived(TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationManager, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler)
    {
        {
            auto lock{ m_lock.lock_shared() };
            THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), m_comActivatorRegistration || m_singletonLongRunningSinkRegistration, "Must register event handlers before calling Register().");
        }

        auto lock{ m_lock.lock_exclusive() };
        return m_foregroundHandlers.add(handler);
    }


    void PushNotificationManager::PushReceived(winrt::event_token const& token) noexcept
    {
        auto lock{ m_lock.lock_exclusive() };
        m_foregroundHandlers.remove(token);
    }

    HRESULT __stdcall PushNotificationManager::InvokeAll(_In_ ULONG length, _In_ byte* payload, _Out_ BOOL* foregroundHandled) noexcept try
    {
        auto args = winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payload, length);

        auto lock{ m_lock.lock_exclusive() };
        m_foregroundHandlers(*this, args);
        *foregroundHandled = args.Handled();
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT __stdcall PushNotificationManager::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector */) noexcept try
    {
        BOOL foregroundHandled = true;
        THROW_IF_FAILED(InvokeAll(payloadLength, payload, &foregroundHandled));

        if (!foregroundHandled)
        {
            if (!AppModel::Identity::IsPackagedProcess())
            {
                wil::unique_cotaskmem_string processName;
                THROW_IF_FAILED(GetCurrentProcessPath(processName));
                THROW_IF_FAILED(PushNotificationHelpers::ProtocolLaunchHelper(processName.get(), payloadLength, payload));
            }
        }

        return S_OK;
    }
    CATCH_RETURN();
}
