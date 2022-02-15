#include "pch.h"
#include "AppNotificationActivationInfo.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationActivationInfo.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    AppNotificationActivationInfo::AppNotificationActivationInfo(hstring const& displayName, winrt::Windows::Foundation::Uri const& iconUri)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, AppModel::Identity::IsPackagedProcess(), "Not applicable for packaged applications");
        THROW_HR_IF_MSG(E_INVALIDARG, (displayName.size() == 0), "Display name string is empty");
        m_displayName = displayName;
        m_iconUri = iconUri;

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
