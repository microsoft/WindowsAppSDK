#pragma once

#include "pch.h"

#include "PushNotificationBackgroundTask.h"

#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>

#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"

namespace winrt
{
    using namespace Windows::ApplicationModel::Background;
    using namespace Microsoft::Windows::PushNotifications;
    using namespace Windows::ApplicationModel::Core;
}

wil::unique_handle g_waitHandleForArgs;

void PushNotificationBackgroundTask::Run(winrt::IBackgroundTaskInstance const& taskInstance)
{
    auto appProperties = winrt::CoreApplication::Properties();
    winrt::PushNotificationReceivedEventArgs activatedEventArgs = winrt::PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(taskInstance);
    appProperties.Insert(ACTIVATED_EVENT_ARGS_KEY, activatedEventArgs);

    SetEvent(g_waitHandleForArgs.get());
}
