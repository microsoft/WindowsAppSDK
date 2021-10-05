#include "pch.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget2.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget2.g.cpp"

#include "Microsoft.Test.DynamicDependency.Widgets.Widget1.h"

namespace winrt::Microsoft::Test::DynamicDependency::Widgets::implementation
{
    Widget2::Widget2() :
        m_widget1(winrt::make<implementation::Widget1>())
    {
    }

    winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 Widget2::GetWidget1()
    {
        return m_widget1;
    }
}
