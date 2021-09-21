// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Microsoft::Utf8
{
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

inline winrt::hstring ToHString(PCSTR utf8)
{
    return ToUtf16<winrt::hstring>(utf8);
}
}
