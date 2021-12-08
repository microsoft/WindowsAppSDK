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

static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs>> g_toastHandlers;

static int g_toastHandlerCount = 0;

winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs>>& GetToastHandlers()
{
    return g_toastHandlers;
}

int& GetToastHandleCount()
{
    return g_toastHandlerCount;
}

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::Foundation;
    using namespace Windows::ApplicationModel::Core;
}

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    static wil::unique_com_class_object_cookie s_toastcomActivatorRegistration;

    winrt::Microsoft::Windows::ToastNotifications::ToastNotificationManager ToastNotificationManager::Default()
    {
        throw hresult_not_implemented();
    }

    void ToastNotificationManager::RegisterActivator(winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo const&  details)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, s_toastcomActivatorRegistration, "ComActivator already registered.");

        GUID comActivatorGuid = GUID_NULL;
        if (!AppModel::Identity::IsPackagedProcess())
        {
            wil::unique_cotaskmem_string processName;
            THROW_IF_FAILED(GetCurrentProcessPath(processName));

            std::wstring appIdentifier{ RetrieveToastGuid() };
            THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(appIdentifier.c_str(), GUID_NULL));

            std::wstring storedComActivatorString{ RetrieveComActivatorGuid(appIdentifier) };

            if (storedComActivatorString.empty())
            {
                THROW_IF_FAILED(CoCreateGuid(&comActivatorGuid));

                // StringFromCLSID returns GUID String with braces.
                wil::unique_cotaskmem_string comActivatorGuidString;
                THROW_IF_FAILED(StringFromCLSID(comActivatorGuid, &comActivatorGuidString));

                RegisterAssets(appIdentifier, details.Assets(), comActivatorGuidString);
                RegisterComServer(processName, comActivatorGuidString);
            }
            else
            {
                // Remove braces around the guid string
                storedComActivatorString = storedComActivatorString.substr(1, storedComActivatorString.size() - 2);
                comActivatorGuid = winrt::guid(storedComActivatorString);
            }
        }

        THROW_IF_FAILED(::CoRegisterClassObject(
            AppModel::Identity::IsPackagedProcess()?details.TaskClsid(): reinterpret_cast<winrt::guid&>(comActivatorGuid),
            winrt::make<ToastActivationCallback_factory>().get(),
            CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE,
            &s_toastcomActivatorRegistration));

        GetWaitHandleForArgs().create();
    }

    void ToastNotificationManager::UnregisterActivator()
    {
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !s_toastcomActivatorRegistration, "ComActivator not registered.");

        s_toastcomActivatorRegistration.reset();

        if (!AppModel::Identity::IsPackagedProcess())
        {
            std::wstring appIdentifier{ RetrieveToastGuid() };
            std::wstring storedComActivatorString{ RetrieveComActivatorGuid(appIdentifier) };

            UnRegisterComServer(storedComActivatorString);
            UnRegisterAppIdentifierFromRegistry(appIdentifier);

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
