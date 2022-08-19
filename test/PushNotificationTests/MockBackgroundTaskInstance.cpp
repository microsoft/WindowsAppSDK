// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "MockBackgroundTaskInstance.h"
#include "MockRawNotification.h"
#include <winrt/base.h>

using namespace winrt::Windows::Networking::PushNotifications;

winrt::guid MockBackgroundTaskInstance::InstanceId()
{
    return winrt::guid();
}

UINT32 MockBackgroundTaskInstance::SuspendedCount()
{
    return 0;
}

UINT32 MockBackgroundTaskInstance::Progress()
{
    return 0;
}

UINT32 MockBackgroundTaskInstance::Progress(UINT32 progress)
{
    return 0;
}

winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration MockBackgroundTaskInstance::Task()
{
    return nullptr;
}

winrt::event_token MockBackgroundTaskInstance::Canceled(winrt::Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler)
{
    return winrt::event_token{};
}

void MockBackgroundTaskInstance::Canceled(winrt::event_token const& token) noexcept
{
    return;
}

winrt::Windows::ApplicationModel::Background::BackgroundTaskDeferral MockBackgroundTaskInstance::GetDeferral()
{
    return nullptr;
}

winrt::Windows::Foundation::IInspectable MockBackgroundTaskInstance::TriggerDetails()
{
    auto rawNotification = winrt::make<MockRawNotification>();
    return rawNotification;
}
