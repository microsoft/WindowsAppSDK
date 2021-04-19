// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Microsoft.ApplicationModel.Activation.AppLifecycle.g.h>

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    struct AppLifecycle
    {
        AppLifecycle() = default;

        static Windows::ApplicationModel::Activation::IActivatedEventArgs GetActivatedEventArgs();
    };
}

namespace winrt::Microsoft::ApplicationModel::Activation::factory_implementation
{
    struct AppLifecycle : AppLifecycleT<AppLifecycle, implementation::AppLifecycle>
    {
    };
}
