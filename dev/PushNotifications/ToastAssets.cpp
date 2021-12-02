#include "pch.h"
#include "ToastAssets.h"
#include "Microsoft.Windows.ToastNotifications.ToastAssets.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    ToastAssets::ToastAssets(hstring const& displayName, winrt::Windows::Foundation::Uri const& iconPath)
    {
        throw hresult_not_implemented();
    }
    hstring ToastAssets::DisplayName()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Uri ToastAssets::IconPath()
    {
        throw hresult_not_implemented();
    }
}
