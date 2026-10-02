// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <mrm/build/AIDict.h>
#include "Helpers.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

const int TQFLAGS_PRIORITY_PRESENT = 0x01;
const int TQFLAGS_FALLBACK_SCORE_PRESENT = 0x02;

struct TestQualifier
{
    PCWSTR pId;
    int expectedIndexInPool;
    int expectedIndexInSet;

    UINT32 present;
    PCWSTR pQualifierName;
    PCWSTR pQualifierValue;
    int priority;
    double fallbackScore;
};

struct TestQualifierSet
{
    PCWSTR pId;
    int expectedIndexInPool;
    int expectedIndexInSet;

    int numQualifiers;
    TestQualifier* pQualifiers;
};

struct TestDecision
{
    PCWSTR pId;
    int expectedIndexInPool;

    int numQualifierSets;
    TestQualifierSet* pQualifierSets;
};

class TestQualifierCollection
{
public:
    TestQualifierCollection();
    ~TestQualifierCollection();

    void Reset();

    static HRESULT InitFromTestValue(__in PCWSTR pValue, __inout TestStringArray* pSpecsOut, __out TestQualifier* pQualifierOut);

    HRESULT InitFromTestVars(__in PCWSTR pPrefix, __in bool required);
    HRESULT InitFromTestVars(__in PCWSTR pPrefix) { return InitFromTestVars(pPrefix, true); }

    int GetNumTestQualifiers() const { return m_numQualifiers; }

    HRESULT GetTestQualifier(__in int index, __out TestQualifier* pQualifierOut) const;

    HRESULT GetTestQualifier(__in PCWSTR pId, __out TestQualifier* pQualifierOut) const;

    bool TryGetQualifier(
        __in PCWSTR pId,
        __in const IDecisionInfo* pDecisions,
        __in const UnifiedEnvironment* pEnvironment,
        __inout QualifierResult* pQualifierOut) const;

    static bool TryGetQualifier(
        __in const TestQualifier* pTestSpec,
        __in const IDecisionInfo* pDecisions,
        __in const UnifiedEnvironment* pEnvironment,
        __inout_opt QualifierResult* pQualifierOut);

    HRESULT GetOrAddQualifier(__in PCWSTR pId, __in DecisionInfoBuilder* pDecisions, __inout_opt QualifierResult* pQualifierOut);

    static HRESULT GetOrAddQualifier(
        __in const TestQualifier* pTestSpec,
        __in DecisionInfoBuilder* pDecisions,
        __inout_opt QualifierResult* pQualifierOut);

protected:
    int m_numQualifiers;

    TestDataArray<String> m_testStrings;
    TestStringArray* m_pSpecs;
    TestQualifier* m_pQualifiers;
};

class TestQualifierSetCollection
{
public:
    TestQualifierSetCollection();
    ~TestQualifierSetCollection();

    void Reset();

    HRESULT InitFromTestVars(__in PCWSTR pPrefix, __in TestQualifierCollection* pQualifiers, __in bool required);

    HRESULT InitFromTestVars(__in PCWSTR pPrefix, __in TestQualifierCollection* pQualifiers)
    {
        return InitFromTestVars(pPrefix, pQualifiers, true);
    }

    int GetNumTestQualifierSets() const { return m_numQualifierSets; }

    HRESULT GetTestQualifierSet(__in int index, __out TestQualifierSet* pQualifierSetOut) const;

    HRESULT GetTestQualifierSet(__in PCWSTR pId, __out TestQualifierSet* pQualifierSetOut) const;

    bool TryGetQualifierSet(
        __in PCWSTR pId,
        __in const IDecisionInfo* pDecisions,
        __in const UnifiedEnvironment* pEnvironment,
        __inout_opt QualifierSetResult* pSetOut) const;

    static bool TryGetMatchedQualifierSet(
        __in const TestQualifierSet* pTestSpec,
        __in const IDecisionInfo* pDecisions,
        __in const UnifiedEnvironment* pEnvironment,
        __inout_opt QualifierSetResult* pSetOut);

    HRESULT GetOrAddQualifierSet(__in PCWSTR pId, __in DecisionInfoBuilder* pDecisions, __inout_opt QualifierSetResult* pSetOut);

    static HRESULT GetOrAddQualifierSet(
        __in const TestQualifierSet* pTestSpec,
        __in DecisionInfoBuilder* pDecisions,
        __inout_opt QualifierSetResult* pSetOut);

protected:
    int m_numQualifierSets;

    TestDataArray<String> m_testStrings;
    TestStringArray* m_pSpecs;
    TestQualifierSet* m_pQualifierSets;
};

class TestDecisionCollection
{
public:
    TestDecisionCollection();
    ~TestDecisionCollection();

    void Reset();

    HRESULT InitFromTestVars(__in PCWSTR pPrefix, __in TestQualifierSetCollection* pSets, __in bool required);

    HRESULT InitFromTestVars(__in PCWSTR pPrefix, __in TestQualifierSetCollection* pSets) { return InitFromTestVars(pPrefix, pSets, true); }

    int GetNumTestDecisions() const { return m_numDecisions; }

    HRESULT GetTestDecision(__in int index, __out TestDecision* pDecisionOut) const;

    HRESULT GetTestDecision(__in PCWSTR pId, __out TestDecision* pDecisionOut) const;

    bool TryGetDecision(
        __in PCWSTR pId,
        __in const IDecisionInfo* pDecisions,
        __in const UnifiedEnvironment* pEnvironment,
        __inout DecisionResult* pDecisionOut) const;

    static bool TryGetDecision(
        __in const TestDecision* pTestSpec,
        __in const IDecisionInfo* pDecisions,
        __in const UnifiedEnvironment* pEnvironment,
        __inout DecisionResult* pDecisionOut);

    HRESULT GetOrAddDecision(__in PCWSTR pId, __in DecisionInfoBuilder* pDecisions, __inout_opt DecisionResult* pDecisionOut);

    static HRESULT GetOrAddDecision(
        __in const TestDecision* pTestSpec,
        __in DecisionInfoBuilder* pDecisions,
        __inout_opt DecisionResult* pDecisionOut);

protected:
    int m_numDecisions;

    TestDataArray<String> m_testStrings;
    TestStringArray* m_pSpecs;
    TestDecision* m_pDecisions;
};

class TestDecisionInfo
{
public:
    TestDecisionInfo();
    ~TestDecisionInfo();

    HRESULT InitDataFromTestVars(__in PCWSTR pPrefix);

    HRESULT ApplyTestData(__inout DecisionInfoBuilder* pBuilder);

    TestQualifierCollection* GetQualifierData() { return &m_qualifiers; }
    TestQualifierSetCollection* GetQualifierSetData() { return &m_qualifierSets; }
    TestDecisionCollection* GetDecisionData() { return &m_decisions; }

protected:
    TestQualifierCollection m_qualifiers;
    TestQualifierSetCollection m_qualifierSets;
    TestDecisionCollection m_decisions;
};

class TestDecisionInfoValidator
{
public:
    TestDecisionInfoValidator();
    ~TestDecisionInfoValidator();

    HRESULT InitDataFromTestVars(__in PCWSTR pPrefix);

    bool TryInitDataFromTestVars(__in PCWSTR pPrefix);

    HRESULT ValidateQualifiers(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment);

    HRESULT ValidateQualifierSets(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment);

    HRESULT ValidateDecisions(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment);

    HRESULT VerifyAll(__in const IDecisionInfo* pDecisionInfo, __in const UnifiedEnvironment* pEnvironment);

    TestQualifierCollection* GetQualifierData() { return &m_qualifiers; }
    TestQualifierSetCollection* GetQualifierSetData() { return &m_qualifierSets; }
    TestDecisionCollection* GetDecisionData() { return &m_decisions; }

    static bool MatchQualifier(
        __in const IDecisionInfo* pDecisionInfo,
        __in const UnifiedEnvironment* pEnvironment,
        __in const IQualifier* pQualifier,
        __in const TestQualifier* pTestQualifier);

    static bool MatchQualifierSet(
        __in const IDecisionInfo* pDecisionInfo,
        __in const UnifiedEnvironment* pEvironment,
        __in const IQualifierSet* pQualifierSet,
        __in const TestQualifierSet* pTestQualifierSet);

    static bool Matches(
        __in const IDecisionInfo* pDecisionInfo,
        __in const UnifiedEnvironment* pEvironment,
        __in const IDecision* pDecision,
        __in const TestDecision* pTestDecision);

protected:
    int m_expectedNumQualifiers;
    int m_expectedNumQualifierSets;
    int m_expectedNumDecisions;

    TestQualifierCollection m_qualifiers;
    TestQualifierSetCollection m_qualifierSets;
    TestDecisionCollection m_decisions;
};

} // namespace UnitTests
