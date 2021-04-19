#pragma once
#include "pch.h"
#include "PushNotificationReceivedEventArgs.h"

extern wil::unique_handle g_waitHandleForArgs;
extern winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs g_activatedEventArgs;
extern wil::critical_section g_lock;
