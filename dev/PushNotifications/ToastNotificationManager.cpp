#include "pch.h"

#include "ToastNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.cpp"
#include <winrt/Windows.Foundation.h>
#include "winrt/Windows.UI.h"
#include <frameworkudk/pushnotifications.h>
#include "NotificationsLongRunningProcess_h.h"
#include "PushNotificationTelemetry.h"
#include <TerminalVelocityFeatures-PushNotifications.h>
#include "externs.h"
#include <stdio.h>

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::Foundation;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    void RegisterValue(wil::unique_hkey const& hKey, PCWSTR const& key, const BYTE* value, DWORD const& valueType, DWORD const& size)
    {
        THROW_IF_FAILED(RegSetValueExW(hKey.get(), key, 0, valueType, value, size));
    }

    void RegisterAssets(std::wstring const& appId, winrt::hstring const& displayName, winrt::Uri const& iconUri, winrt::Color const& color, wil::unique_cotaskmem_string const& clsid)
    {
        wil::unique_hkey hKey;
        std::wstring subKey { L"Software\\Classes\\AppUserModelId\\" + appId };
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
        comRegistrationExeString.append(L"-ToastActivated");
        RegisterValue(hKey, nullptr, reinterpret_cast<const BYTE*>(comRegistrationExeString.c_str()), REG_SZ, (comRegistrationExeString.size() * sizeof(wchar_t)));
    }

    void ToastNotificationManager::RegisterActivator(winrt::hstring const& displayName, winrt::Uri const& iconUri, winrt::Color const& color)
    {
        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));

        GUID guidReference;
        THROW_IF_FAILED(CoCreateGuid(&guidReference));

        wil::unique_cotaskmem_string guidStr;
        THROW_IF_FAILED(StringFromCLSID(guidReference, &guidStr));

        THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(L"D13419AE-3F6E-4872-B84A-F37C728B906D", GUID_NULL));

        RegisterAssets(L"D13419AE-3F6E-4872-B84A-F37C728B906D", displayName, iconUri, color, guidStr);
        RegisterComServer(processName, guidStr);
        return;
    }    
}
