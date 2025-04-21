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
        // VARIANT_TRUE is weird by today's standards:
        //      typedef short VARIANT_BOOL;
        //      #define VARIANT_TRUE  ((VARIANT_BOOL) 0xffff)
        //      #define VARIANT_FALSE ((VARIANT_BOOL) 0)
        // Thus
        //      VarDecFromBool(VARIANT_TRUE)  == -1
        //      VarDecFromBool(VARIANT_FALSE) == 0
        // But decimal(true) would be expected to be 1 (not -1)
        // So we intentionally ignore VarDecFromBool() and treat decimal(bool) == 0 or 1
        THROW_IF_FAILED(::VarDecFromUI4(value ? 1 : 0, &m_decimal));
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

    decimal(PCWSTR value)
    {
        THROW_IF_FAILED(::VarDecFromStr(value, GetThreadLocale(), 0, &m_decimal));
    }

    decimal(PCWSTR value, const LCID locale)
    {
        THROW_IF_FAILED(::VarDecFromStr(value, locale, 0, &m_decimal));
    }

    decimal(const std::wstring& value)
    {
        THROW_IF_FAILED(::VarDecFromStr(value.c_str(), GetThreadLocale(), 0, &m_decimal));
    }

    decimal(const std::wstring& value, const LCID locale)
    {
        THROW_IF_FAILED(::VarDecFromStr(value.c_str(), locale, 0, &m_decimal));
    }

#if defined(WINRT_BASE_H)
    decimal(const winrt::hstring& value)
    {
        THROW_IF_FAILED(::VarDecFromStr(value.c_str(), GetThreadLocale(), 0, &m_decimal));
    }
#endif // defined(WINRT_BASE_H)

#if defined(WINRT_BASE_H)
    decimal(const winrt::hstring& value, const LCID locale)
    {
        THROW_IF_FAILED(::VarDecFromStr(value.c_str(), locale, 0, &m_decimal));
    }
#endif // defined(WINRT_BASE_H)

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
        // VARIANT_TRUE is weird by today's standards:
        //      typedef short VARIANT_BOOL;
        //      #define VARIANT_TRUE  ((VARIANT_BOOL) 0xffff)
        //      #define VARIANT_FALSE ((VARIANT_BOOL) 0)
        // Thus
        //      VarDecFromBool(VARIANT_TRUE)  == -1
        //      VarDecFromBool(VARIANT_FALSE) == 0
        // But decimal(true) would be expected to be 1 (not -1)
        // So we intentionally ignore VarDecFromBool() and treat decimal(bool) == 0 or 1
        THROW_IF_FAILED(::VarDecFromUI4(value ? 1 : 0, &m_decimal));
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

    decimal& operator=(PCWSTR value)
    {
        THROW_IF_FAILED(::VarDecFromStr(value, GetThreadLocale(), 0, &m_decimal));
        return *this;
    }

    decimal& operator=(const std::wstring& value)
    {
        return operator=(value.c_str());
    }

#if defined(WINRT_BASE_H)
    decimal& operator=(const winrt::hstring& value)
    {
        return operator=(value.c_str());
    }
#endif // defined(WINRT_BASE_H)

    bool to_bool() const
    {
        // Treat all values != 0 as true (good)
        return m_decimal.Hi32 | m_decimal.Mid32 | m_decimal.Lo32;
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

    std::wstring to_string() const
    {
        return to_string(GetThreadLocale());
    }

    std::wstring to_string(const LCID locale) const
    {
        wil::unique_bstr bstr;
        THROW_IF_FAILED(::VarBstrFromDec(&m_decimal, locale, 0, wil::out_param(bstr)));
        return std::wstring{ bstr.get() };
    }

#if defined(WINRT_BASE_H)
    winrt::hstring to_hstring() const
    {
        return to_hstring(GetThreadLocale());
    }
#endif // defined(WINRT_BASE_H)

#if defined(WINRT_BASE_H)
    winrt::hstring to_hstring(const LCID locale) const
    {
        wil::unique_bstr bstr;
        THROW_IF_FAILED(::VarBstrFromDec(&m_decimal, locale, 0, wil::out_param(bstr)));
        return winrt::hstring{ bstr.get() };
    }
#endif // defined(WINRT_BASE_H)

    bool operator==(const decimal& value) const
    {
        return compare(value) == 0;
    }

    bool operator!=(const decimal& value) const
    {
        return compare(value) != 0;
    }

    bool operator< (const decimal& value) const
    {
        return compare(value) < 0;
    }

    bool operator<=(const decimal& value) const
    {
        return compare(value) <= 0;
    }

    bool operator> (const decimal& value) const
    {
        return compare(value) > 0;
    }

    bool operator>=(const decimal& value) const
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

    /// Chop to integer.
    decimal fix() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecFix(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    /// Round down to integer.
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
        // VarMod() operates on I4 (int32) at best (not even I8 aka int64)
        // So let's do it the grade school way...
        //
        //      remainder = left % right
        // aka
        //      q = (left / right)
        //      remainder = left - (right * FIX(left / right) * right)

        static const Microsoft::Windows::Foundation::decimal zero{};
        static const Microsoft::Windows::Foundation::decimal one{ 1 };
        if ((*this == value) || (value == one))
        {
            return zero;
        }

        const Microsoft::Windows::Foundation::decimal& left{ *this };
        const Microsoft::Windows::Foundation::decimal& right{ value };
        const bool left_is_negative{ m_decimal.sign != 0 };

        Microsoft::Windows::Foundation::decimal quotient{ left.abs() / right.abs() };
        Microsoft::Windows::Foundation::decimal fix{ quotient.fix() };
        Microsoft::Windows::Foundation::decimal product{ quotient * fix };
        Microsoft::Windows::Foundation::decimal remainder{ left_is_negative ? left + product :  left - product };
        return remainder;
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

/*
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
*/
