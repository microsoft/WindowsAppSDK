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

        std::unique_ptr<WCHAR[]> s{ new WCHAR[lengthIncludingNullTerminator] };

        THROW_IF_WIN32_BOOL_FALSE(MultiByteToWideChar(CP_UTF8, 0, utf8, -1, s.get(), lengthIncludingNullTerminator));
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
        auto length{ lengthIncludingNullTerminator - 1 };

        std::string utf8{};
        utf8.reserve(length);

        THROW_IF_WIN32_BOOL_FALSE(WideCharToMultiByte(CP_UTF8, 0, s, -1, const_cast<char*>(utf8.c_str()), lengthIncludingNullTerminator, nullptr, nullptr));
        return utf8;
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
