# 1. Decimal

This feature provides a WinRT decimal data type comparable to .NET's [System.Decimal](https://learn.microsoft.com/dotnet/api/system.decimal).

# 2. TODO

THIS FEATURE IS CURRENTLY EXPERIMENTAL.

Potential future changes

1. C++ class
   1. Add floor() - round towards +infinity. https://learn.microsoft.com/en-us/dotnet/api/system.decimal.floor
   2. Add ceil() - round towards -infinity. https://learn.microsoft.com/en-us/dotnet/api/system.decimal.ceiling
      1. Rename integer() to ceil() ?
   3. Add round towards zero
   4. decimal zero{}; decimal neg{ -zero }; neg.sign() < 0 because DECIMAL.sign = 0x80. Treat -0 the same as +0 (prevent -0 from being set?)
2. winrt::Microsoft::Windows::Foundation::Decimal
   1. Rename ToDecimal() -- Copy(value) or Clone(value)
   2. Rename Sub() to Subtract()
   3. Rename Mul() to Multiply()
   4. Rename Div() to Divide()
   5. Rename Mod() to Modulo() or Remainder()
3. decimalcppwinrt.h
   1. Add operator+
   2. Add operator-
   3. Add operator++
   4. Add operator--
   5. Add operator + - * / %
   6. Add operator += -= *= /= %=
   7. Add ctor(type) where type = bool / [u]int8/16/32/64 / float / double ?
   8. Add operator=(type) where type = bool / [u]int8/16/32/64 / float / double ?
4. Microsoft.Windows.Foundation.Projection
   1. Delete WDecimal.cs
   2. Add WinRT<->C# conversion functions
      1. System.Decimal ToSystemDecimal(Microsoft.Windows.Foundation.Decimal from)
      1. System.Decimal ToSystemDecimal(Microsoft.Windows.Foundation.DecimalValue from)
      1. Microsoft.Windows.Foundation.Decimal ToDecimal(System.Decimal from)
      1. Microsoft.Windows.Foundation.DecimalValue ToDecimalValue(System.Decimal from)
