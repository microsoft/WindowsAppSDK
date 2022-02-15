#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationActivationInfo.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationActivationInfo : AppNotificationActivationInfoT<AppNotificationActivationInfo>
    {
        AppNotificationActivationInfo() = default;
        AppNotificationActivationInfo(hstring const& displayName, winrt::Windows::Foundation::Uri const& iconUri);
        hstring DisplayName();
        winrt::Windows::Foundation::Uri IconUri();

    private:
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
