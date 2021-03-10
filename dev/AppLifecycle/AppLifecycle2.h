#pragma once
#include <AppLifecycle2.g.h>

wil::unique_handle g_waitHandleForArgs = nullptr;
winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs g_activatedEventArgs{ nullptr };

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct AppLifecycle2
    {
        AppLifecycle2() = default;

        static Microsoft::ProjectReunion::ActivatedEventArgsExtension GetActivatedEventArgs();
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct AppLifecycle2 : AppLifecycle2T<AppLifecycle2, implementation::AppLifecycle2>
    {
    };
}
