// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <oleauto.h>

#if !defined(_VC_NODEFAULTLIB)
#pragma comment(linker, "/defaultlib:oleaut32.lib")
#endif

namespace Microsoft::Windows::Foundation
{
class decimal
{
public:
    decimal() = default;
    ~decimal() = default;

    decimal(const decimal& value) :
        m_decimal(value.m_decimal)
    {
    }

    decimal(const decimal&& value) :
        m_decimal(value.m_decimal)
    {
        m_decimal = DECIMAL{};
    }

    decimal(bool value)
    {
        THROW_IF_FAILED(::VarDecFromBool(value ? VARIANT_TRUE : VARIANT_FALSE, &m_decimal));
    }

    decimal(char value)
    {
        THROW_IF_FAILED(::VarDecFromI1(value, &m_decimal));
    }

    decimal(std::int16_t value)
    {
        THROW_IF_FAILED(::VarDecFromI2(value, &m_decimal));
    }

    decimal(std::int32_t value)
    {
        THROW_IF_FAILED(::VarDecFromI4(value, &m_decimal));
    }

    decimal(std::int64_t value)
    {
        THROW_IF_FAILED(::VarDecFromI8(value, &m_decimal));
    }

    decimal(std::uint8_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI1(value, &m_decimal));
    }

    decimal(std::uint16_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI2(value, &m_decimal));
    }

    decimal(std::uint32_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI4(value, &m_decimal));
    }

    decimal(std::uint64_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI8(value, &m_decimal));
    }

    decimal(float value)
    {
        THROW_IF_FAILED(::VarDecFromR4(value, &m_decimal));
    }

    decimal(double value)
    {
        THROW_IF_FAILED(::VarDecFromR8(value, &m_decimal));
    }

    decimal(long value)
    {
        THROW_IF_FAILED(::VarDecFromI4(value, &m_decimal));
    }

    decimal(unsigned long value)
    {
        THROW_IF_FAILED(::VarDecFromUI4(value, &m_decimal));
    }

#if defined(TODO_STRING)
    template<typename string_type>
    decimal(const string_type& value)
    {
        auto str{ wil::str_raw_ptr(value) };
        THROW_IF_FAILED(::VarDecFromStr(str, GetThreadLocale(), 0, &m_decimal));
    }
#endif // defined(TODO_STRING)

#if defined(TODO_STRING)
    template<typename string_type>
    decimal(const string_type& value, const LCID locale)
    {
        auto str{ wil::str_raw_ptr(value) };
        THROW_IF_FAILED(::VarDecFromStr(str, locale, 0, &m_decimal));
    }
#endif // defined(TODO_STRING)

    decimal& operator=(const decimal& value)
    {
        if (&value != this)
        {
            m_decimal = value.m_decimal;
        }
        return *this;
    }

    decimal& operator=(const decimal&& value)
    {
        if (&value != this)
        {
            m_decimal = value.m_decimal;
            m_decimal = DECIMAL{};
        }
        return *this;
    }

    decimal& operator=(bool value)
    {
        THROW_IF_FAILED(::VarDecFromBool(value ? VARIANT_TRUE : VARIANT_FALSE, &m_decimal));
        return *this;
    }

    decimal& operator=(char value)
    {
        THROW_IF_FAILED(::VarDecFromI1(value, &m_decimal));
        return *this;
    }

    decimal& operator=(std::int16_t value)
    {
        THROW_IF_FAILED(::VarDecFromI2(value, &m_decimal));
        return *this;
    }

    decimal& operator=(std::int32_t value)
    {
        THROW_IF_FAILED(::VarDecFromI4(value, &m_decimal));
        return *this;
    }

    decimal& operator=(std::int64_t value)
    {
        THROW_IF_FAILED(::VarDecFromI8(value, &m_decimal));
        return *this;
    }

    decimal& operator=(std::uint8_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI1(value, &m_decimal));
        return *this;
    }

    decimal& operator=(std::uint16_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI2(value, &m_decimal));
        return *this;
    }

    decimal& operator=(std::uint32_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI4(value, &m_decimal));
        return *this;
    }

    decimal& operator=(std::uint64_t value)
    {
        THROW_IF_FAILED(::VarDecFromUI8(value, &m_decimal));
        return *this;
    }

    decimal& operator=(float value)
    {
        THROW_IF_FAILED(::VarDecFromR4(value, &m_decimal));
        return *this;
    }

    decimal& operator=(double value)
    {
        THROW_IF_FAILED(::VarDecFromR8(value, &m_decimal));
        return *this;
    }

    decimal& operator=(long value)
    {
        THROW_IF_FAILED(::VarDecFromI4(value, &m_decimal));
        return *this;
    }

    decimal& operator=(unsigned long value)
    {
        THROW_IF_FAILED(::VarDecFromUI4(value, &m_decimal));
        return *this;
    }

#if defined(TODO_STRING)
    template<typename string_type>
    decimal& operator=(const string_type& value)
    {
        auto str{ wil::str_raw_ptr(value) };
        THROW_IF_FAILED(::VarDecFromStr(str, GetThreadLocale(), 0, &m_decimal));
    }
#endif // defined(TODO_STRING)

    bool to_bool() const
    {
        VARIANT_BOOL value{};
        THROW_IF_FAILED(::VarBoolFromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    char to_char() const
    {
        char value{};
        THROW_IF_FAILED(::VarI1FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    std::int16_t to_int16() const
    {
        std::int16_t value{};
        THROW_IF_FAILED(::VarI2FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    std::int32_t to_int32() const
    {
        return static_cast<std::int32_t>(to_long());
    }

    std::int64_t to_int64() const
    {
        std::int64_t value{};
        THROW_IF_FAILED(::VarI8FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    std::uint8_t to_uint8() const
    {
        std::uint8_t value{};
        THROW_IF_FAILED(::VarUI1FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    std::uint16_t to_uint16() const
    {
        std::uint16_t value{};
        THROW_IF_FAILED(::VarUI2FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    std::uint32_t to_uint32() const
    {
        return static_cast<std::uint32_t>(to_ulong());
    }

    std::uint64_t to_uint64() const
    {
        std::uint64_t value{};
        THROW_IF_FAILED(::VarUI8FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    float to_float() const
    {
        float value{};
        THROW_IF_FAILED(::VarR4FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    double to_double() const
    {
        double value{};
        THROW_IF_FAILED(::VarR8FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

    long to_long() const
    {
        long value{};
        THROW_IF_FAILED(::VarI4FromDec(&m_decimal, &value));
        return value;
    }

    unsigned long to_ulong() const
    {
        unsigned long value{};
        THROW_IF_FAILED(::VarUI4FromDec(const_cast<DECIMAL*>(&m_decimal), &value));
        return value;
    }

#if defined(TODO_STRING)
    template<typename string_type>
    string_type to_string() const
    {
        return to_string<string_type>(GetThreadLocale());
    }
#endif // defined(TODO_STRING)

#if defined(TODO_STRING)
    template<typename string_type>
    string_type to_string(const LCID locale) const
    {
        wil::unique_bstr bstr;
        THROW_IF_FAILED(::VarBstrFromDec(&m_decimal, locale, 0, wil::out_param(bstr)));
        return wil::make_unique_string<string_type>(bstr.get());
    }
#endif // defined(TODO_STRING)

    bool operator==(const decimal& value) const
    {
        return compare(value) == 0;
    }

    bool operator==(const double value) const
    {
        return compare(value) == 0;
    }

    bool operator!=(const decimal& value) const
    {
        return compare(value) != 0;
    }

    bool operator!=(const double value) const
    {
        return compare(value) != 0;
    }

    bool operator< (const decimal& value) const
    {
        return compare(value) < 0;
    }

    bool operator< (const double value) const
    {
        return compare(value) < 0;
    }

    bool operator<=(const decimal& value) const
    {
        return compare(value) <= 0;
    }

    bool operator<=(const double value) const
    {
        return compare(value) <= 0;
    }

    bool operator> (const decimal& value) const
    {
        return compare(value) > 0;
    }

    bool operator> (const double value) const
    {
        return compare(value) > 0;
    }

    bool operator>=(const decimal& value) const
    {
        return compare(value) >= 0;
    }

    bool operator>=(const double value) const
    {
        return compare(value) >= 0;
    }

    int compare(const decimal& value) const
    {
        static_assert(VARCMP_LT == 0, "VARCMP_LT == 0");
        static_assert(VARCMP_EQ == 1, "VARCMP_EQ == 1");
        static_assert(VARCMP_GT == 2, "VARCMP_GT == 2");
        return ::VarDecCmp(const_cast<DECIMAL*>(&m_decimal), const_cast<DECIMAL*>(&value.m_decimal)) - 1;
    }

    int compare(const double value) const
    {
        static_assert(VARCMP_LT == 0, "VARCMP_LT == 0");
        static_assert(VARCMP_EQ == 1, "VARCMP_EQ == 1");
        static_assert(VARCMP_GT == 2, "VARCMP_GT == 2");
        return ::VarDecCmpR8(const_cast<DECIMAL*>(&m_decimal), value) - 1;
    }

    decimal operator+() const
    {
        return *this;
    }

    decimal operator-() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecNeg(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    decimal abs() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecAbs(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    decimal fix() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecFix(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    decimal integer() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecInt(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    decimal operator+(const decimal& value) const
    {
        decimal result{};
        THROW_IF_FAILED(::VarDecAdd(const_cast<DECIMAL*>(&m_decimal), const_cast<DECIMAL*>(&value.m_decimal), &result.m_decimal));
        return result;
    }

    decimal& operator+=(const decimal& value)
    {
        *this = operator+(value);
        return *this;
    }

    decimal operator-(const decimal& value) const
    {
        decimal result{};
        THROW_IF_FAILED(::VarDecSub(const_cast<DECIMAL*>(&m_decimal), const_cast<DECIMAL*>(&value.m_decimal), &result.m_decimal));
        return result;
    }

    decimal& operator-=(const decimal& value)
    {
        *this = operator-(value);
        return *this;
    }

    decimal operator*(const decimal& value) const
    {
        decimal result{};
        THROW_IF_FAILED(::VarDecMul(const_cast<DECIMAL*>(&m_decimal), const_cast<DECIMAL*>(&value.m_decimal), &result.m_decimal));
        return result;
    }

    decimal& operator*=(const decimal& value)
    {
        *this = operator*(value);
        return *this;
    }

    decimal operator/(const decimal& value) const
    {
        decimal result{};
        THROW_IF_FAILED(::VarDecDiv(const_cast<DECIMAL*>(&m_decimal), const_cast<DECIMAL*>(&value.m_decimal), &result.m_decimal));
        return result;
    }

    decimal& operator/=(const decimal& value)
    {
        *this = operator/(value);
        return *this;
    }

    decimal operator%(const decimal& value) const
    {
        VARIANT left{};
        left.vt = VT_DECIMAL;
        left.decVal = m_decimal;

        VARIANT right{};
        right.vt = VT_DECIMAL;
        right.decVal = value.m_decimal;

        VARIANT result{};
        THROW_IF_FAILED(::VarMod(&left, &right, &result));
        return decimal(result.decVal);
    }

    decimal& operator%=(const decimal& value)
    {
        *this = operator%(value);
        return *this;
    }

    decimal round(const std::int32_t decimalPlaces) const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecRound(const_cast<DECIMAL*>(&m_decimal), decimalPlaces, &value.m_decimal));
        return value;
    }
private:
    decimal(const DECIMAL& value) :
        m_decimal(value)
    {
    }

private:
    DECIMAL m_decimal{};
};
}

inline Microsoft::Windows::Foundation::decimal operator+(const Microsoft::Windows::Foundation::decimal& left, const Microsoft::Windows::Foundation::decimal& right)
{
    return left.operator+(right);
}

inline Microsoft::Windows::Foundation::decimal operator-(const Microsoft::Windows::Foundation::decimal& left, const Microsoft::Windows::Foundation::decimal& right)
{
    return left.operator+(right);
}

inline Microsoft::Windows::Foundation::decimal operator*(const Microsoft::Windows::Foundation::decimal& left, const Microsoft::Windows::Foundation::decimal& right)
{
    return left.operator+(right);
}

inline Microsoft::Windows::Foundation::decimal operator/(const Microsoft::Windows::Foundation::decimal& left, const Microsoft::Windows::Foundation::decimal& right)
{
    return left.operator+(right);
}

inline Microsoft::Windows::Foundation::decimal operator%(const Microsoft::Windows::Foundation::decimal& left, const Microsoft::Windows::Foundation::decimal& right)
{
    return left.operator+(right);
}
