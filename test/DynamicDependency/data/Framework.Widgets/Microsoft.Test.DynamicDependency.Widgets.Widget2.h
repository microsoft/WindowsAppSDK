#pragma once
#include "Microsoft.Test.DynamicDependency.Widgets.Widget2.g.h"

namespace winrt::Microsoft::Test::DynamicDependency::Widgets::implementation
{
    struct Widget2 : Widget2T<Widget2>
    {
        Widget2();

        winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 GetWidget1();

    private:
        winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 m_widget1;
    };
}
namespace winrt::Microsoft::Test::DynamicDependency::Widgets::factory_implementation
{
    struct Widget2 : Widget2T<Widget2, implementation::Widget2>
    {
    };
}
