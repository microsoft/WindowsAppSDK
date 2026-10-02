// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Helpers.h"
#include "TestQualifier.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

class TestReverseFileMap
{
protected:
    BuildHelper m_build;
    PriSectionBuilder* m_pPriBuilder;
    ReverseFileMapSectionBuilder* m_pReverseFileMapBuilder;
    ReverseFileMap* m_pReverseFileMap;
    TestDecisionInfo* m_pTestDI;
    TestDecisionInfo m_testDI;
    IDecisionInfo* m_pDecisionInfo;

public:
    TestReverseFileMap();

    HRESULT InitFromTestVars(__in PriSectionBuilder* pPriBuilder, __in UnifiedEnvironment* pEnvironment, __in PCWSTR pVarPrefix);

    ~TestReverseFileMap() { Release(); }
    void Release();

    AtomPoolGroup* GetBuildAtoms() const { return m_pPriBuilder->GetAtoms(); }
    ReverseFileMapSectionBuilder* GetReverseFileMapBuilder() const { return m_pReverseFileMapBuilder; }
    ReverseFileMap* GetReverseFileMap() const { return m_pReverseFileMap; }
    TestDecisionInfo* GetTestDI() const { return m_pTestDI; }
    IDecisionInfo* GetDecisionInfo() const { return m_pDecisionInfo; }

    HRESULT Finalize();

    HRESULT Build();

    HRESULT CreateReader();

    static HRESULT VerifyCandidate(
        __in ReverseFileMap* pReverseMap,
        __in PCWSTR pWantCandidateValue,
        __in int wantNamedResourceIndex,
        __in int wantQualifierSetIndex);

    static HRESULT VerifyAllAgainstTestVars(
        __in ReverseFileMap* pReverseMap,
        __in const UnifiedEnvironment* pEnvironment,
        __in const IResourceMapBase* pResourceMapBase,
        __in TestDecisionInfo* pTestDI,
        __in IDecisionInfo* pDecisionInfo,
        __in PCWSTR pVarPrefix);
};

} // namespace UnitTests
