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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data, GetSystemDefaultLCID());
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
            Microsoft::Windows::Foundation::decimal object(data);
            const auto to{ object.to_string() };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_string() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_system_default)
        {
            const winrt::hstring data{ L"-12.345" };
            Microsoft::Windows::Foundation::decimal object(data, LOCALE_SYSTEM_DEFAULT);
            const auto to{ object.to_hstring(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(LOCALE_SYSTEM_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_user_default)
        {
            const winrt::hstring data{ L"-12.345" };
            Microsoft::Windows::Foundation::decimal object(data, LOCALE_USER_DEFAULT);
            const auto to{ object.to_hstring(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(LOCALE_USER_DEFAULT) };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_thread)
        {
            const winrt::hstring data{ L"-12.345" };
            Microsoft::Windows::Foundation::decimal object(data, GetThreadLocale());
            const auto to{ object.to_hstring(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(GetThreadLocale()) };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(ctor_to_assign_string_lcid_invariant)
        {
            const winrt::hstring data{ L"-12.345" };
            Microsoft::Windows::Foundation::decimal object(data, LOCALE_INVARIANT);
            const auto to{ object.to_hstring(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to);

            Microsoft::Windows::Foundation::decimal object2;
            object2 = data;
            const auto to2{ object.to_hstring(LOCALE_INVARIANT) };
            VERIFY_ARE_EQUAL(data, to2);
        }

#if defined(WINRT_BASE_H)
        TEST_METHOD(ctor_to_assign_hstring)
        {
            const winrt::hstring data{ L"-12.345" };
            Microsoft::Windows::Foundation::decimal object(data);
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
            Microsoft::Windows::Foundation::decimal object(data, LOCALE_SYSTEM_DEFAULT);
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
            Microsoft::Windows::Foundation::decimal object(data, LOCALE_USER_DEFAULT);
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
            Microsoft::Windows::Foundation::decimal object(data, GetThreadLocale());
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
            Microsoft::Windows::Foundation::decimal object(data, LOCALE_INVARIANT);
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
            Microsoft::Windows::Foundation::decimal decimal_false(false);
            Microsoft::Windows::Foundation::decimal decimal_true(true);
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
            Microsoft::Windows::Foundation::decimal left(static_cast<char>(-123));
            Microsoft::Windows::Foundation::decimal right(static_cast<char>(123));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<std::int16_t>(-32109));
            Microsoft::Windows::Foundation::decimal right(static_cast<std::int16_t>(32109));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<std::int32_t>(-1234567890));
            Microsoft::Windows::Foundation::decimal right(static_cast<std::int32_t>(1234567890));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<std::int64_t>(-1234567890123456789));
            Microsoft::Windows::Foundation::decimal right(static_cast<std::int64_t>(1234567890123456789));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<std::uint8_t>(123));
            Microsoft::Windows::Foundation::decimal right(static_cast<std::uint8_t>(234));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<std::uint16_t>(32109));
            Microsoft::Windows::Foundation::decimal right(static_cast<std::uint16_t>(65432));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<std::uint32_t>(1234567890));
            Microsoft::Windows::Foundation::decimal right(static_cast<std::uint32_t>(4019283756));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<std::uint64_t>(0x1234567890ABCDEF));
            Microsoft::Windows::Foundation::decimal right(static_cast<std::uint64_t>(0xFEDCBA0987654321));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<float>(-1.25));
            Microsoft::Windows::Foundation::decimal right(static_cast<float>(1.25));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<double>(-1.25));
            Microsoft::Windows::Foundation::decimal right(static_cast<double>(1.25));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<long>(-1234567890));
            Microsoft::Windows::Foundation::decimal right(static_cast<long>(1234567890));
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
            Microsoft::Windows::Foundation::decimal left(static_cast<unsigned long>(1234567890));
            Microsoft::Windows::Foundation::decimal right(static_cast<unsigned long>(4019283756));
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
            Microsoft::Windows::Foundation::decimal left(L"-12.345");
            Microsoft::Windows::Foundation::decimal right(L"12.345");
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
            Microsoft::Windows::Foundation::decimal zero(L"0");
            Microsoft::Windows::Foundation::decimal pos(L"12.345");
            Microsoft::Windows::Foundation::decimal neg(L"-12.345");

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

        TEST_METHOD(operator_neg)
        {
            Microsoft::Windows::Foundation::decimal zero(L"0");
            Microsoft::Windows::Foundation::decimal pos(L"12.345");
            Microsoft::Windows::Foundation::decimal neg(L"-12.345");

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
            Microsoft::Windows::Foundation::decimal zero(L"0");
            Microsoft::Windows::Foundation::decimal pos(L"12.345");
            Microsoft::Windows::Foundation::decimal neg(L"-12.345");

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

        TEST_METHOD(fix)
        {
            Microsoft::Windows::Foundation::decimal zero(L"0");
            const auto value{ zero.fix() };
            VERIFY_IS_TRUE(value == zero);

            Microsoft::Windows::Foundation::decimal pos(L"12.345");
            Microsoft::Windows::Foundation::decimal pos_fix(L"12");
            const auto pos_value{ pos.fix() };
            VERIFY_IS_TRUE(pos_value == pos_fix);

            Microsoft::Windows::Foundation::decimal neg(L"-12.345");
            Microsoft::Windows::Foundation::decimal neg_fix(L"-12");
            const auto neg_value{ neg.fix() };
            VERIFY_IS_TRUE(neg_value == neg_fix);
        }

        TEST_METHOD(integer)
        {
            Microsoft::Windows::Foundation::decimal zero(L"0");
            const auto value{ zero.integer() };
            VERIFY_IS_TRUE(value == zero);

            Microsoft::Windows::Foundation::decimal pos(L"12.345");
            Microsoft::Windows::Foundation::decimal pos_integer(L"12");
            const auto pos_value{ pos.integer() };
            VERIFY_IS_TRUE(pos_value == pos_integer);

            Microsoft::Windows::Foundation::decimal neg(L"-12.345");
            Microsoft::Windows::Foundation::decimal neg_integer(L"-13");
            const auto neg_value{ neg.integer() };
            VERIFY_IS_TRUE(neg_value == neg_integer);
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
                Microsoft::Windows::Foundation::decimal left{ value.left };
                Microsoft::Windows::Foundation::decimal right{ value.right };
                Microsoft::Windows::Foundation::decimal expected{ value.result };
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
                Microsoft::Windows::Foundation::decimal left{ value.left };
                Microsoft::Windows::Foundation::decimal right{ value.right };
                Microsoft::Windows::Foundation::decimal expected{ value.result };
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
                Microsoft::Windows::Foundation::decimal left{ value.left };
                Microsoft::Windows::Foundation::decimal right{ value.right };
                Microsoft::Windows::Foundation::decimal expected{ value.result };
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
                Microsoft::Windows::Foundation::decimal left{ value.left };
                Microsoft::Windows::Foundation::decimal right{ value.right };
                Microsoft::Windows::Foundation::decimal expected{ value.result };
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
                Microsoft::Windows::Foundation::decimal data{ 123 };
                Microsoft::Windows::Foundation::decimal zero{};
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
                Microsoft::Windows::Foundation::decimal left{ value.left };
                Microsoft::Windows::Foundation::decimal right{ value.right };
                Microsoft::Windows::Foundation::decimal expected{ value.result };
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
            Microsoft::Windows::Foundation::decimal n_1_888{ L"1.888" };
            Microsoft::Windows::Foundation::decimal n_neg1_888{ L"-1.888" };
            Microsoft::Windows::Foundation::decimal n_1_25{ L"1.25" };
            Microsoft::Windows::Foundation::decimal n_neg1_25{ L"-1.25" };

            Microsoft::Windows::Foundation::decimal n_2{ L"2" };
            Microsoft::Windows::Foundation::decimal n_1_9{ L"1.9" };
            Microsoft::Windows::Foundation::decimal n_1_89{ L"1.89" };
            Microsoft::Windows::Foundation::decimal n_neg1_9{ L"1.9" };
            Microsoft::Windows::Foundation::decimal n_neg1_89{ L"1.89" };

            Microsoft::Windows::Foundation::decimal n_1_888_round_0{ n_1_888.round(0) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_0.to_string().c_str(), n_2.to_string().c_str()));

            Microsoft::Windows::Foundation::decimal n_1_888_round_1{ n_1_888.round(1) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_1.to_string().c_str(), n_1_9.to_string().c_str()));

            Microsoft::Windows::Foundation::decimal n_1_888_round_2{ n_1_888.round(2) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_2.to_string().c_str(), n_1_89.to_string().c_str()));

            Microsoft::Windows::Foundation::decimal n_1_888_round_3{ n_1_888.round(3) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_3.to_string().c_str(), n_1_888.to_string().c_str()));

            Microsoft::Windows::Foundation::decimal n_1_888_round_4{ n_1_888.round(4) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.round(0) = %s vs %s",
                n_1_888.to_string().c_str(), n_1_888_round_4.to_string().c_str(), n_1_888.to_string().c_str()));
        }
    };
}
