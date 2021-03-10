#pragma once

#include "InProcActivatorDetails.g.h"
#include <mutex>

winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs>> g_pushActivatedEvent {};

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct InProcActivatorDetails : InProcActivatorDetailsT<InProcActivatorDetails>
    {
        InProcActivatorDetails() = default;

        InProcActivatorDetails(hstring const& taskClsid);
        hstring TaskClsid();
        Windows::ApplicationModel::Background::IBackgroundCondition Condition();
        void Condition(Windows::ApplicationModel::Background::IBackgroundCondition const& value);
        winrt::event_token PushActivated(Windows::Foundation::EventHandler<Microsoft::ProjectReunion::PushNotificationActivatedEventArgs> const& handler);
        void PushActivated(winrt::event_token const& token) noexcept;
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration Registration();
        void Registration(Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& value);

        private:
            hstring m_taskClsid;
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration m_backgroundTaskRegistration;
            Windows::ApplicationModel::Background::IBackgroundCondition m_backgroundCondition;

            static std::mutex s_mutex;
            static std::unique_lock<std::mutex> s_lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct InProcActivatorDetails : InProcActivatorDetailsT<InProcActivatorDetails, implementation::InProcActivatorDetails>
    {
    };
}
