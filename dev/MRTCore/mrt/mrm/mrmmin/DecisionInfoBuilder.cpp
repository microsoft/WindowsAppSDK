// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"
#include "DecisionInfo.h"
#include "mrm/readers/RemapInfo.h"

namespace Microsoft::Resources::Build
{

class DecisionInfoBuilderData : public IRawDecisionInfo
{
public:
    static HRESULT CreateInstance(
        _In_ const DecisionInfoBuilder* pPool,
        _In_ const UnifiedEnvironment* pEnvironment,
        _Outptr_ DecisionInfoBuilderData** result)
    {
        *result = nullptr;
        RETURN_HR_IF_NULL(E_INVALIDARG, pEnvironment);

        AutoDeletePtr<DecisionInfoBuilderData> pRtrn = new DecisionInfoBuilderData();
        RETURN_IF_NULL_ALLOC(pRtrn);

        RETURN_IF_FAILED(pRtrn->Init(pPool, pEnvironment));
        *result = pRtrn.Detach();

        return S_OK;
    }

    ~DecisionInfoBuilderData()
    {
        delete m_pBaseQualifiers;
        delete m_pQualifiers;
        delete m_pQualifierSets;
        delete m_pDecisions;
        delete m_pReferences;
        delete m_pLiteralsStringPool;

        m_pBaseQualifiers = nullptr;
        m_pQualifiers = nullptr;
        m_pQualifierSets = nullptr;
        m_pDecisions = nullptr;
        m_pReferences = nullptr;
        m_pLiteralsStringPool = nullptr;
    }

    const IDecisionInfo* GetPool() const { return m_pPool; }
    const RemapAtomPool* GetQualifierMapping() const { return nullptr; }
    const UnifiedEnvironment* GetEnvironment() const { return m_pEnvironment; }

    int GetNumBaseQualifiers() const { return m_pBaseQualifiers->Count(); }
    int GetNumQualifiers() const { return m_pQualifiers->Count(); }
    int GetNumQualifierSets() const { return m_pQualifierSets->Count(); }
    int GetNumDecisions() const { return m_pDecisions->Count(); }
    int GetNumReferences() const { return m_pReferences->Count(); }

    UINT32 GetLiteralsSizeInChars() const { return m_pLiteralsStringPool->GetNumCharsInPool(); }

    HRESULT GetBaseQualifier(_In_ int index, _Out_ MRMFILE_BASE_QUALIFIER* pQualifierOut) const
    {
        if (!m_pBaseQualifiers->TryGet(index, pQualifierOut))
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }

    HRESULT GetQualifier(_In_ int index, _Out_ MRMFILE_QUALIFIER* pQualifierOut) const
    {
        if (!m_pQualifiers->TryGet(index, pQualifierOut))
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }

    HRESULT GetQualifierSet(_In_ int index, _Out_ MRMFILE_QUALIFIER_SET* pQualifierSetOut) const
    {
        if (!m_pQualifierSets->TryGet(index, pQualifierSetOut))
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }

    HRESULT GetDecision(_In_ int index, _Out_ MRMFILE_DECISION* pDecisionOut) const
    {
        if (!m_pDecisions->TryGet(index, pDecisionOut))
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }

    HRESULT GetReference(_In_ int index, _Out_ UINT16* pReferenceOut) const
    {
        if (!m_pReferences->TryGet(index, pReferenceOut))
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }

    HRESULT GetLiteral(_In_ int offset, _Inout_ StringResult* pLiteralOut) const
    {
        return m_pLiteralsStringPool->GetString(offset, pLiteralOut);
    }

    HRESULT GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const
    {
        if ((index >= 0) && (index < m_pDecisions->Count()))
        {
            *pNumSetsOut = m_pDecisions->GetAll()[index].numQualifierSetRefs;
            return S_OK;
        }
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    DynamicArray<MRMFILE_BASE_QUALIFIER>* GetBaseQualifiers() const { return m_pBaseQualifiers; }
    DynamicArray<MRMFILE_QUALIFIER>* GetQualifiers() const { return m_pQualifiers; }
    DynamicArray<MRMFILE_QUALIFIER_SET>* GetQualifierSets() const { return m_pQualifierSets; }

    DynamicArray<MRMFILE_DECISION>* GetDecisions() const { return m_pDecisions; }

    DynamicArray<UINT16>* GetReferences() const { return m_pReferences; }
    WriteableStringPool* GetLiteralsStringPool() const { return m_pLiteralsStringPool; }

private:
    DecisionInfoBuilderData() :
        m_pPool(nullptr),
        m_pEnvironment(nullptr),
        m_pBaseQualifiers(nullptr),
        m_pQualifiers(nullptr),
        m_pQualifierSets(nullptr),
        m_pDecisions(nullptr),
        m_pReferences(nullptr),
        m_pLiteralsStringPool(nullptr)
    {}

    HRESULT Init(_In_ const DecisionInfoBuilder* pPool, _In_ const UnifiedEnvironment* pEnvironment)
    {
        m_pPool = pPool;
        m_pEnvironment = pEnvironment;

        RETURN_IF_FAILED(DynamicArray<MRMFILE_BASE_QUALIFIER>::CreateInstance(InitialQualifiersSize, &m_pBaseQualifiers));
        RETURN_IF_FAILED(DynamicArray<MRMFILE_QUALIFIER>::CreateInstance(InitialQualifiersSize, &m_pQualifiers));
        RETURN_IF_FAILED(DynamicArray<MRMFILE_QUALIFIER_SET>::CreateInstance(InitialQualifierSetsSize, &m_pQualifierSets));
        RETURN_IF_FAILED(DynamicArray<MRMFILE_DECISION>::CreateInstance(InitialDecisionsSize, &m_pDecisions));
        RETURN_IF_FAILED(DynamicArray<UINT16>::CreateInstance(InitialReferencesSize, &m_pReferences));
        RETURN_IF_FAILED(
            WriteableStringPool::CreateInstance(InitialLiteralsSize, WriteableStringPool::fCompareCaseInsensitive, &m_pLiteralsStringPool));

        return S_OK;
    }

    const DecisionInfoBuilder* m_pPool;
    const UnifiedEnvironment* m_pEnvironment;

    DynamicArray<MRMFILE_BASE_QUALIFIER>* m_pBaseQualifiers;
    DynamicArray<MRMFILE_QUALIFIER>* m_pQualifiers;
    DynamicArray<MRMFILE_QUALIFIER_SET>* m_pQualifierSets;
    DynamicArray<MRMFILE_DECISION>* m_pDecisions;

    DynamicArray<UINT16>* m_pReferences;
    WriteableStringPool* m_pLiteralsStringPool;

    static const int InitialQualifiersSize = 8;
    static const int InitialQualifierSetsSize = 8;
    static const int InitialDecisionsSize = 8;
    static const int InitialReferencesSize = 16;
    static const int InitialLiteralsSize = 128;
};

HRESULT DecisionInfoBuilder::CreateInstance(
    _In_ UINT32 flags,
    _In_ const UnifiedEnvironment* environment,
    _In_opt_ const IDecisionInfo* baseDecisionInfo,
    _Outptr_ DecisionInfoBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, environment);

    AutoDeletePtr<DecisionInfoBuilder> rtrn = new DecisionInfoBuilder;
    RETURN_IF_NULL_ALLOC(rtrn);
    RETURN_IF_FAILED(rtrn->Init(flags, environment));

    if (baseDecisionInfo != nullptr)
    {
        RETURN_IF_FAILED(rtrn->Merge(baseDecisionInfo));
    }

    *result = rtrn.Detach();

    return S_OK;
}

HRESULT DecisionInfoBuilder::Init(_In_ UINT32 flags, _In_ const UnifiedEnvironment* environment)
{
    m_flags = flags;
    RETURN_IF_FAILED(DecisionInfoBuilderData::CreateInstance(this, environment, &m_pData));

    RETURN_IF_FAILED(InitDefaultContents());
    return S_OK;
}

DecisionInfoBuilder::~DecisionInfoBuilder() { delete m_pData; }

HRESULT DecisionInfoBuilder::InitDefaultContents()
{
    int index = -1;
    MRMFILE_BASE_QUALIFIER baseAlwaysTrueQualifier;
    baseAlwaysTrueQualifier.attribute.uVal = 0;
    baseAlwaysTrueQualifier.op.s.poolIndex = 0;
    baseAlwaysTrueQualifier.op.s.index = static_cast<UINT16>(ICondition::TrueOp);
    baseAlwaysTrueQualifier.valueOffset = 0;
    RETURN_IF_FAILED(m_pData->GetBaseQualifiers()->Add(baseAlwaysTrueQualifier, &index));
    DEF_ASSERT(index == 0);

    // First add the always true qualifier
    MRMFILE_QUALIFIER alwaysTrueQualifier;
    alwaysTrueQualifier.baseQualifierIndex = 0;
    alwaysTrueQualifier.fallbackScore = 0;
    alwaysTrueQualifier.priority = 0;
    alwaysTrueQualifier.pad = 0;

    index = -1;
    RETURN_IF_FAILED(m_pData->GetQualifiers()->Add(alwaysTrueQualifier, &index));
    DEF_ASSERT(index == 0);

    // Now add the unconditional set, which has no qualifiers
    MRMFILE_QUALIFIER_SET unconditionalSet;
    unconditionalSet.firstQualifierRef = 0;
    unconditionalSet.numQualifierRefs = 0;

    index = -1;
    RETURN_IF_FAILED(m_pData->GetQualifierSets()->Add(unconditionalSet, &index));
    DEF_ASSERT(index == 0);

    // Now add the empty decision, which has no values.
    MRMFILE_DECISION emptyDecision;
    emptyDecision.firstQualifierSetRef = 0;
    emptyDecision.numQualifierSetRefs = 0;

    index = -1;
    RETURN_IF_FAILED(m_pData->GetDecisions()->Add(emptyDecision, &index));
    DEF_ASSERT(index == 0);

    // Now add the neutral-only decision, which has a single
    // value that uses the unconditional set.
    MRMFILE_DECISION neutralOnlyDecision;
    neutralOnlyDecision.firstQualifierSetRef = 0;
    neutralOnlyDecision.numQualifierSetRefs = 1;

    index = -1;
    RETURN_IF_FAILED(m_pData->GetDecisions()->Add(neutralOnlyDecision, &index));
    DEF_ASSERT(index == 1);

    // Now add the reference to the unconditional set used by the neutral only
    // decision.
    RETURN_IF_FAILED(m_pData->GetReferences()->Add(0, &index));
    DEF_ASSERT(index == 0);

    return S_OK;
}

HRESULT DecisionInfoBuilder::Merge(
    _In_ const IDecisionInfo* pMerge,
    _Inout_opt_ RemapUInt16* pQualifierMapOpt,
    _Inout_opt_ RemapUInt16* pQualifierSetMapOpt,
    _Inout_opt_ RemapUInt16* pDecisionMapOpt)
{
    QualifierResult qualifier;
    int index;
    AutoDeletePtr<RemapUInt16> spLocalQualifierMap;
    AutoDeletePtr<RemapUInt16> spLocalQualifierSetMap;
    AutoDeletePtr<RemapUInt16> spLocalDecisionMap;
    RemapUInt16* pQualifierMapUsed = pQualifierMapOpt;
    RemapUInt16* pQualifierSetMapUsed = pQualifierSetMapOpt;
    RemapUInt16* pDecisionMapUsed = pDecisionMapOpt;

    // Always use remap information (create if not given) while merging qualifiers, qualifiersets and decisions.
    if (nullptr == pQualifierMapUsed)
    {
        RETURN_IF_FAILED(RemapUInt16::CreateInstance(pMerge->GetNumQualifiers(), &spLocalQualifierMap));
        pQualifierMapUsed = spLocalQualifierMap;
    }

    if (nullptr == pQualifierSetMapUsed)
    {
        RETURN_IF_FAILED(RemapUInt16::CreateInstance(pMerge->GetNumQualifierSets(), &spLocalQualifierSetMap));
        pQualifierSetMapUsed = spLocalQualifierSetMap;
    }

    if (nullptr == pDecisionMapUsed)
    {
        RETURN_IF_FAILED(RemapUInt16::CreateInstance(pMerge->GetNumDecisions(), &spLocalDecisionMap));
        pDecisionMapUsed = spLocalDecisionMap;
    }

    DEF_ASSERT(pQualifierMapUsed != nullptr);
    DEF_ASSERT(pQualifierSetMapUsed != nullptr);
    DEF_ASSERT(pDecisionMapUsed != nullptr);

    // remap the well known qualifiers
    bool ok = true;
    ok = ok && pQualifierMapUsed->TrySetMapping(IDecisionInfo::AlwaysTrueQualifierIndex, IDecisionInfo::AlwaysTrueQualifierIndex);
    ok = ok &&
         pQualifierSetMapUsed->TrySetMapping(IDecisionInfo::UnconditionalQualifierSetIndex, IDecisionInfo::UnconditionalQualifierSetIndex);
    ok = ok && pDecisionMapUsed->TrySetMapping(IDecisionInfo::EmptyDecisionIndex, IDecisionInfo::EmptyDecisionIndex);
    ok = ok && pDecisionMapUsed->TrySetMapping(IDecisionInfo::NeutralOnlyDecisionIndex, IDecisionInfo::NeutralOnlyDecisionIndex);
    if (!ok)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    // merge qualifiers
    for (UINT16 i = 1; i < pMerge->GetNumQualifiers(); i++)
    {
        RETURN_IF_FAILED(pMerge->GetQualifier(i, &qualifier));
        RETURN_IF_FAILED(GetOrAddQualifier(&qualifier, &index));
        if (!pQualifierMapUsed->TrySetMapping(i, static_cast<UINT16>(index)))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
        }
    }

    // merge qualifiersets
    QualifierSetResult qualifierSet;
    for (UINT16 i = 1; i < pMerge->GetNumQualifierSets(); i++)
    {
        RETURN_IF_FAILED(pMerge->GetQualifierSet(i, &qualifierSet));
        RETURN_IF_FAILED(GetOrAddQualifierSet(&qualifierSet, pQualifierMapUsed, &index));
        if (!pQualifierSetMapUsed->TrySetMapping(i, static_cast<UINT16>(index)))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
        }
    }

    // merge decisions
    DecisionResult decision;
    for (UINT16 i = 2; i < pMerge->GetNumDecisions(); i++)
    {
        RETURN_IF_FAILED(pMerge->GetDecision(i, &decision));
        RETURN_IF_FAILED(GetOrAddDecision(&decision, pQualifierSetMapUsed, &index));
        if (!pDecisionMapUsed->TrySetMapping(i, static_cast<UINT16>(index)))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
        }
    }

    return S_OK;
}

const UnifiedEnvironment* DecisionInfoBuilder::GetEnvironment() const { return m_pData->GetEnvironment(); }

HRESULT DecisionInfoBuilder::GetOrAddQualifier(
    _In_ Atom attrName,
    _In_ ICondition::ConditionOperator op,
    _In_opt_ PCWSTR pValue,
    _In_ UINT16 priority,
    _In_ double fallbackScore,
    _Inout_opt_ QualifierResult* pQualifierOut)
{
    DEF_ATOM_SMALL attrNameSmall = {};
    int baseIndex = -1;
    MRMFILE_BASE_QUALIFIER baseQualifier;
    int qualifierIndex = -1;
    MRMFILE_QUALIFIER qualifier;
    UINT16 uFallbackScore = static_cast<UINT16>(static_cast<double>(MRMFILE_MAX_QUALIFIER_SCORE) * fallbackScore);

    if (op == IQualifier::TrueOp)
    {
        if (!attrName.IsNull())
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
        }
        else if (!DefString_IsEmpty(pValue))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
        }
        return ((pQualifierOut != NULL) ? pQualifierOut->Set(m_pData, AlwaysTrueQualifierIndex) : S_OK);
    }
    else if (op == IQualifier::FalseOp)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_OPERATOR);
    }

    if (!attrName.TryGetSmallAtom(&attrNameSmall))
    {
        // attributes must fit in a small atom
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    DynamicArray<MRMFILE_BASE_QUALIFIER>* pBaseQualifiers = m_pData->GetBaseQualifiers();
    DynamicArray<MRMFILE_QUALIFIER>* pQualifiers = m_pData->GetQualifiers();
    WriteableStringPool* pLiteralsStringPool = m_pData->GetLiteralsStringPool();

    // First find the matching base qualifier, if any.
    for (int i = 0; i < pBaseQualifiers->Count(); i++)
    {
        if (!pBaseQualifiers->TryGet(i, &baseQualifier))
        {
            return E_ABORT;
        }

        if ((attrNameSmall.uVal == baseQualifier.attribute.uVal) && (baseQualifier.op.s.poolIndex == 0) &&
            (op == static_cast<ICondition::ConditionOperator>(baseQualifier.op.s.index)) &&
            pLiteralsStringPool->Equals(baseQualifier.valueOffset, pValue))
        {
            baseIndex = i;
            break;
        }
    }

    if (baseIndex < 0)
    {
        // No matching base condition.  Add it.

        // No matching existing condition.  Make sure we're legit:
        HRESULT hr = GetEnvironment()->ValidateQualifierComparison(attrName, op, pValue);
        if (FAILED(hr))
        {
            if (AllowUnknownQualifiers() &&
                ((hr == HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER)) || (hr == HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE))))
            {
                // During merge we just ignore invalid qualifiers or values
                hr = S_OK;
            }
            else
            {
                // During build, an invalid qualifier or value should fail us
                return hr;
            }
        }

        // First add the value
        int offset = pLiteralsStringPool->GetOrAddStringOffset(pValue);
        if (offset < 0)
        {
            // failed to add the string
            return E_UNEXPECTED;
        }

        baseQualifier.attribute = attrNameSmall;
        baseQualifier.op.s.poolIndex = 0;
        baseQualifier.op.s.index = static_cast<UINT16>(op);
        baseQualifier.valueOffset = static_cast<UINT32>(offset);

        RETURN_IF_FAILED(pBaseQualifiers->Add(baseQualifier, &baseIndex));
    }
    else
    {
        // We have a matching base qualifier.  See if the qualifier is already there too.
        for (int i = 0; i < pQualifiers->Count(); i++)
        {
            if (!pQualifiers->TryGet(i, &qualifier))
            {
                return E_ABORT;
            }
            if ((qualifier.baseQualifierIndex == baseIndex) && (qualifier.fallbackScore == uFallbackScore) &&
                (qualifier.priority == priority))
            {
                qualifierIndex = i;
                break;
            }
        }
    }

    if (qualifierIndex < 0)
    {
        // We are.  Add a new condition.
        qualifier.baseQualifierIndex = static_cast<UINT16>(baseIndex);
        qualifier.priority = priority;
        qualifier.fallbackScore = uFallbackScore;
        qualifier.pad = 0;

        RETURN_IF_FAILED(pQualifiers->Add(qualifier, &qualifierIndex));
    }

    return ((pQualifierOut != nullptr) ? pQualifierOut->Set(m_pData, qualifierIndex) : S_OK);
}

HRESULT DecisionInfoBuilder::GetOrAddQualifier(
    _In_opt_ PCWSTR pAttrName,
    _In_ ICondition::ConditionOperator op,
    _In_opt_ PCWSTR pValue,
    _In_ UINT16 priority,
    _In_ double fallbackScore,
    _Inout_opt_ QualifierResult* pQualifierOut)
{
    Atom atom;

    if (op == IQualifier::TrueOp)
    {
        if (!DefString_IsEmpty(pAttrName))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
        }
        else if (!DefString_IsEmpty(pValue))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
        }
        return ((pQualifierOut != nullptr) ? pQualifierOut->Set(m_pData, AlwaysTrueQualifierIndex) : S_OK);
    }
    else if (op == IQualifier::FalseOp)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_OPERATOR);
    }

    RETURN_IF_FAILED(m_pData->GetEnvironment()->GetQualifierNameAtom(pAttrName, &atom));
    RETURN_IF_FAILED(GetOrAddQualifier(atom, op, pValue, priority, fallbackScore, pQualifierOut));

    return S_OK;
}

HRESULT DecisionInfoBuilder::GetOrAddQualifier(
    _In_ PCWSTR pQualifierName,
    _In_ PCWSTR pQualifierValue,
    _In_ double fallbackScore,
    _Inout_opt_ QualifierResult* pQualifierOut)
{
    ResourceQualifier q;
    RETURN_IF_FAILED(m_pData->GetEnvironment()->GetResourceQualifier(pQualifierName, &q));
    RETURN_IF_FAILED(GetOrAddQualifier(
        q.name, ICondition::MatchOp, pQualifierValue, static_cast<UINT16>(q.defaultBuildPriority), fallbackScore, pQualifierOut));
    return S_OK;
}

HRESULT DecisionInfoBuilder::GetOrAddQualifier(_In_ const IQualifier* pQualifier, _Out_opt_ int* pIndexOut)
{
    Atom qualifierName;
    ICondition::ConditionOperator op;
    StringResult value;
    QualifierResult result;

    RETURN_IF_FAILED(pQualifier->GetOperand1Attribute(&qualifierName));
    RETURN_IF_FAILED(pQualifier->GetOperator(&op));
    RETURN_IF_FAILED(pQualifier->GetOperand2Literal(&value));

    double fallbackScore;
    RETURN_IF_FAILED(pQualifier->GetFallbackScore(&fallbackScore));
    RETURN_IF_FAILED(
        GetOrAddQualifier(qualifierName, op, value.GetRef(), static_cast<UINT16>(pQualifier->GetPriority()), fallbackScore, &result));
    if (pIndexOut != nullptr)
    {
        RETURN_IF_FAILED(result.GetQualifierIndex(pIndexOut));
    }
    return S_OK;
}

int DecisionInfoBuilder::GetNumQualifiers() const { return m_pData->GetQualifiers()->Count(); }

HRESULT DecisionInfoBuilder::GetQualifier(_In_ int index, _Inout_ QualifierResult* pQualifierOut) const
{
    return pQualifierOut->Set(m_pData, index);
}

HRESULT DecisionInfoBuilder::GetOrAddQualifierSet(_In_opt_ const IQualifierSet* pQualifierSet, _Out_opt_ int* pIndexOut)
{
    return GetOrAddQualifierSet(pQualifierSet, nullptr, pIndexOut);
}

HRESULT DecisionInfoBuilder::GetOrAddQualifierSet(
    _In_opt_ const IQualifierSet* pNewQualifierSet,
    _In_opt_ RemapUInt16* pQualifierMapRemapInfo,
    _Out_opt_ int* pIndexOut)
{
    // NULL means unconditional
    if (pNewQualifierSet == nullptr)
    {
        if (pIndexOut != nullptr)
        {
            *pIndexOut = UnconditionalQualifierSetIndex;
        }
        return S_OK;
    }

    int numExisting = m_pData->GetNumQualifierSets();
    QualifierSetResult existing;

    // Compare from the end for better perf.  We tend to add in groups sequentially,
    // so the qualifier we need is more often at or closer to the end of the list.
    for (int i = numExisting - 1; i >= 0; i--)
    {
        if (SUCCEEDED(existing.Set(m_pData, i)))
        {
            if (IQualifierSet::Equal(&existing, pNewQualifierSet))
            {
                if (pIndexOut != nullptr)
                {
                    *pIndexOut = i;
                }
                return S_OK;
            }
        }
    }

    // No match. Add it.
    MRMFILE_QUALIFIER_SET fileQS;

    fileQS.firstQualifierRef = static_cast<UINT16>(m_pData->GetNumReferences());
    fileQS.numQualifierRefs = static_cast<UINT16>(pNewQualifierSet->GetNumQualifiers());

    // First add the references.
    QualifierResult qualifierRes;
    UINT16 unRemappedQualifierIndex = 0;
    for (int i = 0; i < pNewQualifierSet->GetNumQualifiers(); i++)
    {
        if (SUCCEEDED(pNewQualifierSet->GetQualifier(i, &qualifierRes)))
        {
            if (pQualifierMapRemapInfo != nullptr)
            {
                int nQualifierIndex;
                RETURN_IF_FAILED(qualifierRes.GetQualifierIndex(&nQualifierIndex));
                if (!pQualifierMapRemapInfo->TryGetMapping(static_cast<UINT16>(nQualifierIndex), &unRemappedQualifierIndex))
                {
                    return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
                }
            }
            else
            {
                int nRemappedQualifierInfo = 0;
                RETURN_IF_FAILED(GetOrAddQualifier(&qualifierRes, &nRemappedQualifierInfo));
                unRemappedQualifierIndex = static_cast<UINT16>(nRemappedQualifierInfo);
            }

            RETURN_IF_FAILED(m_pData->GetReferences()->Add(unRemappedQualifierIndex));
        }
    }

    RETURN_IF_FAILED(m_pData->GetQualifierSets()->Add(fileQS, pIndexOut));

    return S_OK;
}

int DecisionInfoBuilder::GetNumQualifierSets() const { return m_pData->GetQualifierSets()->Count(); }

HRESULT
DecisionInfoBuilder::GetQualifierSet(_In_ int index, _Inout_ QualifierSetResult* pSetOut) const { return pSetOut->Set(m_pData, index); }

HRESULT DecisionInfoBuilder::GetOrAddDecision(_In_ const IDecision* pNewDecision, _Out_opt_ int* pIndexOut)
{
    return GetOrAddDecision(pNewDecision, nullptr, pIndexOut);
}

HRESULT DecisionInfoBuilder::GetOrAddDecision(
    _In_ const IDecision* pNewDecision,
    _In_opt_ RemapUInt16* pQualifierSetMapRemapInfo,
    _Out_opt_ int* pIndexOut)
{
    int numExisting = m_pData->GetNumDecisions();
    DecisionResult existing;

    for (int i = 0; i < numExisting; i++)
    {
        if (SUCCEEDED(existing.Set(m_pData, i)) && IDecision::Equal(&existing, pNewDecision))
        {
            if (pIndexOut != nullptr)
            {
                *pIndexOut = i;
            }
            return S_OK;
        }
    }

    // No match.  Add it.
    MRMFILE_DECISION fileDecision;

    fileDecision.firstQualifierSetRef = static_cast<UINT16>(m_pData->GetNumReferences());
    fileDecision.numQualifierSetRefs = static_cast<UINT16>(pNewDecision->GetNumQualifierSets());

    // First add the references.
    QualifierSetResult qualifierSetRes;
    UINT16 unRemappedQualifierSetIndex = 0;
    for (int i = 0; i < pNewDecision->GetNumQualifierSets(); i++)
    {
        if (SUCCEEDED(pNewDecision->GetQualifierSet(i, &qualifierSetRes)))
        {
            if (pQualifierSetMapRemapInfo != nullptr)
            {
                int nQualifierSetIndex;
                RETURN_IF_FAILED(qualifierSetRes.GetIndex(&nQualifierSetIndex));

                if (!pQualifierSetMapRemapInfo->TryGetMapping(static_cast<UINT16>(nQualifierSetIndex), &unRemappedQualifierSetIndex))
                {
                    return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
                }
            }
            else
            {
                int nRemappedQualifierSetIndex = 0;
                RETURN_IF_FAILED(GetOrAddQualifierSet(&qualifierSetRes, nullptr, &nRemappedQualifierSetIndex));
                unRemappedQualifierSetIndex = static_cast<UINT16>(nRemappedQualifierSetIndex);
            }

            RETURN_IF_FAILED(m_pData->GetReferences()->Add(unRemappedQualifierSetIndex));
        }
    }

    RETURN_IF_FAILED(m_pData->GetDecisions()->Add(fileDecision, pIndexOut));

    return S_OK;
}

int DecisionInfoBuilder::GetNumDecisions() const { return m_pData->GetNumDecisions(); }

HRESULT
DecisionInfoBuilder::GetDecision(_In_ int index, _Inout_ DecisionResult* pDecisionOut) const { return pDecisionOut->Set(m_pData, index); }

HRESULT DecisionInfoBuilder::GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const
{
    return m_pData->GetDecisionNumQualifierSets(index, pNumSetsOut);
}

void DecisionInfoBuilder::GetAlwaysTrueConditionIndex(_Out_ int* pIndexOut) const { *pIndexOut = 0; }

void DecisionInfoBuilder::GetUnconditionalQualifierSetIndex(_Out_ int* pIndexOut) const { *pIndexOut = 0; }

void DecisionInfoBuilder::GetEmptyDecisionIndex(_Out_ int* pIndexOut) const { *pIndexOut = 0; }

void DecisionInfoBuilder::GetNeutralOnlyDecisionIndex(_Out_ int* pIndexOut) const { *pIndexOut = 1; }

HRESULT DecisionInfoSectionBuilder::CreateInstance(
    _In_ FileBuilder* pFileBuilder,
    _In_ const UnifiedEnvironment* pEnvironment,
    _Outptr_ DecisionInfoSectionBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pFileBuilder == nullptr) || (pEnvironment == nullptr));

    AutoDeletePtr<DecisionInfoSectionBuilder> pRtrn = new DecisionInfoSectionBuilder();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pFileBuilder, pEnvironment));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT DecisionInfoSectionBuilder::Init(_In_ FileBuilder* pFileBuilder, _In_ const UnifiedEnvironment* pEnvironment)
{
    RETURN_IF_FAILED(DecisionInfoBuilder::Init(DecisionInfoBuilder::DefaultFlags, pEnvironment));
    m_pFileBuilder = pFileBuilder;

    return S_OK;
}

HRESULT DecisionInfoSectionBuilder::Finalize()
{
    m_finalized = true;
    return S_OK;
}

UINT32 DecisionInfoSectionBuilder::GetMaxSizeInBytes() const
{
    if (!m_finalized)
    {
        return 0;
    }

    UINT32 size = sizeof(MRMFILE_DECISION_INFO_HEADER) + (m_pData->GetNumDecisions() * sizeof(MRMFILE_DECISION)) +
                  (m_pData->GetNumQualifierSets() * sizeof(MRMFILE_QUALIFIER_SET)) +
                  (m_pData->GetNumQualifiers() * sizeof(MRMFILE_QUALIFIER)) +
                  (m_pData->GetNumBaseQualifiers() * sizeof(MRMFILE_BASE_QUALIFIER)) + (m_pData->GetNumReferences() * sizeof(UINT16)) +
                  (m_pData->GetLiteralsSizeInChars() * sizeof(WCHAR));
    size = _DEFFILE_PAD_SECTION(size);
    return size;
}

HRESULT
DecisionInfoSectionBuilder::Build(_Out_writes_bytes_(cbBuffer) VOID* pBuffer, _In_ UINT32 cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const
{
    MRMFILE_DECISION_INFO_HEADER* pHeader;
    MRMFILE_DECISION* pDecisions;
    MRMFILE_QUALIFIER_SET* pQualifierSets;
    MRMFILE_QUALIFIER* pQualifiers;
    MRMFILE_BASE_QUALIFIER* pBaseQualifiers;
    UINT16* pReferences;
    WCHAR* pLiterals;

    RETURN_HR_IF_NULL(E_INVALIDARG, pBuffer);
    RETURN_HR_IF(E_DEF_NOT_READY, !m_finalized);

    if (pcbWrittenOut != nullptr)
    {
        *pcbWrittenOut = 0;
    }

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(pBuffer, cbBuffer));

    HRESULT hr = S_OK;
    pHeader = _SECTION_BUILDER_NEXT(data, MRMFILE_DECISION_INFO_HEADER, &hr);
    pDecisions = _SECTION_BUILDER_NEXT_ARRAY(data, m_pData->GetNumDecisions(), MRMFILE_DECISION, &hr);
    pQualifierSets = _SECTION_BUILDER_NEXT_ARRAY(data, m_pData->GetNumQualifierSets(), MRMFILE_QUALIFIER_SET, &hr);
    pQualifiers = _SECTION_BUILDER_NEXT_ARRAY(data, m_pData->GetNumQualifiers(), MRMFILE_QUALIFIER, &hr);
    pBaseQualifiers = _SECTION_BUILDER_NEXT_ARRAY(data, m_pData->GetNumBaseQualifiers(), MRMFILE_BASE_QUALIFIER, &hr);
    pReferences = _SECTION_BUILDER_NEXT_ARRAY(data, m_pData->GetNumReferences(), UINT16, &hr);
    pLiterals = _SECTION_BUILDER_NEXT_ARRAY(data, m_pData->GetLiteralsSizeInChars(), WCHAR, &hr);
    _SECTION_BUILDER_PAD(&data, &hr);

    RETURN_IF_FAILED(hr);

    _Analysis_assume_(pHeader != nullptr);

    pHeader->numBaseQualifiers = static_cast<UINT16>(m_pData->GetNumBaseQualifiers());
    pHeader->numQualifiers = static_cast<UINT16>(m_pData->GetNumQualifiers());
    pHeader->numQualifierSets = static_cast<UINT16>(m_pData->GetNumQualifierSets());
    pHeader->numDecisions = static_cast<UINT16>(m_pData->GetNumDecisions());
    pHeader->numReferences = static_cast<UINT16>(m_pData->GetNumReferences());
    pHeader->cchLiterals = static_cast<UINT16>(m_pData->GetLiteralsSizeInChars());

    CopyMemory(pDecisions, m_pData->GetDecisions()->GetAll(), pHeader->numDecisions * sizeof(MRMFILE_DECISION));
    CopyMemory(pQualifierSets, m_pData->GetQualifierSets()->GetAll(), pHeader->numQualifierSets * sizeof(MRMFILE_QUALIFIER_SET));
    CopyMemory(pQualifiers, m_pData->GetQualifiers()->GetAll(), pHeader->numQualifiers * sizeof(MRMFILE_QUALIFIER));
    CopyMemory(pBaseQualifiers, m_pData->GetBaseQualifiers()->GetAll(), pHeader->numBaseQualifiers * sizeof(MRMFILE_BASE_QUALIFIER));
    CopyMemory(pReferences, m_pData->GetReferences()->GetAll(), pHeader->numReferences * sizeof(UINT16));
    CopyMemory(pLiterals, m_pData->GetLiteralsStringPool()->GetBuffer(), pHeader->cchLiterals * sizeof(WCHAR));

    if (pcbWrittenOut != nullptr)
    {
        *pcbWrittenOut = static_cast<UINT32>(data.UsedBufferSizeInBytes());
    }
    return S_OK;
}

HRESULT DecisionInfoQualifierSetBuilder::CreateInstance(
    _In_ DecisionInfoBuilder* pDecisionInfoBuilder,
    _Outptr_ DecisionInfoQualifierSetBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pDecisionInfoBuilder);

    AutoDeletePtr<DecisionInfoQualifierSetBuilder> pRtrn = new DecisionInfoQualifierSetBuilder();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pDecisionInfoBuilder));
    *result = pRtrn.Detach();

    return S_OK;
}

DecisionInfoQualifierSetBuilder::~DecisionInfoQualifierSetBuilder()
{
    delete m_pQualifierIndexes;

    m_pDecisionInfo = nullptr;
    m_pQualifierIndexes = nullptr;
}

HRESULT DecisionInfoQualifierSetBuilder::AddQualifier(
    _In_opt_ PCWSTR pQualifierName,
    _In_ ICondition::ConditionOperator conditionOp,
    _In_opt_ PCWSTR pValue,
    _In_ int priority,
    _In_ double fallbackScore,
    _Out_opt_ int* pIndexInSetOut)
{
    RETURN_HR_IF(E_INVALIDARG, (priority < 0) || (priority > MRMFILE_MAX_QUALIFIER_PRIORITY));
    RETURN_HR_IF(E_INVALIDARG, (fallbackScore < MinQualifierScore) || (fallbackScore > MaxQualifierScore));
    QualifierResult qualifier;

    UINT16 qualifierIndex = 0xffff;

    if (conditionOp == IQualifier::TrueOp)
    {
        // If this is always true or always false, both name & value must be empty
        if (!DefString_IsEmpty(pQualifierName))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
        }
        else if (!DefString_IsEmpty(pValue))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
        }

        qualifierIndex = IDecisionInfo::AlwaysTrueQualifierIndex;
    }
    else if (conditionOp == IQualifier::FalseOp)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_OPERATOR);
    }
    else
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER), DefString_IsEmpty(pQualifierName));

        RETURN_IF_FAILED(m_pDecisionInfo->GetOrAddQualifier(
            pQualifierName, conditionOp, pValue, static_cast<UINT16>(priority), fallbackScore, &qualifier));

        int localQualifierIndex;
        RETURN_IF_FAILED(qualifier.GetQualifierIndex(&localQualifierIndex));
        qualifierIndex = static_cast<UINT16>(localQualifierIndex);
    }

    int numQualifiers = m_pQualifierIndexes->Count();
    UINT16* pQualifierIndexes = m_pQualifierIndexes->GetAll();

    for (int i = 0; i < numQualifiers; i++)
    {
        if (pQualifierIndexes[i] == qualifierIndex)
        {
            // condition is already present
            if (pIndexInSetOut != nullptr)
            {
                *pIndexInSetOut = i;
            }
            return S_OK;
        }
    }

    // Our contents are changing.  IF we had an index, it's no longer valid.
    m_index = -1;

    // Insert sorted in descending order
    QualifierResult existing;
    for (int i = 0; i < numQualifiers; i++)
    {
        if (SUCCEEDED(m_pDecisionInfo->GetQualifier(pQualifierIndexes[i], &existing)))
        {
            if (IQualifier::Compare(&qualifier, &existing) > 0)
            {
                if (pIndexInSetOut != nullptr)
                {
                    *pIndexInSetOut = i;
                }
                return m_pQualifierIndexes->Insert(qualifierIndex, i);
            }
        }
    }

    if (pIndexInSetOut != nullptr)
    {
        *pIndexInSetOut = numQualifiers;
    }
    return m_pQualifierIndexes->Insert(qualifierIndex, numQualifiers);
}

HRESULT DecisionInfoQualifierSetBuilder::AddQualifier(
    _In_ PCWSTR pQualifierName,
    _In_ PCWSTR pValue,
    _In_ double fallbackScore,
    _Out_opt_ int* pIndexInSetOut)
{
    ResourceQualifier q;

    RETURN_IF_FAILED(m_pDecisionInfo->GetEnvironment()->GetResourceQualifier(pQualifierName, &q));
    RETURN_IF_FAILED(AddQualifier(pQualifierName, ICondition::MatchOp, pValue, q.defaultBuildPriority, fallbackScore, pIndexInSetOut));

    return S_OK;
}

HRESULT DecisionInfoQualifierSetBuilder::AddQualifier(
    _In_opt_ PCWSTR pQualifierName,
    _In_ ICondition::ConditionOperator conditionOp,
    _In_opt_ PCWSTR pValue,
    _In_ double fallbackScore,
    _Out_opt_ int* pIndexInSetOut)
{
    int defaultWeight = 0;

    if (conditionOp == IQualifier::TrueOp)
    {
        if (!DefString_IsEmpty(pQualifierName))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
        }
        else if (!DefString_IsEmpty(pValue))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_VALUE);
        }
    }
    else if (conditionOp == IQualifier::FalseOp)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_OPERATOR);
    }
    else
    {
        ResourceQualifier qualifier;

        RETURN_IF_FAILED(m_pDecisionInfo->GetEnvironment()->GetResourceQualifier(pQualifierName, &qualifier));
        defaultWeight = qualifier.defaultBuildPriority;
    }
    RETURN_IF_FAILED(AddQualifier(pQualifierName, conditionOp, pValue, defaultWeight, fallbackScore, pIndexInSetOut));

    return S_OK;
}

HRESULT DecisionInfoQualifierSetBuilder::AddQualifiers(
    _In_ int numQualifiers,
    _In_reads_(numQualifiers) MrmBcQualifier* pQualifiers,
    _In_ bool useDefaults)
{
    for (int i = 0; i < numQualifiers; i++)
    {
        if (useDefaults)
        {
            RETURN_IF_FAILED(AddQualifier(
                pQualifiers[i].QualifierName, ICondition::MatchOp, pQualifiers[i].QualifierValue, pQualifiers[i].FallbackScore, nullptr));
        }
        else
        {
            RETURN_IF_FAILED(AddQualifier(
                pQualifiers[i].QualifierName,
                ICondition::MatchOp,
                pQualifiers[i].QualifierValue,
                pQualifiers[i].Priority,
                pQualifiers[i].FallbackScore,
                nullptr));
        }
    }
    return S_OK;
}

int DecisionInfoQualifierSetBuilder::GetNumQualifiers() const { return m_pQualifierIndexes->Count(); }

HRESULT
DecisionInfoQualifierSetBuilder::GetQualifier(_In_ int indexInSet, _Inout_ QualifierResult* pQualifierOut, _Out_opt_ int* pIndexInPoolOut)
    const
{
    UINT16 indexInPool;
    if (!m_pQualifierIndexes->TryGet(indexInSet, &indexInPool))
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    if (pIndexInPoolOut != nullptr)
    {
        *pIndexInPoolOut = indexInPool;
    }

    RETURN_IF_FAILED(m_pDecisionInfo->GetQualifier(indexInPool, pQualifierOut));

    return S_OK;
}

HRESULT DecisionInfoQualifierSetBuilder::GetQualifierIndexInPool(_In_ int indexInSet, _Out_ int* pIndexInPoolOut) const
{
    UINT16 indexInPool;

    if (!m_pQualifierIndexes->TryGet(indexInSet, &indexInPool))
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    *pIndexInPoolOut = indexInPool;
    return S_OK;
}

void DecisionInfoQualifierSetBuilder::Reset()
{
    m_pQualifierIndexes->Reset();
    m_index = -1;
}

HRESULT DecisionInfoQualifierSetBuilder::Init(_In_ DecisionInfoBuilder* pDecisionInfoBuilder)

{
    RETURN_IF_FAILED(DynamicArray<UINT16>::CreateInstance(InitialQualifiersSize, &m_pQualifierIndexes));
    m_pDecisionInfo = pDecisionInfoBuilder;

    return S_OK;
}

HRESULT DecisionBuilder::CreateInstance(_In_ DecisionInfoBuilder* pDecisionInfoBuilder, _Outptr_ DecisionBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pDecisionInfoBuilder);

    AutoDeletePtr<DecisionBuilder> pRtrn = new DecisionBuilder();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pDecisionInfoBuilder));
    *result = pRtrn.Detach();

    return S_OK;
}

DecisionBuilder::~DecisionBuilder()
{
    delete m_pQualifierSetIndexes;
    m_pQualifierSetIndexes = nullptr;
}

HRESULT DecisionBuilder::AddQualifierSet(_In_ const IQualifierSet* pQualifierSet, _Out_opt_ int* pIndexInDecisionOut)
{
    QualifierSetResult existing;
    UINT16 existingIndexInPool;

    int csIndex = -1;

    for (int i = 0; i < m_pQualifierSetIndexes->Count(); i++)
    {
        if (!m_pQualifierSetIndexes->TryGet(i, &existingIndexInPool))
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
        RETURN_IF_FAILED(m_pDecisionInfo->GetQualifierSet(existingIndexInPool, &existing));

        DEFCOMPARISON diff = IQualifierSet::Compare(pQualifierSet, &existing);
        if (diff >= 0)
        {
            if (diff > 0)
            {
                // changing our contents, so reset our index if we have one
                m_index = -1;

                RETURN_IF_FAILED(m_pDecisionInfo->GetOrAddQualifierSet(pQualifierSet, &csIndex));
                RETURN_IF_FAILED(m_pQualifierSetIndexes->Insert(static_cast<UINT16>(csIndex), i));
            }

            if (pIndexInDecisionOut)
            {
                *pIndexInDecisionOut = i;
            }
            return S_OK;
        }
    }

    // changing our contents, so reset our index if we have one
    m_index = -1;

    // No match, and we sort behind everyone else
    RETURN_IF_FAILED(m_pDecisionInfo->GetOrAddQualifierSet(pQualifierSet, &csIndex));
    RETURN_IF_FAILED(m_pQualifierSetIndexes->Add(static_cast<UINT16>(csIndex), pIndexInDecisionOut));

    return S_OK;
}

HRESULT DecisionBuilder::AddQualifierSet(_In_ int qualifierSetIndexInPool, _Out_opt_ int* pIndexInDecisionOut)
{
    QualifierSetResult qualifierSet;

    RETURN_IF_FAILED(m_pDecisionInfo->GetQualifierSet(qualifierSetIndexInPool, &qualifierSet));

    RETURN_IF_FAILED(AddQualifierSet(&qualifierSet, pIndexInDecisionOut));

    return S_OK;
}

HRESULT DecisionBuilder::AddQualifierSetForMerge(_In_ int qualifierSetIndexInPool, _Out_ int* pIndexInDecisionOut)
{
    // In merge operation, Added qualiifer set is ordered by its resources pack so its addition to the decision index
    // doesn't have to be rearranged to have same order.
    m_index = -1;
    RETURN_IF_FAILED(m_pQualifierSetIndexes->Add(static_cast<UINT16>(qualifierSetIndexInPool), pIndexInDecisionOut));

    return S_OK;
}

int DecisionBuilder::GetNumQualifierSets() const { return m_pQualifierSetIndexes->Count(); }

HRESULT
DecisionBuilder::GetQualifierSet(_In_ int indexInDecision, _Inout_ QualifierSetResult* pQualifierSetOut, _Out_opt_ int* pIndexInPoolOut)
    const
{
    UINT16 indexInPool = 0;

    if (!m_pQualifierSetIndexes->TryGet(indexInDecision, &indexInPool))
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    if (pIndexInPoolOut != nullptr)
    {
        *pIndexInPoolOut = indexInPool;
    }

    RETURN_IF_FAILED(m_pDecisionInfo->GetQualifierSet(indexInPool, pQualifierSetOut));

    return S_OK;
}

HRESULT DecisionBuilder::GetQualifierSetIndexInPool(_In_ int indexInDecision, _Out_ int* pIndexInPoolOut) const
{
    UINT16 indexInPool = 0;

    if (!m_pQualifierSetIndexes->TryGet(indexInDecision, &indexInPool))
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    if (pIndexInPoolOut != nullptr)
    {
        *pIndexInPoolOut = indexInPool;
    }

    if (!m_pDecisionInfo->IsValidQualifierSetIndex(indexInPool))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    return S_OK;
}

HRESULT DecisionBuilder::GetQualifierSetIndexInDecision(_In_ int wantIndexInPool, _Out_ int* pIndexInDecisionOut) const
{
    UINT16 existingIndexInPool = 0;

    *pIndexInDecisionOut = -1;

    for (int i = 0; i < m_pQualifierSetIndexes->Count(); i++)
    {
        if (!m_pQualifierSetIndexes->TryGet(i, &existingIndexInPool))
        {
            return E_ABORT;
        }
        if (wantIndexInPool == existingIndexInPool)
        {
            *pIndexInDecisionOut = i;
            return S_OK;
        }
    }

    // not found
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

void DecisionBuilder::Reset()
{
    m_pQualifierSetIndexes->Reset();
    m_index = -1;
}

HRESULT DecisionBuilder::Init(_In_ DecisionInfoBuilder* pDecisionInfoBuilder)
{
    RETURN_IF_FAILED(DynamicArray<UINT16>::CreateInstance(InitialQualifierSetsSize, &m_pQualifierSetIndexes));
    m_pDecisionInfo = pDecisionInfoBuilder;
    return S_OK;
}

} // namespace Microsoft::Resources::Build
