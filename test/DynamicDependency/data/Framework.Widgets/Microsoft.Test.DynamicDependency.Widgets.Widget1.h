// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Test.DynamicDependency.Widgets.Widget1.g.h"

namespace winrt::Microsoft::Test::DynamicDependency::Widgets::implementation
{
    struct Widget1 : Widget1T<Widget1>
    {
        Widget1() = default;

        static winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 GetStatic();
        int32_t Value();
        void Value(int32_t value);

    private:
        int32_t m_value{};
    };
}
namespace winrt::Microsoft::Test::DynamicDependency::Widgets::factory_implementation
{
    struct Widget1 : Widget1T<Widget1, implementation::Widget1>
    {
    };
}
