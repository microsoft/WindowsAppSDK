// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget1.h"
#include "Microsoft.Test.DynamicDependency.Widgets.Widget1.g.cpp"

namespace winrt::Microsoft::Test::DynamicDependency::Widgets::implementation
{
    winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 Widget1::GetStatic()
    {
        static winrt::Microsoft::Test::DynamicDependency::Widgets::Widget1 m_widget;
        return m_widget;
    }
    int32_t Widget1::Value()
    {
        return m_value;
    }
    void Widget1::Value(int32_t value)
    {
        m_value = value;
    }
}
