#include "pch.h"
#include "ToastActivationInfo.h"
#include "Microsoft.Windows.ToastNotifications.ToastActivationInfo.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo ToastActivationInfo::CreateFromActivationGuid(winrt::guid const& taskClsid)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo ToastActivationInfo::CreateFromToastAssets(winrt::Microsoft::Windows::ToastNotifications::ToastAssets const& assets)
    {
        throw hresult_not_implemented();
    }
    winrt::guid ToastActivationInfo::TaskClsid()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ToastNotifications::ToastAssets ToastActivationInfo::Assets()
    {
        throw hresult_not_implemented();
    }
}
