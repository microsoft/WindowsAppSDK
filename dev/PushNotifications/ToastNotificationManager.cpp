#include "pch.h"
#include "ToastNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.cpp"
#include "ToastActivationCallback.h"
#include "externs.h"
#include <iostream>
#include <frameworkudk/pushnotifications.h>
#include "PushNotificationUtility.h"
#include <winrt/Windows.Foundation.h>
#include "winrt/Windows.UI.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Storage.h>

static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::PushNotifications::ToastActivatedEventArgs>> g_toastHandlers;

static int g_toastHandlerCount = 0;

winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::PushNotifications::ToastActivatedEventArgs>>& GetToastHandlers()
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

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    static wil::unique_com_class_object_cookie s_toastcomActivatorRegistration;

    void RegisterAssets(std::wstring const& appId, winrt::hstring const& displayName, winrt::Uri const& iconUri, winrt::Color const& color, wil::unique_cotaskmem_string const& clsid)
    {
        wil::unique_hkey hKey;
        std::wstring subKey{ L"Software\\Classes\\AppUserModelId\\" + appId };
        THROW_IF_FAILED(RegCreateKeyEx(
            HKEY_CURRENT_USER,
            subKey.c_str(),
            0,
            nullptr,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            nullptr,
            &hKey,
            nullptr));

        RegisterValue(hKey, L"DisplayName", reinterpret_cast<const BYTE*>(displayName.c_str()), REG_EXPAND_SZ, displayName.size() * sizeof(wchar_t));
        RegisterValue(hKey, L"IconUri", reinterpret_cast<const BYTE*>(iconUri.AbsoluteUri().c_str()), REG_EXPAND_SZ, iconUri.AbsoluteUri().size() * sizeof(wchar_t));

        WCHAR buffer[24];
        wsprintf(buffer, L"%X%X%X%X", color.A, color.R, color.G, color.B);
        RegisterValue(hKey, L"IconBackgroundColor", reinterpret_cast<const BYTE*>(buffer), REG_SZ, sizeof(buffer));

        std::wstring wideStringClsid{ clsid.get() };
        RegisterValue(hKey, L"CustomActivator", reinterpret_cast<const BYTE*>(wideStringClsid.c_str()), REG_SZ, wideStringClsid.size() * sizeof(wchar_t));
        return;
    }

    void RegisterComServer(wil::unique_cotaskmem_string const& processName, wil::unique_cotaskmem_string const& clsid)
    {
        wil::unique_hkey hKey;
        std::wstring wideStringClsid = { clsid.get() };
        std::wstring subKey{ L"Software\\Classes\\CLSID\\" + wideStringClsid + L"\\LocalServer32" };
        THROW_IF_FAILED(RegCreateKeyEx(
            HKEY_CURRENT_USER,
            subKey.c_str(),
            0,
            nullptr,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            nullptr,
            &hKey,
            nullptr));

        std::wstring comRegistrationExeString{ L"\"" };
        comRegistrationExeString.append(processName.get());
        comRegistrationExeString.append(L"\" ");
        comRegistrationExeString.append(L"----ToastActivated:");
        RegisterValue(hKey, nullptr, reinterpret_cast<const BYTE*>(comRegistrationExeString.c_str()), REG_SZ, (comRegistrationExeString.size() * sizeof(wchar_t)));
    }

    std::wstring RetrieveComActivatorGuid(std::wstring const& appId)
    {
        wil::unique_hkey hKey;
        std::wstring subKey{ L"Software\\Classes\\AppUserModelId\\" + appId };

        THROW_IF_FAILED(RegCreateKeyEx(
            HKEY_CURRENT_USER,
            subKey.c_str(),
            0,
            nullptr,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            nullptr,
            &hKey,
            nullptr));

        WCHAR registeredGuidBuffer[GUID_LENGTH + 4]; // GUID length + '{' + '}' + '\0'
        DWORD bufferLength = sizeof(registeredGuidBuffer);
        HRESULT status = RegGetValueW(
            hKey.get(),
            nullptr,
            L"CustomActivator",
            RRF_RT_REG_SZ,
            nullptr,
            &registeredGuidBuffer,
            &bufferLength);

        if (status == ERROR_FILE_NOT_FOUND)
        {
            return L"";
        }
        else
        {
            THROW_HR_IF(status, FAILED_WIN32(status));
        }
        return registeredGuidBuffer;
    }

    void ToastNotificationManager::RegisterActivator(winrt::hstring const& displayName, winrt::Uri const& iconUri, winrt::Color const& color)
    {
        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));


        std::wstring appId{ RetrieveToastGuid() };
        THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(appId.c_str(), GUID_NULL));

        std::wstring storedComActivatorString { RetrieveComActivatorGuid(appId) };

        GUID comActivatorGuid;
        if (storedComActivatorString.empty())
        {
            THROW_IF_FAILED(CoCreateGuid(&comActivatorGuid));

            wil::unique_cotaskmem_string comActivatorGuidString;
            THROW_IF_FAILED(StringFromCLSID(comActivatorGuid, &comActivatorGuidString));

            RegisterAssets(appId, displayName, iconUri, color, comActivatorGuidString);
            RegisterComServer(processName, comActivatorGuidString);
        }
        else
        {
            storedComActivatorString = storedComActivatorString.substr(1, storedComActivatorString.size() - 2);
            comActivatorGuid = winrt::guid(storedComActivatorString);
        }

        GetWaitHandleForArgs().create();

        THROW_IF_FAILED(::CoRegisterClassObject(
            comActivatorGuid,
            winrt::make<ToastActivationCallback_factory>().get(),
            CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE,
            &s_toastcomActivatorRegistration));

        return;
    }
    
    void ToastNotificationManager::RegisterActivator(winrt::guid const& taskClsid)
    {

        if (AppModel::Identity::IsPackagedProcess())
        {
            THROW_HR_IF_MSG(E_INVALIDARG, s_toastcomActivatorRegistration, "ComActivator already registered.");

            GetWaitHandleForArgs().create();

            THROW_IF_FAILED(::CoRegisterClassObject(
                taskClsid,
                winrt::make<ToastActivationCallback_factory>().get(),
                CLSCTX_LOCAL_SERVER,
                REGCLS_MULTIPLEUSE,
                &s_toastcomActivatorRegistration));
        }
    }

    void ToastNotificationManager::UnRegisterActivator()
    {
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !s_toastcomActivatorRegistration, "ComActivator not registered.");
        s_toastcomActivatorRegistration.reset();
    }

    winrt::event_token ToastNotificationManager::ToastActivated(winrt::Windows::Foundation::EventHandler<Microsoft::Windows::PushNotifications::ToastActivatedEventArgs> handler)
    {
        GetToastHandleCount()++;
        return GetToastHandlers().add(handler);
    }

    void ToastNotificationManager::ToastActivated(winrt::event_token const& token) noexcept
    {
        GetToastHandleCount()--;
        GetToastHandlers().remove(token);
    }
}
