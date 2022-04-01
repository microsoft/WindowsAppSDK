#include "pch.h"
#include "AppNotificationManager.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationManager.g.cpp"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include "externs.h"
#include "PushNotificationUtility.h"
#include "AppNotificationUtility.h"
#include <frameworkudk/pushnotifications.h>
#include <frameworkudk/toastnotifications.h>
#include <FrameworkUdk/toastnotificationsrt.h>
#include "NotificationProperties.h"
#include "NotificationTransientProperties.h"
#include "AppNotification.h"
#include <NotificationProgressData.h>
#include "AppNotificationTelemetry.h"
#include <algorithm>
#include <winerror.h>
#include <string_view>
#include <winrt/Windows.Foundation.Collections.h>
#include <WindowsAppRuntime.SelfContained.h>
#include <ShellLocalization.h>

using namespace std::literals;

constexpr std::wstring_view expectedAppServerArgs = L"----AppNotificationActivated:"sv;

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Microsoft::Windows::AppNotifications;
	using namespace Windows::ApplicationModel::Core;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
    using namespace ::ABI::Windows::Foundation::Collections;
}

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

using namespace Microsoft::Windows::AppNotifications::Helpers;
using namespace Microsoft::Windows::AppNotifications::ShellLocalization;

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    AppNotificationManager::AppNotificationManager() : m_processName(GetCurrentProcessPath()), m_appId(RetrieveNotificationAppId()) {}

    winrt::Microsoft::Windows::AppNotifications::AppNotificationManager AppNotificationManager::Default()
    {
        auto appProperties{ winrt::CoreApplication::Properties() };

        static wil::srwlock lock;

        auto criticalSection{ lock.lock_exclusive() };
        auto storedAppNotificationManager{ appProperties.TryLookup(STORED_APPNOTIFICATION_MANAGER_KEY) };
        if (storedAppNotificationManager)
        {
            return storedAppNotificationManager.as<winrt::Microsoft::Windows::AppNotifications::AppNotificationManager>();
        }
        else
        {
            // Store the AppNotificationManager in the COM static store
            auto appNotificationManager{ winrt::make<AppNotificationManager>() };
            appProperties.Insert(STORED_APPNOTIFICATION_MANAGER_KEY, appNotificationManager);
            return appNotificationManager;
        }
    }

    winrt::Windows::Foundation::IInspectable AppNotificationManager::AppNotificationDeserialize(winrt::Windows::Foundation::Uri const& uri)
    {
        auto appNotificationManager{ Default() };
        auto deserializer{ appNotificationManager.as<INotificationManagerDeserializer>() };
        return deserializer->Deserialize(uri);
    }

    winrt::Windows::Foundation::IInspectable AppNotificationManager::Deserialize(winrt::Windows::Foundation::Uri const& /* uri */)
    {
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_TIMEOUT), !m_waitHandleForArgs.wait(c_receiveArgsTimeoutInMSec));
        return m_activatedEventArgs;
    }

    void AppNotificationManager::Register()
    {
        HRESULT hr{ S_OK };

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogRegister(hr, m_appId);
        }) };

        try
        {
            {
                auto lock{ m_lock.lock_exclusive() };
                THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_OPERATION_IN_PROGRESS), m_registering, "Registration is in progress!");
                m_registering = true;
            }

            auto registeringScopeExit{ wil::scope_exit([&]()
            {
                auto lock { m_lock.lock_exclusive() };
                m_registering = false;
            }) };

            winrt::guid storedComActivatorGuid{ GUID_NULL };
            if (!PushNotificationHelpers::IsPackagedAppScenario())
            {
                if (!AppModel::Identity::IsPackagedProcess())
                {
                    THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(m_appId.c_str(), GUID_NULL));

                    storedComActivatorGuid = RegisterComActivatorGuidAndAssets();
                }

                if (!WindowsAppRuntime::SelfContained::IsSelfContained())
                {
                    auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
                    THROW_IF_FAILED(notificationPlatform->AddToastRegistrationMapping(m_processName.c_str(), m_appId.c_str()));
                }
            }

            winrt::guid registeredClsid{ GUID_NULL };
            if (AppModel::Identity::IsPackagedProcess())
            {
                registeredClsid = PushNotificationHelpers::GetComRegistrationFromRegistry(expectedAppServerArgs.data());
            }

            // Create event handle before COM Registration otherwise if a notification arrives will lead to race condition
            m_waitHandleForArgs.create();

            {
                auto lock{ m_lock.lock_exclusive() };
                THROW_HR_IF_MSG(E_INVALIDARG, m_notificationComActivatorRegistration, "Already Registered for App Notifications!");

                // Check if the caller has registered event handlers, if so the REGCLS_MULTIPLEUSE flag will cause COM to ensure that all activators
                // are routed inproc, otherwise with REGCLS_MULTIPLEUSE COM will launch a new process of the Win32 app for each invocation.
                THROW_IF_FAILED(::CoRegisterClassObject(
                    AppModel::Identity::IsPackagedProcess() ? registeredClsid : storedComActivatorGuid,
                    winrt::make<AppNotificationManagerFactory>().get(),
                    CLSCTX_LOCAL_SERVER,
                    m_notificationHandlers ? REGCLS_MULTIPLEUSE : REGCLS_SINGLEUSE,
                    &m_notificationComActivatorRegistration));
            }
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    // This assumes that the caller has taken an exclusive lock
    void AppNotificationManager::UnregisterHelper()
    {
        m_notificationComActivatorRegistration.reset();
    }

    void AppNotificationManager::Unregister()
    {
        HRESULT hr{ S_OK };

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogUnregister(hr, m_appId);
        }) };

        try
        {
            auto lock{ m_lock.lock_exclusive() };
            THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_OPERATION_IN_PROGRESS), m_registering, "Register or Unregister currently in progress!");
            m_registering = true;
            auto scope_exit = wil::scope_exit(
                [&] {
                    m_registering = false;
                });

            THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !m_notificationComActivatorRegistration, "Not Registered for App Notifications!");
            UnregisterHelper();
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    void AppNotificationManager::UnregisterAll()
    {
        HRESULT hr{ S_OK };

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogUnregisterAll(hr, m_appId);
        }) };

        try
        {
            {
                auto lock{ m_lock.lock_exclusive() };
                UnregisterHelper();
                THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_OPERATION_IN_PROGRESS), m_registering, "Register or Unregister currently in progress!");
                m_registering = true;
            }

            auto scope_exit = wil::scope_exit(
                [&] {
                    auto lock{ m_lock.lock_exclusive() };
                    m_registering = false;
                });

            // Remove any Registrations from the Long Running Process that are necessary for Cloud toasts
            if (!PushNotificationHelpers::IsPackagedAppScenario() && !WindowsAppRuntime::SelfContained::IsSelfContained())
            {
                auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
                THROW_IF_FAILED(notificationPlatform->RemoveToastRegistrationMapping(m_processName.c_str()));
            }

            if (!AppModel::Identity::IsPackagedProcess())
            {
                // If the app icon was inferred from process, then we should clean it up.
                // Do not fail this function if such a file doesn't exist.
                winrt::hresult deleteIconResult{ DeleteIconFromCache() };
                THROW_HR_IF(deleteIconResult, FAILED(deleteIconResult) && deleteIconResult != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));

                std::wstring storedComActivatorString;
                THROW_IF_FAILED(GetActivatorGuid(storedComActivatorString));
                UnRegisterComServer(storedComActivatorString);

                UnRegisterNotificationAppIdentifierFromRegistry();
                THROW_IF_FAILED(PushNotifications_UnregisterFullTrustApplication(m_appId.c_str()));
            }
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::event_token AppNotificationManager::NotificationInvoked(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::AppNotifications::AppNotificationManager, winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs> const& handler)
    {
        auto lock{ m_lock.lock_exclusive() };
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), m_notificationComActivatorRegistration, "Must register event handlers before calling Register()");
        return m_notificationHandlers.add(handler);
    }

    void AppNotificationManager::NotificationInvoked(winrt::event_token const& token) noexcept
    {
        auto lock{ m_lock.lock_exclusive() };
        m_notificationHandlers.remove(token);
    }

    IFACEMETHODIMP AppNotificationManager::Activate(
        LPCWSTR appUserModelId,
        LPCWSTR invokedArgs,
        [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
        [[maybe_unused]] ULONG dataCount) noexcept try
    {

        winrt::IMap<winrt::hstring, winrt::hstring> userInput{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        for (unsigned long i = 0; i < dataCount; i++)
        {
            userInput.Insert(data[i].Key, data[i].Value);
        }

        winrt::AppNotificationActivatedEventArgs activatedEventArgs = winrt::make<implementation::AppNotificationActivatedEventArgs>(invokedArgs, userInput);

        // Need to store the first notification in the case of ToastActivation

        auto lock{ m_lock.lock_exclusive() };
        if (!m_firstNotificationReceived)
        {
            m_firstNotificationReceived = true;

            std::wstring commandLine{ GetCommandLine() };

            // If the app was not launched due to ToastActivation, we will launch a new instance or invoke the foreground handlers.
            // Otherwise we store the EventArgs and signal to the Main thread
            auto pos{ commandLine.find(c_notificationActivatedArgument) };
            if (pos == std::wstring::npos) // Any launch kind that is not AppNotification
            {
                // If the Process was launched due to other Activation Kinds, we will need to
                // re-route the payload to a new process if there are no registered event handlers.
                if (!m_notificationHandlers)
                {
                    winrt::guid registeredClsid{ GUID_NULL };
                    if (AppModel::Identity::IsPackagedProcess())
                    {
                        registeredClsid = PushNotificationHelpers::GetComRegistrationFromRegistry(expectedAppServerArgs.data());
                    }
                    else
                    { 
                        registeredClsid = RegisterComActivatorGuidAndAssets();
                    }

                    auto notificationCallback{ winrt::create_instance<INotificationActivationCallback>(registeredClsid, CLSCTX_ALL) };
                    THROW_IF_FAILED(notificationCallback->Activate(appUserModelId, invokedArgs, data, dataCount));
                }
                else
                {
                    m_notificationHandlers(Default(), activatedEventArgs);
                }
            }
            else
            {
                m_activatedEventArgs = activatedEventArgs;
                SetEvent(m_waitHandleForArgs.get());
            }
        }
        else
        {
            m_notificationHandlers(Default(), activatedEventArgs);
        }

        return S_OK;
    }
    CATCH_RETURN()

    void AppNotificationManager::Show(winrt::Microsoft::Windows::AppNotifications::AppNotification const& notification)
    {
        THROW_HR_IF(WPN_E_NOTIFICATION_POSTED, notification.Id() != 0);

        HRESULT hr{ S_OK };

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogShow(hr, m_appId, notification.Payload(), notification.Tag(), notification.Group());
        }) };

        try
        {
            winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties> notificationProperties = winrt::make_self<NotificationProperties>(notification);

            winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties> notificationTransientProperties = winrt::make_self<NotificationTransientProperties>(notification);

            DWORD notificationId = 0;
            THROW_IF_FAILED(ToastNotifications_PostToast(m_appId.c_str(), notificationProperties.get(), notificationTransientProperties.get(), &notificationId));

            THROW_HR_IF(E_UNEXPECTED, notificationId == 0);

            implementation::AppNotification* notificationImpl = get_self<implementation::AppNotification>(notification);
            notificationImpl->SetNotificationId(notificationId);
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> AppNotificationManager::UpdateAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag, hstring const group)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, tag == winrt::hstring(L""), "Update operation isn't guaranteed to find a specific notification to replace correctly.");
        THROW_HR_IF_MSG(E_INVALIDARG, data.SequenceNumber() == 0, "Sequence Number for Updates should be greater than 0!");

        HRESULT hr{ S_OK };

        auto strong = get_strong();
        co_await resume_background();

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogUpdateAsync(hr, m_appId, tag, group);
        }) };

        try
        {
            winrt::com_ptr<ToastABI::IToastProgressData> toastProgressData{ winrt::make_self<NotificationProgressData>(data) };

            hr = ToastNotifications_UpdateNotificationData(m_appId.c_str(), tag.c_str(), group.c_str(), toastProgressData.get());

            if (SUCCEEDED(hr))
            {
                co_return winrt::AppNotificationProgressResult::Succeeded;
            }
            else if (hr == E_NOT_SET)
            {
                co_return winrt::AppNotificationProgressResult::AppNotificationNotFound;
            }
            else
            {
                THROW_HR(hr);
            }
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> AppNotificationManager::UpdateAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag)
    {
        co_return co_await UpdateAsync(data, tag, L"");
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationSetting AppNotificationManager::Setting()
    {
        HRESULT hr{ S_OK };

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogSetting(hr, m_appId);
        }) };

        try
        {
            DWORD appNotificationSetting{ 0 };
            ToastNotifications_QuerySettings(m_appId.c_str(), &appNotificationSetting);
            return static_cast<winrt::Microsoft::Windows::AppNotifications::AppNotificationSetting>(appNotificationSetting);
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByIdAsync(uint32_t notificationId)
    {
        THROW_HR_IF(E_INVALIDARG, notificationId == 0);

        HRESULT hr{ S_OK };

        auto strong = get_strong();
        co_await winrt::resume_background();

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogRemoveByIdAsync(hr, m_appId, notificationId);
        }) };

        try
        {
            THROW_IF_FAILED(ToastNotifications_RemoveToast(m_appId.c_str(), notificationId));
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByTagAsync(hstring const tag)
    {
        THROW_HR_IF(E_INVALIDARG, tag == winrt::hstring(L""));

        HRESULT hr{ S_OK };

        auto strong = get_strong();
        co_await winrt::resume_background();

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogRemoveByTagAsync(hr, m_appId, tag);
        }) };

        try
        {
            THROW_IF_FAILED(ToastNotifications_RemoveToastsWithTagAndGroup(m_appId.c_str(), tag.c_str(), nullptr));
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByTagAndGroupAsync(hstring const tag, hstring const group)
    {
        THROW_HR_IF(E_INVALIDARG, tag == winrt::hstring(L""));
        THROW_HR_IF(E_INVALIDARG, group == winrt::hstring(L""));

        HRESULT hr{ S_OK };

        auto strong = get_strong();
        co_await winrt::resume_background();

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogRemoveByTagAndGroupAsync(hr, m_appId, tag, group);
        }) };

        try
        {
            THROW_IF_FAILED(ToastNotifications_RemoveToastsWithTagAndGroup(m_appId.c_str(), tag.c_str(), group.c_str()));
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByGroupAsync(hstring const group)
    {
        THROW_HR_IF(E_INVALIDARG, group == winrt::hstring(L""));

        HRESULT hr{ S_OK };

        auto strong = get_strong();
        co_await winrt::resume_background();

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogRemoveByGroupAsync(hr, m_appId);
        }) };

        try
        {
            THROW_IF_FAILED(ToastNotifications_RemoveToastsWithTagAndGroup(m_appId.c_str(), nullptr, group.c_str()));
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveAllAsync()
    {
        HRESULT hr{ S_OK };

        auto strong = get_strong();
        co_await winrt::resume_background();

        auto logTelemetry{ wil::scope_exit([&]() {
            AppNotificationTelemetry::LogRemoveAllAsync(hr, m_appId);
        }) };

        try
        {
            THROW_IF_FAILED(ToastNotifications_RemoveAllToastsForApp(m_appId.c_str()));
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::AppNotifications::AppNotification>> AppNotificationManager::GetAllAsync()
    {
        HRESULT hr{ S_OK };

        auto strong = get_strong();
        co_await winrt::resume_background();

        auto logTelemetry{ wil::scope_exit([&](){
            AppNotificationTelemetry::LogGetAllAsync(hr, m_appId);
        }) };

        try
        {
            winrt::com_ptr<ToastABI::IVector<ToastABI::INotificationProperties*>> toastPropertiesCollection{};
            auto result{ ToastNotifications_GetHistory(m_appId.c_str(), toastPropertiesCollection.put()) };

            THROW_HR_IF(result, result != S_OK && result != E_NOT_SET); // Swallow E_NOT_SET and return an empty properties vector to signal that there are no active toasts

            unsigned int count{};
            if (toastPropertiesCollection)
            {
                THROW_IF_FAILED(toastPropertiesCollection->get_Size(&count));
            }

            winrt::IVector<winrt::Microsoft::Windows::AppNotifications::AppNotification> toastNotifications{ winrt::single_threaded_vector<winrt::Microsoft::Windows::AppNotifications::AppNotification>() };

            for (unsigned i = 0; i < count; ++i)
            {
                ToastABI::INotificationProperties* toastProperties;
                THROW_IF_FAILED(toastPropertiesCollection->GetAt(i, &toastProperties));

                auto toastNotification{ ToastNotificationFromToastProperties(toastProperties) };

                toastNotifications.Append(toastNotification);
            }

            co_return toastNotifications;
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();
            throw;
        }
    }
}
