// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace Microsoft::Windows::Storage
{
/// Allowed characters = ASCII alphanumeric, SPACE, DASH, DOT, UNDERSCORE
/// Avoid https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file
inline bool is_valid_character(const wchar_t c) noexcept
{
    return (L'0' <= c && c <= L'9') ||
           (L'A' <= c && c <= L'Z') ||
           (L'a' <= c && c <= L'z') ||
           (L' ' == c || L'-' == c || L'.' == c || L'_' == c);
}

inline PCWSTR c_prohibitedStringsEquals[24]{
    L".", L"..", L"con", L"prn", L"aux", L"nul",
    L"com1", L"com2", L"com3", L"com4", L"com5", L"com6", L"com7", L"com8", L"com9",
    L"lpt1", L"lpt2", L"lpt3", L"lpt4", L"lpt5", L"lpt6", L"lpt7", L"lpt8", L"lpt9"
};

inline PCWSTR c_prohibitedStringsStartsWith[23]{
    L"con.", L"prn.", L"aux.", L"nul.",
    L"com1.", L"com2.", L"com3.", L"com4.", L"com5.", L"com6.", L"com7.", L"com8.", L"com9.",
    L"lpt1.", L"lpt2.", L"lpt3.", L"lpt4.", L"lpt5.", L"lpt6.", L"lpt7.", L"lpt8.", L"lpt9.",
    L"xn--"
};

inline wchar_t ascii_tolower_ordinal(const wchar_t c) noexcept
{
    return (c >= L'A' && c <= L'Z') ? (c | 0x20) : c;
}

inline bool startswith_ordinal_nocase(_In_ PCWSTR string, _In_ PCWSTR prefix)
{
    for (;;)
    {
        const wchar_t pc{ *prefix++ };
        if (pc == L'\0')
        {
            // prefix fully matched
            return true;
        }

        const wchar_t sc{ *string++ };
        if (sc == 0)
        {
            // string ended before prefix so cannot match
            return false;
        }

        if (ascii_tolower_ordinal(sc) != ascii_tolower_ordinal(pc))
        {
            return false;
        }
    }
}

inline bool contains_prohibited_character(_In_ PCWSTR string)
{
    for (PCWSTR s = string; *s != L'\0'; ++s)
    {
        if (!is_valid_character(*s))
        {
            return true;
        }
    }
    return false;
}

inline bool is_prohibited_string(_In_ PCWSTR string)
{
    // Contains prohibited character(s)
    if (contains_prohibited_character(string))
    {
        return true;
    }

    // Equals a prohibited string
    for (size_t index = 0; index < ARRAYSIZE(c_prohibitedStringsEquals); ++index)
    {
        if (::CompareStringOrdinal(string, -1, c_prohibitedStringsEquals[index], -1, TRUE) == CSTR_EQUAL)
        {
            return true;
        }
    }

    // Starts with a prohibited string
    for (size_t index = 0; index < ARRAYSIZE(c_prohibitedStringsStartsWith); ++index)
    {
        if (startswith_ordinal_nocase(string, c_prohibitedStringsStartsWith[index]))
        {
            return true;
        }
    }

    return false;
}
}
