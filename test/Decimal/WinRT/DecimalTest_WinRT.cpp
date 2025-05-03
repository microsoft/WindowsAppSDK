// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <winrt/Microsoft.Windows.Foundation.h>

#include <decimal.h>
#include <decimalcppwinrt.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

namespace winrt
{
inline winrt::hstring DecimalValueToString(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
{
    return winrt::Microsoft::Windows::Foundation::DecimalHelper::ToString(value);
}
}

namespace WEX::TestExecution
{
    // Teach TAEF how to format a winrt::Microsoft::Windows::Foundation::DecimalValue
    template <>
    class VerifyOutputTraits<winrt::Microsoft::Windows::Foundation::DecimalValue>
    {
    public:
        static WEX::Common::NoThrowString ToString(winrt::Microsoft::Windows::Foundation::DecimalValue const& value)
        {
            const auto s{ winrt::DecimalValueToString(value) };
            return WEX::Common::NoThrowString().Format(L"\"%s\"", s.c_str());
        }
    };

    // Teach TAEF how to compare a winrt::Microsoft::Windows::Foundation::DecimalValue
    template <>
    class VerifyCompareTraits<winrt::Microsoft::Windows::Foundation::DecimalValue, winrt::Microsoft::Windows::Foundation::DecimalValue>
    {
    public:
        static bool AreEqual(winrt::Microsoft::Windows::Foundation::DecimalValue const& expected, winrt::Microsoft::Windows::Foundation::DecimalValue const& actual)
        {
            return winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(expected, actual) == 0;
        }

        static bool AreSame(winrt::Microsoft::Windows::Foundation::DecimalValue const& expected, winrt::Microsoft::Windows::Foundation::DecimalValue const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(winrt::Microsoft::Windows::Foundation::DecimalValue const& expectedLess, winrt::Microsoft::Windows::Foundation::DecimalValue const& expectedGreater)
        {
            return winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(expectedLess, expectedGreater) < 0;
        }

        static bool IsGreaterThan(winrt::Microsoft::Windows::Foundation::DecimalValue const& expectedGreater, winrt::Microsoft::Windows::Foundation::DecimalValue const& expectedLess)
        {
            return winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(expectedGreater, expectedLess) > 0;
        }

        static bool IsNull(winrt::Microsoft::Windows::Foundation::DecimalValue const& /*object*/)
        {
            return false;
        }
    };
}

namespace Test::DecimalValue::Tests
{
    class DecimalTest_WinRT
    {
    public:
        BEGIN_TEST_CLASS(DecimalTest_WinRT)
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

        TEST_METHOD(from_to_bool)
        {
            const bool data{ true };
            const auto value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromBoolean(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToBoolean(value) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_int16)
        {
            const std::int16_t data{ -32109 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt16(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToInt16(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_int32)
        {
            const std::int32_t data{ -1234567890 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt32(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToInt32(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_int64)
        {
            const std::int64_t data{ -1234567890123456789 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt64(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToInt64(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_uint8)
        {
            const std::uint8_t data{ 123 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt8(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToUInt8(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_uint16)
        {
            const std::uint16_t data{ 32109 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt16(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToUInt16(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_uint32)
        {
            const std::uint32_t data{ 1234567890 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt32(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToUInt32(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_uint64)
        {
            const std::uint64_t data{ 0xFEDCBA0987654321 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt64(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToUInt64(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_single)
        {
            const float data{ -1.25 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromSingle(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToSingle(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_double)
        {
            const double data{ -1.25 };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromDouble(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToDouble(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_string)
        {
            const std::wstring data{ L"-12.345" };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToString(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_string_locale_system_default)
        {
            const winrt::hstring data{ L"-12.345" };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromStringWithSystemDefaultLocale(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToStringWithSystemDefaultLocale(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_string_locale_user_default)
        {
            const winrt::hstring data{ L"-12.345" };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromStringWithUserDefaultLocale(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToStringWithUserDefaultLocale(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(from_to_string_locale_thread)
        {
            const winrt::hstring data{ L"-12.345" };
            const auto decimalValue{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromStringWithThreadLocale(data) };
            const auto to{ winrt::Microsoft::Windows::Foundation::DecimalHelper::ToStringWithThreadLocale(decimalValue) };
            VERIFY_ARE_EQUAL(data, to);
        }

        TEST_METHOD(compare_bool)
        {
            const auto decimal_false{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromBoolean(false) };
            const auto decimal_true{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromBoolean(true) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(decimal_false, decimal_false));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(decimal_true, decimal_true));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(decimal_false, decimal_true));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(decimal_true, decimal_false));

            VERIFY_IS_TRUE(decimal_true == decimal_true);
            VERIFY_IS_FALSE(decimal_true != decimal_true);
            VERIFY_IS_FALSE(decimal_true < decimal_true);
            VERIFY_IS_TRUE(decimal_true <= decimal_true);
            VERIFY_IS_FALSE(decimal_true > decimal_true);
            VERIFY_IS_TRUE(decimal_true >= decimal_true);
        }

        TEST_METHOD(compare_int16)
        {
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt16(static_cast<std::int16_t>(-32109)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt16(static_cast<std::int16_t>(32109)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt32(static_cast<std::int32_t>(-1234567890)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt32(static_cast<std::int32_t>(1234567890)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt64(static_cast<std::int64_t>(-1234567890123456789)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt64(static_cast<std::int64_t>(1234567890123456789)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt8(static_cast<std::uint8_t>(123)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt8(static_cast<std::uint8_t>(234)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt16(static_cast<std::uint16_t>(32109)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt16(static_cast<std::uint16_t>(65432)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt32(static_cast<std::uint32_t>(1234567890)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt32(static_cast<std::uint32_t>(4019283756)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt64(static_cast<std::uint64_t>(0x1234567890ABCDEF)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromUInt64(static_cast<std::uint64_t>(0xFEDCBA0987654321)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromSingle(static_cast<float>(-1.25)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromSingle(static_cast<float>(1.25)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromDouble(static_cast<double>(-1.25)) };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromDouble(static_cast<double>(1.25)) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"-12.345") };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"12.345") };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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
            const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"-12.345") };
            const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"12.345") };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, left));
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, right));
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(left, right));
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Compare(right, left));

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

        TEST_METHOD(scale)
        {
            const auto n_0{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"79228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(0u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(n_0));

            const auto n_1{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"7922816251426433759354395033.5" }) };
            VERIFY_ARE_EQUAL(1u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(n_1));

            const auto n_2{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"792281625142643375935439503.35" }) };
            VERIFY_ARE_EQUAL(2u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(n_2));

            const auto n_27{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"79.228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(27u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(n_27));

            const auto n_28{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"7.9228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(28u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(n_28));

            const auto neg_n_0{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-79228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(0u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(neg_n_0));

            const auto neg_n_1{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-7922816251426433759354395033.5" }) };
            VERIFY_ARE_EQUAL(1u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(neg_n_1));

            const auto neg_n_2{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-792281625142643375935439503.35" }) };
            VERIFY_ARE_EQUAL(2u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(neg_n_2));

            const auto neg_n_27{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-79.228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(27u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(neg_n_27));

            const auto neg_n_28{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-7.9228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(28u, winrt::Microsoft::Windows::Foundation::DecimalHelper::Scale(neg_n_28));
        }

        TEST_METHOD(sign)
        {
            const auto zero{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"0" }) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Sign(zero));

            const auto neg_zero{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-0" }) };
            VERIFY_ARE_EQUAL(0, winrt::Microsoft::Windows::Foundation::DecimalHelper::Sign(neg_zero));
            VERIFY_ARE_EQUAL(zero, neg_zero);

            const auto pos{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"12.345" }) };
            VERIFY_ARE_EQUAL(1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Sign(pos));

            const auto neg{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-12.345" }) };
            VERIFY_ARE_EQUAL(-1, winrt::Microsoft::Windows::Foundation::DecimalHelper::Sign(neg));
        }

        TEST_METHOD(min_max)
        {
            VERIFY_ARE_EQUAL(28u, winrt::Microsoft::Windows::Foundation::DecimalHelper::MaxScale());

            const auto max_decimal{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"79228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(max_decimal, winrt::Microsoft::Windows::Foundation::DecimalHelper::MaxValue());

            const auto min_decimal{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-79228162514264337593543950335" }) };
            VERIFY_ARE_EQUAL(min_decimal, winrt::Microsoft::Windows::Foundation::DecimalHelper::MinValue());
        }

        TEST_METHOD(negate)
        {
            const auto zero{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"0" }) };
            const auto pos{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"12.345" }) };
            const auto neg{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-12.345" }) };

            const auto zero_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Negate(zero) };
            VERIFY_IS_TRUE(zero_value == zero);
            VERIFY_IS_TRUE(zero_value != pos);
            VERIFY_IS_TRUE(zero_value != neg);
            VERIFY_IS_TRUE(zero_value < pos);
            VERIFY_IS_TRUE(zero_value > neg);

            const auto pos_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Negate(neg) };
            VERIFY_IS_TRUE(pos_value != zero);
            VERIFY_IS_TRUE(pos_value == pos);
            VERIFY_IS_TRUE(pos_value != neg);
            VERIFY_IS_TRUE(pos_value > zero);
            VERIFY_IS_TRUE(pos_value > neg);

            const auto neg_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Negate(pos) };
            VERIFY_IS_TRUE(neg_value != zero);
            VERIFY_IS_TRUE(neg_value != pos);
            VERIFY_IS_TRUE(neg_value == neg);
            VERIFY_IS_TRUE(neg_value < zero);
            VERIFY_IS_TRUE(neg_value < pos);
        }

        TEST_METHOD(abs)
        {
            const auto zero{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"0" }) };
            const auto pos{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"12.345" }) };
            const auto neg{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-12.345" }) };

            const auto zero_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Abs(zero) };
            VERIFY_IS_TRUE(zero_value == zero);
            VERIFY_IS_TRUE(zero_value != pos);
            VERIFY_IS_TRUE(zero_value != neg);
            VERIFY_IS_TRUE(zero_value < pos);
            VERIFY_IS_TRUE(zero_value > neg);

            const auto pos_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Abs(pos) };
            VERIFY_IS_TRUE(pos_value != zero);
            VERIFY_IS_TRUE(pos_value == pos);
            VERIFY_IS_TRUE(pos_value != neg);
            VERIFY_IS_TRUE(pos_value > zero);
            VERIFY_IS_TRUE(pos_value > neg);

            const auto neg_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Abs(neg) };
            VERIFY_IS_TRUE(neg_value != zero);
            VERIFY_IS_TRUE(neg_value == pos);
            VERIFY_IS_TRUE(neg_value != neg);
            VERIFY_IS_TRUE(neg_value > zero);
            VERIFY_IS_TRUE(neg_value == pos);
        }

        TEST_METHOD(fix)
        {
            const auto zero{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"0" }) };
            const auto value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Fix(zero) };
            VERIFY_IS_TRUE(value == zero);

            const auto pos{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"12.345" }) };
            const auto pos_fix{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"12" }) };
            const auto pos_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Fix(pos) };
            VERIFY_IS_TRUE(pos_value == pos_fix);

            const auto neg{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-12.345" }) };
            const auto neg_fix{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-12" }) };
            const auto neg_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Fix(neg) };
            VERIFY_IS_TRUE(neg_value == neg_fix);
        }

        TEST_METHOD(integer)
        {
            const auto zero{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"0" }) };
            const auto value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Integer(zero) };
            VERIFY_IS_TRUE(value == zero);

            const auto pos{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"12.345" }) };
            const auto pos_integer{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"12" }) };
            const auto pos_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Integer(pos) };
            VERIFY_IS_TRUE(pos_value == pos_integer);

            const auto neg{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-12.345" }) };
            const auto neg_integer{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(winrt::hstring{ L"-13" }) };
            const auto neg_value{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Integer(neg) };
            VERIFY_IS_TRUE(neg_value == neg_integer);
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
                const winrt::hstring leftString{ value.left };
                const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(leftString) };
                const winrt::hstring rightString{ value.right };
                const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                const auto expected{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(expectedString) };
                const auto result{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Add(left, right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Add %s = %s vs %s",
                    winrt::DecimalValueToString(left).c_str(), winrt::DecimalValueToString(right).c_str(),
                    winrt::DecimalValueToString(result).c_str(), winrt::DecimalValueToString(expected).c_str()));
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
                const winrt::hstring leftString{ value.left };
                const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(leftString) };
                const winrt::hstring rightString{ value.right };
                const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                const auto expected{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(expectedString) };
                const auto result{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Subtract(left, right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Subtract %s = %s vs %s",
                    winrt::DecimalValueToString(left).c_str(), winrt::DecimalValueToString(right).c_str(),
                    winrt::DecimalValueToString(result).c_str(), winrt::DecimalValueToString(expected).c_str()));
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
                const winrt::hstring leftString{ value.left };
                const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(leftString) };
                const winrt::hstring rightString{ value.right };
                const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                const auto expected{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(expectedString) };
                const auto result{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Multiply(left, right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Multiply %s = %s vs %s",
                    winrt::DecimalValueToString(left).c_str(), winrt::DecimalValueToString(right).c_str(),
                    winrt::DecimalValueToString(result).c_str(), winrt::DecimalValueToString(expected).c_str()));
            }
        }

        TEST_METHOD(operator_divide)
        {
            try
            {
                const auto data{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt32(123) };
                const winrt::Microsoft::Windows::Foundation::DecimalValue zero{};
                const auto result{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Divide(data, zero) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (wil::ResultException& e)
            {
                VERIFY_ARE_EQUAL(DISP_E_DIVBYZERO, e.GetErrorCode(), WEX::Common::String().Format(L"0x%X %hs", e.GetErrorCode(), e.what()));
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(DISP_E_DIVBYZERO, e.code(), WEX::Common::String().Format(L"0x%X %hs", e.code(), e.message().c_str()));
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
                const winrt::hstring leftString{ value.left };
                const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(leftString) };
                const winrt::hstring rightString{ value.right };
                const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                const auto expected{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(expectedString) };
                const auto result{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Divide(left, right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Divide %s = %s vs %s",
                    winrt::DecimalValueToString(left).c_str(), winrt::DecimalValueToString(right).c_str(),
                    winrt::DecimalValueToString(result).c_str(), winrt::DecimalValueToString(expected).c_str()));
            }
        }

        TEST_METHOD(operator_mod)
        {
            try
            {
                const auto data{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromInt32(123) };
                const winrt::Microsoft::Windows::Foundation::DecimalValue zero{};
                const auto result{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Modulo(data, zero) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (wil::ResultException& e)
            {
                VERIFY_ARE_EQUAL(DISP_E_DIVBYZERO, e.GetErrorCode(), WEX::Common::String().Format(L"0x%X %hs", e.GetErrorCode(), e.what()));
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(DISP_E_DIVBYZERO, e.code(), WEX::Common::String().Format(L"0x%X %hs", e.code(), e.message().c_str()));
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
                const winrt::hstring leftString{ value.left };
                const auto left{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(leftString) };
                const winrt::hstring rightString{ value.right };
                const auto right{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                const auto expected{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(expectedString) };
                const auto result{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Modulo(left, right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Modulo %s = %s vs %s",
                    winrt::DecimalValueToString(left).c_str(), winrt::DecimalValueToString(right).c_str(),
                    winrt::DecimalValueToString(result).c_str(), winrt::DecimalValueToString(expected).c_str()));
            }
        }

        TEST_METHOD(operator_round)
        {
            const auto n_1_888{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"1.888") };
            const auto n_neg1_888{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"-1.888") };
            const auto n_1_25{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"1.25") };
            const auto n_neg1_25{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"-1.25") };

            const auto n_2{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"2") };
            const auto n_1_9{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"1.9") };
            const auto n_1_89{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"1.89") };
            const auto n_neg1_9{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"1.9") };
            const auto n_neg1_89{ winrt::Microsoft::Windows::Foundation::DecimalHelper::FromString(L"1.89") };

            const auto n_1_888_round_0{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Round(n_1_888, 0) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                winrt::DecimalValueToString(n_1_888).c_str(), winrt::DecimalValueToString(n_1_888_round_0).c_str(),
                winrt::DecimalValueToString(n_2).c_str()));

            const auto n_1_888_round_1{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Round(n_1_888, 1) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                winrt::DecimalValueToString(n_1_888).c_str(), winrt::DecimalValueToString(n_1_888_round_1).c_str(),
                winrt::DecimalValueToString(n_1_9).c_str()));

            const auto n_1_888_round_2{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Round(n_1_888, 2) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                winrt::DecimalValueToString(n_1_888).c_str(), winrt::DecimalValueToString(n_1_888_round_2).c_str(),
                winrt::DecimalValueToString(n_1_89).c_str()));

            const auto n_1_888_round_3{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Round(n_1_888, 3) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                winrt::DecimalValueToString(n_1_888).c_str(), winrt::DecimalValueToString(n_1_888_round_3).c_str(),
                winrt::DecimalValueToString(n_1_888).c_str()));

            const auto n_1_888_round_4{ winrt::Microsoft::Windows::Foundation::DecimalHelper::Round(n_1_888, 4) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                winrt::DecimalValueToString(n_1_888).c_str(), winrt::DecimalValueToString(n_1_888_round_4).c_str(),
                winrt::DecimalValueToString(n_1_888).c_str()));
        }
    };
}
