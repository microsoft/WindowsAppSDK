#pragma once

#include "pch.h"

#include "PushBackgroundTaskInstance.h"
#include <winrt/base.h>

using namespace winrt::Windows::Networking::PushNotifications;

winrt::guid PushBackgroundTaskInstance::InstanceId()
{
    return winrt::guid();
}

UINT32 PushBackgroundTaskInstance::SuspendedCount()
{
    return 0;
}

UINT32 PushBackgroundTaskInstance::Progress()
{
    return 0;
}

UINT32 PushBackgroundTaskInstance::Progress(UINT32  /* progress */)
{
    return 0;
}

winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration PushBackgroundTaskInstance::Task()
{
    return nullptr;
}

winrt::event_token PushBackgroundTaskInstance::Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& /* handler */)
{
    return winrt::event_token{};
}

void PushBackgroundTaskInstance::Canceled(winrt::event_token const&  /* token */) noexcept
{
    return;
}

winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral PushBackgroundTaskInstance::GetDeferral()
{
    return nullptr;
}

winrt::Windows::Foundation::IInspectable PushBackgroundTaskInstance::TriggerDetails()
{
    return winrt::box_value(m_payload);
}
