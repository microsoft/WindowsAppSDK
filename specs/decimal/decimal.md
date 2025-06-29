- [1. Decimal](#1-decimal)
- [2. Common Decimal Representation](#2-common-decimal-representation)
- [3. Examples](#3-examples)
- [4. C# Example](#4-c-example)
- [5. C++ Example](#5-c-example)
- [6. WinRT Example](#6-winrt-example)
- [7. WinRT API](#7-winrt-api)
- [8. C++ API](#8-c-api)
  - [8.1. decimal.h](#81-decimalh)
  - [8.2. decimalcppwinrt.h](#82-decimalcppwinrth)
- [9. C# API](#9-c-api)

# 1. Decimal

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

2.1. OLE Automation APIs

The [OLE Automation APIs](https://learn.microsoft.com/windows/win32/api/oleauto/) operating on
[DECIMAL](https://learn.microsoft.com/windows/win32/api/wtypes/ns-wtypes-decimal-r1) provide the
core functionality used by the APIs in this spec e.g. [VarDecFromStr](https://learn.microsoft.com/windows/win32/api/oleauto/nf-oleauto-vardecfromstr)
to convert a string to `DECIMAL`.

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

# 4. C# Example

NOTE: This example uses [C#'s Decimal support](https://learn.microsoft.com/dotnet/api/system.decimal)
providing the canonical reference for examples in other languages.

```c#
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
        var z = (Decimal.Floor(y) - 1) * (Decimal.Ceiling(x) + 1) * -Decimal.Truncate(y);

        Console.WriteLine($"x = {x}");
        Console.WriteLine($"y = {y}");
        Console.WriteLine($"z = {z}");

        Environment.Exit((int)z);
    }
}
```

# 5. C++ Example

This program illustrates the reference example using Windows App SDK's C++ decimal class.

```c++
#include <windows.h>
#include <stdio.h>
#include <decimal.h>

int main()
{
    const Microsoft::Windows::Foundation::decimal a{ 1 };
    const Microsoft::Windows::Foundation::decimal b{ 0.5 };
    const auto c{ Microsoft::Windows::Foundation::decimal::from_string("-6.66") };
    const auto d{ Microsoft::Windows::Foundation::decimal::from_string("1.23") };
    const auto e{ Microsoft::Windows::Foundation::decimal::from_string("4567.089" };
    const Microsoft::Windows::Foundation::decimal f{ -4ll };
    const Microsoft::Windows::Foundation::decimal g{ 1967u };
    const Microsoft::Windows::Foundation::decimal h{ 1001.0f };

    auto x = (((a - b) + (c % d)) * e).round(5) / f;
    auto y = x++.round(3).clamp(f, g);
    auto z = --y.floor() * ++x.ceil() * -y.truncate();

    printf("x = %ls\n", x.to_wstring_invariant().c_str());
    printf("y = %ls\n", y.to_wstring_invariant().c_str());
    printf("z = %ls\n", z.to_wstring_invariant().c_str());
    return z.to_int32();
}
```

# 6. WinRT Example

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
    const auto c{ DH::FromStringInvariant(L"-6.66") };
    const auto d{ DH::FromStringInvariant(L"1.23") };
    const auto e{ DH::FromStringInvariant(L"4567.089") };
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

    printf(L"x = %ls\n", DH::ToStringInvariant(x).c_str());
    printf(L"y = %ls\n", DH::ToStringInvariant(y).c_str());
    printf(L"z = %ls\n", DH::ToStringInvariant(z).c_str());
    return DH::ToInt32(z);
}
```

# 7. WinRT API

Windows App SDK provides a `DecimalHelper` WinRT runtimeclass in addition to the `DecimalValue` structure.

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

        /// Parse the string using the user's default locale.
        static DecimalValue FromString(String source);

        /// Parse the string using the invariant locale.
        static DecimalValue FromStringInvariant(String source);

        /// Parse the string using the specified locale.
        [method_name("FromStringWithLocale")]
        static DecimalValue FromString(String source, String localeName);

        /// Parse the string using the user's default locale.
        static Boolean TryFromString(String source, out DecimalValue value);

        /// Parse the string using the invariant locale.
        static Boolean TryFromStringInvariant(String source, out DecimalValue value);

        /// Parse the string using the specified locale.
        [method_name("TryFromStringWithLocale")]
        static Boolean TryFromString(String source, String localeName, out DecimalValue value);

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

        /// Format the string using the user's default locale.
        static String ToString(DecimalValue value);

        /// Format the string using the invariant locale.
        static String ToStringInvariant(DecimalValue value);

        /// Format the string using the specified locale.
        [method_name("ToStringWithLocale")]
        static String ToString(DecimalValue value, String localeName);

        /// Return true if (left == right).
        static Boolean Equals(DecimalValue left, DecimalValue right);

        /// Compare decimal values.
        /// @return 0 if left and right are equal, <0 if left is less than right or >0 if left is greater than right.
        static Int32 Compare(DecimalValue left, DecimalValue right);

        /// Return true if the value is valid.
        static Boolean IsValid(DecimalValue value);

        /// Return true if value is an integral number.
        static Boolean IsInteger(DecimalValue value);

        /// Return the scaling factor of the value (the number of decimal digits).
        /// @return the scaling factor, ranging from 0 to max_scale().
        static UInt8 Scale(DecimalValue value);

        /// Return the sign of the value.
        /// @return 0 if value is zero, <0 if value is less than zero or >0 if value is greater than zero.
        static Int32 Sign(DecimalValue value);

        /// Return the maximum scaling factor
        static UInt8 MaxScale();

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

# 8. C++ API

Windows App SDK provides a native language decimal data type for C++ as the
`Microsoft::Windows::Foundation::decimal` class in `decimal.h`. This class has the following features:

* Constructor and assignment (operator=) overloads to define a decimal object from various data types
* to_xxx() methods converting a decimal object's value to various string data types
* [try]_from_xxx() methods converting a decimal object's value from various string data types
* Relational operations: `compare()` `==` `!=` `<` `<=` `>` `>=`
* Unary operations: `+` `-` `++` `--`
* Binary operations: `+` `+=` `-` `-=` `*` `*=` `/` `/=` `%` `%=`
* Properties: `sign()` `scale()`
* Mathematical operations: `abs()` `truncate()` `floor()` `ceil()` `round()` `clamp()`
* Constants: `max_scale()` `max_value()` `min_value()`
* Validation: `is_integer()` `is_valid()`

Errors are expressed via thrown exceptions e.g. `decimal{1} / decimal{0}` will throw a divide-by-zero exception

## 8.1. decimal.h

```c++
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_)
#define __WindowsAppSDK_Microsoft_Windows_Foundation_decimal_

#include <winnls.h>
#include <oleauto.h>

#include <string>

#include <wil/cppwinrt.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

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

    decimal(bool value);

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

public:
    /// Parse the string using the user's default locale.
    static decimal from_string(PCSTR source);

    /// Parse the string using the invariant locale.
    static decimal from_string_invariant(PCSTR source);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT ("!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT ("") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_string(PCSTR source, PCSTR localeName);

    /// Parse the string using the user's default locale.
    static bool try_from_string(PCSTR source, decimal& value);

    /// Parse the string using the invariant locale.
    static bool try_from_string_invariant(PCSTR source, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_string(PCSTR source, PCSTR localeName, decimal& value);

public:
    /// Parse the string using the user's default locale.
    static decimal from_string(PCWSTR source);

    /// Parse the string using the invariant locale.
    static decimal from_string_invariant(PCWSTR source);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_string(PCWSTR source, PCWSTR localeName);

    /// Parse the string using the user's default locale.
    static bool try_from_string(PCWSTR source, decimal& value);

    /// Parse the string using the invariant locale.
    static bool try_from_string_invariant(PCWSTR source, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_string(PCWSTR source, PCWSTR localeName, decimal& value);

public:
    /// Parse the string using the user's default locale.
    static decimal from_string(const std::string& source);

    /// Parse the string using the invariant locale.
    static decimal from_string_invariant(const std::string& source);

    /// Parse the string using the specified locale.
    /// @note localeName="!x-sys-default-locale" for the system default locale.
    /// @note localeName="" for the invariant locale.
    /// @note localeName=NULL for the user default locale.
    static decimal from_string(const std::string& source, const std::string& localeName);

    /// Parse the string using the specified locale.
    /// @note localeName="!x-sys-default-locale" for the system default locale.
    /// @note localeName="" for the invariant locale.
    /// @note localeName=NULL for the user default locale.
    static decimal from_string(const std::string& source, const PCSTR localeName);

    /// Parse the string using the user's default locale.
    static bool try_from_string(const std::string& source, decimal& value);

    /// Parse the string using the invariant locale.
    static bool try_from_string_invariant(const std::string& source, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_string(const std::string& source, const std::string& localeName, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_string(const std::string& source, PCSTR localeName, decimal& value);

public:
    /// Parse the string using the user's default locale.
    static decimal from_wstring(const std::wstring& source);

    /// Parse the string using the invariant locale.
    static decimal from_wstring_invariant(const std::wstring& source);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_wstring(const std::wstring& source, const std::wstring& localeName);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_wstring(const std::wstring& source, const std::wstring& localeName);

    /// Parse the string using the user's default locale.
    static bool try_from_wstring(const std::wstring& source, decimal& value);

    /// Parse the string using the invariant locale.
    static bool try_from_wstring_invariant(const std::wstring& source, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_wstring(const std::wstring& source, const std::wstring& localeName, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_wstring(const std::wstring& source, PCWSTR localeName, decimal& value);

public:
#if defined(__hstring_h__) && defined(__WINSTRING_H_)
    /// Parse the string using the user's default locale.
    static decimal from_HSTRING(const HSTRING& source);

    /// Parse the string using the invariant locale.
    static decimal from_HSTRING_invariant(const HSTRING& source);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_HSTRING(const HSTRING& source, const HSTRING& localeName);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_HSTRING(const HSTRING& source, const HSTRING& localeName);

    /// Parse the string using the user's default locale.
    static bool try_from_HSTRING(const HSTRING& source, decimal& value);

    /// Parse the string using the invariant locale.
    static bool try_from_HSTRING_invariant(const HSTRING& source, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_HSTRING(const HSTRING& source, const HSTRING& localeName, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_HSTRING(const HSTRING& source, PCWSTR localeName, decimal& value);
#endif // defined(__hstring_h__) && defined(__WINSTRING_H_)

public:
#if defined(WINRT_BASE_H)
    /// Parse the string using the user's default locale.
    static decimal from_hstring(const winrt::hstring& source);

    /// Parse the string using the invariant locale.
    static decimal from_hstring_invariant(const winrt::hstring& source);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_hstring(const winrt::hstring& source, const winrt::hstring& localeName);

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_hstring(const winrt::hstring& source, PCWSTR localeName);

    /// Parse the string using the user's default locale.
    static bool try_from_hstring(const winrt::hstring& source, decimal& value);

    /// Parse the string using the invariant locale.
    static bool try_from_hstring_invariant(const winrt::hstring& source, decimal& value);

    /// Parse the string using the specified locale.
    static bool try_from_hstring(const winrt::hstring& source, const winrt::hstring& localeName, decimal& value)

    /// Parse the string using the specified locale.
    static bool try_from_hstring(const winrt::hstring& source, const winrt::hstring& localeName, decimal& value);
#endif // defined(WINRT_BASE_H)

    decimal& operator=(const decimal& value);

    decimal& operator=(decimal&& value);

    decimal& operator=(const DECIMAL& value);

    decimal& operator=(bool value);

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

    const DECIMAL& to_decimal() const;

    bool to_bool() const;

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

public:
    // Format the string using the user's default locale.
    std::string to_string() const;

    // Format the string using the invariant locale.
    std::string to_string_invariant() const;

    // Format the string using the specified locale.
    std::string to_string(PCWSTR localeName) const;

    // Format the string using the specified locale.
    std::string to_string(const std::string& localeName) const;

public:
    // Format the string using the user's default locale.
    std::wstring to_wstring() const;

    // Format the string using the invariant locale.
    std::wstring to_wstring_invariant() const;

    // Format the string using the specified locale.
    std::wstring to_wstring(const std::wstring& localeName) const;

    // Format the string using the specified locale.
    std::wstring to_wstring(PCWSTR localeName) const;

public:
#if defined(__hstring_h__) && defined(__WINSTRING_H_)
    HSTRING to_HSTRING() const;

    HSTRING to_HSTRING_invariant() const;

    HSTRING to_HSTRING(const HSTRING& localeName) const;

    HSTRING to_HSTRING(PCWSTR localeName) const;
#endif // defined(__hstring_h__) && defined(__WINSTRING_H_)

public:
#if defined(WINRT_BASE_H)
    winrt::hstring to_hstring() const;

    winrt::hstring to_hstring_invariant() const;

    winrt::hstring to_hstring(const winrt::hstring& localeName) const;

    winrt::hstring to_hstring(PCWSTR localeName) const;
#endif // defined(WINRT_BASE_H)

public:
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

    /// Return true if value is valid.
    static constexpr bool is_valid(const DECIMAL& value);

    /// Return true if this is an integral number.
    bool is_integer() const;

    /// Return true if value is an integral number.
    static constexpr bool is_integer(const DECIMAL& value);

    /// Return the scaling factor of the value (the number of decimal digits).
    /// @return the scaling factor, ranging from 0 to max_scale().
    std::uint8_t scale() const;

    /// Return the sign of the value.
    /// @return 0 if this os zero, <0 if this is less than zero or >0 if this is greater than zero.
    std::int32_t sign() const;

    /// Return the maximum scaling factor
    static constexpr std::uint8_t max_scale();

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

    decimal& operator+=(const decimal& value);

    decimal operator-(const decimal& value) const;

    decimal& operator-=(const decimal& value);

    decimal operator*(const decimal& value) const;

    decimal& operator*=(const decimal& value);

    decimal operator/(const decimal& value) const;

    decimal& operator/=(const decimal& value);

    /// Modulo operation using the Truncated method.
    /// @note The % operator in C, C#, Rust and other languages use this method.
    /// @note The result's sign will match the current value's sign.
    /// @see https://en.wikipedia.org/wiki/Modulo
    decimal operator%(const decimal& value) const;

    decimal& operator%=(const decimal& value);

    decimal round(const std::int32_t decimalPlaces) const;
};
}

#endif // !defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_)
```

## 8.2. decimalcppwinrt.h

This header provides C++/WinRT and Windows App SDK's DecimalValue integration.

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
/// Return true if value is valid.
constexpr bool is_valid(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
{
    return ::Microsoft::Windows::Foundation::decimal::is_valid(to_DECIMAL(value));
}

/// Return true if value is an integral number.
constexpr bool is_integer(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
{
    return ::Microsoft::Windows::Foundation::decimal::is_integer(to_DECIMAL(value));
}

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

# 9. C# API

C# provides rich support via its [Decimal struct](https://learn.microsoft.com/dotnet/api/system.decimal).
Windows App SDK adds a small C# API in an assembly for interop with `DecimalValue`.

```c#
namespace Microsoft.Windows.Foundation
{
    public static class DecimalExtensions
    {
        /// Return a WinRT DecimalValue structure.
        public static Microsoft.Windows.Foundation.DecimalValue ToDecimalValue(this decimal d);

        /// Return a C# Decimal object.
        public static decimal ToDecimal(this decimal d, Microsoft.Windows.Foundation.DecimalValue value);
    }
}
```
