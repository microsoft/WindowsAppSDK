#pragma once

#include "pch.h"

#include "PushNotificationBackgroundTask.h"

#include <winrt/base.h>
#include <winrt/windows.networking.pushnotifications.h>

#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"
#include <iostream>
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Networking::PushNotifications;

wil::unique_handle g_waitHandleForArgs;
winrt::Microsoft::ProjectReunion::PushNotificationReceivedEventArgs g_activatedEventArgs{ nullptr };
int g_sample;

void PushNotificationBackgroundTask::Run(IBackgroundTaskInstance taskInstance)
{
    std::cout << "PushNotificationBackgroundTask::Run -> Start" << std::endl;
    std::cout << g_sample << std::endl;
    g_activatedEventArgs = winrt::Microsoft::ProjectReunion::PushNotificationReceivedEventArgs::CreateFromBackgroundTaskInstance(taskInstance);
    SetEvent(g_waitHandleForArgs.get());
    std::cout << "PushNotificationBackgroundTask::Run -> End" << std::endl;
}
