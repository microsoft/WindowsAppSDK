// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_TAEF_CPPWINRT_H
#define __WINDOWSAPPRUNTIME_TEST_TAEF_CPPWINRT_H

namespace WEX::TestExecution
{
    // Teach TAEF how to format a std::wstring
    template <>
    class VerifyOutputTraits<std::wstring>
    {
    public:
        static WEX::Common::NoThrowString ToString(std::wstring const& value)
        {
            return WEX::Common::NoThrowString().Format(L"%s", s);
        }
    };

    // Teach TAEF how to compare a std::wstring
    template <>
    class VerifyCompareTraits<std::wstring, std::wstring>
    {
    public:
        static bool AreEqual(std::wstring const& expected, std::wstring const& actual)
        {
            return Compare(expected, actual) == 0;
        }

        static bool AreSame(std::wstring const& expected, std::wstring const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(std::wstring const& expectedLess, std::wstring const& expectedGreater)
        {
            return Compare(expectedLess, expectedGreater) < 0;
        }

        static bool IsGreaterThan(std::wstring const& expectedGreater, std::wstring const& expectedLess)
        {
            return Compare(expectedGreater, expectedLess) > 0;
        }

        static bool IsNull(std::wstring const& object)
        {
            return object.c_str() == nullptr;
        }
    private:
        static int Compare(std::wstring const& left, std::wstring const& right)
        {
            return CompareStringOrdinal(left.c_str(), -1, right.c_str(), -1, FALSE) - CSTR_EQUAL;
        }
    };

    // Teach TAEF how to format a std::filesystem::path
    template <>
    class VerifyOutputTraits<std::filesystem::path>
    {
    public:
        static WEX::Common::NoThrowString ToString(std::filesystem::path const& value)
        {
            return WEX::Common::NoThrowString().Format(L"%s", s);
        }
    };

    // Teach TAEF how to compare a std::filesystem::path
    template <>
    class VerifyCompareTraits<std::filesystem::path, std::filesystem::path>
    {
    public:
        static bool AreEqual(std::filesystem::path const& expected, std::filesystem::path const& actual)
        {
            return Compare(expected, actual) == 0;
        }

        static bool AreSame(std::filesystem::path const& expected, std::filesystem::path const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(std::filesystem::path const& expectedLess, std::filesystem::path const& expectedGreater)
        {
            return Compare(expectedLess, expectedGreater) < 0;
        }

        static bool IsGreaterThan(std::filesystem::path const& expectedGreater, std::filesystem::path const& expectedLess)
        {
            return Compare(expectedGreater, expectedLess) > 0;
        }

        static bool IsNull(std::filesystem::path const& object)
        {
            return object.c_str() == nullptr;
        }
    private:
        static int Compare(std::filesystem::path const& left, std::filesystem::path const& right)
        {
            return CompareStringOrdinal(left.c_str(), -1, right.c_str(), -1, FALSE) - CSTR_EQUAL;
        }
    };
}

#endif // __WINDOWSAPPRUNTIME_TEST_TAEF_CPPWINRT_H
