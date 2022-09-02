// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Helpers.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

class TestHierarchicalSchema
{
protected:
    BuildHelper m_build;
    PriSectionBuilder* m_pPriBuilder;
    HierarchicalSchemaSectionBuilder* m_pSchemaBuilder;
    HierarchicalSchema* m_pSchema;

    StandalonePriFile* m_pBaselinePri; // we own this

public:
    TestHierarchicalSchema();

    // Creates a schema from test variables
    HRESULT Init(__in PriSectionBuilder* pPriBuilder, __in PCWSTR pVarPrefix)
    {
        return Init(pPriBuilder, pVarPrefix, (IHierarchicalSchema*)NULL);
    }

    HRESULT Init(__in PriSectionBuilder* pPriBuilder, __in PCWSTR pVarPrefix, __in PCWSTR pBaselineFolder);

    HRESULT Init(__in PriSectionBuilder* pPriBuilder, __in PCWSTR pVarPrefix, __in_opt const IHierarchicalSchema* pBaselineSchema);

    ~TestHierarchicalSchema() { Release(); }
    void Release();

    AtomPoolGroup* GetBuildAtoms() const { return m_pPriBuilder->GetAtoms(); }
    HierarchicalSchemaSectionBuilder* GetSchemaBuilder() const { return m_pSchemaBuilder; }
    HierarchicalSchema* GetSchema() const { return m_pSchema; }

    HRESULT Build();

    HRESULT CreateReader(_In_ const DEFFILE_SECTION_TYPEID& type);

    bool TryVerifySchema(__in PCWSTR pVarPrefix) const { return TryVerifySchema(m_pSchema, pVarPrefix); }

    bool TryVerifyScopes(__in PCWSTR pVarPrefix) const { return TryVerifyScopes(m_pSchema, pVarPrefix); }

    bool TryVerifyItems(__in PCWSTR pVarPrefix) const { return TryVerifyItems(m_pSchema, pVarPrefix); }

    // Static helper methods for those who want to do build schemas one step at a time
    static HRESULT CreateNewSchemaFromTestVars(
        __in PriSectionBuilder* pPriBuilder,
        __in PCWSTR pVarPrefix,
        __in_opt PCWSTR pBaselineFolder,
        _Outptr_opt_result_maybenull_ StandalonePriFile** ppBaselinePriOut,
        _Outptr_ HierarchicalSchemaSectionBuilder** value);

    static HRESULT CreateNewSchemaFromTestVars(
        __in PriSectionBuilder* pPriBuilder,
        __in PCWSTR pVarPrefix,
        __in_opt const IHierarchicalSchema* pBaselineSchema,
        _Outptr_ HierarchicalSchemaSectionBuilder** value);

    static bool TryAddItemsFromTestVars(
        __in PriSectionBuilder* pPriBuilder,
        __in HierarchicalSchemaSectionBuilder* pSchemaBuilder,
        __in PCWSTR pVarPrefix);

    static bool TryVerifySchema(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix);

    static bool TryVerifyVersion(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix);

    static bool TryVerifyScopes(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix);

    static bool TryVerifyItems(__in const IHierarchicalSchema* pSchema, __in PCWSTR pVarPrefix);

    static bool TryVerifyCompatibility(
        __in const IHierarchicalSchema* pOlderSchema,
        __in const IHierarchicalSchema* pNewerSchema,
        __in PCWSTR pVarPrefix);
};

} // namespace UnitTests
