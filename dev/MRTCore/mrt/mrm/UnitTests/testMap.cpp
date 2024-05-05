// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include <mrm/build/AIDict.h>
#include "TestHSchema.h"
#include "TestMap.h"
#include "TestLinks.h"
#include "TestUtils.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

TestResourceMap::TestResourceMap() :
    m_build(),
    m_pPriBuilder(nullptr),
    m_pMapBuilder(nullptr),
    m_pMap(nullptr),
    m_pMyMapBuilder(nullptr),
    m_pMySchemaBuilder(nullptr),
    m_pBaselinePri(nullptr),
    m_expectedFinalizeResult(0),
    m_expectedFinalizeReturn(true),
    m_expectedBuildResult(0),
    m_expectedBuildReturn(true)
{}

// Creates an index from test variables using the supplied schema builder
HRESULT
TestResourceMap::InitFromSchemaAndTestVars(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_opt_ TestDecisionInfo* pTestDI,
    _In_ HierarchicalSchemaSectionBuilder* pSchema,
    _In_ PCWSTR pVarPrefix,
    _In_ MapInitFlags initFlags)
{
    String tmp;
    Release();

    // Read decision info from test vars unless supplied
    if (pTestDI == nullptr)
    {
        if (FAILED(m_testDI.InitDataFromTestVars(pVarPrefix)))
        {
            Log::Warning(tmp.Format(L"[ Couldn't initialize test decision info %s ]", pVarPrefix));
            return E_FAIL;
        }
        Log::Comment(tmp.Format(L"[ Using test decision info from \"%s\" ]", pVarPrefix));
        m_pTestDI = &m_testDI;
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Using supplied test decision info ]"));
        m_pTestDI = pTestDI;
    }

    ResourceMapSectionBuilder* pMapBuilder;
    RETURN_IF_FAILED(ResourceMapSectionBuilder::CreateInstance(
        pPriBuilder, pSchema, pPriBuilder->GetDecisionInfoBuilder(), pPriBuilder->GetEnvironment(), &pMapBuilder));

    // ResourceMapSectionBuilder should exist in the PriSectionBuilder for PriSectionBuilder::AddCandidate use.
    int index;
    VERIFY_SUCCEEDED(pPriBuilder->AddResourceMapBuilder(pMapBuilder, ((initFlags & SetAsPrimary) != 0), &index));
    VERIFY(index >= 0);

    if ((!TryAddCandidatesFromTestVars(pPriBuilder, pMapBuilder, m_pTestDI, pVarPrefix)) ||
        (!TestResourceLinks::TryAddLinksFromTestVars(pMapBuilder, pVarPrefix)))
    {
        delete pMapBuilder;
        return E_FAIL;
    }

    m_pMapBuilder = pMapBuilder;
    m_pPriBuilder = pPriBuilder;

    TestUtils::TryGetExpectedResult(
        tmp.Format(L"%sExpectedFinalizeResult", pVarPrefix), &m_expectedFinalizeResult, &m_expectedFinalizeReturn);
    TestUtils::TryGetExpectedResult(tmp.Format(L"%sExpectedBuildResult", pVarPrefix), &m_expectedBuildResult, &m_expectedBuildReturn);

    RETURN_HR_IF(E_FAIL, m_pMapBuilder == nullptr);

    return S_OK;
}

// Creates a schema and index from test variables
HRESULT
TestResourceMap::InitFromTestVars(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_opt_ TestDecisionInfo* pTestDI,
    _In_ PCWSTR pVarPrefix,
    _In_opt_ PCWSTR pBaselineFolder,
    _In_ TestResourceMap::MapInitFlags initFlags)
{
    String tmp;

    Release();

    Log::Comment(tmp.Format(L"[ Initializing TestResourceMap for \"%s\" ]", pVarPrefix));
    HierarchicalSchemaSectionBuilder* pSchema;
    RETURN_IF_FAILED(
        TestHierarchicalSchema::CreateNewSchemaFromTestVars(pPriBuilder, pVarPrefix, pBaselineFolder, &m_pBaselinePri, &pSchema));
    if (FAILED(InitFromSchemaAndTestVars(pPriBuilder, pTestDI, pSchema, pVarPrefix, initFlags)))
    {
        delete pSchema;
        Log::Error(L"[ Couldn't initalize hierarchical schema from test vars ]");
        return E_FAIL;
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Initialized schema for \"%s\" ]", pVarPrefix));
    }

    bool addSchemaToPri = ((initFlags & AddSchema) != 0);
    bool setAsPrimary = ((initFlags & SetAsPrimary) != 0);
    int index;
    if (addSchemaToPri)
    {
        RETURN_IF_FAILED(pPriBuilder->AddSchemaBuilder(pSchema, setAsPrimary, &index));
        if (index < 0)
        {
            Log::Error(L"[ Couldn't add schema to PRI builder ]");
            return E_FAIL;
        }
    }

    // InitFromTestVar does a Release(), so don't set schema members until it succeeds
    // If we added it to the PRI, the PRI owns it so set MySchemaBuilder to nullptr.
    m_pSchemaBuilder = pSchema;
    m_pMySchemaBuilder = (addSchemaToPri ? nullptr : pSchema);
    return S_OK;
}

void TestResourceMap::Release()
{
    delete m_pMap;
    m_pMap = nullptr;

    delete m_pMyMapBuilder;
    m_pMyMapBuilder = nullptr;
    m_pMapBuilder = nullptr;

    delete m_pMySchemaBuilder;
    m_pMySchemaBuilder = nullptr;
    m_pSchemaBuilder = nullptr;

    delete m_pBaselinePri;
    m_pBaselinePri = nullptr;
    // we don't own the PriBuilder
    // BuildHelper cleans itself up
}

HRESULT
TestResourceMap::Finalize()
{
    RETURN_IF_FAILED(m_pSchemaBuilder->Finalize());

    HRESULT hr = m_pMapBuilder->Finalize();

    VERIFY_ARE_EQUAL(m_expectedFinalizeResult, hr);
    VERIFY_ARE_EQUAL(m_expectedFinalizeReturn, SUCCEEDED(hr));

    return S_OK;
}

HRESULT
TestResourceMap::Build()
{
    HRESULT hr = m_build.Build(m_pMapBuilder);

    VERIFY_ARE_EQUAL(m_expectedBuildResult, hr);
    VERIFY_ARE_EQUAL(m_expectedBuildReturn, SUCCEEDED(hr));

    return S_OK;
}

HRESULT
TestResourceMap::CreateReader(_In_ const IFileSectionResolver* pSections, _In_ const DEFFILE_SECTION_TYPEID& sectionType)
{
    return ResourceMapBase::CreateInstance(pSections, nullptr, sectionType, m_build.GetBuffer(), m_build.GetBufferSize(), &m_pMap);
}

HRESULT
TestResourceMap::CreateNewMapFromTestVars(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ HierarchicalSchemaSectionBuilder* pSchemaBuilder,
    _In_ TestDecisionInfo* pTestDI,
    _In_ PCWSTR pVarPrefix,
    _Outptr_ ResourceMapSectionBuilder** value)
{
    *value = nullptr;
    String tmp;
    ResourceMapSectionBuilder* pMapBuilder = nullptr;

    RETURN_IF_FAILED(ResourceMapSectionBuilder::CreateInstance(
        pPriBuilder, pSchemaBuilder, pPriBuilder->GetDecisionInfoBuilder(), pPriBuilder->GetEnvironment(), &pMapBuilder));

    if (!TryAddCandidatesFromTestVars(pPriBuilder, pMapBuilder, pTestDI, pVarPrefix))
    {
        delete pMapBuilder;
        return E_FAIL;
    }

    *value = pMapBuilder;
    return S_OK;
}

bool TestResourceMap::TryAddCandidatesFromTestVars(
    _In_ PriSectionBuilder* pPriSectionBuilder,
    _In_ ResourceMapSectionBuilder* pMapBuilder,
    _In_ TestDecisionInfo* pTestDI,
    _In_ PCWSTR pVarPrefix)
{
    // Add candidate to the Resource Section or DataItemSections
    HierarchicalSchemaSectionBuilder* pSchemaBuilder = pMapBuilder->GetSchema();
    DecisionInfoSectionBuilder* pDecisions = pMapBuilder->GetDecisionInfo();
    TestDataArray<String> candidates;
    String tmp;

    Log::Comment(tmp.Format(L"[ Adding %sCandidates ]", pVarPrefix));
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sCandidates", pVarPrefix), candidates)))
    {
        TestStringArray candidate;

        for (unsigned i = 0; i < candidates.GetSize(); i++)
        {
            Log::Comment(tmp.Format(L"[ candidate %d: %s ]", i, (PCWSTR)candidates[i]));
            if (!candidate.InitFromList(candidates[i]))
            {
                Log::Warning(L" [ Couldn't parse candidate string ] ");
                continue;
            }

            switch (candidate.GetNumStrings())
            {
            case 1:
                // No parameters - just create the named resource
                int index;
                VERIFY_SUCCEEDED(pSchemaBuilder->GetOrAddItem(candidate.GetString(0), &index));
                VERIFY(index >= 0);
                break;
            case 4:
            {
                // name; type; qualifier set; value
                PCWSTR pName = candidate.GetString(0);
                PCWSTR pType = candidate.GetString(1);
                PCWSTR pQualifierSetName = candidate.GetString(2);
                PCWSTR pValue = candidate.GetString(3);
                QualifierSetResult qs;
                if (FAILED(pTestDI->GetQualifierSetData()->GetOrAddQualifierSet(pQualifierSetName, pDecisions, &qs)))
                {
                    Log::Warning(L"[ Couldn't get qualifier set ]");
                    continue;
                }
                // Add Candidate to section builder where it use data item section for candidate
                MrmEnvironment::ResourceValueType type;
                VERIFY_SUCCEEDED(MrmEnvironment::GetResourceValueType(pType, &type));
                VERIFY_SUCCEEDED(pPriSectionBuilder->AddCandidateWithString(pSchemaBuilder->GetSimpleId(), pName, type, pValue, &qs));
                break;
            }
            default:
                Log::Warning(L"[ Malformed candidate string ]");
                break;
            }
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sCandidates not defined ]", pVarPrefix));
    }
    Log::Comment(tmp.Format(L"[ Done adding %sCandidates ]", pVarPrefix));
    return true;
}

HRESULT
TestResourceMap::AddCandidatesFromTestVars(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ ResourceMapSectionBuilder* pSchemaBuilder,
    _In_ TestDecisionInfo* pTestDI,
    _In_ PCWSTR pVarPrefix)
{
    if (!TryAddCandidatesFromTestVars(pPriBuilder, pSchemaBuilder, pTestDI, pVarPrefix))
    {
        String tmp;
        Log::Error(tmp.Format(L"Couldn't load candidates for %s", pVarPrefix));
        return E_FAIL;
    }
    return S_OK;
}

HRESULT
TestResourceMap::VerifyCandidates(
    _In_ const IResourceMapBase* pMap,
    _In_ TestDecisionInfo* pTestDI,
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_ PCWSTR pVarPrefix)
{
    TestMapPrivate priv;

    priv.pBuilder = nullptr;
    priv.pSubtree = nullptr;
    priv.pMap = pMap;
    priv.pEnvironment = pEnvironment;
    return VerifyCandidates(&priv, pTestDI, pVarPrefix);
}

HRESULT
TestResourceMap::VerifyAllAgainstTestVars(
    _In_ const ResourceMapSectionBuilder* pMap,
    _In_ TestDecisionInfo* pTestDI,
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_ PCWSTR pVarPrefix)
{
    TestMapPrivate priv;

    priv.pBuilder = pMap;
    priv.pSubtree = nullptr;
    priv.pMap = nullptr;
    priv.pEnvironment = pEnvironment;
    return VerifyAllAgainstTestVars(&priv, pTestDI, pVarPrefix);
}

HRESULT
TestResourceMap::VerifyAllAgainstTestVars(
    _In_ const IResourceMapBase* pMap,
    _In_opt_ const ResourceMapSubtree* pSubtree,
    _In_ TestDecisionInfo* pTestDI,
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_ PCWSTR pVarPrefix)
{
    TestMapPrivate priv;

    priv.pBuilder = nullptr;
    priv.pMap = pMap;
    priv.pSubtree = pSubtree;
    priv.pEnvironment = pEnvironment;
    return VerifyAllAgainstTestVars(&priv, pTestDI, pVarPrefix);
}

HRESULT
TestResourceMap::VerifyCandidate(
    _In_ const IResourceMapBase* pMap,
    _In_ const UnifiedEnvironment* /* pEnvironment */,
    _In_opt_ PCWSTR pResourceName,
    _In_ int itemIndex,
    _In_ const IQualifierSet* pWantQualifiers,
    _In_ PCWSTR pWantType,
    _In_ PCWSTR pWantStringValue)
{
    NamedResourceResult namedResource;
    ResourceCandidateResult candidate;
    QualifierSetResult gotQualifiers;
    QualifierSetResult qualifiersByIndex;
    StringResult gotValue;
    MrmEnvironment::ResourceValueType gotType;
    MrmEnvironment::ResourceValueType gotExternalType;
    MrmEnvironment::ResourceValueType wantType;
    VERIFY_SUCCEEDED(MrmEnvironment::GetResourceValueType(pWantType, &wantType));

    if (pResourceName != nullptr)
    {
        VERIFY_SUCCEEDED(pMap->GetResource(pResourceName, &namedResource));
        if (itemIndex >= 0)
        {
            VERIFY_ARE_EQUAL(itemIndex, namedResource.GetResourceIndexInSchema());
        }
    }
    else
    {
        VERIFY_SUCCEEDED(pMap->GetResourceByIndex(itemIndex, &namedResource));
    }

    for (int iCandidate = 0; iCandidate < namedResource.GetNumCandidates(); iCandidate++)
    {
        VERIFY_SUCCEEDED(namedResource.GetCandidate(iCandidate, &candidate));
        VERIFY_SUCCEEDED(candidate.GetQualifiers(&gotQualifiers));
        if (IQualifierSet::Equal(pWantQualifiers, &gotQualifiers))
        {
            VERIFY_SUCCEEDED(candidate.GetResourceValueType(&gotType));
            VERIFY_SUCCEEDED(MrmEnvironment::GetExternalResourceValueType(gotType, &gotExternalType));

            VERIFY((gotType == wantType) || (gotExternalType == wantType));

            if (pWantStringValue != nullptr)
            {
                VERIFY(candidate.TryGetStringValue(&gotValue));
                if (pWantStringValue[0] == L'*')
                {
                    VERIFY(DefString_IsSuffix(&pWantStringValue[1], gotValue.GetRef()));
                }
                else
                {
                    String tmp;
                    Log::Warning(tmp.Format(L"DEBUG:VerifyCandidate:Want=%s,Got=%s", pWantStringValue, gotValue.GetRef()));
                    if (MrmEnvironment::IsPathResourceValueType(gotType))
                    {
                        VERIFY(DefString_IsSuffixI(pWantStringValue, gotValue.GetRef()));
                    }
                    else
                    {
                        VERIFY(gotValue.Compare(pWantStringValue) == Def_Equal);
                    }
                }
            }

            // Verify that qualifier indexes haven't shifted during unification
            VERIFY(pWantQualifiers->GetIndex() == gotQualifiers.GetIndex());
            return S_OK;
        }
    }
    Log::Error(L"No candidate matches qualifier set.");
    return E_FAIL;
}

HRESULT
TestResourceMap::VerifyCandidate(
    _In_ const ResourceMapSectionBuilder* pMap,
    _In_opt_ PCWSTR pResourceName,
    _In_ int itemIndex,
    _In_ const IQualifierSet* pWantQualifiers,
    _In_ PCWSTR pWantType,
    _In_ PCWSTR pWantStringValue)
{
    int gotItemIndex = -1;
    QualifierSetResult gotQualifiers;
    StringResult gotValue;
    int numCandidates = -1;
    MrmEnvironment::ResourceValueType gotType;
    MrmEnvironment::ResourceValueType gotExternalType;
    MrmEnvironment::ResourceValueType wantType;
    VERIFY_SUCCEEDED(MrmEnvironment::GetResourceValueType(pWantType, &wantType));

    if (pResourceName != nullptr)
    {
        VERIFY(pMap->TryGetResourceInfo(pResourceName, &gotItemIndex, &numCandidates));
        if (itemIndex >= 0)
        {
            VERIFY_ARE_EQUAL(itemIndex, gotItemIndex);
        }
        itemIndex = gotItemIndex;
    }
    else
    {
        VERIFY(pMap->TryGetResourceInfo(itemIndex, nullptr, &numCandidates));
    }

    for (int iCandidate = 0; iCandidate < numCandidates; iCandidate++)
    {
        VERIFY(pMap->TryGetCandidateInfo(itemIndex, iCandidate, &gotQualifiers, &gotType, &gotValue));
        if (IQualifierSet::Equal(pWantQualifiers, &gotQualifiers))
        {
            VERIFY_SUCCEEDED(MrmEnvironment::GetExternalResourceValueType(gotType, &gotExternalType));
            VERIFY((wantType == gotType) || (wantType == gotExternalType));

            if (pWantStringValue != nullptr)
            {
                if (pWantStringValue[0] == L'*')
                {
                    VERIFY(DefString_IsSuffix(&pWantStringValue[1], gotValue.GetRef()));
                }
                else
                {
                    VERIFY(gotValue.Compare(pWantStringValue) == Def_Equal);
                }
            }
            return S_OK;
        }
    }
    Log::Error(L"No candidate matches qualifier set.");
    return E_FAIL;
}

HRESULT
TestResourceMap::VerifyCandidates(_In_ TestMapPrivate* pMap, _In_ TestDecisionInfo* pTestDI, _In_ PCWSTR pVarPrefix)
{
    TestDataArray<String> specs;
    String tmp;
    int expectedNumValues = -1;

    Log::Comment(tmp.Format(L"[ Verifying candidates for \"%s\" ]", pVarPrefix));

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumTotalValues", pVarPrefix), expectedNumValues)))
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumTotalValues = %d  ]", pVarPrefix, expectedNumValues));
        if (pMap->pBuilder != nullptr)
        {
            VERIFY(expectedNumValues == pMap->pBuilder->GetTotalNumFinalizedValues());
        }

        if (pMap->pMap != nullptr)
        {
            VERIFY(expectedNumValues == pMap->pMap->GetTotalNumResourceValues());
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumTotalValues not defined ]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedCandidateInfo", pVarPrefix), specs)))
    {
        TestStringArray spec;
        QualifierSetResult wantQualifiers;

        Log::Comment(tmp.Format(L"[ Found %d %sExpectedCandidateInfo ]", (int)specs.GetSize(), pVarPrefix));
        for (unsigned iSpec = 0; iSpec < specs.GetSize(); iSpec++)
        {
            Log::Comment(tmp.Format(L"[ Candidate %d: %s ]", iSpec, (PCWSTR)specs[iSpec]));
            if (!spec.InitFromList(specs[iSpec]))
            {
                Log::Warning(tmp.Format(L"[ Error parsing spec %d in %sExpectedCandidateInfo ]", iSpec, pVarPrefix));
                continue;
            }

            PCWSTR pResourceName = nullptr;
            int itemIndex = -1;
            int candidateIndex = -1;
            // format is:  item ; candidate index; value type; qualifier set name; value
            // where:
            //   - 'item' is either an index or a string
            //   - 'candidate index' is an expected index or '*'
            // Note: builder candidate indexes are unstable, so this method ignores candidate
            //       index beyond syntax validation.  The format includes candidate index so
            //       we can use the same data for builder and reader tests.
            if (spec.GetNumStrings() != 5)
            {
                Log::Warning(tmp.Format(L"[ Malformed expected candidate info \"%s\" - must have 5 fields]", (PCWSTR)specs[iSpec]));
                continue;
            }

            if (!spec.TryGetStringAsInt(0, &itemIndex))
            {
                // not an integer, must be a name.
                pResourceName = spec.GetString(0);
            }

            // verify syntax but otherwise ignore candidate index
            if ((!spec.TryGetStringAsInt(1, &candidateIndex)) && (DefString_Compare(spec.GetString(1), L"*") != Def_Equal))
            {
                Log::Warning(
                    tmp.Format(L"[ Malformed expected candidate info \"%s\" - candidate must be index or '*' ]", (PCWSTR)specs[iSpec]));
                continue;
            }

            PCWSTR pWantType = spec.GetString(2);

            if (pMap->pBuilder != nullptr)
            {
                if (!pTestDI->GetQualifierSetData()->TryGetQualifierSet(
                        spec.GetString(3), pMap->pBuilder->GetDecisionInfo(), pMap->pEnvironment, &wantQualifiers))
                {
                    Log::Warning(tmp.Format(L"[ Malformed expected candidate info \"%s\" - unknown qualifier set ]", (PCWSTR)specs[iSpec]));
                    return E_FAIL;
                }
                VerifyCandidate(pMap->pBuilder, pResourceName, itemIndex, &wantQualifiers, pWantType, spec.GetString(4));
            }

            if (pMap->pMap != nullptr)
            {
                if (!pTestDI->GetQualifierSetData()->TryGetQualifierSet(
                        spec.GetString(3), pMap->pMap->GetDecisionInfo(), pMap->pEnvironment, &wantQualifiers))
                {
                    Log::Warning(tmp.Format(L"[ Malformed expected candidate info \"%s\" - unknown qualifier set ]", (PCWSTR)specs[iSpec]));
                    return E_FAIL;
                }
                VerifyCandidate(pMap->pMap, pMap->pEnvironment, pResourceName, itemIndex, &wantQualifiers, pWantType, spec.GetString(4));
            }
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedCandidateInfo not defined ]", pVarPrefix));
    }

    return S_OK;
}

HRESULT
TestResourceMap::VerifyNamedResources(_In_ TestMapPrivate* pMap, _In_ PCWSTR pVarPrefix)
{
    TestDataArray<String> specs;
    String tmp;

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNamedResourcesInfo", pVarPrefix), specs)))
    {
        TestStringArray spec;
        StringResult gotName;

        Log::Comment(tmp.Format(L"[ Found %d %sExpectedNamedResourcesInfo  ]", (int)specs.GetSize(), pVarPrefix));

        for (unsigned i = 0; i < specs.GetSize(); i++)
        {
            Log::Comment(tmp.Format(L"[ Resource %d: %s ]", i, (PCWSTR)specs[i]));
            if (!spec.InitFromList(specs[i]))
            {
                Log::Warning(tmp.Format(L"[ Error parsing spec %d in %sExpectedNamedResourcesInfo ]", i, pVarPrefix));
                continue;
            }

            int itemIndex = -1;
            int expectedNumCandidates = -1;
            if ((spec.GetNumStrings() < 2) || (spec.GetNumStrings() > 3) || (!spec.TryGetStringAsInt(0, &itemIndex)) ||
                ((spec.GetNumStrings() == 3) && (!spec.TryGetStringAsInt(2, &expectedNumCandidates))))
            {
                Log::Warning(tmp.Format(L"[ Malformed expected item info \"%s\" ]", (PCWSTR)specs[i]));
                continue;
            }

            int gotNumCandidates = -1;
            PCWSTR pWantName = spec.GetString(1);

            if (pMap->pBuilder != nullptr)
            {
                VERIFY(pMap->pBuilder->TryGetResourceInfo(itemIndex, &gotName, &gotNumCandidates));
                VERIFY(gotName.ICompare(pWantName) == Def_Equal);
                VERIFY(gotNumCandidates == expectedNumCandidates);
            }
            if (pMap->pMap != nullptr)
            {
                NamedResourceResult namedResource;
                VERIFY_SUCCEEDED(pMap->pMap->GetResourceByIndex(itemIndex, &namedResource));
                VERIFY_SUCCEEDED(namedResource.GetResourceName(&gotName));
                VERIFY_ARE_EQUAL(expectedNumCandidates, namedResource.GetNumCandidates());
                VERIFY_ARE_EQUAL(Def_Equal, gotName.ICompare(pWantName));
            }
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNamedResourcesInfo not defined ]", pVarPrefix));
    }
    return S_OK;
}

HRESULT
TestResourceMap::VerifyDescendentResources(_In_ TestMapPrivate* pMap, _In_ PCWSTR pVarPrefix)
{
    TestDataArray<String> specs;
    String tmp;
    int expectedNumValues = -1;

    if (pMap->pSubtree == nullptr)
    {
        Log::Warning(tmp.Format(L"[ VerifyDescendentResources(\"%s\") requires subtree ]", pVarPrefix));
        return S_OK;
    }

    Log::Comment(tmp.Format(L"[ VerifyDescendentResources(\"%s\") ]", pVarPrefix));
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumDescendentResources", pVarPrefix), expectedNumValues)))
    {
        VERIFY(expectedNumValues == pMap->pSubtree->GetNumDescendentResources());
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumDescendentResources not specified ]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedDescendentResources", pVarPrefix), specs)))
    {
        TestStringArray spec;
        StringResult gotName;

        Log::Comment(tmp.Format(L"[ Found %d %sExpectedDescendentResources  ]", (int)specs.GetSize(), pVarPrefix));

        for (unsigned i = 0; i < specs.GetSize(); i++)
        {
            Log::Comment(tmp.Format(L"[ Resource %d: %s ]", i, (PCWSTR)specs[i]));
            if (!spec.InitFromList(specs[i]))
            {
                Log::Warning(tmp.Format(L"[ Error parsing spec %d in %sExpectedDescendentResources ]", i, pVarPrefix));
                continue;
            }

            int itemIndex = -1;
            int expectedNumCandidates = -1;
            if ((spec.GetNumStrings() < 2) || (spec.GetNumStrings() > 3) || (!spec.TryGetStringAsInt(0, &itemIndex)) ||
                ((spec.GetNumStrings() == 3) && (!spec.TryGetStringAsInt(2, &expectedNumCandidates))))
            {
                Log::Warning(tmp.Format(L"[ Malformed expected item info \"%s\" ]", (PCWSTR)specs[i]));
                continue;
            }

            PCWSTR pWantName = spec.GetString(1);

            NamedResourceResult namedResource;
            VERIFY_SUCCEEDED(pMap->pSubtree->GetDescendentResource(itemIndex, &namedResource));
            VERIFY_SUCCEEDED(pMap->pSubtree->GetDescendentResourceName(itemIndex, &gotName));
            VERIFY(namedResource.GetNumCandidates() == expectedNumCandidates);
            VERIFY(gotName.ICompare(pWantName) == Def_Equal);
        }
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedDescendentResourcesInfo not defined ]", pVarPrefix));
    }
    return S_OK;
}

HRESULT
TestResourceMap::VerifyDescendentScopes(_In_ TestMapPrivate* pMap, _In_ PCWSTR pVarPrefix)
{
    TestDataArray<String> specs;
    int scopeIndex = -1;
    String tmp;
    String specListString;
    int numScopes;
    StringResult name;
    StringResult atomName;

    if (pMap->pSubtree == nullptr)
    {
        Log::Warning(tmp.Format(L"[ VerifyDescendentScopes(\"%s\") requires subtree ]", pVarPrefix));
        return E_FAIL;
    }

    Log::Comment(tmp.Format(L"[ VerifyDescendentScopes(\"%s\") ]", pVarPrefix));
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumDescendentScopes", pVarPrefix), numScopes)))
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumDescendentScopes = %d ]", pVarPrefix, numScopes));
        VERIFY(numScopes == pMap->pSubtree->GetNumDescendentScopes());
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumDescendentScopes not specified ]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedDescendentScopes", pVarPrefix), specs)))
    {
        Log::Comment(tmp.Format(L"[ Found %d %sExpectedDescendentScopes ]", (int)specs.GetSize(), pVarPrefix));
        for (size_t i = 0; i < specs.GetSize(); i++)
        {
            TestStringArray expected;

            Log::Comment(tmp.Format(L"[ %sExpectedDescendentScopes %d: %s ]", pVarPrefix, (int)i, (PCWSTR)specs[i]));
            if ((!expected.InitFromList(specs[i])) || (expected.GetNumStrings() < 1) || (expected.GetNumStrings() > 3))
            {
                Log::Error(L"Malformed ExpectedDescendentScopes value");
                return E_FAIL;
            }

            // format is:  <scope index> ; <expected name> ; <expected num children>
            if (!expected.TryGetStringAsInt(0, &scopeIndex))
            {
                Log::Error(L"Malformed ExpectedScopes value");
                return E_FAIL;
            }

            VERIFY_SUCCEEDED(pMap->pSubtree->GetDescendentScopeName(scopeIndex, &name));

            int expectedIndex;
            if (expected.GetNumStrings() > 1)
            {
                // second value is expected name
                VERIFY(DefString_Compare(name.GetRef(), expected.GetString(1)) == Def_Equal);

                VERIFY(DefString_Compare(atomName.GetRef(), expected.GetString(1)) == Def_Equal);
            }

            if (expected.GetNumStrings() > 2)
            {
                AutoDeletePtr<const ResourceMapSubtree> pSubtree;
                VERIFY_SUCCEEDED(pMap->pSubtree->GetDescendentScopeSubtree(scopeIndex, &pSubtree));
                VERIFY(pSubtree != nullptr);

                // third value is expected number of children
                expectedIndex = -1;
                if (expected.TryGetStringAsInt(2, &expectedIndex))
                {
                    VERIFY(pSubtree->GetNumChildren() == expectedIndex);
                }
                else if (!DefString_IsEmpty(expected.GetString(2)))
                {
                    Log::Warning(L"Malformed number of children");
                    continue;
                }
            }
        }
    }
    else if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedDescendentScopesList", pVarPrefix), specListString)))
    {
        TestStringArray specList;
        if (!specList.InitFromList(specListString))
        {
            Log::Warning(tmp.Format(L"[ Couldn't parse %sExpectedDescendentScopesList ]", pVarPrefix));
            return E_FAIL;
        }

        Log::Comment(tmp.Format(L"[ Found %d %sExpectedDescendentScopesList ]", specList.GetNumStrings(), pVarPrefix));
        for (int i = 0; i < specList.GetNumStrings(); i++)
        {
            VERIFY_SUCCEEDED(pMap->pSubtree->GetDescendentScopeName(i, &name));
            VERIFY(DefString_Compare(name.GetRef(), specList.GetString(i)) == Def_Equal);
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %sExpectedDescendentScopes not specified ]", pVarPrefix));
    }
    return S_OK;
}

HRESULT
TestResourceMap::VerifyAllAgainstTestVars(_In_ TestMapPrivate* pMap, _In_ TestDecisionInfo* pTestDI, _In_ PCWSTR pVarPrefix)
{
    String tmp;

    Log::Comment(tmp.Format(L"[ Verifying TestResourceMap for \"%s\" ]", pVarPrefix));
    TestDecisionInfoValidator validateDI;
    bool checkDI = validateDI.TryInitDataFromTestVars(pVarPrefix);

    Log::Comment(tmp.Format(L"[ Validator decision info %s for \"%s\" ]", (checkDI ? L"found" : L"not found"), pVarPrefix));

    if (pMap->pBuilder != nullptr)
    {
        if (checkDI)
        {
            RETURN_IF_FAILED(validateDI.VerifyAll(pMap->pBuilder->GetDecisionInfo(), pMap->pEnvironment));
        }
        RETURN_HR_IF(E_FAIL, !TestHierarchicalSchema::TryVerifySchema(pMap->pBuilder->GetSchema(), pVarPrefix));
    }
    if (pMap->pMap != nullptr)
    {
        if (checkDI)
        {
            RETURN_IF_FAILED(validateDI.VerifyAll(pMap->pMap->GetDecisionInfo(), pMap->pEnvironment));
        }
        RETURN_HR_IF(E_FAIL, !TestHierarchicalSchema::TryVerifySchema(pMap->pMap->GetSchema(), pVarPrefix));
    }
    RETURN_IF_FAILED(VerifyNamedResources(pMap, pVarPrefix));
    RETURN_IF_FAILED(VerifyCandidates(pMap, pTestDI, pVarPrefix));
    // ok = VerifyDescendentScopes(pMap, pVarPrefix, pStatus);
    RETURN_IF_FAILED(VerifyDescendentResources(pMap, pVarPrefix));
    return S_OK;
}

} // namespace UnitTests
