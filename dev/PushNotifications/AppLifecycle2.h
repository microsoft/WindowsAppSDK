// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "AppLifecycle2.g.h"

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
