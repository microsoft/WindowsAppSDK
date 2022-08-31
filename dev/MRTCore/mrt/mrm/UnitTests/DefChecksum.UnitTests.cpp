// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include <WexTestClass.h>
#include "mrm/BaseInternal.h"
#include "Helpers.h"
#include "mrm/Checksums.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;

extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace UnitTests
{

/*!
     * DefChecksum Unit Tests
     */
class DefChecksumUnitTests : public WEX::TestClass<DefChecksumUnitTests>
{
public:
    TEST_CLASS(DefChecksumUnitTests);

    TEST_METHOD(IntegerChecksumTests);
    TEST_METHOD(DataChecksumTests);
    TEST_METHOD(StringChecksumTests);
    BEGIN_TEST_METHOD(AtomPoolChecksumTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DefChecksum.UnitTests.xml#AtomPoolChecksumTests")
    END_TEST_METHOD()
    BEGIN_TEST_METHOD(StringListChecksumTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DefChecksum.UnitTests.xml#StringListChecksumTests")
    END_TEST_METHOD()
    BEGIN_TEST_METHOD(FileChecksumTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DefChecksum.UnitTests.xml#FileChecksumTests")
    END_TEST_METHOD()
    TEST_METHOD(FileChecksumFailsForMissingFile);
};

void DefChecksumUnitTests::IntegerChecksumTests(void)
{
    DefChecksum::Checksum cs1;
    DefChecksum::Checksum cs2;

    // Verify that order changes are detected
    cs1 = cs2 = 0;
    cs1 = DefChecksum::ComputeUInt32Checksum(cs1, 0x12345678);
    cs1 = DefChecksum::ComputeUInt32Checksum(cs1, 0xfedcba98);

    cs2 = DefChecksum::ComputeUInt32Checksum(cs2, 0xfedcba98);
    cs2 = DefChecksum::ComputeUInt32Checksum(cs2, 0x12345678);
    VERIFY_ARE_NOT_EQUAL(cs1, cs2);

    // Verify that adding '0' changes the result
    cs1 = cs2 = 0;
    cs1 = DefChecksum::ComputeUInt32Checksum(cs1, 0x12345678);
    cs1 = DefChecksum::ComputeUInt32Checksum(cs1, 0xfedcba98);

    cs2 = DefChecksum::ComputeUInt32Checksum(cs2, 0x12345678);
    cs2 = DefChecksum::ComputeUInt32Checksum(cs2, 0);
    cs2 = DefChecksum::ComputeUInt32Checksum(cs2, 0xfedcba98);
    VERIFY_ARE_NOT_EQUAL(cs1, cs2);
}

void DefChecksumUnitTests::DataChecksumTests(void)
{
    DefChecksum::Checksum cs1;
    DefChecksum::Checksum cs2;
    BYTE buf1[100];

    SecureZeroMemory(buf1, sizeof(buf1));

    // Verify that length differences are detected
    cs1 = cs2 = 0;
    cs1 = DefChecksum::ComputeChecksum(cs1, buf1, sizeof(buf1));
    cs2 = DefChecksum::ComputeChecksum(cs2, buf1, sizeof(buf1) - 1);
    VERIFY_ARE_NOT_EQUAL(cs1, cs2);
}

void DefChecksumUnitTests::StringChecksumTests(void)
{
    DefChecksum::Checksum cs1;
    DefChecksum::Checksum cs2;

    // Verify that case differences are detected when they should be...
    cs1 = cs2 = 0;
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"String1", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string1", &cs2));
    VERIFY_ARE_NOT_EQUAL(cs1, cs2);

    // ...but not when they shouldn't
    cs1 = cs2 = 0;
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, true, L"String1", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, true, L"string1", &cs2));
    VERIFY_ARE_EQUAL(cs1, cs2);

    // verify that a sequence of identical strings compares identically
    cs1 = cs2 = 0;
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string1", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string2", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string3", &cs1));

    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string1", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string2", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string3", &cs2));
    VERIFY_ARE_EQUAL(cs1, cs2);

    // verify that inserting a NULL into otherwise identical sequences changes the checksum
    cs1 = cs2 = 0;
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string1", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, NULL, &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string2", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string3", &cs1));

    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string1", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string2", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string3", &cs2));
    VERIFY_ARE_NOT_EQUAL(cs1, cs2);

    // verify that inserting an empty string into otherwise identical sequences changes the checksum
    cs1 = cs2 = 0;
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string1", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string2", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string3", &cs1));

    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string1", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string2", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string3", &cs2));
    VERIFY_ARE_NOT_EQUAL(cs1, cs2);

    // verify that NULL & empty string compare differently
    cs1 = cs2 = 0;
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string1", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, NULL, &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string2", &cs1));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs1, false, L"string3", &cs1));

    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string1", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string2", &cs2));
    VERIFY_SUCCEEDED(DefChecksum::ComputeStringChecksum(cs2, false, L"string3", &cs2));
    VERIFY_ARE_NOT_EQUAL(cs1, cs2);
}

void DefChecksumUnitTests::AtomPoolChecksumTests(void)
{
    bool shouldMatch;
    String pool1Description;
    String pool2Description;
    bool pool1IsCaseInsensitive;
    bool pool2IsCaseInsensitive;
    TestDataArray<String> pool1Strings;
    TestDataArray<String> pool2Strings;

    if (FAILED(TestData::TryGetValue(L"ShouldMatch", shouldMatch)) ||
        FAILED(TestData::TryGetValue(L"Pool1Description", pool1Description)) ||
        FAILED(TestData::TryGetValue(L"Pool2Description", pool2Description)) ||
        FAILED(TestData::TryGetValue(L"Pool1IsCaseInsensitive", pool1IsCaseInsensitive)) ||
        FAILED(TestData::TryGetValue(L"Pool2IsCaseInsensitive", pool2IsCaseInsensitive)) ||
        FAILED(TestData::TryGetValue(L"Pool1Strings", pool1Strings)) || FAILED(TestData::TryGetValue(L"Pool2Strings", pool2Strings)))
    {
        Log::Error(L"Couldn't load test data");
        return;
    }

    TestAtomPool pool1;
    if (!pool1.Init(pool1Description, pool1IsCaseInsensitive, pool1Strings, NULL))
    {
        Log::Error(L"Couldn't create test atom pool 1");
        return;
    }

    TestAtomPool pool2;
    if (!pool2.Init(pool2Description, pool2IsCaseInsensitive, pool2Strings, NULL))
    {
        Log::Error(L"Couldn't create test atom pool 2");
        return;
    }

    int compareSize;
    DefChecksum::Checksum cs1 = 0;
    if (SUCCEEDED(TestData::TryGetValue(L"Pool1CompareSize", compareSize)))
    {
        VERIFY_SUCCEEDED(DefChecksum::ComputeAtomPoolChecksum(0, pool1.GetPool(), compareSize, &cs1));
    }
    else
    {
        VERIFY_SUCCEEDED(DefChecksum::ComputeAtomPoolChecksum(0, pool1.GetPool(), &cs1));
    }
    VERIFY(cs1 != 0);

    DefChecksum::Checksum cs2 = 0;
    if (SUCCEEDED(TestData::TryGetValue(L"Pool2CompareSize", compareSize)))
    {
        VERIFY_SUCCEEDED(DefChecksum::ComputeAtomPoolChecksum(0, pool2.GetPool(), compareSize, &cs2));
    }
    else
    {
        VERIFY_SUCCEEDED(DefChecksum::ComputeAtomPoolChecksum(0, pool2.GetPool(), &cs2));
    }
    VERIFY(cs2 != 0);

    if (shouldMatch)
    {
        VERIFY_ARE_EQUAL(cs1, cs2);
    }
    else
    {
        VERIFY_ARE_NOT_EQUAL(cs1, cs2);
    }
}

static void VerifyStringListChecksums(
    _In_ DefChecksum::ChecksumFlags flags,
    _In_ TestStringArray& strings1,
    _In_ TestStringArray& strings2,
    _In_ bool verifyMatch,
    _In_ bool verifyMismatch)
{
    String tmp;

    if (verifyMatch == verifyMismatch)
    {
        if (verifyMatch && verifyMismatch)
        {
            Log::Warning(L"[Test data expects match and mismatch for same value]\n");
            return;
        }
        Log::Warning(tmp.Format(
            L"[%s/%s: Test data expects neither match nor mismatch]\n",
            (((flags & DefChecksum::Checksum_CaseSensitivityMask) == DefChecksum::Checksum_CaseInsensitive) ? L"Case-insensitive" :
                                                                                                              L"Case-sensitive"),
            (((flags & DefChecksum::Checksum_SortMask) == DefChecksum::Checksum_Sorted) ? L"Sorted" : L"Unsorted")));
        return;
    }
    Log::Comment(tmp.Format(
        L"[%s/%s: expect %s]\n",
        (((flags & DefChecksum::Checksum_CaseSensitivityMask) == DefChecksum::Checksum_CaseInsensitive) ? L"Case-insensitive" :
                                                                                                          L"Case-sensitive"),
        (((flags & DefChecksum::Checksum_SortMask) == DefChecksum::Checksum_Sorted) ? L"Sorted" : L"Unsorted"),
        (verifyMatch ? L"Match" : L"Mismatch")));

    if (verifyMatch || verifyMismatch)
    {

        DefChecksum::Checksum cs1;
        VERIFY_SUCCEEDED(
            DefChecksum::ComputeStringArrayChecksum(0, flags, static_cast<size_t>(strings1.GetNumStrings()), strings1.GetStrings(), &cs1));
        DefChecksum::Checksum cs2;
        VERIFY_SUCCEEDED(
            DefChecksum::ComputeStringArrayChecksum(0, flags, static_cast<size_t>(strings2.GetNumStrings()), strings2.GetStrings(), &cs2));
        if (verifyMatch)
        {
            VERIFY_ARE_EQUAL(cs1, cs2);
        }
        else
        {
            VERIFY_ARE_NOT_EQUAL(cs1, cs2);
        }
    }
}

void DefChecksumUnitTests::StringListChecksumTests(void)
{
    TestDataArray<String> data1;
    TestDataArray<String> data2;
    TestStringArray strings1;
    TestStringArray strings2;

    if (FAILED(TestData::TryGetValue(L"Strings1", data1)) || FAILED(TestData::TryGetValue(L"Strings2", data2)) ||
        (!strings1.InitFromArray(data1)) || (!strings2.InitFromArray(data2)))
    {
        Log::Error(L"Couldn't load test data.\n");
    }

    bool shouldTest;

    DefChecksum::ChecksumFlags flags = DefChecksum::Checksum_CaseSensitive | DefChecksum::Checksum_Unsorted;
    bool verifyMatch = (SUCCEEDED(TestData::TryGetValue(L"VerifyMatch", shouldTest)) && shouldTest);
    bool verifyMismatch = (SUCCEEDED(TestData::TryGetValue(L"VerifyMismatch", shouldTest)) && shouldTest);
    VerifyStringListChecksums(flags, strings1, strings2, verifyMatch, verifyMismatch);

    flags = DefChecksum::Checksum_CaseInsensitive | DefChecksum::Checksum_Unsorted;
    verifyMatch = (SUCCEEDED(TestData::TryGetValue(L"VerifyCaseInsensitiveMatch", shouldTest)) && shouldTest);
    verifyMismatch = (SUCCEEDED(TestData::TryGetValue(L"VerifyCaseInsensitiveMismatch", shouldTest)) && shouldTest);
    VerifyStringListChecksums(flags, strings1, strings2, verifyMatch, verifyMismatch);

    flags = DefChecksum::Checksum_CaseSensitive | DefChecksum::Checksum_Sorted;
    verifyMatch = (SUCCEEDED(TestData::TryGetValue(L"VerifySortedMatch", shouldTest)) && shouldTest);
    verifyMismatch = (SUCCEEDED(TestData::TryGetValue(L"VerifySortedMismatch", shouldTest)) && shouldTest);
    VerifyStringListChecksums(flags, strings1, strings2, verifyMatch, verifyMismatch);

    flags = DefChecksum::Checksum_CaseInsensitive | DefChecksum::Checksum_Sorted;
    verifyMatch = (SUCCEEDED(TestData::TryGetValue(L"VerifySortedCaseInsensitiveMatch", shouldTest)) && shouldTest);
    verifyMismatch = (SUCCEEDED(TestData::TryGetValue(L"VerifySortedCaseInsensitiveMismatch", shouldTest)) && shouldTest);
    VerifyStringListChecksums(flags, strings1, strings2, verifyMatch, verifyMismatch);
}

void DefChecksumUnitTests::FileChecksumTests(void)
{
    WEX::Common::String testDirectory;
    if (FAILED(RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDirectory)))
    {
        Log::Error(L"Unable to find TestDeploymentDir");
        return;
    }

    // TestMD does not support binplacing an empty file. So create it here.
    String tmp;
    StringResult emptyFile;

    HRESULT hr;
    if (FAILED(hr = emptyFile.SetRef(testDirectory)) || FAILED(hr = emptyFile.ConcatPathElement(L"Files\\empty.htm")))
    {
        Log::Error(tmp.Format(L"Unable to create full path to data file '%s', hr=0x%0X", emptyFile.GetRef(), hr));
        return;
    }

    HANDLE emptyFileHandle =
        CreateFileW(emptyFile.GetRef(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    VERIFY_ARE_NOT_EQUAL(emptyFileHandle, INVALID_HANDLE_VALUE);
    CloseHandle(emptyFileHandle);

    String checksumFile;
    DEF_CHECKSUM expectedChecksum;

    if (FAILED(TestData::TryGetValue(L"File", checksumFile)) || FAILED(TestData::TryGetValue(L"ExpectedChecksum", expectedChecksum)))
    {
        Log::Error(L"Couldn't load test data");
        return;
    }

    StringResult absolutePath;

    if (FAILED(hr = absolutePath.SetRef(testDirectory)) || FAILED(hr = absolutePath.ConcatPathElement(checksumFile)))
    {
        Log::Error(tmp.Format(L"Unable to create full path to data file '%s', hr=0x%0X", checksumFile.GetBuffer(), hr));
        return;
    }

    Log::Comment(tmp.Format(L"Computing Hash of file '%s'", absolutePath.GetRef()));
    DefChecksum::Checksum checksum;
    VERIFY_SUCCEEDED(DefChecksum::ComputeFileChecksum(0, absolutePath.GetRef(), &checksum));
    VERIFY_ARE_EQUAL(expectedChecksum, checksum);
}

void DefChecksumUnitTests::FileChecksumFailsForMissingFile(void)
{
    DefChecksum::Checksum checksum;
    VERIFY_FAILED(DefChecksum::ComputeFileChecksum(0, L"missingfile.htm", &checksum));
}

}; // namespace UnitTests
