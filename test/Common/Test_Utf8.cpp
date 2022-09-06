// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace Test::Common
{
    class Utf8Tests
    {
    public:
        BEGIN_TEST_CLASS(Utf8Tests)
        END_TEST_CLASS()

        TEST_METHOD(ToUtf16_std_unique_ptr_WCHARarray_From_PCSTR)
        {
            PCSTR before{ c_string_utf8 };
            PCWSTR expectedAfter{ c_string_utf16 };

            const auto after{ Microsoft::Utf8::ToUtf16<std::unique_ptr<WCHAR[]>>(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.get(), expectedAfter), FormatComparison(after.get(), expectedAfter));
        }

        TEST_METHOD(ToUtf16_std_wstring_From_PCSTR)
        {
            PCSTR before{ c_string_utf8 };
            PCWSTR expectedAfter{ c_string_utf16 };

            const auto after{ Microsoft::Utf8::ToUtf16<std::wstring>(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.c_str(), expectedAfter), FormatComparison(after.c_str(), expectedAfter));
        }

        TEST_METHOD(ToUtf16_winrt_hstring_From_PCSTR)
        {
            PCSTR before{ c_string_utf8 };
            PCWSTR expectedAfter{ c_string_utf16 };

            const auto after{ Microsoft::Utf8::ToUtf16<winrt::hstring>(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.c_str(), expectedAfter), FormatComparison(after.c_str(), expectedAfter));
        }

        TEST_METHOD(ToUtf16_std_wstring_From_std_string)
        {
            std::string before{ c_string_utf8 };
            PCWSTR expectedAfter{ c_string_utf16 };

            const auto after{ Microsoft::Utf8::ToUtf16(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.c_str(), expectedAfter), FormatComparison(after.c_str(), expectedAfter));
        }

        TEST_METHOD(ToHString_winrt_hstring_From_PCSTR)
        {
            PCSTR before{ c_string_utf8 };
            PCWSTR expectedAfter{ c_string_utf16 };

            const auto after{ Microsoft::Utf8::ToHString(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.c_str(), expectedAfter), FormatComparison(after.c_str(), expectedAfter));
        }

        TEST_METHOD(ToUtf8_std_unique_ptr_chararray_From_PCWSTR)
        {
            PCWSTR before{ c_string_utf16 };
            PCSTR expectedAfter{ c_string_utf8 };

            const auto after{ Microsoft::Utf8::ToUtf8<std::unique_ptr<char[]>>(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.get(), expectedAfter), FormatComparison(after.get(), expectedAfter));
        }

        TEST_METHOD(ToUtf8_std_string_From_PCWSTR)
        {
            PCWSTR before{ c_string_utf16 };
            PCSTR expectedAfter{ c_string_utf8 };

            const auto after{ Microsoft::Utf8::ToUtf8<std::string>(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.c_str(), expectedAfter), FormatComparison(after.c_str(), expectedAfter));
        }

        TEST_METHOD(ToUtf8_std_string_From_std_wstring)
        {
            std::wstring before{ c_string_utf16 };
            PCSTR expectedAfter{ c_string_utf8 };

            const auto after{ Microsoft::Utf8::ToUtf8(before) };
            VERIFY_ARE_EQUAL(0, Compare(after.c_str(), expectedAfter), FormatComparison(after.c_str(), expectedAfter));
        }

    private:
        static WEX::Common::String FormatComparison(PCSTR left, PCSTR right)
        {
            return WEX::Common::String().Format(L"%hs == %hs",
                                                left ? left : "<null>",
                                                right ? right : "<null>");
        }

        static WEX::Common::String FormatComparison(PCWSTR left, PCWSTR right)
        {
            return WEX::Common::String().Format(L"%ls == %ls",
                                                left ? left : L"<null>",
                                                right ? right : L"<null>");
        }

    private:
        static inline PCSTR c_string_utf8{ "hello world" };
        static inline PCWSTR c_string_utf16{ L"hello world" };

        static int Compare(PCSTR left, PCSTR right)
        {
            if (!left)
            {
                return !right ? 0 : -1;
            }
            else if (!right)
            {
                return 1;
            }
            else
            {
                return strcmp(left, right);
            }
        }

        static int Compare(PCWSTR left, PCWSTR right)
        {
            if (!left)
            {
                return !right ? 0 : -1;
            }
            else if (!right)
            {
                return 1;
            }
            else
            {
                return CompareStringOrdinal(left, -1, right, -1, FALSE) - CSTR_EQUAL;
            }
        }
    };
}
