#pragma once
#include "PushNotificationActivationInfo.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationActivationInfo : PushNotificationActivationInfoT<PushNotificationActivationInfo>
    {
        PushNotificationActivationInfo() = default;

        PushNotificationActivationInfo(Microsoft::ProjectReunion::PushNotificationRegistrationKind const& kind, winrt::guid const& taskClsid);
        winrt::guid TaskClsid();
        Microsoft::ProjectReunion::PushNotificationRegistrationKind Kind();
        com_array<Windows::ApplicationModel::Background::IBackgroundCondition> GetConditions();
        void SetConditions(array_view<Windows::ApplicationModel::Background::IBackgroundCondition const> conditions);

    private:
        Microsoft::ProjectReunion::PushNotificationRegistrationKind m_kind;
        winrt::guid m_taskClsid;
        winrt::com_array<Windows::ApplicationModel::Background::IBackgroundCondition> m_backgroundConditions{};
        wil::critical_section m_lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationActivationInfo : PushNotificationActivationInfoT<PushNotificationActivationInfo, implementation::PushNotificationActivationInfo>
    {
    };
}
