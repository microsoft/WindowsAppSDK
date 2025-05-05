// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_)
#define __WindowsAppSDK_Microsoft_Windows_Foundation_decimal_

#include <oleauto.h>

#if !defined(_VC_NODEFAULTLIB)
#pragma comment(linker, "/defaultlib:oleaut32.lib")
#endif

inline int compare(const DECIMAL& left, const DECIMAL& right)
{
    static_assert(VARCMP_LT == 0, "VARCMP_LT == 0");
    static_assert(VARCMP_EQ == 1, "VARCMP_EQ == 1");
    static_assert(VARCMP_GT == 2, "VARCMP_GT == 2");
    return ::VarDecCmp(const_cast<DECIMAL*>(&left), const_cast<DECIMAL*>(&right)) - 1;
}

inline bool operator==(const DECIMAL& left, const DECIMAL& right)
{
    return compare(left, right) == 0;
}

inline bool operator!=(const DECIMAL& left, const DECIMAL& right)
{
    return compare(left, right) != 0;
}

inline bool operator< (const DECIMAL& left, const DECIMAL& right)
{
    return compare(left, right) < 0;
}

inline bool operator<=(const DECIMAL& left, const DECIMAL& right)
{
    return compare(left, right) <= 0;
}

inline bool operator> (const DECIMAL& left, const DECIMAL& right)
{
    return compare(left, right) > 0;
}

inline bool operator>=(const DECIMAL& left, const DECIMAL& right)
{
    return compare(left, right) >= 0;
}

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

    decimal(decimal&& value) :
        m_decimal(value.m_decimal)
    {
        value.m_decimal = DECIMAL{};
    }

    constexpr decimal(const DECIMAL& value) :
        m_decimal(value)
    {
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
        // So we intentionally ignore VarDecFromBool() and set decimal(bool) == 0 or 1
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
        THROW_IF_FAILED(::VarDecFromStr(value, LOCALE_INVARIANT, 0, &m_decimal));
    }

    decimal(PCWSTR value, const LCID locale)
    {
        THROW_IF_FAILED(::VarDecFromStr(value, locale, 0, &m_decimal));
    }

    decimal(const std::wstring& value)
    {
        THROW_IF_FAILED(::VarDecFromStr(value.c_str(), LOCALE_INVARIANT, 0, &m_decimal));
    }

    decimal(const std::wstring& value, const LCID locale)
    {
        THROW_IF_FAILED(::VarDecFromStr(value.c_str(), locale, 0, &m_decimal));
    }

#if defined(WINRT_BASE_H)
    decimal(const winrt::hstring& value)
    {
        THROW_IF_FAILED(::VarDecFromStr(value.c_str(), LOCALE_INVARIANT, 0, &m_decimal));
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

    decimal& operator=(decimal&& value)
    {
        if (&value != this)
        {
            m_decimal = value.m_decimal;
            value.m_decimal = DECIMAL{};
        }
        return *this;
    }

    decimal& operator=(const DECIMAL& value)
    {
        if (&value != &m_decimal)
        {
            m_decimal = value;
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
        // So we intentionally ignore VarDecFromBool() and set decimal(bool) == 0 or 1
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
        THROW_IF_FAILED(::VarDecFromStr(value, LOCALE_INVARIANT, 0, &m_decimal));
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

    const DECIMAL& to_decimal() const
    {
        // Treat all values != 0 as true (good)
        return m_decimal;
    }

    bool to_bool() const
    {
        // Treat values != 0 as true
        return (m_decimal.Lo64 != 0) || (m_decimal.Hi32 != 0);
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
        return to_string(LOCALE_INVARIANT);
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
        return to_hstring(LOCALE_INVARIANT);
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
        return compare(value.m_decimal);
    }

    bool operator==(const DECIMAL& value) const
    {
        return compare(value) == 0;
    }

    bool operator!=(const DECIMAL& value) const
    {
        return compare(value) != 0;
    }

    bool operator< (const DECIMAL& value) const
    {
        return compare(value) < 0;
    }

    bool operator<=(const DECIMAL& value) const
    {
        return compare(value) <= 0;
    }

    bool operator> (const DECIMAL& value) const
    {
        return compare(value) > 0;
    }

    bool operator>=(const DECIMAL& value) const
    {
        return compare(value) >= 0;
    }

    int compare(const DECIMAL& value) const
    {
        return ::compare(m_decimal, value);
    }

    /// Return true if this is valid.
    static bool is_valid()
    {
        return is_valid(m_decimal);
    }

    /// Return true if value is valid.
    static constexpr bool is_valid(const DECIMAL& value)
    {
        const BYTE sign_is_negative{ 0x80 };
        return (value.scale <= max_scale()) && ((value & ~sign_is_negative) == 0);
    }

    /// Return the scaling factor of the value (the number of decimal digits).
    /// @return the scaling factor, ranging from 0 to max_scale().
    std::uint32_t scale() const
    {
        return m_decimal.scale;
    }

    /// Return the sign of the value.
    /// @return 0 if this os zero, <0 if this is less than zero or >0 if this is greater than zero.
    std::int32_t sign() const
    {
        return ((m_decimal.Lo64 == 0) && (m_decimal.Hi32 == 0)) ? 0 : (m_decimal.sign != 0 ? -1 : 1);
    }

    /// Return the maximum scaling factor
    static constexpr std::uint32_t max_scale()
    {
        return 28;
    }

    /// Return the maximum value (79,228,162,514,264,337,593,543,950,335).
    static constexpr decimal max_value()
    {
        DECIMAL value{};
        value.Lo64 = 0xFFFFFFFFFFFFFFFFllu;
        value.Hi32 = 0xFFFFFFFFu;
        return decimal{ value };
    }

    /// Return the minimum value (-79,228,162,514,264,337,593,543,950,335).
    static constexpr decimal min_value()
    {
        DECIMAL value{};
        value.Lo64 = 0xFFFFFFFFFFFFFFFFllu;
        value.Hi32 = 0xFFFFFFFFu;
        value.sign = DECIMAL_NEG;
        return decimal{ value };
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
    /// @note this rounds down to -infinity.
    decimal integer() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecInt(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    decimal operator++()
    {
        return operator+=(decimal(1));
    }

    decimal operator++(int)
    {
        const decimal before(m_decimal);
        operator+=(decimal(1));
        return before;
    }

    decimal operator--()
    {
        return operator-=(decimal(1));
    }

    decimal operator--(int)
    {
        const decimal before(m_decimal);
        operator-=(decimal(1));
        return before;
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

    /// Modulo operation using the Truncated method.
    /// @note The % operator in C, C#, Rust and other languages use this method.
    /// @note The result's sign will match the current value's sign.
    /// @see https://en.wikipedia.org/wiki/Modulo
    decimal operator%(const decimal& value) const
    {
        // VarMod() operates on I4 (int32) at best (not even I8 aka int64)
        // So let's do it the grade school way and matching .NET's Decimal...
        //
        //      remainder = left % right
        // aka
        //      aleft = ABS(left)
        //      aright = ABS(right)
        //      q = (aleft / aright)
        //      remainder = aleft - (aright * FIX(aleft / aright) * aright)
        //      remainder = IF left < 0 THEN remainder = -remainder

        const Microsoft::Windows::Foundation::decimal aleft{ abs() };
        const Microsoft::Windows::Foundation::decimal aright{ value.abs() };
        const bool left_is_negative{ m_decimal.sign != 0 };

        const Microsoft::Windows::Foundation::decimal quotient{ aleft.abs() / aright.abs() };
        const Microsoft::Windows::Foundation::decimal fix{ quotient.fix() };
        const Microsoft::Windows::Foundation::decimal product{ fix * aright };
        const Microsoft::Windows::Foundation::decimal remainder{ aleft - product };
        return left_is_negative ? -remainder : remainder;
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
    DECIMAL m_decimal{};
};
}

#endif // !defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_)
