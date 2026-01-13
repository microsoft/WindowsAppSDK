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
