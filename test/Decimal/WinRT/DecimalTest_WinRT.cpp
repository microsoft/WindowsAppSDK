// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <winrt/Microsoft.Windows.Foundation.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

namespace WEX::TestExecution
{
    // Teach TAEF how to format a winrt::Microsoft::Windows::Foundation::Decimal
    template <>
    class VerifyOutputTraits<winrt::Microsoft::Windows::Foundation::Decimal>
    {
    public:
        static WEX::Common::NoThrowString ToString(winrt::Microsoft::Windows::Foundation::Decimal const& value)
        {
            const auto s{ value.ToString() };
            return WEX::Common::NoThrowString().Format(L"\"%s\"", s.c_str());
        }
    };

    // Teach TAEF how to compare a winrt::Microsoft::Windows::Foundation::Decimal
    template <>
    class VerifyCompareTraits<winrt::Microsoft::Windows::Foundation::Decimal, winrt::Microsoft::Windows::Foundation::Decimal>
    {
    public:
        static bool AreEqual(winrt::Microsoft::Windows::Foundation::Decimal const& expected, winrt::Microsoft::Windows::Foundation::Decimal const& actual)
        {
            return expected.Compare(actual) == 0;
        }

        static bool AreSame(winrt::Microsoft::Windows::Foundation::Decimal const& expected, winrt::Microsoft::Windows::Foundation::Decimal const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(winrt::Microsoft::Windows::Foundation::Decimal const& expectedLess, winrt::Microsoft::Windows::Foundation::Decimal const& expectedGreater)
        {
            return expectedLess.Compare(expectedGreater) < 0;
        }

        static bool IsGreaterThan(winrt::Microsoft::Windows::Foundation::Decimal const& expectedGreater, winrt::Microsoft::Windows::Foundation::Decimal const& expectedLess)
        {
            return expectedGreater.Compare(expectedLess) > 0;
        }

        static bool IsNull(winrt::Microsoft::Windows::Foundation::Decimal const& object)
        {
            return !!object;
        }
    };
}

namespace Test::Decimal::Tests
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

        TEST_METHOD(ctor)
        {
            const std::int64_t data{};
            winrt::Microsoft::Windows::Foundation::Decimal decimal;
            const auto value{ decimal.ToInt64() };
            VERIFY_ARE_EQUAL(data, value);
        }

        TEST_METHOD(create_to_set_decimal)
        {
            const std::int32_t dataValue{ -1234567890 };
            winrt::Microsoft::Windows::Foundation::Decimal data(winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt32(dataValue));
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromDecimal(data) };
            const auto to{ object.ToDecimal() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromDecimal(data);
            const auto to2{ object.ToDecimal() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_bool)
        {
            const bool data{ true };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromBoolean(data) };
            const auto to{ object.ToBoolean() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromBoolean(data);
            const auto to2{ object.ToBoolean() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_int16)
        {
            const std::int16_t data{ -32109};
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt16(data) };
            const auto to{ object.ToInt16() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromInt16(data);
            const auto to2{ object.ToInt16() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_int32)
        {
            const std::int32_t data{ -1234567890 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt32(data) };
            const auto to{ object.ToInt32() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromInt32(data);
            const auto to2{ object.ToInt32() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_int64)
        {
            const std::int64_t data{ -1234567890123456789 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt64(data) };
            const auto to{ object.ToInt64() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromInt64(data);
            const auto to2{ object.ToInt64() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_uint8)
        {
            const std::uint8_t data{ 123 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt8(data) };
            const auto to{ object.ToUInt8() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromUInt8(data);
            const auto to2{ object.ToUInt16() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_uint16)
        {
            const std::uint16_t data{ 32109 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt16(data) };
            const auto to{ object.ToUInt16() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromUInt16(data);
            const auto to2{ object.ToUInt16() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_uint32)
        {
            const std::uint32_t data{ 1234567890 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt32(data) };
            const auto to{ object.ToUInt32() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromUInt32(data);
            const auto to2{ object.ToUInt32() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_uint64)
        {
            const std::uint64_t data{ 0xFEDCBA0987654321 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt64(data) };
            const auto to{ object.ToUInt64() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromUInt64(data);
            const auto to2{ object.ToUInt64() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_single)
        {
            const float data{ -1.25 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromSingle(data) };
            const auto to{ object.ToSingle() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromSingle(data);
            const auto to2{ object.ToSingle() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_double)
        {
            const double data{ -1.25 };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromDouble(data) };
            const auto to{ object.ToDouble() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromDouble(data);
            const auto to2{ object.ToDouble() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_string)
        {
            const std::wstring data{ L"-12.345" };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(data) };
            const auto to{ object.ToString() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromString(data);
            const auto to2{ object.ToString() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_string_locale_system_default)
        {
            const winrt::hstring data{ L"-12.345" };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromStringWithSystemDefaultLocale(data) };
            const auto to{ object.ToStringWithSystemDefaultLocale() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromStringWithSystemDefaultLocale(data);
            const auto to2{ object.ToStringWithSystemDefaultLocale() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_string_locale_user_default)
        {
            const winrt::hstring data{ L"-12.345" };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromStringWithUserDefaultLocale(data) };
            const auto to{ object.ToStringWithUserDefaultLocale() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromStringWithUserDefaultLocale(data);
            const auto to2{ object.ToStringWithUserDefaultLocale() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_string_locale_thread)
        {
            const winrt::hstring data{ L"-12.345" };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromStringWithThreadLocale(data) };
            const auto to{ object.ToStringWithThreadLocale() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromStringWithThreadLocale(data);
            const auto to2{ object.ToStringWithThreadLocale() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(create_to_set_string_locale_invariant)
        {
            const winrt::hstring data{ L"-12.345" };
            winrt::Microsoft::Windows::Foundation::Decimal object{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromStringWithInvariantLocale(data) };
            const auto to{ object.ToStringWithInvariantLocale() };
            VERIFY_ARE_EQUAL(data, to);

            winrt::Microsoft::Windows::Foundation::Decimal object2;
            object2.SetFromStringWithInvariantLocale(data);
            const auto to2{ object.ToStringWithInvariantLocale() };
            VERIFY_ARE_EQUAL(data, to2);
        }

        TEST_METHOD(compare_bool)
        {
            winrt::Microsoft::Windows::Foundation::Decimal decimal_false{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromBoolean(false) };
            winrt::Microsoft::Windows::Foundation::Decimal decimal_true{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromBoolean(true) };
            VERIFY_ARE_EQUAL(0, decimal_false.Compare(decimal_false));
            VERIFY_ARE_EQUAL(0, decimal_true.Compare(decimal_true));
            VERIFY_ARE_EQUAL(-1, decimal_false.Compare(decimal_true));
            VERIFY_ARE_EQUAL(1, decimal_true.Compare(decimal_false));

            VERIFY_IS_TRUE(decimal_true == decimal_true);
            VERIFY_IS_FALSE(decimal_true != decimal_true);
            VERIFY_IS_FALSE(decimal_true < decimal_true);
            VERIFY_IS_TRUE(decimal_true <= decimal_true);
            VERIFY_IS_FALSE(decimal_true > decimal_true);
            VERIFY_IS_TRUE(decimal_true >= decimal_true);
        }

        TEST_METHOD(compare_int16)
        {
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt16(static_cast<std::int16_t>(-32109)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt16(static_cast<std::int16_t>(32109)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt32(static_cast<std::int32_t>(-1234567890)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt32(static_cast<std::int32_t>(1234567890)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt64(static_cast<std::int64_t>(-1234567890123456789)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt64(static_cast<std::int64_t>(1234567890123456789)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt8(static_cast<std::uint8_t>(123)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt8(static_cast<std::uint8_t>(234)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt16(static_cast<std::uint16_t>(32109)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt16(static_cast<std::uint16_t>(65432)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt32(static_cast<std::uint32_t>(1234567890)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt32(static_cast<std::uint32_t>(4019283756)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt64(static_cast<std::uint64_t>(0x1234567890ABCDEF)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromUInt64(static_cast<std::uint64_t>(0xFEDCBA0987654321)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromSingle(static_cast<float>(-1.25)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromSingle(static_cast<float>(1.25)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromDouble(static_cast<double>(-1.25)) };
            winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromDouble(static_cast<double>(1.25)) };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            const winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"-12.345") };
            const winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"12.345") };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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
            const winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"-12.345") };
            const winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"12.345") };
            VERIFY_ARE_EQUAL(0, left.Compare(left));
            VERIFY_ARE_EQUAL(0, right.Compare(right));
            VERIFY_ARE_EQUAL(-1, left.Compare(right));
            VERIFY_ARE_EQUAL(1, right.Compare(left));

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

        TEST_METHOD(negate)
        {
            winrt::Microsoft::Windows::Foundation::Decimal zero{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"0" }) };
            winrt::Microsoft::Windows::Foundation::Decimal pos{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"12.345" }) };
            winrt::Microsoft::Windows::Foundation::Decimal neg{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"-12.345" }) };

            const auto zero_value{ zero.Negate() };
            VERIFY_IS_TRUE(zero_value == zero);
            VERIFY_IS_TRUE(zero_value != pos);
            VERIFY_IS_TRUE(zero_value != neg);
            VERIFY_IS_TRUE(zero_value < pos);
            VERIFY_IS_TRUE(zero_value > neg);

            const auto pos_value{ neg.Negate() };
            VERIFY_IS_TRUE(pos_value != zero);
            VERIFY_IS_TRUE(pos_value == pos);
            VERIFY_IS_TRUE(pos_value != neg);
            VERIFY_IS_TRUE(pos_value > zero);
            VERIFY_IS_TRUE(pos_value > neg);

            const auto neg_value{ pos.Negate() };
            VERIFY_IS_TRUE(neg_value != zero);
            VERIFY_IS_TRUE(neg_value != pos);
            VERIFY_IS_TRUE(neg_value == neg);
            VERIFY_IS_TRUE(neg_value < zero);
            VERIFY_IS_TRUE(neg_value < pos);
        }

        TEST_METHOD(abs)
        {
            winrt::Microsoft::Windows::Foundation::Decimal zero{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"0" }) };
            winrt::Microsoft::Windows::Foundation::Decimal pos{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"12.345" }) };
            winrt::Microsoft::Windows::Foundation::Decimal neg{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"-12.345" }) };

            const auto zero_value{ zero.Abs() };
            VERIFY_IS_TRUE(zero_value == zero);
            VERIFY_IS_TRUE(zero_value != pos);
            VERIFY_IS_TRUE(zero_value != neg);
            VERIFY_IS_TRUE(zero_value < pos);
            VERIFY_IS_TRUE(zero_value > neg);

            const auto pos_value{ pos.Abs() };
            VERIFY_IS_TRUE(pos_value != zero);
            VERIFY_IS_TRUE(pos_value == pos);
            VERIFY_IS_TRUE(pos_value != neg);
            VERIFY_IS_TRUE(pos_value > zero);
            VERIFY_IS_TRUE(pos_value > neg);

            const auto neg_value{ neg.Abs() };
            VERIFY_IS_TRUE(neg_value != zero);
            VERIFY_IS_TRUE(neg_value == pos);
            VERIFY_IS_TRUE(neg_value != neg);
            VERIFY_IS_TRUE(neg_value > zero);
            VERIFY_IS_TRUE(neg_value == pos);
        }

        TEST_METHOD(fix)
        {
            winrt::Microsoft::Windows::Foundation::Decimal zero{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"0" }) };
            const auto value{ zero.Fix() };
            VERIFY_IS_TRUE(value == zero);

            winrt::Microsoft::Windows::Foundation::Decimal pos{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"12.345" }) };
            winrt::Microsoft::Windows::Foundation::Decimal pos_fix{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"12" }) };
            const auto pos_value{ pos.Fix() };
            VERIFY_IS_TRUE(pos_value == pos_fix);

            winrt::Microsoft::Windows::Foundation::Decimal neg{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"-12.345" }) };
            winrt::Microsoft::Windows::Foundation::Decimal neg_fix{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"-12" }) };
            const auto neg_value{ neg.Fix() };
            VERIFY_IS_TRUE(neg_value == neg_fix);
        }

        TEST_METHOD(integer)
        {
            winrt::Microsoft::Windows::Foundation::Decimal zero{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"0" }) };
            const auto value{ zero.Integer() };
            VERIFY_IS_TRUE(value == zero);

            winrt::Microsoft::Windows::Foundation::Decimal pos{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"12.345" }) };
            winrt::Microsoft::Windows::Foundation::Decimal pos_integer{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"12" }) };
            const auto pos_value{ pos.Integer() };
            VERIFY_IS_TRUE(pos_value == pos_integer);

            winrt::Microsoft::Windows::Foundation::Decimal neg{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"-12.345" }) };
            winrt::Microsoft::Windows::Foundation::Decimal neg_integer{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(winrt::hstring{ L"-13" }) };
            const auto neg_value{ neg.Integer() };
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
                winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(leftString) };
                const winrt::hstring rightString{ value.right };
                winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                winrt::Microsoft::Windows::Foundation::Decimal expected{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(expectedString) };
                const winrt::Microsoft::Windows::Foundation::Decimal result{ left.Add(right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Add %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result.ToString().c_str(), expected.ToString().c_str()));

                winrt::Microsoft::Windows::Foundation::Decimal result2{ left };
                result2.AddAssign(right);
                VERIFY_ARE_EQUAL(expected, result2, WEX::Common::String().Format(L"%s AddAssign %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result2.ToString().c_str(), expected.ToString().c_str()));
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
                winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(leftString) };
                const winrt::hstring rightString{ value.right };
                winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                winrt::Microsoft::Windows::Foundation::Decimal expected{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(expectedString) };
                const winrt::Microsoft::Windows::Foundation::Decimal result{ left.Sub(right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Sub %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result.ToString().c_str(), expected.ToString().c_str()));

                winrt::Microsoft::Windows::Foundation::Decimal result2{ left };
                result2.SubAssign(right);
                VERIFY_ARE_EQUAL(expected, result2, WEX::Common::String().Format(L"%s SubAssign %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result2.ToString().c_str(), expected.ToString().c_str()));
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
                winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(leftString) };
                const winrt::hstring rightString{ value.right };
                winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                winrt::Microsoft::Windows::Foundation::Decimal expected{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(expectedString) };
                const winrt::Microsoft::Windows::Foundation::Decimal result{ left.Mul(right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Mul %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result.ToString().c_str(), expected.ToString().c_str()));

                winrt::Microsoft::Windows::Foundation::Decimal result2{ left };
                result2.MulAssign(right);
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s MulAssign %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result2.ToString().c_str(), expected.ToString().c_str()));
            }
        }

        TEST_METHOD(operator_divide)
        {
            try
            {
                winrt::Microsoft::Windows::Foundation::Decimal data{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt32(123) };
                winrt::Microsoft::Windows::Foundation::Decimal zero{};
                const auto result{ data.Div(zero) };
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
                const winrt::hstring leftString{ value.left };
                winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(leftString) };
                const winrt::hstring rightString{ value.right };
                winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                winrt::Microsoft::Windows::Foundation::Decimal expected{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(expectedString) };
                const winrt::Microsoft::Windows::Foundation::Decimal result{ left.Div(right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Div %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result.ToString().c_str(), expected.ToString().c_str()));

                winrt::Microsoft::Windows::Foundation::Decimal result2{ left };
                result2.DivAssign(right);
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s DivAssign %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result2.ToString().c_str(), expected.ToString().c_str()));
            }
        }

        TEST_METHOD(operator_mod)
        {
            try
            {
                winrt::Microsoft::Windows::Foundation::Decimal data{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromInt32(123) };
                winrt::Microsoft::Windows::Foundation::Decimal zero{};
                const auto result{ data.Mod(zero) };
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
                const winrt::hstring leftString{ value.left };
                winrt::Microsoft::Windows::Foundation::Decimal left{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(leftString) };
                const winrt::hstring rightString{ value.right };
                winrt::Microsoft::Windows::Foundation::Decimal right{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(rightString) };
                const winrt::hstring expectedString{ value.result };
                winrt::Microsoft::Windows::Foundation::Decimal expected{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(expectedString) };
                const winrt::Microsoft::Windows::Foundation::Decimal result{ left.Mod(right) };
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s Mod %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result.ToString().c_str(), expected.ToString().c_str()));

                winrt::Microsoft::Windows::Foundation::Decimal result2{ left };
                result2.ModAssign(right);
                VERIFY_ARE_EQUAL(expected, result, WEX::Common::String().Format(L"%s ModAssign %s = %s vs %s",
                    left.ToString().c_str(), right.ToString().c_str(), result2.ToString().c_str(), expected.ToString().c_str()));
            }
        }

        TEST_METHOD(operator_round)
        {
            const winrt::Microsoft::Windows::Foundation::Decimal n_1_888{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"1.888") };
            const winrt::Microsoft::Windows::Foundation::Decimal n_neg1_888{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"-1.888") };
            const winrt::Microsoft::Windows::Foundation::Decimal n_1_25{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"1.25") };
            const winrt::Microsoft::Windows::Foundation::Decimal n_neg1_25{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"-1.25") };

            const winrt::Microsoft::Windows::Foundation::Decimal n_2{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"2") };
            const winrt::Microsoft::Windows::Foundation::Decimal n_1_9{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"1.9") };
            const winrt::Microsoft::Windows::Foundation::Decimal n_1_89{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"1.89") };
            const winrt::Microsoft::Windows::Foundation::Decimal n_neg1_9{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"1.9") };
            const winrt::Microsoft::Windows::Foundation::Decimal n_neg1_89{ winrt::Microsoft::Windows::Foundation::Decimal::CreateFromString(L"1.89") };

            const winrt::Microsoft::Windows::Foundation::Decimal n_1_888_round_0{ n_1_888.Round(0) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                n_1_888.ToString().c_str(), n_1_888_round_0.ToString().c_str(), n_2.ToString().c_str()));

            const winrt::Microsoft::Windows::Foundation::Decimal n_1_888_round_1{ n_1_888.Round(1) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                n_1_888.ToString().c_str(), n_1_888_round_1.ToString().c_str(), n_1_9.ToString().c_str()));

            const winrt::Microsoft::Windows::Foundation::Decimal n_1_888_round_2{ n_1_888.Round(2) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                n_1_888.ToString().c_str(), n_1_888_round_2.ToString().c_str(), n_1_89.ToString().c_str()));

            const winrt::Microsoft::Windows::Foundation::Decimal n_1_888_round_3{ n_1_888.Round(3) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                n_1_888.ToString().c_str(), n_1_888_round_3.ToString().c_str(), n_1_888.ToString().c_str()));

            const winrt::Microsoft::Windows::Foundation::Decimal n_1_888_round_4{ n_1_888.Round(4) };
            VERIFY_ARE_EQUAL(n_2, n_1_888_round_0, WEX::Common::String().Format(L"%s.Round(0) = %s vs %s",
                n_1_888.ToString().c_str(), n_1_888_round_4.ToString().c_str(), n_1_888.ToString().c_str()));
        }
    };
}
