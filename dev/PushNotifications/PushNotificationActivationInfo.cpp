#include "pch.h"
#include "PushNotificationActivationInfo.h"
#include "Microsoft.Windows.PushNotifications.PushNotificationActivationInfo.g.cpp"

#include <Windows.ApplicationModel.background.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    PushNotificationActivationInfo::PushNotificationActivationInfo(Microsoft::Windows::PushNotifications::PushNotificationRegistrationKind const& kind, winrt::guid const& taskClsid)
    {
        m_kind = kind;
        m_taskClsid = taskClsid;
    }
    winrt::guid PushNotificationActivationInfo::TaskClsid()
    {
        auto lock = m_lock.lock_shared();
        return m_taskClsid;
    }
    Microsoft::Windows::PushNotifications::PushNotificationRegistrationKind PushNotificationActivationInfo::Kind()
    {
        auto lock = m_lock.lock_shared();
        return m_kind;
    }
    winrt::com_array<winrt::Windows::ApplicationModel::Background::IBackgroundCondition> PushNotificationActivationInfo::GetConditions()
    {
        auto lock = m_lock.lock_shared();
        return winrt::com_array<winrt::Windows::ApplicationModel::Background::IBackgroundCondition>(m_backgroundConditions.begin(), m_backgroundConditions.end());
    }
    void PushNotificationActivationInfo::SetConditions(array_view<winrt::Windows::ApplicationModel::Background::IBackgroundCondition const> conditions)
    {
        auto lock = m_lock.lock_exclusive();
        m_backgroundConditions = winrt::com_array<winrt::Windows::ApplicationModel::Background::IBackgroundCondition>(conditions.begin(), conditions.end());
    }
}
