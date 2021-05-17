#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationActivationInfo.g.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct PushNotificationActivationInfo : PushNotificationActivationInfoT<PushNotificationActivationInfo>
    {
        PushNotificationActivationInfo(Microsoft::Windows::PushNotifications::PushNotificationRegistrationKind const& kind, winrt::guid const& taskClsid);
        winrt::guid TaskClsid();
        Microsoft::Windows::PushNotifications::PushNotificationRegistrationKind Kind();
        winrt::com_array<winrt::Windows::ApplicationModel::Background::IBackgroundCondition> GetConditions();
        void SetConditions(array_view<winrt::Windows::ApplicationModel::Background::IBackgroundCondition const> conditions);

    private:
        const Microsoft::Windows::PushNotifications::PushNotificationRegistrationKind m_kind;
        const winrt::guid m_taskClsid;
        winrt::com_array<winrt::Windows::ApplicationModel::Background::IBackgroundCondition> m_backgroundConditions{};
        wil::srwlock m_lock;
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationActivationInfo : PushNotificationActivationInfoT<PushNotificationActivationInfo, implementation::PushNotificationActivationInfo>
    {
    };
}
