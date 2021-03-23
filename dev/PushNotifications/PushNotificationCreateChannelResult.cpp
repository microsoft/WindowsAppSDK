#include "pch.h"

#include "PushNotificationCreateChannelResult.h"
#include "PushNotificationCreateChannelResult.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PushNotificationCreateChannelResult::PushNotificationCreateChannelResult(Microsoft::ProjectReunion::PushNotificationChannel const& channel, winrt::hresult const& extendedError, Microsoft::ProjectReunion::PushNotificationChannelStatus const& status)
    {
        m_channel = channel;
        m_extendedError = extendedError;
        m_status = status;
    }
    Microsoft::ProjectReunion::PushNotificationChannel PushNotificationCreateChannelResult::Channel()
    {
        auto lock = m_lock.lock();
        return m_channel;
    }
    winrt::hresult PushNotificationCreateChannelResult::ExtendedError()
    {
        auto lock = m_lock.lock();
        return m_extendedError;
    }
    Microsoft::ProjectReunion::PushNotificationChannelStatus PushNotificationCreateChannelResult::Status()
    {
        auto lock = m_lock.lock();
        return m_status;
    }
}
