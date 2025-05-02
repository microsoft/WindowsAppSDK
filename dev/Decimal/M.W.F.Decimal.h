// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Foundation.Decimal.g.h"

#include <decimal.h>
#include <decimalcppwinrt.h>

namespace winrt::Microsoft::Windows::Foundation::implementation
{
    struct Decimal : DecimalT<Decimal>
    {
        Decimal() = default;

        Decimal(::Microsoft::Windows::Foundation::decimal const& value) :
            m_decimal(value)
        {
        }

        Decimal(winrt::Microsoft::Windows::Foundation::DecimalValue const& value) :
            m_decimal(to_DECIMAL(value))
        {
        }

        Decimal(DECIMAL const& value) :
            m_decimal(value)
        {
        }

        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromBoolean(bool value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromInt16(int16_t value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromInt32(int32_t value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromInt64(int64_t value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromUInt8(uint8_t value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromUInt16(uint16_t value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromUInt32(uint32_t value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromUInt64(uint64_t value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromSingle(float value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromDouble(double value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromString(hstring const& value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromStringWithSystemDefaultLocale(hstring const& value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromStringWithUserDefaultLocale(hstring const& value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromStringWithThreadLocale(hstring const& value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromStringWithInvariantLocale(hstring const& value);
        static winrt::Microsoft::Windows::Foundation::Decimal Create(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromDecimal(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        static winrt::Microsoft::Windows::Foundation::Decimal CreateFromDecimalValue(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        static uint32_t MaxScale();
        static winrt::Microsoft::Windows::Foundation::Decimal MaxValue();
        static winrt::Microsoft::Windows::Foundation::Decimal MinValue();
        void SetFromBoolean(bool value);
        void SetFromInt16(int16_t value);
        void SetFromInt32(int32_t value);
        void SetFromInt64(int64_t value);
        void SetFromUInt8(uint8_t value);
        void SetFromUInt16(uint16_t value);
        void SetFromUInt32(uint32_t value);
        void SetFromUInt64(uint64_t value);
        void SetFromSingle(float value);
        void SetFromDouble(double value);
        void SetFromString(hstring const& value);
        void SetFromStringWithSystemDefaultLocale(hstring const& value);
        void SetFromStringWithUserDefaultLocale(hstring const& value);
        void SetFromStringWithThreadLocale(hstring const& value);
        void SetFromStringWithInvariantLocale(hstring const& value);
        void Set(winrt::Windows::Foundation::IInspectable const& value);
        void SetFromDecimal(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        void SetFromDecimalValue(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);
        bool ToBoolean();
        int16_t ToInt16();
        int32_t ToInt32();
        int64_t ToInt64();
        uint8_t ToUInt8();
        uint16_t ToUInt16();
        uint32_t ToUInt32();
        uint64_t ToUInt64();
        float ToSingle();
        double ToDouble();
        hstring ToStringWithSystemDefaultLocale();
        hstring ToStringWithUserDefaultLocale();
        hstring ToStringWithThreadLocale();
        hstring ToStringWithInvariantLocale();
        winrt::Windows::Foundation::IInspectable ToObject();
        winrt::Microsoft::Windows::Foundation::Decimal ToDecimal();
        winrt::Microsoft::Windows::Foundation::DecimalValue ToDecimalValue();
        bool Equals(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        int32_t Compare(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        uint32_t Scale();
        int32_t Sign();
        winrt::Microsoft::Windows::Foundation::Decimal Negate();
        winrt::Microsoft::Windows::Foundation::Decimal Abs();
        winrt::Microsoft::Windows::Foundation::Decimal Fix();
        winrt::Microsoft::Windows::Foundation::Decimal Integer();
        winrt::Microsoft::Windows::Foundation::Decimal Round(int32_t decimalPlaces);
        winrt::Microsoft::Windows::Foundation::Decimal Add(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        winrt::Microsoft::Windows::Foundation::Decimal Sub(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        winrt::Microsoft::Windows::Foundation::Decimal Mul(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        winrt::Microsoft::Windows::Foundation::Decimal Div(winrt::Microsoft::Windows::Foundation::Decimal const& value);
        winrt::Microsoft::Windows::Foundation::Decimal Mod(winrt::Microsoft::Windows::Foundation::Decimal const& value);
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
