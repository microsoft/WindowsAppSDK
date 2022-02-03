#include "pch.h"
#include "ToastActivationInfo.h"
#include "Microsoft.Windows.ToastNotifications.ToastActivationInfo.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo ToastActivationInfo::CreateFromActivationGuid(winrt::guid const& taskClsid)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        THROW_HR_IF(E_INVALIDARG, (taskClsid == winrt::guid(GUID_NULL)));

        return winrt::make<ToastActivationInfo>(taskClsid);
    }

    winrt::Microsoft::Windows::ToastNotifications::ToastActivationInfo ToastActivationInfo::CreateFromToastAssets(winrt::Microsoft::Windows::ToastNotifications::ToastAssets const& assets)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, AppModel::Identity::IsPackagedProcess(), "Not applicable for packaged applications");

        THROW_HR_IF_NULL_MSG(E_POINTER, assets, "Invalid Toast asset parameter");

        THROW_HR_IF_NULL_MSG(E_POINTER, assets.IconPath(), "Invalid icon URI");

        THROW_HR_IF_MSG(E_INVALIDARG, (assets.DisplayName().size() == 0), "Display name string is empty");

        return winrt::make<ToastActivationInfo>(assets);
    }

    winrt::guid ToastActivationInfo::TaskClsid()
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        return m_taskClsid;
    }

    winrt::Microsoft::Windows::ToastNotifications::ToastAssets ToastActivationInfo::Assets()
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, AppModel::Identity::IsPackagedProcess(), "Not applicable for packaged applications");

        return m_assets;
    }
}
