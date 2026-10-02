// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <windows.h>
#include <WexTestClass.h>
#include "mrm/BaseInternal.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;
using namespace Microsoft::Resources;

namespace UnitTests
{

class ChooseBestEncodingUnitTests : public WEX::TestClass<ChooseBestEncodingUnitTests>
{
public:
    TEST_CLASS(ChooseBestEncodingUnitTests);

    TEST_METHOD(AllAsciiResultsInAscii);
    TEST_METHOD(Utf8AndUtf16SameLengthExcludingNullResultsInUtf8);
    TEST_METHOD(Utf8AndUtf16SameLengthIncludingNullResultsInUtf16);
    TEST_METHOD(ShorterInUtf8);
    TEST_METHOD(ShorterInUtf16);
    TEST_METHOD(SingleAsciiCharacterReturnsAscii);
    TEST_METHOD(DoubleAsciiCharacterReturnsAscii);
    TEST_METHOD(SingleUnicodeCharacter);
    TEST_METHOD(DoubleUnicodeCharacter);
    TEST_METHOD(UTF16StringsViaCodePoints);
    TEST_METHOD(UTF8StringsViaCodePoints);
    TEST_METHOD(AsciiStringsViaCodePoints);
    TEST_METHOD(InvalidCharactersReturnUtf16);

private:
    PWSTR GetEncodingNameString(_In_ DEFSTRING_ENCODING encoding);

#pragma prefast(push)
#pragma prefast(disable : __WARNING_SPEC_INVALID_SYNTAX2, "The buffer syntax confuses prefast.");

    void InsertCharacterIntoWideStringWithoutTerminating(
        _In_ unsigned int codePoint,
        _Out_writes_to_(cchBuffer, *cchWritten) wchar_t* psBuffer,
        _In_range_(>=, 2) unsigned int cchBuffer,
        _Deref_out_range_(1, 2) unsigned int* cchWritten);

#pragma prefast(pop)

    void ValidateStringFromCodePoints(
        _In_reads_(cCodePoints) unsigned int* codePoints,
        _In_range_(1, 20) unsigned int cCodePoints,
        _In_ DEFSTRING_ENCODING expectedEncoding);

    void CheckForAndDisplayFailure(_In_ DEFSTRING_ENCODING expectedEncoding, _In_ DEFSTRING_ENCODING actualEncoding);

    unsigned int GetUtf16ByteCount(_In_ unsigned int codePoint);
    unsigned int GetUtf8ByteCount(_In_ unsigned int codePoint);

    bool IsValidCodePoint(_In_ unsigned int codePoint);

    static const unsigned int Utf16BasicPlaneFirstBatchStart = 0x0;
    static const unsigned int Utf16BasicPlaneFirstBatchEnd = 0xD7FF;

    static const unsigned int Utf16BasicPlaneSecondBatchStart = 0xE000;
    static const unsigned int Utf16BasicPlaneSecondBatchEnd = 0xFFFF;

    static const unsigned int Utf16SupplementaryPlaneStart = 0x10000;
    static const unsigned int Utf16SupplementaryPlaneEnd = 0x10FFFF;

    static const unsigned int Utf8OneByteStart = 0x0;
    static const unsigned int Utf8OneByteEnd = 0x7F;

    static const unsigned int Utf8TwoByteStart = 0x80;
    static const unsigned int Utf8TwoByteEnd = 0x7FF;

    static const unsigned int Utf8ThreeByteStart = 0x800;
    static const unsigned int Utf8ThreeByteEnd = 0xFFFF;

    static const unsigned int Utf8FourByteStart = 0x10000;
    static const unsigned int Utf8FourByteEnd = 0x10FFFF;
};

PWSTR ChooseBestEncodingUnitTests::GetEncodingNameString(_In_ DEFSTRING_ENCODING encoding)
{
    switch (encoding)
    {
    case DEFSTRING_ENCODING_ASCII:
        return L"ASCII";
    case DEFSTRING_ENCODING_UTF8:
        return L"UTF-8";
    case DEFSTRING_ENCODING_UTF16:
        return L"UTF-16";
    default:
        return L"Unknown";
    }
}

#pragma prefast(push)
#pragma prefast(disable : __WARNING_SPEC_INVALID_SYNTAX2, "The buffer syntax confuses prefast.");

void ChooseBestEncodingUnitTests::InsertCharacterIntoWideStringWithoutTerminating(
    _In_ unsigned int codePoint,
    _Out_writes_to_(cchBuffer, *cchWriten) wchar_t* psBuffer,
    _In_range_(>=, 2) unsigned int cchBuffer,
    _Deref_out_range_(1, 2) unsigned int* cchWritten)
{
    unsigned int utf16ByteCount = GetUtf16ByteCount(codePoint);

    if (cchBuffer < 2)
    {

        VERIFY_IS_TRUE(cchBuffer >= 2, L"Test bug! Buffer too small.");

        // OACR doesn't realize that  the above verify will terimate execution.
        *cchWritten = 1;
        *psBuffer = L'\0';
    }
    else
    {

        if (utf16ByteCount == 2)
        {

            psBuffer[0] = static_cast<wchar_t>(codePoint);
            *cchWritten = 1;
        }
        else
        {

            static const unsigned int mask = ((1 << 10) - 1);

            psBuffer[0] = static_cast<wchar_t>(((((codePoint - 0x10000) >> 10) & mask) + 0xD800));
            psBuffer[1] = static_cast<wchar_t>(((codePoint - 0x10000) & mask) + 0xDC00);
            *cchWritten = 2;
        }
    }
}

#pragma prefast(pop)

// Creates a string from code points and validates the length.
void ChooseBestEncodingUnitTests::ValidateStringFromCodePoints(
    _In_reads_(cCodePoints) unsigned int* codePoints,
    _In_range_(1, 20) unsigned int cCodePoints,
    _In_ DEFSTRING_ENCODING expectedEncoding)
{
    wchar_t szStringFromNumber[MAX_PATH];
    unsigned int cchWritten;
    unsigned int cchLeft = ARRAYSIZE(szStringFromNumber);
    wchar_t* psCurrentBufferPosition = szStringFromNumber;

    for (unsigned int i = 0; i < cCodePoints; i++)
    {

        InsertCharacterIntoWideStringWithoutTerminating(codePoints[i], psCurrentBufferPosition, cchLeft, &cchWritten);

        psCurrentBufferPosition += cchWritten;
        cchLeft -= cchWritten;
    }

    *psCurrentBufferPosition = L'\0';

    DEFSTRING_ENCODING actualEncoding = DefString_ChooseBestEncoding(szStringFromNumber);
    PWSTR pszExpectedEncoding = GetEncodingNameString(expectedEncoding);

    String formatter;
    Log::Comment(formatter.Format(L"Testing %s with expected encoding %s.", szStringFromNumber, pszExpectedEncoding));
    CheckForAndDisplayFailure(expectedEncoding, actualEncoding);
}

void ChooseBestEncodingUnitTests::CheckForAndDisplayFailure(
    _In_ DEFSTRING_ENCODING expectedEncoding,
    _In_ DEFSTRING_ENCODING actualEncoding)
{
    if (actualEncoding != expectedEncoding)
    {

        String formatter;
        PWSTR pszExpectedEncoding = GetEncodingNameString(expectedEncoding);
        PWSTR pszActualEncoding = GetEncodingNameString(actualEncoding);

        Log::Error(formatter.Format(L"Expected %s, got %s.", pszExpectedEncoding, pszActualEncoding));
        VERIFY_ARE_EQUAL(actualEncoding, expectedEncoding);
    }
}

// This supports invalid code points since we have tests for that.
unsigned int ChooseBestEncodingUnitTests::GetUtf16ByteCount(_In_ unsigned int codePoint)
{
    if (codePoint >= Utf16SupplementaryPlaneStart && codePoint <= Utf16SupplementaryPlaneEnd)
    {

        return 4;
    }
    else
    {

        return 2;
    }
}

// Returns 0 for invalid code points. Shouldn't be hit because our invalid code point tests should not ask.
unsigned int ChooseBestEncodingUnitTests::GetUtf8ByteCount(_In_ unsigned int codePoint)
{
    if (codePoint <= Utf8OneByteEnd)
    {

        return 1;
    }
    else if (codePoint >= Utf8TwoByteStart && codePoint <= Utf8TwoByteEnd)
    {

        return 2;
    }
    else if (codePoint >= Utf8ThreeByteStart && codePoint <= Utf8ThreeByteEnd)
    {

        return 3;
    }
    else if (codePoint >= Utf8FourByteStart && codePoint <= Utf8FourByteEnd)
    {

        return 4;
    }
    else
    {

        VERIFY_IS_TRUE(false, L"Test bug! Unexpected invalid code point.");
        return 0;
    }
}

bool ChooseBestEncodingUnitTests::IsValidCodePoint(_In_ unsigned int codePoint)
{
    if ((codePoint <= Utf16BasicPlaneFirstBatchEnd) ||
        (codePoint >= Utf16BasicPlaneSecondBatchStart && codePoint <= Utf16BasicPlaneSecondBatchEnd))
    {

        return true;
    }
    else if (codePoint >= Utf16SupplementaryPlaneStart && codePoint <= Utf16SupplementaryPlaneEnd)
    {

        return true;
    }
    else
    {

        return false;
    }
}

// Strings using only ASCII characters should go to ASCII because it is both small and easy to decode.
void ChooseBestEncodingUnitTests::AllAsciiResultsInAscii()
{
    PCWSTR const c_pszStringsToTest[] = {
        L"test",
        L"",
        L"a",
        L"1",
        L"Z",
        L"+",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {

        Log::Comment(String().Format(L"Testing %s.", c_pszStringsToTest[i]));

        CheckForAndDisplayFailure(DEFSTRING_ENCODING_ASCII, DefString_ChooseBestEncoding(c_pszStringsToTest[i]));
    }
}

// Same character strings go to UTF-8 over UTF-16 because UTF-8 uses a single-byte NULL terminator.
void ChooseBestEncodingUnitTests::Utf8AndUtf16SameLengthExcludingNullResultsInUtf8()
{
    PCWSTR const c_pszStringsToTest[] = {
        L"©",
        L"©Ö",
        L"©ÖĆ",
        L"ûhæ",
        L"f☺", //  1 + 3 vs 2 + 2
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {

        Log::Comment(String().Format(L"Testing %s.", c_pszStringsToTest[i]));

        CheckForAndDisplayFailure(DEFSTRING_ENCODING_UTF8, DefString_ChooseBestEncoding(c_pszStringsToTest[i]));
    }
}

void ChooseBestEncodingUnitTests::ShorterInUtf8()
{
    PCWSTR const c_pszStringsToTest[] = {
        L"fo☺",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {

        Log::Comment(String().Format(L"Testing %s.", c_pszStringsToTest[i]));

        CheckForAndDisplayFailure(DEFSTRING_ENCODING_UTF8, DefString_ChooseBestEncoding(c_pszStringsToTest[i]));
    }
}

void ChooseBestEncodingUnitTests::Utf8AndUtf16SameLengthIncludingNullResultsInUtf16()
{
    PCWSTR const c_pszStringsToTest[] = {
        L"©☺", // 2 + 2 + 2 vs 2 + 3 + 1
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {

        Log::Comment(String().Format(L"Testing %s.", c_pszStringsToTest[i]));

        CheckForAndDisplayFailure(DEFSTRING_ENCODING_UTF16, DefString_ChooseBestEncoding(c_pszStringsToTest[i]));
    }
}

void ChooseBestEncodingUnitTests::ShorterInUtf16()
{
    PCWSTR const c_pszStringsToTest[] = {
        // These are three bytes each in UTF-8 and two in UTF-16.
        L"┌╟●☺",
        L"ﬕײַﬥ﬩",
        L"ﬕײַⱶⱩⱭ",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {

        Log::Comment(String().Format(L"Testing %s.", c_pszStringsToTest[i]));

        CheckForAndDisplayFailure(DEFSTRING_ENCODING_UTF16, DefString_ChooseBestEncoding(c_pszStringsToTest[i]));
    }
}

// Test all permutations of one character ASCII strings. Those should always be ASCII.
void ChooseBestEncodingUnitTests::SingleAsciiCharacterReturnsAscii()
{
    bool fAllCorrect = true;

    for (unsigned int i = 0; i < 128; i++)
    {

        wchar_t szAsciiOneChar[2] = {static_cast<wchar_t>(i), L'\0'};

        DEFSTRING_ENCODING actualEncoding = DefString_ChooseBestEncoding(szAsciiOneChar);

        // Only display this on error.
        if (actualEncoding != DEFSTRING_ENCODING_ASCII)
        {

            String formatter;
            Log::Error(formatter.Format(L"String %s failed.", szAsciiOneChar));

            CheckForAndDisplayFailure(DEFSTRING_ENCODING_ASCII, actualEncoding);
            fAllCorrect = false;
        }
    }

    if (fAllCorrect)
    {

        Log::Comment(L"All single-character ASCII strings check out.");
    }
}

// Test all permutations of two character ASCII strings. Those should always be ASCII.
void ChooseBestEncodingUnitTests::DoubleAsciiCharacterReturnsAscii()
{
    bool fAllCorrect = true;

    for (unsigned int i = 0; i < 128; i++)
    {

        for (unsigned int j = 0; j < 128; j++)
        {

            wchar_t szAsciiTwoChars[3] = {static_cast<wchar_t>(i), static_cast<wchar_t>(j), L'\0'};

            DEFSTRING_ENCODING actualEncoding = DefString_ChooseBestEncoding(szAsciiTwoChars);

            // Only display this on error.
            if (actualEncoding != DEFSTRING_ENCODING_ASCII)
            {

                String formatter;
                Log::Error(formatter.Format(L"String %s failed.", szAsciiTwoChars));

                CheckForAndDisplayFailure(DEFSTRING_ENCODING_ASCII, actualEncoding);
                fAllCorrect = false;
            }
        }
    }

    if (fAllCorrect)
    {

        Log::Comment(L"All two-character ASCII strings check out.");
    }
}

// Test a sample of single-character UNICODE strings.
void ChooseBestEncodingUnitTests::SingleUnicodeCharacter()
{
    bool fAllCorrect = true;

    for (unsigned int i = 1; i <= Utf16SupplementaryPlaneEnd; i += 100)
    {

        if (IsValidCodePoint(i))
        {

            wchar_t szUtf16[3];
            unsigned int utf16ByteCount = GetUtf16ByteCount(i);
            unsigned int utf8ByteCount = GetUtf8ByteCount(i);

            unsigned int cchWritten;
            InsertCharacterIntoWideStringWithoutTerminating(i, szUtf16, ARRAYSIZE(szUtf16), &cchWritten);

            szUtf16[cchWritten] = L'\0';

            DEFSTRING_ENCODING expectedEncoding;
            if (utf8ByteCount == 1)
            {
                // One-byte UTF8 characters should be encoded as ASCII.
                expectedEncoding = DEFSTRING_ENCODING_ASCII;
            }
            else
            {
                // Account for NULL, and when equal pick UTF-16.
                expectedEncoding = (utf8ByteCount + 1 < utf16ByteCount + 2) ? DEFSTRING_ENCODING_UTF8 : DEFSTRING_ENCODING_UTF16;
            }

            DEFSTRING_ENCODING actualEncoding = DefString_ChooseBestEncoding(szUtf16);

            // Only display this on error.
            if (expectedEncoding != actualEncoding)
            {

                String formatter;
                Log::Error(formatter.Format(L"String %s (code point %x) failed.", szUtf16, i));

                CheckForAndDisplayFailure(expectedEncoding, actualEncoding);
                fAllCorrect = false;
            }
        }
    }

    if (fAllCorrect)
    {

        Log::Comment(L"One-character UNICODE strings check out.");
    }
}

// Test a sample of double-character UNICODE strings.
void ChooseBestEncodingUnitTests::DoubleUnicodeCharacter()
{
    bool fAllCorrect = true;

    for (unsigned int i = 100; i <= Utf16SupplementaryPlaneEnd; i += 1000)
    {

        // Different set of strings.
        for (unsigned int j = 50; j <= Utf16SupplementaryPlaneEnd; j += 3333)
        {

            if (IsValidCodePoint(i) && IsValidCodePoint(j))
            {

                wchar_t szUtf16[5];
                unsigned int utf16ByteCountOne = GetUtf16ByteCount(i);
                unsigned int utf8ByteCountOne = GetUtf8ByteCount(i);

                unsigned int utf16ByteCountTwo = GetUtf16ByteCount(j);
                unsigned int utf8ByteCountTwo = GetUtf8ByteCount(j);

                unsigned int cchWritten;
                unsigned int cchLeft = ARRAYSIZE(szUtf16);
                wchar_t* psCurrentBufferPosition = szUtf16;

                InsertCharacterIntoWideStringWithoutTerminating(i, psCurrentBufferPosition, cchLeft, &cchWritten);

                psCurrentBufferPosition += cchWritten;
                cchLeft -= cchWritten;

                InsertCharacterIntoWideStringWithoutTerminating(j, psCurrentBufferPosition, cchLeft, &cchWritten);

                psCurrentBufferPosition[cchWritten] = L'\0';

                DEFSTRING_ENCODING expectedEncoding;
                if (utf8ByteCountOne == 1 && utf8ByteCountTwo == 1)
                {
                    // One-byte UTF8 characters should be encoded as ASCII.
                    expectedEncoding = DEFSTRING_ENCODING_ASCII;
                }
                else
                {
                    // Account for NULL, and when equal pick UTF-16.
                    expectedEncoding = (utf8ByteCountOne + utf8ByteCountTwo + 1 < utf16ByteCountOne + utf16ByteCountTwo + 2) ?
                                           DEFSTRING_ENCODING_UTF8 :
                                           DEFSTRING_ENCODING_UTF16;
                }

                DEFSTRING_ENCODING actualEncoding = DefString_ChooseBestEncoding(szUtf16);

                // Only display this on error.
                if (expectedEncoding != actualEncoding)
                {

                    String formatter;
                    Log::Error(formatter.Format(L"String %s failed.", szUtf16));

                    CheckForAndDisplayFailure(expectedEncoding, actualEncoding);
                    fAllCorrect = false;
                }
            }
        }
    }

    if (fAllCorrect)
    {

        Log::Comment(L"Two-character UNICODE strings check out.");
    }
}

// Tests a set of strings that will encode to UTF8.
void ChooseBestEncodingUnitTests::UTF8StringsViaCodePoints()
{
    unsigned int stringOne[] = {128}; // UTF-8 wins because the NULL terminator is smaller
    unsigned int stringTwo[] = {10, 11, 12, 200};
    unsigned int stringThree[] = {0x80, 0x81, 0x82, 0x7FF};
    unsigned int stringFour[] = {0x10000, 0x10001, 0x10002, 0x10003}; // Smaller NULL.
    unsigned int stringFive[] = {1, 2, 1000, 10000};
    unsigned int stringSix[] = {0x700, 0x701, 0x7FF, 0x800, 0x10FFFF, 1};

    ValidateStringFromCodePoints(stringOne, ARRAYSIZE(stringOne), DEFSTRING_ENCODING_UTF8);
    ValidateStringFromCodePoints(stringTwo, ARRAYSIZE(stringTwo), DEFSTRING_ENCODING_UTF8);
    ValidateStringFromCodePoints(stringThree, ARRAYSIZE(stringThree), DEFSTRING_ENCODING_UTF8);
    ValidateStringFromCodePoints(stringFour, ARRAYSIZE(stringFour), DEFSTRING_ENCODING_UTF8);
    ValidateStringFromCodePoints(stringFive, ARRAYSIZE(stringFive), DEFSTRING_ENCODING_UTF8);
    ValidateStringFromCodePoints(stringSix, ARRAYSIZE(stringSix), DEFSTRING_ENCODING_UTF8);
}

// Tests a set of strings that will encode to UTF16.
void ChooseBestEncodingUnitTests::UTF16StringsViaCodePoints()
{
    // To get to UTF-16 you need characters that encode to 3 bytes in UTF-8 but 2 in UTF-16.
    // Those are 0x800 - 0xD7FF and 0xE000 - 0xFFFF.
    // If the string encodes to the same size in both, UTF-16 wins.
    unsigned int stringOne[] = {0x800, 1, 0xD7FF}; // Encodes to 8 in both, so UTF-16 wins.
    unsigned int stringTwo[] = {0x800};
    unsigned int stringThree[] = {0x800, 0x80, 0xD7FF, 0xE000, 0xE000, 0xE001, 0xFFFF};
    unsigned int stringFour[] = {0x800, 0};
    unsigned int stringFive[] = {0x801, 0x10000, 0x10001, 0x10FFFF};
    unsigned int stringSix[] = {0x801, 0x802, 0x10000, 0x10001, 0x10FFFF};

    ValidateStringFromCodePoints(stringOne, ARRAYSIZE(stringOne), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringTwo, ARRAYSIZE(stringTwo), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringThree, ARRAYSIZE(stringThree), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringFour, ARRAYSIZE(stringFour), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringFive, ARRAYSIZE(stringFive), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringSix, ARRAYSIZE(stringSix), DEFSTRING_ENCODING_UTF16);
}

// Tests a set of strings that will encode to ASCII.
void ChooseBestEncodingUnitTests::AsciiStringsViaCodePoints()
{
    // All code points < 128 -> ASCII. 0 ends the string but is supported.
    unsigned int stringOne[] = {1, 2, 3};
    unsigned int stringTwo[] = {1, 2, 127};
    unsigned int stringThree[] = {101, 102, 0, 0xFFFFFFFF}; // Invalid character after the NULL is ignored.
    unsigned int stringFour[] = {127, 90, 100, 1, 127};
    unsigned int stringFive[] = {127, 1, 1, 3, 5, 111};
    unsigned int stringSix[] = {0, 1, 2, 3};

    ValidateStringFromCodePoints(stringOne, ARRAYSIZE(stringOne), DEFSTRING_ENCODING_ASCII);
    ValidateStringFromCodePoints(stringTwo, ARRAYSIZE(stringTwo), DEFSTRING_ENCODING_ASCII);
    ValidateStringFromCodePoints(stringThree, ARRAYSIZE(stringThree), DEFSTRING_ENCODING_ASCII);
    ValidateStringFromCodePoints(stringFour, ARRAYSIZE(stringFour), DEFSTRING_ENCODING_ASCII);
    ValidateStringFromCodePoints(stringFive, ARRAYSIZE(stringFive), DEFSTRING_ENCODING_ASCII);
    ValidateStringFromCodePoints(stringSix, ARRAYSIZE(stringSix), DEFSTRING_ENCODING_ASCII);
}

// The API returns UTF-16 for invalid code points.
void ChooseBestEncodingUnitTests::InvalidCharactersReturnUtf16()
{
    unsigned int stringOne[] = {1, 2, 3, 0xDFFF};
    unsigned int stringTwo[] = {1, 2, 127, 0xDBFF};
    // Manually assembing invalid code points via two characters.
    unsigned int stringThree[] = {101, 102, 1, 0xDC00, 0xDC00}; // First code point beyond lead surrogage range
    unsigned int stringFour[] = {101, 102, 1, 0xDFFF, 0xDC00}; // Last code point beyond lead surrogate range but before BMP starts again.
    unsigned int stringFive[] = {101, 102, 1, 0xD800, 0xDBFF}; // Last code point before trail surrogate range.
    unsigned int stringSix[] = {101, 102, 1, 0xD800, 0xE000}; // First code point past trail surrogate range.

    ValidateStringFromCodePoints(stringOne, ARRAYSIZE(stringOne), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringTwo, ARRAYSIZE(stringTwo), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringThree, ARRAYSIZE(stringThree), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringFour, ARRAYSIZE(stringFour), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringFive, ARRAYSIZE(stringFive), DEFSTRING_ENCODING_UTF16);
    ValidateStringFromCodePoints(stringSix, ARRAYSIZE(stringSix), DEFSTRING_ENCODING_UTF16);
}

class StringConversionUnitTests : public WEX::TestClass<StringConversionUnitTests>
{
public:
    TEST_CLASS(StringConversionUnitTests);

    TEST_METHOD(RoundTripThroughPublicFunctionAscii);
    TEST_METHOD(RoundTripThroughPublicFunctionUtf8);
    TEST_METHOD(InvalidUtf8);
};

// Round trip through public function.
void StringConversionUnitTests::RoundTripThroughPublicFunctionAscii()
{
    PCWSTR const c_pszStringsToTest[] = {
        L"foo",
        L"",
        L"!@#$~19az",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {

        char pszOfficialAscii[MAX_PATH] = {};
        int cbOfficialAscii =
            WideCharToMultiByte(CP_ACP, 0, c_pszStringsToTest[i], -1, pszOfficialAscii, sizeof(pszOfficialAscii), nullptr, nullptr);

        VERIFY_IS_TRUE(cbOfficialAscii > 0);

        if (cbOfficialAscii < 1)
        {
            // OACR doesnt understand the VERIFY macros.
            return;
        }

        pszOfficialAscii[MAX_PATH - 1] = '\0'; // Make OACR happy.

        PWSTR pszUtf16;
        VERIFY_SUCCEEDED(DefString_ConvertAsciiToUtf16(pszOfficialAscii, cbOfficialAscii, &pszUtf16));
        VERIFY_IS_NOT_NULL(pszUtf16);
        VERIFY_ARE_EQUAL(wcslen(pszUtf16) + 1, static_cast<size_t>(cbOfficialAscii));

        VERIFY_ARE_EQUAL(0, memcmp(pszUtf16, c_pszStringsToTest[i], wcslen(c_pszStringsToTest[i])));

        VERIFY_ARE_EQUAL(CSTR_EQUAL, CompareStringOrdinal(c_pszStringsToTest[i], -1, pszUtf16, -1, FALSE));

        _DefFree(pszUtf16);
    }
}

// Round trip through public function.
void StringConversionUnitTests::RoundTripThroughPublicFunctionUtf8()
{
    PCWSTR const c_pszStringsToTest[] = {
        L"foo",
        L"",
        L"!@#$~19az",
        L"©",
        L"ab©cd",
        L"©Ö",
        L"©ÖĆ",
        L"ûhæ",
        L"┌╟●☺",
        L"ﬕײַﬥ﬩",
        L"ﬕײַⱶⱩⱭ",
        L"!1QAﬕײַⱶⱩⱭ",
        L"ûhæ123",
        L"a┌╟●☺a",
        L"11vvﬕײַﬥ﬩",
        L"aﬕײַⱶⱩⱭ18@1",
        // These are compliance test cases.
        L"中文",
        L"⒈①Ⅻㄨㄩ",
        L"啊阿鼾齄",
        L"丂丄狚狛",
        L"狜狝﨨﨩",
        L"ˊˋ˙–〇",
        L"㐀㐁䶴䶵",
        L"𠀀𠀁𪛕𪛖",
        L"བོད་ཡིག   ༀ༁༂༃༄༅ྡྷྣྤྥ",
        L"དབྱངས་ཅན་སྒྲོལ་དཀར། བཀྲ་ཤིས་རྒྱལ།",
        L"ئۇيغۇر تىلى   ;؋ ، ؍ ؎ ؏ؐ   ﻲ ﻳ ﻴ ﻵ ﻶ ﻷ ﻸ ﻹ ﻺ ﻻ",
        L"ۋېڭكقق ھس قك كدسدق د",
        L"ᠮᠣᠩᠭᠣᠯ  ᠦᠰᠦᠭ ᢎᢏᢐᢑᢒᢓᢔᢕᢖᢗ",
        L"ᠣᠺᠵᠡᠵᠺᠰ ᠬᠵᠠᠬᠳᠰᠣᠬᠡᠵᠬ ᠬᠵᠺᠠᠬᠳᠰ ᠺᠬᠣ ᠠ",
        L"ꆈꌠꁱꂷ;ꀀꀁꀂꀃꀄꀅꀆ꓁꓂꓃꓄꓅꓆",
        L"ꉬꄒꐵꄓꐨꐵꄓꐨ",
        L"ᥘᥣᥭᥰ ᥖᥭᥰ ᥖᥬᥲᥑᥨᥒᥰ",
        L"ᦎᦷᦑᦺᦖᦺᧈᦉᦲᧇᦉᦸᧂᦗᧃᦓᦱ",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {

        char pszOfficialUtf8[MAX_PATH] = {};
        int cbOfficialUtf8 =
            WideCharToMultiByte(CP_UTF8, 0, c_pszStringsToTest[i], -1, pszOfficialUtf8, sizeof(pszOfficialUtf8), nullptr, nullptr);

        VERIFY_IS_TRUE(cbOfficialUtf8 > 0);

        if (cbOfficialUtf8 < 1)
        {
            // OACR doesnt understand the VERIFY macros.
            return;
        }

        pszOfficialUtf8[MAX_PATH - 1] = '\0'; // Make OACR happy.

        size_t cchUtf16IncludingNull;
        PWSTR pszUtf16;
        VERIFY_SUCCEEDED(DefString_ConvertUtf8ToUtf16(pszOfficialUtf8, cbOfficialUtf8, &cchUtf16IncludingNull, &pszUtf16));
        VERIFY_IS_NOT_NULL(pszUtf16);
        VERIFY_ARE_EQUAL(cchUtf16IncludingNull, wcslen(pszUtf16) + 1);
        VERIFY_ARE_EQUAL(cchUtf16IncludingNull, wcslen(c_pszStringsToTest[i]) + 1);

        VERIFY_ARE_EQUAL(0, memcmp(pszUtf16, c_pszStringsToTest[i], wcslen(c_pszStringsToTest[i])));

        VERIFY_ARE_EQUAL(CSTR_EQUAL, CompareStringOrdinal(c_pszStringsToTest[i], -1, pszUtf16, -1, FALSE));

        _DefFree(pszUtf16);
    }
}

void StringConversionUnitTests::InvalidUtf8()
{
    // Manually assembing invalid code points.
    char stringOne[] = {0xC0, 0xC0, 0}; // Two byte sequence. Second byte is invalid.
    char stringTwo[] = {1, 0xC0, 0xC0, 128, 0}; // Third byte (second byte of second code point) is invalid.
    char stringThree[] = {0xE0, 0xC0, 0}; // Three byte sequence but only two valid bytes.
    char stringFour[] = {0xE0, 22, 0x80, 0}; // Three byte sequence. Second byte is invalid.
    char stringFive[] = {0xF0, 0xC0, 1, 2, 0}; // Four byte sequence. Second byte is invalid.
    char stringSix[] = {0xF0, 0x80, 0xC0, 0}; // Four byte sequence. Third byte is invalid.
    char stringSeven[] = {0xF0, 0x80, 0x80, 0xC0, 0}; // Four byte sequence. Fourth byte is invalid.
    char stringEight[] = {0xF8, 0x80, 0x80, 0x80, 0x80, 0}; // Deprecated 5 byte sequence.
    char stringNine[] = {0xFC, 0x80, 0x80, 0x80, 0x80, 0x80, 0}; // Deprecated 6 byte sequence.
    size_t cchUtf16IncludingNull;

    PWSTR utf16String;
    HRESULT hr = DefString_ConvertUtf8ToUtf16(stringOne, sizeof(stringOne), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringTwo, sizeof(stringTwo), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringThree, sizeof(stringThree), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringFour, sizeof(stringFour), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringFive, sizeof(stringFive), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringSix, sizeof(stringSix), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringSeven, sizeof(stringSeven), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringEight, sizeof(stringEight), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);

    hr = DefString_ConvertUtf8ToUtf16(stringNine, sizeof(stringNine), &cchUtf16IncludingNull, &utf16String);
    VERIFY_IS_NULL(utf16String);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION));
    VERIFY_ARE_EQUAL(cchUtf16IncludingNull, 0u);
}

} // namespace UnitTests