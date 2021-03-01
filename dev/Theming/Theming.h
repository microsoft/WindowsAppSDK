// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Theming.g.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct Theming
    {
        Theming() = default;
        static bool IsDarkModeEneabled();
        static bool IsDarkModeActive();
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct Theming : ThemingT<Theming, implementation::Theming>
    {
    };
}
