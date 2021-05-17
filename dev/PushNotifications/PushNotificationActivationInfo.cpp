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
    PushNotificationActivationInfo::PushNotificationActivationInfo(winrt::PushNotificationRegistrationKind const& kind, winrt::guid const& taskClsid) : m_kind(kind), m_taskClsid(taskClsid) {}

    winrt::guid PushNotificationActivationInfo::TaskClsid()
    {
        return m_taskClsid;
    }

    winrt::PushNotificationRegistrationKind PushNotificationActivationInfo::Kind()
    {
        return m_kind;
    }

    winrt::com_array<winrt::IBackgroundCondition> PushNotificationActivationInfo::GetConditions()
    {
        auto lock = m_lock.lock_shared();
        return { m_backgroundConditions.begin(), m_backgroundConditions.end() };
    }

    void PushNotificationActivationInfo::SetConditions(array_view<winrt::IBackgroundCondition const> conditions)
    {
        // Need to destroy old conditions outside of lock.
        auto replacement = winrt::com_array(conditions.begin(), conditions.end());
        auto lock = m_lock.lock_exclusive();
        swap(m_backgroundConditions, replacement);
    }
}
