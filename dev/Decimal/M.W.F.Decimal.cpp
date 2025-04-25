// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.F.Decimal.h"
#include "Microsoft.Windows.Foundation.Decimal.g.cpp"

#include "DecimalTelemetry.h"

namespace winrt::Microsoft::Windows::Foundation::implementation
{
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromBoolean(bool value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromInt16(int16_t value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromInt32(int32_t value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromInt64(int64_t value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromUInt8(uint8_t value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromUInt16(uint16_t value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromUInt32(uint32_t value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromUInt64(uint64_t value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromSingle(float value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromDouble(double value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromString(hstring const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromStringWithSystemDefaultLocale(hstring const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value, LOCALE_SYSTEM_DEFAULT));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromStringWithUserDefaultLocale(hstring const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value, LOCALE_USER_DEFAULT));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromStringWithThreadLocale(hstring const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value, GetThreadLocale()));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromStringWithInvariantLocale(hstring const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(::Microsoft::Windows::Foundation::decimal(value, LOCALE_INVARIANT));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Create(winrt::Windows::Foundation::IInspectable const& value)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::CreateFromDecimalValue(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(to_decimal(value));
    }
    void Decimal::SetFromBoolean(bool value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromInt16(int16_t value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromInt32(int32_t value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromInt64(int64_t value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromUInt8(uint8_t value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromUInt16(uint16_t value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromUInt32(uint32_t value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromUInt64(uint64_t value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromSingle(float value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromDouble(double value)
    {
        m_decimal = value;
    }
    void Decimal::SetFromString(hstring const& value)
    {
        ::Microsoft::Windows::Foundation::decimal decimal{ value };
        m_decimal = decimal;
    }
    void Decimal::SetFromStringWithSystemDefaultLocale(hstring const& value)
    {
        ::Microsoft::Windows::Foundation::decimal decimal(value, LOCALE_SYSTEM_DEFAULT);
        m_decimal = decimal;
    }
    void Decimal::SetFromStringWithUserDefaultLocale(hstring const& value)
    {
        ::Microsoft::Windows::Foundation::decimal decimal(value, LOCALE_USER_DEFAULT);
        m_decimal = decimal;
    }
    void Decimal::SetFromStringWithThreadLocale(hstring const& value)
    {
        ::Microsoft::Windows::Foundation::decimal decimal(value, GetThreadLocale());
        m_decimal = decimal;
    }
    void Decimal::SetFromStringWithInvariantLocale(hstring const& value)
    {
        ::Microsoft::Windows::Foundation::decimal decimal(value, LOCALE_INVARIANT);
        m_decimal = decimal;
    }
    void Decimal::Set(winrt::Windows::Foundation::IInspectable const& value)
    {
        throw hresult_not_implemented();
    }
    void Decimal::SetFromDecimalValue(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
    {
        const auto& decimalValue{ *reinterpret_cast<const DECIMAL*>(&value) };
        m_decimal = decimalValue;
    }
    bool Decimal::ToBoolean()
    {
        return m_decimal.to_bool();
    }
    int16_t Decimal::ToInt16()
    {
        return m_decimal.to_int16();
    }
    int32_t Decimal::ToInt32()
    {
        return m_decimal.to_int32();
    }
    int64_t Decimal::ToInt64()
    {
        return m_decimal.to_int64();
    }
    uint8_t Decimal::ToUInt8()
    {
        return m_decimal.to_uint8();
    }
    uint16_t Decimal::ToUInt16()
    {
        return m_decimal.to_uint16();
    }
    uint32_t Decimal::ToUInt32()
    {
        return m_decimal.to_uint32();
    }
    uint64_t Decimal::ToUInt64()
    {
        return m_decimal.to_uint64();
    }
    float Decimal::ToSingle()
    {
        return m_decimal.to_float();
    }
    double Decimal::ToDouble()
    {
        return m_decimal.to_double();
    }
    hstring Decimal::ToStringWithSystemDefaultLocale()
    {
        return m_decimal.to_hstring(LOCALE_SYSTEM_DEFAULT);
    }
    hstring Decimal::ToStringWithUserDefaultLocale()
    {
        return m_decimal.to_hstring(LOCALE_USER_DEFAULT);
    }
    hstring Decimal::ToStringWithThreadLocale()
    {
        return m_decimal.to_hstring(GetThreadLocale());
    }
    hstring Decimal::ToStringWithInvariantLocale()
    {
        return m_decimal.to_hstring(LOCALE_INVARIANT);
    }
    winrt::Windows::Foundation::IInspectable Decimal::ToObject()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Foundation::DecimalValue Decimal::ToDecimalValue()
    {
        const auto& decimal{ m_decimal.to_decimal() };
        return *reinterpret_cast<const winrt::Microsoft::Windows::Foundation::DecimalValue*>(&decimal);
    }
    int32_t Decimal::Compare(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return m_decimal.compare(to_DECIMAL(value.ToDecimalValue()));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Negate()
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(-m_decimal);
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Abs()
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal.abs());
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Fix()
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal.fix());
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Integer()
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal.integer());
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Round(int32_t decimalPlaces)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal.round(decimalPlaces));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Add(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal + to_decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::AddAssign(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        m_decimal += to_decimal(value);
        return *this;
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Sub(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal - to_decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::SubAssign(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        m_decimal -= to_decimal(value);
        return *this;
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Mul(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal * to_decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::MulAssign(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        m_decimal *= to_decimal(value);
        return *this;
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Div(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal / to_decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::DivAssign(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        m_decimal /= to_decimal(value);
        return *this;
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::Mod(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal % to_decimal(value));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::ModAssign(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        m_decimal %= to_decimal(value);
        return *this;
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::ModVariant(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal.mod_variant(to_decimal(value)));
    }
    winrt::Microsoft::Windows::Foundation::Decimal Decimal::ModTruncated(winrt::Microsoft::Windows::Foundation::Decimal const& value)
    {
        return winrt::make<winrt::Microsoft::Windows::Foundation::implementation::Decimal>(m_decimal.mod_truncated(to_decimal(value)));
    }
    hstring Decimal::ToString()
    {
        return m_decimal.to_hstring();
    }
}
