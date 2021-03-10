// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace MddCore
{
    inline winrt::hstring utf8_to_hstring(PCSTR utf8)
    {
        if (!utf8)
        {
            return winrt::hstring();
        }

        const auto lengthIncludingNullTerminator{ MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0) };
        THROW_IF_WIN32_BOOL_FALSE(lengthIncludingNullTerminator);

        std::unique_ptr<WCHAR[]> s{ std::make_unique<WCHAR[]>(lengthIncludingNullTerminator) };

        THROW_IF_WIN32_BOOL_FALSE(MultiByteToWideChar(CP_UTF8, 0, utf8, -1, s.get(), lengthIncludingNullTerminator));
        s[lengthIncludingNullTerminator - 1] = L'\0';
        return winrt::hstring(s.get());
    }

    inline std::string to_utf8(PCWSTR s)
    {
        if (!s)
        {
            return nullptr;
        }

        const auto lengthIncludingNullTerminator{ WideCharToMultiByte(CP_UTF8, 0, s, -1, nullptr, 0, nullptr, nullptr) };
        THROW_IF_WIN32_BOOL_FALSE(lengthIncludingNullTerminator);

        std::unique_ptr<char[]> utf8{ std::make_unique<char[]>(lengthIncludingNullTerminator) };

        THROW_IF_WIN32_BOOL_FALSE(WideCharToMultiByte(CP_UTF8, 0, s, -1, utf8.get(), lengthIncludingNullTerminator, nullptr, nullptr));
        utf8[lengthIncludingNullTerminator - 1] = '\0';
        return std::string(utf8.get());
    }

    inline std::string to_utf8(const std::wstring& s)
    {
        return to_utf8(s.c_str());
    }

    inline std::string to_utf8(const winrt::hstring& s)
    {
        return to_utf8(s.c_str());
    }
}
