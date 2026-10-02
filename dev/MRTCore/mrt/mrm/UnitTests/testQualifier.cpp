// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include <mrm/build/AIDict.h>
#include "Helpers.h"
#include "TestQualifier.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

bool TrySplitIndexInPlace(__inout PWSTR pIdStr, __out int* pIndexOut)
{
    PWSTR pIndexStr = NULL;

    *pIndexOut = -1;
    pIndexStr = wcschr(pIdStr, L'=');
    if (pIndexStr != NULL)
    {
        // has an index.  truncate the name and parse the index.
        if (swscanf_s(&pIndexStr[1], L"%d", pIndexOut) != 1)
        {
            String tmp;
            Log::Error(tmp.Format(L"[ illegal name: \"%s\" (index not integer)]", pIdStr));
            return false;
        }
        *pIndexStr = L'\0';
    }
    return true;
}

bool TrySplitIndex(__in PCWSTR pIdStr, __inout StringResult* pIdOut, __out int* pIndexOut)
{
    size_t pos = 0;

    *pIndexOut = -1;
    pIdOut->SetRef(pIdStr);
    if (pIdOut->TryFindFirstOf(L'=', &pos))
    {
        PCWSTR pIndexStr = &pIdOut->GetRef()[pos + 1];
        if (swscanf_s(pIndexStr, L"%d", pIndexOut) != 1)
        {
            String tmp;
            Log::Error(tmp.Format(L"[ illegal name: \"%s\" (index not integer)]", pIdStr));
            return false;
        }
        pIdOut->Truncate(pos);
    }
    return true;
}

TestQualifierCollection::TestQualifierCollection() : m_numQualifiers(0), m_pSpecs(NULL), m_pQualifiers(NULL) {}

TestQualifierCollection::~TestQualifierCollection() { Reset(); }

void TestQualifierCollection::Reset()
{
    delete[] m_pSpecs;
    delete[] m_pQualifiers;

    m_numQualifiers = 0;
    m_pSpecs = NULL;
    m_pQualifiers = NULL;
}

HRESULT
TestQualifierCollection::InitFromTestValue(__in PCWSTR pValue, __inout TestStringArray* pSpecsOut, __out TestQualifier* pQualifierOut)
{
    String tmp;
    PWSTR pIdStr;
    int index;

    SecureZeroMemory(pQualifierOut, sizeof(TestQualifier));

    if (!pSpecsOut->InitFromList(pValue) || (pSpecsOut->GetNumStrings() < 3))
    {
        Log::Error(tmp.Format(L"[ illegal qualifier spec: \"%s\" ]", pValue));
        return E_FAIL;
    }

    // Qualifier name is of the form "#<name>[=<index>]"
    // If present, <index> specifies the expected index
    pIdStr = pSpecsOut->GetWritableString(0);

    if (pIdStr[0] != L'#')
    {
        Log::Error(tmp.Format(L"[ illegal qualifier id \"%s\" (must start with '#')", pIdStr));
        return E_FAIL;
    }

    if (!TrySplitIndexInPlace(pIdStr, &index))
    {
        return E_FAIL;
    }

    pQualifierOut->pId = pIdStr;
    pQualifierOut->expectedIndexInPool = index;
    pQualifierOut->expectedIndexInSet = -1;
    pQualifierOut->present = 0;
    pQualifierOut->pQualifierName = pSpecsOut->GetString(1);
    pQualifierOut->pQualifierValue = pSpecsOut->GetString(2);
    pQualifierOut->priority = 0;
    pQualifierOut->fallbackScore = 0.0;

    if (pSpecsOut->GetNumStrings() > 3)
    {
        // if present, spec 3 is priority
        if (pSpecsOut->TryGetStringAsInt(3, &pQualifierOut->priority))
        {
            pQualifierOut->present |= TQFLAGS_PRIORITY_PRESENT;
        }
        else if (DefString_Compare(pSpecsOut->GetString(3), L"*"))
        {
            // '*' means use default.  Anything else that isn't an integer is an error.
            Log::Error(tmp.Format(L"[ illegal qualifier priority in \"%s\" (must be integer)", pValue));
            return E_FAIL;
        }
    }

    if (pSpecsOut->GetNumStrings() > 4)
    {
        // if present, spec 4 is fallback score
        if ((!pSpecsOut->TryGetStringAsDouble(4, &pQualifierOut->fallbackScore)) || (pQualifierOut->fallbackScore < 0.0) ||
            (pQualifierOut->fallbackScore > 1.0))
        {
            Log::Error(tmp.Format(L"[ illegal qualifier fallback score in \"%s\" (must be 0.0-1.1)", pValue));
            return E_FAIL;
        }
        pQualifierOut->present |= TQFLAGS_FALLBACK_SCORE_PRESENT;
    }

    if (pSpecsOut->GetNumStrings() > 5)
    {
        Log::Warning(tmp.Format(L"[ extra fields in qualifier spec \"%s\" ignored ]", pValue));
    }
    return S_OK;
}

HRESULT
TestQualifierCollection::InitFromTestVars(__in PCWSTR pPrefix, __in bool required)
{
    String tmp;

    Reset();
    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sQualifiers", pPrefix), m_testStrings)))
    {
        Log::Comment(tmp.Format(L"[ Qualifier spec: %sQualifiers not found - trying Qualifiers ]", pPrefix));
        if (FAILED(TestData::TryGetValue(L"Qualifiers", m_testStrings)))
        {
            if (required)
            {
                Log::Error(tmp.Format(L"[%s Qualifiers required but not specified ]", pPrefix));
            }
            else
            {
                Log::Warning(tmp.Format(L"[%s Qualifiers not specified ]", pPrefix));
            }
            return E_FAIL;
        }
        else
        {
            Log::Comment(L"[ Using Qualifiers ]");
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Using %sQualifiers ]", pPrefix));
    }

    m_numQualifiers = static_cast<UINT>(m_testStrings.GetSize());
    m_pSpecs = new TestStringArray[m_numQualifiers];
    m_pQualifiers = new TestQualifier[m_numQualifiers];

    for (int i = 0; i < m_numQualifiers; i++)
    {
        if (FAILED(InitFromTestValue(m_testStrings[i], &m_pSpecs[i], &m_pQualifiers[i])))
        {
            if (required)
            {
                Log::Error(tmp.Format(L"[ Couldn't initialize qualifier %d in %sQualifiers ]", i, pPrefix));
                return E_FAIL;
            }
            continue;
        }
    }
    return S_OK;
}

HRESULT
TestQualifierCollection::GetTestQualifier(__in int index, __out TestQualifier* pQualifierOut) const
{
    if ((index < 0) || (index >= m_numQualifiers))
    {
        SecureZeroMemory(pQualifierOut, sizeof(TestQualifier));
        return E_DEF_OUT_OF_RANGE;
    }
    *pQualifierOut = m_pQualifiers[index];
    return S_OK;
}

HRESULT
TestQualifierCollection::GetTestQualifier(__in PCWSTR pId, __out TestQualifier* pQualifierOut) const
{

    for (int i = 0; i < m_numQualifiers; i++)
    {
        if (DefString_ICompare(pId, m_pQualifiers[i].pId) == 0)
        {
            *pQualifierOut = m_pQualifiers[i];
            return S_OK;
        }
    }

    SecureZeroMemory(pQualifierOut, sizeof(TestQualifier));
    return E_DEF_KEY_NOT_FOUND;
}

bool TestQualifierCollection::TryGetQualifier(
    __in PCWSTR pId,
    __in const IDecisionInfo* pDecisions,
    __in const UnifiedEnvironment* pEnvironment,
    __inout QualifierResult* pQualifierOut) const
{
    TestQualifier qualifier;
    String tmp;

    if (FAILED(GetTestQualifier(pId, &qualifier)))
    {
        Log::Warning(tmp.Format(L"[ Qualifier \"%s\" not found ]", pId));
        return false;
    }
    return TryGetQualifier(&qualifier, pDecisions, pEnvironment, pQualifierOut);
}

bool TestQualifierCollection::TryGetQualifier(
    __in const TestQualifier* pTestSpec,
    __in const IDecisionInfo* pDecisions,
    __in const UnifiedEnvironment* pEnvironment,
    __inout_opt QualifierResult* pQualifierOut)
{
    String tmp;

    if (FAILED(pDecisions->GetQualifier(pTestSpec->expectedIndexInPool, pQualifierOut)))
    {
        Log::Warning(tmp.Format(L"[ Qualifier %d not found ]", pTestSpec->expectedIndexInPool));
        return false;
    }

    if (!TestDecisionInfoValidator::MatchQualifier(pDecisions, pEnvironment, pQualifierOut, pTestSpec))
    {
        Log::Warning(tmp.Format(L"[ Qualifier %d does not match ]", pTestSpec->expectedIndexInPool));
        return false;
    }

    return true;
}

HRESULT
TestQualifierCollection::GetOrAddQualifier(
    __in PCWSTR pId,
    __in DecisionInfoBuilder* pDecisions,
    __inout_opt QualifierResult* pQualifierOut)
{
    TestQualifier qualifier;
    RETURN_IF_FAILED(GetTestQualifier(pId, &qualifier));

    return GetOrAddQualifier(&qualifier, pDecisions, pQualifierOut);
}

HRESULT
TestQualifierCollection::GetOrAddQualifier(
    __in const TestQualifier* pTestSpec,
    __in DecisionInfoBuilder* pDecisions,
    __inout_opt QualifierResult* pQualifierOut)
{
    QualifierResult result;

    if ((pTestSpec->present & TQFLAGS_PRIORITY_PRESENT) != 0)
    {
        return pDecisions->GetOrAddQualifier(
            pTestSpec->pQualifierName,
            pTestSpec->pQualifierValue,
            static_cast<UINT16>(pTestSpec->priority),
            pTestSpec->fallbackScore,
            pQualifierOut);
    }

    return pDecisions->GetOrAddQualifier(pTestSpec->pQualifierName, pTestSpec->pQualifierValue, pTestSpec->fallbackScore, pQualifierOut);
}

TestQualifierSetCollection::TestQualifierSetCollection() : m_numQualifierSets(0), m_pSpecs(NULL), m_pQualifierSets(NULL) {}

TestQualifierSetCollection::~TestQualifierSetCollection() { Reset(); }

void TestQualifierSetCollection::Reset()
{
    delete[] m_pSpecs;
    if (m_pQualifierSets != NULL)
    {
        for (int i = 0; i < m_numQualifierSets; i++)
        {
            if (m_pQualifierSets[i].pQualifiers != NULL)
            {
                Def_Free(m_pQualifierSets[i].pQualifiers);
                m_pQualifierSets[i].pQualifiers = NULL;
            }
        }

        delete[] m_pQualifierSets;
        m_pQualifierSets = NULL;
    }
}

HRESULT
TestQualifierSetCollection::InitFromTestVars(__in PCWSTR pPrefix, __in TestQualifierCollection* pQualifiers, __in bool required)
{
    String tmp;
    PWSTR pIdStr;
    int index;
    StringResult nameStr;
    int indexInSet;

    Reset();

    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sQualifierSets", pPrefix), m_testStrings)))
    {
        Log::Comment(tmp.Format(L"[ QualifierSet spec: %sQualifierSets not found - trying QualifierSets ]", pPrefix));
        if (FAILED(TestData::TryGetValue(L"QualifierSets", m_testStrings)))
        {
            if (required)
            {
                Log::Error(tmp.Format(L"[%s Qualifier sets required but not specified ]", pPrefix));
            }
            else
            {
                Log::Warning(tmp.Format(L"[%s Qualifier sets not specified ]", pPrefix));
            }
            return E_FAIL;
        }
        else
        {
            Log::Comment(L"[ Using QualifierSets ]");
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Using %sQualifierSets ]", pPrefix));
    }

    m_numQualifierSets = static_cast<UINT>(m_testStrings.GetSize());
    m_pSpecs = new TestStringArray[m_numQualifierSets];
    m_pQualifierSets = new TestQualifierSet[m_numQualifierSets];

    for (int i = 0; i < m_numQualifierSets; i++)
    {
        if (!m_pSpecs[i].InitFromList(m_testStrings[i]) || (m_pSpecs[i].GetNumStrings() < 1))
        {
            Log::Warning(tmp.Format(L"[ illegal qualifier set spec: \"%s\" ]", (PCWSTR)m_testStrings[i]));
            return E_FAIL;
        }

        // Qualifier set name is of the form "$<name>[=<index>]"
        // If present, <index> specifies the expected index
        pIdStr = m_pSpecs[i].GetWritableString(0);

        if (pIdStr[0] != L'$')
        {
            Log::Warning(tmp.Format(L"[ illegal qualifier set id \"%s\" (must start with '$') ]", pIdStr));
            return E_FAIL;
        }

        if (!TrySplitIndexInPlace(pIdStr, &index))
        {
            return E_FAIL;
        }

        m_pQualifierSets[i].pId = pIdStr;
        m_pQualifierSets[i].expectedIndexInPool = index;
        m_pQualifierSets[i].expectedIndexInSet = -1;
        m_pQualifierSets[i].numQualifiers = m_pSpecs[i].GetNumStrings() - 1;
        if (m_pQualifierSets[i].numQualifiers > 0)
        {
            m_pQualifierSets[i].pQualifiers = _DefArray_AllocZeroed(TestQualifier, m_pQualifierSets[i].numQualifiers);
            RETURN_IF_NULL_ALLOC(m_pQualifierSets[i].pQualifiers);
        }
        else
        {
            m_pQualifierSets[i].pQualifiers = NULL;
        }

        for (int q = 0; q < m_pQualifierSets[i].numQualifiers; q++)
        {
            // spec is of the form #<name>[=<indexInSet>]
            PCWSTR pQualifierSpec = m_pSpecs[i].GetString(q + 1);
            if (!TrySplitIndex(pQualifierSpec, &nameStr, &indexInSet))
            {
                Log::Warning(tmp.Format(L"[ couldn't parse qualifier spec string ]"));
                return E_FAIL;
            }

            RETURN_IF_FAILED(pQualifiers->GetTestQualifier(nameStr.GetRef(), &m_pQualifierSets[i].pQualifiers[q]));
            m_pQualifierSets[i].pQualifiers[q].expectedIndexInSet = indexInSet;
        }
    }
    return S_OK;
}

HRESULT
TestQualifierSetCollection::GetTestQualifierSet(__in int index, __out TestQualifierSet* pQualifierSetOut) const
{
    if ((index < 0) || (index >= m_numQualifierSets))
    {
        SecureZeroMemory(pQualifierSetOut, sizeof(TestQualifierSet));
        return E_DEF_OUT_OF_RANGE;
    }
    *pQualifierSetOut = m_pQualifierSets[index];
    return S_OK;
}

HRESULT
TestQualifierSetCollection::GetTestQualifierSet(__in PCWSTR pId, __out TestQualifierSet* pQualifierSetOut) const
{
    for (int i = 0; i < m_numQualifierSets; i++)
    {
        if (DefString_ICompare(pId, m_pQualifierSets[i].pId) == Def_Equal)
        {
            *pQualifierSetOut = m_pQualifierSets[i];
            return S_OK;
        }
    }

    SecureZeroMemory(pQualifierSetOut, sizeof(TestQualifierSet));
    return E_DEF_KEY_NOT_FOUND;
}

bool TestQualifierSetCollection::TryGetQualifierSet(
    __in PCWSTR pId,
    __in const IDecisionInfo* pDecisions,
    __in const UnifiedEnvironment* pEnvironment,
    __inout_opt QualifierSetResult* pSetOut) const
{
    TestQualifierSet qs;
    String tmp;

    if (FAILED(GetTestQualifierSet(pId, &qs)))
    {
        Log::Warning(tmp.Format(L"[ Qualifier Set \"%s\" not found ]", pId));
        return false;
    }

    return TryGetMatchedQualifierSet(&qs, pDecisions, pEnvironment, pSetOut);
}

bool TestQualifierSetCollection::TryGetMatchedQualifierSet(
    __in const TestQualifierSet* pTestSpec,
    __in const IDecisionInfo* pDecisions,
    __in const UnifiedEnvironment* pEnvironment,
    __inout_opt QualifierSetResult* pSetOut)
{
    String tmp;

    // Enumerate the QualifierSet in IDecisionInfo and we expect to find one that matches the test's
    for (UINT i = 0; i < pDecisions->GetNumQualifierSets(); i++)
    {
        if (FAILED(pDecisions->GetQualifierSet(i, pSetOut)))
        {
            Log::Warning(tmp.Format(L"[ Expected to find Qualifier Set %d but failed ]", i));
            return false;
        }

        if (TestDecisionInfoValidator::MatchQualifierSet(pDecisions, pEnvironment, pSetOut, pTestSpec))
        {
            // Found it!
            return true;
        }
    }

    Log::Warning(tmp.Format(L"[ Unexpected: None of the QualifierSet in IDecisionInfo matches the test's Qualifier Set. ]"));
    return E_MRM_ITEM_NOT_FOUND;
}

HRESULT
TestQualifierSetCollection::GetOrAddQualifierSet(
    __in PCWSTR pId,
    __in DecisionInfoBuilder* pDecisions,
    __inout_opt QualifierSetResult* pSetOut)
{
    TestQualifierSet qs;

    RETURN_IF_FAILED(GetTestQualifierSet(pId, &qs));
    return GetOrAddQualifierSet(&qs, pDecisions, pSetOut);
}

HRESULT
TestQualifierSetCollection::GetOrAddQualifierSet(
    __in const TestQualifierSet* pTestSpec,
    __in DecisionInfoBuilder* pDecisions,
    __inout_opt QualifierSetResult* pSetOut)
{
    AutoDeletePtr<DecisionInfoQualifierSetBuilder> pSetBuilder;
    RETURN_IF_FAILED(DecisionInfoQualifierSetBuilder::CreateInstance(pDecisions, &pSetBuilder));
    TestQualifier tq;
    int gotIndex;
    int poolIndex;
    String tmp;

    for (int iQualifier = 0; iQualifier < pTestSpec->numQualifiers; iQualifier++)
    {
        tq = pTestSpec->pQualifiers[iQualifier];

        if ((tq.present & TQFLAGS_PRIORITY_PRESENT) != 0)
        {
            RETURN_IF_FAILED(pSetBuilder->AddQualifier(tq.pQualifierName, tq.pQualifierValue, tq.priority, tq.fallbackScore, &gotIndex));
        }
        else
        {
            RETURN_IF_FAILED(pSetBuilder->AddQualifier(tq.pQualifierName, tq.pQualifierValue, tq.fallbackScore, &gotIndex));
        }

        if (tq.expectedIndexInSet >= 0)
        {
            VERIFY(gotIndex == tq.expectedIndexInSet);
        }
        if (tq.expectedIndexInPool >= 0)
        {
            RETURN_IF_FAILED(pSetBuilder->GetQualifierIndexInPool(gotIndex, &poolIndex));

            VERIFY(poolIndex == tq.expectedIndexInPool);
        }
    }

    int index = -1;

    RETURN_IF_FAILED(pDecisions->GetOrAddQualifierSet(pSetBuilder, &index));
    RETURN_IF_FAILED(pDecisions->GetQualifierSet(index, pSetOut));
    return S_OK;
}

TestDecisionCollection::TestDecisionCollection() : m_numDecisions(0), m_pSpecs(NULL), m_pDecisions(NULL) {}

TestDecisionCollection::~TestDecisionCollection() { Reset(); }

void TestDecisionCollection::Reset()
{
    delete[] m_pSpecs;
    if (m_pDecisions != NULL)
    {
        for (int i = 0; i < m_numDecisions; i++)
        {
            if (m_pDecisions[i].pQualifierSets != NULL)
            {
                Def_Free(m_pDecisions[i].pQualifierSets);
                m_pDecisions[i].pQualifierSets = NULL;
            }
        }

        delete[] m_pDecisions;
        m_pDecisions = NULL;
    }
}

HRESULT
TestDecisionCollection::InitFromTestVars(__in PCWSTR pPrefix, __in TestQualifierSetCollection* pQualifierSets, __in bool required)
{
    String tmp;
    PWSTR pIdStr;
    StringResult nameStr;
    int index;
    int indexInSet;

    Reset();

    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sDecisions", pPrefix), m_testStrings)))
    {
        Log::Comment(tmp.Format(L"[ Decisions spec: %sDecisions not found - trying Decisions ]", pPrefix));
        if (FAILED(TestData::TryGetValue(L"Decisions", m_testStrings)))
        {
            if (required)
            {
                Log::Error(tmp.Format(L"[%s Decisions required but not specified ]", pPrefix));
            }
            else
            {
                Log::Warning(tmp.Format(L"[%s Decisions not specified ]", pPrefix));
            }
            return E_FAIL;
        }
        else
        {
            Log::Comment(L"[ Using Decisions ]");
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Using %sDecisions ]", pPrefix));
    }

    m_numDecisions = static_cast<int>(m_testStrings.GetSize());
    m_pSpecs = new TestStringArray[m_numDecisions];
    m_pDecisions = new TestDecision[m_numDecisions];

    for (int i = 0; i < m_numDecisions; i++)
    {
        if (!m_pSpecs[i].InitFromList(m_testStrings[i]) || (m_pSpecs[i].GetNumStrings() < 2))
        {
            Log::Warning(tmp.Format(L"[ illegal decision spec: \"%s\" ]", (PCWSTR)m_testStrings[i]));
            return E_FAIL;
        }

        // Decision name is of the form "@<name>[=<index>]"
        // If present, <index> specifies the expected index
        pIdStr = m_pSpecs[i].GetWritableString(0);

        if (pIdStr[0] != L'@')
        {
            Log::Warning(tmp.Format(L"[ illegal qualifier set id \"%s\" (must start with '@')", pIdStr));
            return E_FAIL;
        }

        if (!TrySplitIndexInPlace(pIdStr, &index))
        {
            return E_FAIL;
        }

        m_pDecisions[i].pId = pIdStr;
        m_pDecisions[i].expectedIndexInPool = index;
        m_pDecisions[i].numQualifierSets = m_pSpecs[i].GetNumStrings() - 1;
        m_pDecisions[i].pQualifierSets = _DefArray_AllocZeroed(TestQualifierSet, m_pDecisions[i].numQualifierSets);
        RETURN_IF_NULL_ALLOC(m_pDecisions[i].pQualifierSets);

        for (int q = 0; q < m_pDecisions[i].numQualifierSets; q++)
        {
            PCWSTR pQualifierSetSpec = m_pSpecs[i].GetString(q + 1);
            if (!TrySplitIndex(pQualifierSetSpec, &nameStr, &indexInSet))
            {
                Log::Warning(tmp.Format(L"[ couldn't parse qualifier set spec string ]"));
                return E_FAIL;
            }

            RETURN_IF_FAILED(pQualifierSets->GetTestQualifierSet(nameStr.GetRef(), &m_pDecisions[i].pQualifierSets[q]));

            m_pDecisions[i].pQualifierSets[q].expectedIndexInSet = indexInSet;
        }
    }
    return S_OK;
}

HRESULT
TestDecisionCollection::GetTestDecision(__in int index, __out TestDecision* pDecisionOut) const
{
    if ((index < 0) || (index >= m_numDecisions))
    {
        SecureZeroMemory(pDecisionOut, sizeof(TestDecision));
        return E_DEF_OUT_OF_RANGE;
    }
    *pDecisionOut = m_pDecisions[index];
    return S_OK;
}

HRESULT
TestDecisionCollection::GetTestDecision(__in PCWSTR pId, __out TestDecision* pDecisionOut) const
{
    for (int i = 0; i < m_numDecisions; i++)
    {
        if (DefString_ICompare(pId, m_pDecisions[i].pId) == 0)
        {
            *pDecisionOut = m_pDecisions[i];
            return S_OK;
        }
    }

    SecureZeroMemory(pDecisionOut, sizeof(TestDecision));
    return E_DEF_KEY_NOT_FOUND;
}

bool TestDecisionCollection::TryGetDecision(
    __in PCWSTR pId,
    __in const IDecisionInfo* pDecisions,
    __in const UnifiedEnvironment* pEnvironment,
    __inout DecisionResult* pDecisionOut) const
{
    TestDecision decision;
    String tmp;

    if (FAILED(GetTestDecision(pId, &decision)))
    {
        Log::Warning(tmp.Format(L"[ Decision \"%s\" not found ]", pId));
        return false;
    }
    return TryGetDecision(&decision, pDecisions, pEnvironment, pDecisionOut);
}

bool TestDecisionCollection::TryGetDecision(
    __in const TestDecision* pTestSpec,
    __in const IDecisionInfo* pDecisions,
    __in const UnifiedEnvironment* pEnvironment,
    __inout DecisionResult* pDecisionOut)
{
    String tmp;

    if (FAILED(pDecisions->GetDecision(pTestSpec->expectedIndexInPool, pDecisionOut)))
    {
        Log::Warning(tmp.Format(L"[ Decision %d not found ]", pTestSpec->expectedIndexInPool));
        return false;
    }

    if (!TestDecisionInfoValidator::Matches(pDecisions, pEnvironment, pDecisionOut, pTestSpec))
    {
        Log::Warning(tmp.Format(L"[ Decision %d does not match ]", pTestSpec->expectedIndexInPool));
        return false;
    }

    return true;
}

HRESULT
TestDecisionCollection::GetOrAddDecision(__in PCWSTR pId, __in DecisionInfoBuilder* pDecisions, __inout_opt DecisionResult* pDecisionOut)
{
    TestDecision decision;
    RETURN_IF_FAILED(GetTestDecision(pId, &decision));

    return GetOrAddDecision(&decision, pDecisions, pDecisionOut);
}

HRESULT
TestDecisionCollection::GetOrAddDecision(
    __in const TestDecision* pTestSpec,
    __in DecisionInfoBuilder* pDecisions,
    __inout_opt DecisionResult* pDecisionOut)
{
    AutoDeletePtr<DecisionBuilder> pDecisionBuilder;
    RETURN_IF_FAILED(DecisionBuilder::CreateInstance(pDecisions, &pDecisionBuilder));

    QualifierSetResult qs;
    int gotIndex;
    int poolIndex;

    for (int iDecision = 0; iDecision < pTestSpec->numQualifierSets; iDecision++)
    {
        RETURN_IF_FAILED(TestQualifierSetCollection::GetOrAddQualifierSet(&pTestSpec->pQualifierSets[iDecision], pDecisions, &qs));

        RETURN_IF_FAILED(pDecisionBuilder->AddQualifierSet(&qs, &gotIndex));

        if (pTestSpec->pQualifierSets[iDecision].expectedIndexInSet >= 0)
        {
            VERIFY(gotIndex == pTestSpec->pQualifierSets[iDecision].expectedIndexInSet);
        }

        if (pTestSpec->pQualifierSets[iDecision].expectedIndexInPool >= 0)
        {
            RETURN_IF_FAILED(pDecisionBuilder->GetQualifierSetIndexInPool(gotIndex, &poolIndex));

            VERIFY(poolIndex == pTestSpec->pQualifierSets[iDecision].expectedIndexInPool);
        }
    }

    int index = -1;

    RETURN_IF_FAILED(pDecisions->GetOrAddDecision(pDecisionBuilder, &index));
    RETURN_IF_FAILED(pDecisions->GetDecision(index, pDecisionOut));
    return S_OK;
}

TestDecisionInfo::TestDecisionInfo() {}

TestDecisionInfo::~TestDecisionInfo() {}

HRESULT
TestDecisionInfo::InitDataFromTestVars(__in PCWSTR pPrefix)
{
    String tmp;
    String altPrefix;

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sUsesDecisionInfo", pPrefix), altPrefix)))
    {
        Log::Comment(tmp.Format(L"[ Using prefix \"%s\" for \"%sUsesDecisionInfo ]", (PCWSTR)altPrefix, pPrefix));
        pPrefix = (PCWSTR)altPrefix;
    }

    RETURN_IF_FAILED(m_qualifiers.InitFromTestVars(pPrefix));
    RETURN_IF_FAILED(m_qualifierSets.InitFromTestVars(pPrefix, &m_qualifiers));
    RETURN_IF_FAILED(m_decisions.InitFromTestVars(pPrefix, &m_qualifierSets));

    return S_OK;
}

HRESULT
TestDecisionInfo::ApplyTestData(__inout DecisionInfoBuilder* pBuilder)
{
    String tmp;
    TestDecision td;
    TestQualifierSet tqs;
    TestQualifier tq;
    int gotIndex;
    int poolIndex;

    AutoDeletePtr<DecisionInfoQualifierSetBuilder> pSetBuilder;
    RETURN_IF_FAILED(DecisionInfoQualifierSetBuilder::CreateInstance(pBuilder, &pSetBuilder));
    AutoDeletePtr<DecisionBuilder> pDecisionBuilder;
    RETURN_IF_FAILED(DecisionBuilder::CreateInstance(pBuilder, &pDecisionBuilder));

    for (int iDecision = 0; iDecision < m_decisions.GetNumTestDecisions(); iDecision++)
    {
        RETURN_IF_FAILED(m_decisions.GetTestDecision(iDecision, &td));
        Log::Comment(tmp.Format(L"[ Applying '%s' ]", td.pId));

        pDecisionBuilder->Reset();
        for (int iSet = 0; iSet < td.numQualifierSets; iSet++)
        {
            tqs = td.pQualifierSets[iSet];
            Log::Comment(tmp.Format(L"[     Applying '%s' ]", tqs.pId));

            pSetBuilder->Reset();
            for (int iQualifier = 0; iQualifier < tqs.numQualifiers; iQualifier++)
            {
                tq = tqs.pQualifiers[iQualifier];
                Log::Comment(tmp.Format(L"[         Applying '%s' ]", tq.pId));

                if ((tq.present & TQFLAGS_PRIORITY_PRESENT) != 0)
                {
                    RETURN_IF_FAILED(
                        pSetBuilder->AddQualifier(tq.pQualifierName, tq.pQualifierValue, tq.priority, tq.fallbackScore, &gotIndex));
                }
                else
                {
                    RETURN_IF_FAILED(pSetBuilder->AddQualifier(tq.pQualifierName, tq.pQualifierValue, tq.fallbackScore, &gotIndex));
                }

                if (tq.expectedIndexInSet >= 0)
                {
                    VERIFY(gotIndex == tq.expectedIndexInSet);
                }
                if (tq.expectedIndexInPool >= 0)
                {
                    RETURN_IF_FAILED(pSetBuilder->GetQualifierIndexInPool(gotIndex, &poolIndex));

                    VERIFY(poolIndex == tq.expectedIndexInPool);
                }
                Log::Comment(tmp.Format(L"[         Done applying '%s' ]", tq.pId));
            }

            RETURN_IF_FAILED(pDecisionBuilder->AddQualifierSet(pSetBuilder, &gotIndex));

            if (tqs.expectedIndexInSet >= 0)
            {
                VERIFY(gotIndex == tqs.expectedIndexInSet);
            }
            if (tqs.expectedIndexInPool >= 0)
            {
                RETURN_IF_FAILED(pDecisionBuilder->GetQualifierSetIndexInPool(gotIndex, &poolIndex));

                VERIFY(poolIndex == tqs.expectedIndexInPool);
            }
            Log::Comment(tmp.Format(L"[     Done applying '%s' ]", tqs.pId));
        }

        RETURN_IF_FAILED(pBuilder->GetOrAddDecision(pDecisionBuilder, &gotIndex));

        // if the testDecision has an expected index, make sure we got it
        if (td.expectedIndexInPool >= 0)
        {
            VERIFY(gotIndex == td.expectedIndexInPool);
        }
        Log::Comment(tmp.Format(L"[ Done applying '%s' ]", td.pId));
    }
    return S_OK;
}

TestDecisionInfoValidator::TestDecisionInfoValidator() :
    m_expectedNumQualifiers(-1), m_expectedNumQualifierSets(-1), m_expectedNumDecisions(-1)
{}

TestDecisionInfoValidator::~TestDecisionInfoValidator() {}

HRESULT
TestDecisionInfoValidator::InitDataFromTestVars(__in PCWSTR pPrefix)
{
    String tmp;
    String altPrefix;

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sValidatorUsesDecisionInfo", pPrefix), altPrefix)))
    {
        Log::Comment(tmp.Format(L"[ Using prefix \"%s\" for \"%sValidatorUsesDecisionInfo ]", (PCWSTR)altPrefix, pPrefix));
        pPrefix = (PCWSTR)altPrefix;
    }
    else
    {
        Log::Warning(tmp.Format(L"[ %sValidatorUsesDecisionInfo not found ]", pPrefix));
    }

    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumQualifiers", pPrefix), m_expectedNumQualifiers)))
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumQualifiers not defined ]", pPrefix));
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumQualifiers = %d ]", pPrefix, m_expectedNumQualifiers));
    }

    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumQualifierSets", pPrefix), m_expectedNumQualifierSets)))
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumQualifierSets not defined ]", pPrefix));
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumQualifierSets = %d ]", pPrefix, m_expectedNumQualifierSets));
    }

    if (FAILED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumDecisions", pPrefix), m_expectedNumDecisions)))
    {
        Log::Warning(tmp.Format(L"[ %sExpectedNumDecisions not defined ]", pPrefix));
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %sExpectedNumDecisions = %d ]", pPrefix, m_expectedNumDecisions));
    }

    if (FAILED(m_qualifiers.InitFromTestVars(tmp.Format(L"%sExpected", pPrefix))))
    {
        Log::Warning(tmp.Format(L"[ %sExpected: test qualifiers not defined ]", pPrefix));
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Test qualifiers found for %sExpected ]", pPrefix));
    }

    if (FAILED(m_qualifierSets.InitFromTestVars(tmp.Format(L"%sExpected", pPrefix), &m_qualifiers)))
    {
        Log::Warning(tmp.Format(L"[ %sExpected: test qualifier sets not defined ]", pPrefix));
    }
    else
    {
        Log::Comment(tmp.Format(L"[ Test qualifiers found for %sExpected ]", pPrefix));
    }

    RETURN_IF_FAILED(m_decisions.InitFromTestVars(tmp.Format(L"%sExpected", pPrefix), &m_qualifierSets));
    Log::Comment(tmp.Format(L"[ Test decisions found for %sExpected ]", pPrefix));

    return S_OK;
}

bool TestDecisionInfoValidator::TryInitDataFromTestVars(__in PCWSTR pPrefix)
{
    String tmp;
    String altPrefix;
    // return true if we find anything actionable at all, false otherwise

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sValidatorUsesDecisionInfo", pPrefix), altPrefix)))
    {
        Log::Comment(tmp.Format(L"[ Using prefix \"%s\" for \"%sValidatorUsesDecisionInfo ]", (PCWSTR)altPrefix, pPrefix));
        pPrefix = (PCWSTR)altPrefix;
    }

    return (
        SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumQualifiers", pPrefix), m_expectedNumQualifiers)) ||
        SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumQualifierSets", pPrefix), m_expectedNumQualifierSets)) ||
        SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%sExpectedNumDecisions", pPrefix), m_expectedNumDecisions)) ||
        SUCCEEDED(m_qualifiers.InitFromTestVars(tmp.Format(L"%sExpected", pPrefix), false)) ||
        SUCCEEDED(m_qualifierSets.InitFromTestVars(tmp.Format(L"%sExpected", pPrefix), &m_qualifiers, false)) ||
        SUCCEEDED(m_decisions.InitFromTestVars(tmp.Format(L"%sExpected", pPrefix), &m_qualifierSets, false)));
}

HRESULT
TestDecisionInfoValidator::ValidateQualifiers(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment)
{
    Log::Comment(L"[ Validating Qualifiers ]");
    if (m_expectedNumQualifiers >= 0)
    {
        VERIFY(m_expectedNumQualifiers <= pDecisionInfo->GetNumQualifiers());
    }

    TestQualifier tq;
    QualifierResult qualifier;

    for (int i = 0; i < m_qualifiers.GetNumTestQualifiers(); i++)
    {
        if (FAILED(m_qualifiers.GetTestQualifier(i, &tq)))
        {
            Log::Warning(L"[ Unexpected error getting test qualifier ]");
            continue;
        }
        if (tq.expectedIndexInPool >= 0)
        {
            VERIFY_SUCCEEDED(pDecisionInfo->GetQualifier(tq.expectedIndexInPool, &qualifier));
            VERIFY(MatchQualifier(pDecisionInfo, pEnvironment, &qualifier, &tq));
        }
        else
        {
            Log::Warning(L"[ Unable to validate qualifier - expected index not specified ]");
        }
    }

    return S_OK;
}

HRESULT
TestDecisionInfoValidator::ValidateQualifierSets(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment)
{
    Log::Comment(L"[ Validating Qualifier Sets ]");
    if (m_expectedNumQualifierSets > 0)
    {
        VERIFY(m_expectedNumQualifierSets == pDecisionInfo->GetNumQualifierSets());
    }

    TestQualifierSet tqs;
    QualifierSetResult qualifierSet;

    for (int i = 0; i < m_qualifierSets.GetNumTestQualifierSets(); i++)
    {
        if (FAILED(m_qualifierSets.GetTestQualifierSet(i, &tqs)))
        {
            Log::Warning(L"[ Unexpected error getting test qualifier set ]");
            continue;
        }

        if (tqs.expectedIndexInPool >= 0)
        {
            VERIFY_SUCCEEDED(pDecisionInfo->GetQualifierSet(tqs.expectedIndexInPool, &qualifierSet));
            VERIFY(MatchQualifierSet(pDecisionInfo, pEnvironment, &qualifierSet, &tqs));
        }
        else
        {
            Log::Warning(L"[ Unable to validate qualifier set - expected index not specified ]");
        }
    }
    return S_OK;
}

HRESULT
TestDecisionInfoValidator::ValidateDecisions(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment)
{
    Log::Comment(L"[ Validating Decisions ]");
    if (m_expectedNumDecisions > 0)
    {
        VERIFY(m_expectedNumDecisions == pDecisionInfo->GetNumDecisions());
    }

    TestDecision td;
    DecisionResult decision;

    for (int i = 0; i < m_decisions.GetNumTestDecisions(); i++)
    {
        if (FAILED(m_decisions.GetTestDecision(i, &td)))
        {
            Log::Warning(L"[ Unexpected error getting test decision ]");
            continue;
        }

        if (td.expectedIndexInPool >= 0)
        {
            VERIFY_SUCCEEDED(pDecisionInfo->GetDecision(td.expectedIndexInPool, &decision));
            VERIFY(Matches(pDecisionInfo, pEnvironment, &decision, &td));
        }
        else
        {
            Log::Warning(L"[ Unable to validate decision - expected index not specified ]");
        }
    }
    return S_OK;
}

HRESULT
TestDecisionInfoValidator::VerifyAll(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment)
{
    RETURN_IF_FAILED(ValidateQualifiers(pDecisionInfo, pEnvironment));
    RETURN_IF_FAILED(ValidateQualifierSets(pDecisionInfo, pEnvironment));
    RETURN_IF_FAILED(ValidateDecisions(pDecisionInfo, pEnvironment));

    return S_OK;
}

bool TestDecisionInfoValidator::MatchQualifier(
    __in const IDecisionInfo*,
    __in const UnifiedEnvironment* pEnvironment,
    __in const IQualifier* pQualifier,
    __in const TestQualifier* pTestQualifier)
{
    ResourceQualifier wantQual;
    Atom haveQual;
    StringResult haveValue;

    // compare names
    if ((FAILED(pEnvironment->GetResourceQualifier(pTestQualifier->pQualifierName, &wantQual))) ||
        (FAILED(pQualifier->GetOperand1Attribute(&haveQual))) || (!haveQual.IsEqual(wantQual.name)))
    {
        return false;
    }

    if ((FAILED(pQualifier->GetOperand2Literal(&haveValue))) ||
        (haveValue.CompareWithOptions(pTestQualifier->pQualifierValue, DefCompare_CaseInsensitive) != Def_Equal))
    {
        return false;
    }

    if (((pTestQualifier->present & TQFLAGS_PRIORITY_PRESENT) != 0) && (pTestQualifier->priority != pQualifier->GetPriority()))
    {
        return false;
    }

    if ((pTestQualifier->present & TQFLAGS_FALLBACK_SCORE_PRESENT) != 0)
    {
        int iWant = static_cast<int>(pTestQualifier->fallbackScore * IQualifier::MaxFallbackScore);
        double fallbackScore;
        pQualifier->GetFallbackScore(&fallbackScore);
        int iHave = static_cast<int>(fallbackScore * IQualifier::MaxFallbackScore);
        if (iWant != iHave)
        {
            return false;
        }
    }

    return true;
}

bool TestDecisionInfoValidator::MatchQualifierSet(
    __in const IDecisionInfo* pDecisionInfo,
    __in const UnifiedEnvironment* pEnvironment,
    __in const IQualifierSet* pQualifierSet,
    __in const TestQualifierSet* pTestQualifierSet)
{
    if (pQualifierSet->GetNumQualifiers() != pTestQualifierSet->numQualifiers)
    {
        return false;
    }

    // Two QualifierSet match each other if they have the same set of qualifiers.
    // The orders of the qualifiers do not have to match.
    for (int i = 0; i < pTestQualifierSet->numQualifiers; i++)
    {
        const TestQualifier* pTestQualifier = &pTestQualifierSet->pQualifiers[i];
        bool foundMatched = false;
        // We expect to find one qualier in pQualifierSet in that matches pTestQualifier
        for (int j = 0; j < pQualifierSet->GetNumQualifiers(); j++)
        {
            QualifierResult qualifier;
            int indexInPool;
            if (FAILED(pQualifierSet->GetQualifier(j, &qualifier, &indexInPool)))
            {
                return false;
            }

            if (MatchQualifier(pDecisionInfo, pEnvironment, &qualifier, pTestQualifier))
            {
                // Found a match
                foundMatched = true;
                break;
            }
        }

        if (!foundMatched)
        {
            // No match found error out
            return false;
        }
    }

    return true;
}

bool TestDecisionInfoValidator::Matches(
    __in const IDecisionInfo* pDecisionInfo,
    __in const UnifiedEnvironment* pEnvironment,
    __in const IDecision* pDecision,
    __in const TestDecision* pTestDecision)
{
    if (pTestDecision->expectedIndexInPool >= 0)
    {
        VERIFY(pDecision->GetIndex() == pTestDecision->expectedIndexInPool);
    }

    VERIFY((pDecision->GetNumQualifierSets() == pTestDecision->numQualifierSets));

    QualifierSetResult qualifierSet;
    int indexInPool;

    for (int i = 0; i < pTestDecision->numQualifierSets; i++)
    {
        const TestQualifierSet* pTestQualifierSet = &pTestDecision->pQualifierSets[i];

        if (pTestQualifierSet->expectedIndexInPool >= 0)
        {
            if (FAILED(pDecision->GetQualifierSet(i, &qualifierSet, &indexInPool)))
            {
                Log::Error(L"[ Unexpected error getting qualifier set from decision ]");
                return false;
            }
            VERIFY(pTestQualifierSet->expectedIndexInPool == indexInPool);
            VERIFY(MatchQualifierSet(pDecisionInfo, pEnvironment, &qualifierSet, pTestQualifierSet));
        }
        else
        {
            Log::Warning(L"[ No expected pool index in decision test ]");
        }
    }
    return true;
}

} // namespace UnitTests
