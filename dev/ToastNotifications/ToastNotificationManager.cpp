#include "pch.h"
#include "ToastNotificationManager.h"
#include "Microsoft.Windows.ToastNotifications.ToastNotificationManager.g.cpp"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include "ToastActivationCallback.h"
#include "externs.h"
#include "ToastNotificationUtility.h"
#include <frameworkudk/pushnotifications.h>
#include <frameworkudk/toastnotifications.h>
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

namespace ToastABI = ABI::Microsoft::Internal::ToastNotifications;
namespace CollectionsABI = ABI::Windows::Foundation::Collections;

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
        if (!AppModel::Identity::IsPackagedProcess())
        {
            storedComActivatorString = RegisterComActivatorGuidAndAssets(details);
            // Remove braces around the guid string
            storedComActivatorString = storedComActivatorString.substr(1, storedComActivatorString.size() - 2);
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
            UnRegisterAppIdentifierFromRegistry();

            // TODO: Remove ToastGuid reference from LRP
        }
    }
    winrt::event_token ToastNotificationManager::ToastActivated(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs> const& /* handler */)
    {
        throw hresult_not_implemented();
    }
    void ToastNotificationManager::ToastActivated(winrt::event_token const&/* token */)
    {
        throw hresult_not_implemented();
    }
    void ToastNotificationManager::ShowToast(winrt::Microsoft::Windows::ToastNotifications::ToastNotification const& /* toast */)
    {
        throw hresult_not_implemented();
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
        std::wstring appId { RetrieveAppId() };
        DWORD toastNotificationSetting{ 0 };
        ToastNotifications_QuerySettings(appId.c_str(), &toastNotificationSetting);

        return static_cast<winrt::Microsoft::Windows::ToastNotifications::ToastNotificationSetting>(toastNotificationSetting);
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastNotificationHistory ToastNotificationManager::History()
    {
        std::wstring appId{ RetrieveAppId() };
        winrt::com_ptr <CollectionsABI::IVector<ToastABI::INotificationProperties*>> toastPropertiesCollection;
        ToastNotifications_GetHistory(appId.c_str(), toastPropertiesCollection.put());
        throw hresult_not_implemented();
    }
    winrt::Windows::Data::Xml::Dom::XmlDocument ToastNotificationManager::GetXmlTemplateContent(winrt::Microsoft::Windows::ToastNotifications::ToastTemplateType const& /* type */)
    {
        throw hresult_not_implemented();
    }
}
