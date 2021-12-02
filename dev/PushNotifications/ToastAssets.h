#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastAssets.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastAssets : ToastAssetsT<ToastAssets>
    {
        ToastAssets() = default;

        ToastAssets(hstring const& displayName, winrt::Windows::Foundation::Uri const& iconPath);
        hstring DisplayName();
        winrt::Windows::Foundation::Uri IconPath();
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastAssets : ToastAssetsT<ToastAssets, implementation::ToastAssets>
    {
    };
}
