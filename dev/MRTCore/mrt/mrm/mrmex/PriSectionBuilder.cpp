// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

PriSectionBuilder::PriSectionBuilder(_In_opt_ FileBuilder* pFileBuilder) :
    m_pFileBuilder(pFileBuilder),
    m_pAtoms(nullptr),
    m_pUnifiedEnvironment(nullptr),
    m_pDecisionInfo(nullptr),
    m_pSchemas(nullptr),
    m_pMaps(nullptr),
    m_environmentMapping(nullptr),
    m_environmentBaseline(nullptr),
    m_pPrimarySchemaName(nullptr),
    m_pPrimarySchema(nullptr),
    m_pPrimaryMap(nullptr),
    m_pAlternateSchemaName(nullptr),
    m_pAlternateSchema(nullptr),
    m_pAlternateMap(nullptr),
    m_sectionIndex(BaseFile::SectionIndexNone),
    m_priBuilderPhase(PriBuilderPhase::PriUninitialized),
    m_priBuildType(PriBuildType::PriBuildFromScratch),
    m_nFlags(0),
    m_bAllocFileBuilder(false),
    m_dataItems(nullptr),
    m_pFileListBuilder(nullptr),
    m_linkBuilders(nullptr),
    m_pBuilderConfiguration(nullptr)
{}

PriSectionBuilder::~PriSectionBuilder()
{
    delete m_pUnifiedEnvironment;
    m_pUnifiedEnvironment = nullptr;

    if (m_pSchemas != nullptr)
    {
        for (int i = 0; i < m_pSchemas->Count(); i++)
        {
            HierarchicalSchemaSectionBuilder* pSchema;
            if (SUCCEEDED(m_pSchemas->Get(i, &pSchema)))
            {
                delete pSchema;
            }
        }

        delete m_pSchemas;
        m_pSchemas = nullptr;
    }

    delete m_pDecisionInfo;
    m_pDecisionInfo = nullptr;

    if (m_pMaps != nullptr)
    {
        for (int i = 0; i < m_pMaps->Count(); i++)
        {
            ResourceMapSectionBuilder* pMap;
            if (SUCCEEDED(m_pMaps->Get(i, &pMap)))
            {
                delete pMap;
            }
        }
        delete m_pMaps;
        m_pMaps = nullptr;
    }

    delete m_dataItems;

    if (m_linkBuilders != nullptr)
    {
        for (int i = 0; i < m_linkBuilders->Count(); i++)
        {
            ResourceLinkSectionBuilder* links;
            if (SUCCEEDED(m_linkBuilders->Get(i, &links)))
            {
                delete links;
            }
        }

        delete m_linkBuilders;
        m_linkBuilders = nullptr;
    }

    delete m_pFileListBuilder;
    m_pFileListBuilder = nullptr;

    delete m_environmentBaseline;
    delete m_environmentMapping;

    if (m_pPrimarySchemaName != nullptr)
    {
        Def_Free(m_pPrimarySchemaName);
    }

    m_pPrimarySchemaName = nullptr;
    m_pPrimarySchema = nullptr;
    m_pPrimaryMap = nullptr;

    if (m_pAlternateSchemaName != nullptr)
    {
        Def_Free(m_pAlternateSchemaName);
    }

    m_pAlternateSchemaName = nullptr;
    m_pAlternateSchema = nullptr;
    m_pAlternateMap = nullptr;

    delete m_pAtoms;
    m_pAtoms = nullptr;
}

HRESULT PriSectionBuilder::Init(_In_ CoreProfile* pProfile)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pProfile);
    RETURN_HR_IF(E_DEF_NOT_READY, m_pFileBuilder == nullptr);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    m_pBuilderConfiguration = pProfile->GetBuildConfiguration();
    if (m_pBuilderConfiguration == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    RETURN_IF_FAILED(AtomPoolGroup::CreateInstance(10, &m_pAtoms));

    RETURN_IF_FAILED(UnifiedEnvironment::CreateInstance(pProfile, m_pAtoms, &m_pUnifiedEnvironment));
    RETURN_IF_FAILED(DynamicArray<HierarchicalSchemaSectionBuilder*>::CreateInstance(2, &m_pSchemas));
    RETURN_IF_FAILED(DynamicArray<ResourceMapSectionBuilder*>::CreateInstance(2, &m_pMaps));

    _Analysis_assume_((m_pUnifiedEnvironment != nullptr) && (m_pSchemas != nullptr) && (m_pMaps != nullptr));

    RETURN_IF_FAILED(DecisionInfoSectionBuilder::CreateInstance(m_pFileBuilder, m_pUnifiedEnvironment, &m_pDecisionInfo));
    RETURN_IF_FAILED(m_pFileBuilder->AddSection(m_pDecisionInfo));

    // Add the PriSectionBuilder as a section to m_pFileBuilder
    RETURN_IF_FAILED(m_pFileBuilder->AddSection(this));

    // See if we have to include mappings from some previous baseline
    int baseEnvironmentIndex;
    if (pProfile->TryGetBaseEnvironmentIndex(&baseEnvironmentIndex))
    {
        RETURN_IF_FAILED(pProfile->CreateEnvironment(baseEnvironmentIndex, m_pAtoms, &m_environmentBaseline));
        RETURN_IF_FAILED(EnvironmentMappingSectionBuilder::CreateInstance(
            m_pUnifiedEnvironment->GetDefaultEnvironment(), m_environmentBaseline, &m_environmentMapping));
        RETURN_IF_FAILED(m_pFileBuilder->AddSection(m_environmentMapping));
    }

    RETURN_IF_FAILED(DataItemOrchestrator::CreateInstance(m_pFileBuilder, pProfile, m_pDecisionInfo, &m_dataItems));

    return S_OK;
}

HRESULT PriSectionBuilder::CreateInstance(_In_ FileBuilder* pFileBuilder, _In_ CoreProfile* pProfile, _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pFileBuilder == nullptr));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    pRtrn->m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriSectionBuilder::CreateInstance(
    _In_ FileBuilder* pFileBuilder,
    _In_ PCWSTR pPackageName,
    _In_ UINT16 majorVersion,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pProfile == nullptr) || (pFileBuilder == nullptr) || DefString_IsEmpty(pPackageName) || (majorVersion < 0));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    RETURN_IF_FAILED(pRtrn->InitFromScratch(pPackageName, majorVersion, pProfile));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriSectionBuilder::CreateInstance(
    _In_ FileBuilder* pFileBuilder,
    _In_ const IHierarchicalSchema* const pPreviousSchema,
    _In_ CoreProfile* pProfile,
    _In_ PriBuildType priBuildType,
    _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pProfile == nullptr) || (pFileBuilder == nullptr) || (pPreviousSchema == nullptr));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    pRtrn->m_priBuildType = priBuildType;

    const IHierarchicalSchemaVersionInfo* pPreviousSchemaVersion = pPreviousSchema->GetVersionInfo();
    DEF_ASSERT(pPreviousSchemaVersion != nullptr);
    _Analysis_assume_(pPreviousSchemaVersion != nullptr);

    RETURN_IF_FAILED(pRtrn->AddPrimarySchemaBuilder(pPreviousSchemaVersion->GetMajorVersion(), pPreviousSchema));

    pRtrn->m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    RETURN_IF_FAILED(pRtrn->GetOrAddPrimaryResourceMapBuilder(nullptr));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT
PriSectionBuilder::CreateInstance(
    _In_ FileBuilder* pFileBuilder,
    _In_ PCWSTR pPackageName,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pProfile == nullptr) || (pFileBuilder == nullptr) || DefString_IsEmpty(pPackageName));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    RETURN_IF_FAILED(pRtrn->InitFromSchema(pPackageName, pProfile));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriSectionBuilder::CreateInstance(
    _In_ FileBuilder* pFileBuilder,
    _In_ PCWSTR pNewSchemaName,
    _In_ PCWSTR pPriFilePath,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(
        E_INVALIDARG,
        (pProfile == nullptr) || (pFileBuilder == nullptr) || DefString_IsEmpty(pNewSchemaName) || DefString_IsEmpty(pPriFilePath));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    RETURN_IF_FAILED(pRtrn->InitFromReadOnlySchema(pNewSchemaName, pPriFilePath, pProfile));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriSectionBuilder::CreateForResourcePack(
    _In_ FileBuilder* pFileBuilder,
    _In_ PCWSTR pNewSchemaName,
    _In_ const IHierarchicalSchema* pPreviousSchema,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(
        E_INVALIDARG,
        (pProfile == nullptr) || (pFileBuilder == nullptr) || DefString_IsEmpty(pNewSchemaName) || (pPreviousSchema == nullptr));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    RETURN_IF_FAILED(pRtrn->InitFromReadOnlySchema(pNewSchemaName, pPreviousSchema, pProfile));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriSectionBuilder::CreateInstance(
    _In_ FileBuilder* pFileBuilder,
    _In_reads_bytes_(cbPriData) const BYTE* pPriData,
    _In_ size_t cbPriData,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pProfile == nullptr) || (pFileBuilder == nullptr) || (pPriData == nullptr) || (cbPriData == 0));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    RETURN_IF_FAILED(pRtrn->InitFromSchema(pPriData, cbPriData, pProfile));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriSectionBuilder::CreateInstance(
    _In_ FileBuilder* pFileBuilder,
    _In_ PCWSTR pNewSchemaName,
    _In_reads_bytes_(cbPriData) const BYTE* pPriData,
    _In_ size_t cbPriData,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriSectionBuilder** result)
{
    *result = nullptr;

    RETURN_HR_IF(
        E_INVALIDARG,
        (pProfile == nullptr) || (pFileBuilder == nullptr) || (pPriData == nullptr) || (cbPriData == 0) ||
            DefString_IsEmpty(pNewSchemaName));

    AutoDeletePtr<PriSectionBuilder> pRtrn = new PriSectionBuilder(pFileBuilder);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pProfile));
    RETURN_IF_FAILED(pRtrn->InitFromReadOnlySchema(pNewSchemaName, pPriData, cbPriData, pProfile));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriSectionBuilder::InitFromScratch(_In_ PCWSTR pPackageName, _In_ UINT16 majorVersion, _In_ CoreProfile* /*pProfile*/)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPackageName));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    m_priBuildType = PriBuildType::PriBuildFromScratch;

    RETURN_IF_FAILED(DefString_Dup(pPackageName, &m_pPrimarySchemaName));

    RETURN_IF_FAILED(AddPrimarySchemaBuilder(majorVersion, nullptr));

    m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(nullptr));

    return S_OK;
}

HRESULT PriSectionBuilder::InitFromSchema(_In_ PCWSTR pPriFilePath, _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPriFilePath) || (pProfile == nullptr));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    m_priBuildType = PriBuildType::PriBuildFromPrevSchema;
    RETURN_IF_FAILED(InitFromSchemaHelper(pPriFilePath, pProfile));

    m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    return S_OK;
}

HRESULT PriSectionBuilder::InitFromReadOnlySchema(_In_ PCWSTR pNewSchemaName, _In_ PCWSTR pPriFilePath, _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pNewSchemaName) || DefString_IsEmpty(pPriFilePath) || (pProfile == nullptr));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    m_priBuildType = PriBuildType::PriBuildFromPrevReadOnlySchema;
    RETURN_IF_FAILED(DefString_Dup(pNewSchemaName, &m_pAlternateSchemaName));
    RETURN_IF_FAILED(InitFromSchemaHelper(pPriFilePath, pProfile));

    m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    return S_OK;
}

HRESULT PriSectionBuilder::InitFromSchemaHelper(_In_ PCWSTR pPriFilePath, _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPriFilePath));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    AutoDeletePtr<StandalonePriFile> pPri;
    const IHierarchicalSchema* pSchema = nullptr;

    RETURN_IF_FAILED(StandalonePriFile::CreateInstance(0, pPriFilePath, pProfile, &pPri));

    RETURN_IF_FAILED(pPri->GetPrimarySchema(&pSchema));

    if ((m_pAlternateSchemaName != nullptr) && (DefString_Compare(m_pAlternateSchemaName, pSchema->GetSimpleId()) == Def_Equal))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_MAP_NAME);
    }

    // Create a ResourceSchemaSectionBuilder from pPreviousSchema and set it as default schema
    RETURN_IF_FAILED(AddPrimarySchemaBuilder(pSchema->GetMajorVersion(), pSchema));

    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(nullptr));

    return S_OK;
}

HRESULT
PriSectionBuilder::InitFromSchema(_In_reads_bytes_(cbPriData) const BYTE* pPriData, _In_ size_t cbPriData, _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, (pPriData == nullptr) || (cbPriData <= 0) || (pProfile == nullptr));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    m_priBuildType = PriBuildType::PriBuildFromPrevSchema;
    RETURN_IF_FAILED(InitFromSchemaHelper(pPriData, cbPriData, pProfile));

    m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    return S_OK;
}

HRESULT PriSectionBuilder::InitFromReadOnlySchema(
    _In_ PCWSTR pNewSchemaName,
    _In_reads_bytes_(cbPriData) const BYTE* pPriData,
    _In_ size_t cbPriData,
    _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, (pPriData == nullptr) || (cbPriData <= 0) || (pProfile == nullptr));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    m_priBuildType = PriBuildType::PriBuildFromPrevReadOnlySchema;
    RETURN_IF_FAILED(DefString_Dup(pNewSchemaName, &m_pAlternateSchemaName));
    RETURN_IF_FAILED(InitFromSchemaHelper(pPriData, cbPriData, pProfile));

    m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    return S_OK;
}

HRESULT PriSectionBuilder::InitFromReadOnlySchema(
    _In_ PCWSTR pNewSchemaName,
    _In_ const IHierarchicalSchema* pPreviousSchema,
    _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, (pPreviousSchema == nullptr) || (pProfile == nullptr));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    m_priBuildType = PriBuildType::PriBuildFromPrevReadOnlySchema;
    RETURN_IF_FAILED(DefString_Dup(pNewSchemaName, &m_pAlternateSchemaName));
    RETURN_IF_FAILED(InitFromSchemaHelper(pPreviousSchema));

    m_priBuilderPhase = PriBuilderPhase::PriInitialized;

    return S_OK;
}

HRESULT PriSectionBuilder::InitFromSchemaHelper(_In_reads_bytes_(cbData) const BYTE* pData, _In_ size_t cbData, _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, (pData == nullptr) || (cbData <= 0) || (pProfile == nullptr));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    AutoDeletePtr<StandalonePriFile> pPri;
    const IHierarchicalSchema* pSchema = nullptr;

    RETURN_IF_FAILED(StandalonePriFile::CreateInstance(0, pData, cbData, pProfile, &pPri));

    RETURN_IF_FAILED(pPri->GetPrimarySchema(&pSchema));

    // Create a second ResourceSchemaSectionBuilder from pPreviousSchema
    RETURN_IF_FAILED(AddPrimarySchemaBuilder(pSchema->GetMajorVersion(), pSchema));

    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(nullptr));

    return S_OK;
}

HRESULT PriSectionBuilder::InitFromSchemaHelper(_In_ const IHierarchicalSchema* pPreviousSchema)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pPreviousSchema);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    if ((m_pAlternateSchemaName != nullptr) && (DefString_Compare(m_pAlternateSchemaName, pPreviousSchema->GetSimpleId()) == Def_Equal))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_MAP_NAME);
    }

    // Create a ResourceSchemaSectionBuilder from pPreviousSchema and set it as default schema
    RETURN_IF_FAILED(AddPrimarySchemaBuilder(pPreviousSchema->GetMajorVersion(), pPreviousSchema));

    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(nullptr));

    return S_OK;
}

HRESULT PriSectionBuilder::AddPrimarySchemaBuilder(_In_ UINT16 majorVersion, _In_opt_ const IHierarchicalSchema* pPreviousSchema)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriUninitialized);

    StringResult uniqueName;
    AutoDeletePtr<HierarchicalSchemaSectionBuilder> pSchema;

    if (m_pPrimarySchema != nullptr)
    {
        return S_OK;
    }

    if (m_priBuildType == PriBuildType::PriBuildFromScratch)
    {
        // Create a schema section builder with the default unique name as defined by our profile
        // and version 1.0.
        RETURN_IF_FAILED(m_pUnifiedEnvironment->GetProfile()->GetDefaultUniqueName(m_pPrimarySchemaName, &uniqueName));

        RETURN_IF_FAILED(
            HierarchicalSchemaSectionBuilder::CreateInstance(this, m_pPrimarySchemaName, uniqueName.GetRef(), majorVersion, &pSchema));
    }
    else if (
        (m_priBuildType == PriBuildType::PriBuildFromPrevSchema) || (m_priBuildType == PriBuildType::PriBuildFromPrevReadOnlySchema) ||
        (m_priBuildType == PriBuildType::PriBuildForDeploymentMerge))
    {
        RETURN_IF_FAILED(HierarchicalSchemaSectionBuilder::CreateInstance(this, pPreviousSchema, m_priBuildType, &pSchema));
    }
    else
    {
        return E_NOTIMPL;
    }

    int index;
    RETURN_IF_FAILED(AddSchemaBuilder(pSchema, true, &index));

    pSchema.Detach();

    return S_OK;
}

HRESULT PriSectionBuilder::AddAlternateSchemaBuilder()
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);

    StringResult secondSchemaUniqueName;
    UINT16 iMajorVersion = 1;
    AutoDeletePtr<HierarchicalSchemaSectionBuilder> pSchema;

    RETURN_IF_FAILED(secondSchemaUniqueName.Init(L":"));

    if (m_pAlternateSchema != nullptr)
    {
        return S_OK;
    }

    if (m_priBuildType != PriBuildType::PriBuildFromPrevReadOnlySchema)
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }

    RETURN_IF_FAILED(secondSchemaUniqueName.Concat(m_pAlternateSchemaName));

    RETURN_IF_FAILED(HierarchicalSchemaSectionBuilder::CreateInstance(
        this, m_pAlternateSchemaName, secondSchemaUniqueName.GetRef(), iMajorVersion, &pSchema));

    int index;
    RETURN_IF_FAILED(AddSchemaBuilder(pSchema, false, &index));

    m_pAlternateSchema = pSchema.Detach();

    return S_OK;
}

HRESULT PriSectionBuilder::AddCandidateWithString(
    _In_opt_ PCWSTR schemaName,
    _In_ PCWSTR resourceName,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_opt_ PCWSTR value,
    _In_opt_ IQualifierSet* qualifiers)
{
    RETURN_IF_FAILED(GetCanAddCandidate(schemaName, resourceName));
    RETURN_HR_IF(E_DEF_INCOMPATIBLE_VALUE_TYPE, !MrmEnvironment::IsUtf16ResourceValueType(valueType));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetMapBuilderForAddCandidate(schemaName, &mapBuilder));

    value = (value ? value : L"");

    if (m_pBuilderConfiguration->UseDataItemLocator())
    {
        AutoDeletePtr<IBuildInstanceReference> buildInstanceReference;
        MrmEnvironment::ResourceValueType optimalValueType = valueType;
        int qualifierSetIndex;

        if (m_pBuilderConfiguration->UseOptimalPayloadEncoding())
        {
            RETURN_IF_FAILED(m_dataItems->AddOptimizedStringAndCreateInstanceReference(
                valueType, value, qualifiers, &buildInstanceReference, &qualifierSetIndex, &optimalValueType));
        }
        else
        {
            RETURN_IF_FAILED(
                m_dataItems->AddStringAndCreateInstanceReference(value, qualifiers, &buildInstanceReference, &qualifierSetIndex));
        }

        RETURN_IF_FAILED(mapBuilder->AddCandidate(resourceName, optimalValueType, buildInstanceReference, qualifierSetIndex));

        // else buildInstanceReference will be deleted when ResourceMapSectionBuilder::Build resolves
        // the DataItemSectionBuilder's section index, which is not available until all sections are finalized
        buildInstanceReference.Detach();
    }
    else
    {
        // Internal strings do not support optimized payload
        PCWSTR valueAsString = reinterpret_cast<PCWSTR>(value);
#pragma prefast(suppress : 26018, "This legacy path can only ever be called with a null-terminated string.")

        RETURN_IF_FAILED(mapBuilder->AddCandidateWithInternalString(resourceName, valueType, valueAsString, qualifiers));
    }

    return S_OK;
}

HRESULT PriSectionBuilder::AddCandidateWithEmbeddedData(
    _In_opt_ PCWSTR schemaName,
    _In_ PCWSTR resourceName,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_reads_bytes_(valueSizeInBytes) const BYTE* value,
    _In_ UINT valueSizeInBytes,
    _In_opt_ IQualifierSet* qualifiers)
{
    // This must be Windows Blue environment (Windows 8 profile will fail this locator test)
    RETURN_IF_FAILED(GetCanAddCandidate(schemaName, resourceName));
    RETURN_HR_IF(E_DEF_INCOMPATIBLE_LOCATOR_TYPE, !m_pBuilderConfiguration->UseDataItemLocator());
    RETURN_HR_IF_NULL(E_INVALIDARG, value);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), !MrmEnvironment::IsBinaryResourceValueType(valueType));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetMapBuilderForAddCandidate(schemaName, &mapBuilder));

    int qualifierSetIndex;

    AutoDeletePtr<IBuildInstanceReference> buildInstanceReference;
    RETURN_IF_FAILED(
        m_dataItems->AddDataAndCreateInstanceReference(value, valueSizeInBytes, qualifiers, &buildInstanceReference, &qualifierSetIndex));

    RETURN_IF_FAILED(mapBuilder->AddCandidate(resourceName, valueType, buildInstanceReference, qualifierSetIndex));

    // else buildInstanceReference will be deleted when ResourceMapSectionBuilder::Build resolves
    // the DataItemSectionBuilder's section index, which is not available until all sections are finalized
    buildInstanceReference.Detach();

    return S_OK;
}

HRESULT PriSectionBuilder::GetCanAddCandidate(_In_opt_ PCWSTR schemaName, _In_ PCWSTR resourceName) const
{

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);
    RETURN_HR_IF(E_INVALIDARG, (schemaName != nullptr) && DefString_IsEmpty(schemaName));
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(resourceName));

    return S_OK;
}

HRESULT PriSectionBuilder::GetMapBuilderForAddCandidate(_In_opt_ PCWSTR schemaName, _Out_ ResourceMapSectionBuilder** result)
{
    *result = nullptr;

    if (schemaName != nullptr)
    {
        *result = GetResourceMapBuilder(schemaName);
    }
    else
    {
        RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(result));
    }

    return S_OK;
}

HRESULT PriSectionBuilder::AddCandidateByReference(
    _In_opt_ PCWSTR schemaName,
    _In_ PCWSTR resourceName,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_ IBuildInstanceReference* buildInstanceReference,
    _In_opt_ IQualifierSet* qualifiers)

{
    // The method is called from the Runtime merge operation where it already has
    // resource packs that gives can file and data item index
    RETURN_IF_FAILED(GetCanAddCandidate(schemaName, resourceName));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetMapBuilderForAddCandidate(schemaName, &mapBuilder));

    // Add qualifierSet to the DecisionInfoSectionBuilder and get the
    // qualifier index,
    int qualifierSetIndex;
    RETURN_IF_FAILED(m_pDecisionInfo->GetOrAddQualifierSet(qualifiers, &qualifierSetIndex));

    return mapBuilder->AddCandidate(resourceName, valueType, buildInstanceReference, qualifierSetIndex);
}

HRESULT PriSectionBuilder::AddCandidateByReference(
    _In_opt_ PCWSTR schemaName,
    _In_ PCWSTR resourceName,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_ IBuildInstanceReference* buildInstanceReference,
    _In_ int newQualifierSetIndex)
{
    // The method is called from the Runtime merge operation where it already has
    // resource packs that gives can file and data item index
    RETURN_IF_FAILED(GetCanAddCandidate(schemaName, resourceName));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetMapBuilderForAddCandidate(schemaName, &mapBuilder));
    return mapBuilder->AddCandidate(resourceName, valueType, buildInstanceReference, newQualifierSetIndex);
}

HRESULT PriSectionBuilder::AddCandidateByReference(
    _In_opt_ PCWSTR schemaName,
    _In_ Atom::Index resourceIndex,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_ IBuildInstanceReference* buildInstanceReference,
    _In_ int newQualifierSetIndex)
{
    // The method is called from the Resource Pack merge operation that can easily pass the
    // Atom type item name, and new qualifier set instead of QualifierSet object
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);
    RETURN_HR_IF(E_INVALIDARG, (schemaName != nullptr) && DefString_IsEmpty(schemaName));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetMapBuilderForAddCandidate(schemaName, &mapBuilder));
    return mapBuilder->AddCandidate(resourceIndex, valueType, buildInstanceReference, newQualifierSetIndex);
}

HRESULT PriSectionBuilder::AddResourceLink(_In_ PCWSTR linkFromResourceName, _In_ PCWSTR linkToResourceName)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(linkFromResourceName) || DefString_IsEmpty(linkToResourceName));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(&mapBuilder));

    return mapBuilder->AddResourceLink(linkFromResourceName, linkToResourceName);
}

HRESULT PriSectionBuilder::AddResourceLink(_In_ int linkFromResourceIndex, _In_ PCWSTR linkToResourceName)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(linkToResourceName));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(&mapBuilder));

    return mapBuilder->AddResourceLink(linkFromResourceIndex, linkToResourceName);
}

HRESULT
PriSectionBuilder::AddResourceLink(
    _In_ PCWSTR linkFromResourceName,
    _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
    _In_ PCWSTR linkToResourceName)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(linkFromResourceName) || DefString_IsEmpty(linkToResourceName));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(&mapBuilder));

    return mapBuilder->AddResourceLink(linkFromResourceName, linkToSchema, linkToResourceName);
}

HRESULT
PriSectionBuilder::AddResourceLink(
    _In_ int linkFromResourceIndex,
    _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
    _In_ PCWSTR linkToResourceName)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);
    RETURN_HR_IF(E_INVALIDARG, (linkToSchema == nullptr) || DefString_IsEmpty(linkToResourceName));

    ResourceMapSectionBuilder* mapBuilder;
    RETURN_IF_FAILED(GetOrAddPrimaryResourceMapBuilder(&mapBuilder));

    return mapBuilder->AddResourceLink(linkFromResourceIndex, linkToSchema, linkToResourceName);
}

const UnifiedEnvironment* PriSectionBuilder::GetEnvironment() const { return m_pUnifiedEnvironment; }

HRESULT PriSectionBuilder::GetSchemaVersionInfo(_In_opt_ PCWSTR pSchemaName, _Out_ UINT16* pMajorVersion, _Out_ UINT16* pMinorVersion) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriFinalizedAll);
    RETURN_HR_IF(E_INVALIDARG, (pMajorVersion == nullptr) || (pMinorVersion == nullptr));

    HierarchicalSchemaSectionBuilder* pSchema = GetSchemaBuilder(pSchemaName);
    if (pSchema == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    *pMajorVersion = pSchema->GetMajorVersion();
    *pMinorVersion = pSchema->GetMinorVersion();
    return S_OK;
}

int PriSectionBuilder::GetNumSchemas() const { return m_pSchemas->Count(); }

HierarchicalSchemaSectionBuilder* PriSectionBuilder::GetSchemaBuilder(_In_ int index) const
{
    HierarchicalSchemaSectionBuilder* pSchema = nullptr;
    if (!m_pSchemas->TryGet(index, &pSchema))
    {
        return nullptr;
    }

    return pSchema;
}

HierarchicalSchemaSectionBuilder* PriSectionBuilder::GetSchemaBuilder(_In_opt_ PCWSTR pSchemaName) const
{
    if (DefString_IsEmpty(pSchemaName))
    {
        return m_pPrimarySchema;
    }

    HierarchicalSchemaSectionBuilder* pSchema = nullptr;

    for (int i = 0; i < m_pSchemas->Count(); i++)
    {
        if (m_pSchemas->TryGet(i, &pSchema))
        {
            if (DefString_ICompare(pSchema->GetSimpleId(), pSchemaName) == Def_Equal)
            {
                return pSchema;
            }
        }
    }

    return nullptr;
}

HRESULT PriSectionBuilder::AddSchemaBuilder(_In_ HierarchicalSchemaSectionBuilder* pSchema, _In_ bool isDefault, _Out_ int* index)
{
    *index = -1;
    RETURN_HR_IF_NULL(E_INVALIDARG, pSchema);

    int indexRtrn = -1;
    RETURN_IF_FAILED(m_pSchemas->Add(pSchema, &indexRtrn));
    RETURN_IF_FAILED(m_pFileBuilder->AddSection(pSchema));

    if (isDefault)
    {
        if (m_pPrimarySchemaName != nullptr)
        {
            Def_Free(m_pPrimarySchemaName);
        }
        RETURN_IF_FAILED(DefString_Dup(pSchema->GetUniqueId(), &m_pPrimarySchemaName));
        m_pPrimarySchema = pSchema;
        m_pPrimaryMap = nullptr;
    }
    *index = indexRtrn;

    return S_OK;
}

HRESULT PriSectionBuilder::GetQualifierSetBuilder(_Outptr_ DecisionInfoQualifierSetBuilder** result) const
{
    return DecisionInfoQualifierSetBuilder::CreateInstance(m_pDecisionInfo, result);
}

int PriSectionBuilder::GetNumResourceMaps() const { return m_pMaps->Count(); }

ResourceMapSectionBuilder* PriSectionBuilder::GetResourceMapBuilder(_In_ int index) const
{
    ResourceMapSectionBuilder* pMap = nullptr;

    if (!m_pMaps->TryGet(index, &pMap))
    {
        return nullptr;
    }

    return pMap;
}

ResourceMapSectionBuilder* PriSectionBuilder::GetResourceMapBuilder(_In_opt_ PCWSTR pSchemaName) const
{
    if (DefString_IsEmpty(pSchemaName))
    {
        return m_pPrimaryMap;
    }

    ResourceMapSectionBuilder* pMap = nullptr;
    HierarchicalSchemaSectionBuilder* pSchema = nullptr;

    for (int i = 0; i < m_pMaps->Count(); i++)
    {
        if (m_pMaps->TryGet(i, &pMap))
        {
            pSchema = pMap->GetSchema();

            DEF_ASSERT(pSchema != nullptr);

            if (DefString_ICompare(pSchema->GetSimpleId(), pSchemaName) == Def_Equal)
            {
                return pMap;
            }
        }
    }

    return nullptr;
}

HRESULT PriSectionBuilder::GetOrAddPrimaryResourceMapBuilder(_Out_opt_ ResourceMapSectionBuilder** result)
{
    if (result != nullptr)
    {
        *result = nullptr;
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase > PriBuilderPhase::PriInitialized);

    if (m_pPrimaryMap == nullptr)
    {
        AutoDeletePtr<ResourceMapSectionBuilder> pMap;

        // Create the default ResourceMapSectionBuilder
        RETURN_IF_FAILED(ResourceMapSectionBuilder::CreateInstance(
            this, m_pPrimarySchema, m_pDecisionInfo, m_pUnifiedEnvironment, m_priBuildType, &pMap));

        int index;
        RETURN_IF_FAILED(AddResourceMapBuilder(pMap, true, &index));

        pMap.Detach();
    }

    if (result != nullptr)
    {
        *result = m_pPrimaryMap;
    }

    return S_OK;
}

HRESULT PriSectionBuilder::GetOrAddAlternateResourceMapBuilder(_Out_ ResourceMapSectionBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase > PriBuilderPhase::PriInitialized);

    if (m_pAlternateMap != nullptr)
    {
        *result = m_pAlternateMap;
        return S_OK;
    }

    RETURN_IF_FAILED(AddAlternateSchemaBuilder());

    // Create a second ResourceMapSectionBuilder
    AutoDeletePtr<ResourceMapSectionBuilder> pMap;
    RETURN_IF_FAILED(
        ResourceMapSectionBuilder::CreateInstance(this, m_pAlternateSchema, m_pDecisionInfo, m_pUnifiedEnvironment, m_priBuildType, &pMap));

    int index;
    RETURN_IF_FAILED(AddResourceMapBuilder(pMap, false, &index));

    m_pAlternateMap = pMap.Detach();
    *result = m_pAlternateMap;

    return S_OK;
}

HRESULT PriSectionBuilder::AddResourceMapBuilder(_In_ ResourceMapSectionBuilder* pMap, _In_ bool isDefault, _Out_ int* index)
{
    *index = -1;
    RETURN_HR_IF_NULL(E_INVALIDARG, pMap);

    int indexRtrn = -1;
    RETURN_IF_FAILED(m_pMaps->Add(pMap, &indexRtrn));
    RETURN_IF_FAILED(m_pFileBuilder->AddSection(pMap));

    if (isDefault)
    {
        m_pPrimaryMap = pMap;
        if (m_pPrimarySchema != pMap->GetSchema())
        {
            if (m_pPrimarySchemaName != nullptr)
            {
                Def_Free(m_pPrimarySchemaName);
            }
            RETURN_IF_FAILED(DefString_Dup(pMap->GetSchema()->GetUniqueId(), &m_pPrimarySchemaName));
            m_pPrimarySchema = pMap->GetSchema();
        }
    }
    *index = indexRtrn;
    return S_OK;
}

HRESULT PriSectionBuilder::AddResourceMapBuilder(
    _In_ const IHierarchicalSchema* pPreviousSchema,
    _In_ bool bIsDefault,
    _In_ PriBuildType priBuildType,
    _Out_ int* index)
{
    *index = -1;
    RETURN_HR_IF_NULL(E_INVALIDARG, pPreviousSchema);

    HierarchicalSchemaSectionBuilder* pSchema = nullptr;
    AutoDeletePtr<ResourceMapSectionBuilder> pMap;

    pSchema = GetSchemaBuilder(pPreviousSchema->GetSimpleId());
    if (pSchema == nullptr)
    {
        RETURN_IF_FAILED(HierarchicalSchemaSectionBuilder::CreateInstance(this, pPreviousSchema, priBuildType, &pSchema));

        int builderIndex;
        HRESULT hr = AddSchemaBuilder(pSchema, bIsDefault, &builderIndex);
        if (FAILED(hr))
        {
            delete pSchema;
            return hr;
        }
    }

    RETURN_IF_FAILED(
        ResourceMapSectionBuilder::CreateInstance(this, pSchema, m_pDecisionInfo, m_pUnifiedEnvironment, m_priBuildType, &pMap));

    RETURN_IF_FAILED(AddResourceMapBuilder(pMap, bIsDefault, index));

    pMap.Detach();

    return S_OK;
}

HRESULT
PriSectionBuilder::GetOrAddResourceLinkBuilder(_In_ ResourceMapSectionBuilder* mapBuilder, _Out_ ResourceLinkSectionBuilder** result)
{
    *result = nullptr;

    ResourceLinkSectionBuilder* rtrn = mapBuilder->GetLinks();
    if (rtrn == nullptr)
    {
        if (m_linkBuilders != nullptr)
        {
            for (int i = 0; i < m_linkBuilders->Count(); i++)
            {
                ResourceLinkSectionBuilder* current;
                (void)m_linkBuilders->Get(i, &current);
                if ((current != nullptr) && (current->GetSchema() == mapBuilder->GetSchema()))
                {
                    rtrn = current;
                    break;
                }
            }
        }
        else
        {
            RETURN_IF_FAILED(DynamicArray<ResourceLinkSectionBuilder*>::CreateInstance(2, &m_linkBuilders));
        }

        if (rtrn == nullptr)
        {
            RETURN_IF_FAILED(ResourceLinkSectionBuilder::CreateInstance(mapBuilder->GetSchema(), &rtrn));

            HRESULT hr = m_linkBuilders->Add(rtrn, nullptr);
            if (FAILED(hr))
            {
                delete rtrn;
                return hr;
            }

            RETURN_IF_FAILED(m_pFileBuilder->AddSection(rtrn));
        }
    }

    *result = rtrn;
    return S_OK;
}

HRESULT PriSectionBuilder::AddFileListSectionBuilder(_In_ FileListBuilder* pFileListSectionBuilder)
{
    if (m_pFileListBuilder != nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
    }

    RETURN_IF_FAILED(m_pFileBuilder->AddSection(pFileListSectionBuilder));

    m_pFileListBuilder = pFileListSectionBuilder;
    return S_OK;
}

/*
  *   ISectionBuilder Implementation
  */
bool PriSectionBuilder::IsValid() const { return true; }

HRESULT PriSectionBuilder::Finalize()
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), !IsValid() || (m_priBuilderPhase < PriBuilderPhase::PriInitialized));

    m_priBuilderPhase = PriBuilderPhase::PriFinalizedSection;

    // FileList and DataItem Section Finalize should come before ResourceMap Finalize
    // fileInfo index and data item section should be finalizd before it is used by ResourceMap
    if (m_pFileListBuilder != nullptr)
    {
        RETURN_IF_FAILED(m_pFileListBuilder->Finalize());
    }

    RETURN_IF_FAILED(m_dataItems->Finalize());

    // We have to finalize our maps, then our schemas and then
    // decision info, to make sure they finalize in the proper
    // order.  The file builder will finalize again but that's
    // a no-op.
    for (int i = 0; i < m_pMaps->Count(); i++)
    {
        ResourceMapSectionBuilder* pMap;
        RETURN_IF_FAILED(m_pMaps->Get(i, &pMap));
        RETURN_IF_FAILED(pMap->Finalize());
    }

    for (int i = 0; i < m_pSchemas->Count(); i++)
    {
        HierarchicalSchemaSectionBuilder* pSchema;
        RETURN_IF_FAILED(m_pSchemas->Get(i, &pSchema));
        RETURN_IF_FAILED(pSchema->Finalize());
    }

    RETURN_IF_FAILED(m_pDecisionInfo->Finalize());

    // Now find our primary map, if we have one.
    m_pPrimaryMap = nullptr;
    if (m_pPrimarySchema != nullptr)
    {
        for (int i = 0; i < m_pMaps->Count(); i++)
        {
            ResourceMapSectionBuilder* pMap;
            (void)m_pMaps->Get(i, &pMap);
            if ((pMap != nullptr) && (pMap->GetSchema() == m_pPrimarySchema))
            {
                m_pPrimaryMap = pMap;
            }
        }
    }

    m_priBuilderPhase = PriFinalizedAll;

    return S_OK;
}

UINT32 PriSectionBuilder::GetMaxSizeInBytes() const
{
    if (m_priBuilderPhase < PriBuilderPhase::PriFinalizedSection)
    {
        return 0;
    }

    UINT32 cbTotal = sizeof(MRMFILE_PRI_DESCRIPTOR_EX) + (0 * sizeof(DEFFILE_SECTION_INDEX)) // embedded environments not supported yet
                     + (GetNumSchemas() * sizeof(DEFFILE_SECTION_INDEX)) +
                     (1 * sizeof(DEFFILE_SECTION_INDEX)) // currently support only 1 decision info
                     + (GetNumResourceMaps() * sizeof(DEFFILE_SECTION_INDEX)) +
                     (m_pFileListBuilder ? sizeof(DEFFILE_SECTION_INDEX) : 0) // currently support maximum 1 file reference supported
                     + (m_dataItems->GetNumFinalizedDataItemSections() * sizeof(DEFFILE_SECTION_INDEX)); // data items sections is supported
    cbTotal = _DEFFILE_PAD_SECTION(cbTotal);

    return cbTotal;
}

HRESULT PriSectionBuilder::Build(_Out_writes_bytes_(cbData) VOID* pData, _In_ UINT32 cbData, _Out_opt_ UINT32* pcbWritten) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pData);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase < PriBuilderPhase::PriFinalizedSection);

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(pData, cbData));

    MRMFILE_PRI_DESCRIPTOR_EX* pHeader = nullptr;
    DEFFILE_SECTION_INDEX* pSchemas = nullptr;
    DEFFILE_SECTION_INDEX* pDecisionInfos = nullptr;
    DEFFILE_SECTION_INDEX* pResourceMaps = nullptr;
    DEFFILE_SECTION_INDEX* pDataItems = nullptr;
    DEFFILE_SECTION_INDEX* pFileList = nullptr;
    HRESULT hr = S_OK;

    pHeader = _SECTION_BUILDER_NEXT(data, MRMFILE_PRI_DESCRIPTOR_EX, &hr);
    pSchemas = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumSchemas(), DEFFILE_SECTION_INDEX, &hr);
    pDecisionInfos = _SECTION_BUILDER_NEXT_ARRAY(data, 1, DEFFILE_SECTION_INDEX, &hr);
    pResourceMaps = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumResourceMaps(), DEFFILE_SECTION_INDEX, &hr);

    if (m_pFileListBuilder != nullptr)
    {
        pFileList = _SECTION_BUILDER_NEXT_ARRAY(data, 1, DEFFILE_SECTION_INDEX, &hr);
    }

    if (m_dataItems->GetNumFinalizedDataItemSections() > 0)
    {
        pDataItems = _SECTION_BUILDER_NEXT_ARRAY(data, m_dataItems->GetNumFinalizedDataItemSections(), DEFFILE_SECTION_INDEX, &hr);
    }

    _SECTION_BUILDER_PAD(&data, &hr);
    RETURN_IF_FAILED(hr);

    _Analysis_assume_((pHeader != nullptr) && (pDecisionInfos != nullptr));

    pHeader->flags = static_cast<UINT16>(m_nFlags);
    pHeader->includedFilesSectionIndex = DEFFILE_SECTION_INDEX_NONE;
    pHeader->numEnvironments = 0;
    pHeader->numSchemas = static_cast<UINT16>(GetNumSchemas());
    pHeader->numDecisionInfos = 1;
    pHeader->numResourceMaps = static_cast<UINT16>(GetNumResourceMaps());
    pHeader->primaryResourceMap = (m_pPrimaryMap ? m_pPrimaryMap->GetSectionIndex() : DEFFILE_SECTION_INDEX_NONE);
    pHeader->numReferencedFileSections = 0;
    pHeader->numReferencedFileSections = m_pFileListBuilder ? 1 : 0;
    pHeader->numDataItemSections = static_cast<UINT16>(m_dataItems->GetNumFinalizedDataItemSections());
    pHeader->pad = 0;

    for (int i = 0; i < GetNumSchemas(); i++)
    {
        _Analysis_assume_(pSchemas != nullptr);

        HierarchicalSchemaSectionBuilder* pSchema;
        (void)m_pSchemas->Get(i, &pSchema);
        pSchemas[i] = (pSchema ? pSchema->GetSectionIndex() : DEFFILE_SECTION_INDEX_NONE);
    }

    pDecisionInfos[0] = m_pDecisionInfo->GetSectionIndex();

    for (int i = 0; i < GetNumResourceMaps(); i++)
    {
        _Analysis_assume_(pSchemas != nullptr);

        ResourceMapSectionBuilder* pMap;
        (void)m_pMaps->Get(i, &pMap);
        pResourceMaps[i] = (pMap ? pMap->GetSectionIndex() : DEFFILE_SECTION_INDEX_NONE);
    }

    if (m_pFileListBuilder != nullptr)
    {
        pFileList[0] = m_pFileListBuilder->GetSectionIndex();
    }

    for (int i = 0; i < m_dataItems->GetNumFinalizedDataItemSections(); i++)
    {
        DataItemsSectionBuilder* builder;
        RETURN_IF_FAILED(m_dataItems->GetFinalizedDataItemSection(i, &builder));

        pDataItems[i] = builder->GetSectionIndex();
    }

    if (pcbWritten != nullptr)
    {
        *pcbWritten = static_cast<UINT32>(data.UsedBufferSizeInBytes());
    }

    return S_OK;
}

HRESULT PriSectionBuilder::SetPriFileFlags(_In_ UINT32 nFlags)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), !IsValid() || (m_priBuilderPhase > PriBuilderPhase::PriInitialized));

    m_nFlags = nFlags;

    return S_OK;
}

HRESULT PriFileBuilder::CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(PriSectionBuilder::CreateInstance(pRtrn, pProfile, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileBuilder::CreateInstance(
    _In_ PCWSTR pPackageName,
    _In_ UINT16 majorVersion,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPackageName));

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(PriSectionBuilder::CreateInstance(pRtrn, pPackageName, majorVersion, pProfile, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileBuilder::CreateInstance(
    _In_ const IHierarchicalSchema* const pPreviousSchema,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, pPreviousSchema == nullptr);

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(
        PriSectionBuilder::CreateInstance(pRtrn, pPreviousSchema, pProfile, PriBuildType::PriBuildFromPrevSchema, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileBuilder::CreateInstance(
    _In_ const IHierarchicalSchema* const pPreviousSchema,
    _In_ CoreProfile* pProfile,
    _In_ PriBuildType priBuildType,
    _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, pPreviousSchema == nullptr);

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(PriSectionBuilder::CreateInstance(pRtrn, pPreviousSchema, pProfile, priBuildType, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileBuilder::CreateInstance(
    _In_ PCWSTR pPackageName,
    _In_ PCWSTR pPriFilePath,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPackageName) || DefString_IsEmpty(pPriFilePath));

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(PriSectionBuilder::CreateInstance(pRtrn, pPackageName, pPriFilePath, pProfile, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileBuilder::CreateForResourcePack(
    _In_ PCWSTR pPackageName,
    _In_ const IHierarchicalSchema* pPreviousSchema,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPackageName) || (pPreviousSchema == nullptr));

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(PriSectionBuilder::CreateForResourcePack(pRtrn, pPackageName, pPreviousSchema, pProfile, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileBuilder::CreateInstance(_In_ PCWSTR pPackageName, _In_ CoreProfile* pProfile, _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPackageName));

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(PriSectionBuilder::CreateInstance(pRtrn, pPackageName, pProfile, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileBuilder::CreateInstance(
    _In_reads_bytes_(cbPriData) const BYTE* pPriData,
    _In_ size_t cbPriData,
    _In_ CoreProfile* pProfile,
    _Outptr_ PriFileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pPriData == nullptr) || (*pPriData == 0));

    DEFFILE_MAGIC magic;
    RETURN_IF_FAILED(PriFileBuilder::GetFileMagic(pProfile, &magic));

    AutoDeletePtr<PriFileBuilder> pRtrn = new PriFileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(PriSectionBuilder::CreateInstance(pRtrn, pPriData, cbPriData, pProfile, &pRtrn->m_pDescriptor));

    *result = pRtrn.Detach();
    return S_OK;
}

PriFileBuilder::~PriFileBuilder() { delete m_pDescriptor; }

PriFileBuilder::PriFileBuilder(DEFFILE_MAGIC magic) : FileBuilder(magic), m_pDescriptor(nullptr) {}

HRESULT PriFileBuilder::VerifyFilePath(_In_ PCWSTR pszFilePath)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pszFilePath));

    HANDLE hFindFile;
    WIN32_FIND_DATA FindFileData;

    hFindFile = FindFirstFile(pszFilePath, &FindFileData);

    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    }

    FindClose(hFindFile);

    return S_OK;
}

HRESULT PriFileBuilder::VerifyPriFilePath(_In_ PCWSTR pPriFilePath)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPriFilePath));
    RETURN_IF_FAILED(VerifyFilePath(pPriFilePath));

    if (TRUE == DefString_IsSuffixI(L".pri", pPriFilePath))
    {
        return S_OK;
    }

    return E_FAIL;
}

HRESULT PriFileBuilder::VerifyFileNotEmpty(_In_ PCWSTR pszFilePath)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pszFilePath));

    WIN32_FILE_ATTRIBUTE_DATA attributeData = {};
    RETURN_IF_WIN32_BOOL_FALSE_EXPECTED(GetFileAttributesEx(pszFilePath, GetFileExInfoStandard, static_cast<LPVOID>(&attributeData)));

    if ((attributeData.nFileSizeHigh == 0) && (attributeData.nFileSizeLow == 0))
    {
        return HRESULT_FROM_WIN32(ERROR_NO_DATA);
    }

    return S_OK;
}

HRESULT PriFileBuilder::VerifyPriFileNotEmpty(_In_ PCWSTR pPriFilePath)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPriFilePath));
    RETURN_IF_FAILED_EXPECTED(VerifyFileNotEmpty(pPriFilePath));

    if (TRUE == DefString_IsSuffixI(L".pri", pPriFilePath))
    {
        return S_OK;
    }

    return E_FAIL;
}

HRESULT PriFileBuilder::GetFileMagic(_In_ CoreProfile* pProfile, _Out_ DEFFILE_MAGIC* magic)
{
    DEFFILE_MAGIC nullMagic = {};
    *magic = nullMagic;

    MrmBuildConfiguration* pBuildConfiguration = pProfile->GetBuildConfiguration();
    RETURN_IF_NULL_ALLOC(pBuildConfiguration);

    *magic = pBuildConfiguration->GetFileMagicNumber();
    return S_OK;
}

} // namespace Microsoft::Resources::Build