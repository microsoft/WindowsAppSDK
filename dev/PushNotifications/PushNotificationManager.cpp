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

constexpr std::wstring_view backgroundTaskName = L"PushBackgroundTaskName"sv;
constexpr std::wstring_view expectedPushServerArgs = L"----WindowsAppRuntimePushServer:"sv;

static wil::unique_event g_waitHandleForArgs;
static winrt::guid g_comServerClsid{ GUID_NULL };

wil::unique_event& GetWaitHandleForArgs()
{
    return g_waitHandleForArgs;
}

namespace winrt
{
    using namespace Windows::ApplicationModel::Core;
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

    void PushNotificationManager::RegisterSinkHelper()
    {
        bool registeredEvent{ false };
        {
            auto lock{ m_lock.lock_shared() };
            registeredEvent = bool(m_foregroundHandlers);
        }

        if (registeredEvent)
        {
            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                auto appUserModelId{ PushNotificationHelpers::GetAppUserModelId() };

                // Register a sink with platform which is initialized in the current process
                THROW_IF_FAILED(PushNotifications_RegisterNotificationSinkForFullTrustApplication(appUserModelId.get(), PushNotificationManager::Default().as<ABI::Microsoft::Internal::PushNotifications::INotificationListener>().get()));
            }
            else
            {
                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                // Register a sink with platform brokered through PushNotificationsLongRunningProcess
                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterForegroundActivator(PushNotificationManager::Default().as<IWpnForegroundSink>().get(), m_processName.get()));

                winrt::guid registeredClsid{ GUID_NULL };
                {
                    auto lock{ m_lock.lock_shared() };
                    registeredClsid = m_registeredClsid;
                }
                // m_registeredClsid is set to GUID_NULL for unpackaged applications
                THROW_IF_FAILED(notificationsLongRunningPlatform->RegisterLongRunningActivatorWithClsid(m_processName.get(), registeredClsid));
            }
        }
    }

    void PushNotificationManager::UnregisterSinkHelper()
    {
        if (PushNotificationHelpers::IsPackagedAppScenario())
        {
            auto appUserModelId{ PushNotificationHelpers::GetAppUserModelId() };
            THROW_IF_FAILED(PushNotifications_UnregisterNotificationSinkForFullTrustApplication(appUserModelId.get()));
        }
        else
        {
            auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
            THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterForegroundActivator(m_processName.get()));
            THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterLongRunningActivator(m_processName.get()));
        }
    }

    PushNotificationManager::PushNotificationManager()
    {
        THROW_IF_FAILED(GetCurrentProcessPath(m_processName));

        if (AppModel::Identity::IsPackagedProcess())
        {
            // Returns ComActivator CLSID from registry. This CLSID provided in manifest is registered when a packaged app is installed
            THROW_IF_FAILED(PushNotificationHelpers::GetComRegistrationFromRegistry(expectedPushServerArgs.data(), m_registeredClsid));
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

                        // Need to recreate the Foreground sinks since channel creation removes the old sink
                        RegisterSinkHelper();
                    }
                    else
                    {
                        auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                        // AppId is generated by PushNotificationLongRunningTask singleton
                        wil::unique_cotaskmem_string unpackagedAppUserModelId;
                        THROW_IF_FAILED(notificationPlatform->RegisterFullTrustApplication(m_processName.get(), remoteId, &unpackagedAppUserModelId));

                        THROW_IF_FAILED(CreateChannelWithRemoteIdHelper(unpackagedAppUserModelId, remoteId, channelInfo));

                        // Need to recreate the Foreground sinks since channel creation removes the old sink
                        RegisterSinkHelper();

                        std::wstring toastAppId{ RetrieveNotificationAppId() };
                        THROW_IF_FAILED(notificationPlatform->AddToastRegistrationMapping(m_processName.get(), toastAppId.c_str()));
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
                    UnregisterSinkHelper(); // Need to clean up sinks if failure occurs.
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
        for (auto task : tasks)
        {
            if (task.Value().Name() == backgroundTaskFullName)
            {
                return task.Value();
            }
        }
        return nullptr;
    }

    void PushNotificationManager::Register()
    {
        {
            auto lock{ m_lock.lock_exclusive() };
            THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_OPERATION_IN_PROGRESS), m_registering, "Registration is in progress!");
            m_registering = true;
        }

        try
        {
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

                        m_registering = false;
                    }

                    UnregisterSinkHelper();
                }
                )};

                winrt::hstring backgroundTaskFullName;
                {
                    auto lock{ m_lock.lock_shared() };
                    backgroundTaskFullName = backgroundTaskName + winrt::to_hstring(m_registeredClsid);
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

                // Register a sink for the application to receive foreground raw notifications
                RegisterSinkHelper();

                {
                    auto lock{ m_lock.lock_exclusive() };
                    // Register a PushNotificationBackgroundTask to handle background activation scenarios

                    GetWaitHandleForArgs().create();
                    THROW_IF_FAILED(::CoRegisterClassObject(
                        m_registeredClsid,
                        winrt::make<PushNotificationManagerFactory>().get(),
                        CLSCTX_LOCAL_SERVER,
                        m_foregroundHandlers ? REGCLS_MULTIPLEUSE : REGCLS_SINGLEUSE,
                        &m_comActivatorRegistration));
                }

                scopeExitToCleanRegistrations.release();
            }
            else
            {
                {
                    auto lock{ m_lock.lock_shared() };
                    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_ALREADY_REGISTERED), m_singletonForegroundRegistration || m_singletonBackgroundRegistration);
                }

                auto scopeExitToCleanRegistrations{ wil::scope_exit([&]()
                {
                    {
                        auto lock { m_lock.lock_exclusive() };

                        m_comActivatorRegistration.reset();
                        m_singletonBackgroundRegistration = false;
                        m_singletonForegroundRegistration = false;
                        m_registering = false;
                    }

                    UnregisterSinkHelper();

                    auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
                    LOG_IF_FAILED(notificationsLongRunningPlatform->UnregisterFullTrustApplication(m_processName.get()));
                }) };

                auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
                wil::unique_cotaskmem_string unpackagedAppUserModelId;
                // Apps treated as unpackaged need to call RegisterFullTrustApplication and register with the LRP
                THROW_IF_FAILED(notificationPlatform->RegisterFullTrustApplication(m_processName.get(), GUID_NULL, &unpackagedAppUserModelId));

                // Register a sink for the application to receive foreground raw notifications
                RegisterSinkHelper();
                {
                    auto lock{ m_lock.lock_exclusive() };
                    m_singletonForegroundRegistration = true;
                    m_singletonBackgroundRegistration = true;
                }

                // Register a COM object for the PushNotificationLongRunningProcess to CoCreate in background activation scenarios
                if (AppModel::Identity::IsPackagedProcess())
                {
                    auto lock{ m_lock.lock_exclusive() };
                    GetWaitHandleForArgs().create();
                    THROW_IF_FAILED(::CoRegisterClassObject(
                        m_registeredClsid,
                        winrt::make<PushNotificationManagerFactory>().get(),
                        CLSCTX_LOCAL_SERVER,
                        m_foregroundHandlers ? REGCLS_MULTIPLEUSE : REGCLS_SINGLEUSE,
                        &m_comActivatorRegistration));
                }

                scopeExitToCleanRegistrations.release();
            }
        }
        catch (...)
        {
            PushNotificationTelemetry::ActivatorRegisteredByApi(wil::ResultFromCaughtException());
            throw;
        }

        {
            auto lock{ m_lock.lock_exclusive() };
            m_registering = false;
        }
    }

    void PushNotificationManager::Unregister()
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

        try
        {
            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                {
                    auto lock{ m_lock.lock_exclusive() };
                    THROW_HR_IF_MSG(E_UNEXPECTED, !m_comActivatorRegistration, "Need to call Register() before calling Unregister().");
                    // m_comActivatorRegistration handles multiple unregistrations
                    m_comActivatorRegistration.reset();
                }

                UnregisterSinkHelper();
            }
            else
            {
                if (AppModel::Identity::IsPackagedProcess())
                {
                    auto lock{ m_lock.lock_exclusive() };
                    THROW_HR_IF_MSG(E_UNEXPECTED, !m_comActivatorRegistration, "Need to call Register() before calling Unregister().");
                    m_comActivatorRegistration.reset();
                }

                {
                    auto lock{ m_lock.lock_exclusive() };
                    THROW_HR_IF_MSG(E_UNEXPECTED, !m_singletonForegroundRegistration, "Need to call Register() before calling Unregister().");
                }

                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
                // Unregister foreground sink with the Long Running Process Singelton
                THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterForegroundActivator(m_processName.get()));

                {
                    auto lock{ m_lock.lock_exclusive() };
                    m_singletonForegroundRegistration = false;
                }
            }
        }
        catch (...)
        {
            PushNotificationTelemetry::ActivatorUnregisteredByApi(wil::ResultFromCaughtException());
            throw;
        }

        PushNotificationTelemetry::ActivatorUnregisteredByApi(S_OK);
    }

    void PushNotificationManager::UnregisterAll()
    {
        bool unregisterCompleted{ false };
        {
            auto lock{ m_lock.lock_exclusive() };
            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                unregisterCompleted = !m_comActivatorRegistration;
            }
            else
            {
                if (AppModel::Identity::IsPackagedProcess())
                {
                    unregisterCompleted = (!m_singletonForegroundRegistration && !m_comActivatorRegistration);
                }
                else
                {
                    unregisterCompleted = !m_singletonForegroundRegistration;
                }
            }
        }

        if (!unregisterCompleted)
        {
            Unregister();
        }

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

        try
        {
            try
            {
                auto lock{ m_lock.lock_exclusive() };
                if (m_channel != nullptr)
                {
                    m_channel.Close();
                }
            }
            catch (...)
            {
                LOG_IF_FAILED(wil::ResultFromCaughtException());
            }
           

            if (PushNotificationHelpers::IsPackagedAppScenario())
            {
                {
                    auto lock{ m_lock.lock_exclusive() };
                    THROW_HR_IF_NULL(E_UNEXPECTED, m_pushTriggerRegistration);

                    m_pushTriggerRegistration.Unregister(true);
                    m_pushTriggerRegistration = nullptr;
                }
            }
            else
            {
                auto notificationsLongRunningPlatform{ PushNotificationHelpers::GetNotificationPlatform() };

                {
                    auto lock{ m_lock.lock_exclusive() };
                    THROW_HR_IF(E_UNEXPECTED, !m_singletonBackgroundRegistration);
                }

                // Removes the Long Running Singleton sink registered with platform for both packaged and unpackaged applications 
                THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterLongRunningActivator(m_processName.get()));

                THROW_IF_FAILED(notificationsLongRunningPlatform->UnregisterFullTrustApplication(m_processName.get()));

                {
                    auto lock{ m_lock.lock_exclusive() };
                    m_singletonBackgroundRegistration = false;
                }
            }
        }
        catch (...)
        {
            PushNotificationTelemetry::ActivatorUnregisteredByApi(wil::ResultFromCaughtException());
            throw;
        }

        PushNotificationTelemetry::ActivatorUnregisteredByApi(S_OK);
    }

    winrt::event_token PushNotificationManager::PushReceived(TypedEventHandler<winrt::Microsoft::Windows::PushNotifications::PushNotificationManager, winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler)
    {
        {
            auto lock{ m_lock.lock_shared() };
            THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), m_comActivatorRegistration || m_singletonBackgroundRegistration, "Must register event handlers before calling Register().");
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
        if (m_foregroundHandlers)
        {
            m_foregroundHandlers(*this, args);
            *foregroundHandled = true;
        }
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT __stdcall PushNotificationManager::OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING /*correlationVector */) noexcept try
    {
        BOOL handlerRegistered{ false };
        THROW_IF_FAILED(InvokeAll(payloadLength, payload, &handlerRegistered));
        THROW_HR_IF(E_UNEXPECTED, !handlerRegistered);

        return S_OK;
    }
    CATCH_RETURN();

    void PushNotificationManager::Run(winrt::IBackgroundTaskInstance const& taskInstance)
    {
        auto appProperties = winrt::CoreApplication::Properties();
        // This function can be triggered by either OS background infrastructure
        // or by the PushNotificationsLongRunningProcess.
        if (!m_firstNotificationReceived)
        {
            m_firstNotificationReceived = true;
            std::wstring commandLine{ GetCommandLine() };
            auto pos{ commandLine.find(expectedPushServerArgs) };
            if (pos == std::wstring::npos) // Any launch kind that is not PushNotification
            {
                THROW_HR_IF(E_UNEXPECTED, m_foregroundHandlers);

                winrt::guid registeredClsid{ GUID_NULL };
                THROW_IF_FAILED(PushNotificationHelpers::GetComRegistrationFromRegistry(expectedPushServerArgs.data(), registeredClsid));

                auto backgroundTask{ winrt::create_instance<IBackgroundTask>(registeredClsid, CLSCTX_ALL) };
                backgroundTask.Run(taskInstance);
                return;
            }
        }

        if (PushNotificationHelpers::IsPackagedAppScenario())
        {
            winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs activatedEventArgs{ winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(taskInstance) };
            appProperties.Insert(ACTIVATED_EVENT_ARGS_KEY, activatedEventArgs);
        }
        else
        {
            // Need to mock a RawNotification object instead of winrt boxing: https://github.com/microsoft/WindowsAppSDK/issues/2075
            winrt::hstring payload{ winrt::unbox_value<winrt::hstring>(taskInstance.TriggerDetails()) };
            winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs activatedEventArgs{ winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payload.c_str()) };
            appProperties.Insert(LRP_ACTIVATED_EVENT_ARGS_KEY, activatedEventArgs);
        }

        SetEvent(GetWaitHandleForArgs().get());
    }

}
