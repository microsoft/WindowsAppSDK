// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_TAEF_CPPWINRT_H
#define __WINDOWSAPPRUNTIME_TEST_TAEF_CPPWINRT_H

namespace WEX::TestExecution
{
    // Teach TAEF how to format a winrt::hstring
    template <>
    class VerifyOutputTraits<winrt::hstring>
    {
    public:
        static WEX::Common::NoThrowString ToString(winrt::hstring const& value)
        {
            const auto s{ value.c_str() };
            if (!s)
            {
                return WEX::Common::NoThrowString(L"nullptr");
            }
            else
            {
                return WEX::Common::NoThrowString().Format(L"\"%s\"", s);
            }
        }
    };

    // Teach TAEF how to compare a winrt::hstring
    template <>
    class VerifyCompareTraits<winrt::hstring, winrt::hstring>
    {
    public:
        static bool AreEqual(winrt::hstring const& expected, winrt::hstring const& actual)
        {
            return Compare(expected, actual) == 0;
        }

        static bool AreSame(winrt::hstring const& expected, winrt::hstring const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(winrt::hstring const& expectedLess, winrt::hstring const& expectedGreater)
        {
            return Compare(expectedLess, expectedGreater) < 0;
        }

        static bool IsGreaterThan(winrt::hstring const& expectedGreater, winrt::hstring const& expectedLess)
        {
            return Compare(expectedGreater, expectedLess) > 0;
        }

        static bool IsNull(winrt::hstring const& object)
        {
            return object.c_str() == nullptr;
        }
    private:
        static int Compare(winrt::hstring const& left, winrt::hstring const& right)
        {
            if (left == right)
            {
                return 0;
            }
            else if (left.c_str() == nullptr)
            {
                return -1;
            }
            else if (right.c_str() == nullptr)
            {
                return 1;
            }
            else
            {
                return CompareStringOrdinal(left .c_str(), -1, right.c_str(), -1, FALSE) - CSTR_EQUAL;
            }
        }
    };
}

#endif // __WINDOWSAPPRUNTIME_TEST_TAEF_CPPWINRT_H
