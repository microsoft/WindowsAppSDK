#pragma once

#include "pch.h"

#include "PushNotificationBackgroundTask.h"

#include <winrt/base.h>
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"

namespace winrt
{
    using namespace Windows::ApplicationModel::Background;
    using namespace Microsoft::Windows::PushNotifications;
}

wil::unique_handle g_waitHandleForArgs;
winrt::PushNotificationReceivedEventArgs g_activatedEventArgs{ nullptr };

void PushNotificationBackgroundTask::Run(winrt::IBackgroundTaskInstance taskInstance)
{
    SetEvent(g_waitHandleForArgs.get());
    auto lock = g_lock.lock();
    g_activatedEventArgs = winrt::PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(taskInstance);
}
