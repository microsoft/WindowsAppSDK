// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Microsoft.Windows.AppLifecycle.AppLifecycle.g.h>

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    struct AppLifecycle
    {
        AppLifecycle() = default;

        static Windows::ApplicationModel::Activation::IActivatedEventArgs GetActivatedEventArgs();
    };
}

namespace winrt::Microsoft::Windows::AppLifecycle::factory_implementation
{
    struct AppLifecycle : AppLifecycleT<AppLifecycle, implementation::AppLifecycle>
    {
    };
}
