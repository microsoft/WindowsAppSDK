#include "pch.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget2.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget2.g.cpp"

namespace winrt::Microsoft::Test::DynamicDependency::Widgets::implementation
{
    winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 Widget2::GetWidget1()
    {
        throw hresult_not_implemented();
    }
}
