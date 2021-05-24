#pragma once
#include "pch.h"
#include "PushNotificationReceivedEventArgs.h"

extern wil::unique_handle g_waitHandleForArgs;
extern wil::critical_section g_lock;

const winrt::hstring ACTIVATED_EVENT_ARGS_KEY = L"GlobalActivatedEventArgs";
