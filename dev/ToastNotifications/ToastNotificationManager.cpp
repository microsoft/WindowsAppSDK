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
    using namespace Microsoft::Windows::ToastNotifications;
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
    winrt::Windows::Foundation::IAsyncOperation<winrt::ToastProgressResult> ToastNotificationManager::UpdateToastProgressDataAsync(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData data, hstring tag, hstring group)
    {
        std::wstring appId{ RetrieveAppId() };
        auto hr = ToastNotifications_UpdateNotificationData(appId.c_str(), tag.c_str(), group.c_str(), &data);

        if (hr == S_OK)
        {
            co_return winrt::ToastProgressResult::Succeeded;
        }
        else if (hr == E_NOT_SET)
        {
            co_return winrt::ToastProgressResult::NotificationNotFound;
        }
        else
        {
            co_return winrt::ToastProgressResult::Failed;
        }
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::ToastProgressResult> ToastNotificationManager::UpdateToastProgressDataAsync(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData data, hstring tag)
    {
        std::wstring appId{ RetrieveAppId() };
        auto hr = ToastNotifications_UpdateNotificationData(appId.c_str(), tag.c_str(), nullptr, &data);

        if (hr == S_OK)
        {
            co_return winrt::ToastProgressResult::Succeeded;
        }
        else if (hr == E_NOT_SET)
        {
            co_return winrt::ToastProgressResult::NotificationNotFound;
        }
        else
        {
            co_return winrt::ToastProgressResult::Failed;
        }
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastNotificationSetting ToastNotificationManager::Setting()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastNotificationHistory ToastNotificationManager::History()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Data::Xml::Dom::XmlDocument ToastNotificationManager::GetXmlTemplateContent(winrt::Microsoft::Windows::ToastNotifications::ToastTemplateType const& /* type */)
    {
        throw hresult_not_implemented();
    }
}
