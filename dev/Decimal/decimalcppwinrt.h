// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <oleauto.h>

#if defined(WINRT_Microsoft_Windows_Foundation_H) && !defined(__WINDOWSAPPSDK_WIMRT_M_W_F_DECIMAL_)
#define __WINDOWSAPPSDK_WIMRT_M_W_F_DECIMAL_

//----------------------------------------------------------------------
// WinRT Decimal operators

inline bool operator==(
    winrt::Microsoft::Windows::Foundation::Decimal const& left,
    winrt::Microsoft::Windows::Foundation::Decimal const& right)
{
    return left.Compare(right) == 0;
}

inline bool operator!=(
    winrt::Microsoft::Windows::Foundation::Decimal const& left,
    winrt::Microsoft::Windows::Foundation::Decimal const& right)
{
    return left.Compare(right) != 0;
}

inline bool operator<(
    winrt::Microsoft::Windows::Foundation::Decimal const& left,
    winrt::Microsoft::Windows::Foundation::Decimal const& right)
{
    return left.Compare(right) < 0;
}

inline bool operator<=(
    winrt::Microsoft::Windows::Foundation::Decimal const& left,
    winrt::Microsoft::Windows::Foundation::Decimal const& right)
{
    return left.Compare(right) <= 0;
}

inline bool operator>(
    winrt::Microsoft::Windows::Foundation::Decimal const& left,
    winrt::Microsoft::Windows::Foundation::Decimal const& right)
{
    return left.Compare(right) > 0;
}

inline bool operator>=(
    winrt::Microsoft::Windows::Foundation::Decimal const& left,
    winrt::Microsoft::Windows::Foundation::Decimal const& right)
{
    return left.Compare(right) >= 0;
}

//----------------------------------------------------------------------
// Conversion functions

namespace winrt::Microsoft::Windows::Foundation
{
/// Return value as DECIMAL.
inline DECIMAL to_DECIMAL(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
{
    return *reinterpret_cast<DECIMAL const*>(&value);
}

/// Return value as DECIMAL.
inline DECIMAL to_DECIMAL(winrt::Microsoft::Windows::Foundation::Decimal const& value)
{
    return to_DECIMAL(value.ToDecimalValue());
}

/// Return value as a WinRT DecimalValue structure.
inline winrt::Microsoft::Windows::Foundation::DecimalValue to_DecimalValue(DECIMAL const& value)
{
    return *reinterpret_cast<winrt::Microsoft::Windows::Foundation::DecimalValue const*>(&value);
}

/// Return value as a WinRT Decimal object.
inline winrt::Microsoft::Windows::Foundation::Decimal to_Decimal(DECIMAL const& value)
{
    return winrt::Microsoft::Windows::Foundation::Decimal::CreateFromDecimalValue(to_DecimalValue(value));
}

#if defined(DECIMAL_H) && !defined(__WINDOWSAPPSDK_DECIMAL_)
#define __WINDOWSAPPSDK_DECIMAL_

/// Return value as a WinRT DecimalValue structure.
inline winrt::Microsoft::Windows::Foundation::DecimalValue to_DecimalValue(::Microsoft::Windows::Foundation::decimal const& value)
{
    return to_DecimalValue(value.to_decimal());
}

/// Return value as a WinRT decimal object.
inline winrt::Microsoft::Windows::Foundation::Decimal to_Decimal(::Microsoft::Windows::Foundation::decimal const& value)
{
    return to_Decimal(value.to_decimal());
}

/// Return value as a C++ decimal object.
inline ::Microsoft::Windows::Foundation::decimal to_decimal(winrt::Microsoft::Windows::Foundation::Decimal const& value)
{
    return ::Microsoft::Windows::Foundation::decimal{ to_DECIMAL(value) };
}

/// Return value as a C++ decimal object.
inline ::Microsoft::Windows::Foundation::decimal to_decimal(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
{
    return ::Microsoft::Windows::Foundation::decimal{ to_DECIMAL(value) };
}

#endif // defined(DECIMAL_H) && !defined(__WINDOWSAPPSDK_DECIMAL_)

}

#endif // defined(WINRT_Microsoft_Windows_Foundation_H) && !defined(__WINDOWSAPPSDK_WIMRT_M_W_F_DECIMAL_)
