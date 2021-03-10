#pragma once

#include "pch.h"

#include <winrt/Windows.ApplicationModel.background.h>

#include "ReunionPushTask.h"

#include <winrt/base.h>
#include <winrt/windows.networking.pushnotifications.h>

#include "PushNotificationActivatedEventArgs.h"

using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Networking::PushNotifications;

extern winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs g_activatedEventArgs;
extern winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs>> g_pushActivatedEvent;
extern wil::unique_handle g_waitHandleForArgs;

void ReunionPushTask::Run(IBackgroundTaskInstance taskInstance)
{
    winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs args{ taskInstance };

    // If we have a PushActivated handler around, the app is already in foreground
    if (g_pushActivatedEvent)
    {
        g_pushActivatedEvent(nullptr, args);
    }
    else // There is no PushActivated handler. It means that we want to pass the args to AppLifecycle2
    {
        g_activatedEventArgs = args;
        SetEvent(g_waitHandleForArgs.get());
    }
}


