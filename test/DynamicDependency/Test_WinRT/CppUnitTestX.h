// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<> inline std::wstring ToString<winrt::hstring>(const winrt::hstring& t)
	{
	    RETURN_WIDE_STRING(t.c_str());
	}

	template<> inline std::wstring ToString<winrt::hstring>(const winrt::hstring* t)
	{
	    if (NULL == t)
	    {
	        return std::wstring(L"(NULL)");
        }
	    RETURN_WIDE_STRING(t->c_str());
	}
	template<> inline std::wstring ToString<winrt::hstring>(winrt::hstring* t)
	{
	    if (NULL == t)
	    {
	        return std::wstring(L"(NULL)");
        }
	    RETURN_WIDE_STRING(t->c_str());
	}

    class AssertX
    {
    public:
		static void AreEqual(const winrt::hstring& expected, const winrt::hstring& actual, const char* message, const __LineInfo* pLineInfo = NULL)
		{
			Assert::AreEqual(expected.c_str(), actual.c_str(), message, pLineInfo);
		}

		static void AreEqual(const winrt::hstring& expected, const winrt::hstring& actual, const wchar_t* message, const __LineInfo* pLineInfo = NULL)
		{
			Assert::AreEqual(expected.c_str(), actual.c_str(), message, pLineInfo);
		}

		static void AreEqual(const winrt::hstring& expected, const winrt::hstring& actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			Assert::AreEqual(expected.c_str(), actual.c_str(), ignoreCase, message, pLineInfo);
		}

		static void AreNotEqual(const winrt::hstring& expected, const winrt::hstring& actual, const char* message, const __LineInfo* pLineInfo = NULL)
		{
			Assert::AreNotEqual(expected.c_str(), actual.c_str(), message, pLineInfo);
		}

		static void AreNotEqual(const winrt::hstring& expected, const winrt::hstring& actual, const wchar_t* message, const __LineInfo* pLineInfo = NULL)
		{
			Assert::AreNotEqual(expected.c_str(), actual.c_str(), message, pLineInfo);
		}

		static void AreNotEqual(const winrt::hstring& expected, const winrt::hstring& actual, bool ignoreCase = false, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			Assert::AreNotEqual(expected.c_str(), actual.c_str(), ignoreCase, message, pLineInfo);
		}

		static void Succeeded(HRESULT hr, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			Assert::IsTrue(SUCCEEDED(hr), message, pLineInfo);
		}

		static void Failed(HRESULT hr, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
		{
			Assert::IsTrue(FAILED(hr), message, pLineInfo);
		}
    };
}
