#include "pch.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget1.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget1.g.cpp"

namespace winrt::Microsoft::Test::DynamicDependency::Widgets::implementation
{
    int32_t Widget1::Value()
    {
        return m_value;
    }
    void Widget1::Value(int32_t value)
    {
        m_value = value;
    }
}
