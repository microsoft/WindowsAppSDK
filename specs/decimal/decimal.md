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

# 3. Examples

The examples are a program displaying the results of the the mathematical formula:

```
x = (((a - b) + (c % d)) * e).round(5) / f;
y = x++.round(3).clamp(f, g);
z = --y.floor() * ++x.ceil() * -y.truncate();
```

Given the values

```
a = 1
b = 0.5
c = -6.66
d = 1.23
e = 4567.089
f = -4
g = 1967
h = 1001.0
```

the output is

```
x == 12.4177225
y == 11.418
z == -1540
```

and the process exit code is -1540.

# 3.1. C#

NOTE: This example uses [C#'s Decimal support](https://learn.microsoft.com/dotnet/api/system.decimal)
providing the canonical reference for examples in other languages.

```c++
Using System;
Using System.IO;

class Program
{
    static void Main()
    {
        var a = new Decimal(1);
        var b = new Decimal(0.5);
        var c = Decimal.Parse("-6.66");
        var d = Decimal.Parse("1.23");
        var e = Decimal.Parse("4567.089");
        var f = new Decimal((long)-4);
        var g = new Decimal((uint)1967);
        var h = new Decimal(1001.0);

        var x = Decimal.Round(((a - b) + (c % d)) * e, 5) / f;
        var y = Math.Clamp(Decimal.Round(x++, 3), f, g);
        var yfloor = Decimal.Floor(y);
        var xceil = Decimal.Ceiling(x);
        var z = --yfloor * ++xceil * -Decimal.Truncate(y);

        Console.WriteLine($"x = {x}");
        Console.WriteLine($"y = {y}");
        Console.WriteLine($"z = {z}");

        Environment.Exit((int)z);
    }
}
```

# 3.2. C++

This program illustrates the reference example using Windows App SDK's C++ decimal class.

```c++
#include <windows.h>
#include <stdio.h>
#include <decimal.h>

int main()
{
    const Microsoft::Windows::Foundation::decimal a{ 1 };
    const Microsoft::Windows::Foundation::decimal b{ 0.5 };
    const Microsoft::Windows::Foundation::decimal c{ L"-6.66" };
    const Microsoft::Windows::Foundation::decimal d{ L"1.23" };
    const Microsoft::Windows::Foundation::decimal e{ L"4567.089" };
    const Microsoft::Windows::Foundation::decimal f{ -4ll };
    const Microsoft::Windows::Foundation::decimal g{ 1967u };
    const Microsoft::Windows::Foundation::decimal h{ 1001.0f };

    auto x = (((a - b) + (c % d)) * e).round(5) / f;
    auto y = x++.round(3).clamp(f, g);
    auto z = --y.floor() * ++x.ceil() * -y.truncate();

    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"x = %ls", x.to_string().c_str()));
    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"y = %ls", y.to_string().c_str()));
    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"z = %ls", z.to_string().c_str()));

    printf(L"x = %ls\n", x.to_string().c_str());
    printf(L"y = %ls\n", y.to_string().c_str());
    printf(L"z = %ls\n", z.to_string().c_str());
    return z.to_int32();
}
```

# 3.3. WinRT

This program illustrates the reference example using Windows App SDK's WinRT `DecimalValue` struct and `DecimalHelper` runtimeclass.

```c++
#include <windows.h>
#include <stdio.h>
#include <winrt/Microsoft.Windows.Foundation.h>

int main()
{
    using DH = winrt::Microsoft::Windows::Foundation::DecimalHelper;
    const auto a{ DH::FromInt32(1) };
    const auto b{ DH::FromDouble(0.5) };
    const auto c{ DH::FromString(L"-6.66") };
    const auto d{ DH::FromString(L"1.23") };
    const auto e{ DH::FromString(L"4567.089") };
    const auto f{ DH::FromInt64(-4ll) };
    const auto g{ DH::FromUInt16(1967u) };
    const auto h{ DH::FromSingle(1001.0f) };

    // WinRT equivalent to C++ formula
    //
    //   x = (((a - b) + (c % d)) * e).round(5) / f
    //   y = x++.round(3).clamp(f, g)
    //   z = --y.floor() * ++x.ceil() * -y.truncate()

    auto x = DH::Divide(DH::Round(DH::Multiply(DH::Add(DH::Subtract(a, b), (DH::Modulo(c, d))), e), 5), f);
    auto one = DH::FromInt32(1);
    auto y = DH::Clamp(DH::Round(x, 3), f, g);
    x = DH::Add(x, one);
    auto z = DH::Multiply(DH::Multiply(DH::Subtract(DH::Floor(y), one), DH::Add(DH::Ceiling(x), one)), DH::Negate(DH::Truncate(y)));

    printf(L"x = %ls\n", DH::ToString(x).c_str());
    printf(L"y = %ls\n", DH::ToString(y).c_str());
    printf(L"z = %ls\n", DH::ToString(z).c_str());
    return DH::ToInt32(z);
}
```

# 4. WinRT API

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

        /// Return true if the value is valid.
        static Boolean IsValid(DecimalValue value);

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

        /// Return the integral digits; any fractional digits are discarded.
        static DecimalValue Truncate(DecimalValue value);

        /// Return the integral digits rounded down to -infinity; any fractional digits are discarded.
        static DecimalValue Floor(DecimalValue value);

        /// Return the integral digits rounded up to +infinity; any fractional digits are discarded.
        static DecimalValue Ceiling(DecimalValue value);

        /// Return the value rounded to the specific number of decimal places.
        static DecimalValue Round(DecimalValue value, Int32 decimalPlaces);

        /// Return value clamped to the inclusive range of min and max.
        /// @return value if min <= value <= max, or min if value < min, or max if max < value.
        static DecimalValue Clamp(DecimalValue value, DecimalValue min, DecimalValue max);

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

# 5. C++ API

Windows App SDK provides a native language decimal data type for C++ as the
`Microsoft::Windows::Foundation::decimal` class in `decimal.h`. This class has the following features:

* Constructor and assignment (operator=) overloads to define a decimal object from various data types
* to_xxx() methods converting a decimal object's value to various data types
* Relational operations: `compare()` `==` `!=` `<` `<=` `>` `>=`
* Unary operations: + - ++ --
* Binary operations: + += - -= * *= / /= % %=
* Properties: `sign()` `scale()`
* Mathematical operations: `abs()` `truncate()` `floor()` `ceil()` `round()` `clamp()`
* Constants: `max_scale()` `max_value()` `min_value()`

Errors are expressed via thrown exceptions e.g. `decimal{1} / decimal{0}` will throw a divide-by-zero exception

## 4.1. decimal.h

```c++
#if !defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_)
#define __WindowsAppSDK_Microsoft_Windows_Foundation_decimal_

#include <oleauto.h>

#if !defined(_VC_NODEFAULTLIB)
#pragma comment(linker, "/defaultlib:oleaut32.lib")
#endif

inline int compare(const DECIMAL& left, const DECIMAL& right);

inline bool operator==(const DECIMAL& left, const DECIMAL& right);

inline bool operator!=(const DECIMAL& left, const DECIMAL& right);

inline bool operator< (const DECIMAL& left, const DECIMAL& right);

inline bool operator<=(const DECIMAL& left, const DECIMAL& right);

inline bool operator> (const DECIMAL& left, const DECIMAL& right);

inline bool operator>=(const DECIMAL& left, const DECIMAL& right);

namespace Microsoft::Windows::Foundation
{
class decimal
{
public:
    decimal() = default;
    ~decimal() = default;

    decimal(const decimal& value);
    decimal(decimal&& value);
    constexpr decimal(const DECIMAL& value);
    decimal(bool value)l
    decimal(char value);
    decimal(std::int16_t value);
    decimal(std::int32_t value);
    decimal(std::int64_t value);
    decimal(std::uint8_t value);
    decimal(std::uint16_t value);
    decimal(std::uint32_t value);
    decimal(std::uint64_t value);
    decimal(float value);
    decimal(double value);
    decimal(long value);
    decimal(unsigned long value);
    decimal(PCWSTR value);
    decimal(PCWSTR value, const LCID locale);
    decimal(const std::wstring& value);
    decimal(const std::wstring& value, const LCID locale);
#if defined(__WINSTRING_H_)
    decimal(const HSTRING& value);
    decimal(const HSTRING& value, const LCID locale);
#endif // defined(__WINSTRING_H_)
#if defined(WINRT_BASE_H)
    decimal(const winrt::hstring& value);
    decimal(const winrt::hstring& value, const LCID locale);
#endif // defined(WINRT_BASE_H)

    decimal& operator=(const decimal& value);
    decimal& operator=(decimal&& value);
    decimal& operator=(const DECIMAL& value);
    decimal& operator=(bool value);
    decimal& operator=(char value);
    decimal& operator=(std::int16_t value);
    decimal& operator=(std::int32_t value);
    decimal& operator=(std::int64_t value);
    decimal& operator=(std::uint8_t value);
    decimal& operator=(std::uint16_t value);
    decimal& operator=(std::uint32_t value);
    decimal& operator=(std::uint64_t value);
    decimal& operator=(float value);
    decimal& operator=(double value);
    decimal& operator=(long value);
    decimal& operator=(unsigned long value);
    decimal& operator=(PCWSTR value);
    decimal& operator=(const std::wstring& value);
#if defined(__WINSTRING_H_)
    decimal& operator=(const HSTRING& value);
#endif // defined(__WINSTRING_H_)
#if defined(WINRT_BASE_H)
    decimal& operator=(const winrt::hstring& value);
#endif // defined(WINRT_BASE_H)

    const DECIMAL& to_decimal() const;
    bool to_bool() const;
    char to_char() const;
    std::int16_t to_int16() const;
    std::int32_t to_int32() const;
    std::int64_t to_int64() const;
    std::uint8_t to_uint8() const;
    std::uint16_t to_uint16() const;
    std::uint32_t to_uint32() const;
    std::uint64_t to_uint64() const;
    float to_float() const;
    double to_double() const;
    long to_long() const;
    unsigned long to_ulong() const;
    std::wstring to_string() const;
    std::wstring to_string(const LCID locale) const;
#if defined(__WINSTRING_H_)
    HSTRING to_HSTRING() const;
    HSTRING to_HSTRING(const LCID locale) const;
#endif // defined(WINRT_BASE_H)
#if defined(WINRT_BASE_H)
    winrt::hstring to_hstring() const;
    winrt::hstring to_hstring(const LCID locale) const;
#endif // defined(WINRT_BASE_H)

    bool operator==(const decimal& value) const;
    bool operator!=(const decimal& value) const;
    bool operator< (const decimal& value) const;
    bool operator<=(const decimal& value) const;
    bool operator> (const decimal& value) const;
    bool operator>=(const decimal& value) const;
    int compare(const decimal& value) const;

    bool operator==(const DECIMAL& value) const;
    bool operator!=(const DECIMAL& value) const;
    bool operator< (const DECIMAL& value) const;
    bool operator<=(const DECIMAL& value) const;
    bool operator> (const DECIMAL& value) const;
    bool operator>=(const DECIMAL& value) const;
    int compare(const DECIMAL& value) const;

    /// Return true if this is valid.
    bool is_valid();

    /// Return true if value is valid.
    static constexpr bool is_valid(const DECIMAL& value);

    /// Return the scaling factor of the value (the number of decimal digits).
    /// @return the scaling factor, ranging from 0 to max_scale().
    std::uint32_t scale() const;

    /// Return the sign of the value.
    /// @return 0 if this os zero, <0 if this is less than zero or >0 if this is greater than zero.
    std::int32_t sign() const;

    /// Return the maximum scaling factor
    static constexpr std::uint32_t max_scale();

    /// Return the maximum value (79,228,162,514,264,337,593,543,950,335).
    static constexpr decimal max_value();

    /// Return the minimum value (-79,228,162,514,264,337,593,543,950,335).
    static constexpr decimal min_value();

    decimal operator+() const;

    decimal operator-() const;

    decimal abs() const;

    /// Return the integral digits; any fractional digits are discarded.
    decimal truncate() const;

    /// Return the integral digits rounded down to -infinity; any fractional digits are discarded.
    decimal floor() const;

    /// Return the integral digits rounded up to +infinity; any fractional digits are discarded.
    decimal ceil() const;

    /// Return this clamped to the inclusive range of min and max.
    /// @return this if min <= this <= max, or min if this < min, or max if max < this.
    decimal clamp(decimal min, decimal max) const;

    decimal operator++();
    decimal operator++(int);

    decimal operator--();
    decimal operator--(int);

    decimal operator+(const decimal& value) const;
    decimal operator-(const decimal& value) const;
    decimal operator*(const decimal& value) const;
    decimal operator/(const decimal& value) const;

    /// Modulo operation using the Truncated method.
    /// @note The % operator in C, C#, Rust and other languages use this method.
    /// @note The result's sign will match the current value's sign.
    /// @see https://en.wikipedia.org/wiki/Modulo
    decimal operator%(const decimal& value) const;

    decimal& operator+=(const decimal& value);
    decimal& operator-=(const decimal& value);
    decimal& operator*=(const decimal& value);
    decimal& operator/=(const decimal& value);
    decimal& operator%=(const decimal& value);

    decimal round(const std::int32_t decimalPlaces) const;

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
inline DECIMAL to_DECIMAL(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);

/// Return value as a WinRT DecimalValue structure.
inline winrt::Microsoft::Windows::Foundation::DecimalValue to_DecimalValue(DECIMAL const& value);
}

//----------------------------------------------------------
// WinRT DecimalValue operators

// C++/WinRT generates bool operator==(DecimalValue const& left, DecimalValue const& right)

// C++/WinRT generates bool operator!=(DecimalValue const& left, DecimalValue const& right)

inline bool operator<(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right);

inline bool operator<=(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right);

inline bool operator>(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right);

inline bool operator>=(
    winrt::Microsoft::Windows::Foundation::DecimalValue const& left,
    winrt::Microsoft::Windows::Foundation::DecimalValue const& right);

#endif // defined(WINRT_Microsoft_Windows_Foundation_H) && !defined(__WINDOWSAPPSDK_WINRT_M_W_F_DECIMAL_)

//----------------------------------------------------------------------
// C++ decimal support

#if defined(WINRT_Microsoft_Windows_Foundation_H) && defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_) && !defined(__WINDOWSAPPSDK_CPP_M_W_F_DECIMAL_)
#define __WINDOWSAPPSDK_CPP_M_W_F_DECIMAL_

//----------------------------------------------------------
// WinRT DecimalValue <-> C++ decimal conversions

namespace winrt::Microsoft::Windows::Foundation
{
/// Return true if value is valid.
constexpr bool is_valid(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);

/// Return value as a C++ decimal object.
inline ::Microsoft::Windows::Foundation::decimal to_decimal(winrt::Microsoft::Windows::Foundation::DecimalValue const& value);

/// Return value as a WinRT DecimalValue structure.
inline winrt::Microsoft::Windows::Foundation::DecimalValue to_DecimalValue(::Microsoft::Windows::Foundation::decimal const& value);
}

#endif // defined(WINRT_Microsoft_Windows_Foundation_H) && defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_) && !defined(__WINDOWSAPPSDK_CPP_M_W_F_DECIMAL_)
```

# 6. Open Issues

# 6.1. API Review

Potential changes for API Review consideration:

1. String conversions - How to handle
   1. VarDecFromStr() and VarBStrFromDec() support localization via LCID. WinRT doesn't.
      1. Support LCID for localization?
         1. C++ has to/from string with optional LCID parameter
            1. Default LCID=LOCALE_INVARIANT
         2. WinRT has pre-canned variants:
            1. ToString()                           // LCID=LOCALE_INVARIANT
            2. ToStringWithSystemDefaultLocale()    // LCID=GetSystemDefaultLCID()
            3. ToStringWithUserDefaultLocale()      // LCID=GetUserDefaultLCID()
            4. ToStringWithThreadLocale()           // LCID=GetThreadLocale()
      2. Use alternative ??? for localization?
         1. ??? <-> LCID conversion APIs?
         2. Rewrite VarDecFromStr() and VBstrFromDec() as equivalents using ???
         3. Windows.Globalization.NumberFormatting.DecimalFormatter has Format/Parse(Double/Int64/UInt64) but no DECIMAL
2. Rename FromString*() to Parse() + TryParse()?
3. Rename ToString*() to Format()?

# 6.2. TODO

Punchlist to reach Stable:

1. C++ class
   1. Add Round(decimalPlaces, Windows.Globalization.NumberFormatting.RoundingAlgorithm)
2. winrt::Microsoft::Windows::Foundation::DecimalHelper
   1. Add Round(decimalPlaces, Windows.Globalization.NumberFormatting.RoundingAlgorithm)
   2. Add experimental checks
3. C# Tests
   1. TAEF for C# ?
   2. Port test\inc\WindowsAppRuntime.Test.Package.h to C#
   3. Port test\inc\WindowsAppRuntime.Test.Bootstrap.h to C#
   4. Register framework package
   5. Bootstrap.Initialize()
   6. Implement remaining tests
