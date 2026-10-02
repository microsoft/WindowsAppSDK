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
        validate(value);
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

private:
    static std::unique_ptr<WCHAR[]> to_wide_string(PCSTR source)
    {
        if (!source)
        {
            return std::make_unique<WCHAR[]>(0);
        }

        const auto lengthIncludingNullTerminator{ ::MultiByteToWideChar(CP_ACP, 0, source, -1, nullptr, 0) };
        THROW_IF_WIN32_BOOL_FALSE(lengthIncludingNullTerminator);

        std::unique_ptr<WCHAR[]> s{ std::make_unique<WCHAR[]>(lengthIncludingNullTerminator) };

        THROW_IF_WIN32_BOOL_FALSE(::MultiByteToWideChar(CP_ACP, 0, source, -1, s.get(), lengthIncludingNullTerminator));
        s[lengthIncludingNullTerminator - 1] = L'\0';
        return s;
    }

    static std::unique_ptr<char[]> to_narrow_string(PCWSTR source)
    {
        if (!source)
        {
            return std::make_unique<char[]>(0);
        }

        const auto lengthIncludingNullTerminator{ ::WideCharToMultiByte(CP_ACP, 0, source, -1, nullptr, 0, nullptr, nullptr) };
        THROW_IF_WIN32_BOOL_FALSE(lengthIncludingNullTerminator);

        std::unique_ptr<char[]> s{ std::make_unique<char[]>(lengthIncludingNullTerminator) };

        THROW_IF_WIN32_BOOL_FALSE(::WideCharToMultiByte(CP_ACP, 0, source, -1, s.get(), lengthIncludingNullTerminator, nullptr, nullptr));
        s[lengthIncludingNullTerminator - 1] = '\0';
        return s;
    }

private:
    static decimal from_string_with_locale(PCSTR source, const LCID localeId)
    {
        const auto sourceAsWideString{ to_wide_string(source) };
        return from_string_with_locale(sourceAsWideString.get(), localeId);
    }

    static decimal from_string_with_locale(PCSTR source, PCSTR localeName)
    {
        const auto sourceAsWideString{ to_wide_string(source) };
        const auto localeNameAsWideString{ to_wide_string(localeName) };
        return from_string_with_locale(sourceAsWideString.get(), localeNameAsWideString.get());
    }

    static bool try_from_string_with_locale(PCSTR source, const LCID localeId, decimal& value)
    {
        const auto sourceAsWideString{ to_wide_string(source) };
        return try_from_string_with_locale(sourceAsWideString.get(), localeId, value);
    }

    static bool try_from_string_with_locale(PCSTR source, PCSTR localeName, decimal& value)
    {
        const auto sourceAsWideString{ to_wide_string(source) };
        const auto localeNameAsWideString{ to_wide_string(localeName) };
        return try_from_string_with_locale(sourceAsWideString.get(), localeNameAsWideString.get(), value);
    }

public:
    /// Parse the string using the user's default locale.
    static decimal from_string(PCSTR source)
    {
        return from_string_with_locale(source, LOCALE_USER_DEFAULT);
    }

    /// Parse the string using the invariant locale.
    static decimal from_string_invariant(PCSTR source)
    {
        return from_string_with_locale(source, LOCALE_INVARIANT);
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT ("!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_INVARIANT ("") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_string(PCSTR source, PCSTR localeName)
    {
        return from_string_with_locale(source, localeName);
    }

    /// Parse the string using the user's default locale.
    static bool try_from_string(PCSTR source, decimal& value)
    {
        return try_from_string_with_locale(source, LOCALE_USER_DEFAULT, value);
    }

    /// Parse the string using the invariant locale.
    static bool try_from_string_invariant(PCSTR source, decimal& value)
    {
        return try_from_string_with_locale(source, LOCALE_INVARIANT, value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_string(PCSTR source, PCSTR localeName, decimal& value)
    {
        return try_from_string_with_locale(source, localeName, value);
    }

private:
    static LCID to_lcid(PCWSTR localeName)
    {
        const LCID lcid{ ::LocaleNameToLCID(localeName, 0) };
        THROW_LAST_ERROR_IF_MSG(lcid == 0, "%ls", localeName);
        return lcid;
    }

    static bool try_to_lcid(PCWSTR localeName, LCID& lcid)
    {
        lcid = ::LocaleNameToLCID(localeName, 0);
        if (lcid == 0)
        {
            std::ignore = LOG_LAST_ERROR_MSG("%ls", localeName);
            return false;
        }
        return true;
    }

private:
    static decimal from_string_with_locale(PCWSTR source, const LCID localeId)
    {
        decimal value;
        THROW_IF_FAILED(::VarDecFromStr(source, localeId, 0, &value.m_decimal));

        // VarDecFromStr() sets the result from a local variable that doesn't initialize DECIMAL.wReserved :-(
        // Make sure it's always zero to avoid inconsistent results by others using the value
        value.m_decimal.wReserved = 0;

        return value;
    }

    static decimal from_string_with_locale(PCWSTR source, PCWSTR localeName)
    {
        return from_string_with_locale(source, to_lcid(localeName));
    }

    static bool try_from_string_with_locale(PCWSTR source, const LCID localeId, decimal& value)
    {
        const HRESULT hr{ ::VarDecFromStr(source, localeId, 0, &value.m_decimal) };
        if (FAILED(hr))
        {
            return false;
        }

        // VarDecFromStr() sets the result from a local variable that doesn't initialize DECIMAL.wReserved :-(
        // Make sure it's always zero to avoid inconsistent results by others using the source
        value.m_decimal.wReserved = 0;

        return true;
    }

    static bool try_from_string_with_locale(PCWSTR source, PCWSTR localeName, decimal& value)
    {
        LCID lcid{};
        if (!try_to_lcid(localeName, lcid))
        {
            return false;
        }
        return try_from_string_with_locale(source, lcid, value);
    }

public:
    /// Parse the string using the user's default locale.
    static decimal from_string(PCWSTR source)
    {
        return from_string_with_locale(source, LOCALE_USER_DEFAULT);
    }

    /// Parse the string using the invariant locale.
    static decimal from_string_invariant(PCWSTR source)
    {
        return from_string_with_locale(source, LOCALE_INVARIANT);
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_string(PCWSTR source, PCWSTR localeName)
    {
        return from_string_with_locale(source, localeName);
    }

    /// Parse the string using the user's default locale.
    static bool try_from_string(PCWSTR source, decimal& value)
    {
        return try_from_string_with_locale(source, LOCALE_USER_DEFAULT, value);
    }

    /// Parse the string using the invariant locale.
    static bool try_from_string_invariant(PCWSTR source, decimal& value)
    {
        return try_from_string_with_locale(source, LOCALE_INVARIANT, value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_string(PCWSTR source, PCWSTR localeName, decimal& value)
    {
        return try_from_string_with_locale(source, localeName, value);
    }

public:
    /// Parse the string using the user's default locale.
    static decimal from_string(const std::string& source)
    {
        return from_string_with_locale(source.c_str(), LOCALE_USER_DEFAULT);
    }

    /// Parse the string using the invariant locale.
    static decimal from_string_invariant(const std::string& source)
    {
        return from_string_with_locale(source.c_str(), LOCALE_INVARIANT);
    }

    /// Parse the string using the specified locale.
    /// @note localeName="!x-sys-default-locale" for the system default locale.
    /// @note localeName="" for the invariant locale.
    /// @note localeName=NULL for the user default locale.
    static decimal from_string(const std::string& source, const std::string& localeName)
    {
        return from_string_with_locale(source.c_str(), localeName.c_str());
    }

    /// Parse the string using the specified locale.
    /// @note localeName="!x-sys-default-locale" for the system default locale.
    /// @note localeName="" for the invariant locale.
    /// @note localeName=NULL for the user default locale.
    static decimal from_string(const std::string& source, const PCSTR localeName)
    {
        return from_string_with_locale(source.c_str(), localeName);
    }

    /// Parse the string using the user's default locale.
    static bool try_from_string(const std::string& source, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), LOCALE_USER_DEFAULT, value);
    }

    /// Parse the string using the invariant locale.
    static bool try_from_string_invariant(const std::string& source, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), LOCALE_INVARIANT, value);
    }

    /// Parse the string using the specified locale.
    /// @note localeName="!x-sys-default-locale" for the system default locale.
    /// @note localeName="" for the invariant locale.
    /// @note localeName=NULL for the user default locale.
    static bool try_from_string(const std::string& source, const std::string& localeName, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), localeName.c_str(), value);
    }

    /// Parse the string using the specified locale.
    /// @note localeName="!x-sys-default-locale" for the system default locale.
    /// @note localeName="" for the invariant locale.
    /// @note localeName=NULL for the user default locale.
    static bool try_from_string(const std::string& source, PCSTR localeName, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), localeName, value);
    }

public:
    /// Parse the string using the user's default locale.
    static decimal from_wstring(const std::wstring& source)
    {
        return from_string_with_locale(source.c_str(), LOCALE_USER_DEFAULT);
    }

    /// Parse the string using the invariant locale.
    static decimal from_wstring_invariant(const std::wstring& source)
    {
        return from_string_with_locale(source.c_str(), LOCALE_INVARIANT);
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_wstring(const std::wstring& source, const std::wstring& localeName)
    {
        return from_string_with_locale(source.c_str(), localeName.c_str());
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_wstring(const std::wstring& source, PCWSTR localeName)
    {
        return from_string_with_locale(source.c_str(), localeName);
    }

    /// Parse the string using the user's default locale.
    static bool try_from_wstring(const std::wstring& source, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), LOCALE_USER_DEFAULT, value);
    }

    /// Parse the string using the invariant locale.
    static bool try_from_wstring_invariant(const std::wstring& source, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), LOCALE_INVARIANT, value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_wstring(const std::wstring& source, const std::wstring& localeName, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), localeName.c_str(), value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_wstring(const std::wstring& source, PCWSTR localeName, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), localeName, value);
    }

public:
#if defined(__hstring_h__) && defined(__WINSTRING_H_)
    /// Parse the string using the user's default locale.
    static decimal from_HSTRING(const HSTRING& source)
    {
        return from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), static_cast<LCID>(LOCALE_USER_DEFAULT));
    }

    /// Parse the string using the invariant locale.
    static decimal from_HSTRING_invariant(const HSTRING& source)
    {
        return from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), LOCALE_INVARIANT);
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_HSTRING(const HSTRING& source, const HSTRING& localeName)
    {
        return from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), ::WindowsGetStringRawBuffer(localeName, nullptr));
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_HSTRING(const HSTRING& source, PCWSTR localeName)
    {
        return from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), localeName);
    }

    /// Parse the string using the user's default locale.
    static bool try_from_HSTRING(const HSTRING& source, decimal& value)
    {
        return try_from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), LOCALE_USER_DEFAULT, value);
    }

    /// Parse the string using the invariant locale.
    static bool try_from_HSTRING_invariant(const HSTRING& source, decimal& value)
    {
        return try_from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), LOCALE_INVARIANT, value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_HSTRING(const HSTRING& source, const HSTRING& localeName, decimal& value)
    {
        return try_from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), ::WindowsGetStringRawBuffer(localeName, nullptr), value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_HSTRING(const HSTRING& source, PCWSTR localeName, decimal& value)
    {
        return try_from_string_with_locale(::WindowsGetStringRawBuffer(source, nullptr), localeName, value);
    }
#endif // defined(__hstring_h__) && defined(__WINSTRING_H_)

public:
#if defined(WINRT_BASE_H)
    /// Parse the string using the user's default locale.
    static decimal from_hstring(const winrt::hstring& source)
    {
        return from_string_with_locale(source.c_str(), LOCALE_USER_DEFAULT);
    }

    /// Parse the string using the invariant locale.
    static decimal from_hstring_invariant(const winrt::hstring& source)
    {
        return from_string_with_locale(source.c_str(), LOCALE_INVARIANT);
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_hstring(const winrt::hstring& source, const winrt::hstring& localeName)
    {
        return from_string_with_locale(source.c_str(), localeName.c_str());
    }

    /// Parse the string using the specified locale.
    /// @note localeName=LOCALE_NAME_SYSTEM_DEFAULT (L"!x-sys-default-locale") for the system default locale.
    /// @note localeName=LOCALE_NAME_INVARIANT (L"") for the invariant locale.
    /// @note localeName=LOCALE_NAME_USER_DEFAULT (NULL) for the user default locale.
    static decimal from_hstring(const winrt::hstring& source, PCWSTR localeName)
    {
        return from_string_with_locale(source.c_str(), localeName);
    }

    /// Parse the string using the user's default locale.
    static bool try_from_hstring(const winrt::hstring& source, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), LOCALE_USER_DEFAULT, value);
    }

    /// Parse the string using the invariant locale.
    static bool try_from_hstring_invariant(const winrt::hstring& source, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), LOCALE_INVARIANT, value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_hstring(const winrt::hstring& source, const winrt::hstring& localeName, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), localeName.c_str(), value);
    }

    /// Parse the string using the specified locale.
    static bool try_from_hstring(const winrt::hstring& source, PCWSTR localeName, decimal& value)
    {
        return try_from_string_with_locale(source.c_str(), localeName, value);
    }
#endif // defined(WINRT_BASE_H)

public:
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
        validate(value);

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

private:
    wil::unique_bstr to_bstr_with_locale(const LCID lcid) const
    {
        wil::unique_bstr bstr;
        THROW_IF_FAILED(::VarBstrFromDec(&m_decimal, lcid, 0, wil::out_param(bstr)));
        return bstr;
    }

    wil::unique_bstr to_bstr_with_locale(PCWSTR localeName) const
    {
        return to_bstr_with_locale(to_lcid(localeName));
    }

public:
    // Format the string using the user's default locale.
    std::string to_string() const
    {
        const auto bstr{ to_bstr_with_locale(LOCALE_USER_DEFAULT) };
        return std::string{ to_narrow_string(bstr.get()).get() };
    }

    // Format the string using the invariant locale.
    std::string to_string_invariant() const
    {
        const auto bstr{ to_bstr_with_locale(LOCALE_INVARIANT) };
        return std::string{ to_narrow_string(bstr.get()).get() };
    }

    // Format the string using the specified locale.
    std::string to_string(PCSTR localeName) const
    {
        const auto bstr{ to_bstr_with_locale(to_wide_string(localeName).get()) };
        return std::string{ to_narrow_string(bstr.get()).get() };
    }

    // Format the string using the specified locale.
    std::string to_string(const std::string& localeName) const
    {
        return to_string(localeName.c_str());
    }

public:
    // Format the string using the user's default locale.
    std::wstring to_wstring() const
    {
        return std::wstring{ to_bstr_with_locale(LOCALE_USER_DEFAULT).get() };
    }

    // Format the string using the invariant locale.
    std::wstring to_wstring_invariant() const
    {
        return std::wstring{ to_bstr_with_locale(LOCALE_INVARIANT).get() };
    }

    // Format the string using the specified locale.
    std::wstring to_wstring(const std::wstring& localeName) const
    {
        return std::wstring{ to_bstr_with_locale(localeName.c_str()).get() };
    }

    // Format the string using the specified locale.
    std::wstring to_wstring(PCWSTR localeName) const
    {
        return std::wstring{ to_bstr_with_locale(localeName).get() };
    }

public:
#if defined(__hstring_h__) && defined(__WINSTRING_H_)
    HSTRING to_HSTRING() const
    {
        const auto bstr{ to_bstr_with_locale(LOCALE_USER_DEFAULT) };
        HSTRING hstring{};
        THROW_IF_FAILED(::WindowsCreateString(bstr.get(), ::SysStringLen(bstr.get()), &hstring));
        return hstring;
    }

    HSTRING to_HSTRING_invariant() const
    {
        const auto bstr{ to_bstr_with_locale(LOCALE_INVARIANT) };
        HSTRING hstring{};
        THROW_IF_FAILED(::WindowsCreateString(bstr.get(), ::SysStringLen(bstr.get()), &hstring));
        return hstring;
    }

    HSTRING to_HSTRING(const HSTRING& localeName) const
    {
        return to_HSTRING(::WindowsGetStringRawBuffer(localeName, nullptr));
    }

    HSTRING to_HSTRING(PCWSTR localeName) const
    {
        const auto bstr{ to_bstr_with_locale(localeName) };
        HSTRING hstring{};
        THROW_IF_FAILED(::WindowsCreateString(bstr.get(), ::SysStringLen(bstr.get()), &hstring));
        return hstring;
    }
#endif // defined(__hstring_h__) && defined(__WINSTRING_H_)

public:
#if defined(WINRT_BASE_H)
    winrt::hstring to_hstring() const
    {
        return winrt::hstring{ to_bstr_with_locale(LOCALE_USER_DEFAULT).get() };
    }

    winrt::hstring to_hstring_invariant() const
    {
        return winrt::hstring{ to_bstr_with_locale(LOCALE_INVARIANT).get() };
    }

    winrt::hstring to_hstring(const winrt::hstring& localeName) const
    {
        return to_hstring(localeName.c_str());
    }

    winrt::hstring to_hstring(PCWSTR localeName) const
    {
        return winrt::hstring{ to_bstr_with_locale(localeName).get() };
    }
#endif // defined(WINRT_BASE_H)

public:
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

    /// Return true if value is valid.
    static constexpr bool is_valid(const DECIMAL& value)
    {
        const BYTE sign_is_negative{ 0x80 };
        return (value.scale <= max_scale()) && ((value.sign & ~sign_is_negative) == 0);
    }

    /// Return true if this is an integral number.
    bool is_integer() const
    {
        return m_decimal.scale == 0;
    }

    /// Return true if value is an integral number.
    static constexpr bool is_integer(const DECIMAL& value)
    {
        validate(value);
        return value.scale == 0;
    }

    /// Return the scaling factor of the value (the number of decimal digits).
    /// @return the scaling factor, ranging from 0 to max_scale().
    std::uint8_t scale() const
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
    static constexpr std::uint8_t max_scale()
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
        // VarDecNeg(0) ==> -0 ("signed zero")
        // We don't support signed zero (neither do C#, Python and other languages)
        // Handle it
        if ((m_decimal.Lo64 == 0) && (m_decimal.Hi32 == 0))
        {
            // Current value is zero. Result is zero
            return *this;
        }

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

    /// Return the integral digits; any fractional digits are discarded.
    decimal truncate() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecFix(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    /// Return the integral digits rounded down to -infinity; any fractional digits are discarded.
    decimal floor() const
    {
        decimal value{};
        THROW_IF_FAILED(::VarDecInt(const_cast<DECIMAL*>(&m_decimal), &value.m_decimal));
        return value;
    }

    /// Return the integral digits rounded up to +infinity; any fractional digits are discarded.
    decimal ceil() const
    {
        // The floor(x) function returns the greatest integer less than or equal to x.
        // By negating x and applying floor(), we get the smallest integer greater than or equal to -x.
        // Negating the result gives the ceiling of x.
        // Thus math.ceil(this) == -math.floor(-this)
        return operator-().floor().operator-();
    }

    /// Return this clamped to the inclusive range of min and max.
    /// @return this if min <= this <= max, or min if this < min, or max if max < this.
    decimal clamp(decimal min, decimal max) const
    {
        if (max < min)
        {
            throw std::invalid_argument("max < min");
        }
        return *this < min ? min : (*this > max ? max : *this);
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
        //      remainder = aleft - (aright * TRUNCATE(aleft / aright) * aright)
        //      remainder = IF left < 0 THEN remainder = -remainder

        const Microsoft::Windows::Foundation::decimal aleft{ abs() };
        const Microsoft::Windows::Foundation::decimal aright{ value.abs() };
        const bool left_is_negative{ m_decimal.sign != 0 };

        const Microsoft::Windows::Foundation::decimal quotient{ aleft.abs() / aright.abs() };
        const Microsoft::Windows::Foundation::decimal truncate{ quotient.truncate() };
        const Microsoft::Windows::Foundation::decimal product{ truncate * aright };
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
    /// @throw std::invalid_argument if value is not valid.
    static constexpr void validate(const DECIMAL& value)
    {
        if (!is_valid(value))
        {
            throw std::invalid_argument("value is not valid");
        }
    }

private:
    DECIMAL m_decimal{};
};
}

#endif // !defined(__WindowsAppSDK_Microsoft_Windows_Foundation_decimal_)
