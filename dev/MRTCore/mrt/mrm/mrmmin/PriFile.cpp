// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"

namespace Microsoft::Resources
{

HRESULT PriDescriptor::CreateInstance(
    _In_ const IFileSectionResolver* const pSections,
    _In_ const ISchemaCollection* const pSchemaCollection,
    _In_ const IFileSection* const pSection,
    _Outptr_ PriDescriptor** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pSection == nullptr) || (pSections == nullptr));

    AutoDeletePtr<PriDescriptor> pRtrn = new PriDescriptor();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSections, pSchemaCollection, pSection, pSection->GetData(), pSection->GetDataSize()));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT PriDescriptor::CreateInstance(
    _In_ const IFileSectionResolver* pSections,
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ int cbData,
    _Outptr_ PriDescriptor** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pSections == nullptr) || (pData == nullptr));

    AutoDeletePtr<PriDescriptor> pRtrn = new PriDescriptor();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSections, pSchemaCollection, nullptr, pData, cbData));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT PriDescriptor::Init(
    _In_ const IFileSectionResolver* pSections,
    _In_ const ISchemaCollection* const pSchemaCollection,
    _In_opt_ const IFileSection* const pSection,
    _In_reads_bytes_(cbData) const void* const pData,
    _In_ int cbData)
{
    SectionParser data;

    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));

    RETURN_IF_FAILED(data.Set(pData, cbData));

    m_pSections = pSections;
    m_pSchemaCollection = pSchemaCollection;

    HRESULT hr = S_OK;
    m_pHeader = _SECTION_PARSER_NEXT(data, MRMFILE_PRI_DESCRIPTOR_EX, &hr);
    RETURN_IF_FAILED(hr);

    _Analysis_assume_(m_pHeader != nullptr);

    if (m_pHeader->numEnvironments > 0)
    {
        // embedded environments not supported yet
        return E_NOTIMPL;
    }

    m_pSchemaSectionIndices = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numSchemas, DEFFILE_SECTION_INDEX, &hr);
    RETURN_IF_FAILED(ValidateSectionIndex(m_pSchemaSectionIndices, m_pHeader->numSchemas));

    m_pDecisionInfoSectionIndices = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numDecisionInfos, DEFFILE_SECTION_INDEX, &hr);
    RETURN_IF_FAILED(ValidateSectionIndex(m_pDecisionInfoSectionIndices, m_pHeader->numDecisionInfos));

    m_pResourceMapSectionIndices = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numResourceMaps, DEFFILE_SECTION_INDEX, &hr);
    RETURN_IF_FAILED(ValidateSectionIndex(m_pResourceMapSectionIndices, m_pHeader->numResourceMaps));

    m_pReferencedFileSectionIndices = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numReferencedFileSections, DEFFILE_SECTION_INDEX, &hr);
    RETURN_IF_FAILED(ValidateSectionIndex(m_pReferencedFileSectionIndices, m_pHeader->numReferencedFileSections));

    m_pDataItemSectionIndices = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numDataItemSections, DEFFILE_SECTION_INDEX, &hr);
    RETURN_IF_FAILED(ValidateSectionIndex(m_pDataItemSectionIndices, m_pHeader->numDataItemSections));

    RETURN_IF_FAILED(hr);
    return S_OK;
}

HRESULT
PriDescriptor::ValidateSectionIndex(_In_reads_opt_(indexCounts) const DEFFILE_SECTION_INDEX* pSectionIndexes, _In_ int indexCounts) const
{
    RETURN_HR_IF(E_INVALIDARG, (indexCounts < 0) || (indexCounts > DEFFILE_MAX_SECTION_COUNT));

    if (indexCounts > 0)
    {
        // We failed to get our array of sections, which means the file is corrupt
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), !pSectionIndexes);
        for (int i = 0; i < indexCounts; i++)
        {
            RETURN_HR_IF(E_INVALIDARG, (pSectionIndexes[i] < 0) || (pSectionIndexes[i] > DEFFILE_MAX_SECTION_COUNT));
        }
    }
    return S_OK;
}

HRESULT PriDescriptor::GetSchema(_In_ int index, _In_ bool fallbackToMap, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_pHeader->numSchemas - 1));

    const HierarchicalSchema* schema;
    HRESULT hr = m_pSections->GetSchemaSection(0, m_pSchemaSectionIndices[index], (HierarchicalSchema**)&schema);
    if ((hr == HRESULT_FROM_WIN32(ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_LOAD_UNLOAD_PRI_FILE)) && fallbackToMap)
    {
        const ResourceMapBase* mapForSchema;
        if (SUCCEEDED(GetResourceMap(index, &mapForSchema)))
        {
            *result = mapForSchema->GetSchema();
            return S_OK;
        }
    }
    RETURN_IF_FAILED(hr);

    *result = schema;
    return S_OK;
}

HRESULT PriDescriptor::GetResourceMap(_In_ int index, _Out_ const ResourceMapBase** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_pHeader->numResourceMaps - 1));

    RETURN_IF_FAILED(
        m_pSections->GetResourceMapSection(m_pSchemaCollection, 0, m_pResourceMapSectionIndices[index], (ResourceMapBase**)result));

    return S_OK;
}

HRESULT PriDescriptor::GetPrimaryResourceMap(_Out_ const ResourceMapBase** result) const
{
    *result = nullptr;

    if (m_pHeader->primaryResourceMap == BaseFile::SectionIndexNone)
    {
        return S_OK;
    }
    RETURN_IF_FAILED(m_pSections->GetResourceMapSection(m_pSchemaCollection, 0, m_pHeader->primaryResourceMap, (ResourceMapBase**)result));

    return S_OK;
}

HRESULT PriDescriptor::GetDecisionInfo(_In_ int index, _Out_ const DecisionInfoFileSection** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_pHeader->numDecisionInfos - 1));

    RETURN_IF_FAILED(m_pSections->GetDecisionInfoSection(0, m_pDecisionInfoSectionIndices[index], (DecisionInfoFileSection**)result));

    return S_OK;
}

HRESULT PriDescriptor::GetIncludedFiles(_Out_ const FileFileList** result) const
{
    *result = nullptr;

    if (m_pHeader->includedFilesSectionIndex == BaseFile::SectionIndexNone)
    {
        return S_OK;
    }
    RETURN_IF_FAILED(m_pSections->GetFileListSection(0, m_pHeader->includedFilesSectionIndex, (FileFileList**)result));

    return S_OK;
}

HRESULT PriDescriptor::GetReferencedFileSection(_In_ int index, _Out_ const FileFileList** result) const
{
    *result = nullptr;

    RETURN_HR_IF_EXPECTED(E_INVALIDARG, (index < 0) || (index > m_pHeader->numReferencedFileSections - 1));

    RETURN_IF_FAILED(m_pSections->GetFileListSection(0, m_pReferencedFileSectionIndices[index], (FileFileList**)result));

    return S_OK;
}

HRESULT PriDescriptor::GetDataItemSection(_In_ int index, _Out_ const FileDataItemsSection** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_pHeader->numDataItemSections - 1));

    RETURN_IF_FAILED(m_pSections->GetDataItemsSection(0, m_pDataItemSectionIndices[index], (FileDataItemsSection**)result));

    return S_OK;
}

HRESULT PriDescriptor::GetTargetOsVersion(
    _In_ CoreProfile* pProfile,
    _Inout_opt_ StringResult* pPlatformOut,
    _Inout_opt_ StringResult* pVersionOut) const
{
    if (m_pParentFile != nullptr)
    {
        const DEFFILE_HEADER* pFileHeader = m_pParentFile->GetFileHeader();
        return const_cast<CoreProfile*>(pProfile)->GetTargetPlatformAndVersionForFileMagic(pFileHeader->magic, pPlatformOut, pVersionOut);
    }
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFile::CreateInstance(_In_ const IMrmFile* pFile, _Outptr_ const PriFile** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, pFile == nullptr);

    AutoDeletePtr<PriFile> pRtrn = new PriFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->InitPriFile(pFile, nullptr, nullptr));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT PriFile::CreateInstance(_In_ const IMrmFile* pFile, _In_ IUnifiedResourceView* pView, _Outptr_ const PriFile** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pFile == nullptr) || (pView == nullptr));

    AutoDeletePtr<PriFile> pRtrn = new PriFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->InitPriFile(pFile, pView, nullptr));

    *result = pRtrn.Detach();

    return S_OK;
}

PriFile::PriFile() : m_pDescriptor(nullptr), m_pFile(nullptr), m_pView(nullptr) {}

HRESULT
PriFile::InitPriFile(_In_ const IMrmFile* pFile, _In_opt_ IUnifiedResourceView* pView, _In_opt_ const ISchemaCollection* pOverrideSchema)
{
    RETURN_HR_IF(E_INVALIDARG, pFile == nullptr);

    m_pFile = pFile;
    m_pView = pView;

    const BaseFile* basefile;
    RETURN_IF_FAILED(m_pFile->GetBaseFile(&basefile));

    // Check file magic number
    if (m_pView != nullptr)
    {
        // If the view has no profile then assume it accepts anything.
        if (m_pView->GetProfile() != nullptr)
        {
            const DEFFILE_HEADER* pHeader = basefile->GetFileHeader();

            if (!m_pView->GetProfile()->IsSupportedFileMagicNumber(pHeader->magic))
            {
                return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
            }
        }
    }

    BaseFile::SectionIndex headerSectionIndex = basefile->GetFirstSectionIndex(gPriDescriptorExSectionType);
    if (headerSectionIndex < 0)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    RETURN_IF_FAILED(m_pFile->GetPriDescriptorSection(
        pOverrideSchema != nullptr ? pOverrideSchema : pView, headerSectionIndex, (PriDescriptor**)&m_pDescriptor));

    RETURN_HR_IF_NULL(E_FAIL, m_pDescriptor);

    return S_OK;
}

PriFile::~PriFile() {}

void PriFile::SetPackageRoot(_In_ PCWSTR /* pPackageRoot */) {}

AtomPoolGroup* PriFile::GetAtoms() const { return m_pView ? m_pView->GetAtoms() : NULL; }

UnifiedEnvironment* PriFile::GetUnifiedEnvironment() const { return m_pView ? m_pView->GetUnifiedEnvironment() : NULL; }

UnifiedDecisionInfo* PriFile::GetDefaultDecisionInfo() const { return m_pView ? m_pView->GetDefaultDecisionInfo() : NULL; }

HRESULT PriFile::GetFileDefaultEnvironment(
    _Inout_opt_ StringResult* fileEnvironmentName,
    _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const
{
    const IMrmFile* baseMrmFile = GetBaseMrmFile();

    if (baseMrmFile != nullptr)
    {
        RETURN_IF_FAILED(baseMrmFile->GetFileDefaultEnvironment(0, fileEnvironmentName, fileEnvironmentVersion));
    }
    else
    {
        const CoreProfile* profile = GetProfile();
        const BaseFile* baseFile;
        RETURN_IF_FAILED(GetBaseFile(&baseFile));
        const DEFFILE_HEADER* header = ((baseFile != nullptr) ? baseFile->GetFileHeader() : nullptr);

        if ((profile == nullptr) || (header == nullptr))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        RETURN_IF_FAILED(profile->GetDefaultEnvironmentForFileMagic(header->magic, fileEnvironmentName, fileEnvironmentVersion));
    }

    return S_OK;
}

HRESULT PriFile::GetBaseFile(_Out_ const BaseFile** result) const
{
    *result = nullptr;
    if (m_pFile != nullptr)
    {
        RETURN_IF_FAILED(m_pFile->GetBaseFile(result));
    }
    return S_OK;
}

int PriFile::GetNumSchemas() const { return (m_pDescriptor ? m_pDescriptor->GetNumSchemas() : 0); }

HRESULT PriFile::GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    // fail gracefully if m_pDescriptor is NULL
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pDescriptor);

    _Analysis_assume_(m_pDescriptor != nullptr);

    RETURN_IF_FAILED(m_pDescriptor->GetSchema(index, true, result));

    return S_OK;
}

HRESULT PriFile::GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    // fail gracefully if m_pDescriptor is NULL
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pDescriptor);

    _Analysis_assume_(m_pDescriptor != nullptr);

    const ResourceMapBase* pMap;
    RETURN_IF_FAILED(m_pDescriptor->GetPrimaryResourceMap(&pMap));

    if (pMap != nullptr)
    {
        *result = pMap->GetSchema();
    }
    return S_OK;
}

HRESULT PriFile::GetSchemaById(_In_ PCWSTR pSchemaId, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    const IHierarchicalSchema* pSchema = nullptr;
    int numSchemas = 0;

    numSchemas = GetNumSchemas();

    for (int i = 0; i < numSchemas; i++)
    {
        (void)m_pDescriptor->GetSchema(i, true, &pSchema);
        if ((pSchema != nullptr) && (DefString_ICompare(pSchema->GetSimpleId(), pSchemaId) == Def_Equal))
        {
            *result = pSchema;
            return S_OK;
        }
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFile::FindSchema(_In_ const HierarchicalSchemaReference* pRef, _Out_ const IHierarchicalSchema** ppSchemaOut) const
{
    *ppSchemaOut = nullptr;

    const IHierarchicalSchema* pBest = nullptr;
    const IHierarchicalSchema* pSchema = nullptr;
    int numSchemas = GetNumSchemas();

    for (int i = 0; i < numSchemas; i++)
    {
        (void)m_pDescriptor->GetSchema(i, false, &pSchema);
        if (pSchema != nullptr)
        {
            if (pRef->CheckIsIdentical(pSchema))
            {
                // can't get better than identical
                pBest = pSchema;
                break;
            }

            if (pRef->CheckIsCompatible(pSchema))
            {
                // If we can't get an identical match, the latest version is second-best.
                // e.g. if we're looking for 1.1, 1.3 is better than 1.2.
                if ((pBest == nullptr) || (pSchema->GetMinorVersion() > pBest->GetMinorVersion()))
                {
                    pBest = pSchema;
                }
            }
        }
    }

    if (pBest != nullptr)
    {

        *ppSchemaOut = pBest;
        return S_OK;
    }
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

int PriFile::GetNumResourceMaps() const { return (m_pDescriptor ? m_pDescriptor->GetNumResourceMaps() : 0); }

HRESULT PriFile::GetResourceMap(_In_ int index, _Out_ const IResourceMapBase** result) const
{
    *result = nullptr;

    // fail gracefully if m_pDescriptor is NULL
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pDescriptor);

    const ResourceMapBase* map;
    RETURN_IF_FAILED(m_pDescriptor->GetResourceMap(index, &map));

    *result = map;
    return S_OK;
}

HRESULT PriFile::GetPrimaryResourceMap(_Out_ const IResourceMapBase** result) const
{
    *result = nullptr;

    // fail gracefully if m_pDescriptor is NULL
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pDescriptor);

    const ResourceMapBase* map;
    RETURN_IF_FAILED(m_pDescriptor->GetPrimaryResourceMap(&map));

    *result = map;
    return S_OK;
}

HRESULT PriFile::GetResourceMapById(_In_ PCWSTR pSchemaId, _Out_ const IResourceMapBase** result) const
{
    *result = nullptr;

    const ResourceMapBase* pMap = NULL;
    int numMaps = 0;

    numMaps = GetNumResourceMaps();

    for (int i = 0; i < numMaps; i++)
    {
        (void)m_pDescriptor->GetResourceMap(i, &pMap);
        if ((pMap != NULL) && (DefString_ICompare(pMap->GetSchema()->GetSimpleId(), pSchemaId) == Def_Equal))
        {
            *result = pMap;
            return S_OK;
        }
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

bool PriFile::TryFindResourceMap(_In_ const HierarchicalSchemaReference* pRef, __deref_opt_out_opt const IResourceMapBase** ppMapOut) const
{
    const ResourceMapBase* pMap = NULL;
    int numMaps = 0;
    const ResourceMapBase* pBest = NULL;

    if (ppMapOut != NULL)
    {
        *ppMapOut = NULL;
    }

    numMaps = GetNumResourceMaps();

    for (int i = 0; i < numMaps; i++)
    {
        (void)m_pDescriptor->GetResourceMap(i, &pMap);
        if (pMap != NULL)
        {
            if (pRef->CheckIsIdentical(pMap->GetSchema()))
            {
                pBest = pMap;
                break; // can't get better than identical
            }

            if (pRef->CheckIsCompatible(pMap->GetSchema()))
            {
                if ((pBest == NULL) || (pMap->GetSchema()->GetMinorVersion() > pBest->GetSchema()->GetMinorVersion()))
                {
                    pBest = pMap;
                }
            }
        }
    }

    if (ppMapOut != NULL)
    {
        *ppMapOut = pBest;
    }

    return (pBest != NULL);
}

int PriFile::GetNumDecisionInfos() const { return (m_pDescriptor ? m_pDescriptor->GetNumDecisionInfos() : 0); }

HRESULT PriFile::GetDecisionInfo(_In_ int index, _Out_ const DecisionInfoFileSection** result) const
{
    *result = nullptr;

    // fail gracefully if m_pDescriptor is NULL
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pDescriptor);

    RETURN_IF_FAILED(m_pDescriptor->GetDecisionInfo(index, result));

    return S_OK;
}

HRESULT PriFile::GetFileList(_In_ int index, _Out_ const FileFileList** result) const
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pDescriptor);

    RETURN_IF_FAILED_WITH_EXPECTED(m_pDescriptor->GetReferencedFileSection(index, result), E_INVALIDARG);

    return S_OK;
}

bool PriFile::TryGetReverseFileMap(_Outptr_opt_ const ReverseFileMap** ppMapOut) const
{
    if (ppMapOut != nullptr)
    {
        *ppMapOut = nullptr;
    }

    if (m_pFile == nullptr)
    {
        return false;
    }

    const BaseFile* basefile;
    if (FAILED(m_pFile->GetBaseFile(&basefile)))
    {
        return false;
    }

    BaseFile::SectionIndex reverseMapSectionIndex = basefile->GetFirstSectionIndex(gReverseFileMapSectionType);
    if (reverseMapSectionIndex < 0)
    {
        return false;
    }

    ReverseFileMap* pReverseMap;
    (void)m_pFile->GetReverseFileMapSection(reverseMapSectionIndex, &pReverseMap);
    if (pReverseMap == nullptr)
    {
        return false;
    }

    if (ppMapOut != nullptr)
    {
        *ppMapOut = pReverseMap;
    }
    return true;
}

HRESULT
StandalonePriFile::CreateInstance(_In_ UINT32 flags, _In_ PCWSTR pFileName, _In_ CoreProfile* pProfile, _Outptr_ StandalonePriFile** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFileName));

    AutoDeletePtr<StandalonePriFile> pRtrn = new StandalonePriFile();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pProfile, nullptr, flags, pFileName));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT StandalonePriFile::CreateInstance(
    _In_ UINT32 flags,
    _In_ PCWSTR pFileName,
    _In_ CoreProfile* pProfile,
    _In_ const ISchemaCollection* overrideSchemas,
    _Outptr_ StandalonePriFile** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFileName));

    AutoDeletePtr<StandalonePriFile> pRtrn = new StandalonePriFile();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pProfile, overrideSchemas, flags, pFileName));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT StandalonePriFile::CreateInstance(
    _In_ UINT32 flags,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ size_t cbData,
    _In_ CoreProfile* pProfile,
    _Outptr_ StandalonePriFile** result)
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pData);

    AutoDeletePtr<StandalonePriFile> pRtrn = new StandalonePriFile();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pProfile, nullptr, flags, pData, cbData));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT StandalonePriFile::CreateInstance(
    _In_ UINT32 flags,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ size_t cbData,
    _In_ CoreProfile* pProfile,
    _In_ const ISchemaCollection* overrideSchemas,
    _Outptr_ StandalonePriFile** result)
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pData);

    AutoDeletePtr<StandalonePriFile> pRtrn = new StandalonePriFile();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pProfile, overrideSchemas, flags, pData, cbData));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT
StandalonePriFile::Init(_In_ CoreProfile* pProfile, _In_ const ISchemaCollection* overrideSchemas, _In_ UINT32 flags, _In_ PCWSTR pFileName)
{
    m_pProfile = pProfile;
    m_overrideSchemas = nullptr;

    RETURN_IF_FAILED(InitEnvironmentAndDecisions());
    RETURN_IF_FAILED(MrmFile::Init(m_pEnvironment, flags, pFileName));
    RETURN_IF_FAILED(InitStandalonePriFile(overrideSchemas));

    return S_OK;
}

HRESULT StandalonePriFile::Init(
    _In_ CoreProfile* pProfile,
    _In_ const ISchemaCollection* overrideSchemas,
    _In_ UINT32 flags,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ size_t cbData)
{
    m_pProfile = pProfile;
    m_overrideSchemas = nullptr;

    RETURN_IF_FAILED(InitEnvironmentAndDecisions());
    RETURN_IF_FAILED(MrmFile::Init(m_pEnvironment, flags, pData, cbData));
    RETURN_IF_FAILED(InitStandalonePriFile(overrideSchemas));

    return S_OK;
}

HRESULT StandalonePriFile::InitEnvironmentAndDecisions()
{
    RETURN_HR_IF(E_DEF_ALREADY_INITIALIZED, m_pAtoms != nullptr);

    RETURN_IF_FAILED(AtomPoolGroup::CreateInstance(4, &m_pAtoms));

    RETURN_IF_FAILED(UnifiedEnvironment::CreateInstance(m_pProfile, m_pAtoms, &m_pEnvironment));

    RETURN_IF_FAILED(UnifiedDecisionInfo::CreateInstance(m_pEnvironment, nullptr, &m_pDecisions));

    return S_OK;
}

HRESULT StandalonePriFile::GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    if (m_overrideSchemas != nullptr)
    {
        return m_overrideSchemas->GetSchema(index, result);
    }
    else
    {
        return PriFile::GetSchema(index, result);
    }
}

HRESULT StandalonePriFile::GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const
{
    if (m_overrideSchemas != nullptr)
    {
        return m_overrideSchemas->GetPrimarySchema(result);
    }
    else
    {
        return PriFile::GetPrimarySchema(result);
    }
}

HRESULT StandalonePriFile::GetSchemaById(_In_ PCWSTR pSchemaId, _Out_ const IHierarchicalSchema** result) const
{
    if (m_overrideSchemas != nullptr)
    {
        return m_overrideSchemas->GetSchemaById(pSchemaId, result);
    }
    else
    {
        return PriFile::GetSchemaById(pSchemaId, result);
    }
}

HRESULT StandalonePriFile::InitStandalonePriFile(_In_opt_ const ISchemaCollection* overrideSchemas)
{
    m_overrideSchemas = overrideSchemas;

    RETURN_IF_FAILED(PriFile::InitPriFile(this, this, m_overrideSchemas));

    for (int i = 0; i < GetNumSchemas(); i++)
    {
        if (m_overrideSchemas != nullptr)
        {
            const IHierarchicalSchema* pSchema;
            RETURN_IF_FAILED(m_overrideSchemas->GetSchema(i, &pSchema));

            // Clone pools to ensure proper pool bookkeeping.
            AutoDeletePtr<IAtomPool> newScopeNames;
            RETURN_IF_FAILED(pSchema->GetScopeNames()->Clone(&newScopeNames));

            RETURN_IF_FAILED(m_pAtoms->AddAtomPool(newScopeNames, true));
            newScopeNames.Detach();

            AutoDeletePtr<IAtomPool> newItemNames;
            RETURN_IF_FAILED(pSchema->GetItemNames()->Clone(&newItemNames));

            RETURN_IF_FAILED(m_pAtoms->AddAtomPool(newItemNames, true));
            newItemNames.Detach();
        }
        else
        {
            const IHierarchicalSchema* pSchema;
            RETURN_IF_FAILED(GetSchema(i, &pSchema));
            RETURN_IF_FAILED(m_pAtoms->AddAtomPool(pSchema->GetScopeNames(), false));
            RETURN_IF_FAILED(m_pAtoms->AddAtomPool(pSchema->GetItemNames(), false));
        }
    }

    for (int i = 0; i < GetNumDecisionInfos(); i++)
    {
        const DecisionInfoFileSection* pDecisions;
        RETURN_IF_FAILED(GetDecisionInfo(i, &pDecisions));
        RETURN_IF_FAILED(m_pDecisions->Merge(pDecisions, nullptr, nullptr, nullptr));
    }

    return S_OK;
}

StandalonePriFile::~StandalonePriFile()
{
    delete m_pDecisions;
    delete m_pEnvironment;
    delete m_pAtoms;

    m_pDecisions = nullptr;
    m_pEnvironment = nullptr;
    m_pAtoms = nullptr;
}

} // namespace Microsoft::Resources