// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources
{

class IDecisionInfo;

/*!
     * An ICondition represents a single comparison operation, typically used
     * to evaluate the relevance of some item for a specific context.  It consists
     * of an operator and one or two operands.
     *
     * The operator is specified as an atom. Most operators accept two operands.
     *
     * The first operand is always an attribute, specified by atom.
     *
     * When specified, the second operand is either a literal string or an attribute
     * specified by atom.
     */

static const double MinConditionScore = 0.0;
static const double MaxConditionScore = 1.0;

class ICondition : public DefObject
{
public:
    enum ConditionOperator
    {
        FalseOp = 0,
        TrueOp = 1,
        AttrDefinedOp = 2,
        AttrUndefinedOp = 3,
        NotEqualOp = 4,
        NoMatchOp = 5,
        LessOp = 6,
        LessOrEqualOp = 7,
        GreaterOp = 8,
        GreaterOrEqualOp = 9,
        MatchOp = 10,
        EqualOp = 11,
        ExtendedOp = 12
    };

    static bool IsValidConditionOperator(_In_ ConditionOperator op)
    {
        return ((static_cast<int>(op) >= 0) && (static_cast<int>(op) <= static_cast<int>(ExtendedOp)));
    }

    _Check_return_ virtual HRESULT GetOperand1Attribute(_Out_ Atom* pAttrOut) const = 0;

    virtual HRESULT GetOperand1Qualifier(_Out_ Atom* pAttrOut) const { return GetOperand1Attribute(pAttrOut); }

    virtual bool OperatorIsCustom() const = 0;

    virtual HRESULT GetOperator(_Out_ ConditionOperator* pOperatorOut) const = 0;

    virtual HRESULT GetCustomOperator(_Out_ Atom* pOpOut) const = 0;

    virtual bool OperatorIsUnary() const = 0;

    virtual HRESULT Operand2IsLiteral(_Out_ bool* result) const = 0;

    virtual HRESULT GetOperand2Literal(_Inout_ StringResult* pLiteralOut) const = 0;

    virtual HRESULT GetOperand2Attribute(_Inout_ Atom* pAttrOut) const = 0;

    static bool Equal(_In_ const ICondition* pCondition1, _In_ const ICondition* pCondition2);

    static DEFCOMPARISON Compare(_In_ const ICondition* pCondition1, _In_ const ICondition* pCondition2);
};

static const double MinQualifierScore = 0.0;
static const double MaxQualifierScore = 1.0;

/*!
     * An IQualifier represents a single comparison operation, with an
     * associated priority which indicates the importance of this qualifier relative
     * to any other qualifiers in consideration, for both normal and fallback
     * use.
     */
class IQualifier : public ICondition
{
public:
    virtual int GetPriority() const = 0;

    virtual HRESULT GetFallbackScore(_Out_ double* score) const = 0;
    virtual int GetFallbackScoreAsScaledInt() const = 0;

    virtual HRESULT GetQualifierIndex(_Out_ int* index) const = 0;
    virtual HRESULT GetBaseQualifierIndex(_Out_ int* index) const = 0;

    static bool Equal(_In_opt_ const IQualifier* pCondition1, _In_opt_ const IQualifier* pCondition2);

    static DEFCOMPARISON Compare(_In_opt_ const IQualifier* pCondition1, _In_opt_ const IQualifier* pCondition2);

    // fallback score is 0.0-1.0 at runtime, but
    // is stored as value in the range 0-1000 here.
    static const UINT16 MinFallbackScore = MRMFILE_MIN_QUALIFIER_SCORE;
    static const UINT16 MaxFallbackScore = MRMFILE_MAX_QUALIFIER_SCORE;

    static HRESULT ToUint16Score(_In_ double score, _Out_ UINT16* result)
    {
        RETURN_HR_IF(E_INVALIDARG, (score < 0.0) || (score > 1.0));
        *result = (UINT16)(score * (double)MRMFILE_MAX_QUALIFIER_SCORE);
        return S_OK;
    }

    static HRESULT ToDoubleScore(_In_ UINT16 score, _Out_ double* result)
    {
        RETURN_HR_IF(E_INVALIDARG, (score < MinFallbackScore) || (score > MaxFallbackScore));
        *result = ((double)score) / ((double)MRMFILE_MAX_QUALIFIER_SCORE);
        return S_OK;
    }
};

class QualifierResult;
class QualifierSetResult;

class IQualifierSet : public DefObject
{
public:
    virtual int GetNumQualifiers() const = 0;

    virtual HRESULT GetQualifier(_In_ int indexInSet, _Inout_ QualifierResult* pResultOut, _Out_opt_ int* pIndexInPoolOut = nullptr)
        const = 0;

    virtual HRESULT GetQualifierIndexInPool(_In_ int indexInSet, _Out_ int* pIndexInPoolOut) const = 0;

    virtual HRESULT GetIndex(_Out_ int* index) const = 0;

    virtual HRESULT GetPool(_Out_ const IDecisionInfo** result) const = 0;

    virtual int GetIndex() const = 0;

    virtual const IDecisionInfo* GetPool() const = 0;

    bool GetIsNeutralOrDefault() const;

    static bool Equal(_In_ const IQualifierSet* pQualifierSet1, _In_ const IQualifierSet* pQualifierSet2);

    static DEFCOMPARISON Compare(_In_opt_ const IQualifierSet* pQualifierSet1, _In_opt_ const IQualifierSet* pQualifierSet2);
};

class IDecision : public DefObject
{
public:
    virtual int GetNumQualifierSets() const = 0;

    virtual HRESULT GetQualifierSetIndexInPool(_In_ int indexInDecision, _Out_ int* pSetIndexInPoolOut) const = 0;

    virtual HRESULT GetQualifierSet(_In_ int indexInDecision, _Inout_ QualifierSetResult* pSetOut, _Out_opt_ int* pSetIndexOut = nullptr)
        const = 0;

    virtual HRESULT GetIndex(_Out_ int* index) const = 0;

    virtual HRESULT GetPool(_Out_ const IDecisionInfo** result) const = 0;

    virtual int GetIndex() const = 0;

    virtual const IDecisionInfo* GetPool() const = 0;

    bool GetAlwaysYieldsResult() const;

    static bool Equal(_In_ const IDecision* pDecision1, _In_ const IDecision* pDecision2);

    static DEFCOMPARISON Compare(_In_opt_ const IDecision* pDecision1, _In_opt_ const IDecision* pDecision2);
};

class IRawDecisionInfo;

class QualifierResult : public IQualifier
{
public:
    QualifierResult();
    virtual ~QualifierResult();

    HRESULT Set(_In_ const IRawDecisionInfo* pRaw, _In_ int index);

    HRESULT GetOperand1Attribute(_Out_ Atom* pAttrOut) const;

    bool OperatorIsCustom() const;

    HRESULT GetOperator(_Out_ ConditionOperator* pOperatorOut) const;

    HRESULT GetCustomOperator(_Out_ Atom* pOpOut) const;

    bool OperatorIsUnary() const;

    HRESULT Operand2IsLiteral(_Out_ bool* result) const;

    HRESULT GetOperand2Literal(_Inout_ StringResult* pLiteralOut) const;

    HRESULT GetOperand2Attribute(_Inout_ Atom* pAttrOut) const;

    int GetPriority() const;

    HRESULT GetFallbackScore(_Out_ double* score) const;

    int GetFallbackScoreAsScaledInt() const;

    HRESULT GetQualifierIndex(_Out_ int* index) const;

    HRESULT GetBaseQualifierIndex(_Out_ int* index) const;

protected:
    const IRawDecisionInfo* m_pRaw{ nullptr };

    MRMFILE_BASE_QUALIFIER m_baseQualifier{};
    MRMFILE_QUALIFIER m_qualifier{};

    int m_baseIndex{ 0 };
    int m_index{ 0 };
};

class QualifierSetResult : public IQualifierSet
{
public:
    QualifierSetResult();
    virtual ~QualifierSetResult();

    HRESULT Set(_In_ const IRawDecisionInfo* pRaw, _In_ int index);

    HRESULT SetToUnconditionalSet(_In_opt_ const IRawDecisionInfo* pRaw);

    int GetNumQualifiers() const;

    HRESULT GetQualifier(_In_ int indexInSet, _Inout_ QualifierResult* pResultOut, _Out_opt_ int* pIndexInPoolOut = nullptr) const;

    HRESULT GetQualifierIndexInPool(_In_ int indexInSet, _Out_ int* pIndexInPoolOut) const;

    HRESULT GetIndex(_Out_ int* index) const;
    HRESULT GetPool(_Out_ const IDecisionInfo** result) const;

    int GetIndex() const;
    const IDecisionInfo* GetPool() const;

protected:
    const IRawDecisionInfo* m_pRaw{ nullptr };

    MRMFILE_QUALIFIER_SET m_qualifierSet{};
    int m_index{ 0 };
};

class DecisionResult : public IDecision
{
public:
    DecisionResult();
    virtual ~DecisionResult();

    HRESULT Set(_In_ const IRawDecisionInfo* pRaw, _In_ int index);

    HRESULT SetToEmptyDecision(_In_opt_ const IRawDecisionInfo* pRaw);

    HRESULT SetToNeutralOnlyDecision(_In_opt_ const IRawDecisionInfo* pRaw);

    int GetNumQualifierSets() const;

    HRESULT GetQualifierSetIndexInPool(_In_ int indexInDecision, _Out_ int* pSetIndexInPoolOut) const;

    HRESULT
    GetQualifierSet(_In_ int indexInDecision, _Inout_ QualifierSetResult* pSetOut, _Out_opt_ int* pSetIndexInPoolOut = nullptr) const;

    HRESULT GetIndex(_Out_ int* index) const;
    HRESULT GetPool(_Out_ const IDecisionInfo** result) const;

    int GetIndex() const;
    const IDecisionInfo* GetPool() const;

protected:
    const IRawDecisionInfo* m_pRaw{ nullptr };

    MRMFILE_DECISION m_decision{};
    int m_index{ 0 };
};

class IEnvironment;

class IDecisionInfo : public DefObject
{
public:
    virtual int GetNumQualifiers() const = 0;

    virtual HRESULT GetQualifier(_In_ int index, _Inout_ QualifierResult* pResult) const = 0;

    virtual int GetNumQualifierSets() const = 0;

    virtual HRESULT GetQualifierSet(_In_ int index, _Inout_ QualifierSetResult* pResult) const = 0;

    virtual int GetNumDecisions() const = 0;

    virtual HRESULT GetDecision(_In_ int index, _Inout_ DecisionResult* pResult) const = 0;

    virtual HRESULT GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const = 0;

    static const int AlwaysTrueQualifierIndex = MRMFILE_ALWAYS_TRUE_QUALIFIER_INDEX;
    static const int UnconditionalQualifierSetIndex = MRMFILE_UNCONDITIONAL_QUALIFIER_SET_INDEX;
    static const int EmptyDecisionIndex = MRMFILE_EMPTY_DECISION_INDEX;
    static const int NeutralOnlyDecisionIndex = MRMFILE_NEUTRAL_ONLY_DECISION_INDEX;
};

} // namespace Microsoft::Resources