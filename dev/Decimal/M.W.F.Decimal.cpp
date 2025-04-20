// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.F.Decimal.h"
#include "Microsoft.Windows.Foundation.Decimal.g.cpp"

#include "DecimalTelemetry.h"

namespace winrt::Microsoft::Windows::Foundation::implementation
{
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Abs()
    {
        throw hresult_not_implemented();
    }
    hstring Decimal::ToString()
    {
        throw hresult_not_implemented();
    }
}
