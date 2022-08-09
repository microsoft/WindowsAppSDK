// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Test.DynamicDependency.Widgets.Widget2.g.h"

namespace winrt::Microsoft::Test::DynamicDependency::Widgets::implementation
{
    struct Widget2 : Widget2T<Widget2>
    {
        Widget2() = default;

        static winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 GetStaticWidget1();
        winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 GetWidget1();
    };
}
namespace winrt::Microsoft::Test::DynamicDependency::Widgets::factory_implementation
{
    struct Widget2 : Widget2T<Widget2, implementation::Widget2>
    {
    };
}
