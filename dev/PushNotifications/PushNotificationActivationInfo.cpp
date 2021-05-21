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
    PushNotificationActivationInfo::PushNotificationActivationInfo(winrt::PushNotificationRegistrationOption const& option, winrt::guid const& taskClsid) : m_option(option), m_taskClsid(taskClsid) {}

    winrt::guid PushNotificationActivationInfo::TaskClsid()
    {
        return m_taskClsid;
    }

    winrt::PushNotificationRegistrationOption PushNotificationActivationInfo::Option()
    {
        return m_option;
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
