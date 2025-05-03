# 1. Decimal

THIS FEATURE IS CURRENTLY EXPERIMENTAL.

This feature provides a common decimal representation and aids for use within and across programming languages.

Some languages have a native decimal data type, e.g. [Decimal struct in C#](https://learn.microsoft.com/dotnet/api/system.decimal)
and [decimal in Python](https://docs.python.org/3/library/decimal.html). These are recommended for
use in their languages. Windows App SDK provides supplemental aids for interoperability with the
common data type.

Other languages have no native decimal data type e.g. C++, Rust and Javascript. Windows App SDK
provides language native support for some languages including interoperability with the common data
type:

* C++ -- `Microsoft::Windows::Foundation::decimal`

Windows App SDK provides a decimal WinRT runtimeclass `Microsoft.Windows.Foundation.Decimal` as a
fallback for languages without a native decimal data type (whether provided by the language or
Windows App SDK). This is fully functional but has performance overhead relative to language native
data types which are commonly stack allocated and offer better language integration. The WinRT type
is recommended when your language has no native type or other comparable solution.

# 2. Common Decimal Representation

The Win32 [DECIMAL](https://learn.microsoft.com/windows/win32/api/wtypes/ns-wtypes-decimal-r1)
structure is the common decimal format, stored as a 96-bit (12-byte) unsigned integer scaled by a
variable power of 10. The power of 10 scaling factor specifies the number of digits to the right of
the decimal point, and ranges from 0 to 28. This is expressed in WinRT as the following structure:

```c# (but really midl3)
    struct DecimalValue
    {
        UInt16 Reserved;
        Byte Scale;         // Allowed values: 0-28
        Byte Sign;          // Allowed values: 0x80 = negative, 0x00 = zero or positive
        UInt32 Hi32;
        UInt64 Lo64;
    }
```

This matches the memory layout and use of the Win32 [DECIMAL](https://learn.microsoft.com/windows/win32/api/wtypes/ns-wtypes-decimal-r1)
structure and the [C# Decimal struct](https://learn.microsoft.com/dotnet/api/system.decimal). This
data structure may be re-expressed in each language using language-specific constructs e.g. WinRT
defines the `DecimalValue` structure as the Win32 `DECIMAL` definition syntax is incompatible with
WinRT IDL.

# 3. WinRT API

Windows App SDK provides a `Decimal` WinRT runtimeclass in addition to the `DecimalValue` structure.

```c# (but really MIDL3)
namespace Microsoft.Windows.Foundation
{
    [contractversion(1)]
    apicontract DecimalContract{};

    /// WinRT representation of the Win32 DECIMAL structure.
    /// @note This is the identical memory layout and encoding of the Win32 DECIMAL structure.
    ///       The latter's definition is valid for COM but not WinRT making this equivalent structure necessary.
    /// @see https://learn.microsoft.com/windows/win32/api/wtypes/ns-wtypes-decimal-r1
    [feature(Feature_Decimal)]
    [contract(DecimalContract, 1)]
    struct DecimalValue
    {
        UInt16 Reserved;
        UInt8 Scale;        // Allowed values: 0-28
        UInt8 Sign;         // Allowed values: 0x80 = negative, 0x00 = zero or positive
        UInt32 Hi32;
        UInt64 Lo64;
    };

    [feature(Feature_Decimal)]
    [contract(DecimalContract, 1)]
    runtimeclass DecimalHelper
    {
        static DecimalValue FromBoolean(Boolean value);
        static DecimalValue FromInt16(Int16 value);
        static DecimalValue FromInt32(Int32 value);
        static DecimalValue FromInt64(Int64 value);
        static DecimalValue FromUInt8(UInt8 value);
        static DecimalValue FromUInt16(UInt16 value);
        static DecimalValue FromUInt32(UInt32 value);
        static DecimalValue FromUInt64(UInt64 value);
        static DecimalValue FromSingle(Single value);
        static DecimalValue FromDouble(Double value);
        static DecimalValue FromString(String value);                          // LCID=LOCALE_INVARIANT
        static DecimalValue FromStringWithSystemDefaultLocale(String value);   // LCID=GetSystemDefaultLCID()
        static DecimalValue FromStringWithUserDefaultLocale(String value);     // LCID=GetUserDefaultLCID()
        static DecimalValue FromStringWithThreadLocale(String value);          // LCID=GetThreadLocale()

        static Boolean ToBoolean(DecimalValue value);
        static Int16 ToInt16(DecimalValue value);
        static Int32 ToInt32(DecimalValue value);
        static Int64 ToInt64(DecimalValue value);
        static UInt8 ToUInt8(DecimalValue value);
        static UInt16 ToUInt16(DecimalValue value);
        static UInt32 ToUInt32(DecimalValue value);
        static UInt64 ToUInt64(DecimalValue value);
        static Single ToSingle(DecimalValue value);
        static Double ToDouble(DecimalValue value);
        static String ToString(DecimalValue value);                         // LCID=LOCALE_INVARIANT
        static String ToStringWithSystemDefaultLocale(DecimalValue value);  // LCID=GetSystemDefaultLCID()
        static String ToStringWithUserDefaultLocale(DecimalValue value);    // LCID=GetUserDefaultLCID()
        static String ToStringWithThreadLocale(DecimalValue value);         // LCID=GetThreadLocale()

        /// Return true if (left == right).
        static Boolean Equals(DecimalValue left, DecimalValue right);

        /// Compare decimal values.
        /// @return 0 if left and right are equal, <0 if left is less than right or >0 if left is greater than right.
        static Int32 Compare(DecimalValue left, DecimalValue right);

        /// Return the scaling factor of the value (the number of decimal digits).
        /// @return the scaling factor, ranging from 0 to max_scale().
        static UInt32 Scale(DecimalValue value);

        /// Return the sign of the value.
        /// @return 0 if value is zero, <0 if value is less than zero or >0 if value is greater than zero.
        static Int32 Sign(DecimalValue value);

        /// Return the maximum scaling factor
        static UInt32 MaxScale();

        /// Return the maximum value (79,228,162,514,264,337,593,543,950,335).
        static DecimalValue MaxValue();

        /// Return the minimum value (-79,228,162,514,264,337,593,543,950,335).
        static DecimalValue MinValue();

        /// Return a decimal whose value is (-value).
        static DecimalValue Negate(DecimalValue value);

        /// Return the absolute value.
        static DecimalValue Abs(DecimalValue value);

        /// Return the value's integer portion (zero to the right of the decimal point).
        static DecimalValue Fix(DecimalValue value);

        /// Return the value rounded down to the nearest integer.
        static DecimalValue Integer(DecimalValue value);

        /// Return the value rounded to the specific number of decimal places.
        static DecimalValue Round(DecimalValue value, Int32 decimalPlaces);

        /// Returns a DecimalValue whose value is (left + right).
        static DecimalValue Add(DecimalValue left, DecimalValue right);

        /// Returns a DecimalValue whose value is (left - right).
        static DecimalValue Subtract(DecimalValue left, DecimalValue right);

        /// Returns a DecimalValue whose value is (left * right).
        static DecimalValue Multiply(DecimalValue left, DecimalValue right);

        /// Returns a DecimalValue whose value is (left / right).
        static DecimalValue Divide(DecimalValue left, DecimalValue right);

        /// Returns a DecimalValue whose value is (left % right).
        static DecimalValue Modulo(DecimalValue left, DecimalValue right);
    }
}
```

# 4. C++ API

Windows App SDK provides a native language decimal data type for C++ as the
`Microsoft::Windows::Foundation::decimal` class in `decimal.h`. This class has the following features:

* Constructor and assignment (operator=) overloads to define a decimal object from various data types
* to_xxx() methods converting a decimal object's value to various data types
* Relational operations: `compare()` `==` `!=` `<` `<=` `>` `>=`
* Unary operations: + - ++ --
* Binary operations: + += - -= * *= / /= % %=
* Properties: `sign()` `scale()`
* Mathematical operations: `abs()` `fix()` `integer()` `round()`
* Constants: `max_scale()` `max_value()` `min_value()`

Errors are expressed via thrown exceptions e.g. `decimal{1} / decimal{0}` will throw a divide-by-zero exception

## 4.1. decimal.h

```c++
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
```

## 4.2. decimalcppwinmrt.h

```c++
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <oleauto.h>

//----------------------------------------------------------------------
// WinRT DecimalValue support

#if defined(WINRT_Microsoft_Windows_Foundation_H) && !defined(__WINDOWSAPPSDK_WINRT_M_W_F_DECIMAL_)
#define __WINDOWSAPPSDK_WINRT_M_W_F_DECIMAL_

//----------------------------------------------------------
// WinRT DecimalValue <-> Win32 DECIMAL conversions

namespace winrt::Microsoft::Windows::Foundation
{
/// Return value as a Win32 DECIMAL structure.
inline DECIMAL to_DECIMAL(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
{
    return std::bit_cast<DECIMAL>(value);
}

/// Return value as a WinRT DecimalValue structure.
inline winrt::Microsoft::Windows::Foundation::DecimalValue to_DecimalValue(DECIMAL const& value)
{
    return std::bit_cast<winrt::Microsoft::Windows::Foundation::DecimalValue>(value);
}
}

//----------------------------------------------------------
// WinRT DecimalValue operators

// C++/WinRT generates bool operator==(DecimalValue const& left, DecimalValue const& right)

// C++/WinRT generates bool operator!=(DecimalValue const& left, DecimalValue const& right)

inline bool operator<(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right)
{
    return winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right) < 0;
}

inline bool operator<=(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right)
{
    return winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right) <= 0;
}

inline bool operator>(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right)
{
    return winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right) > 0;
}

inline bool operator>=(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right)
{
    return winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right) >= 0;
}

#endif // defined(WINRT_Microsoft_Windows_Foundation_H) && !defined(__WINDOWSAPPSDK_WINRT_M_W_F_DECIMAL_)

//----------------------------------------------------------------------
// C++ decimal support

#if defined(WINRT_Microsoft_Windows_Foundation_H) && defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_) && !defined(__WINDOWSAPPSDK_CPP_M_W_F_DECIMAL_)
#define __WINDOWSAPPSDK_CPP_M_W_F_DECIMAL_

//----------------------------------------------------------
// WinRT DecimalValue <-> C++ decimal conversions

namespace winrt::Microsoft::Windows::Foundation
{
/// Return value as a C++ decimal object.
inline ::Microsoft::Windows::Foundation::decimal to_decimal(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
{
    return ::Microsoft::Windows::Foundation::decimal{ to_DECIMAL(value) };
}

/// Return value as a WinRT DecimalValue structure.
inline winrt::Microsoft::Windows::Foundation::DecimalValue to_DecimalValue(::Microsoft::Windows::Foundation::decimal const& value)
{
    return to_DecimalValue(value.to_decimal());
}
}

#endif // defined(WINRT_Microsoft_Windows_Foundation_H) && defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_) && !defined(__WINDOWSAPPSDK_CPP_M_W_F_DECIMAL_)
```

# 6. Open Issues

# 6.1. API Review

Potential changes for API Review consideration:

1. String conversions - How to handle
   1. VarDecFromStr() and VarBStrFromDec() support localization via LCID. WinRT doesn't.
      1. Support LCID for localization?
         1. C++ has to/from string with taking (value, LCID) with default LCID=LOCALE_INVARIANT
         2. WinRT has pre-canned variants:
            1. ToStringWithSystemDefaultLocale();           // LCID=GetSystemDefaultLCID()
            2. ToStringWithUserDefaultLocale();             // LCID=GetUserDefaultLCID()
            3. ToStringWithThreadLocale();                  // LCID=GetThreadLocale()
            4. ToStringWithInvariantLocale();               // LCID=LOCALE_INVARIANT
            5. ToString() == ToStringWithInvariantLocale()
      2. Use alternative ??? for localization?
         1. ??? <-> LCID conversion APIs?
         2. Rewrite VarDecFromStr() and VBstrFromDec() as equivalents using ???
         3. Windows.Globalization.NumberFormatting.DecimalFormatter has Format(Double/Int64/UInt64) but no DECIMAL
2. C++ class
   1. Add floor() - round towards +infinity. https://learn.microsoft.com/en-us/dotnet/api/system.decimal.floor
   2. Add ceil() - round towards -infinity. https://learn.microsoft.com/en-us/dotnet/api/system.decimal.ceiling
      1. Rename integer() to ceil() ?
   3. Add floor-ceil-variant() - round towards zero
3. winrt::Microsoft::Windows::Foundation::DecimalHelper
   1. Add Floor()
   2. Rename Integer() to Ceil()
   3. Add Floor-Ceil-Variant() for rounds towards zero

# 6.2. TODO

Punchlist to reach Stable:

1. C++ class
   1. BUG? decimal zero{}; decimal neg{ -zero }; neg.sign() < 0 because DECIMAL.sign = 0x80. Treat -0 the same as +0 (prevent -0 from being set?)
2. winrt::Microsoft::Windows::Foundation::DecimalHelper
   1. Add experimental checks
3. C# Tests
   1. TAEF for C# ?
   2. Port test\inc\WindowsAppRuntime.Test.Package.h to C#
   3. Port test\inc\WindowsAppRuntime.Test.Bootstrap.h to C#
   4. Register framework package
   5. Bootstrap.Initialize()
   6. Implement remaining tests
