// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "PushNotificationBackgroundTask.h"

#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>

#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"
#include "PushNotificationUtility.h"

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

namespace winrt
{
    using namespace Windows::ApplicationModel::Background;
    using namespace Microsoft::Windows::PushNotifications;
    using namespace Windows::ApplicationModel::Core;
}

void PushNotificationBackgroundTask::Run(winrt::IBackgroundTaskInstance const& taskInstance)
{
    auto appProperties = winrt::CoreApplication::Properties();
    // This function can be triggered by either OS background infrastructure
    // or by the PushNotificationsLongRunningProcess.
    if (PushNotificationHelpers::IsPackagedAppScenario())
    {
        winrt::PushNotificationReceivedEventArgs activatedEventArgs{ winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(taskInstance) };
        appProperties.Insert(ACTIVATED_EVENT_ARGS_KEY, activatedEventArgs);
    }
    else
    {
        // Need to mock a RawNotification object instead of winrt boxing: https://github.com/microsoft/WindowsAppSDK/issues/2075
        winrt::hstring payload{ winrt::unbox_value<winrt::hstring>(taskInstance.TriggerDetails()) };
        winrt::PushNotificationReceivedEventArgs activatedEventArgs{ winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payload.c_str()) };
        appProperties.Insert(LRP_ACTIVATED_EVENT_ARGS_KEY, activatedEventArgs);
    }

    SetEvent(GetWaitHandleForArgs().get());
}
