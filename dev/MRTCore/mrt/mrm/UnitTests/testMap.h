// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Helpers.h"
#include "testQualifier.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

class TestResourceMap
{
protected:
    BuildHelper m_build;

    PriSectionBuilder* m_pPriBuilder;
    ResourceMapSectionBuilder* m_pMapBuilder; // we might not own this
    HierarchicalSchemaSectionBuilder* m_pSchemaBuilder; // we might not own this
    ResourceMapBase* m_pMap;
    TestDecisionInfo* m_pTestDI;

    ResourceMapSectionBuilder* m_pMyMapBuilder; // we own this
    HierarchicalSchemaSectionBuilder* m_pMySchemaBuilder; // we own this
    TestDecisionInfo m_testDI;

    StandalonePriFile* m_pBaselinePri; // we own this, if it exists

    DEFRESULT m_expectedBuildResult;
    bool m_expectedBuildReturn;

    DEFRESULT m_expectedFinalizeResult;
    bool m_expectedFinalizeReturn;

public:
    TestResourceMap();

    typedef enum MapInitFlags
    {
        AddNone = 0x00,
        AddDecisionInfo = 0x01,
        AddSchema = 0x02,
        AddMap = 0x04,
        SetAsPrimary = 0x08,
        AddAll = 0x07,
        AddAllAsPrimary = 0x0f
    } MapInitFlags;

    // Creates a map from test variables using the supplied schema builder
    HRESULT InitFromSchemaAndTestVars(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_opt_ TestDecisionInfo* pTestDI,
        _In_ HierarchicalSchemaSectionBuilder* pSchema,
        _In_ PCWSTR pVarPrefix,
        _In_ MapInitFlags initFlags);

    // Creates both schema and map from test variables
    HRESULT InitFromTestVars(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_opt_ TestDecisionInfo* pTestDI,
        _In_ PCWSTR pVarPrefix,
        _In_opt_ PCWSTR pBaselineFolder,
        _In_ MapInitFlags initFlags);

    ~TestResourceMap() { Release(); }
    void Release();

    AtomPoolGroup* GetBuildAtoms() const { return m_pPriBuilder->GetAtoms(); }
    HierarchicalSchemaSectionBuilder* GetSchemaBuilder() const { return m_pSchemaBuilder; }
    ResourceMapSectionBuilder* GetMapBuilder() const { return m_pMapBuilder; }
    TestDecisionInfo* GetTestDI() const { return m_pTestDI; }

    PCWSTR GetBuilderMapUniqueId() const { return m_pMapBuilder->GetSchema()->GetUniqueId(); }
    PCWSTR GetBuilderMapSimpleId() const { return m_pMapBuilder->GetSchema()->GetSimpleId(); }
    BaseFile::SectionIndex GetMapBuilderSectionIndex() const { return m_pMapBuilder->GetSectionIndex(); }
    ResourceMapBase* GetMap() const { return m_pMap; }

    HRESULT Finalize();

    // Cede ownership releases ownership without clearing out the pointer,
    // meaning the object is still live but somebody else owns freeing it.
    bool CedeBuilderOwnership() { m_pMyMapBuilder = NULL; }

    HRESULT Build();

    HRESULT CreateReader(_In_ const IFileSectionResolver* pSections, _In_ const DEFFILE_SECTION_TYPEID& sectionType);

    DEFRESULT GetExpectedFinalizeResult() const { return m_expectedFinalizeResult; }
    bool GetExpectedFinalizeReturn() const { return m_expectedFinalizeReturn; }

    void SetExpectedFinalizeResult(_In_ DEFRESULT expectedResult, _In_ bool expectedReturn)
    {
        m_expectedFinalizeResult = expectedResult;
        m_expectedFinalizeReturn = expectedReturn;
    }

    DEFRESULT GetExpectedBuildResult() const { return m_expectedBuildResult; }
    bool GetExpectedBuildReturn() const { return m_expectedBuildReturn; }

    void SetExpectedBuildResult(_In_ DEFRESULT expectedResult, _In_ bool expectedReturn)
    {
        m_expectedBuildResult = expectedResult;
        m_expectedBuildReturn = expectedReturn;
    }

    // Static helper methods for those who want to do build maps one step at a time
    static HRESULT CreateNewMapFromTestVars(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ HierarchicalSchemaSectionBuilder* pSchema,
        _In_ TestDecisionInfo* pTestDI,
        _In_ PCWSTR pVarPrefix,
        _Outptr_ ResourceMapSectionBuilder** value);

    static HRESULT AddCandidatesFromTestVars(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ ResourceMapSectionBuilder* pMapBuilder,
        _In_ TestDecisionInfo* pTestDI,
        _In_ PCWSTR pVarPrefix);

    static bool TryAddCandidatesFromTestVars(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ ResourceMapSectionBuilder* pMapBuilder,
        _In_ TestDecisionInfo* pTestDI,
        _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyCandidates(
        _In_ const ResourceMapSectionBuilder* pMap,
        _In_ TestDecisionInfo* pTestDI,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyCandidates(
        _In_ const IResourceMapBase* pMap,
        _In_ TestDecisionInfo* pTestDI,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyAllAgainstTestVars(
        _In_ const ResourceMapSectionBuilder* pMap,
        _In_ TestDecisionInfo* pTestDI,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyAllAgainstTestVars(
        _In_ const IResourceMapBase* pMap,
        _In_opt_ const ResourceMapSubtree* pSubtree,
        _In_ TestDecisionInfo* pTestDI,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyAllAgainstTestVars(
        _In_ const IResourceMapBase* pMap,
        _In_ TestDecisionInfo* pTestDI,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ PCWSTR pVarPrefix)
    {
        return VerifyAllAgainstTestVars(pMap, NULL, pTestDI, pEnvironment, pVarPrefix);
    }

protected:
    typedef struct _TestMapPrivate
    {
        const ResourceMapSectionBuilder* pBuilder;
        const IResourceMapBase* pMap;
        const ResourceMapSubtree* pSubtree;
        const UnifiedEnvironment* pEnvironment;
    } TestMapPrivate;

    static HRESULT VerifyCandidate(
        _In_ const ResourceMapSectionBuilder* pMap,
        _In_opt_ PCWSTR pItemName,
        _In_ int itemIndex,
        _In_ const IQualifierSet* wantQualifiers,
        _In_ PCWSTR pWantType,
        _In_ PCWSTR wantStringValue);

    static HRESULT VerifyCandidate(
        _In_ const IResourceMapBase* pMap,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_opt_ PCWSTR pItemName,
        _In_ int itemIndex,
        _In_ const IQualifierSet* wantQualifiers,
        _In_ PCWSTR pWantType,
        _In_ PCWSTR wantStringValue);

    static HRESULT VerifyCandidates(_In_ TestMapPrivate* pMap, _In_ TestDecisionInfo* pTestDI, _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyNamedResources(_In_ TestMapPrivate* pMap, _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyDescendentResources(_In_ TestMapPrivate* pMap, _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyDescendentScopes(_In_ TestMapPrivate* pMap, _In_ PCWSTR pVarPrefix);

    static HRESULT VerifyAllAgainstTestVars(_In_ TestMapPrivate* pMap, _In_ TestDecisionInfo* pTestDI, _In_ PCWSTR pVarPrefix);
};

} // namespace UnitTests
