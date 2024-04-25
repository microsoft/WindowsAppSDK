// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"
#include "DecisionInfo.h"

namespace Microsoft::Resources
{

class DecisionInfoFileData : public IRawDecisionInfo
{
public:
    static HRESULT CreateInstance(
        _In_ const DecisionInfoFileSection* pDecisionInfo,
        _In_reads_bytes_(cbData) const void* pData,
        _In_ size_t cbData,
        _In_opt_ const RemapAtomPool* pQualifierMapping,
        _Outptr_ DecisionInfoFileData** data)
    {
        *data = nullptr;
        AutoDeletePtr<DecisionInfoFileData> pRtrn = new DecisionInfoFileData();
        RETURN_IF_NULL_ALLOC(pRtrn);

        RETURN_IF_FAILED(pRtrn->Init(pDecisionInfo, pData, cbData, pQualifierMapping));

        *data = pRtrn.Detach();

        return S_OK;
    }

    virtual ~DecisionInfoFileData() {}

    int GetNumBaseQualifiers() const { return m_pHeader->numBaseQualifiers; }
    int GetNumQualifiers() const { return m_pHeader->numQualifiers; }
    int GetNumQualifierSets() const { return m_pHeader->numQualifierSets; }
    int GetNumDecisions() const { return m_pHeader->numDecisions; }
    int GetNumReferences() const { return m_pHeader->numReferences; }
    UINT32 GetLiteralsSizeInChars() const { return m_pHeader->cchLiterals; }

    HRESULT GetBaseQualifier(_In_ int index, _Out_ MRMFILE_BASE_QUALIFIER* pQualifierOut) const
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), !IsValidBaseQualifierIndex(index));

        _Analysis_assume_((index >= 0) && (index < m_pHeader->numBaseQualifiers));

        *pQualifierOut = m_pBaseQualifiers[index];

        if (m_pQualifierMapping != nullptr)
        {
            Atom::Index mappedIndex;
            if (m_pQualifierMapping->TryGetMappedIndex(pQualifierOut->attribute.s.index, &mappedIndex))
            {
                pQualifierOut->attribute.s.index = static_cast<DEF_ATOM_INDEX_SMALL>(mappedIndex);
                pQualifierOut->attribute.s.poolIndex = static_cast<DEF_ATOM_INDEX_SMALL>(m_pQualifierMapping->GetTargetPoolIndex());
            }
            else
            {
                // need to remap the pool index from the file to that of the runtime.
                pQualifierOut->attribute.s.poolIndex = static_cast<DEF_ATOM_INDEX_SMALL>(m_pQualifierMapping->GetSourcePoolIndex());
            }
        }
        return S_OK;
    }

    HRESULT GetQualifier(_In_ int index, _Out_ MRMFILE_QUALIFIER* pConditionOut) const
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), !IsValidQualifierIndex(index));

        _Analysis_assume_((index >= 0) && (index < m_pHeader->numQualifiers));

        *pConditionOut = m_pQualifiers[index];
        return S_OK;
    }

    HRESULT GetQualifierSet(_In_ int index, _Out_ MRMFILE_QUALIFIER_SET* pQualifierSetOut) const
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), !IsValidQualifierSetIndex(index));

        _Analysis_assume_((index >= 0) && (index < m_pHeader->numQualifierSets));

        *pQualifierSetOut = m_pQualifierSets[index];
        return S_OK;
    }

    HRESULT GetDecision(_In_ int index, _Out_ MRMFILE_DECISION* pDecisionOut) const
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), !IsValidDecisionIndex(index));

        _Analysis_assume_((index >= 0) && (index < m_pHeader->numDecisions));

        *pDecisionOut = m_pDecisions[index];
        return S_OK;
    }

    HRESULT GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const
    {
        *pNumSetsOut = 0;

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), !IsValidDecisionIndex(index));

        _Analysis_assume_((index >= 0) && (index < m_pHeader->numDecisions));

        *pNumSetsOut = m_pDecisions[index].numQualifierSetRefs;
        return S_OK;
    }

    HRESULT GetReference(_In_ int index, _Out_ UINT16* pReferenceOut) const
    {
        *pReferenceOut = UINT16_MAX;

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), !IsValidReferenceIndex(index));

        _Analysis_assume_((index >= 0) && (index < m_pHeader->numReferences));

        *pReferenceOut = m_pReferences[index];
        return S_OK;
    }

    HRESULT GetLiteral(_In_ int offset, _Inout_ StringResult* pLiteralOut) const
    {
        if (IsValidLiteralOffset(offset))
        {
            _Analysis_assume_(offset < m_pHeader->cchLiterals);
            return pLiteralOut->SetRef(&m_pLiterals[offset]);
        }

        RETURN_IF_FAILED(pLiteralOut->Truncate(0));

        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    const RemapAtomPool* GetQualifierMapping() const { return m_pQualifierMapping; }

    const IDecisionInfo* GetPool() const { return m_pDecisionInfo; }

private:
    const RemapAtomPool* m_pQualifierMapping{ nullptr };
    const DecisionInfoFileSection* m_pDecisionInfo{ nullptr };

    const MRMFILE_DECISION_INFO_HEADER* m_pHeader{ nullptr };
    _Field_size_(m_pHeader->numDecisions) const MRMFILE_DECISION* m_pDecisions{ nullptr };
    _Field_size_(m_pHeader->numQualifierSets) const MRMFILE_QUALIFIER_SET* m_pQualifierSets{ nullptr };
    _Field_size_(m_pHeader->numQualifiers) const MRMFILE_QUALIFIER* m_pQualifiers{ nullptr };
    _Field_size_(m_pHeader->numBaseQualifiers) const MRMFILE_BASE_QUALIFIER* m_pBaseQualifiers{ nullptr };
    _Field_size_(m_pHeader->numReferences) const UINT16* m_pReferences{ nullptr };
    _Field_size_(m_pHeader->cchLiterals) PCWSTR m_pLiterals{ nullptr };

    DecisionInfoFileData() :
        m_pHeader(nullptr),
        m_pDecisions(nullptr),
        m_pQualifierSets(nullptr),
        m_pQualifiers(nullptr),
        m_pBaseQualifiers(nullptr),
        m_pReferences(nullptr),
        m_pLiterals(nullptr)
    {}

    HRESULT Init(
        _In_ const DecisionInfoFileSection* pDecisionInfo,
        _In_reads_bytes_(cbData) const void* pData,
        _In_ size_t cbData,
        _In_opt_ const RemapAtomPool* pQualifierMapping)
    {
        SectionParser data;
        RETURN_IF_FAILED(data.Set(pData, static_cast<UINT32>(cbData)));

        m_pDecisionInfo = pDecisionInfo;
        m_pQualifierMapping = pQualifierMapping;

        HRESULT hr = S_OK;
        m_pHeader = _SECTION_PARSER_NEXT(data, MRMFILE_DECISION_INFO_HEADER, &hr);
        RETURN_IF_FAILED(hr);

        m_pDecisions = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numDecisions, MRMFILE_DECISION, &hr);
        m_pQualifierSets = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numQualifierSets, MRMFILE_QUALIFIER_SET, &hr);
        m_pQualifiers = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numQualifiers, MRMFILE_QUALIFIER, &hr);
        m_pBaseQualifiers = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numBaseQualifiers, MRMFILE_BASE_QUALIFIER, &hr);
        m_pReferences = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numReferences, UINT16, &hr);
        m_pLiterals = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cchLiterals, WCHAR, &hr);
        data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);

        return hr;
    }
};

bool ICondition::Equal(_In_ const ICondition* pCondition1, _In_ const ICondition* pCondition2)
{
    if (Compare(pCondition1, pCondition2) == Def_Equal)
    {
        return true;
    }
    else
    {
        return false;
    }
}

DEFCOMPARISON ICondition::Compare(_In_ const ICondition* pCondition1, _In_ const ICondition* pCondition2)
{
    if (pCondition1 == pCondition2)
    {
        // identity
        return Def_Equal;
    }
    else if ((pCondition1 == NULL) != (pCondition2 == NULL))
    {
        // one of the two conditions is NULL
        return (pCondition1 ? Def_Greater : Def_Less);
    }

    Atom atom1, atom2;
    ConditionOperator op1, op2;
    StringResult string1, string2;
    bool bOperand2IsLiteral1, bOperand2IsLiteral2;

    if (FAILED(pCondition1->GetOperand1Attribute(&atom1)) || FAILED(pCondition2->GetOperand1Attribute(&atom2)) || (!atom1.IsEqual(atom2)))
    {
        return ((atom1.GetInt64() > atom2.GetInt64()) ? Def_Greater : Def_Less);
    }

    if (FAILED(pCondition1->GetOperator(&op1)) || FAILED(pCondition2->GetOperator(&op2)))
    {
        return Def_CompareError;
    }

    if ((op1 != op2))
    {
        return ((op1 > op2) ? Def_Greater : Def_Less);
    }

    // op1 is equal to op2 at this point. If they both have extended operators,
    // check to make sure they are the same.
    if ((op1 == ICondition::ExtendedOp))
    {
        if (FAILED(pCondition1->GetCustomOperator(&atom1)) || FAILED(pCondition2->GetCustomOperator(&atom2)))
        {
            return Def_CompareError;
        }
        if ((!atom1.IsEqual(atom2)))
        {
            return ((atom1.GetInt64() > atom2.GetInt64()) ? Def_Greater : Def_Less);
        }
    }

    if (FAILED(pCondition1->Operand2IsLiteral(&bOperand2IsLiteral1)) || FAILED(pCondition2->Operand2IsLiteral(&bOperand2IsLiteral2)))
    {
        return Def_CompareError;
    }

    if (!bOperand2IsLiteral1 && bOperand2IsLiteral2)
    {
        return Def_Greater;
    }
    else if (bOperand2IsLiteral1 && !bOperand2IsLiteral2)
    {
        return Def_Less;
    }
    else if (!bOperand2IsLiteral1 && !bOperand2IsLiteral2)
    {
        // both operands are attributes
        if (FAILED(pCondition1->GetOperand2Attribute(&atom1)) || FAILED(pCondition2->GetOperand2Attribute(&atom2)))
        {
            return Def_CompareError;
        }

        if ((!atom1.IsEqual(atom2)))
        {
            return ((atom1.GetUInt64() > atom2.GetUInt64()) ? Def_Greater : Def_Less);
        }
        else
        {
            return Def_Equal;
        }
    }
    else
    { // if (bOperand2IsLiteral1 && bOperand2IsLiteral2)
        // both operands are literals
        if (FAILED(pCondition1->GetOperand2Literal(&string1)) || FAILED(pCondition2->GetOperand2Literal(&string2)))
        {
            return Def_CompareError;
        }

        return DefString_ICompare(string1.GetRef(), string2.GetRef());
    }
}

bool IQualifier::Equal(_In_opt_ const IQualifier* pQualifier1, _In_opt_ const IQualifier* pQualifier2)
{
    if (Compare(pQualifier1, pQualifier2) != Def_Equal)
    {
        return false;
    }
    else if (pQualifier1 == nullptr)
    {
        return true;
    }

    _Analysis_assume_(pQualifier2 != nullptr);

    return (pQualifier1->GetPriority() == pQualifier2->GetPriority()) &&
           (pQualifier1->GetFallbackScoreAsScaledInt() == pQualifier2->GetFallbackScoreAsScaledInt());
}

DEFCOMPARISON IQualifier::Compare(_In_opt_ const IQualifier* pQualifier1, _In_opt_ const IQualifier* pQualifier2)
{
    if (pQualifier1 == nullptr)
    {
        if (pQualifier2 == nullptr)
        {
            return Def_Equal;
        }

        return Def_Less;
    }

    if (pQualifier2 == nullptr)
    {
        return Def_Greater;
    }

    // Priority takes priority
    int diff = pQualifier1->GetPriority() - pQualifier2->GetPriority();
    if (diff != 0)
    {
        return ((diff > 0) ? Def_Greater : Def_Less);
    }

    // If priority is equal, the condition comes next
    DEFCOMPARISON rtrn = ICondition::Compare(pQualifier1, pQualifier2);

    if (rtrn == Def_Equal)
    {
        // If condition is equal, look at fallback score to disambiguate
        diff = pQualifier1->GetFallbackScoreAsScaledInt() - pQualifier2->GetFallbackScoreAsScaledInt();
        if (diff != 0)
        {
            rtrn = ((diff > 0) ? Def_Greater : Def_Less);
        }
    }

    return rtrn;
}

bool IQualifierSet::GetIsNeutralOrDefault() const
{
    int numQualifiers = GetNumQualifiers();

    if (numQualifiers == 0)
    {
        // no qualifiers == neutral
        return true;
    }

    QualifierResult qualifier;
    for (int i = 0; i < numQualifiers; i++)
    {
        if (FAILED(GetQualifier(i, &qualifier)))
        {
            return false;
        }

        double fallbackScore;
        if (FAILED(qualifier.GetFallbackScore(&fallbackScore)) || (fallbackScore == 0.0))
        {
            return false;
        }
    }

    return true;
}

bool IQualifierSet::Equal(_In_ const IQualifierSet* pQualifierSet1, _In_ const IQualifierSet* pQualifierSet2)
{
    if (pQualifierSet1->GetNumQualifiers() != pQualifierSet2->GetNumQualifiers())
    {
        return false;
    }

    if ((pQualifierSet1->GetIndex() == pQualifierSet2->GetIndex()) && (pQualifierSet1->GetPool() == pQualifierSet2->GetPool()))
    {
        // index/pool is only reliable if both are defined
        if ((pQualifierSet1->GetIndex() >= 0) && (pQualifierSet1->GetPool() != nullptr))
        {
            return true;
        }
    }

    QualifierResult c1;
    QualifierResult c2;
    for (int i = 0; i < pQualifierSet1->GetNumQualifiers(); i++)
    {
        (void)pQualifierSet1->GetQualifier(i, &c1);
        (void)pQualifierSet2->GetQualifier(i, &c2);

        if (!IQualifier::Equal(&c1, &c2))
        {
            return false;
        }
    }

    return true;
}

DEFCOMPARISON IQualifierSet::Compare(_In_opt_ const IQualifierSet* pQualifierSet1, _In_opt_ const IQualifierSet* pQualifierSet2)
{
    if (pQualifierSet1 == nullptr)
    {
        if (pQualifierSet2 == nullptr)
        {
            return Def_Equal;
        }

        return Def_Less;
    }

    if (pQualifierSet2 == nullptr)
    {
        return Def_Greater;
    }

    DEFCOMPARISON rtrn = Def_Equal;

    int numConditions = min(pQualifierSet1->GetNumQualifiers(), pQualifierSet2->GetNumQualifiers());

    QualifierResult c1;
    QualifierResult c2;
    for (int i = 0; i < numConditions; i++)
    {
        (void)pQualifierSet1->GetQualifier(i, &c1);
        (void)pQualifierSet2->GetQualifier(i, &c2);

        rtrn = IQualifier::Compare(&c1, &c2);
        if (rtrn != Def_Equal)
        {
            return rtrn;
        }
    }

    // They match as far as they go.  Whichever is longer is greater.

    int diff = pQualifierSet1->GetNumQualifiers() - pQualifierSet2->GetNumQualifiers();
    return (diff == 0 ? Def_Equal : (diff > 0 ? Def_Greater : Def_Less));
}

bool IDecision::GetAlwaysYieldsResult() const
{
    int numQualifierSets = GetNumQualifierSets();

    if (numQualifierSets == 0)
    {
        // no qualifier sets == never yields a result
        return false;
    }

    QualifierSetResult qualifierSet;
    for (int i = 0; i < numQualifierSets; i++)
    {
        if (FAILED(GetQualifierSet(i, &qualifierSet)))
        {
            return false;
        }

        if (qualifierSet.GetIsNeutralOrDefault())
        {
            // if any one of our qualifier sets is neutral or
            // default, then we always yield a result.
            return true;
        }
    }

    // None of our qualifier sets are neutral or default.  We
    // might fail to return a result.
    return false;
}

bool IDecision::Equal(_In_ const IDecision* pDecision1, _In_ const IDecision* pDecision2)
{
    if (pDecision1->GetNumQualifierSets() != pDecision2->GetNumQualifierSets())
    {
        return false;
    }

    if ((pDecision1->GetIndex() == pDecision2->GetIndex()) && (pDecision1->GetPool() == pDecision2->GetPool()))
    {

        // index/pool is only reliable if both are defined
        if ((pDecision1->GetIndex() >= 0) && (pDecision1->GetPool() != nullptr))
        {
            return true;
        }
    }

    int numQualifierSets = pDecision1->GetNumQualifierSets();

    QualifierSetResult qs1;
    QualifierSetResult qs2;

    for (int i = 0; i < numQualifierSets; i++)
    {
        (void)pDecision1->GetQualifierSet(i, &qs1);
        (void)pDecision2->GetQualifierSet(i, &qs2);

        if (!IQualifierSet::Equal(&qs1, &qs2))
        {
            return false;
        }
    }

    return true;
}

DEFCOMPARISON IDecision::Compare(_In_opt_ const IDecision* pDecision1, _In_opt_ const IDecision* pDecision2)
{
    if (pDecision1 == nullptr)
    {
        if (pDecision2 == nullptr)
        {
            return Def_Equal;
        }

        return Def_Less;
    }

    if (pDecision2 == nullptr)
    {
        return Def_Greater;
    }

    DEFCOMPARISON rtrn = Def_Equal;

    int numQualifierSets = min(pDecision1->GetNumQualifierSets(), pDecision2->GetNumQualifierSets());

    QualifierSetResult c1;
    QualifierSetResult c2;

    for (int i = 0; i < numQualifierSets; i++)
    {
        (void)pDecision1->GetQualifierSet(i, &c1);
        (void)pDecision2->GetQualifierSet(i, &c2);

        rtrn = IQualifierSet::Compare(&c1, &c2);
        if (rtrn != Def_Equal)
        {
            return rtrn;
        }
    }

    // They match as far as they go.  Whichever is longer is greater.

    int diff = pDecision1->GetNumQualifierSets() - pDecision2->GetNumQualifierSets();
    return (diff == 0 ? Def_Equal : (diff > 0 ? Def_Greater : Def_Less));
}

QualifierResult::QualifierResult() : m_pRaw(nullptr), m_index(-1), m_baseIndex(-1) {}

QualifierResult::~QualifierResult() {}

HRESULT QualifierResult::Set(_In_ const IRawDecisionInfo* pRaw, _In_ int index)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pRaw);

    MRMFILE_QUALIFIER fileQualifier = {0};
    MRMFILE_BASE_QUALIFIER baseQualifier = {0};

    RETURN_IF_FAILED(pRaw->GetQualifier(index, &fileQualifier));
    RETURN_IF_FAILED(pRaw->GetBaseQualifier(fileQualifier.baseQualifierIndex, &baseQualifier));

    m_pRaw = pRaw;

    m_baseQualifier = baseQualifier;
    m_baseIndex = fileQualifier.baseQualifierIndex;
    m_qualifier = fileQualifier;
    m_index = index;

    return S_OK;
}

HRESULT QualifierResult::GetOperand1Attribute(_Out_ Atom* pAttrOut) const
{
    *pAttrOut = Atom::NullAtom;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    *pAttrOut = Atom(m_baseQualifier.attribute);
    return S_OK;
}

bool QualifierResult::OperatorIsCustom() const
{
    if (m_pRaw == nullptr)
    {
        return false;
    }

    return (m_baseQualifier.op.s.poolIndex != 0);
}

HRESULT QualifierResult::GetOperator(_Out_ ConditionOperator* pOperatorOut) const
{
    *pOperatorOut = ICondition::MatchOp;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    if (m_baseQualifier.op.s.poolIndex != 0)
    {
        *pOperatorOut = ICondition::ExtendedOp;
        return S_OK;
    }
    else if (!ICondition::IsValidConditionOperator(static_cast<ConditionOperator>(m_baseQualifier.op.s.index)))
    {
        // file or builder data is bad
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    *pOperatorOut = static_cast<ConditionOperator>(m_baseQualifier.op.s.index);
    return S_OK;
}

HRESULT QualifierResult::GetCustomOperator(_Out_ Atom* pOpOut) const
{
    *pOpOut = Atom::NullAtom;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    if (m_baseQualifier.op.s.poolIndex == 0)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_QUALIFIER_OPERATOR);
    }

    *pOpOut = Atom(m_baseQualifier.op);
    return S_OK;
}

bool QualifierResult::OperatorIsUnary() const
{
    if (m_pRaw == nullptr)
    {
        return false;
    }

    return (
        (m_baseQualifier.op.s.poolIndex != 0) &&
        ((static_cast<ConditionOperator>(m_baseQualifier.op.s.index) == ICondition::AttrDefinedOp) ||
         (static_cast<ConditionOperator>(m_baseQualifier.op.s.index) == ICondition::AttrUndefinedOp)));
}

HRESULT QualifierResult::Operand2IsLiteral(_Out_ bool* result) const
{
    *result = false;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    // no current support for attribute operand
    *result = true;

    return S_OK;
}

HRESULT QualifierResult::GetOperand2Literal(_Inout_ StringResult* pLiteralOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    return m_pRaw->GetLiteral(m_baseQualifier.valueOffset, pLiteralOut);
}

HRESULT QualifierResult::GetOperand2Attribute(_Inout_ Atom* pAttrOut) const
{
    *pAttrOut = Atom::NullAtom;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    return E_DEF_CONDITION_OPERAND_NOT_ATTRIBUTE;
}

int QualifierResult::GetPriority() const
{
    if (m_pRaw == nullptr)
    {
        return -1;
    }

    if (m_qualifier.priority > MRMFILE_MAX_QUALIFIER_PRIORITY)
    {
        // illegal data in the file
        return -1;
    }

    return m_qualifier.priority;
}

int QualifierResult::GetFallbackScoreAsScaledInt() const
{
    if (m_pRaw == nullptr)
    {
        return 0;
    }

    if (m_qualifier.priority > MRMFILE_MAX_QUALIFIER_PRIORITY)
    {
        // illegal data in the file
        return 0;
    }

    return m_qualifier.fallbackScore;
}

HRESULT QualifierResult::GetFallbackScore(_Out_ double* score) const
{
    *score = 0.0;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    // illegal data in the file
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), m_qualifier.priority > MRMFILE_MAX_QUALIFIER_PRIORITY);

    *score = (static_cast<double>(m_qualifier.fallbackScore) / static_cast<double>(MRMFILE_MAX_QUALIFIER_PRIORITY));
    return S_OK;
}

HRESULT QualifierResult::GetQualifierIndex(_Out_ int* index) const
{
    *index = 0;
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    *index = m_index;

    return S_OK;
}

HRESULT QualifierResult::GetBaseQualifierIndex(_Out_ int* index) const
{
    *index = 0;
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    *index = m_baseIndex;

    return S_OK;
}

QualifierSetResult::QualifierSetResult() : m_pRaw(nullptr), m_index(-1) {}

QualifierSetResult::~QualifierSetResult()
{
    m_pRaw = nullptr;
    m_index = -1;
}

HRESULT QualifierSetResult::Set(_In_ const IRawDecisionInfo* pRaw, _In_ int index)
{
    RETURN_HR_IF(E_INVALIDARG, (pRaw == nullptr) || (index < 0));

    MRMFILE_QUALIFIER_SET fileQualifierSet = {};
    RETURN_IF_FAILED(pRaw->GetQualifierSet(index, &fileQualifierSet));

    m_pRaw = pRaw;
    m_index = index;
    m_qualifierSet = fileQualifierSet;
    return S_OK;
}

HRESULT QualifierSetResult::SetToUnconditionalSet(_In_opt_ const IRawDecisionInfo* pRaw)
{
    m_pRaw = pRaw;
    m_index = IDecisionInfo::UnconditionalQualifierSetIndex;
    m_qualifierSet.firstQualifierRef = 0;
    m_qualifierSet.numQualifierRefs = 0;
    return S_OK;
}

int QualifierSetResult::GetNumQualifiers() const
{
    if (m_index == IDecisionInfo::UnconditionalQualifierSetIndex)
    {
        return 0;
    }

    if (m_pRaw == nullptr)
    {
        return 0;
    }
    return m_qualifierSet.numQualifierRefs;
}

HRESULT QualifierSetResult::GetQualifier(_In_ int indexInSet, _Inout_ QualifierResult* pResultOut, _Out_opt_ int* pIndexInPoolOut) const
{
    if (pIndexInPoolOut != nullptr)
    {
        *pIndexInPoolOut = -1;
    }

    if (m_pRaw == nullptr)
    {
        if (m_index == IDecisionInfo::UnconditionalQualifierSetIndex)
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }

        return E_DEF_NOT_READY;
    }

    if ((indexInSet < 0) || (indexInSet >= m_qualifierSet.numQualifierRefs))
    {
        // caller asked for a condition that doesn't exist
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    UINT16 indexInPool = 0;

    RETURN_IF_FAILED(m_pRaw->GetReference(m_qualifierSet.firstQualifierRef + indexInSet, &indexInPool));
    RETURN_IF_FAILED(pResultOut->Set(m_pRaw, indexInPool));

    if (pIndexInPoolOut != nullptr)
    {
        *pIndexInPoolOut = indexInPool;
    }

    return S_OK;
}

HRESULT QualifierSetResult::GetQualifierIndexInPool(_In_ int indexInSet, _Out_ int* pIndexInPoolOut) const
{
    *pIndexInPoolOut = -1;

    if (m_pRaw == nullptr)
    {
        if (m_index == IDecisionInfo::UnconditionalQualifierSetIndex)
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }

        return E_DEF_NOT_READY;
    }

    DEF_ASSERT(pIndexInPoolOut != nullptr);

    if ((indexInSet < 0) || (indexInSet >= m_qualifierSet.numQualifierRefs))
    {
        // caller asked for a qualifier that doesn't exist
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    UINT16 indexInPool = 0;

    RETURN_IF_FAILED(m_pRaw->GetReference(m_qualifierSet.firstQualifierRef + indexInSet, &indexInPool));

    if (!m_pRaw->IsValidQualifierIndex(indexInPool))
    {
        // file data is damaged
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    *pIndexInPoolOut = indexInPool;
    return S_OK;
}

HRESULT QualifierSetResult::GetIndex(_Out_ int* index) const
{
    *index = 0;

    if ((m_pRaw == nullptr) && (m_index != IDecisionInfo::UnconditionalQualifierSetIndex))
    {
        return E_DEF_NOT_READY;
    }

    *index = m_index;

    return S_OK;
}

HRESULT QualifierSetResult::GetPool(_Out_ const IDecisionInfo** result) const
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    *result = m_pRaw->GetPool();

    return S_OK;
}

int QualifierSetResult::GetIndex() const
{

    if ((m_pRaw == nullptr) && (m_index != IDecisionInfo::UnconditionalQualifierSetIndex))
    {
        return 0;
    }

    return m_index;
}

const IDecisionInfo* QualifierSetResult::GetPool() const
{
    if (m_pRaw == nullptr)
    {
        return nullptr;
    }

    return m_pRaw->GetPool();
}

DecisionResult::DecisionResult() : m_pRaw(nullptr), m_index(-1) {}

DecisionResult::~DecisionResult()
{
    m_pRaw = nullptr;
    m_index = -1;
}

HRESULT DecisionResult::Set(_In_ const IRawDecisionInfo* pRaw, _In_ int index)
{
    RETURN_HR_IF(E_INVALIDARG, (pRaw == nullptr) || (index < -1));

    MRMFILE_DECISION decision;

    RETURN_IF_FAILED(pRaw->GetDecision(index, &decision));

    m_pRaw = pRaw;
    m_index = index;
    m_decision = decision;
    return S_OK;
}

HRESULT DecisionResult::SetToEmptyDecision(_In_opt_ const IRawDecisionInfo* pRaw)
{
    m_pRaw = pRaw;
    m_index = 0;
    m_decision.firstQualifierSetRef = 0;
    m_decision.numQualifierSetRefs = 0;
    return S_OK;
}

HRESULT DecisionResult::SetToNeutralOnlyDecision(_In_opt_ const IRawDecisionInfo* pRaw)
{
    m_pRaw = pRaw;
    m_index = 1;
    m_decision.firstQualifierSetRef = 0;
    m_decision.numQualifierSetRefs = 1;
    return S_OK;
}

int DecisionResult::GetNumQualifierSets() const
{
    // Empty & Neutral-Only decision are okay, otherwise we need a decision info
    if (m_pRaw == nullptr)
    {
        if (m_index == IDecisionInfo::EmptyDecisionIndex)
        {
            return 0;
        }
        else if (m_index == IDecisionInfo::NeutralOnlyDecisionIndex)
        {
            return 1;
        }

        return -1;
    }

    return m_decision.numQualifierSetRefs;
}

HRESULT DecisionResult::GetQualifierSetIndexInPool(_In_ int indexInDecision, _Out_ int* pSetIndexInPoolOut) const
{
    *pSetIndexInPoolOut = -1;

    if (m_pRaw == nullptr)
    {
        if ((indexInDecision == 0) && (m_index == IDecisionInfo::NeutralOnlyDecisionIndex))
        {
            // special case neutral-only decision
            *pSetIndexInPoolOut = IDecisionInfo::UnconditionalQualifierSetIndex;
            return S_OK;
        }

        RETURN_HR_IF(
            HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND),
            (m_index == IDecisionInfo::NeutralOnlyDecisionIndex) || (m_index == IDecisionInfo::EmptyDecisionIndex));

        return E_DEF_NOT_READY;
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (indexInDecision < 0) || (indexInDecision >= m_decision.numQualifierSetRefs));

    int indexOfReference = m_decision.firstQualifierSetRef + indexInDecision;
    UINT16 setIndex = 0;
    RETURN_IF_FAILED(m_pRaw->GetReference(indexOfReference, &setIndex));

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), !m_pRaw->IsValidQualifierSetIndex(setIndex));

    *pSetIndexInPoolOut = setIndex;

    return S_OK;
}

HRESULT
DecisionResult::GetQualifierSet(_In_ int indexInDecision, _Inout_ QualifierSetResult* pSetOut, _Out_opt_ int* pSetIndexInPoolOut) const
{
    if (pSetIndexInPoolOut != nullptr)
    {
        *pSetIndexInPoolOut = -1;
    }

    if (m_pRaw == nullptr)
    {
        if ((indexInDecision == 0) && (m_index == IDecisionInfo::NeutralOnlyDecisionIndex))
        {
            // special case neutral-only decision
            if (SUCCEEDED(pSetOut->SetToUnconditionalSet(m_pRaw)))
            {
                if (pSetIndexInPoolOut)
                {
                    *pSetIndexInPoolOut = IDecisionInfo::UnconditionalQualifierSetIndex;
                }
                return S_OK;
            }
        }
        RETURN_HR_IF(
            HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND),
            (m_index == IDecisionInfo::NeutralOnlyDecisionIndex) || (m_index == IDecisionInfo::EmptyDecisionIndex));

        return E_DEF_NOT_READY;
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (indexInDecision < 0) || (indexInDecision >= m_decision.numQualifierSetRefs));

    int indexOfReference = m_decision.firstQualifierSetRef + indexInDecision;
    UINT16 indexInPool = 0;
    RETURN_IF_FAILED(m_pRaw->GetReference(indexOfReference, &indexInPool));

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), !m_pRaw->IsValidQualifierSetIndex(indexInPool));

    RETURN_IF_FAILED(pSetOut->Set(m_pRaw, indexInPool));

    if (pSetIndexInPoolOut != nullptr)
    {
        *pSetIndexInPoolOut = indexInPool;
    }

    return S_OK;
}

HRESULT DecisionResult::GetIndex(_Out_ int* index) const
{
    *index = 0;
    if ((m_pRaw == nullptr && ((m_index < 0) || (m_index > IDecisionInfo::NeutralOnlyDecisionIndex))))
    {
        return E_DEF_NOT_READY;
    }

    *index = m_index;
    return S_OK;
}

HRESULT DecisionResult::GetPool(_Out_ const IDecisionInfo** result) const
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRaw);

    *result = m_pRaw->GetPool();
    return S_OK;
}

int DecisionResult::GetIndex() const
{
    if ((m_pRaw == nullptr && ((m_index < 0) || (m_index > IDecisionInfo::NeutralOnlyDecisionIndex))))
    {
        return 0;
    }

    return m_index;
}

const IDecisionInfo* DecisionResult::GetPool() const
{
    if (m_pRaw == nullptr)
    {
        return nullptr;
    }

    return m_pRaw->GetPool();
}

HRESULT DecisionInfoFileSection::CreateInstance(
    _In_ const IFileSection* const pSection,
    _In_opt_ const RemapAtomPool* pQualifierMapping,
    _Outptr_ DecisionInfoFileSection** result)
{
    *result = nullptr;

    AutoDeletePtr<DecisionInfoFileSection> pRtrn = new DecisionInfoFileSection();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pSection, pSection->GetData(), pSection->GetDataSize(), pQualifierMapping));
    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT DecisionInfoFileSection::CreateInstance(
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ int cbData,
    _In_opt_ const RemapAtomPool* pQualifierMapping,
    _Outptr_ DecisionInfoFileSection** result)
{
    *result = nullptr;

    AutoDeletePtr<DecisionInfoFileSection> pRtrn = new DecisionInfoFileSection();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(nullptr, pData, cbData, pQualifierMapping));
    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT DecisionInfoFileSection::Init(
    _In_opt_ const IFileSection* pFileSection,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ int cbData,
    _In_opt_ const RemapAtomPool* pQualifierMapping)
{
    m_pFileData = nullptr;

    RETURN_IF_FAILED(FileSectionBase::Init(pFileSection, pData, cbData));

    RETURN_IF_FAILED(DecisionInfoFileData::CreateInstance(this, pData, cbData, pQualifierMapping, &m_pFileData));

    return S_OK;
}

DecisionInfoFileSection::~DecisionInfoFileSection()
{
    delete m_pFileData;
    m_pFileData = nullptr;
}

int DecisionInfoFileSection::GetNumQualifiers() const { return m_pFileData->GetNumQualifiers(); }

const RemapAtomPool* DecisionInfoFileSection::GetQualifierMapping() const { return m_pFileData->GetQualifierMapping(); }

HRESULT
DecisionInfoFileSection::GetQualifier(_In_ int index, _Inout_ QualifierResult* pResult) const { return pResult->Set(m_pFileData, index); }

int DecisionInfoFileSection::GetNumQualifierSets() const { return m_pFileData->GetNumQualifierSets(); }

HRESULT DecisionInfoFileSection::GetQualifierSet(_In_ int index, _Inout_ QualifierSetResult* pResult) const
{
    return pResult->Set(m_pFileData, index);
}

int DecisionInfoFileSection::GetNumDecisions() const { return m_pFileData->GetNumDecisions(); }

HRESULT DecisionInfoFileSection::GetDecision(_In_ int index, _Inout_ DecisionResult* pResult) const
{
    return pResult->Set(m_pFileData, index);
}

HRESULT DecisionInfoFileSection::GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const
{
    return m_pFileData->GetDecisionNumQualifierSets(index, pNumSetsOut);
}

} // namespace Microsoft::Resources
