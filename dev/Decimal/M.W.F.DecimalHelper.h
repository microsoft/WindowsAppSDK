// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Foundation.DecimalHelper.g.h"

#include <decimal.h>

namespace winrt::Microsoft::Windows::Foundation::implementation
{
    struct DecimalHelper
    {
        DecimalHelper() = default;

        static winrt::Microsoft::Windows::Foundation::DecimalValue FromBoolean(bool value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromInt16(int16_t value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromInt32(int32_t value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromInt64(int64_t value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromUInt8(uint8_t value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromUInt16(uint16_t value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromUInt32(uint32_t value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromUInt64(uint64_t value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromSingle(float value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromDouble(double value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromString(hstring const& source);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromStringInvariant(hstring const& source);
        static winrt::Microsoft::Windows::Foundation::DecimalValue FromString(hstring const& source, hstring const& localeName);
        static bool TryFromString(hstring const& source, winrt::Microsoft::Windows::Foundation::DecimalValue& value);
        static bool TryFromStringInvariant(hstring const& source, winrt::Microsoft::Windows::Foundation::DecimalValue& value);
        static bool TryFromString(hstring const& source, hstring const& localeName, winrt::Microsoft::Windows::Foundation::DecimalValue& value);
        static bool ToBoolean(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static int16_t ToInt16(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static int32_t ToInt32(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static int64_t ToInt64(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static uint8_t ToUInt8(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static uint16_t ToUInt16(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static uint32_t ToUInt32(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static uint64_t ToUInt64(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static float ToSingle(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static double ToDouble(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static hstring ToString(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static hstring ToStringInvariant(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static hstring ToString(winrt::Microsoft::Windows::Foundation::DecimalValue const& value, const winrt::hstring& localeName);
        static bool Equals(winrt::Microsoft::Windows::Foundation::DecimalValue const& left, winrt::Microsoft::Windows::Foundation::DecimalValue const& right);
        static int32_t Compare(winrt::Microsoft::Windows::Foundation::DecimalValue const& left, winrt::Microsoft::Windows::Foundation::DecimalValue const& right);
        static bool IsValid(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static bool IsInteger(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static uint8_t Scale(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static int32_t Sign(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static uint8_t MaxScale();
        static winrt::Microsoft::Windows::Foundation::DecimalValue MaxValue();
        static winrt::Microsoft::Windows::Foundation::DecimalValue MinValue();
        static winrt::Microsoft::Windows::Foundation::DecimalValue Negate(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Abs(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Truncate(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Floor(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Ceiling(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Round(winrt::Microsoft::Windows::Foundation::DecimalValue const& value, int32_t decimalPlaces);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Clamp(winrt::Microsoft::Windows::Foundation::DecimalValue const& value, winrt::Microsoft::Windows::Foundation::DecimalValue const& min, winrt::Microsoft::Windows::Foundation::DecimalValue const& max);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Add(winrt::Microsoft::Windows::Foundation::DecimalValue const& left, winrt::Microsoft::Windows::Foundation::DecimalValue const& right);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Subtract(winrt::Microsoft::Windows::Foundation::DecimalValue const& left, winrt::Microsoft::Windows::Foundation::DecimalValue const& right);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Multiply(winrt::Microsoft::Windows::Foundation::DecimalValue const& left, winrt::Microsoft::Windows::Foundation::DecimalValue const& right);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Divide(winrt::Microsoft::Windows::Foundation::DecimalValue const& left, winrt::Microsoft::Windows::Foundation::DecimalValue const& right);
        static winrt::Microsoft::Windows::Foundation::DecimalValue Modulo(winrt::Microsoft::Windows::Foundation::DecimalValue const& left, winrt::Microsoft::Windows::Foundation::DecimalValue const& right);
    };
}
namespace winrt::Microsoft::Windows::Foundation::factory_implementation
{
    struct DecimalHelper : DecimalHelperT<DecimalHelper, implementation::DecimalHelper>
    {
    };
}
