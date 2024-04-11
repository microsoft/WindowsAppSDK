// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include <mrm/build/AIDict.h>
#include "Helpers.h"
#include "TestReverseMap.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

TestReverseFileMap::TestReverseFileMap() : m_build(), m_pPriBuilder(NULL), m_pReverseFileMapBuilder(NULL), m_pReverseFileMap(NULL) {}

HRESULT
TestReverseFileMap::InitFromTestVars(__in PriSectionBuilder* pPriBuilder, __in UnifiedEnvironment* pEnvironment, __in PCWSTR pVarPrefix)
{
    String tmp;
    String simpleid;

    Release();

    // Initialize TestDI
    RETURN_IF_FAILED(m_testDI.InitDataFromTestVars(pVarPrefix));

    Log::Comment(tmp.Format(L"[ Using test decision info from \"%s\" ]", pVarPrefix));
    m_pTestDI = &m_testDI;

    m_pPriBuilder = pPriBuilder;
    ResourceMapSectionBuilder* pResourceMapSectionBuilder = nullptr;

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sSimpleId", pVarPrefix), simpleid)))
    {
        pResourceMapSectionBuilder = pPriBuilder->GetResourceMapBuilder(simpleid);
        VERIFY(pResourceMapSectionBuilder != NULL);
    }
    else
    {
        RETURN_IF_FAILED(pPriBuilder->GetOrAddPrimaryResourceMapBuilder(&pResourceMapSectionBuilder));
        VERIFY(pResourceMapSectionBuilder != NULL);
    }

    // Store decision info
    m_pDecisionInfo = pResourceMapSectionBuilder->GetDecisionInfo();

    // Create Reverse Map Section Builder
    RETURN_IF_FAILED(ReverseFileMapSectionBuilder::CreateInstance(pPriBuilder, pEnvironment, &m_pReverseFileMapBuilder));

    int indexOut;
    DynamicArray<ResourceMapSectionBuilder*> resMapSectionBuilders;
    VERIFY_SUCCEEDED(resMapSectionBuilders.Add(pResourceMapSectionBuilder, &indexOut));

    // Populate the file list and the reverse map section
    VERIFY_SUCCEEDED(m_pReverseFileMapBuilder->GenerateMap(&resMapSectionBuilders));

    return S_OK;
}

void TestReverseFileMap::Release()
{
    delete m_pReverseFileMap;
    m_pReverseFileMap = NULL;

    delete m_pReverseFileMapBuilder;
    m_pReverseFileMapBuilder = NULL;

    m_pPriBuilder = NULL;
}

HRESULT
TestReverseFileMap::Build() { return m_build.Build(m_pReverseFileMapBuilder); }

HRESULT
TestReverseFileMap::CreateReader()
{
    return ReverseFileMap::CreateInstance(m_build.GetBuffer(), m_build.GetBufferSize(), &m_pReverseFileMap);
}

HRESULT
TestReverseFileMap::Finalize()
{
    VERIFY_SUCCEEDED(m_pReverseFileMapBuilder->Finalize());
    return S_OK;
}

HRESULT
TestReverseFileMap::VerifyCandidate(
    __in ReverseFileMap* pReverseMap,
    __in PCWSTR pWantCandidateValue,
    __in int wantNamedResourceIndex,
    __in int wantQualifierSetIndex)
{
    String tmp;
    int candidateRevMapIndex;
    int gotQualifierSetIndex = 0;
    int gotNamedResourceIndex = 0;
    if (pReverseMap->TryGetReverseMapCandidateIndex(pWantCandidateValue, &candidateRevMapIndex))
    {
        VERIFY_SUCCEEDED(pReverseMap->GetCandidateInfo(candidateRevMapIndex, &gotQualifierSetIndex, &gotNamedResourceIndex));
        VERIFY(wantQualifierSetIndex == gotQualifierSetIndex);
        VERIFY(wantNamedResourceIndex == gotNamedResourceIndex);
    }
    else
    {
        Log::Error(tmp.Format(L"Candidate value not found in the reverse map \"%s\"", pWantCandidateValue));
        return E_FAIL;
    }
    return S_OK;
}

HRESULT
TestReverseFileMap::VerifyAllAgainstTestVars(
    __in ReverseFileMap* pReverseMap,
    __in const UnifiedEnvironment* pEnvironment,
    __in const IResourceMapBase* pResourceMapBase,
    __in TestDecisionInfo* pTestDI,
    __in IDecisionInfo* pDecisionInfo,
    __in PCWSTR pVarPrefix)
{
    TestDataArray<String> specs;
    String tmp;
    int expectedNumCandidates = -1;

    Log::Comment(tmp.Format(L"[ Verifying candidates for \"%s\" ]", pVarPrefix));

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumCandidates", pVarPrefix), expectedNumCandidates)))
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumCandidates = %d  ]", pVarPrefix, expectedNumCandidates));
        VERIFY(pReverseMap->GetNumEntries() == expectedNumCandidates);
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumCandidates not defined ]", pVarPrefix));
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

            PCWSTR pResourceName = NULL;
            int itemIndex = -1;
            int candidateIndex = -1;
            // format is:  item ; candidate index; value type; qualifier set name; value
            // where:
            //   - 'item' is a string
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

            if (!pTestDI->GetQualifierSetData()->TryGetQualifierSet(spec.GetString(3), pDecisionInfo, pEnvironment, &wantQualifiers))
            {
                Log::Warning(tmp.Format(L"[ Malformed expected candidate info \"%s\" - unknown qualifier set ]", (PCWSTR)specs[iSpec]));
                continue;
            }

            // Get resource index
            NamedResourceResult namedResourceResult;
            VERIFY_SUCCEEDED(pResourceMapBase->GetResource(pResourceName, &namedResourceResult));
            int wantResourceIndex = namedResourceResult.GetResourceIndexInSchema();

            VerifyCandidate(pReverseMap, spec.GetString(4), wantResourceIndex, wantQualifiers.GetIndex());
        }
    }
    return S_OK;
}

} // namespace UnitTests