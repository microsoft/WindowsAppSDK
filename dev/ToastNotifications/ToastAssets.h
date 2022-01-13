#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastAssets.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastAssets : ToastAssetsT<ToastAssets>
    {
        ToastAssets() = default;

        ToastAssets(winrt::hstring const& displayName, winrt::Windows::Foundation::Uri const& iconPath) : m_displayName(displayName), m_iconPath(iconPath) {};
        hstring DisplayName();
        winrt::Windows::Foundation::Uri IconPath();

    private:
        const hstring m_displayName;
        const winrt::Windows::Foundation::Uri m_iconPath;
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastAssets : ToastAssetsT<ToastAssets, implementation::ToastAssets>
    {
    };
}
