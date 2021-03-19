// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <AppLifecycle.g.h>

wil::unique_handle g_waitHandleForArgs = nullptr;
winrt::Microsoft::ProjectReunion::PushNotificationReceivedEventArgs g_activatedEventArgs{ nullptr };

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct AppLifecycle
    {
        AppLifecycle() = default;

        static Windows::ApplicationModel::Activation::IActivatedEventArgs GetActivatedEventArgs();

        static Microsoft::ProjectReunion::ActivationArguments GetActivatedEventArgs2();
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct AppLifecycle : AppLifecycleT<AppLifecycle, implementation::AppLifecycle>
    {
    };
}
