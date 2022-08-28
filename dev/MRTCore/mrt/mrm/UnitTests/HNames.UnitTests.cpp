// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include <WexTestClass.h>

#include "Helpers.h"

#include "mrm/build/Base.h"
#include "mrm/readers/HNames.h"
#include "mrm/readers/FileLists.h"
#include "mrm/build/HNamesBuilder.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class HierarchicalNamesUnitTests : public WEX::TestClass<HierarchicalNamesUnitTests>
{
    TEST_CLASS(HierarchicalNamesUnitTests);

    TEST_METHOD(New_ParamChecks);

    BEGIN_TEST_METHOD(SimpleBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:HNames.UnitTests.xml#SimpleBuilderReaderTests")
    END_TEST_METHOD()

    BEGIN_TEST_METHOD(SimpleBuilderReaderExTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:HNames.UnitTests.xml#SimpleBuilderReaderTests")
    END_TEST_METHOD()

    BEGIN_TEST_METHOD(LargeBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:HNames.UnitTests.xml#LargeBuilderReaderTests")
    END_TEST_METHOD()
};

void CheckNames(_In_ const IHierarchicalNames* pNames)
{
    TestDataArray<String> specs;
    int scopeIndex = -1;
    int itemIndex = -1;
    int nameIndex = -1;
    StringResult name;
    String tmp;

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedNames", specs)))
    {
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;

            Log::Comment(tmp.Format(L"[ ExpectedNames %d: %s ]", i, (PCWSTR)specs[i]));
            if ((!expected.InitFromList(specs[i])) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 4))
            {
                Log::Error(L"Malformed ExpectedNames value");
                return;
            }

            // format is:  <name index> ; <expected name> ; <expected scope index> ; <expected item index>
            if (!expected.TryGetStringAsInt(0, &nameIndex))
            {
                Log::Error(L"Malformed ExpectedNames value");
                return;
            }

            VERIFY(pNames->TryGetName(nameIndex, &name, &scopeIndex, &itemIndex));

            int expectedIndex;
            if (expected.GetNumStrings() > 1)
            {
                // second value is expected name
                VERIFY(DefString_Compare(name.GetRef(), expected.GetString(1)) == Def_Equal);
            }

            if (expected.GetNumStrings() > 2)
            {
                // third value is expected scope index
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(2, &expectedIndex))
                {
                    VERIFY(scopeIndex == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(2)))
                {
                    Log::Warning(L"Malformed scope index");
                }
            }

            if (expected.GetNumStrings() > 3)
            {
                // fourth value is expected item index
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(3, &expectedIndex))
                {
                    VERIFY(itemIndex == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(3)))
                {
                    Log::Warning(L"Malformed item index");
                }
            }
        }
    }
    else
    {
        Log::Comment(L"[ No ExpectedNames specified ]");
        return;
    }

    return;
}

void CheckBuilderContents(_In_ const HierarchicalNamesBuilder* pBuilder)
{
    TestDataArray<String> specs;
    int scopeIndex = -1;
    int itemIndex = -1;
    Atom::Index atomIndex;
    String tmp;
    const IAtomPool* pScopeNames = pBuilder->GetScopeNames();
    const IAtomPool* pItemNames = pBuilder->GetItemNames();

    int numScopes;
    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedNumScopes", numScopes)))
    {
        VERIFY(numScopes == pBuilder->GetNumScopes());
    }
    else
    {
        Log::Comment(L"[ ExpectedNumScopes not specified ]");
    }

    int numItems;
    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedNumItems", numItems)))
    {
        VERIFY(numItems == pBuilder->GetNumItems());
    }
    else
    {
        Log::Comment(L"[ ExpectedNumItems not specified ]");
    }

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedContents", specs)))
    {
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;
            Log::Comment(tmp.Format(L"[ ExpectedContents %d: %s ]", i, (PCWSTR)specs[i]));
            if ((!expected.InitFromList(specs[i])) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 4))
            {
                Log::Error(L"Malformed ExpectedContents value");
                return;
            }

            VERIFY(pBuilder->Contains(expected.GetString(0), &scopeIndex, &itemIndex));

            if (scopeIndex > 0)
            {
                VERIFY(pScopeNames->Contains(expected.GetString(0)));
                VERIFY(pScopeNames->TryGetIndex(expected.GetString(0), &atomIndex));
                VERIFY(((int)atomIndex) == scopeIndex);
            }
            else if (itemIndex >= 0)
            {
                VERIFY(pItemNames->Contains(expected.GetString(0)));
                VERIFY(pItemNames->TryGetIndex(expected.GetString(0), &atomIndex));
                VERIFY(((int)atomIndex) == itemIndex);
            }

            int expectedIndex;
            if (expected.GetNumStrings() > 1)
            {
                // second value is expected scope index
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(1, &expectedIndex))
                {
                    VERIFY(scopeIndex == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(1)))
                {
                    Log::Warning(L"Malformed scope index");
                }
            }
            if (expected.GetNumStrings() > 2)
            {
                // third value is expected item index
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(2, &expectedIndex))
                {
                    VERIFY(itemIndex == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(2)))
                {
                    Log::Warning(L"Malformed item index");
                }
            }
        }
    }
    else
    {
        Log::Comment(L"[ No ExpectedContents specified ]");
        return;
    }

    TestDataArray<String> unexpectedSpecs;
    if (SUCCEEDED(TestData::TryGetValue(L"UnexpectedContents", unexpectedSpecs)))
    {
        for (size_t i = 0; i < unexpectedSpecs.GetSize(); i++)
        {
            Log::Comment(tmp.Format(L"[ UnexpectedContents %d: %s ]", i, (PCWSTR)unexpectedSpecs[i]));

            VERIFY(!pBuilder->Contains((PCWSTR)unexpectedSpecs[i], &scopeIndex, &itemIndex));
        }
    }
    else
    {
        Log::Comment(L"[ No UnexpectedContents specified ]");
        return;
    }
    return;
}

void CheckContents(__in const IHierarchicalNames* pNames)
{
    TestDataArray<String> specs;
    int scopeIndex = -1;
    int itemIndex = -1;
    int nameIndex = -1;
    Atom::Index atomIndex;
    String tmp;
    const IAtomPool* pScopeNames = pNames->GetScopeNames();
    const IAtomPool* pItemNames = pNames->GetItemNames();

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedContents", specs)))
    {
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;
            Log::Comment(tmp.Format(L"[ ExpectedContents %d: %s ]", i, (PCWSTR)specs[i]));
            if ((!expected.InitFromList(specs[i])) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 4))
            {
                Log::Error(L"Malformed ExpectedContents value");
                return;
            }

            VERIFY(pNames->Contains(expected.GetString(0), &scopeIndex, &itemIndex, &nameIndex));

            if (scopeIndex > 0)
            {
                VERIFY(pScopeNames->Contains(expected.GetString(0)));
                VERIFY(pScopeNames->TryGetIndex(expected.GetString(0), &atomIndex));
                VERIFY(((int)atomIndex) == scopeIndex);
            }
            else if (itemIndex >= 0)
            {
                VERIFY(pItemNames->Contains(expected.GetString(0)));
                VERIFY(pItemNames->TryGetIndex(expected.GetString(0), &atomIndex));
                VERIFY(((int)atomIndex) == itemIndex);
            }

            int expectedIndex;
            if (expected.GetNumStrings() > 1)
            {
                // second value is expected scope index
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(1, &expectedIndex))
                {
                    VERIFY(scopeIndex == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(1)))
                {
                    Log::Warning(L"Malformed scope index");
                }
            }
            if (expected.GetNumStrings() > 2)
            {
                // third value is expected item index
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(2, &expectedIndex))
                {
                    VERIFY(itemIndex == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(2)))
                {
                    Log::Warning(L"Malformed item index");
                }
            }
            if (expected.GetNumStrings() > 3)
            {
                // fourth value is expected name index
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(3, &expectedIndex))
                {
                    VERIFY(nameIndex == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(3)))
                {
                    Log::Warning(L"Malformed name index");
                }
            }
        }
    }
    else
    {
        Log::Comment(L"[ No ExpectedContents specified ]");
        return;
    }

    TestDataArray<String> unexpectedSpecs;
    if (SUCCEEDED(TestData::TryGetValue(L"UnexpectedContents", unexpectedSpecs)))
    {
        for (size_t i = 0; i < unexpectedSpecs.GetSize(); i++)
        {
            Log::Comment(tmp.Format(L"[ UnexpectedContents %d: %s ]", i, (PCWSTR)unexpectedSpecs[i]));

            VERIFY(!pNames->Contains((PCWSTR)unexpectedSpecs[i], &scopeIndex, &itemIndex, &nameIndex));
        }
    }
    else
    {
        Log::Comment(L"[ No UnexpectedContents specified ]");
        return;
    }
    return;
}

void CheckScopes(__in const IHierarchicalNames* pNames)
{
    TestDataArray<String> specs;
    int scopeIndex = -1;
    int numChildren = -1;
    String tmp;
    int numScopes;
    const IAtomPool* pScopeNames = pNames->GetScopeNames();
    StringResult name;
    StringResult atomName;

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedNumScopes", numScopes)))
    {
        VERIFY(numScopes == pNames->GetNumScopes());
        VERIFY(numScopes == pScopeNames->GetNumAtoms());
    }
    else
    {
        Log::Comment(L"[ ExpectedNumScopes not specified ]");
    }

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedScopes", specs)))
    {
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;

            Log::Comment(tmp.Format(L"[ ExpectedScopes %d: %s ]", i, (PCWSTR)specs[i]));
            if ((!expected.InitFromList(specs[i])) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 3))
            {
                Log::Error(L"Malformed ExpectedScopes value");
                return;
            }

            // format is:  <scope index> ; <expected name> ; <expected num children>
            if (!expected.TryGetStringAsInt(0, &scopeIndex))
            {
                Log::Error(L"Malformed ExpectedScopes value");
                return;
            }

            VERIFY(pNames->TryGetScopeInfo(scopeIndex, &name, &numChildren));

            int expectedIndex;
            if (expected.GetNumStrings() > 1)
            {
                // second value is expected name
                VERIFY(DefString_Compare(name.GetRef(), expected.GetString(1)) == Def_Equal);

                VERIFY(pScopeNames->TryGetString(scopeIndex, &atomName));
                VERIFY(DefString_Compare(atomName.GetRef(), expected.GetString(1)) == Def_Equal);
            }
            if (expected.GetNumStrings() > 2)
            {
                // third value is expected number of children
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(2, &expectedIndex))
                {
                    VERIFY(numChildren == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(2)))
                {
                    Log::Warning(L"Malformed number of children");
                }
            }
        }
    }
    else
    {
        Log::Comment(L"[ No ExpectedScopes specified ]");
        return;
    }
    return;
}

void CheckScopeChildren(__in const IHierarchicalNames* pNames)
{
    TestDataArray<String> specs;
    int scopeIndex = -1;
    String tmp;
    StringResult name;
    StringResult atomName;

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedScopeChildren", specs)))
    {
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;

            Log::Comment(tmp.Format(L"[ ExpectedScopeChildren %d: %s ]", i, (PCWSTR)specs[i]));
            if ((!expected.InitFromList(specs[i])) || (expected.GetNumStrings() < 1))
            {
                Log::Error(L"Malformed ExpectedScopeChildren value");
                return;
            }

            // format is:  <scope index> ; <child name>*
            if (!expected.TryGetStringAsInt(0, &scopeIndex))
            {
                Log::Error(L"Malformed ExpectedScopes value");
                return;
            }

            for (size_t c = 1; c < expected.GetNumStrings(); c++)
            {
                VERIFY(pNames->TryGetScopeChildName(scopeIndex, static_cast<int>(c - 1), &name));
                VERIFY(DefString_Compare(name.GetRef(), expected.GetString(static_cast<int>(c))) == Def_Equal);
            }
        }
    }
    else
    {
        Log::Comment(L"[ No ExpectedScopeChildren specified ]");
        return;
    }
    return;
}

void CheckItems(__in const IHierarchicalNames* pNames)
{
    TestDataArray<String> specs;
    int itemIndex;
    int numItems;
    const IAtomPool* pItemNames = pNames->GetItemNames();
    StringResult name;
    StringResult atomName;
    String tmp;

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedNumItems", numItems)))
    {
        VERIFY(numItems == pNames->GetNumItems());
        VERIFY(numItems == pItemNames->GetNumAtoms());
    }
    else
    {
        Log::Comment(L"[ ExpectedNumItems not specified ]");
    }

    if (SUCCEEDED(TestData::TryGetValue(L"ExpectedItems", specs)))
    {
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;

            Log::Comment(tmp.Format(L"[ ExpectedItems %d: %s ]", i, (PCWSTR)specs[i]));
            if ((!expected.InitFromList(specs[i])) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 2))
            {
                Log::Error(L"Malformed ExpectedItems value");
                return;
            }

            // format is:  <item index> ; <expected name>
            if (!expected.TryGetStringAsInt(0, &itemIndex))
            {
                Log::Error(L"Malformed ExpectedItems value");
                return;
            }

            VERIFY(pNames->TryGetItemInfo(itemIndex, &name));

            if (expected.GetNumStrings() > 1)
            {
                // second value is expected name
                VERIFY(DefString_Compare(name.GetRef(), expected.GetString(1)) == Def_Equal);

                VERIFY(pItemNames->TryGetString(itemIndex, &atomName));
                VERIFY(DefString_Compare(atomName.GetRef(), expected.GetString(1)) == Def_Equal);
            }
        }
    }
    else
    {
        Log::Comment(L"[ No ExpectedItems specified ]");
        return;
    }
}

void HierarchicalNamesUnitTests::New_ParamChecks(void)
{
    BYTE buf[1000];
    HierarchicalNames* pPool;
    HRESULT hr;

    SecureZeroMemory(buf, sizeof(buf));

#pragma prefast(suppress : 6309, "Test case testing illegal arguments")
    hr = HierarchicalNames::CreateInstance(gHierarchicalNamesSectionType, nullptr, 0, &pPool);
    VERIFY_HRESULT_FAILURE(E_INVALIDARG, hr);
    delete pPool;

#pragma prefast(suppress : 6309, "Test case testing illegal arguments")
    hr = HierarchicalNames::CreateInstance(gHierarchicalNamesSectionType, static_cast<const void*>(nullptr), (UINT32)sizeof(buf), &pPool);
    VERIFY_HRESULT_FAILURE(E_INVALIDARG, hr);
    delete pPool;

    hr = HierarchicalNames::CreateInstance(gHierarchicalNamesSectionType, buf, 0, &pPool);
    VERIFY_HRESULT_FAILURE(E_INVALIDARG, hr);
    delete pPool;

    // Now test with the extended header format
#pragma prefast(suppress : 6309, "Test case testing illegal arguments")
    hr = HierarchicalNames::CreateInstance(gHierarchicalNamesExSectionType, nullptr, 0, &pPool);
    VERIFY_HRESULT_FAILURE(E_INVALIDARG, hr);
    delete pPool;

#pragma prefast(suppress : 6309, "Test case testing illegal arguments")
    hr = HierarchicalNames::CreateInstance(gHierarchicalNamesExSectionType, static_cast<void*>(nullptr), (UINT32)sizeof(buf), &pPool);
    VERIFY_HRESULT_FAILURE(E_INVALIDARG, hr);
    delete pPool;

    hr = HierarchicalNames::CreateInstance(gHierarchicalNamesExSectionType, buf, 0, &pPool);
    VERIFY_HRESULT_FAILURE(E_INVALIDARG, hr);
    delete pPool;
}

static void SimpleBuilderReaderTestsInternal(_In_ UINT32 flags, _In_ const DEFFILE_SECTION_TYPEID& type)
{
    HRESULT hr;
    HierarchicalNamesBuilder* pBuilder;
    const HierarchicalNames* pReader = NULL;

    TestDataArray<String> specs;
    TestDataArray<String> bogus;
    String tmp;

    hr = HierarchicalNamesBuilder::CreateInstance(flags, &pBuilder);
    VERIFY_HRESULT_EXPR((pBuilder != NULL), hr);

    // First look for valid items to add
    if (SUCCEEDED(TestData::TryGetValue(L"InitStrings", specs)))
    {
        // Try to build according to our init specs
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            PCWSTR name = specs[i];
            Log::Comment(tmp.Format(L"[ InitString: %s ]", name));
            ItemInfo* pItem;
            hr = pBuilder->GetOrAddItem(name, &pItem);
            VERIFY_HRESULT_EXPR((pItem != NULL), hr);
        }
    }
    else
    {
        Log::Comment(L"[ No InitStrings specified ]");
    }

    // First look for bogus items to fail to add
    if (SUCCEEDED(TestData::TryGetValue(L"BogusStrings", bogus)))
    {
        // Try to build according to our bogus specs,
        // which should all fail
        for (size_t i = 0; i < bogus.GetSize(); i++)
        {
            PCWSTR name = bogus[i];
            Log::Comment(tmp.Format(L"[ BogusString: %s ]", name));
            ItemInfo* pItem;
            hr = pBuilder->GetOrAddItem(name, &pItem);
            VERIFY((pItem == NULL) && FAILED(hr));
        }
    }
    else
    {
        Log::Comment(L"[ No BogusStrings specified ]");
    }

    CheckBuilderContents(pBuilder);

    BuildHelper names;
    VERIFY_HRESULT(names.Build(pBuilder));

    Log::Comment(tmp.Format(L"[ HierarchicalName section built:  %d bytes ]", names.GetBufferSize()));

    // Should be able to read the built pool
    hr = HierarchicalNames::CreateInstance(type, names.GetBuffer(), names.GetBufferSize(), (HierarchicalNames**)&pReader);
    VERIFY_HRESULT_EXPR((pReader != NULL), hr);

    CheckNames(pReader);
    CheckContents(pReader);
    CheckScopes(pReader);
    CheckScopeChildren(pReader);
    CheckItems(pReader);

    delete pReader;
    delete pBuilder;
}

void HierarchicalNamesUnitTests::SimpleBuilderReaderTests(void)
{
    Log::Comment(L"[ Building UTF-16 with original HNames format ]");
    SimpleBuilderReaderTestsInternal(HierarchicalNamesBuilder::BuildUtf16Only, gHierarchicalNamesSectionType);
}

void HierarchicalNamesUnitTests::SimpleBuilderReaderExTests(void)
{
    Log::Comment(L"[ Building ASCII/UTF-16 with new HNames format ]");
    SimpleBuilderReaderTestsInternal(HierarchicalNamesBuilder::BuildAsciiOrUtf16, gHierarchicalNamesExSectionType);
}

void HierarchicalNamesUnitTests::LargeBuilderReaderTests(void)
{
    HRESULT hr = S_OK;
    String tmp;

    AutoDeletePtr<HierarchicalNamesBuilder> pBuilder;
    hr = HierarchicalNamesBuilder::CreateInstance(0, &pBuilder);
    VERIFY_HRESULT_EXPR((pBuilder != NULL), hr);

    int numItems = -1;
    String nameFormat = L"Item%d";

    if (FAILED(TestData::TryGetValue(L"NumItems", numItems)))
    {
        Log::Error(L"[ NumItems not defined ]");
        return;
    }

    if (FAILED(TestData::TryGetValue(L"NameFormat", nameFormat)))
    {
        Log::Warning(L"[ NameFormat not defined. Using default ]");
    }

    StringResult name;
    WCHAR nameBuf[MAX_PATH];
    SYSTEMTIME start;
    SYSTEMTIME checkpoint;
    SYSTEMTIME elapsed;

    GetSystemTime(&start);
    Log::Comment(tmp.Format(
        L"[ Start populating builder at: %02d:%02d:%02d.%03d ]", start.wHour, start.wMinute, start.wSecond, start.wMilliseconds));
    for (int iItem = 0; iItem < numItems; iItem++)
    {
        hr = StringCchPrintf(nameBuf, ARRAYSIZE(nameBuf), (PCWSTR)nameFormat, iItem);
        if (FAILED(hr))
        {
            Log::Error(tmp.Format(L"[ Couldn't create item name (0x%x) ]", hr));
            return;
        }

        // throttle logging based on number of resources to be generated
        if ((numItems < 100) || ((numItems < 1000) && ((iItem % 10) == 0)) || ((iItem % 100) == 0))
        {
            Log::Comment(tmp.Format(L"[ Adding \"%s\" ]", nameBuf));
        }

        ItemInfo* item;
        if (FAILED(pBuilder->GetOrAddItem(nameBuf, &item)))
        {
            Log::Error(tmp.Format(L"[ Couldn't add item '%s' ]", nameBuf));
        }
    }
    GetSystemTime(&checkpoint);
    ComputeElapsedTime(start, checkpoint, &elapsed);
    Log::Comment(tmp.Format(
        L"[ Done populating builder at: %02d:%02d:%02d.%03d (elapsed: %02d:%02d:%02d:%03d) ]",
        checkpoint.wHour,
        checkpoint.wMinute,
        checkpoint.wSecond,
        checkpoint.wMilliseconds,
        elapsed.wHour,
        elapsed.wMinute,
        elapsed.wSecond,
        elapsed.wMilliseconds));

    Log::Comment(L"[ Check builder contents ]");
    for (int iItem = 0; iItem < numItems; iItem++)
    {
        hr = StringCchPrintf(nameBuf, ARRAYSIZE(nameBuf), (PCWSTR)nameFormat, iItem);
        if (FAILED(hr))
        {
            Log::Error(tmp.Format(L"[ Couldn't create item name (0x%x) ]", hr));
            return;
        }

        // throttle logging based on number of resources to be generated
        if ((numItems < 100) || ((numItems < 1000) && ((iItem % 10) == 0)) || ((iItem % 100) == 0))
        {
            Log::Comment(tmp.Format(L"[ Verifying \"%s\" ]", nameBuf));
        }

        if (!pBuilder->GetItemNames()->TryGetString(iItem, &name))
        {
            Log::Error(tmp.Format(L"[ Couldn't read back name %d from item names atom pool ]", iItem));
            return;
        }

        if (DefString_Compare(nameBuf, name.GetRef()) != Def_Equal)
        {
            Log::Error(tmp.Format(L"[ Expected name '%s' for item %d, got '%s' ]", nameBuf, iItem, name.GetRef()));
            return;
        }
    }

    bool shouldSucceed = true;

    if (FAILED(TestData::TryGetValue(L"ShouldSucceed", shouldSucceed)))
    {
        Log::Warning(L"[ ShouldSucceed not defined. Using default ]");
    }

    BuildHelper names;

    if (shouldSucceed)
    {
        GetSystemTime(&start);
        Log::Comment(tmp.Format(
            L"[ Start building hierarchical names at: %02d:%02d:%02d.%03d ]",
            start.wHour,
            start.wMinute,
            start.wSecond,
            start.wMilliseconds));
        VERIFY_HRESULT(names.Build(pBuilder));
        GetSystemTime(&checkpoint);
        ComputeElapsedTime(start, checkpoint, &elapsed);
        Log::Comment(tmp.Format(
            L"[ Done building hierarchical names at: %02d:%02d:%02d.%03d (elapsed: %02d:%02d:%02d:%03d) ]",
            checkpoint.wHour,
            checkpoint.wMinute,
            checkpoint.wSecond,
            checkpoint.wMilliseconds,
            elapsed.wHour,
            elapsed.wMinute,
            elapsed.wSecond,
            elapsed.wMilliseconds));

        Log::Comment(L"[ Read back built hierarchical names ]");
        AutoDeletePtr<HierarchicalNames> pReader;
        hr = HierarchicalNames::CreateInstance(gHierarchicalNamesSectionType, names.GetBuffer(), names.GetBufferSize(), &pReader);
        VERIFY_HRESULT_EXPR((pReader != NULL), hr);

        Log::Comment(L"[ Check reader contents by index ]");
        for (int iItem = 0; iItem < numItems; iItem++)
        {
            hr = StringCchPrintf(nameBuf, ARRAYSIZE(nameBuf), (PCWSTR)nameFormat, iItem);
            if (FAILED(hr))
            {
                Log::Error(tmp.Format(L"[ Couldn't create item name (0x%x) ]", hr));
                return;
            }

            // throttle logging based on number of resources to be generated
            if ((numItems < 100) || ((numItems < 1000) && ((iItem % 10) == 0)) || ((iItem % 100) == 0))
            {
                Log::Comment(tmp.Format(L"[ Verifying \"%s\" ]", nameBuf));
            }

            if (!pReader->GetItemNames()->TryGetString(iItem, &name))
            {
                Log::Error(tmp.Format(L"[ Couldn't read back name %d from item names atom pool ]", iItem));
                return;
            }

            if (DefString_Compare(nameBuf, name.GetRef()) != Def_Equal)
            {
                Log::Error(tmp.Format(L"[ Expected name '%s' for item %d, got '%s' ]", nameBuf, iItem, name.GetRef()));
                return;
            }
        }
    }
    else
    {
        hr = names.Build(pBuilder);
        VERIFY_HRESULT_FAILURE(HRESULT_FROM_WIN32(ERROR_MRM_TOO_MANY_RESOURCES), hr);
    }
}

}; // namespace UnitTests
