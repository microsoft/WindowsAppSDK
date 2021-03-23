#include "pch.h"
#include "PushNotificationActivationInfo.h"
#include "PushNotificationActivationInfo.g.cpp"

#include <Windows.ApplicationModel.background.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushNotificationActivationInfo::PushNotificationActivationInfo(Microsoft::ProjectReunion::PushNotificationRegistrationKind const& kind, winrt::guid const& taskClsid)
    {
        m_kind = kind;
        m_taskClsid = taskClsid;
    }
    winrt::guid PushNotificationActivationInfo::TaskClsid()
    {
        auto lock = m_lock.lock();
        return m_taskClsid;
    }
    Microsoft::ProjectReunion::PushNotificationRegistrationKind PushNotificationActivationInfo::Kind()
    {
        auto lock = m_lock.lock();
        return m_kind;
    }
    com_array<Windows::ApplicationModel::Background::IBackgroundCondition> PushNotificationActivationInfo::GetConditions()
    {
        auto lock = m_lock.lock();
        return winrt::com_array<Windows::ApplicationModel::Background::IBackgroundCondition>(m_backgroundConditions.begin(), m_backgroundConditions.end());
    }
    void PushNotificationActivationInfo::SetConditions(array_view<Windows::ApplicationModel::Background::IBackgroundCondition const> conditions)
    {
        auto lock = m_lock.lock();
        m_backgroundConditions = winrt::com_array<Windows::ApplicationModel::Background::IBackgroundCondition>(conditions.begin(), conditions.end());
    }
}
