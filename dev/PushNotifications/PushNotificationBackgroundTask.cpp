#pragma once

#include "pch.h"

#include "PushNotificationBackgroundTask.h"

#include <winrt/base.h>
#include <winrt/windows.networking.pushnotifications.h>
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"

using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Networking::PushNotifications;

wil::unique_handle g_waitHandleForArgs;
winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs g_activatedEventArgs{ nullptr };

void PushNotificationBackgroundTask::Run(IBackgroundTaskInstance taskInstance)
{
    auto lock = g_lock.lock();
    g_activatedEventArgs = winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(taskInstance);
    SetEvent(g_waitHandleForArgs.get());
}
