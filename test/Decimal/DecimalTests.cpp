// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <decimal.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

static const winrt::hstring null_hstring;

namespace Test::ApplicationData::Tests
{
    class ApplicationDataTests
    {
    public:
        BEGIN_TEST_CLASS(ApplicationDataTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TD::DumpExecutionContext();
            ::TB::Setup();
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

        TEST_METHOD(ctor_to_assign_string)
        {
            //TODO
        }

        TEST_METHOD(compare_bool)
        {
            //TODO
        }

        TEST_METHOD(compare_char)
        {
            //TODO
        }

        TEST_METHOD(compare_int16)
        {
            //TODO
        }

        TEST_METHOD(compare_int32)
        {
            //TODO
        }

        TEST_METHOD(compare_int64)
        {
            //TODO
        }

        TEST_METHOD(compare_uint8)
        {
            //TODO
        }

        TEST_METHOD(compare_uint16)
        {
            //TODO
        }

        TEST_METHOD(compare_uint32)
        {
            //TODO
        }

        TEST_METHOD(compare_uint64)
        {
            //TODO
        }

        TEST_METHOD(compare_float)
        {
            //TODO
        }

        TEST_METHOD(compare_double)
        {
            //TODO
        }

        TEST_METHOD(compare_long)
        {
            //TODO
        }

        TEST_METHOD(compare_ulong)
        {
            //TODO
        }

        TEST_METHOD(compare_string)
        {
            //TODO
        }

        TEST_METHOD(operator_pos)
        {
            //TODO
        }

        TEST_METHOD(operator_neg)
        {
            //TODO
        }

        TEST_METHOD(abs)
        {
            //TODO
        }

        TEST_METHOD(fix)
        {
            //TODO
        }

        TEST_METHOD(integer)
        {
            //TODO
        }

        TEST_METHOD(operator_add)
        {
            //TODO
        }

        TEST_METHOD(operator_subtract)
        {
            //TODO
        }

        TEST_METHOD(operator_multiply)
        {
            //TODO
        }

        TEST_METHOD(operator_divide)
        {
            //TODO
        }

        TEST_METHOD(operator_modulo)
        {
            //TODO
        }

        TEST_METHOD(operator_round)
        {
            //TODO
        }
    };
}
