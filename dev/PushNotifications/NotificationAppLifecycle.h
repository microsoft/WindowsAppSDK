#pragma once

#include <NotificationAppLifecycle.g.h>

wil::unique_handle g_waitHandleForArgs = nullptr;
winrt::Microsoft::ProjectReunion::PushNotificationReceivedEventArgs g_activatedEventArgs{ nullptr };

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct NotificationAppLifecycle
    {
        NotificationAppLifecycle() = default;

        static Microsoft::ProjectReunion::NotificationActivationArguments GetRawNotificationEventArgs();
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct NotificationAppLifecycle : NotificationAppLifecycleT<NotificationAppLifecycle, implementation::NotificationAppLifecycle>
    {
    };
}
