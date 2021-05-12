#include "pch.h"
#include "PushNotificationActivationInfo.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationActivationInfo.g.cpp"

#include <Windows.ApplicationModel.background.h>

namespace winrt
{
    using namespace Microsoft::Windows::PushNotifications;
    using namespace Windows::ApplicationModel::Background;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationActivationInfo::PushNotificationActivationInfo(winrt::PushNotificationRegistrationKind const& kind, winrt::guid const& taskClsid)
    {
        m_kind = kind;
        m_taskClsid = taskClsid;
    }
    winrt::guid PushNotificationActivationInfo::TaskClsid()
    {
        auto lock = m_lock.lock_shared();
        return m_taskClsid;
    }

    winrt::PushNotificationRegistrationKind PushNotificationActivationInfo::Kind()
    {
        auto lock = m_lock.lock_shared();
        return m_kind;
    }
    winrt::com_array<winrt::IBackgroundCondition> PushNotificationActivationInfo::GetConditions()
    {
        auto lock = m_lock.lock_shared();
        return winrt::com_array<winrt::IBackgroundCondition>(m_backgroundConditions.begin(), m_backgroundConditions.end());
    }
    void PushNotificationActivationInfo::SetConditions(array_view<winrt::IBackgroundCondition const> conditions)
    {
        auto lock = m_lock.lock_exclusive();
        m_backgroundConditions = winrt::com_array<winrt::IBackgroundCondition>(conditions.begin(), conditions.end());
    }
}
