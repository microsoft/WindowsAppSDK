// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Foundation.Decimal.g.h"

#include <decimal.h>

namespace winrt::Microsoft::Windows::Foundation::implementation
{
    struct Decimal : DecimalT<Decimal>
    {
        Decimal() = default;

        winrt::Microsoft::Windows::Foundation::Decimal Abs();
        hstring ToString();

    private:
        ::Microsoft::Windows::Foundation::decimal m_decimal;
    };
}
namespace winrt::Microsoft::Windows::Foundation::factory_implementation
{
    struct Decimal : DecimalT<Decimal, implementation::Decimal>
    {
    };
}
