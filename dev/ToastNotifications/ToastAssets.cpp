#include "pch.h"
#include "ToastAssets.h"
#include "Microsoft.Windows.ToastNotifications.ToastAssets.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    hstring ToastAssets::DisplayName()
    {
        return m_displayName;
    }
    winrt::Windows::Foundation::Uri ToastAssets::IconPath()
    {
        return m_iconPath;
    }
}
