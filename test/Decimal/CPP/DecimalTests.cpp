// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <decimal.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

namespace WEX::TestExecution
{
    // Teach TAEF how to format a Microsoft::Windows::Foundation::decimal
    template <>
    class VerifyOutputTraits<Microsoft::Windows::Foundation::decimal>
    {
    public:
        static WEX::Common::NoThrowString ToString(Microsoft::Windows::Foundation::decimal const& value)
        {
            const auto s{ value.to_string() };
            return WEX::Common::NoThrowString().Format(L"\"%s\"", s.c_str());
        }
    };

    // Teach TAEF how to compare a Microsoft::Windows::Foundation::decimal
    template <>
    class VerifyCompareTraits<Microsoft::Windows::Foundation::decimal, Microsoft::Windows::Foundation::decimal>
    {
    public:
        static bool AreEqual(Microsoft::Windows::Foundation::decimal const& expected, Microsoft::Windows::Foundation::decimal const& actual)
        {
            return expected == actual;
        }

        static bool AreSame(Microsoft::Windows::Foundation::decimal const& expected, Microsoft::Windows::Foundation::decimal const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(Microsoft::Windows::Foundation::decimal const& expectedLess, Microsoft::Windows::Foundation::decimal const& expectedGreater)
        {
            return expectedLess < expectedGreater;
        }

        static bool IsGreaterThan(Microsoft::Windows::Foundation::decimal const& expectedGreater, Microsoft::Windows::Foundation::decimal const& expectedLess)
        {
            return expectedGreater > expectedLess;
        }

        static bool IsNull(Microsoft::Windows::Foundation::decimal const& /*object*/)
        {
            return false;
        }
    };
}

namespace Test::Decimal::Tests
{
    class DecimalTests
    {
    public:
        BEGIN_TEST_CLASS(DecimalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TD::DumpExecutionContext();
            ::TB::Setup(TB::Packages::Framework);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(ctor)
        {
            const std::int64_t data{};
            Microsoft::Windows::Foundation::decimal decimal;
            const auto value{ decimal.to_int64() };
            VERIFY_ARE_EQUAL(data, value);
        }

        TEST_METHOD(ctor_assign_move)
        {
            const Microsoft::Windows::Foundation::decimal data{ -1234567890 };
            const Microsoft::Windows::Foundation::decimal zero{};

            Microsoft::Windows::Foundation::decimal before{ data };
            VERIFY_ARE_EQUAL(data, before);
            const Microsoft::Windows::Foundation::decimal after = std::move(before);
            VERIFY_ARE_EQUAL(data, after);
            VERIFY_ARE_EQUAL(zero, before);
        }

        TEST_METHOD(ctor_to_assign_decimal)
        {
            const Microsoft::Windows::Foundation::decimal data{ -1234567890 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_decimal() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_decimal() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_bool)
        {
            const bool data{ true };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_bool() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_bool() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_char)
        {
            const char data{ -123 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_char() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_char() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_int16)
        {
            const std::int16_t data{ -32109};
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_int16() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_int16() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_int32)
        {
            const std::int32_t data{ -1234567890 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_int32() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_int32() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_int64)
        {
            const std::int64_t data{ -1234567890123456789 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_int64() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_int64() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_uint8)
        {
            const std::uint8_t data{ 123 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_uint8() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_uint16() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_uint16)
        {
            const std::uint16_t data{ 32109 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_uint16() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_uint16() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_uint32)
        {
            const std::uint32_t data{ 1234567890 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_uint32() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_uint32() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_uint64)
        {
            const std::uint64_t data{ 0xFEDCBA0987654321 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_uint64() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_uint64() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_float)
        {
            const float data{ -1.25 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_float() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_float() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_double)
        {
            const double data{ -1.25 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_double() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_double() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_long)
        {
            const long data{ -1234567890 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_long() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_long() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_ulong)
        {
            const unsigned long data{ 1234567890 };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_ulong() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_ulong() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_pcwstr)
        {
            PCWSTR data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_string() };
            VERIFY_ARE_EQUAL(0, wcscmp(data, to.c_str()));

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string() };
            VERIFY_ARE_EQUAL(0, wcscmp(data, to.c_str()), std::format(L"'{}' == '{}'", data, to.c_str()).c_str());
        }

        TEST_METHOD(ctor_to_assign_pcwstr_lcid)
        {
            PCWSTR data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, GetSystemDefaultLCID());
            const auto to{ object.to_string(GetSystemDefaultLCID()) };
            VERIFY_ARE_EQUAL(0, wcscmp(data, to.c_str()));

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string(GetSystemDefaultLCID()) };
            VERIFY_ARE_EQUAL(0, wcscmp(data, to.c_str()), std::format(L"'{}' == '{}'", data, to.c_str()).c_str());
        }

        TEST_METHOD(ctor_to_assign_string)
        {
            const std::wstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_string() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_system_default)
        {
            const std::wstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_SYSTEM_DEFAULT);
            const auto to{ object.to_hstring(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_user_default)
        {
            const std::wstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_USER_DEFAULT);
            const auto to{ object.to_string(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_thread)
        {
            const std::wstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, GetThreadLocale());
            const auto to{ object.to_string(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_invariant)
        {
            const std::wstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_INVARIANT);
            const auto to{ object.to_string(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to2);
        }

#if defined(__WINSTRING_H_)
        TEST_METHOD(ctor_to_assign_HSTRING)
        {
            PCWSTR rawData{ L"-12.345" };
            const HSTRING data{};
            VERIFY_SUCCEEDED(WindowsCreateString(rawData, wcslen(rawData), wil::out_param(data)));
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_HSTRING() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_HSTRING() };
            VERIFY_ARE_EQUAL(data, to2);

            WindowsDeleteString(data);
            WindowsDeleteString(to);
            WindowsDeleteString(to2);
        }
#endif // defined(__WINSTRING_H_)

#if defined(__WINSTRING_H_)
        TEST_METHOD(ctor_to_assign_HSTRING_lcid_system_default)
        {
            PCWSTR rawData{ L"-12.345" };
            const HSTRING data{};
            VERIFY_SUCCEEDED(WindowsCreateString(rawData, wcslen(rawData), wil::out_param(data)));
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_SYSTEM_DEFAULT);
            const auto to{ object.to_HSTRING(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_HSTRING(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);

            WindowsDeleteString(data);
            WindowsDeleteString(to);
            WindowsDeleteString(to2);
        }
#endif // defined(__WINSTRING_H_)

#if defined(__WINSTRING_H_)
        TEST_METHOD(ctor_to_assign_HSTRING_lcid_user_default)
        {
            PCWSTR rawData{ L"-12.345" };
            const HSTRING data{};
            VERIFY_SUCCEEDED(WindowsCreateString(rawData, wcslen(rawData), wil::out_param(data)));
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_USER_DEFAULT);
            const auto to{ object.to_HSTRING(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_HSTRING(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);

            WindowsDeleteString(data);
            WindowsDeleteString(to);
            WindowsDeleteString(to2);
        }
#endif // defined(__WINSTRING_H_)

#if defined(__WINSTRING_H_)
        TEST_METHOD(ctor_to_assign_HSTRING_lcid_thread)
        {
            PCWSTR rawData{ L"-12.345" };
            const HSTRING data{};
            VERIFY_SUCCEEDED(WindowsCreateString(rawData, wcslen(rawData), wil::out_param(data)));
            const Microsoft::Windows::Foundation::decimal object(data, GetThreadLocale());
            const auto to{ object.to_HSTRING(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_HSTRING(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to2);

            WindowsDeleteString(data);
            WindowsDeleteString(to);
            WindowsDeleteString(to2);
        }
#endif // defined(__WINSTRING_H_)

#if defined(__WINSTRING_H_)
        TEST_METHOD(ctor_to_assign_HSTRING_lcid_invariant)
        {
            PCWSTR rawData{ L"-12.345" };
            const HSTRING data{};
            VERIFY_SUCCEEDED(WindowsCreateString(rawData, wcslen(rawData), wil::out_param(data)));
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_INVARIANT);
            const auto to{ object.to_HSTRING(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_HSTRING(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to2);

            WindowsDeleteString(data);
            WindowsDeleteString(to);
            WindowsDeleteString(to2);
        }
#endif // defined(__WINSTRING_H_)

#if defined(WINRT_BASE_H)
        TEST_METHOD(ctor_to_assign_hstring)
        {
            const winrt::hstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object{ data };
            const auto to{ object.to_hstring() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring() };
            VERIFY_ARE_EQUAL(data, to2);
        }
#endif // defined(WINRT_BASE_H)

#if defined(WINRT_BASE_H)
        TEST_METHOD(ctor_to_assign_hstring_lcid_system_default)
        {
            const winrt::hstring data{ L"-12.345" };
            const ::Microsoft::Windows::Foundation::decimal object(data, LOCALE_SYSTEM_DEFAULT);
            const auto to{ object.to_hstring(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);
        }
#endif // defined(WINRT_BASE_H)

#if defined(WINRT_BASE_H)
        TEST_METHOD(ctor_to_assign_hstring_lcid_user_default)
        {
            const winrt::hstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_USER_DEFAULT);
            const auto to{ object.to_hstring(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);
        }
#endif // defined(WINRT_BASE_H)

#if defined(WINRT_BASE_H)
        TEST_METHOD(ctor_to_assign_hstring_lcid_thread)
        {
            const winrt::hstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, GetThreadLocale());
            const auto to{ object.to_hstring(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to2);
        }
#endif // defined(WINRT_BASE_H)

#if defined(WINRT_BASE_H)
        TEST_METHOD(ctor_to_assign_hstring_lcid_invariant)
        {
            const winrt::hstring data{ L"-12.345" };
            const Microsoft::Windows::Foundation::decimal object(data, LOCALE_INVARIANT);
            const auto to{ object.to_hstring(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to2);
        }
#endif // defined(WINRT_BASE_H)

        TEST_METHOD(compare_bool)
        {
            const Microsoft::Windows::Foundation::decimal decimal_false(false);
            const Microsoft::Windows::Foundation::decimal decimal_true(true);
            VERIFY_ARE_EQUAL(0, decimal_false.compare(decimal_false));
            VERIFY_ARE_EQUAL(0, decimal_true.compare(decimal_true));
            VERIFY_ARE_EQUAL(-1, decimal_false.compare(decimal_true));
            VERIFY_ARE_EQUAL(1, decimal_true.compare(decimal_false));

            VERIFY_IS_TRUE(decimal_true == decimal_true);
            VERIFY_IS_FALSE(decimal_true != decimal_true);
            VERIFY_IS_FALSE(decimal_true < decimal_true);
            VERIFY_IS_TRUE(decimal_true <= decimal_true);
            VERIFY_IS_FALSE(decimal_true > decimal_true);
            VERIFY_IS_TRUE(decimal_true >= decimal_true);
        }

        TEST_METHOD(compare_char)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<char>(-123));
            const Microsoft::Windows::Foundation::decimal right(static_cast<char>(123));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_int16)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<std::int16_t>(-32109));
            const Microsoft::Windows::Foundation::decimal right(static_cast<std::int16_t>(32109));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_int32)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<std::int32_t>(-1234567890));
            const Microsoft::Windows::Foundation::decimal right(static_cast<std::int32_t>(1234567890));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_int64)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<std::int64_t>(-1234567890123456789));
            const Microsoft::Windows::Foundation::decimal right(static_cast<std::int64_t>(1234567890123456789));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_uint8)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<std::uint8_t>(123));
            const Microsoft::Windows::Foundation::decimal right(static_cast<std::uint8_t>(234));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_uint16)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<std::uint16_t>(32109));
            const Microsoft::Windows::Foundation::decimal right(static_cast<std::uint16_t>(65432));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_uint32)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<std::uint32_t>(1234567890));
            const Microsoft::Windows::Foundation::decimal right(static_cast<std::uint32_t>(4019283756));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_uint64)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<std::uint64_t>(0x1234567890ABCDEF));
            const Microsoft::Windows::Foundation::decimal right(static_cast<std::uint64_t>(0xFEDCBA0987654321));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_float)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<float>(-1.25));
            const Microsoft::Windows::Foundation::decimal right(static_cast<float>(1.25));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_double)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<double>(-1.25));
            const Microsoft::Windows::Foundation::decimal right(static_cast<double>(1.25));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_long)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<long>(-1234567890));
            const Microsoft::Windows::Foundation::decimal right(static_cast<long>(1234567890));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_ulong)
        {
            const Microsoft::Windows::Foundation::decimal left(static_cast<unsigned long>(1234567890));
            const Microsoft::Windows::Foundation::decimal right(static_cast<unsigned long>(4019283756));
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_string)
        {
            const Microsoft::Windows::Foundation::decimal left(L"-12.345");
            const Microsoft::Windows::Foundation::decimal right(L"12.345");
            VERIFY_ARE_EQUAL(0, left.compare(left));
            VERIFY_ARE_EQUAL(0, right.compare(right));
            VERIFY_ARE_EQUAL(-1, left.compare(right));
            VERIFY_ARE_EQUAL(1, right.compare(left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(compare_decimal)
        {
            const Microsoft::Windows::Foundation::decimal leftDecimal{ L"-12.345" };
            const DECIMAL left{ leftDecimal.to_decimal() };
            const Microsoft::Windows::Foundation::decimal rightDecimal{ L"12.345" };
            const DECIMAL right{ rightDecimal.to_decimal() };
            VERIFY_ARE_EQUAL(0, leftDecimal.compare(left));
            VERIFY_ARE_EQUAL(0, rightDecimal.compare(right));
            VERIFY_ARE_EQUAL(-1, leftDecimal.compare(right));
            VERIFY_ARE_EQUAL(1, rightDecimal.compare(left));

            VERIFY_ARE_EQUAL(0, compare(left, left));
            VERIFY_ARE_EQUAL(0, compare(right, right));
            VERIFY_ARE_EQUAL(-1, compare(left, right));
            VERIFY_ARE_EQUAL(1, compare(right, left));

            VERIFY_IS_TRUE(left == left);
            VERIFY_IS_FALSE(left != left);
            VERIFY_IS_FALSE(left < left);
            VERIFY_IS_TRUE(left <= left);
            VERIFY_IS_FALSE(left > left);
            VERIFY_IS_TRUE(left >= left);

            VERIFY_IS_TRUE(right == right);
            VERIFY_IS_FALSE(right != right);
            VERIFY_IS_FALSE(right < right);
            VERIFY_IS_TRUE(right <= right);
            VERIFY_IS_FALSE(right > right);
            VERIFY_IS_TRUE(right >= right);

            VERIFY_IS_FALSE(left == right);
            VERIFY_IS_TRUE(left != right);
            VERIFY_IS_TRUE(left < right);
            VERIFY_IS_TRUE(left <= right);
            VERIFY_IS_FALSE(left > right);
            VERIFY_IS_FALSE(left >= right);

            VERIFY_IS_FALSE(right == left);
            VERIFY_IS_TRUE(right != left);
            VERIFY_IS_FALSE(right < left);
            VERIFY_IS_FALSE(right <= left);
            VERIFY_IS_TRUE(right > left);
            VERIFY_IS_TRUE(right >= left);
        }

        TEST_METHOD(operator_pos)
        {
            const Microsoft::Windows::Foundation::decimal zero(L"0");
            const Microsoft::Windows::Foundation::decimal pos(L"12.345");
            const Microsoft::Windows::Foundation::decimal neg(L"-12.345");

            const auto zero_value{ +zero };
            VERIFY_IS_TRUE(zero_value == zero);
            VERIFY_IS_TRUE(zero_value != pos);
            VERIFY_IS_TRUE(zero_value != neg);
            VERIFY_IS_TRUE(zero_value < pos);
            VERIFY_IS_TRUE(zero_value > neg);

            const auto pos_value{ +pos };
            VERIFY_IS_TRUE(pos_value != zero);
            VERIFY_IS_TRUE(pos_value == pos);
            VERIFY_IS_TRUE(pos_value != neg);
            VERIFY_IS_TRUE(pos_value > zero);
            VERIFY_IS_TRUE(pos_value > neg);

            const auto neg_value{ +neg };
            VERIFY_IS_TRUE(neg_value != zero);
            VERIFY_IS_TRUE(neg_value != pos);
            VERIFY_IS_TRUE(neg_value == neg);
            VERIFY_IS_TRUE(neg_value < zero);
            VERIFY_IS_TRUE(neg_value < pos);
        }

        TEST_METHOD(is_valid)
        {
            // Scale = 0 to 28
            DECIMAL value{};
            VERIFY_IS_TRUE(Microsoft::Windows::Foundation::decimal::is_valid(value));

            for (BYTE scale=0; scale <= Microsoft::Windows::Foundation::decimal::max_scale(); ++scale)
            {
                value.scale = scale;
                VERIFY_IS_TRUE(Microsoft::Windows::Foundation::decimal::is_valid(value));
            }

            value.scale = static_cast<BYTE>(Microsoft::Windows::Foundation::decimal::max_scale() + 1);
            VERIFY_IS_FALSE(Microsoft::Windows::Foundation::decimal::is_valid(value));

            // Sign is 0x00 or 0x80
            value = DECIMAL{};
            const BYTE sign_is_negative{ 0x80 };
            value.sign = sign_is_negative;
            VERIFY_IS_TRUE(Microsoft::Windows::Foundation::decimal::is_valid(value));

            for (BYTE sign=0x01; sign < sign_is_negative; sign <<= 1)
            {
                value.sign = sign;
                VERIFY_IS_FALSE(Microsoft::Windows::Foundation::decimal::is_valid(value), WEX::Common::String().Format(L"sign=0x%02X", static_cast<std::uint32_t>(value.sign)));
            }
        }

        TEST_METHOD(scale)
        {
            const Microsoft::Windows::Foundation::decimal n_0{ L"79228162514264337593543950335" };
            VERIFY_ARE_EQUAL(0u, n_0.scale());

            const Microsoft::Windows::Foundation::decimal n_1{ L"7922816251426433759354395033.5" };
            VERIFY_ARE_EQUAL(1u, n_1.scale());

            const Microsoft::Windows::Foundation::decimal n_2{ L"792281625142643375935439503.35" };
            VERIFY_ARE_EQUAL(2u, n_2.scale());

            const Microsoft::Windows::Foundation::decimal n_27{ L"79.228162514264337593543950335" };
            VERIFY_ARE_EQUAL(27u, n_27.scale());

            const Microsoft::Windows::Foundation::decimal n_28{ L"7.9228162514264337593543950335" };
            VERIFY_ARE_EQUAL(28u, n_28.scale());

            const Microsoft::Windows::Foundation::decimal neg_n_0{ L"-79228162514264337593543950335" };
            VERIFY_ARE_EQUAL(0u, neg_n_0.scale());

            const Microsoft::Windows::Foundation::decimal neg_n_1{ L"-7922816251426433759354395033.5" };
            VERIFY_ARE_EQUAL(1u, neg_n_1.scale());

            const Microsoft::Windows::Foundation::decimal neg_n_2{ L"-792281625142643375935439503.35" };
            VERIFY_ARE_EQUAL(2u, neg_n_2.scale());

            const Microsoft::Windows::Foundation::decimal neg_n_27{ L"-79.228162514264337593543950335" };
            VERIFY_ARE_EQUAL(27u, neg_n_27.scale());

            const Microsoft::Windows::Foundation::decimal neg_n_28{ L"-7.9228162514264337593543950335" };
            VERIFY_ARE_EQUAL(28u, neg_n_28.scale());
        }

        TEST_METHOD(sign)
        {
            const Microsoft::Windows::Foundation::decimal zero(L"0");
            VERIFY_ARE_EQUAL(0, zero.sign());

            const Microsoft::Windows::Foundation::decimal neg_zero(L"-0");
            VERIFY_ARE_EQUAL(0, neg_zero.sign());
            VERIFY_ARE_EQUAL(zero, neg_zero);

            const Microsoft::Windows::Foundation::decimal pos(L"12.345");
            VERIFY_ARE_EQUAL(1, pos.sign());

            const Microsoft::Windows::Foundation::decimal neg(L"-12.345");
            VERIFY_ARE_EQUAL(-1, neg.sign());
        }

        TEST_METHOD(min_max)
        {
            VERIFY_ARE_EQUAL(28u, Microsoft::Windows::Foundation::decimal::max_scale());

            const Microsoft::Windows::Foundation::decimal max_decimal(L"79228162514264337593543950335");
            VERIFY_ARE_EQUAL(max_decimal, Microsoft::Windows::Foundation::decimal::max_value());

            const Microsoft::Windows::Foundation::decimal min_decimal(L"-79228162514264337593543950335");
            VERIFY_ARE_EQUAL(min_decimal, Microsoft::Windows::Foundation::decimal::min_value());
        }

        TEST_METHOD(operator_neg)
        {
            const Microsoft::Windows::Foundation::decimal zero(L"0");
            const Microsoft::Windows::Foundation::decimal pos(L"12.345");
            const Microsoft::Windows::Foundation::decimal neg(L"-12.345");

            const auto zero_value{ -zero };
            VERIFY_IS_TRUE(zero_value == zero);
            VERIFY_IS_TRUE(zero_value != pos);
            VERIFY_IS_TRUE(zero_value != neg);
            VERIFY_IS_TRUE(zero_value < pos);
            VERIFY_IS_TRUE(zero_value > neg);

            const auto pos_value{ -neg };
            VERIFY_IS_TRUE(pos_value != zero);
            VERIFY_IS_TRUE(pos_value == pos);
            VERIFY_IS_TRUE(pos_value != neg);
            VERIFY_IS_TRUE(pos_value > zero);
            VERIFY_IS_TRUE(pos_value > neg);

            const auto neg_value{ -pos };
            VERIFY_IS_TRUE(neg_value != zero);
            VERIFY_IS_TRUE(neg_value != pos);
            VERIFY_IS_TRUE(neg_value == neg);
            VERIFY_IS_TRUE(neg_value < zero);
            VERIFY_IS_TRUE(neg_value < pos);
        }

        TEST_METHOD(abs)
        {
            const Microsoft::Windows::Foundation::decimal zero(L"0");
            const Microsoft::Windows::Foundation::decimal pos(L"12.345");
            const Microsoft::Windows::Foundation::decimal neg(L"-12.345");

            const auto zero_value{ zero.abs() };
            VERIFY_IS_TRUE(zero_value == zero);
            VERIFY_IS_TRUE(zero_value != pos);
            VERIFY_IS_TRUE(zero_value != neg);
            VERIFY_IS_TRUE(zero_value < pos);
            VERIFY_IS_TRUE(zero_value > neg);

            const auto pos_value{ pos.abs() };
            VERIFY_IS_TRUE(pos_value != zero);
            VERIFY_IS_TRUE(pos_value == pos);
            VERIFY_IS_TRUE(pos_value != neg);
            VERIFY_IS_TRUE(pos_value > zero);
            VERIFY_IS_TRUE(pos_value > neg);

            const auto neg_value{ neg.abs() };
            VERIFY_IS_TRUE(neg_value != zero);
            VERIFY_IS_TRUE(neg_value == pos);
            VERIFY_IS_TRUE(neg_value != neg);
            VERIFY_IS_TRUE(neg_value > zero);
            VERIFY_IS_TRUE(neg_value == pos);
        }

        TEST_METHOD(truncate)
        {
            const Microsoft::Windows::Foundation::decimal zero(L"0");
            const auto value{ zero.truncate() };
            VERIFY_IS_TRUE(value == zero);

            const Microsoft::Windows::Foundation::decimal pos(L"12.345");
            const Microsoft::Windows::Foundation::decimal pos_fix(L"12");
            const auto pos_value{ pos.truncate() };
            VERIFY_IS_TRUE(pos_value == pos_fix);

            const Microsoft::Windows::Foundation::decimal neg(L"-12.345");
            const Microsoft::Windows::Foundation::decimal neg_fix(L"-12");
            const auto neg_value{ neg.truncate() };
            VERIFY_IS_TRUE(neg_value == neg_fix);
        }

        TEST_METHOD(floor)
        {
            const Microsoft::Windows::Foundation::decimal zero(L"0");
            const auto value{ zero.floor() };
            VERIFY_IS_TRUE(value == zero);

            const Microsoft::Windows::Foundation::decimal pos(L"12.345");
            const Microsoft::Windows::Foundation::decimal pos_integer(L"12");
            const auto pos_value{ pos.floor() };
            VERIFY_IS_TRUE(pos_value == pos_integer);

            const Microsoft::Windows::Foundation::decimal neg(L"-12.345");
            const Microsoft::Windows::Foundation::decimal neg_integer(L"-13");
            const auto neg_value{ neg.floor() };
            VERIFY_IS_TRUE(neg_value == neg_integer);
        }

        TEST_METHOD(ceil)
        {
            const Microsoft::Windows::Foundation::decimal zero(L"0");
            const auto value{ zero.ceil() };
            VERIFY_IS_TRUE(value == zero);

            const Microsoft::Windows::Foundation::decimal pos(L"12.345");
            const Microsoft::Windows::Foundation::decimal pos_integer(L"13");
            const auto pos_value{ pos.ceil() };
            VERIFY_IS_TRUE(pos_value == pos_integer);

            const Microsoft::Windows::Foundation::decimal neg(L"-12.345");
            const Microsoft::Windows::Foundation::decimal neg_integer(L"-12");
            const auto neg_value{ neg.ceil() };
            VERIFY_IS_TRUE(neg_value == neg_integer);
        }

        TEST_METHOD(clamp)
        {
            const Microsoft::Windows::Foundation::decimal n1{ 1 };
            const Microsoft::Windows::Foundation::decimal n2{ 2 };
            const Microsoft::Windows::Foundation::decimal n3{ 3 };

            try
            {
                const auto value_n1{ n1.clamp(n3, n2) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (std::invalid_argument& e)
            {
                VERIFY_ARE_EQUAL(WEX::Common::String(L"max < min"), WEX::Common::String().Format(L"%hs", e.what()));
            }

            const auto value_n1{ n1.clamp(n2, n3) };
            VERIFY_IS_TRUE(value_n1 == n2);

            const auto value_n2{ n2.clamp(n1, n3) };
            VERIFY_IS_TRUE(value_n2 == n2);

            const auto value_n3{ n3.clamp(n1, n2) };
            VERIFY_IS_TRUE(value_n3 == n2);
        }

        TEST_METHOD(operator_increment)
        {
            struct values
            {
                PCWSTR left;
                PCWSTR result;
            } values[]{
                { L"0",                     L"1"                     },
                { L"1",                     L"2"                     },
                { L"123",                   L"124"                   },
                { L"255",                   L"256"                   },
                { L"65535",                 L"65536"                 },
                { L"1234567890",            L"1234567891"            },
                { L"91028374659102837465",  L"91028374659102837466"  },
                { L"-0",                    L"1"                     },
                { L"-1",                    L"0"                     },
                { L"-123",                  L"-122"                  },
                { L"-255",                  L"-254"                  },
                { L"-65535",                L"-65534"                },
                { L"-1234567890",           L"-1234567889"           },
                { L"-91028374659102837465", L"-91028374659102837464" },
                { L"1.2",                   L"2.2"                   },
                { L"-1.2",                  L"-0.2"                  },
                { L".2",                    L"1.2"                   },
                { L"-.2",                   L"0.8"                   }
            };
            for (size_t index=0; index < ARRAYSIZE(values); ++index)
            {
                const auto& value{ values[index] };
                const Microsoft::Windows::Foundation::decimal before { value.left };
                Microsoft::Windows::Foundation::decimal expected{ value.result };
                {
                    Microsoft::Windows::Foundation::decimal left{ before };
                    const Microsoft::Windows::Foundation::decimal returned{ ++left };
                    VERIFY_ARE_EQUAL(returned, left, WEX::Common::String().Format(L"++%s value = %s vs %s",
                        before.to_string().c_str(), left.to_string().c_str(), expected.to_string().c_str()));
                    VERIFY_ARE_EQUAL(expected, left, WEX::Common::String().Format(L"++%s return = %s vs %s",
                        before.to_string().c_str(), returned.to_string().c_str(), expected.to_string().c_str()));
                }
                {
                    Microsoft::Windows::Foundation::decimal left{ before };
                    const Microsoft::Windows::Foundation::decimal returned{ left++ };
                    VERIFY_ARE_NOT_EQUAL(returned, left, WEX::Common::String().Format(L"%s++ value = %s vs %s",
                        before.to_string().c_str(), left.to_string().c_str(), expected.to_string().c_str()));
                    VERIFY_ARE_EQUAL(expected, left, WEX::Common::String().Format(L"%s++ return = %s vs %s",
                        before.to_string().c_str(), returned.to_string().c_str(), expected.to_string().c_str()));
                }
            }
        }

        TEST_METHOD(operator_decrement)
        {
            struct values
            {
                PCWSTR left;
                PCWSTR result;
            } values[]{
                { L"0",                     L"-1"                    },
                { L"1",                     L"0"                     },
                { L"123",                   L"122"                   },
                { L"255",                   L"254"                   },
                { L"65535",                 L"65534"                 },
                { L"1234567890",            L"1234567889"            },
                { L"91028374659102837465",  L"91028374659102837464"  },
                { L"-0",                    L"-1"                    },
                { L"-1",                    L"-2"                    },
                { L"-123",                  L"-124"                  },
                { L"-255",                  L"-256"                  },
                { L"-65535",                L"-65536"                },
                { L"-1234567890",           L"-1234567891"           },
                { L"-91028374659102837465", L"-91028374659102837466" },
                { L"1.2",                   L"0.2"                   },
                { L"-1.2",                  L"-2.2"                  },
                { L".2",                    L"-0.8"                  },
                { L"-.2",                   L"-1.2"                  }
            };
            for (size_t index=0; index < ARRAYSIZE(values); --index)
            {
                const auto& value{ values[index] };
                const Microsoft::Windows::Foundation::decimal before { value.left };
                Microsoft::Windows::Foundation::decimal expected{ value.result };
                {
                    Microsoft::Windows::Foundation::decimal left{ before };
                    const Microsoft::Windows::Foundation::decimal returned{ --left };
                    VERIFY_ARE_EQUAL(returned, left, WEX::Common::String().Format(L"--%s value = %s vs %s",
                        before.to_string().c_str(), left.to_string().c_str(), expected.to_string().c_str()));
                    VERIFY_ARE_EQUAL(expected, left, WEX::Common::String().Format(L"--%s return = %s vs %s",
                        before.to_string().c_str(), returned.to_string().c_str(), expected.to_string().c_str()));
                }
                {
                    Microsoft::Windows::Foundation::decimal left{ before };
                    const Microsoft::Windows::Foundation::decimal returned{ left-- };
                    VERIFY_ARE_NOT_EQUAL(returned, left, WEX::Common::String().Format(L"%s-- value = %s vs %s",
                        before.to_string().c_str(), left.to_string().c_str(), expected.to_string().c_str()));
                    VERIFY_ARE_EQUAL(expected, left, WEX::Common::String().Format(L"%s-- return = %s vs %s",
                        before.to_string().c_str(), returned.to_string().c_str(), expected.to_string().c_str()));
                }
            }
        }

        TEST_METHOD(operator_add)
        {
            struct values
            {
                PCWSTR left;
                PCWSTR right;
                PCWSTR result;
            } values[]{
                { L"0",         L"0",       L"0"     },
                { L"1",         L"2",       L"3"     },
                { L"123",       L"4567",    L"4690"  },
                { L"1",         L"-2",      L"-1"    },
                { L"-1",        L"-2",      L"-3"    },
                { L"-1",        L"2",       L"1"     },
                { L"-0",        L"-0",      L"0"     },
                { L"-0",        L"0",       L"0"     },
                { L"0",         L"-0",      L"0"     },
                { L"1.2",       L"3.45",    L"4.65"  },
                { L"-1.2",      L"3.45",    L"2.25"  },
                { L"1.2",       L"-3.45",   L"-2.25" },
                { L"-1.2",      L"-3.45",   L"-4.65" },
                { L".2",        L".45",     L".65"   },
                { L"-.2",       L".45",     L".25"   },
                { L".2",        L"-.45",    L"-.25"  },
                { L"-.2",       L"-.45",    L"-.65"  }
            };
            for (size_t index=0; index < ARRAYSIZE(values); ++index)
            {
                const auto& value{ values[index] };
                const Microsoft::Windows::Foundation::decimal left{ value.left };
                const Microsoft::Windows::Foundation::decimal right{ value.right };
                const Microsoft::Windows::Foundation::decimal expected{ value.result };
                const Microsoft::Windows::Foundation::decimal result{ left + right };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s + %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result.to_string().c_str(), expected.to_string().c_str()));

                Microsoft::Windows::Foundation::decimal result2{ left };
                result2 += right;
                VERIFY_ARE_EQUAL(expected, result2, WEX::Common::String().Format(L"%s += %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result2.to_string().c_str(), expected.to_string().c_str()));
            }
        }

        TEST_METHOD(operator_subtract)
        {
            struct values
            {
                PCWSTR left;
                PCWSTR right;
                PCWSTR result;
            } values[]{
                { L"0",         L"0",       L"0"     },
                { L"1",         L"2",       L"-1"    },
                { L"123",       L"4567",    L"-4444" },
                { L"1",         L"-2",      L"3"     },
                { L"-1",        L"-2",      L"1"     },
                { L"-1",        L"2",       L"-3"    },
                { L"-0",        L"-0",      L"0"     },
                { L"-0",        L"0",       L"0"     },
                { L"0",         L"-0",      L"0"     },
                { L"1.2",       L"3.45",    L"-2.25" },
                { L"-1.2",      L"3.45",    L"-4.65" },
                { L"1.2",       L"-3.45",   L"4.65"  },
                { L"-1.2",      L"-3.45",   L"2.25"  },
                { L".2",        L".45",     L"-.25"  },
                { L"-.2",       L".45",     L"-.65"  },
                { L".2",        L"-.45",    L".65"   },
                { L"-.2",       L"-.45",    L".25"   }
            };
            for (size_t index=0; index < ARRAYSIZE(values); ++index)
            {
                const auto& value{ values[index] };
                const Microsoft::Windows::Foundation::decimal left{ value.left };
                const Microsoft::Windows::Foundation::decimal right{ value.right };
                const Microsoft::Windows::Foundation::decimal expected{ value.result };
                const Microsoft::Windows::Foundation::decimal result{ left - right };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s - %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result.to_string().c_str(), expected.to_string().c_str()));

                Microsoft::Windows::Foundation::decimal result2{ left };
                result2 -= right;
                VERIFY_ARE_EQUAL(expected, result2, WEX::Common::String().Format(L"%s -= %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result2.to_string().c_str(), expected.to_string().c_str()));
            }
        }

        TEST_METHOD(operator_multiply)
        {
            struct values
            {
                PCWSTR left;
                PCWSTR right;
                PCWSTR result;
            } values[]{
                { L"0",         L"0",       L"0"      },
                { L"1",         L"2",       L"2"      },
                { L"123",       L"4567",    L"561741" },
                { L"1",         L"-2",      L"-2"     },
                { L"-1",        L"-2",      L"2"      },
                { L"-1",        L"2",       L"-2"     },
                { L"-0",        L"-0",      L"0"      },
                { L"-0",        L"0",       L"0"      },
                { L"0",         L"-0",      L"0"      },
                { L"1.2",       L"3.45",    L"4.140"  },
                { L"-1.2",      L"3.45",    L"-4.140" },
                { L"1.2",       L"-3.45",   L"-4.140" },
                { L"-1.2",      L"-3.45",   L"4.140"  },
                { L".2",        L".45",     L"0.090"  },
                { L"-.2",       L".45",     L"-0.090" },
                { L".2",        L"-.45",    L"-0.090" },
                { L"-.2",       L"-.45",    L"0.090"  }
            };
            for (size_t index=0; index < ARRAYSIZE(values); ++index)
            {
                const auto& value{ values[index] };
                const Microsoft::Windows::Foundation::decimal left{ value.left };
                const Microsoft::Windows::Foundation::decimal right{ value.right };
                const Microsoft::Windows::Foundation::decimal expected{ value.result };
                const Microsoft::Windows::Foundation::decimal result{ left * right };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s * %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result.to_string().c_str(), expected.to_string().c_str()));

                Microsoft::Windows::Foundation::decimal result2{ left };
                result2 *= right;
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s *= %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result2.to_string().c_str(), expected.to_string().c_str()));
            }
        }

        TEST_METHOD(operator_divide)
        {
            try
            {
                Microsoft::Windows::Foundation::decimal data{ 123 };
                Microsoft::Windows::Foundation::decimal zero{};
                const auto result{ data / zero };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (wil::ResultException& e)
            {
                VERIFY_ARE_EQUAL(DISP_E_DIVBYZERO, e.GetErrorCode(), WEX::Common::String().Format(L"0x%X %hs", e.GetErrorCode(), e.what()));
            }

            struct values
            {
                PCWSTR left;
                PCWSTR right;
                PCWSTR result;
            } values[]{
                { L"1",         L"2",       L"0.5"                             },
                { L"123",       L"4567",    L"0.0269323407050580249616816291"  },
                { L"1",         L"-2",      L"-0.5"                            },
                { L"-1",        L"-2",      L"0.5"                             },
                { L"-1",        L"2",       L"-0.5"                            },
                { L"1.2",       L"3.45",    L"0.3478260869565217391304347826"  },
                { L"-1.2",      L"3.45",    L"-0.3478260869565217391304347826" },
                { L"1.2",       L"-3.45",   L"-0.3478260869565217391304347826" },
                { L"-1.2",      L"-3.45",   L"0.3478260869565217391304347826"  },
                { L".2",        L".45",     L"0.4444444444444444444444444444"  },
                { L"-.2",       L".45",     L"-0.4444444444444444444444444444" },
                { L".2",        L"-.45",    L"-0.4444444444444444444444444444" },
                { L"-.2",       L"-.45",    L"0.4444444444444444444444444444"  }
            };
            for (size_t index=0; index < ARRAYSIZE(values); ++index)
            {
                const auto& value{ values[index] };
                const Microsoft::Windows::Foundation::decimal left{ value.left };
                const Microsoft::Windows::Foundation::decimal right{ value.right };
                const Microsoft::Windows::Foundation::decimal expected{ value.result };
                const Microsoft::Windows::Foundation::decimal result{ left / right };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s / %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result.to_string().c_str(), expected.to_string().c_str()));

                Microsoft::Windows::Foundation::decimal result2{ left };
                result2 /= right;
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s /= %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result2.to_string().c_str(), expected.to_string().c_str()));
            }
        }

        TEST_METHOD(operator_mod)
        {
            try
            {
                const Microsoft::Windows::Foundation::decimal data{ 123 };
                const Microsoft::Windows::Foundation::decimal zero{};
                const auto result{ data % zero };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (wil::ResultException& e)
            {
                VERIFY_ARE_EQUAL(DISP_E_DIVBYZERO, e.GetErrorCode(), WEX::Common::String().Format(L"0x%X %hs", e.GetErrorCode(), e.what()));
            }

            struct values
            {
                PCWSTR left;
                PCWSTR right;
                PCWSTR result;
            } values[]{
                { L"1",     L"2",       L"1"     },
                { L"123",   L"4567",    L"123"   },
                { L"1",     L"-2",      L"1"     },
                { L"-1",    L"-2",      L"-1"    },
                { L"-1",    L"2",       L"-1"    },
                { L"1.2",   L"3.45",    L"1.2"   },
                { L"-1.2",  L"3.45",    L"-1.2"  },
                { L"1.2",   L"-3.45",   L"1.2"   },
                { L"-1.2",  L"-3.45",   L"-1.2"  },
                { L".2",    L".45",     L"0.2"   },
                { L"-.2",   L".45",     L"-0.2"  },
                { L".2",    L"-.45",    L"0.2"   },
                { L"-.2",   L"-.45",    L"-0.2"  },

                { L"2",     L"1",       L"0"     },
                { L"4567",  L"123",     L"16"    },
                { L"3.45",  L"1.2",     L"1.05"  },
                { L"2",     L"-1",      L"0"     },
                { L"-2",    L"1",       L"0"     },
                { L"-2",    L"-1",      L"0"     },
                { L"3.45",  L"-1.2",    L"1.05"  },
                { L"-3.45", L"1.2",     L"-1.05" },
                { L"-3.45", L"-1.2",    L"-1.05" },
                { L".45",   L".2",      L"0.05"  },
                { L".45",   L"-.2",     L"0.05"  },
                { L"-.45",  L".2",      L"-0.05" },
                { L"-.45",  L"-.2",     L"-0.05" }
            };
            for (size_t index=0; index < ARRAYSIZE(values); ++index)
            {
                const auto& value{ values[index] };
                const Microsoft::Windows::Foundation::decimal left{ value.left };
                const Microsoft::Windows::Foundation::decimal right{ value.right };
                const Microsoft::Windows::Foundation::decimal expected{ value.result };
                const Microsoft::Windows::Foundation::decimal result{ left % right };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s %% %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result.to_string().c_str(), expected.to_string().c_str()));

                Microsoft::Windows::Foundation::decimal result2{ left };
                result2 %= right;
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s %%= %s = %s vs %s",
                    left.to_string().c_str(), right.to_string().c_str(), result2.to_string().c_str(), expected.to_string().c_str()));
            }
        }

        TEST_METHOD(operator_round)
        {
            const Microsoft::Windows::Foundation::decimal n_1_888{ L"1.888" };
            const Microsoft::Windows::Foundation::decimal n_neg1_888{ L"-1.888" };
            const Microsoft::Windows::Foundation::decimal n_1_25{ L"1.25" };
            const Microsoft::Windows::Foundation::decimal n_neg1_25{ L"-1.25" };

            const Microsoft::Windows::Foundation::decimal n_1_2{ L"1.2" };
            const Microsoft::Windows::Foundation::decimal n_1_89{ L"1.89" };
            const Microsoft::Windows::Foundation::decimal n_1_9{ L"1.9" };
            const Microsoft::Windows::Foundation::decimal n_1{ L"1" };
            const Microsoft::Windows::Foundation::decimal n_2{ L"2" };
            const Microsoft::Windows::Foundation::decimal n_neg1_2{ L"-1.2" };
            const Microsoft::Windows::Foundation::decimal n_neg1_89{ L"-1.89" };
            const Microsoft::Windows::Foundation::decimal n_neg1_9{ L"-1.9" };
            const Microsoft::Windows::Foundation::decimal n_neg1{ L"-1" };
            const Microsoft::Windows::Foundation::decimal n_neg2{ L"-2" };

            //----------------------------------------------

            const Microsoft::Windows::Foundation::decimal n_1_888_round_0{ n_1_888.round(0) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_0.to_string().c_str(), n_2.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_888_round_1{ n_1_888.round(1) };
            VERIFY_ARE_EQUAL(n_1_9, n_1_888_round_1, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_1.to_string().c_str(), n_1_9.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_888_round_2{ n_1_888.round(2) };
            VERIFY_ARE_EQUAL(n_1_89, n_1_888_round_2, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_2.to_string().c_str(), n_1_89.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_888_round_3{ n_1_888.round(3) };
            VERIFY_ARE_EQUAL(n_1_888, n_1_888_round_3, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_3.to_string().c_str(), n_1_888.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_888_round_4{ n_1_888.round(4) };
            VERIFY_ARE_EQUAL(n_1_888, n_1_888_round_4, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_4.to_string().c_str(), n_1_888.to_string().c_str()));

            //----------------------------------------------

            const Microsoft::Windows::Foundation::decimal n_neg1_888_round_0{ n_neg1_888.round(0) };
            VERIFY_ARE_EQUAL(n_neg2, n_neg1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_888.to_string().c_str(), n_neg1_888_round_0.to_string().c_str(), n_neg2.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_888_round_1{ n_neg1_888.round(1) };
            VERIFY_ARE_EQUAL(n_neg2, n_neg1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_888.to_string().c_str(), n_neg1_888_round_1.to_string().c_str(), n_neg1_9.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_888_round_2{ n_neg1_888.round(2) };
            VERIFY_ARE_EQUAL(n_neg2, n_neg1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_888.to_string().c_str(), n_neg1_888_round_2.to_string().c_str(), n_neg1_89.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_888_round_3{ n_neg1_888.round(3) };
            VERIFY_ARE_EQUAL(n_neg2, n_neg1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_888.to_string().c_str(), n_neg1_888_round_3.to_string().c_str(), n_neg1_888.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_888_round_4{ n_neg1_888.round(4) };
            VERIFY_ARE_EQUAL(n_neg2, n_neg1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_888.to_string().c_str(), n_neg1_888_round_4.to_string().c_str(), n_neg1_888.to_string().c_str()));

            //----------------------------------------------

            const Microsoft::Windows::Foundation::decimal n_1_25_round_0{ n_1_25.round(0) };
            VERIFY_ARE_EQUAL(n_1, n_1_25_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_25.to_string().c_str(), n_1_25_round_0.to_string().c_str(), n_1.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_25_round_1{ n_1_25.round(1) };
            VERIFY_ARE_EQUAL(n_1_2, n_1_25_round_1, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_25.to_string().c_str(), n_1_25_round_1.to_string().c_str(), n_1_2.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_25_round_2{ n_1_25.round(2) };
            VERIFY_ARE_EQUAL(n_1_25, n_1_25_round_2, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_25.to_string().c_str(), n_1_25_round_2.to_string().c_str(), n_1_25.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_25_round_3{ n_1_25.round(3) };
            VERIFY_ARE_EQUAL(n_1_25, n_1_25_round_3, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_25.to_string().c_str(), n_1_25_round_3.to_string().c_str(), n_1_25.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_1_25_round_4{ n_1_25.round(4) };
            VERIFY_ARE_EQUAL(n_1_25, n_1_25_round_4, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_25.to_string().c_str(), n_1_25_round_4.to_string().c_str(), n_1_25.to_string().c_str()));

            //----------------------------------------------

            const Microsoft::Windows::Foundation::decimal n_neg1_25_round_0{ n_neg1_25.round(0) };
            VERIFY_ARE_EQUAL(n_neg1, n_neg1_25_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_25.to_string().c_str(), n_neg1_25_round_0.to_string().c_str(), n_neg1.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_25_round_1{ n_neg1_25.round(1) };
            VERIFY_ARE_EQUAL(n_neg1_2, n_neg1_25_round_1, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_25.to_string().c_str(), n_neg1_25_round_1.to_string().c_str(), n_neg1_2.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_25_round_2{ n_neg1_25.round(2) };
            VERIFY_ARE_EQUAL(n_neg1_25, n_neg1_25_round_2, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_25.to_string().c_str(), n_neg1_25_round_2.to_string().c_str(), n_neg1_25.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_25_round_3{ n_neg1_25.round(3) };
            VERIFY_ARE_EQUAL(n_neg1_25, n_neg1_25_round_3, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_25.to_string().c_str(), n_neg1_25_round_3.to_string().c_str(), n_neg1_25.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal n_neg1_25_round_4{ n_neg1_25.round(4) };
            VERIFY_ARE_EQUAL(n_neg1_25, n_neg1_25_round_4, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_neg1_25.to_string().c_str(), n_neg1_25_round_4.to_string().c_str(), n_neg1_25.to_string().c_str()));
        }

        TEST_METHOD(math)
        {
            const Microsoft::Windows::Foundation::decimal a{ 1 };
            const Microsoft::Windows::Foundation::decimal b{ 0.5 };
            const Microsoft::Windows::Foundation::decimal c{ L"-6.66" };
            const Microsoft::Windows::Foundation::decimal d{ L"1.23" };
            const Microsoft::Windows::Foundation::decimal e{ L"4567.089" };
            const Microsoft::Windows::Foundation::decimal f{ -4ll };
            const Microsoft::Windows::Foundation::decimal g{ 1967u };
            const Microsoft::Windows::Foundation::decimal h{ 1001.0f };

            auto x = (((a - b) + (c % d)) * e).round(5) / f;
            auto y = x++.round(3).clamp(f, g);
            auto z = --y.floor() * ++x.ceil() * -y.truncate();

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"x = %ls", x.to_string().c_str()));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"y = %ls", y.to_string().c_str()));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"z = %ls", z.to_string().c_str()));

            const Microsoft::Windows::Foundation::decimal expectedX{ L"12.4177225" };
            const Microsoft::Windows::Foundation::decimal expectedY{ L"11.418" };
            const Microsoft::Windows::Foundation::decimal expectedZ{ L"-1540" };
            VERIFY_ARE_EQUAL(expectedX, x);
            VERIFY_ARE_EQUAL(expectedY, y);
            VERIFY_ARE_EQUAL(expectedZ, z);
        }
    };
}
