#include "pch.h"

#include <winrt/base.h>

#include "InProcActivatorDetails.h"
#include "InProcActivatorDetails.g.cpp"

#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Foundation.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::mutex InProcActivatorDetails::s_mutex;
    std::unique_lock<std::mutex> InProcActivatorDetails::s_lock(s_mutex, std::defer_lock); // Avoid locking during the constructor call

    InProcActivatorDetails::InProcActivatorDetails(hstring const& taskClsid)
    {
        m_taskClsid = taskClsid;
    }

    hstring InProcActivatorDetails::TaskClsid()
    {
        return m_taskClsid;
    }

    // During registration we should call this
    Windows::ApplicationModel::Background::IBackgroundCondition InProcActivatorDetails::Condition()
    {
        s_lock.lock();
        return m_backgroundCondition;
    }

    // May be used by the developer
    void InProcActivatorDetails::Condition(Windows::ApplicationModel::Background::IBackgroundCondition const& value)
    {
        s_lock.lock();
        m_backgroundCondition = value;
    }

    winrt::event_token InProcActivatorDetails::PushActivated(Windows::Foundation::EventHandler<Microsoft::ProjectReunion::PushNotificationActivatedEventArgs> const& handler)
    {
        s_lock.lock();
        return g_pushActivatedEvent.add(handler);
    }

    void InProcActivatorDetails::PushActivated(winrt::event_token const& token) noexcept
    {
        s_lock.lock();
        g_pushActivatedEvent.remove(token);
    }

    Windows::ApplicationModel::Background::IBackgroundTaskRegistration InProcActivatorDetails::Registration()
    {
        s_lock.lock();
        return m_backgroundTaskRegistration;
    }

    void InProcActivatorDetails::Registration(Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& value)
    {
        s_lock.lock();
        m_backgroundTaskRegistration = value;
    }
}
