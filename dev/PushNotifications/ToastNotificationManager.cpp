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

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::Foundation;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    static std::wstring GetRegistrySubKey(std::wstring const& appId)
    {
        return L"Software\\Classes\\AppUserModelId\\" + appId;
    }

    void RegisterAsset(wil::unique_hkey const& hKey, std::wstring const& key, const BYTE* value)
    {
        THROW_IF_FAILED(RegSetValueExW(hKey.get(), key.c_str(), 0, REG_SZ, value, 0));
    }

    void RegisterAssets(std::wstring const& appId, winrt::hstring const& displayName, winrt::Uri const& iconUri, winrt::Color const& color)
    {
        wil::unique_hkey hKey;
        std::wstring subKey { GetRegistrySubKey(appId) };
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
            
        RegisterAsset(hKey, L"DisplayName", reinterpret_cast<const BYTE*>(displayName.c_str()));
        RegisterAsset(hKey, L"IconUri", nullptr);
        RegisterAsset(hKey, L"IconBackgroundColor", nullptr);
        RegisterAsset(hKey, L"CustomActivator", nullptr);
        return;
    }

    void ToastNotificationManager::RegisterActivator(winrt::hstring const& displayName, winrt::Uri const& iconUri, winrt::Color const& color)
    {
        auto notificationPlatform{ wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));

        wil::unique_cotaskmem_string unpackagedAppUserModelId;
        THROW_IF_FAILED(notificationPlatform->RegisterFullTrustApplication(processName.get(), GUID_NULL, &unpackagedAppUserModelId));

        RegisterAssets(unpackagedAppUserModelId.get(), displayName, iconUri, color);
        return;
    }    
}
