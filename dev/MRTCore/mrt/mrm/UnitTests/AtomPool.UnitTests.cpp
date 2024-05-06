// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include <WexTestClass.h>

#include "Helpers.h"
#include "mrm/build/Base.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{

/*!
     * AtomPool Unit Test helpers
     */
class AtomPoolUnitTest
{
protected:
    static bool ParseAtomSpec(__in const String& spec, __inout String& keyOut, __inout int& indexOut);
    _Success_(return == true) static bool GetTestSetup(__out bool& isCaseInsensitiveOut, __out int& poolIndexOut, __out TestDataArray<String>& initSpecsOut);
    static void CheckAtomPoolGetMethods(__in const IAtomPool* pPool);
    static void CheckUnexpectedStrings(__in const IAtomPool* pPool);
};

_Success_(return == true)
bool AtomPoolUnitTest::GetTestSetup(__out bool& bIsCaseInsensitiveOut, __out int& poolIndexOut, __out TestDataArray<String>& initSpecsOut)
{
    // pool index & case-sensitivity must be specified
    if (FAILED(TestData::TryGetValue(L"PoolIndex", poolIndexOut)) ||
        FAILED(TestData::TryGetValue(L"IsCaseInsensitive", bIsCaseInsensitiveOut)))
    {
        Log::Error(L"Missing pool index or case-sensitivity");
        return false;
    }
    // for initialization, we want "InitStrings" but we'll take "ExpectedStrings"
    if (FAILED(TestData::TryGetValue(L"InitStrings", initSpecsOut)) && FAILED(TestData::TryGetValue(L"ExpectedStrings", initSpecsOut)))
    {
        Log::Error(L"Neither InitStrings or ExpectedStrings were specified");
        return false;
    }
    return true;
}

bool AtomPoolUnitTest::ParseAtomSpec(__in const String& spec, __inout String& keyOut, __inout int& indexOut)
{
    return TestAtomPool::ParseAtomSpec(spec, keyOut, indexOut);
}

void AtomPoolUnitTest::CheckAtomPoolGetMethods(__in const IAtomPool* pPool)
{
    Atom atom;

    int poolIndex;
    bool bIsCaseInsensitive;
    TestDataArray<String> specs;

    if (FAILED(TestData::TryGetValue(L"IsCaseInsensitive", bIsCaseInsensitive)) || FAILED(TestData::TryGetValue(L"PoolIndex", poolIndex)) ||
        FAILED(TestData::TryGetValue(L"ExpectedStrings", specs)))
    {
        Log::Error(L"Error reading test data");
        return;
    }

    // make sure we got the expected index
    VERIFY_ARE_EQUAL(poolIndex, pPool->GetPoolIndex());

    int numExpected;
    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedNumUniqueStrings", numExpected)))
    {
        VERIFY_ARE_EQUAL(numExpected, pPool->GetNumAtoms());
    }
    else
    {
        Log::Warning(L"Num expected strings not specified");
    }

    DEFCOMPAREOPTIONS compareOpts = (bIsCaseInsensitive ? DefCompare_CaseInsensitive : DefCompare_Default);
    StringResult str;

    String key;
    int index = 0;

    for (size_t i = 0; i < specs.GetSize(); i++)
    {
        if (!ParseAtomSpec(specs[i], key, index))
        {
            Log::Error(L"Error parsing atom spec");
            continue;
        }

        atom.Set(index, poolIndex);

        // Test TryGetString(Atom)
        VERIFY(pPool->TryGetString(atom, &str));
        VERIFY((DefString_CompareWithOptions(key, str.GetRef(), compareOpts) == Def_Equal));

        // Test TryGetString(Index)
        VERIFY(pPool->TryGetString(index, &str));
        VERIFY((DefString_CompareWithOptions(key, str.GetRef(), compareOpts) == Def_Equal));

        Atom gotAtom = Atom::NullAtom;
        // Test TryGetAtom(PCWSTR)
        VERIFY(pPool->TryGetAtom(key, &gotAtom));
        VERIFY((gotAtom.GetIndex() == index));

        Atom::Index gotIndex = Atom::IndexNone;
        // Test TryGetIndex(PCWSTR)
        VERIFY(pPool->TryGetIndex(key, &gotIndex));
        VERIFY((gotIndex == index));

        // Test Contains(PCWSTR) & Contains(Atom)
        VERIFY(pPool->Contains(key));
        VERIFY(pPool->Contains(atom));

        // Test Equals(Atom, PCWSTR)
        VERIFY(pPool->Equals(atom, key));
    }
}

void AtomPoolUnitTest::CheckUnexpectedStrings(__in const IAtomPool* pPool)
{
    TestDataArray<String> strings;

    if (FAILED(TestData::TryGetValue(L"UnexpectedStrings", strings)))
    {
        return;
    }
    for (int i = 0; i < strings.GetSize(); i++)
    {
        // Contains, TryGetAtom and TryGetString should all return false without setting an error
        VERIFY(!pPool->Contains(strings[i]));
        VERIFY(!pPool->TryGetAtom(strings[i], NULL));
        VERIFY(!pPool->TryGetIndex(strings[i], NULL));
    }
}

/*!
     * FileAtomPool Unit Tests
     */
class FileAtomPoolUnitTests : public WEX::TestClass<FileAtomPoolUnitTests>, public AtomPoolUnitTest
{
    TEST_CLASS(FileAtomPoolUnitTests);

    TEST_METHOD(New_ParamChecks);
    TEST_METHOD(BadPool);

    BEGIN_TEST_METHOD(SimpleBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:AtomPool.UnitTests.xml#SimpleAtomPoolTests")
    END_TEST_METHOD()

    BEGIN_TEST_METHOD(SimpleCloneBuilderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:AtomPool.UnitTests.xml#SimpleAtomPoolTests")
    END_TEST_METHOD()

    BEGIN_TEST_METHOD(BigPoolBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:AtomPool.UnitTests.xml#BigAtomPoolTests")
    END_TEST_METHOD()
};

void FileAtomPoolUnitTests::New_ParamChecks(void)
{
    BYTE buf[1000];
    FileAtomPool* pPool;

    SecureZeroMemory(buf, sizeof(buf));

    HRESULT hr = FileAtomPool::CreateInstance(NULL, 0, &pPool);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pPool;

    hr = FileAtomPool::CreateInstance((const void*)NULL, (UINT32)sizeof(buf), &pPool);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pPool;

    hr = FileAtomPool::CreateInstance(buf, 0, &pPool);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pPool;
}

void FileAtomPoolUnitTests::BadPool(void)
{
    FileAtomPoolBuilder* pBuilder;
    const FileAtomPool* pReader = NULL;
    Atom atom;

    VERIFY_SUCCEEDED(FileAtomPoolBuilder::CreateInstance(L"Test", true, &pBuilder));

    VERIFY_SUCCEEDED(pBuilder->GetOrAddAtom(L"str1", &atom));
    VERIFY_ARE_EQUAL(atom.GetIndex(), 0);

    VERIFY_SUCCEEDED(pBuilder->GetOrAddAtom(L"str2", &atom));
    VERIFY_ARE_EQUAL(atom.GetIndex(), 1);

    BuildHelper pool;

    // Trying to build with pool index 0 should fail
    VERIFY_ARE_EQUAL(pool.Build(pBuilder), E_DEF_ATOM_BAD_POOL);

    // Now lets try with "none" - should fail again
    pBuilder->SetPoolIndex(Atom::PoolIndexNone);
    VERIFY_ARE_EQUAL(pool.Build(pBuilder), E_DEF_ATOM_BAD_POOL);

    // Now try with a legal index, should succeed
    pBuilder->SetPoolIndex(1);
    VERIFY_SUCCEEDED(pool.Build(pBuilder));

    // Should be able to read the built pool
    VERIFY_SUCCEEDED(FileAtomPool::CreateInstance(pool.GetBuffer(), pool.GetBufferSize(), (FileAtomPool**)&pReader));

    // make sure we got the index we expected
    VERIFY_ARE_EQUAL(1, pReader->GetPoolIndex());

    atom = Atom::NullAtom;
    VERIFY(pReader->TryGetAtom(L"str1", &atom) && (atom.GetIndex() == 0));

    atom = Atom::NullAtom;
    VERIFY(pReader->TryGetAtom(L"str2", &atom) && (atom.GetIndex() == 1));

    delete pReader;

    // Now hack the header and try to read a pool with index 0 - should fail
    DEFFILE_ATOMPOOL_HEADER* pHdr = reinterpret_cast<DEFFILE_ATOMPOOL_HEADER*>(pool.GetBuffer());
    pHdr->poolIndex = DEF_ATOM_NULL_POOL_INDEX;
    VERIFY_ARE_EQUAL(
        E_DEF_ATOM_BAD_POOL,
        FileAtomPool::CreateInstance(pool.GetBuffer(), pool.GetBufferSize(), (FileAtomPool**)&pReader),
        L"Read a FileAtomPool with poolIndex 0");

    delete pReader;

    // Now hack the header and try to read a pool with index "none" - should fail
    pHdr = reinterpret_cast<DEFFILE_ATOMPOOL_HEADER*>(pool.GetBuffer());
    pHdr->poolIndex = DEF_ATOM_POOL_INDEX_NONE;
    VERIFY_ARE_EQUAL(
        E_DEF_ATOM_BAD_POOL,
        FileAtomPool::CreateInstance(pool.GetBuffer(), pool.GetBufferSize(), (FileAtomPool**)&pReader),
        L"Read a FileAtomPool with poolIndex 0");
    VERIFY_IS_NULL(pReader);

    delete pReader;
    delete pBuilder;
}

void FileAtomPoolUnitTests::SimpleBuilderReaderTests(void)
{
    FileAtomPoolBuilder* pBuilder;
    const FileAtomPool* pReader = NULL;
    Atom atom;

    int poolIndex = 0;
    bool bIsCaseInsensitive;
    TestDataArray<String> specs;

    if (!GetTestSetup(bIsCaseInsensitive, poolIndex, specs))
    {
        Log::Error(L"Couldn't initialize test");
        return;
    }

    // Try to build according to our init specs
    VERIFY_SUCCEEDED(FileAtomPoolBuilder::CreateInstance(L"Test", bIsCaseInsensitive, &pBuilder));

    pBuilder->SetPoolIndex(poolIndex);

    String key;
    int index = 0;
    for (size_t i = 0; i < specs.GetSize(); i++)
    {
        if (!ParseAtomSpec(specs[i], key, index))
        {
            Log::Error(L"Couldn't parse atom spec");
            continue;
        }

        VERIFY_SUCCEEDED(pBuilder->GetOrAddAtom(key, &atom));
        VERIFY_ARE_EQUAL(atom.GetIndex(), index);
    }

    // Okay, we've added all of the strings.  Now let's make sure we can
    // find them again where we expect.

    DEFCOMPAREOPTIONS compareOpts = (bIsCaseInsensitive ? DefCompare_CaseInsensitive : DefCompare_Default);
    StringResult str;

    for (size_t i = 0; i < specs.GetSize(); i++)
    {
        VERIFY_IS_TRUE(ParseAtomSpec(specs[i], key, index));

        // Test TryGetString(atom)
        atom.Set(index, poolIndex);
        VERIFY(pBuilder->TryGetString(atom, &str));
        VERIFY((DefString_CompareWithOptions(str.GetRef(), key, compareOpts) == Def_Equal));

        // Test TryGetString(index)
        VERIFY(pBuilder->TryGetString(index, &str));
        VERIFY((DefString_CompareWithOptions(str.GetRef(), key, compareOpts) == Def_Equal));

        // Test TryGetAtom(PCWSTR)
        Atom gotAtom;
        gotAtom.Set(0, 0);
        VERIFY(pBuilder->TryGetAtom(key, &gotAtom));
        VERIFY((gotAtom.GetPoolIndex() == poolIndex) && (gotAtom.GetIndex() == index));

        // Test TryGetIndex(PCWSTR)
        Atom::Index gotIndex = Atom::IndexNone;
        VERIFY(pBuilder->TryGetIndex(key, &gotIndex));
        VERIFY((gotIndex == index));

        // Test Contains(PCWSTR) & Contains(atom)
        VERIFY(pBuilder->Contains(key));
        VERIFY(pBuilder->Contains(atom));

        // Test Equals(Atom, PCWSTR)
        VERIFY(pBuilder->Equals(atom, key));
    }

    BuildHelper pool;
    VERIFY_SUCCEEDED(pool.Build(pBuilder));

    // Should be able to read the built pool
    VERIFY_SUCCEEDED(FileAtomPool::CreateInstance(pool.GetBuffer(), pool.GetBufferSize(), (FileAtomPool**)&pReader));
    VERIFY_IS_NOT_NULL(pReader);

    // Standard get method validation
    CheckAtomPoolGetMethods(pReader);

    // make sure no unexpected strings work
    CheckUnexpectedStrings(pReader);

    delete pReader;
    delete pBuilder;
}

void FileAtomPoolUnitTests::SimpleCloneBuilderTests(void)
{
    TestAtomPool testPool;
    FileAtomPoolBuilder* pBuilder;
    const FileAtomPool* pReader = NULL;
    Atom atom;

    int poolIndex = 0;
    bool bIsCaseInsensitive;
    TestDataArray<String> specs;

    if (!GetTestSetup(bIsCaseInsensitive, poolIndex, specs))
    {
        Log::Error(L"Couldn't initialize test");
        return;
    }

    // Try to build according to our init specs
    VERIFY(testPool.InitFromSpecs(L"test", bIsCaseInsensitive, specs, NULL));

    VERIFY_SUCCEEDED(FileAtomPoolBuilder::CreateInstance(testPool.GetPool(), &pBuilder));

    pBuilder->SetPoolIndex(poolIndex);

    // Now let's make sure we can find all of the strings where we expect them.

    String key;
    int index = 0;
    DEFCOMPAREOPTIONS compareOpts = (bIsCaseInsensitive ? DefCompare_CaseInsensitive : DefCompare_Default);
    StringResult str;

    for (size_t i = 0; i < specs.GetSize(); i++)
    {
        if (!ParseAtomSpec(specs[i], key, index))
        {
            Log::Error(L"Couldn't parse atom spec (test error)");
            return;
        }

        // Test TryGetString(atom)
        atom.Set(index, poolIndex);
        VERIFY(pBuilder->TryGetString(atom, &str));
        VERIFY((DefString_CompareWithOptions(str.GetRef(), key, compareOpts) == Def_Equal));

        // Test TryGetString(index)
        VERIFY(pBuilder->TryGetString(index, &str));
        VERIFY((DefString_CompareWithOptions(str.GetRef(), key, compareOpts) == Def_Equal));

        // Test TryGetAtom(PCWSTR)
        Atom gotAtom;
        gotAtom.Set(0, 0);
        VERIFY(pBuilder->TryGetAtom(key, &gotAtom));
        VERIFY((gotAtom.GetPoolIndex() == poolIndex) && (gotAtom.GetIndex() == index));

        // Test TryGetIndex(PCWSTR)
        Atom::Index gotIndex = Atom::IndexNone;
        VERIFY(pBuilder->TryGetIndex(key, &gotIndex));
        VERIFY((gotIndex == index));

        // Test Contains(PCWSTR) & Contains(atom)
        VERIFY(pBuilder->Contains(key));
        VERIFY(pBuilder->Contains(atom));

        // Test Equals(Atom, PCWSTR)
        VERIFY(pBuilder->Equals(atom, key));
    }

    BuildHelper pool;
    VERIFY_SUCCEEDED(pool.Build(pBuilder));

    // Should be able to read the built pool
    VERIFY_SUCCEEDED(FileAtomPool::CreateInstance(pool.GetBuffer(), pool.GetBufferSize(), (FileAtomPool**)&pReader));

    // Standard get method validation
    CheckAtomPoolGetMethods(pReader);

    // make sure no unexpected strings work
    CheckUnexpectedStrings(pReader);

    delete pReader;
    delete pBuilder;
}

void FileAtomPoolUnitTests::BigPoolBuilderReaderTests(void)
{
    FileAtomPoolBuilder* pBuilder = NULL;
    const FileAtomPool* pReader = NULL;
    Atom atom;
    WCHAR buf[100];
    String desc;
    int poolIndex;
    bool bIsCaseInsensitive;
    int numAtoms;

    if (FAILED(TestData::TryGetValue(L"PoolDescription", desc)) || FAILED(TestData::TryGetValue(L"PoolIndex", poolIndex)) ||
        FAILED(TestData::TryGetValue(L"IsCaseInsensitive", bIsCaseInsensitive)) || FAILED(TestData::TryGetValue(L"NumAtoms", numAtoms)))
    {
        Log::Error(L"Couldn't load test data");
        return;
    }
    VERIFY_SUCCEEDED(FileAtomPoolBuilder::CreateInstance(L"BigPool", true, &pBuilder));

    String logmsg;
    logmsg.Format(L"Creating %d atoms", numAtoms);
    Log::Comment(logmsg);
    for (int i = 0; i < numAtoms; i++)
    {
        if (FAILED(StringCchPrintf(buf, 100, L"Atom%d", i)))
        {
            Log::Error(L"StringCchPrintf failed!");
            return;
        }

        if (FAILED(pBuilder->GetOrAddAtom(buf, &atom)) || (atom.GetIndex() != i))
        {
            // only report failures to reduce noise
            VERIFY((atom.GetIndex() == i));
        }
        if ((i > 0) && ((i % 1000) == 0))
        {
            logmsg.Format(L"%d Atoms", i);
            Log::Comment(logmsg);
        }
    }

    pBuilder->SetPoolIndex(1);
    VERIFY(pBuilder->GetNumAtoms() == numAtoms);

    BuildHelper pool;
    VERIFY_SUCCEEDED(pool.Build(pBuilder));

    // Should be able to read the built pool
    VERIFY_SUCCEEDED(FileAtomPool::CreateInstance(pool.GetBuffer(), pool.GetBufferSize(), (FileAtomPool**)&pReader));

    // Make sure all of the atoms are there

    VERIFY(pReader->GetNumAtoms() == numAtoms);

    DEFCOMPAREOPTIONS compareOpts = (bIsCaseInsensitive ? DefCompare_CaseInsensitive : DefCompare_Default);

    StringResult str;
    logmsg.Format(L"Verifying %d atoms", numAtoms);
    Log::Comment(logmsg);
    for (int i = 0; i < numAtoms; i++)
    {
        if (FAILED(StringCchPrintf(buf, 100, L"Atom%d", i)))
        {
            Log::Error(L"StringCchPrintf failed");
            return;
        }

        // only log failures to reduce noise
        if ((!pReader->TryGetAtom(buf, &atom)) || (atom.GetIndex() != i))
        {
            logmsg.Format(L"TryGetAtom(%s) failed", buf);
            VERIFY_FAIL((PCWSTR)logmsg);
        }

        if ((!pReader->TryGetString(i, &str)) || (str.CompareWithOptions(buf, compareOpts) != Def_Equal))
        {
            logmsg.Format(L"TryGetString(%d) failed", i);
            VERIFY_FAIL((PCWSTR)logmsg);
        }

        if ((!pReader->TryGetString(atom, &str)) || (str.CompareWithOptions(buf, compareOpts) != Def_Equal))
        {
            logmsg.Format(L"TryGetString([%d,%d] failed)", atom.GetPoolIndex(), atom.GetIndex());
            VERIFY_FAIL((PCWSTR)logmsg);
        }

        if ((i > 0) && ((i % 1000) == 0))
        {
            logmsg.Format(L"%d Atoms", i);
            Log::Comment(logmsg);
        }
    }

    delete pReader;
    delete pBuilder;
}

/*!
     * StaticAtomPool Unit Tests
     */
class StaticAtomPoolUnitTests : public WEX::TestClass<StaticAtomPoolUnitTests>, public AtomPoolUnitTest
{
    TEST_CLASS(StaticAtomPoolUnitTests);

    static PWSTR* GetStringArray(TestDataArray<String>& stringsIn);
    static void FreeStringArray(__in_ecount(numStrings) PWSTR* ppStrings, int numStrings);

    TEST_METHOD(New_ParamChecks);

    BEGIN_TEST_METHOD(SimpleTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:AtomPool.UnitTests.xml#SimpleStaticAtomPoolTests")
    END_TEST_METHOD()
};

PWSTR* StaticAtomPoolUnitTests::GetStringArray(TestDataArray<String>& initSpecs)
{
    PWSTR* pRtrn = _DefArray_AllocZeroed(PWSTR, initSpecs.GetSize());
    String key;
    int index = 0;
    for (int i = 0; i < initSpecs.GetSize(); i++)
    {
        ParseAtomSpec(initSpecs[i], key, index);
        pRtrn[i] = _DefDuplicateString(key);
    }
    return pRtrn;
}

void StaticAtomPoolUnitTests::FreeStringArray(__in_ecount(numStrings) PWSTR* ppStrings, int numStrings)
{
    for (int i = 0; i < numStrings; i++)
    {
        Def_Free(ppStrings[i]);
    }
    Def_Free(ppStrings);
}

void StaticAtomPoolUnitTests::New_ParamChecks(void)
{
    BYTE buf[1000];
    StaticAtomPool* pPool = NULL;
    static PCWSTR pTestStrings[3] = {L"Str1", L"Str2", L"Str3"};
    static PCWSTR pTestStringsNull[3] = {L"Str1", NULL, L"Str3"};
    static PCWSTR pTestStringsEmpty[3] = {L"Str1", L"Str2", L""};

    SecureZeroMemory(buf, sizeof(buf));

    // negative numStrings
    HRESULT hr = StaticAtomPool::CreateInstance(pTestStrings, -3, L"Description", true, &pPool);
    VERIFY_IS_TRUE(pPool == NULL);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pPool;

    // NULL ppStrings with positive count
    hr = StaticAtomPool::CreateInstance(NULL, 10, L"Description", true, &pPool);
    VERIFY_IS_TRUE(pPool == NULL);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pPool;

    // NULL string in the array
    hr = StaticAtomPool::CreateInstance(pTestStringsNull, 3, L"Test", true, &pPool);
    VERIFY_IS_TRUE(pPool == NULL);
    VERIFY_ARE_EQUAL(hr, E_DEF_ATOM_BAD_STRING);

    // Empty string in the array
    hr = StaticAtomPool::CreateInstance(pTestStringsEmpty, 3, L"Test", true, &pPool);
    VERIFY_IS_TRUE(pPool == NULL);
    VERIFY_ARE_EQUAL(hr, E_DEF_ATOM_BAD_STRING);
}

void StaticAtomPoolUnitTests::SimpleTests(void)
{
    StaticAtomPool* pPool = NULL;
    Atom atom;

    int poolIndex = 0;
    bool bIsCaseInsensitive;
    TestDataArray<String> initSpecs;
    PWSTR* ppStrings = NULL;

    if (!GetTestSetup(bIsCaseInsensitive, poolIndex, initSpecs))
    {
        Log::Error(L"Coudn't initialize test data");
        return;
    }

    ppStrings = GetStringArray(initSpecs);
    VERIFY_IS_TRUE(ppStrings != NULL);

    VERIFY_SUCCEEDED(StaticAtomPool::CreateInstance(ppStrings, static_cast<int>(initSpecs.GetSize()), L"Test", bIsCaseInsensitive, &pPool));

    // pool index 0 is illegal
    pPool->SetPoolIndex(poolIndex);

    // make sure we got the expected index
    VERIFY_ARE_EQUAL(poolIndex, pPool->GetPoolIndex());

    int numExpected;
    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedNumUniqueStrings", numExpected)))
    {
        VERIFY_ARE_EQUAL(numExpected, pPool->GetNumAtoms());
    }
    else
    {
        Log::Warning(L"Num expected strings not specified");
    }

    CheckAtomPoolGetMethods(pPool);

    CheckUnexpectedStrings(pPool);

    FreeStringArray(ppStrings, static_cast<int>(initSpecs.GetSize()));
    delete pPool;
}

}; // namespace UnitTests
