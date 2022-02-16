#include "pch.h"
#include "AppNotificationManager.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationManager.g.cpp"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include "AppNotificationActivationCallback.h"
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

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    winrt::Microsoft::Windows::AppNotifications::AppNotificationManager AppNotificationManager::Default()
    {
        static auto appNotificationManager{winrt::make<AppNotificationManager>()};
        return appNotificationManager;
    }

    void AppNotificationManager::Register(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivationInfo const& details)
    {
        THROW_HR_IF_NULL(E_INVALIDARG, details);

        std::wstring storedComActivatorString;
        if (!PushNotificationHelpers::IsPackagedAppScenario())
        {
            std::wstring toastAppId{ RetrieveNotificationAppId() };
            if (!AppModel::Identity::IsPackagedProcess())
            {
                THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(toastAppId.c_str(), GUID_NULL));

                storedComActivatorString = RegisterComActivatorGuidAndAssets(details);
                // Remove braces around the guid string
                storedComActivatorString = storedComActivatorString.substr(1, storedComActivatorString.size() - 2);
            }

            wil::unique_cotaskmem_string processName;
            THROW_IF_FAILED(GetCurrentProcessPath(processName));
            auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
            THROW_IF_FAILED(notificationPlatform->AddToastRegistrationMapping(processName.get(), toastAppId.c_str()));
        }

        {
            auto lock{ m_registrationLock.lock_exclusive() };
            THROW_HR_IF_MSG(E_INVALIDARG, m_notificationComActivatorRegistration, "Already Registered for App Notifications!");
            THROW_IF_FAILED(::CoRegisterClassObject(
                AppModel::Identity::IsPackagedProcess() ? details.TaskClsid() : winrt::guid(storedComActivatorString),
                winrt::make<AppNotificationActivationCallbackFactory>().get(),
                CLSCTX_LOCAL_SERVER,
                REGCLS_MULTIPLEUSE,
                &m_notificationComActivatorRegistration));
        }

        GetWaitHandleForArgs().create();
    }

    void AppNotificationManager::Register()
    {
        THROW_HR(E_NOTIMPL);
    }

    void AppNotificationManager::Unregister()
    {
        auto lock{ m_registrationLock.lock_exclusive() };
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !m_notificationComActivatorRegistration, "Not Registered for App Notifications!");
        m_notificationComActivatorRegistration.reset();
    }

    void AppNotificationManager::UnregisterAll()
    {
        Unregister();

        // Remove any Registrations from the Long Running Process that are necessary for Cloud toasts
        if (!PushNotificationHelpers::IsPackagedAppScenario())
        {
            wil::unique_cotaskmem_string processName;
            THROW_IF_FAILED(GetCurrentProcessPath(processName));
            auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
            THROW_IF_FAILED(notificationPlatform->RemoveToastRegistrationMapping(processName.get()));
        }

        if (!AppModel::Identity::IsPackagedProcess())
        {
            std::wstring toastAppId{ RetrieveNotificationAppId() };
            std::wstring storedComActivatorString;
            THROW_IF_WIN32_ERROR(GetActivatorGuid(storedComActivatorString));
            UnRegisterComServer(storedComActivatorString);
            
            UnRegisterNotificationAppIdentifierFromRegistry();
            THROW_IF_FAILED(PushNotifications_UnregisterFullTrustApplication(toastAppId.c_str()));
        }
    }

    winrt::event_token AppNotificationManager::NotificationInvoked(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::AppNotifications::AppNotificationManager, winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs> const& handler)
    {
        auto lock{ m_registrationLock.lock_exclusive() };
        return m_notificationHandlers.add(handler);
    }

    void AppNotificationManager::NotificationInvoked(winrt::event_token const& token) noexcept
    {
        auto lock{ m_registrationLock.lock_exclusive() };
        m_notificationHandlers.remove(token);
    }

    void AppNotificationManager::Show(winrt::Microsoft::Windows::AppNotifications::AppNotification const& notification)
    {
        THROW_HR_IF(WPN_E_NOTIFICATION_POSTED, notification.Id() != 0);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties> notificationProperties = winrt::make_self<NotificationProperties>(notification);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties> notificationTransientProperties = winrt::make_self<NotificationTransientProperties>(notification);

        auto notificationAppId{ ::Microsoft::Windows::AppNotifications::Helpers::RetrieveNotificationAppId() };

        DWORD notificationId = 0;
        THROW_IF_FAILED(ToastNotifications_PostToast(notificationAppId.c_str(), notificationProperties.get(), notificationTransientProperties.get(), &notificationId));

        THROW_HR_IF(E_UNEXPECTED, notificationId == 0);

        winrt::Microsoft::Windows::AppNotifications::implementation::AppNotification* notificationImpl = get_self< winrt::Microsoft::Windows::AppNotifications::implementation::AppNotification>(notification);
        notificationImpl->SetNotificationId(notificationId);
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> AppNotificationManager::UpdateAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag, hstring const group)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, tag == winrt::hstring(L""), "Update operation isn't guarenteed to find a specific notification to replace correctly.");
        THROW_HR_IF_MSG(E_INVALIDARG, data.SequenceNumber() == 0, "Sequence Number for Updates should be greater than 0!");

        std::wstring appId{ RetrieveNotificationAppId() };

        winrt::com_ptr<ToastABI::IToastProgressData> toastProgressData{ winrt::make_self<NotificationProgressData>(data) };

        auto hr = ToastNotifications_UpdateNotificationData(appId.c_str(), tag.c_str(), group.c_str(), toastProgressData.get());

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

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> AppNotificationManager::UpdateAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag)
    {
        co_return co_await UpdateAsync(data, tag, L"");
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotificationSetting AppNotificationManager::Setting()
    {
        std::wstring appId{ RetrieveNotificationAppId() };
        DWORD appNotificationSetting{ 0 };
        ToastNotifications_QuerySettings(appId.c_str(), &appNotificationSetting);
        return static_cast<winrt::Microsoft::Windows::AppNotifications::AppNotificationSetting>(appNotificationSetting);
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByIdAsync(uint32_t notificationId)
    {
        THROW_HR_IF(E_INVALIDARG, notificationId == 0);

        co_await winrt::resume_background();

        std::wstring appId{ RetrieveNotificationAppId() };
        THROW_IF_FAILED(ToastNotifications_RemoveToast(appId.c_str(), notificationId));
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByTagAsync(hstring tag)
    {
        THROW_HR_IF(E_INVALIDARG, tag == winrt::hstring(L""));
		
        std::wstring _tag{ tag.c_str() };

        co_await winrt::resume_background();

        std::wstring appId{ RetrieveNotificationAppId() };
        THROW_IF_FAILED(ToastNotifications_RemoveToastsWithTagAndGroup(appId.c_str(), _tag.c_str(), nullptr));
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByTagAndGroupAsync(hstring tag, hstring group)
    {
        THROW_HR_IF(E_INVALIDARG, tag == winrt::hstring(L""));
        THROW_HR_IF(E_INVALIDARG, group == winrt::hstring(L""));
					
        std::wstring _tag{ tag.c_str() };
        std::wstring _group{ group.c_str() };

        co_await winrt::resume_background();

        std::wstring appId{ RetrieveNotificationAppId() };
        THROW_IF_FAILED(ToastNotifications_RemoveToastsWithTagAndGroup(appId.c_str(), _tag.c_str(), _group.c_str()));
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveByGroupAsync(hstring group)
    {
        THROW_HR_IF(E_INVALIDARG, group == winrt::hstring(L""));
		
        std::wstring _group{ group.c_str() };

        co_await winrt::resume_background();

        std::wstring appId{ RetrieveNotificationAppId() };
        THROW_IF_FAILED(ToastNotifications_RemoveToastsWithTagAndGroup(appId.c_str(), nullptr, _group.c_str()));
    }

    winrt::Windows::Foundation::IAsyncAction AppNotificationManager::RemoveAllAsync()
    {
        co_await winrt::resume_background();

        std::wstring appId{ RetrieveNotificationAppId() };
        THROW_IF_FAILED(ToastNotifications_RemoveAllToastsForApp(appId.c_str()));
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::AppNotifications::AppNotification>> AppNotificationManager::GetAllAsync()
    {
        co_await winrt::resume_background();

        std::wstring appId{ RetrieveNotificationAppId() };
        winrt::com_ptr<ToastABI::IVector<ToastABI::INotificationProperties*>> toastPropertiesCollection{};
        auto result{ ToastNotifications_GetHistory(appId.c_str(), toastPropertiesCollection.put()) };

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

    bool AppNotificationManager::ContainsInvokeHandler()
    {
        auto lock{ m_registrationLock.lock_shared() };
        return (bool)m_notificationHandlers;
    }

    void AppNotificationManager::InvokeHandler(const winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs& args)
    {
        auto lock{ m_registrationLock.lock_shared() };
        m_notificationHandlers(*this, args);
    }
}
