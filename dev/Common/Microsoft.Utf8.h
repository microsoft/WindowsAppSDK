// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSOFT_UTF8_H
#define __MICROSOFT_UTF8_H

namespace Microsoft::Utf8
{
// UTF8->UTF16 conversions
template<typename T>
T ToUtf16(PCSTR utf8);

template<> inline std::unique_ptr<WCHAR[]> ToUtf16(PCSTR utf8)
{
    if (!utf8)
    {
        return std::make_unique<WCHAR[]>(0);
    }

    const auto lengthIncludingNullTerminator{ ::MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0) };
    THROW_IF_WIN32_BOOL_FALSE(lengthIncludingNullTerminator);

    std::unique_ptr<WCHAR[]> s{ std::make_unique<WCHAR[]>(lengthIncludingNullTerminator) };

    THROW_IF_WIN32_BOOL_FALSE(::MultiByteToWideChar(CP_UTF8, 0, utf8, -1, s.get(), lengthIncludingNullTerminator));
    s[lengthIncludingNullTerminator - 1] = L'\0';
    return s;
}

template<> inline std::wstring ToUtf16(PCSTR utf8)
{
    if (!utf8)
    {
        return std::wstring();
    }

    auto s{ ToUtf16<std::unique_ptr<WCHAR[]>>(utf8) };
    return std::wstring(s.get());
}

template<> inline winrt::hstring ToUtf16(PCSTR utf8)
{
    if (!utf8)
    {
        return winrt::hstring();
    }

    auto s{ ToUtf16<std::unique_ptr<WCHAR[]>>(utf8) };
    return winrt::hstring(s.get());
}

inline std::wstring ToUtf16(const std::string& utf8)
{
    return ToUtf16<std::wstring>(utf8.c_str());
}

inline winrt::hstring ToHString(PCSTR utf8)
{
    return ToUtf16<winrt::hstring>(utf8);
}

// UTF16->UTF8 conversions
template<typename T>
T ToUtf8(PCWSTR utf16);

template<> inline std::unique_ptr<char[]> ToUtf8(PCWSTR utf16)
{
    if (!utf16)
    {
        return std::make_unique<char[]>(0);
    }

    const auto lengthIncludingNullTerminator{ ::WideCharToMultiByte(CP_UTF8, 0, utf16, -1, nullptr, 0, nullptr, nullptr) };
    THROW_IF_WIN32_BOOL_FALSE(lengthIncludingNullTerminator);

    std::unique_ptr<char[]> s{ std::make_unique<char[]>(lengthIncludingNullTerminator) };

    THROW_IF_WIN32_BOOL_FALSE(::WideCharToMultiByte(CP_UTF8, 0, utf16, -1, s.get(), lengthIncludingNullTerminator, nullptr, nullptr));
    s[lengthIncludingNullTerminator - 1] = '\0';
    return s;
}

template<> inline std::string ToUtf8(PCWSTR utf16)
{
    if (!utf16)
    {
        return std::string();
    }

    auto s{ ToUtf8<std::unique_ptr<char[]>>(utf16) };
    return std::string(s.get());
}

inline std::string ToUtf8(const std::wstring& utf16)
{
    return ToUtf8<std::string>(utf16.c_str());
}
}

#endif // __MICROSOFT_UTF8_H
