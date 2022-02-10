#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationActivationInfo.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationActivationInfo : AppNotificationActivationInfoT<AppNotificationActivationInfo>
    {
        AppNotificationActivationInfo() = default;

        AppNotificationActivationInfo(winrt::guid const& taskClsid);
        AppNotificationActivationInfo(hstring const& displayName, winrt::Windows::Foundation::Uri const& iconUri);
        winrt::guid TaskClsid();
        hstring DisplayName();
        winrt::Windows::Foundation::Uri IconUri();

    private:
        winrt::guid m_taskClsid{ GUID_NULL };
        hstring m_displayName;
        winrt::Windows::Foundation::Uri m_iconUri{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationActivationInfo : AppNotificationActivationInfoT<AppNotificationActivationInfo, implementation::AppNotificationActivationInfo>
    {
    };
}
