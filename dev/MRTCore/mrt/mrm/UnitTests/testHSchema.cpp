// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include <mrm/build/AIDict.h>
#include "Helpers.h"
#include "TestHSchema.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

TestHierarchicalSchema::TestHierarchicalSchema() :
    m_build(), m_pPriBuilder(NULL), m_pSchemaBuilder(NULL), m_pSchema(NULL), m_pBaselinePri(NULL)
{}

// Creates a schema from test variables
HRESULT
TestHierarchicalSchema::Init(__in PriSectionBuilder* pPriBuilder, __in PCWSTR pVarPrefix, __in PCWSTR pBaselineFolder)
{
    Release();

    RETURN_IF_FAILED(CreateNewSchemaFromTestVars(pPriBuilder, pVarPrefix, pBaselineFolder, &m_pBaselinePri, &m_pSchemaBuilder));
    m_pPriBuilder = pPriBuilder;

    return S_OK;
}

HRESULT
TestHierarchicalSchema::Init(
    __in PriSectionBuilder* pPriBuilder,
    __in PCWSTR pVarPrefix,
    __in_opt const IHierarchicalSchema* pBaselineSchema)
{
    Release();

    RETURN_IF_FAILED(CreateNewSchemaFromTestVars(pPriBuilder, pVarPrefix, pBaselineSchema, &m_pSchemaBuilder));
    m_pPriBuilder = pPriBuilder;

    return S_OK;
}

void TestHierarchicalSchema::Release()
{
    delete m_pSchema;
    m_pSchema = NULL;

    delete m_pSchemaBuilder;
    m_pSchemaBuilder = NULL;

    delete m_pBaselinePri;
    m_pBaselinePri = NULL;

    // we don't own the PriBuilder
    // BuildHelper cleans itself up
}

HRESULT
TestHierarchicalSchema::Build() { return m_build.Build(m_pSchemaBuilder); }

HRESULT
TestHierarchicalSchema::CreateReader(_In_ const DEFFILE_SECTION_TYPEID& type)
{
    return HierarchicalSchema::CreateInstance(type, m_build.GetBuffer(), m_build.GetBufferSize(), &m_pSchema);
}

bool TestHierarchicalSchema::TryVerifySchema(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix)
{
    String tmp;
    Log::Comment(tmp.Format(L"[ Verifying schema \"%s\" ]", pVarPrefix));
    //  verify that the schema contains what we expect it to
    bool ok = true;
    ok = ok && TestHierarchicalSchema::TryVerifyVersion(pSchema, pVarPrefix);
    ok = ok && TestHierarchicalSchema::TryVerifyScopes(pSchema, pVarPrefix);
    ok = ok && TestHierarchicalSchema::TryVerifyItems(pSchema, pVarPrefix);
    return ok;
}

bool TestHierarchicalSchema::TryVerifyVersion(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix)
{
    String tmp;
    int version;

    Log::Comment(tmp.Format(L"[ Verifying schema verison \"%s\" ]", pVarPrefix));
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedMajorVersion", pVarPrefix), version)))
    {
        if (pSchema->GetVersionInfo() != NULL)
        {
            VERIFY_ARE_EQUAL(pSchema->GetVersionInfo()->GetMajorVersion(), version);
        }
        else
        {
            Log::Warning(tmp.Format(L"[ %sExpectedMajorVersion specified but schema has no version ]", pVarPrefix));
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[%sExpectedMajorVersion not verified]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedMinorVersion", pVarPrefix), version)))
    {
        VERIFY_ARE_EQUAL(pSchema->GetVersionInfo()->GetMinorVersion(), version);
    }
    else
    {
        Log::Warning(tmp.Format(L"[%sExpectedMinorVersion not verified]", pVarPrefix));
    }
    return true;
}

bool TestHierarchicalSchema::TryVerifyScopes(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix)
{
    TestDataArray<String> specs;
    int scopeIndex = -1;
    int numChildren = -1;
    String tmp;
    String specListString;
    int numScopes;
    const IAtomPool* pScopeNames = pSchema->GetScopeNames();
    StringResult name;
    StringResult atomName;

    Log::Comment(tmp.Format(L"[ Verifying schema scopes \"%s\" ]", pVarPrefix));
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumScopes", pVarPrefix), numScopes)))
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumScopes = %d ]", pVarPrefix, numScopes));
        VERIFY(numScopes == pSchema->GetNumScopes());
        VERIFY(numScopes == pScopeNames->GetNumAtoms());
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumScopes not specified ]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedScopes", pVarPrefix), specs)))
    {
        Log::Comment(tmp.Format(L"[ Found %d %sExpectedScopes ]", (int)specs.GetSize(), pVarPrefix));
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;

            Log::Comment(tmp.Format(L"[ %sExpectedScopes %d: %s ]", pVarPrefix, (int)i, (PCWSTR)specs[i]));
            if (!expected.InitFromList(specs[i]) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 3))
            {
                Log::Error(L"Malformed ExpectedScopes value");
                return false;
            }

            // format is:  <scope index> ; <expected name> ; <expected num children>
            if (!expected.TryGetStringAsInt(0, &scopeIndex))
            {
                Log::Error(L"Malformed ExpectedScopes value");
                return false;
            }

            VERIFY(pSchema->TryGetScopeInfo(scopeIndex, &name, &numChildren));

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
                    continue;
                }
            }
        }
    }
    else if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedScopesList", pVarPrefix), specListString)))
    {
        TestStringArray specList;
        if (!specList.InitFromList(specListString))
        {
            Log::Warning(tmp.Format(L"[ Couldn't parse %sExpectedScopesList ]", pVarPrefix));
            return false;
        }

        Log::Comment(tmp.Format(L"[ Found %d %sExpectedScopesList ]", specList.GetNumStrings(), pVarPrefix));
        for (int i = 0; i < specList.GetNumStrings(); i++)
        {
            VERIFY(pSchema->TryGetScopeInfo(i + 1, &name));
            VERIFY(DefString_Compare(name.GetRef(), specList.GetString(i)) == Def_Equal);
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %sExpectedScopes not specified ]", pVarPrefix));
    }

    String unexpectedList;
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sUnexpectedScopes", pVarPrefix), unexpectedList)))
    {
        Log::Comment(tmp.Format(L"[ Found %sUnexpectedScopes ]", pVarPrefix));

        TestStringArray specList;
        if (specList.InitFromList((PCWSTR)unexpectedList))
        {
            for (int i = 0; i < specList.GetNumStrings(); i++)
            {
                VERIFY(!pSchema->GetScopeNames()->Contains(specList.GetString(i)));
            }
        }
        else
        {
            Log::Warning(tmp.Format(L"[ Couldn't parse %sUnexpectedScopes ]", pVarPrefix));
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sUnexpectedScopes not specified ]", pVarPrefix));
    }
    return true;
}

bool TestHierarchicalSchema::TryVerifyItems(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix)
{
    TestDataArray<String> specs;
    int itemIndex;
    int numItems;
    const IAtomPool* pItemNames = pSchema->GetItemNames();
    StringResult name;
    StringResult atomName;
    String specListString;
    String tmp;

    Log::Comment(tmp.Format(L"[ Verifying schema items \"%s\" ]", pVarPrefix));

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumItems", pVarPrefix), numItems)))
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumItems = %d ]", pVarPrefix, numItems));
        VERIFY(numItems == pSchema->GetNumItems());
        VERIFY(numItems == pItemNames->GetNumAtoms());
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumItems not specified ]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedItems", pVarPrefix), specs)))
    {
        Log::Comment(tmp.Format(L"[ Found %d %sExpectedItems ]", (int)specs.GetSize(), pVarPrefix));

        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;

            Log::Comment(tmp.Format(L"[ %sExpectedItems %d: %s ]", pVarPrefix, (int)i, (PCWSTR)specs[i]));
            if (!expected.InitFromList(specs[i]) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 2))
            {
                Log::Error(L"Malformed ExpectedItems value");
                return false;
            }

            // format is:  <item index> ; <expected name>
            if (!expected.TryGetStringAsInt(0, &itemIndex))
            {
                Log::Error(L"Malformed ExpectedItems value");
                return false;
            }

            VERIFY(pSchema->TryGetItemInfo(itemIndex, &name));

            if (expected.GetNumStrings() > 1)
            {
                // second value is expected name
                VERIFY(DefString_Compare(name.GetRef(), expected.GetString(1)) == Def_Equal);

                VERIFY(pItemNames->TryGetString(itemIndex, &atomName));
                VERIFY(DefString_Compare(atomName.GetRef(), expected.GetString(1)) == Def_Equal);
            }
        }
    }
    else if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedItemsList", pVarPrefix), specListString)))
    {
        TestStringArray specList;
        if (specList.InitFromList(specListString))
        {
            Log::Comment(tmp.Format(L"[ Found %d %sExpectedItemsList ]", specList.GetNumStrings(), pVarPrefix));
            for (int i = 0; i < specList.GetNumStrings(); i++)
            {
                VERIFY(pSchema->TryGetItemInfo(i, &name));
                VERIFY(DefString_Compare(name.GetRef(), specList.GetString(i)) == Def_Equal);
            }
        }
        else
        {
            Log::Warning(tmp.Format(L"[ Couldn't parse %sExpectedItemsList ]", pVarPrefix));
            return false;
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedItems not specified ]", pVarPrefix));
    }

    String unexpectedList;
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sUnexpectedItems", pVarPrefix), unexpectedList)))
    {
        TestStringArray specList;
        if (specList.InitFromList((PCWSTR)unexpectedList))
        {
            for (int i = 0; i < specList.GetNumStrings(); i++)
            {
                Log::Comment(tmp.Format(L"[ Found %d %sUnexpectedItems ]", specList.GetNumStrings(), pVarPrefix));
                VERIFY(!pSchema->GetScopeNames()->Contains(specList.GetString(i)));
            }
        }
        else
        {
            Log::Warning(tmp.Format(L"[ Couldn't parse %sUnexpectedItems ]", pVarPrefix));
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sUnexpectedItems not specified ]", pVarPrefix));
    }
    return true;
}

bool TestHierarchicalSchema::TryVerifyCompatibility(
    __in const IHierarchicalSchema* pOlderSchema,
    __in const IHierarchicalSchema* pNewerSchema,
    __in PCWSTR pVarPrefix)
{
    String tmp;
    bool ok = true;
    bool expected;

    Log::Comment(tmp.Format(L"[ Verifying compatibility for \"%s\"]", pVarPrefix));
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sShouldBeIdentical", pVarPrefix), expected)))
    {
        bool isIdentical = CheckHierarchicalSchemaVersionIsIdentical(pOlderSchema->GetVersionInfo(), pNewerSchema->GetVersionInfo());
        Log::Comment(tmp.Format(L"[ %sShouldBeIdentical == %s ]", pVarPrefix, (isIdentical ? L"true" : L"false")));
        VERIFY(expected == isIdentical);
        ok = ok && (expected == isIdentical);
    }
    else
    {
        Log::Warning(tmp.Format(L"[%sShouldBeIdentical not verified]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sShouldBeCompatible", pVarPrefix), expected)))
    {
        bool isCompatible = CheckHierarchicalSchemaVersionIsCompatible(pNewerSchema, pOlderSchema->GetVersionInfo());
        Log::Comment(tmp.Format(L"[ %sShouldBeCompatible == %s ]", pVarPrefix, (isCompatible ? L"true" : L"false")));
        VERIFY(expected == isCompatible);
        ok = ok && (expected == isCompatible);
    }
    else
    {
        Log::Warning(tmp.Format(L"[%sShouldBeCompatible not verified]", pVarPrefix));
    }

    return ok;
}

HRESULT
TestHierarchicalSchema::CreateNewSchemaFromTestVars(
    __in PriSectionBuilder* pPriBuilder,
    __in PCWSTR pVarPrefix,
    __in_opt PCWSTR pBaselineFolder,
    _Outptr_opt_result_maybenull_ StandalonePriFile** ppBaselinePriOut,
    _Outptr_ HierarchicalSchemaSectionBuilder** value)
{
    String tmp;
    String tmp2;
    String simpleId;
    String uniqueId;
    int majorVersion = 0;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    HierarchicalSchemaSectionBuilder* pSchemaBuilder = NULL;

    // Always NULL out the return so our caller can safely just delete it
    if (ppBaselinePriOut != NULL)
    {
        *ppBaselinePriOut = NULL;
    }

    *value = nullptr;

    // see if we should build from a baseline
    const IHierarchicalSchema* pBaselineSchema = NULL;
    String baselineList;
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sBaselineSchema", pVarPrefix), baselineList)))
    {
        TestStringArray baseline;
        if ((pBaselineFolder == NULL) || (ppBaselinePriOut == NULL))
        {
            Log::Error(tmp.Format(L"Test data for \"%s\" specifies baseline but test supplies no folder", pVarPrefix));
            return E_FAIL;
        }
        else if (!baseline.InitFromList((PCWSTR)baselineList) || (baseline.GetNumStrings() != 2))
        {
            Log::Error(tmp.Format(L"Malformed baseline \"%s\" for \"%s\"", (PCWSTR)baselineList, pVarPrefix));
            return E_FAIL;
        }

        StringResult str;
        VERIFY_SUCCEEDED(str.Init(pBaselineFolder));
        if (FAILED(str.ConcatPathElement(tmp.Format(L"%s.pri", baseline.GetString(0)))))
        {
            Log::Error(L"Error constructing path for baseline PRI file");
            return E_FAIL;
        }

        VERIFY_SUCCEEDED(StandalonePriFile::CreateInstance(0, str.GetRef(), pProfile, ppBaselinePriOut));
        if (*ppBaselinePriOut == NULL)
        {
            Log::Error(tmp.Format(L"Error loading baseline PRI \"%s\"", str.GetRef()));
            return E_FAIL;
        }

        VERIFY_SUCCEEDED((*ppBaselinePriOut)->GetSchemaById(baseline.GetString(1), &pBaselineSchema));
        if (pBaselineSchema == NULL)
        {
            Log::Error(tmp.Format(L"Couldn't find hierarchical schema \"%s\" in baseline PRI \"%s\"", baseline.GetString(1), str.GetRef()));
            return E_FAIL;
        }
    }
    else
    {
        // Not building from a baseline.  Look for other variables
        if (FAILED(TestData::TryGetValue(tmp.Format(L"%sSimpleId", pVarPrefix), simpleId)))
        {
            simpleId = L"Test";
        }
        else
        {
            simpleId.Trim();
        }

        if (FAILED(TestData::TryGetValue(tmp.Format(L"%sMajorVersion", pVarPrefix), majorVersion)))
        {
            majorVersion = 1;
        }

        if (FAILED(TestData::TryGetValue(tmp.Format(L"%sUniqueId", pVarPrefix), uniqueId)))
        {
            uniqueId = tmp.Format(L":%s", (PCWSTR)simpleId);
            Log::Warning(tmp.Format(L"Unique name not specified. Assuming unique name %s", (PCWSTR)uniqueId));
        }
    }

    if (pBaselineSchema == NULL)
    {
        VERIFY_SUCCEEDED(HierarchicalSchemaSectionBuilder::CreateInstance(
            pPriBuilder, simpleId, uniqueId, static_cast<UINT16>(majorVersion), &pSchemaBuilder));
    }
    else
    {
        VERIFY_SUCCEEDED(
            HierarchicalSchemaSectionBuilder::CreateInstance(pPriBuilder, pBaselineSchema, PriBuildFromPrevSchema, &pSchemaBuilder));
    }
    if (pSchemaBuilder != NULL)
    {
        if (!TryAddItemsFromTestVars(pPriBuilder, pSchemaBuilder, pVarPrefix))
        {
            delete pSchemaBuilder;
            pSchemaBuilder = NULL;
            Log::Error(tmp.Format(L"Test setup: items for \"%s\"", pVarPrefix));
        }
    }
    else
    {
        Log::Error(tmp.Format(L"Error creating schema for \"%s\"", pVarPrefix));
    }

    *value = pSchemaBuilder;
    return S_OK;
}

HRESULT
TestHierarchicalSchema::CreateNewSchemaFromTestVars(
    __in PriSectionBuilder* pPriBuilder,
    __in PCWSTR pVarPrefix,
    __in_opt const IHierarchicalSchema* pBaselineSchema,
    _Outptr_ HierarchicalSchemaSectionBuilder** value)
{
    String tmp;
    String tmp2;
    String simpleId;
    String uniqueId;
    int majorVersion = 0;
    HierarchicalSchemaSectionBuilder* pSchemaBuilder = NULL;

    *value = nullptr;

    // see if we should build from a baseline
    bool bVersioned = false;
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sVersionedBuild", pVarPrefix), bVersioned)) && bVersioned)
    {
        Log::Comment(tmp.Format(L"[ %s: versioned build ]", pVarPrefix));
        if (pBaselineSchema == NULL)
        {
            Log::Error(tmp.Format(L"[ %s: Data specifies versioned build but no baseline supplied ]", pVarPrefix));
            return E_FAIL;
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %s: non-versioned build ]", pVarPrefix));
        // Not building from a baseline.  Look for other variables
        if (FAILED(TestData::TryGetValue(tmp.Format(L"%sSimpleId", pVarPrefix), simpleId)))
        {
            simpleId = L"Test";
        }
        else
        {
            simpleId.Trim();
        }

        if (FAILED(TestData::TryGetValue(tmp.Format(L"%sMajorVersion", pVarPrefix), majorVersion)))
        {
            majorVersion = 1;
        }

        if (FAILED(TestData::TryGetValue(tmp.Format(L"%sUniqueId", pVarPrefix), uniqueId)))
        {
            uniqueId = tmp.Format(L":%s", (PCWSTR)simpleId);
        }
    }

    if (!bVersioned)
    {
        VERIFY_SUCCEEDED(HierarchicalSchemaSectionBuilder::CreateInstance(
            pPriBuilder, simpleId, uniqueId, static_cast<UINT16>(majorVersion), &pSchemaBuilder));
    }
    else
    {
        VERIFY_SUCCEEDED(
            HierarchicalSchemaSectionBuilder::CreateInstance(pPriBuilder, pBaselineSchema, PriBuildFromPrevSchema, &pSchemaBuilder));
    }
    if (pSchemaBuilder != NULL)
    {
        if (!TryAddItemsFromTestVars(pPriBuilder, pSchemaBuilder, pVarPrefix))
        {
            delete pSchemaBuilder;
            pSchemaBuilder = NULL;
            Log::Error(tmp.Format(L"Test setup: items for \"%s\"", pVarPrefix));
        }
    }
    else
    {
        Log::Error(tmp.Format(L"Error creating schema for \"%s\"", pVarPrefix));
    }

    *value = pSchemaBuilder;
    return S_OK;
}

bool TestHierarchicalSchema::TryAddItemsFromTestVars(
    __in PriSectionBuilder* /*pPriBuilder*/,
    __in HierarchicalSchemaSectionBuilder* pSchemaBuilder,
    __in PCWSTR pVarPrefix)
{
    TestStringArray itemNames;
    int itemIndex;
    String tmp;

    if (itemNames.TryInitFromTestVars(tmp.Format(L"%sItemNames", pVarPrefix)))
    {
        for (int i = 0; i < itemNames.GetNumStrings(); i++)
        {
            HRESULT hr = pSchemaBuilder->GetOrAddItem(itemNames.GetString(i), &itemIndex);
            if (FAILED(hr) || (itemIndex < 0))
            {
                Log::Error(tmp.Format(L"[ Error adding item %s ]", itemNames.GetString(i)));
                return false;
            }
            Log::Comment(tmp.Format(L"[ Index(%s) = %d ]", itemNames.GetString(i), itemIndex));
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ HSchema: %sItemNames not defined ]", pVarPrefix));
    }
    return true;
}

} // namespace UnitTests
