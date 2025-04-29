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

The [DECIMAL structure](https://learn.microsoft.com/windows/win32/api/wtypes/ns-wtypes-decimal-r1)
is the common decimal format, stored as a 96-bit (12-byte) unsigned integer scaled by a variable
power of 10. The power of 10 scaling factor specifies the number of digits to the right of the
decimal point, and ranges from 0 to 28. This is expressed in WinRT as the following structure:

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

This matches the memory layout and use of the [Win32 DECIMAL structure](https://learn.microsoft.com/windows/win32/api/wtypes/ns-wtypes-decimal-r1)
and the [C# Decimal struct](https://learn.microsoft.com/dotnet/api/system.decimal). This data
structure may be re-expressed in each language using language-specific constructs e.g. WinRT defines
the `DecimalValue` structure as the Win32 `DECIMAL` definition syntax is incompatible with WinRT IDL.

# 3. WinRT API

Windows App SDK provides a `Decimal` WinRT runtimeclass in addition to the `DecimalValue` structure.

```c# (but really MIDL3)
namespace Microsoft.Windows.Foundation
{
    [contractversion(1)]
    apicontract DecimalContract{};

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
    runtimeclass Decimal : Windows.Foundation.IStringable
    {
        Decimal();

        static Decimal CreateFromBoolean(Boolean value);
        static Decimal CreateFromInt16(Int16 value);
        static Decimal CreateFromInt32(Int32 value);
        static Decimal CreateFromInt64(Int64 value);
        static Decimal CreateFromUInt8(UInt8 value);
        static Decimal CreateFromUInt16(UInt16 value);
        static Decimal CreateFromUInt32(UInt32 value);
        static Decimal CreateFromUInt64(UInt64 value);
        static Decimal CreateFromSingle(Single value);
        static Decimal CreateFromDouble(Double value);
        static Decimal CreateFromString(String value);                          // LCID=LOCALE_INVARIANT
        static Decimal CreateFromStringWithSystemDefaultLocale(String value);   // LCID=GetSystemDefaultLCID()
        static Decimal CreateFromStringWithUserDefaultLocale(String value);     // LCID=GetUserDefaultLCID()
        static Decimal CreateFromStringWithThreadLocale(String value);          // LCID=GetThreadLocale()
        static Decimal CreateFromStringWithInvariantLocale(String value);       // LCID=LOCALE_INVARIANT
        static Decimal Create(IInspectable value);
        static Decimal CreateFromDecimal(Decimal value);
        static Decimal CreateFromDecimalValue(DecimalValue value);

        void SetFromBoolean(Boolean value);
        void SetFromInt16(Int16 value);
        void SetFromInt32(Int32 value);
        void SetFromInt64(Int64 value);
        void SetFromUInt8(UInt8 value);
        void SetFromUInt16(UInt16 value);
        void SetFromUInt32(UInt32 value);
        void SetFromUInt64(UInt64 value);
        void SetFromSingle(Single value);
        void SetFromDouble(Double value);
        void SetFromString(String value);                           // LCID=LOCALE_INVARIANT
        void SetFromStringWithSystemDefaultLocale(String value);    // LCID=GetSystemDefaultLCID()
        void SetFromStringWithUserDefaultLocale(String value);      // LCID=GetUserDefaultLCID()
        void SetFromStringWithThreadLocale(String value);           // LCID=GetThreadLocale()
        void SetFromStringWithInvariantLocale(String value);        // LCID=LOCALE_INVARIANT
        void Set(IInspectable value);
        void SetFromDecimal(Decimal value);
        void SetFromDecimalValue(DecimalValue value);

        Boolean ToBoolean();
        Int16 ToInt16();
        Int32 ToInt32();
        Int64 ToInt64();
        UInt8 ToUInt8();
        UInt16 ToUInt16();
        UInt32 ToUInt32();
        UInt64 ToUInt64();
        Single ToSingle();
        Double ToDouble();
        //String ToString(); inherited from IStringable     // LCID=LOCALE_INVARIANT
        String ToStringWithSystemDefaultLocale();           // LCID=GetSystemDefaultLCID()
        String ToStringWithUserDefaultLocale();             // LCID=GetUserDefaultLCID()
        String ToStringWithThreadLocale();                  // LCID=GetThreadLocale()
        String ToStringWithInvariantLocale();               // LCID=LOCALE_INVARIANT
        IInspectable ToObject();
        Decimal ToDecimal();                //TODO: Rename to Copy(value) or Clone(value) ?
        DecimalValue ToDecimalValue();

        /// Return true if (this == value).
        Boolean Equals(Decimal value);

        /// Compare this decimal with value.
        /// @return 0 if this and value are equal, <0 if this is less than value or >0 if this is greater than value.
        Int32 Compare(Decimal value);

        /// Return the scaling factor of the value (the number of decimal digits).
        /// @return the scaling factor, ranging from 0 to max_scale().
        UInt32 Scale { get; };

        /// Return the sign of the value.
        /// @return 0 if this os zero, <0 if this is less than zero or >0 if this is greater than zero.
        Int32 Sign { get; };

        /// Return the maximum scaling factor
        static UInt32 MaxScale{ get; };

        /// Return the maximum value (79,228,162,514,264,337,593,543,950,335).
        static Decimal MaxValue{ get; };

        /// Return the minimum value (-79,228,162,514,264,337,593,543,950,335).
        static Decimal MinValue{ get; };

        /// Return a decimal whose value is (-this).
        Decimal Negate();

        /// Return the absolute value.
        Decimal Abs();

        /// Return the value's integer portion (zero to the right of the decimal point).
        Decimal Fix();

        /// Return the value rounded down to the nearest integer.
        Decimal Integer();

        /// Return the value rounded to the specific number of decimal places.
        Decimal Round(Int32 decimalPlaces);

        /// Returns a Decimal whose value is (this + value).
        Decimal Add(Decimal value);

        /// Returns a Decimal whose value is (this - value).
        Decimal Sub(Decimal value);

        /// Returns a Decimal whose value is (this * value).
        Decimal Mul(Decimal value);

        /// Returns a Decimal whose value is (this / value).
        Decimal Div(Decimal value);

        /// Returns a Decimal whose value is (this % value).
        Decimal Mod(Decimal value);
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

## 4.1. Microsoft.Windows.Foundation (C++)

TODO insert header filename(s) and API here

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
2. C++ class
   1. Add floor() - round towards +infinity. https://learn.microsoft.com/en-us/dotnet/api/system.decimal.floor
   2. Add ceil() - round towards -infinity. https://learn.microsoft.com/en-us/dotnet/api/system.decimal.ceiling
      1. Rename integer() to ceil() ?
   3. Add floor-ceil-variant() - round towards zero
3. winrt::Microsoft::Windows::Foundation::Decimal
   1. Rename ToDecimal() to Copy(value) or Clone(value)
   2. Add Floor()
   3. Rename Integer() to Ceil()
   4. Add Floor-Ceil-Variant() for rounds towards zero
   5. Rename Sub() to Subtract()
   6. Rename Mul() to Multiply()
   7. Rename Div() to Divide()
   8. Rename Mod() to Remainder()

# 6.2. TODO

Punchlist to reach Stable:

1. C++ class
   1. BUG? decimal zero{}; decimal neg{ -zero }; neg.sign() < 0 because DECIMAL.sign = 0x80. Treat -0 the same as +0 (prevent -0 from being set?)
2. winrt::Microsoft::Windows::Foundation::Decimal
   1. Implement IInspectable methods -- Create(IInspectable), Set(IInspectable), ToObject()
   2. Add experimental checks in ctor + static methods
3. decimalcppwinrt.h
   1. Merge into decimal.h
4. Microsoft.Windows.Foundation.Projection
   1. --none--
5. C# Tests
   1. TAEF for C# ?
   2. Port test\inc\WindowsAppRuntime.Test.Package.h to C#
   3. Port test\inc\WindowsAppRuntime.Test.Bootstrap.h to C#
   4. Register framework package
   5. Bootstrap.Initialize()
   6. Implement remaining tests
