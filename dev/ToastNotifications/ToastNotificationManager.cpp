#include "pch.h"
#include "ToastNotificationManager.h"
#include "Microsoft.Windows.ToastNotifications.ToastNotificationManager.g.cpp"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include "ToastActivationCallback.h"
#include "externs.h"
#include "PushNotificationUtility.h"
#include "ToastNotificationUtility.h"
#include <frameworkudk/pushnotifications.h>
#include <frameworkudk/toastnotifications.h>
#include <FrameworkUdk/toastnotificationsrt.h>
#include "NotificationProperties.h"
#include <NotificationTransientProperties.h>

static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs>> g_toastHandlers;

winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs>>& GetToastHandlers()
{
    return g_toastHandlers;
}

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::Foundation;
    using namespace Windows::ApplicationModel::Core;
}

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    static wil::unique_com_class_object_cookie s_toastcomActivatorRegistration;

    winrt::Microsoft::Windows::ToastNotifications::ToastNotificationManager ToastNotificationManager::Default()
    {
        static auto toastNotificationManager{ winrt::make<ToastNotificationManager>() };
        return toastNotificationManager;
    }

    void ToastNotificationManager::RegisterActivator(winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo const& details)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, s_toastcomActivatorRegistration, "Toast activator already registered.");

        THROW_HR_IF_NULL(E_INVALIDARG, details);

        std::wstring storedComActivatorString;
        if (!PushNotificationHelpers::IsPackagedAppScenario())
        {
            std::wstring toastAppId{ RetrieveToastAppId() };
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

        THROW_IF_FAILED(::CoRegisterClassObject(
            AppModel::Identity::IsPackagedProcess() ? details.TaskClsid() : winrt::guid(storedComActivatorString),
            winrt::make<ToastActivationCallbackFactory>().get(),
            CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE,
            &s_toastcomActivatorRegistration));

        GetWaitHandleForArgs().create();
    }

    void ToastNotificationManager::UnregisterActivator()
    {
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !s_toastcomActivatorRegistration, "Toast activator not registered.");

        s_toastcomActivatorRegistration.reset();

        if (!AppModel::Identity::IsPackagedProcess())
        {
            std::wstring storedComActivatorString;
            THROW_IF_WIN32_ERROR(GetActivatorGuid(storedComActivatorString));

            UnRegisterComServer(storedComActivatorString);
            UnRegisterToastAppIdentifierFromRegistry();

            wil::unique_cotaskmem_string processName;
            THROW_IF_FAILED(GetCurrentProcessPath(processName));
            auto notificationPlatform{ PushNotificationHelpers::GetNotificationPlatform() };
            THROW_IF_FAILED(notificationPlatform->RemoveToastRegistrationMapping(processName.get()));
        }
    }
    winrt::event_token ToastNotificationManager::ToastActivated(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs> const& handler)
    {
        return GetToastHandlers().add(handler);
    }
    void ToastNotificationManager::ToastActivated(winrt::event_token const& token)
    {
        GetToastHandlers().remove(token);
    }
    void ToastNotificationManager::ShowToast(winrt::Microsoft::Windows::ToastNotifications::ToastNotification const& toast)
    {
        THROW_HR_IF(WPN_E_NOTIFICATION_POSTED, toast.ToastId() != 0);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties> notificationProperties
            = winrt::make_self<NotificationProperties>(toast);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties> notificationTransientProperties
            = winrt::make_self<NotificationTransientProperties>(toast);

        auto toastAppId{ RetrieveToastAppId() };

        DWORD notificationId = 0;
        THROW_IF_FAILED(ToastNotifications_PostToast(toastAppId.c_str(), notificationProperties.get(), notificationTransientProperties.get(), &notificationId));

        THROW_HR_IF(E_UNEXPECTED, notificationId == 0);
        toast.ToastId(notificationId);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::ToastNotifications::ToastProgressResult> ToastNotificationManager::UpdateToastProgressDataAsync(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData /* data */, hstring /* tag */, hstring /* group */)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::ToastNotifications::ToastProgressResult> ToastNotificationManager::UpdateToastProgressDataAsync(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData /* data */, hstring /* tag */)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastNotificationSetting ToastNotificationManager::Setting()
    {
        std::wstring appId { RetrieveToastAppId() };
        DWORD toastNotificationSetting{ 0 };
        ToastNotifications_QuerySettings(appId.c_str(), &toastNotificationSetting);

        return static_cast<winrt::Microsoft::Windows::ToastNotifications::ToastNotificationSetting>(toastNotificationSetting);
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationManager::RemoveWithIdentiferAsync(uint32_t toastIdentifier)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationManager::RemoveWithTagAsync(hstring /*tag*/)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationManager::RemoveWithTagGroupAsync(hstring /*tag*/, hstring /*group*/)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationManager::RemoveGroupAsync(hstring /*group*/)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationManager::RemoveAllAsync()
    {
        co_await winrt::resume_background();

        std::wstring appId{ RetrieveToastAppId() };
        auto result{ ToastNotifications_RemoveAllToastsForApp(appId.c_str()) };

        co_return;
    }
    wil::unique_cotaskmem_string ConvertUtf8StringToWideString(unsigned long payloadLength, _In_ byte* utf8String)
    {
        int size = MultiByteToWideChar(
            CP_UTF8,
            0,
            reinterpret_cast<PCSTR>(utf8String),
            payloadLength,
            nullptr,
            0);
        THROW_LAST_ERROR_IF(size == 0);

        wil::unique_cotaskmem_string wideString = wil::make_unique_string<wil::unique_cotaskmem_string>(nullptr, size);

        size = MultiByteToWideChar(
            CP_UTF8,
            0,
            reinterpret_cast<PCSTR>(utf8String),
            payloadLength,
            wideString.get(),
            size);
        THROW_LAST_ERROR_IF(size == 0);

        return wideString;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ToastNotifications::ToastNotification>> ToastNotificationManager::GetAllAsync()
    {
        co_await winrt::resume_background();

        std::wstring appId{ RetrieveToastAppId() };
        ABI::Windows::Foundation::Collections::IVector<ABI::Microsoft::Internal::ToastNotifications::INotificationProperties*>* notificationProperties;
        auto status = ToastNotifications_GetHistory(appId.c_str(), &notificationProperties);

        THROW_HR_IF(E_NOT_SET, status != S_OK);

        unsigned int count;
        THROW_HR_IF(E_NOT_SET, notificationProperties->get_Size(&count) !=  0);
        
        THROW_HR_IF(E_NOT_SET, count == 0);

        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ToastNotifications::ToastNotification> result { winrt::single_threaded_vector<winrt::Microsoft::Windows::ToastNotifications::ToastNotification>() };

        for (unsigned i = 0; i < count; ++i)
        {
            ABI::Microsoft::Internal::ToastNotifications::INotificationProperties* properties;
            auto r = notificationProperties->GetAt(i, &properties);

            unsigned int payloadSize;
            wil::unique_cotaskmem_array_ptr<byte> payload;
            properties->get_Payload(&payloadSize, &payload);

            auto wide = ConvertUtf8StringToWideString(payloadSize, payload.get());
            hstring payload2(wide.get());
            winrt::hstring xmlPayload{ L"<toast>intrepidToast</toast>" };

            winrt::Windows::Data::Xml::Dom::XmlDocument xmlDocument{};
            xmlDocument.LoadXml(payload2);

            winrt::Microsoft::Windows::ToastNotifications::ToastNotification notification(xmlDocument);

            // Unique identifier used to replace a notification within a group.
            //String Tag;
            wil::unique_hstring tag;
            properties->get_Tag(&tag);
            notification.Tag(wil::str_raw_ptr(tag));

            // Unique identifier for a toast group in the app
            //String Group;
            wil::unique_hstring group;
            properties->get_Group(&group);
            notification.Group(wil::str_raw_ptr(group));

            // A unique identifier for the Toast generated by the platform.
            //UInt32 ToastId;
            unsigned int notificationId;
            properties->get_NotificationId(&notificationId);
            notification.ToastId(notificationId);

            // The notification Xml Payload
            //Windows.Data.Xml.Dom.XmlDocument Payload{ get; };

            // Gets or sets additional information about the toast progress.
            //ToastProgressData ProgressData;
#if 0
            winrt::com_ptr<ToastABI::IToastProgressData> toastProgressDataActual;
            VERIFY_SUCCEEDED(actual->get_ToastProgressData(toastProgressDataActual.put()));
            if (toastProgressDataExpected)
            {
                VerifyAreEqualsToastProgressData(toastProgressDataExpected, toastProgressDataActual.get());
            }
#endif
            // Gets or sets the time after which a toast notification should not be displayed.
            //Windows.Foundation.DateTime ExpirationTime;
            unsigned long long expiry;
            properties->get_Expiry(&expiry);
            FILETIME expiryFileTime;
            expiryFileTime.dwHighDateTime = expiry >> 32;
            expiryFileTime.dwLowDateTime = expiry;
            //*expiry = static_cast<ULONGLONG>(m_expiry.dwHighDateTime) << 32 | static_cast<ULONGLONG>(m_expiry.dwLowDateTime);
            //winrt::Windows::Foundation::DateTime converted(expiry);
            auto expiryClock = winrt::clock::from_file_time(expiryFileTime);
            notification.ExpirationTime(expiryClock);

            // Indicates whether the toast will remain in the Action Center after a reboot.
            //Boolean ExpiresOnReboot;
            boolean expiresOnReboot;
            properties->get_ExpiresOnReboot(&expiresOnReboot);
            notification.ExpiresOnReboot(expiresOnReboot);

            // Gets or sets the priority for a Toast.
            // Hints on how and at what urgency level a notification should be presented to the user (whether to wake up the screen, etc).
            //ToastPriority Priority;

            // Gets or sets whether a toast's pop-up UI is displayed on the user's screen.
            //Boolean SuppressDisplay;

            result.Append(notification);
        }

        co_return result;
    }
    winrt::Windows::Data::Xml::Dom::XmlDocument ToastNotificationManager::GetXmlTemplateContent(winrt::Microsoft::Windows::ToastNotifications::ToastTemplateType const& /* type */)
    {
        throw hresult_not_implemented();
    }
}
