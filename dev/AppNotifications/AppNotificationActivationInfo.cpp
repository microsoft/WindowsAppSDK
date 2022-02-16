#include "pch.h"
#include "AppNotificationActivationInfo.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationActivationInfo.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    AppNotificationActivationInfo::AppNotificationActivationInfo(winrt::guid const& taskClsid)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");
        THROW_HR_IF(E_INVALIDARG, (taskClsid == winrt::guid(GUID_NULL)));
        m_taskClsid = taskClsid;
    }

    AppNotificationActivationInfo::AppNotificationActivationInfo(hstring const& displayName, winrt::Windows::Foundation::Uri const& iconUri)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, AppModel::Identity::IsPackagedProcess(), "Not applicable for packaged applications");
        THROW_HR_IF_MSG(E_INVALIDARG, (displayName.size() == 0), "Display name string is empty");
        m_displayName = displayName;
        m_iconUri = iconUri;

    }

    winrt::guid AppNotificationActivationInfo::TaskClsid()
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        return m_taskClsid;
    }

    hstring AppNotificationActivationInfo::DisplayName()
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, AppModel::Identity::IsPackagedProcess(), "Not applicable for packaged applications");
        return m_displayName;
    }

    winrt::Windows::Foundation::Uri AppNotificationActivationInfo::IconUri()
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, AppModel::Identity::IsPackagedProcess(), "Not applicable for packaged applications");
        return m_iconUri;
    }
}
