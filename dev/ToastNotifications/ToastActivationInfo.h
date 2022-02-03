#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastActivationInfo.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastActivationInfo : ToastActivationInfoT<ToastActivationInfo>
    {
        ToastActivationInfo() = default;

        ToastActivationInfo(winrt::guid const& taskClsid) : m_taskClsid(taskClsid) {};
        ToastActivationInfo(winrt::Microsoft::Windows::ToastNotifications::ToastAssets const& assets) : m_assets(assets) {};
        static winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo CreateFromActivationGuid(winrt::guid const& taskClsid);
        static winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo CreateFromToastAssets(winrt::Microsoft::Windows::ToastNotifications::ToastAssets const& assets);
        winrt::guid TaskClsid();
        winrt::Microsoft::Windows::ToastNotifications::ToastAssets Assets();

    private:
        const winrt::guid m_taskClsid{ GUID_NULL };
        const winrt::Microsoft::Windows::ToastNotifications::ToastAssets m_assets{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::ToastNotifications::factory_implementation
{
    struct ToastActivationInfo : ToastActivationInfoT<ToastActivationInfo, implementation::ToastActivationInfo>
    {
    };
}
