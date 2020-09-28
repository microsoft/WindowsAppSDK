// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

class ResourceMapFileData : public IRawResourceMap
{
public:
    static HRESULT CreateInstance(
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_ const IFileSectionResolver* pSections,
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ UINT32 cbData,
        _Outptr_ ResourceMapFileData** result)
    {
        *result = nullptr;
        RETURN_HR_IF_EXPECTED(E_INVALIDARG, (pSections == nullptr) || (pData == nullptr));

        AutoDeletePtr<ResourceMapFileData> pRtrn = new ResourceMapFileData(pSections);
        RETURN_IF_NULL_ALLOC(pRtrn);
        RETURN_IF_FAILED(pRtrn->Init(sectionType, pSchemaCollection, pData, cbData));

        *result = pRtrn.Detach();

        return S_OK;
    }

    virtual ~ResourceMapFileData()
    {
        delete m_pInternalData;

        m_pInternalData = nullptr;

        if (m_ppEnvironmentRefs != nullptr)
        {
            for (int i = 0; i < m_pHeader->numEnvironmentRefs; i++)
            {
                delete m_ppEnvironmentRefs[i];
                m_ppEnvironmentRefs[i] = nullptr;
            }

            Def_Free(m_ppEnvironmentRefs);
            m_ppEnvironmentRefs = nullptr;
        }

        delete m_pOverrideDecisionMap;
        m_pOverrideDecisionMap = nullptr;
    }

    const IHierarchicalSchema* GetSchema() const { return (m_pOverrideSchema ? m_pOverrideSchema : m_pSchema); }
    const IHierarchicalSchema* GetOriginalSchema() const { return m_pSchema; }
    const IDecisionInfo* GetDecisionInfo() const { return (m_pOverrideDecisionInfo ? m_pOverrideDecisionInfo : m_pDecisionInfo); }

    HRESULT SetPackageRootPath(_In_ PCWSTR pPath) const
    {
        RETURN_IF_FAILED(m_packageRootPath.SetCopy(pPath));
        RETURN_IF_FAILED(m_packageRootPath.GetLength(&m_cchPackageRootPath));
        return S_OK;
    }

    PCWSTR GetPackageRootPath() const { return m_packageRootPath.GetRef(); }

    int GetNumEnvironments() const { return m_pHeader->numEnvironmentRefs; }

    HRESULT GetEnvironmentRef(_In_ int index, _Out_ const EnvironmentReference** result) const
    {
        *result = nullptr;

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index > GetNumEnvironments() - 1));

        *result = m_ppEnvironmentRefs[index];
        return S_OK;
    }

    int GetTotalNumResourceValues() const { return m_pHeader->numValues; }
    bool IsValidResourceValueIndex(_In_ int index) const { return ((index >= 0) && (index < m_pHeader->numValues)); }

    int GetNumResourceValueTypes() const { return m_pHeader->numResourceValueTypes; }
    bool IsValidResourceValueTypeOffset(_In_ int index) const { return ((index >= 0) && (index < m_pHeader->numResourceValueTypes)); }

    HRESULT GetDecision(_In_ int index, _Inout_ DecisionResult* pDecisionOut) const
    {
        return GetDecisionInfo()->GetDecision(index, pDecisionOut);
    }

    int GetNumResources() const { return m_pSchema->GetNumItems(); }

    int GetNumDirEntries() const { return m_pHeader->numDirEntries + (m_pLargeHeader ? m_pLargeHeader->numDirEntries : 0); }
    int GetNumRanges() const { return m_pHeader->numRanges + (m_pLargeHeader ? m_pLargeHeader->numRanges : 0); }
    int GetNumItems() const { return m_pHeader->numItems + (m_pLargeHeader ? m_pLargeHeader->numItems : 0); }

    void GetDirEntry(_In_ int index, _Out_ MRMFILE_MAP_DIR_ENTRY_LARGE* pEntryOut) const
    {
        DEF_ASSERT(index < GetNumDirEntries());

        if (index < m_pHeader->numDirEntries)
        {
            pEntryOut->itemIndex = m_pStandardDir[index].itemIndex;
            pEntryOut->rangeOrItemOffset = m_pStandardDir[index].rangeOrItemOffset;
        }
        else
        {
            *pEntryOut = m_pLargeDir[index - m_pHeader->numDirEntries];
        }
    }

    void GetRange(_In_ int index, _Out_ MRMFILE_MAP_RANGE_LARGE* pRangeOut) const
    {
        DEF_ASSERT(index < GetNumRanges());

        if (index < m_pHeader->numRanges)
        {
            pRangeOut->firstItemOffset = m_pStandardRanges[index].firstItemOffset;
            pRangeOut->numItems = m_pStandardRanges[index].numItems;
        }
        else
        {
            *pRangeOut = m_pLargeRanges[index - m_pHeader->numRanges];
        }
    }

    void GetItem(_In_ int index, _Out_ MRMFILE_MAP_ITEM_LARGE* pItemOut) const
    {
        DEF_ASSERT(index < GetNumItems());

        if (index < m_pHeader->numItems)
        {
            pItemOut->decisionIndex = m_pStandardItems[index].decisionIndex;
            pItemOut->firstCandidateValueOffset = m_pStandardItems[index].firstCandidateValueOffset;
            pItemOut->pad = 0;
        }
        else
        {
            *pItemOut = m_pLargeItems[index - m_pHeader->numItems];
        }
    }

    HRESULT GetRawResourceInfo(_In_ int resourceIndexInSchema, _Out_ int* pDecisionIndexOut, _Out_ int* pFirstCandidateIndexOut) const
    {
        const IHierarchicalSchema* pEffectiveSchema = (m_pOverrideSchema ? m_pOverrideSchema : m_pSchema);

        RETURN_HR_IF_EXPECTED(
            HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND),
            (resourceIndexInSchema < 0) || (resourceIndexInSchema > pEffectiveSchema->GetNumItems() - 1));

        RETURN_HR_IF_EXPECTED(E_INVALIDARG, (pDecisionIndexOut == nullptr) || (pFirstCandidateIndexOut == nullptr));

        int itemOffset = -1;
        MRMFILE_MAP_ITEM_LARGE item = {0};

        // If we have an override schema and this item's index is above our original
        // schema, don't bother looking for a match.
        if ((m_pOverrideSchema == nullptr) || (resourceIndexInSchema < m_pSchema->GetNumItems()))
        {

            // Search for an entry in the directory that matches our
            // schema item index.   Linear for now but can move to a
            // binary search if necessary.
            MRMFILE_MAP_DIR_ENTRY_LARGE dir;

            for (int iDir = 0; iDir < GetNumDirEntries(); iDir++)
            {
                GetDirEntry(iDir, &dir);
                if (dir.itemIndex <= resourceIndexInSchema)
                {
                    int offset = dir.rangeOrItemOffset;
                    if (offset < GetNumRanges())
                    {
                        // offset < numRanges means the dir entry refers
                        // to a range.
                        // See if our item is in it.  We know
                        // that resourceIndexInSchema is greater than
                        // the start of the range, so just test against
                        // the end.
                        MRMFILE_MAP_RANGE_LARGE range;
                        GetRange(offset, &range);
                        if (resourceIndexInSchema < (dir.itemIndex + range.numItems))
                        {
                            itemOffset = range.firstItemOffset + (resourceIndexInSchema - dir.itemIndex);
                            if (itemOffset >= GetNumItems())
                            {
                                // range refers to an item that's out of range
                                // file/data is damaged
                                return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
                            }
                            GetItem(itemOffset, &item);
                            break; // found our range. stop.
                        }
                    }
                    else if (dir.itemIndex == static_cast<UINT32>(resourceIndexInSchema))
                    {
                        // Index >= numRanges means the dir entry refers
                        // to an item, in which case the itemIndex in the
                        // directory must match exactly.  Subtract number
                        // of ranges to get the item offset.
                        itemOffset = offset - GetNumRanges();
                        if (itemOffset >= GetNumItems())
                        {
                            // dir entry refers to an item that's out of range
                            // file/data is damaged.
                            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
                        }
                        GetItem(itemOffset, &item);
                        break; // found our item.  stop.
                    }
                }
                else
                {
                    break;
                }
            }
        }

        if (pDecisionIndexOut != nullptr)
        {
            if (itemOffset >= 0)
            {
                UINT16 decisionIndex = item.decisionIndex;
                if (m_pOverrideDecisionInfo)
                {
                    UINT16 remap = -1;
                    if (m_pOverrideDecisionMap && m_pOverrideDecisionMap->TryGetMapping(decisionIndex, &remap))
                    {
                        decisionIndex = remap;
                    }
                }
                *pDecisionIndexOut = decisionIndex;
            }
            else
            {
                *pDecisionIndexOut = -1;
            }
        }

        if (pFirstCandidateIndexOut != nullptr)
        {
            *pFirstCandidateIndexOut = (itemOffset >= 0 ? item.firstCandidateValueOffset : -1);
        }

        return S_OK;
    }

    HRESULT GetRawValueInfo(
        _In_ int valueIndex,
        _Out_opt_ MRMFILE_MAP_VALUE_LOCATOR* pLocatorTypeOut,
        _Out_opt_ UINT32* pDataOut,
        _Out_opt_ UINT16* extraDataOut,
        _Out_opt_ UINT16* pDetailOut,
        _Out_opt_ MrmEnvironment::ResourceValueType* pValueTypeOut) const
    {
        if (!IsValidResourceValueIndex(valueIndex))
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }

        const MRMFILE_MAP_VALUE_LARGE* pValue;
        MRMFILE_MAP_VALUE_LARGE value = {};
        if (m_largeValues)
        {
            pValue = &m_pResourceValuesLarge[valueIndex];
        }
        else
        {
            memcpy(&value, &m_pResourceValues[valueIndex], sizeof(MRMFILE_MAP_VALUE));
            pValue = &value;
        }

        if (pLocatorTypeOut != nullptr)
        {
            *pLocatorTypeOut = pValue->valueLocatorType;
        }

        if (pDataOut != nullptr)
        {
            *pDataOut = (pValue->data2 << 16 | pValue->data1);
        }

        if (extraDataOut != nullptr)
        {
            *extraDataOut = pValue->data3;
        }

        if (pDetailOut != nullptr)
        {
            *pDetailOut = pValue->detail;
        }

        if (pValueTypeOut != nullptr)
        {
            if (!IsValidResourceValueTypeOffset(pValue->resourceValueTypeOffset))
            {
                // data is damaged
                return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
            }

            Atom typeAtom;
            typeAtom.Set(m_pResourceValueTypes[pValue->resourceValueTypeOffset]);
            *pValueTypeOut = MrmEnvironment::GetResourceValueTypeForAtom(typeAtom);
        }
        return S_OK;
    }

    HRESULT GetInternalData(_In_ UINT32 offset, _In_ UINT32 cbData, _Inout_ BlobResult* pDataOut) const
    {
        return m_pInternalData->GetDataRef(offset, cbData, pDataOut);
    }

    HRESULT GetReferenceDataAsBlob(_In_ UINT32 itemIndex, _In_ UINT16 sectionIndex, _In_ UINT16 detail, _Inout_ BlobResult* pDataOut) const
    {
        UINT16 fileIndex = detail;

        const FileDataItemsSection* pDataSection;
        RETURN_IF_FAILED(m_pSectionResolver->GetDataItemsSection(
            fileIndex, (BaseFile::SectionIndex)sectionIndex, (FileDataItemsSection**)&pDataSection));
        if (pDataSection != nullptr)
        {
            return pDataSection->GetItemDataRef(itemIndex, pDataOut);
        }

        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT GetInternalDataAsString(
        _In_ UINT32 offset,
        _In_ UINT32 cbData,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _Inout_ StringResult* pStringOut) const
    {
        BlobResult blob;

        RETURN_IF_FAILED(m_pInternalData->GetDataRef(offset, cbData, &blob));

        return GetDataAsString(&blob, valueType, 0, pStringOut);
    }

    HRESULT GetReferenceDataAsString(
        _In_ UINT32 itemIndex,
        _In_ UINT16 sectionIndex,
        _In_ UINT16 detail,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _Inout_ StringResult* pStringOut) const
    {
        UINT16 fileIndex = detail;

        const FileDataItemsSection* pDataSection;
        RETURN_IF_FAILED(m_pSectionResolver->GetDataItemsSection(
            fileIndex, (BaseFile::SectionIndex)sectionIndex, (FileDataItemsSection**)&pDataSection));
        if (pDataSection != nullptr)
        {
            BlobResult blob;
            RETURN_IF_FAILED(pDataSection->GetItemDataRef(itemIndex, &blob));

            // It prepend the file full path if the valueType is 'Path'
            return GetDataAsString(&blob, valueType, fileIndex, pStringOut);
        }

        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT SetDecisionInfoOverride(_In_ const IDecisionInfo* pOverrideDecisionInfo, _In_ const RemapUInt16* pOverrideDecisionMap) const
    {
        m_pOverrideDecisionInfo = pOverrideDecisionInfo;

        if (pOverrideDecisionMap != nullptr)
        {
            RETURN_IF_FAILED(RemapUInt16::CreateInstance(pOverrideDecisionMap, &m_pOverrideDecisionMap));
        }
        else
        {
            m_pOverrideDecisionMap = nullptr;
        }

        return S_OK;
    }

    void ResetDecisionInfoOverride() const
    {
        delete m_pOverrideDecisionMap;
        m_pOverrideDecisionInfo = nullptr;
        m_pOverrideDecisionMap = nullptr;
    }

    HRESULT SetSchemaOverride(_In_ const IHierarchicalSchema* pOverrideSchema) const
    {
        m_pOverrideSchema = pOverrideSchema;
        return S_OK;
    }

    HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pPathOut) const
    {
        return m_pSectionResolver->GetFilePath(fileIndex, pPathOut);
    }

    int GetNumFiles() const { return m_pSectionResolver->GetNumFiles(); }

    const IResourceLinks* GetLinks() const { return m_links; }
    void SetLinks(_In_ const IResourceLinks* links) { m_links = links; }

    bool TryGetResourceLinkForResourceIndex(
        _In_ UINT32 linksFromResourceIndex,
        _Out_ const IHierarchicalSchema** linksToSchema,
        _Out_ UINT32* linksToResourceIndex) const
    {
        return (
            (m_links != nullptr) ?
                m_links->TryGetResourceLinkForResourceIndex(linksFromResourceIndex, linksToSchema, linksToResourceIndex) :
                false);
    }

private:
    HRESULT GetDataAsString(
        _In_ BlobResult* pBlobResult,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ int fileIndex,
        _Inout_ StringResult* pStringOut) const
    {
        if (MrmEnvironment::IsBinaryResourceValueType(valueType))
        {
            // Can't get a string for embedded data
            return HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH);
        }

        if (!MrmEnvironment::IsPathResourceValueType(valueType) || m_packageRootPath.IsEmpty())
        {
            return GetStringResultFromBlobResult(pBlobResult, MrmEnvironment::MapResourceValueTypeToEncoding(valueType), pStringOut);
        }

        // It's a path, and we have a package root.  Prepare to concatenate.
        StringResult tmp;
        RETURN_IF_FAILED(GetStringResultFromBlobResult(pBlobResult, MrmEnvironment::MapResourceValueTypeToEncoding(valueType), &tmp));

        bool absolutePath;
        RETURN_IF_FAILED(tmp.IsAbsolutePath(&absolutePath));

        if (absolutePath)
        {
            // It's already absolute - just return it.
            return pStringOut->SetContentsFromOther(&tmp);
        }

        // Not absolute. Return our package root followed by the value from the map
        if (fileIndex == 0)
        {
            RETURN_IF_FAILED(pStringOut->SetRef(m_packageRootPath.GetRef()));
        }
        else
        {
            // GetFilePath set the referenced string rather than copy
            RETURN_IF_FAILED(m_pSectionResolver->GetAbsoluteFolderPath(fileIndex, pStringOut));
        }

        RETURN_IF_FAILED(pStringOut->ConcatPathElement(tmp.GetRef()));

        return S_OK;
    }

protected:
    const IHierarchicalSchema* m_pSchema;
    const IDecisionInfo* m_pDecisionInfo;

    mutable StringResult m_packageRootPath;
    mutable size_t m_cchPackageRootPath;

    mutable const IDecisionInfo* m_pOverrideDecisionInfo;
    mutable RemapUInt16* m_pOverrideDecisionMap;
    mutable const IHierarchicalSchema* m_pOverrideSchema;

    mutable const IResourceLinks* m_links;

    _Field_size_(1) const MRMFILE_RESOURCE_MAP_HEADER* m_pHeader;
    _Field_size_(m_pHeader->cbSchemaRef) const BYTE* m_pSchemaRefData;
    _Field_size_(m_pHeader->cbEnvironmentRefs) const BYTE* m_pEnvironmentRefData;
    _Field_size_(m_pHeader->numEnvironmentRefs) const MRMFILE_ENVIRONMENT_REF* m_pFileEnvironmentRefs;
    _Field_size_(m_pHeader->numResourceValueTypes) const DEF_ATOM* m_pResourceValueTypes;
    _Field_size_(m_pHeader->numDirEntries) const MRMFILE_MAP_DIR_ENTRY* m_pStandardDir;
    _Field_size_(m_pHeader->numRanges) const MRMFILE_MAP_RANGE* m_pStandardRanges;
    _Field_size_(m_pHeader->numItems) const MRMFILE_MAP_ITEM* m_pStandardItems;
    _Field_size_(m_pHeader->numValues) const MRMFILE_MAP_VALUE* m_pResourceValues;
    _Field_size_(m_pHeader->numValues) const MRMFILE_MAP_VALUE_LARGE* m_pResourceValuesLarge;

    _Field_size_(1) const MRMFILE_RESOURCE_MAP_HEADER_LARGE* m_pLargeHeader;
    _Field_size_(m_pLargeHeader->numDirEntries) const MRMFILE_MAP_DIR_ENTRY_LARGE* m_pLargeDir;
    _Field_size_(m_pLargeHeader->numRanges) const MRMFILE_MAP_RANGE_LARGE* m_pLargeRanges;
    _Field_size_(m_pLargeHeader->numItems) const MRMFILE_MAP_ITEM_LARGE* m_pLargeItems;

    const FileDataSection* m_pInternalData;
    const IFileSectionResolver* m_pSectionResolver;

    bool m_largeValues;

    _Field_size_(m_pHeader->numEnvironmentRefs) const EnvironmentReference** m_ppEnvironmentRefs;

    ResourceMapFileData(_In_ const IFileSectionResolver* pSections) :
        m_pSchema(nullptr),
        m_pDecisionInfo(nullptr),
        m_packageRootPath(),
        m_pHeader(nullptr),
        m_pEnvironmentRefData(nullptr),
        m_pFileEnvironmentRefs(nullptr),
        m_pResourceValueTypes(nullptr),
        m_pStandardDir(nullptr),
        m_pStandardRanges(nullptr),
        m_pStandardItems(nullptr),
        m_pResourceValues(nullptr),
        m_pResourceValuesLarge(nullptr),
        m_pLargeHeader(nullptr),
        m_pLargeDir(nullptr),
        m_pLargeRanges(nullptr),
        m_pLargeItems(nullptr),
        m_pInternalData(nullptr),
        m_ppEnvironmentRefs(nullptr),
        m_pOverrideDecisionInfo(nullptr),
        m_pOverrideDecisionMap(nullptr),
        m_pOverrideSchema(nullptr),
        m_pSectionResolver(pSections),
        m_links(nullptr),
        m_largeValues(false)
    {}

    HRESULT Init(
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ UINT32 cbData)
    {
        SectionParser data;
        RETURN_IF_FAILED(data.Set(pData, cbData));

        HRESULT hr = S_OK;
        m_pHeader = _SECTION_PARSER_NEXT(data, MRMFILE_RESOURCE_MAP_HEADER, &hr);
        if (m_pHeader == nullptr)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        // ResourceMap section _must_ have at least one environment ResourceMap2 must _not_ have environments.
        if (((m_pHeader->cbEnvironmentRefs > 0) != (m_pHeader->numEnvironmentRefs > 0)) ||
            ((m_pHeader->cbEnvironmentRefs > 0) != BaseFile::SectionTypesEqual(sectionType, gResourceMapSectionType)))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        if (m_pHeader->cbEnvironmentRefs > 0)
        {
            m_pEnvironmentRefData = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cbEnvironmentRefs, BYTE, &hr);
        }

        if (m_pHeader->cbSchemaRef > 0)
        {
            m_pSchemaRefData = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cbSchemaRef, BYTE, &hr);
        }

        m_pResourceValueTypes = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numResourceValueTypes, DEF_ATOM, &hr);
        m_pStandardDir = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numDirEntries, MRMFILE_MAP_DIR_ENTRY, &hr);
        m_pStandardRanges = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numRanges, MRMFILE_MAP_RANGE, &hr);
        m_pStandardItems = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numItems, MRMFILE_MAP_ITEM, &hr);

        if (m_pHeader->cbLargeItemData > 0)
        {
            const BYTE* pLargeData = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cbLargeItemData, BYTE, &hr);
            if (pLargeData == nullptr)
            {
                return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
            }

            SectionParser largeData;
            RETURN_IF_FAILED(largeData.Set(pLargeData, m_pHeader->cbLargeItemData));

            m_pLargeHeader = _SECTION_PARSER_NEXT(largeData, MRMFILE_RESOURCE_MAP_HEADER_LARGE, &hr);

            m_pLargeDir = _SECTION_PARSER_NEXT_ARRAY(largeData, m_pLargeHeader->numDirEntries, MRMFILE_MAP_DIR_ENTRY_LARGE, &hr);
            m_pLargeRanges = _SECTION_PARSER_NEXT_ARRAY(largeData, m_pLargeHeader->numRanges, MRMFILE_MAP_RANGE_LARGE, &hr);
            m_pLargeItems = _SECTION_PARSER_NEXT_ARRAY(largeData, m_pLargeHeader->numItems, MRMFILE_MAP_ITEM_LARGE, &hr);
        }

        m_largeValues = (m_pHeader->flags & MRMFILE_RESOURCE_MAP_BUILD_LARGE_VALUE);

        if (m_largeValues)
        {
            m_pResourceValuesLarge = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numValues, MRMFILE_MAP_VALUE_LARGE, &hr);
        }
        else
        {
            m_pResourceValues = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numValues, MRMFILE_MAP_VALUE, &hr);
        }
        const BYTE* pInternalData = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cbInternalValueData, BYTE, &hr);
        data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);

        RETURN_IF_FAILED(hr);

        if (m_pHeader->cbEnvironmentRefs > 0)
        {
            // get out our environments
            SectionParser envData;
            RETURN_IF_FAILED(envData.Set(m_pEnvironmentRefData, m_pHeader->cbEnvironmentRefs));
            m_pFileEnvironmentRefs = _SECTION_PARSER_NEXT_ARRAY(envData, m_pHeader->numEnvironmentRefs, MRMFILE_ENVIRONMENT_REF, &hr);
        }

        RETURN_IF_FAILED(hr);

        _Analysis_assume_(m_pFileEnvironmentRefs != nullptr);

        RETURN_IF_FAILED(
            FileDataSection::CreateInstance(pInternalData, m_pHeader->cbInternalValueData, (FileDataSection**)&m_pInternalData));

        if (m_pHeader->cbSchemaRef > 0)
        {
            AutoDeletePtr<HierarchicalSchemaReference> schemaReference;
            RETURN_IF_FAILED(HierarchicalSchemaReference::CreateInstance(m_pSchemaRefData, m_pHeader->cbSchemaRef, &schemaReference));

            if (pSchemaCollection == nullptr)
            {
                // There are initialization code paths that do not provide a schema collection.
                // These should never be used with schema reference files, and the caller needs to ensure that.
                return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
            }

            RETURN_IF_FAILED(pSchemaCollection->FindSchema(schemaReference, &m_pSchema));
        }
        else
        {
            HierarchicalSchema* schema;
            RETURN_IF_FAILED(m_pSectionResolver->GetSchemaSection(0, m_pHeader->schemaSectionIndex, &schema));
            m_pSchema = schema;
        }

        DecisionInfoFileSection* decisionInfo;
        RETURN_IF_FAILED(m_pSectionResolver->GetDecisionInfoSection(0, m_pHeader->decisionInfoSectionIndex, &decisionInfo));
        m_pDecisionInfo = decisionInfo;

        if (m_pHeader->numEnvironmentRefs > 0)
        {
            m_ppEnvironmentRefs = _DefArray_AllocZeroed(const EnvironmentReference*, m_pHeader->numEnvironmentRefs);
            RETURN_IF_NULL_ALLOC(m_ppEnvironmentRefs);

#pragma prefast(suppress : 26045, "Prefast doesn't detect that Array_AllocZeroed guarantees array size")
            for (int i = 0; i < m_pHeader->numEnvironmentRefs; i++)
            {
                RETURN_IF_FAILED(
                    EnvironmentReference::CreateInstance(&m_pFileEnvironmentRefs[i], (EnvironmentReference**)&m_ppEnvironmentRefs[i]));
            }
        }

        return S_OK;
    }
};

ResourceCandidateResult::ResourceCandidateResult() : m_pRawMap(nullptr) {}

void ResourceCandidateResult::Set(
    _In_ const IRawResourceMap* pRawMap,
    _In_ int valueGlobalIndex,
    _In_ int decisionIndex,
    _In_ int candidateIndexInDecision)
{
    m_pRawMap = pRawMap;
    m_valueGlobalIndex = valueGlobalIndex;
    m_decisionIndex = decisionIndex;
    m_candidateIndexInDecision = candidateIndexInDecision;
}

HRESULT ResourceCandidateResult::GetResourceValueType(_Out_ MrmEnvironment::ResourceValueType* pTypeOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRawMap);

    return m_pRawMap->GetRawValueInfo(m_valueGlobalIndex, nullptr, nullptr, nullptr, nullptr, pTypeOut);
}

HRESULT
ResourceCandidateResult::GetValueLocation(
    _Out_opt_ MRMFILE_MAP_VALUE_LOCATOR* pLocatorType,
    _Out_opt_ UINT32* pDataOut,
    _Out_opt_ UINT16* extraDataOut,
    _Out_opt_ UINT16* pDetailOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRawMap);

    return m_pRawMap->GetRawValueInfo(m_valueGlobalIndex, pLocatorType, pDataOut, extraDataOut, pDetailOut, nullptr);
}

bool ResourceCandidateResult::TryGetStringValue(_Inout_ StringResult* pStringOut) const
{
    MrmEnvironment::ResourceValueType valueType;
    MRMFILE_MAP_VALUE_LOCATOR locatorType;
    UINT32 data;
    UINT16 extraData;
    UINT16 detail;

    if (SUCCEEDED(m_pRawMap->GetRawValueInfo(m_valueGlobalIndex, &locatorType, &data, &extraData, &detail, &valueType)))
    {
        switch (locatorType)
        {
        case MRMFILE_MAP_VALUE_LOCATOR_INTERNAL:
            return SUCCEEDED(m_pRawMap->GetInternalDataAsString(data, detail, valueType, pStringOut));
        case MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM:
        {
            UINT32 itemIndex = ((extraData << 16) | (data & 0xffff));
            UINT16 sectionIndex = static_cast<UINT16>(data >> 16);
            return SUCCEEDED(m_pRawMap->GetReferenceDataAsString(itemIndex, sectionIndex, detail, valueType, pStringOut));
        }
        case MRMFILE_MAP_VALUE_LOCATOR_FILE_ITEM:
        default:
            break;
        }
    }
    return false;
}

HRESULT ResourceCandidateResult::GetSourceFileIndex(_Inout_ int* pIndexOut) const
{
    MRMFILE_MAP_VALUE_LOCATOR locatorType;
    UINT16 detail;

    RETURN_IF_FAILED(m_pRawMap->GetRawValueInfo(m_valueGlobalIndex, &locatorType, nullptr, nullptr, &detail, nullptr));

    switch (locatorType)
    {
    case MRMFILE_MAP_VALUE_LOCATOR_INTERNAL:
        *pIndexOut = 0; // Windows 8 format that has only single file
        return S_OK;
    case MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM:
        *pIndexOut = detail; // Windows 8.1 format that has fileIndex in the detal
        return S_OK;
    case MRMFILE_MAP_VALUE_LOCATOR_FILE_ITEM:
    default:
        return E_NOTIMPL;
    }
}

bool ResourceCandidateResult::TryGetBlobValue(_Inout_ BlobResult* pBlobOut) const
{
    MRMFILE_MAP_VALUE_LOCATOR locatorType;
    UINT32 data;
    UINT16 extraData;
    UINT16 detail;

    if (SUCCEEDED(m_pRawMap->GetRawValueInfo(m_valueGlobalIndex, &locatorType, &data, &extraData, &detail, nullptr)))
    {
        switch (locatorType)
        {
        case MRMFILE_MAP_VALUE_LOCATOR_INTERNAL:
            return SUCCEEDED(m_pRawMap->GetInternalData(data, detail, pBlobOut));
        case MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM:
        {
            UINT32 itemIndex = ((extraData << 16) | (data & 0xffff));
            UINT16 sectionIndex = static_cast<UINT16>(data >> 16);
            return SUCCEEDED(m_pRawMap->GetReferenceDataAsBlob(itemIndex, sectionIndex, detail, pBlobOut));
        }
        case MRMFILE_MAP_VALUE_LOCATOR_FILE_ITEM:
        default:
            break;
        }
    }
    return false;
}

HRESULT ResourceCandidateResult::GetQualifiers(_Inout_ QualifierSetResult* pQualifiersOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pRawMap);

    DecisionResult decision;
    RETURN_IF_FAILED(m_pRawMap->GetDecision(m_decisionIndex, &decision));

    return decision.GetQualifierSet(m_candidateIndexInDecision, pQualifiersOut);
}

NamedResourceResult::NamedResourceResult() :
    m_pRawMap(nullptr), m_resourceIndexInSchema(-1), m_decisionIndex(-1), m_firstCandidateGlobalIndex(-1), m_pSchema(nullptr)
{}

NamedResourceResult::~NamedResourceResult() {}

HRESULT
NamedResourceResult::Set(
    _In_ const IRawResourceMap* pRawMap,
    _In_ int resourceIndexInSchema,
    _In_ int decisionIndex,
    _In_ int firstCandidateGlobalIndex)
{
    m_pRawMap = pRawMap;
    m_resourceIndexInSchema = resourceIndexInSchema;
    m_decisionIndex = decisionIndex;
    m_firstCandidateGlobalIndex = firstCandidateGlobalIndex;
    m_pSchema = (pRawMap ? pRawMap->GetSchema() : nullptr);

    if (m_pRawMap != nullptr)
    {
        if (((resourceIndexInSchema < 0) || (resourceIndexInSchema >= pRawMap->GetSchema()->GetNumItems())) ||
            (decisionIndex >= pRawMap->GetDecisionInfo()->GetNumDecisions()))
        {
            // decisionIndex < 0 is valid
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
    }

    return S_OK;
}

HRESULT NamedResourceResult::Set(_In_ const IHierarchicalSchema* pSchema, _In_ int resourceIndexInSchema)
{
    m_pRawMap = nullptr;
    m_pSchema = pSchema;
    m_resourceIndexInSchema = resourceIndexInSchema;
    m_decisionIndex = IDecisionInfo::EmptyDecisionIndex;
    m_firstCandidateGlobalIndex = -1;

    if (m_pSchema != nullptr)
    {
        if ((resourceIndexInSchema < 0) || (resourceIndexInSchema >= m_pSchema->GetNumItems()))
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
    }
    return S_OK;
}

HRESULT NamedResourceResult::GetResourceName(_Out_ Atom* pNameOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pSchema);

    if (m_pSchema->GetItemNames()->TryGetAtom((Atom::Index)m_resourceIndexInSchema, pNameOut))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT NamedResourceResult::GetResourceName(_Inout_ StringResult* pNameOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pSchema);

    if (m_pSchema->GetItemNames()->TryGetString((Atom::Index)m_resourceIndexInSchema, pNameOut))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT NamedResourceResult::GetItemLocalName(_Inout_ StringResult* pNameOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pSchema);

    if (m_pSchema->TryGetItemLocalName((Atom::Index)m_resourceIndexInSchema, pNameOut))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT NamedResourceResult::GetDecision(_Inout_ DecisionResult* pDecisionOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pSchema);

    if (m_pRawMap == nullptr || m_decisionIndex < 0)
    {
        return pDecisionOut->SetToEmptyDecision(nullptr);
    }

    return m_pRawMap->GetDecision(m_decisionIndex, pDecisionOut);
}

int NamedResourceResult::GetNumCandidates() const
{
    if (m_pSchema == nullptr)
    {
        return -1;
    }

    if ((m_decisionIndex < 0) || (m_decisionIndex == IDecisionInfo::EmptyDecisionIndex))
    {
        // valid item but no candidates
        return 0;
    }

    DEF_ASSERT(m_pRawMap != nullptr);

    int numSets = 0;
    if (SUCCEEDED(m_pRawMap->GetDecisionInfo()->GetDecisionNumQualifierSets(m_decisionIndex, &numSets)))
    {
        return numSets;
    }

    return -1;
}

HRESULT NamedResourceResult::GetCandidate(_In_ int index, _Inout_ ResourceCandidateResult* pCandidateOut) const
{
    if (m_pRawMap == nullptr)
    {
        if (m_pSchema == nullptr)
        {
            return E_DEF_NOT_READY;
        }

        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    if ((index < 0) || (GetNumCandidates() <= index))
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    pCandidateOut->Set(m_pRawMap, m_firstCandidateGlobalIndex + index, m_decisionIndex, index);

    return S_OK;
}

bool NamedResourceResult::TryGetResourceLink(_Out_ const IHierarchicalSchema** linksToSchema, _Out_ UINT32* linksToResourceIndex) const
{
    if (m_pRawMap == nullptr)
    {
        return false;
    }

    return m_pRawMap->TryGetResourceLinkForResourceIndex(m_resourceIndexInSchema, linksToSchema, linksToResourceIndex);
}

ResourceMapSubtree::ResourceMapSubtree() :
    m_pFullMap(nullptr),
    m_pSchema(nullptr),
    m_scopeIndex(-1),
    m_numDescendentResources(-1),
    m_numDescendentScopes(-1),
    m_pDescendentResources(nullptr),
    m_pDescendentScopes(nullptr)
{}

ResourceMapSubtree::~ResourceMapSubtree()
{
    if (m_pDescendentResources != nullptr)
    {
        Def_Free(m_pDescendentResources);
        m_pDescendentResources = nullptr;
    }

    if (m_pDescendentScopes != nullptr)
    {
        Def_Free(m_pDescendentScopes);
        m_pDescendentScopes = nullptr;
    }
    m_numDescendentResources = -1;
    m_numDescendentScopes = -1;
}

HRESULT
ResourceMapSubtree::CreateInstance(_In_ const IResourceMapBase* pFullMap, _In_ int scopeIndex, _Outptr_ const ResourceMapSubtree** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL_EXPECTED(E_INVALIDARG, pFullMap);

    AutoDeletePtr<ResourceMapSubtree> pRtrn = new ResourceMapSubtree();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->InitResourceMapSubtree(pFullMap, scopeIndex));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ResourceMapSubtree::InitResourceMapSubtree(_In_ const IResourceMapBase* pFullMap, _In_ int scopeIndex)
{
    RETURN_HR_IF_NULL_EXPECTED(E_INVALIDARG, pFullMap);
    RETURN_HR_IF_EXPECTED(
        HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (scopeIndex < 0) || (scopeIndex > pFullMap->GetSchema()->GetNumScopes() - 1));

    m_pFullMap = pFullMap;
    m_pSchema = pFullMap->GetSchema();
    m_scopeIndex = scopeIndex;

    int numChildren = 0;

    RETURN_IF_FAILED(m_strResMapFullScopeName.SetCopy(m_pSchema->GetSimpleId()));
    RETURN_IF_FAILED(m_strResMapFullScopeName.Concat(L"/"));

    StringResult strResMapScopeName;
    if (m_pSchema->TryGetScopeInfo(m_scopeIndex, &strResMapScopeName, &numChildren))
    {
        RETURN_IF_FAILED(m_strResMapFullScopeName.Concat(strResMapScopeName.GetRef()));
    }
    m_initGeneration = m_pFullMap->GetCurrentGeneration();

    return S_OK;
}

PCWSTR ResourceMapSubtree::GetFullScopeName() const { return m_strResMapFullScopeName.GetRef(); }

int ResourceMapSubtree::GetNumChildren() const
{
    StringResult name;
    int numChildren = 0;

    if (m_pSchema->TryGetScopeInfo(m_scopeIndex, &name, &numChildren))
    {
        return numChildren;
    }
    return 0;
}

HRESULT ResourceMapSubtree::GetChildScopeSubtree(_In_ int childIndex, _Out_ const ResourceMapSubtree** result) const
{
    *result = nullptr;

    int childScopeIndex = -1;
    int childItemIndex = -1;

    if (m_pSchema->TryGetScopeChild(m_scopeIndex, childIndex, &childScopeIndex, &childItemIndex))
    {
        if (childScopeIndex < 0)
        {
            // child is an item, not a scope
            // Could return DEF_INVALID_OBJECT if we want to distinguish
            // mismatch from unknown scope.
            return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
        }

        return ResourceMapSubtree::CreateInstance(m_pFullMap, childScopeIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

HRESULT ResourceMapSubtree::GetChildName(_In_ int childIndex, _Inout_ StringResult* pNameOut) const
{
    if (m_pSchema->TryGetScopeChildName(m_scopeIndex, childIndex, pNameOut))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

bool ResourceMapSubtree::ChildIsScope(_In_ int childIndex) const
{
    int childScopeIndex = -1;
    int childItemIndex = -1;

    if (m_pSchema->TryGetScopeChild(m_scopeIndex, childIndex, &childScopeIndex, &childItemIndex))
    {
        return (childScopeIndex >= 0);
    }

    return false;
}

HRESULT ResourceMapSubtree::GetChildResource(_In_ int childIndex, _Inout_ NamedResourceResult* pResourceOut) const
{
    int childScopeIndex = -1;
    int childItemIndex = -1;

    if (m_pSchema->TryGetScopeChild(m_scopeIndex, childIndex, &childScopeIndex, &childItemIndex))
    {
        if (childItemIndex < 0)
        {
            // child is a scope not an item
            // Could return DEF_INVALID_OBJECT if we want to distinguish
            // mismatch from unknown item.
            return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
        }
        return m_pFullMap->GetResourceByIndex(childItemIndex, pResourceOut);
    }

    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

HRESULT ResourceMapSubtree::GetResource(_In_ PCWSTR pPath, _Inout_ NamedResourceResult* pResourceOut) const
{
    int schemaScopeIndex = -1;
    int schemaItemIndex = -1;

    RETURN_HR_IF_EXPECTED(E_INVALIDARG, (pPath == nullptr) || (*pPath == 0));

    if (!m_pSchema->Contains(pPath, m_scopeIndex, &schemaScopeIndex, &schemaItemIndex))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
    }

    if (schemaItemIndex < 0)
    {
        // Could return DEF_INVALID_OBJECT if we want to distinguish
        // mismatch from unknown item.
        return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
    }

    return m_pFullMap->GetResourceByIndex(schemaItemIndex, pResourceOut);
}

HRESULT ResourceMapSubtree::GetSubtree(_In_ PCWSTR pPath, _Out_ const ResourceMapSubtree** result) const
{
    *result = nullptr;

    int schemaScopeIndex = -1;
    int schemaItemIndex = -1;

    RETURN_HR_IF_EXPECTED(E_INVALIDARG, (pPath == nullptr) || (*pPath == 0));

    if (!m_pSchema->Contains(pPath, m_scopeIndex, &schemaScopeIndex, &schemaItemIndex))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    if (schemaScopeIndex < 0)
    {
        // Could return DEF_INVALID_OBJECT if we want to distinguish
        // mismatch from unknown item.
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    return ResourceMapSubtree::CreateInstance(m_pFullMap, schemaScopeIndex, result);
}

HRESULT ResourceMapSubtree::GetSubtreeByIndex(_In_ int indexInSchema, _Out_ const ResourceMapSubtree** result) const
{
    *result = nullptr;

    if (indexInSchema < 0)
    {
        // Could return DEF_INVALID_OBJECT if we want to distinguish
        // mismatch from unknown item.
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    return ResourceMapSubtree::CreateInstance(this->m_pFullMap, indexInSchema, result);
}

bool ResourceMapSubtree::CheckVersionIsCompatible(_In_ HierarchicalSchemaVersionInfo* wantVersion) const
{
    return Microsoft::Resources::CheckHierarchicalSchemaVersionIsCompatible(this->m_pSchema, wantVersion);
}

int ResourceMapSubtree::GetIndexInSchema() const { return this->m_scopeIndex; }

HRESULT ResourceMapSubtree::MoveToSubtree(_In_ PCWSTR pPath)
{
    int schemaScopeIndex = -1;
    int schemaItemIndex = -1;

    RETURN_HR_IF_EXPECTED(E_INVALIDARG, (pPath == nullptr) || (*pPath == 0));

    if (!m_pSchema->Contains(pPath, m_scopeIndex, &schemaScopeIndex, &schemaItemIndex))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    if (schemaScopeIndex < 0)
    {
        // Could return DEF_INVALID_OBJECT if we want to distinguish
        // mismatch from unknown item.
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    m_scopeIndex = schemaScopeIndex;
    return S_OK;
}

int ResourceMapSubtree::GetNumDescendentResources() const
{
    if (FAILED(GetOrUpdateDescendents()))
    {
        return -1;
    }

    return m_numDescendentResources;
}

HRESULT ResourceMapSubtree::GetDescendentResource(_In_ int index, _Inout_ NamedResourceResult* pItemOut) const
{
    RETURN_IF_FAILED(GetOrUpdateDescendents());

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index > m_numDescendentResources - 1));

    return m_pFullMap->GetResourceByIndex(m_pDescendentResources[index], pItemOut);
}

HRESULT ResourceMapSubtree::GetResourceNameBySchemaIndex(_In_ int indexInSchema, _Inout_ StringResult* pNameOut) const
{
    if (m_pSchema->GetItemNames()->TryGetString(indexInSchema, pNameOut))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
}

// Gets the name of the resource relative to this scope
HRESULT ResourceMapSubtree::GetDescendentResourceName(_In_ int index, _Inout_ StringResult* pNameOut) const
{
    RETURN_IF_FAILED(GetOrUpdateDescendents());

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index > m_numDescendentResources - 1));

    if (m_pSchema->TryGetRelativeItemName(m_scopeIndex, m_pDescendentResources[index], pNameOut))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
}

int ResourceMapSubtree::GetNumDescendentScopes() const
{
    if (FAILED(GetOrUpdateDescendents()))
    {
        return -1;
    }

    return m_numDescendentScopes;
}

HRESULT ResourceMapSubtree::GetDescendentScopeSubtree(_In_ int index, _Out_ const ResourceMapSubtree** result) const
{
    *result = nullptr;
    RETURN_IF_FAILED(GetOrUpdateDescendents());

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index > m_numDescendentScopes - 1));

    return ResourceMapSubtree::CreateInstance(m_pFullMap, m_pDescendentScopes[index], result);
}

// Gets the name of the descendent scope relative to this one
HRESULT ResourceMapSubtree::GetDescendentScopeName(_In_ int index, _Inout_ StringResult* pNameOut) const
{
    RETURN_IF_FAILED(GetOrUpdateDescendents());

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index > m_numDescendentScopes - 1));

    if (m_pSchema->TryGetRelativeScopeName(m_scopeIndex, m_pDescendentScopes[index], pNameOut))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
}

HRESULT ResourceMapSubtree::GetOrUpdateDescendentResources() const
{
    // set to zero to indicate that we've attempted to get the resources
    m_numDescendentResources = 0;

    int numResources = 0;
    RETURN_IF_FAILED(m_pSchema->GetNumDescendents(m_scopeIndex, nullptr, &numResources));

    if (numResources > 0)
    {
        if (m_pDescendentResources)
        {
            Def_Free(m_pDescendentResources);
            m_pDescendentResources = nullptr;
        }
        m_pDescendentResources = _DefArray_AllocZeroed(int, numResources);
        RETURN_IF_NULL_ALLOC(m_pDescendentResources);

        int numWritten = 0;
        RETURN_IF_FAILED(m_pSchema->GetDescendents(m_scopeIndex, 0, nullptr, nullptr, numResources, m_pDescendentResources, &numWritten));

        DEF_ASSERT(numWritten == numResources);
        m_numDescendentResources = numResources;
    }

    return S_OK;
}

HRESULT ResourceMapSubtree::GetOrUpdateDescendentScopes() const
{
    // set to zero to indicate that we've attempted to get the scopes
    m_numDescendentScopes = 0;

    int numScopes = 0;
    RETURN_IF_FAILED(m_pSchema->GetNumDescendents(m_scopeIndex, &numScopes, nullptr));

    if (numScopes > 0)
    {
        if (m_pDescendentScopes != nullptr)
        {
            Def_Free(m_pDescendentScopes);
            m_pDescendentScopes = nullptr;
        }
        m_pDescendentScopes = _DefArray_AllocZeroed(int, numScopes);
        RETURN_IF_NULL_ALLOC(m_pDescendentScopes);

        int numWritten = 0;
        RETURN_IF_FAILED(m_pSchema->GetDescendents(m_scopeIndex, numScopes, m_pDescendentScopes, &numWritten, 0, nullptr, nullptr));

        DEF_ASSERT(numWritten == numScopes);
        m_numDescendentScopes = numScopes;
    }
    return S_OK;
}

HRESULT ResourceMapSubtree::GetOrUpdateDescendents() const
{
    if (m_numDescendentResources < 0 || m_currentMinorVersion != m_pSchema->GetMinorVersion())
    {
        RETURN_IF_FAILED(GetOrUpdateDescendentResources());
    }

    if (m_numDescendentScopes < 0 || m_currentMinorVersion != m_pSchema->GetMinorVersion())
    {
        RETURN_IF_FAILED(GetOrUpdateDescendentScopes());
    }

    m_currentMinorVersion = m_pSchema->GetMinorVersion();
    return S_OK;
}

bool ResourceMapSubtree::IsValid() const
{
    if (m_initGeneration != m_pFullMap->GetCurrentGeneration())
    {
        return false;
    }

    return true;
}

HRESULT ResourceMapBase::CreateInstance(
    _In_ const IFileSectionResolver* pSections,
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ const IFileSection* const pSection,
    _Outptr_ ResourceMapBase** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL_EXPECTED(E_INVALIDARG, pSections);

    AutoDeletePtr<ResourceMapBase> pRtrn = new ResourceMapBase();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(
        pRtrn->Init(pSections, pSchemaCollection, pSection->GetSectionType(), pSection, pSection->GetData(), pSection->GetDataSize()));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ResourceMapBase::CreateInstance(
    _In_ const IFileSectionResolver* pSections,
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ const DEFFILE_SECTION_TYPEID& sectionType,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ int cbData,
    _Outptr_ ResourceMapBase** result)
{
    *result = nullptr;
    RETURN_HR_IF_EXPECTED(E_INVALIDARG, (pSections == nullptr) || (pData == nullptr));

    AutoDeletePtr<ResourceMapBase> pRtrn = new ResourceMapBase();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSections, pSchemaCollection, sectionType, nullptr, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ResourceMapBase::Init(
    _In_ const IFileSectionResolver* pSections,
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ const DEFFILE_SECTION_TYPEID& sectionType,
    _In_opt_ const IFileSection* const pSection,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ UINT32 cbData)
{
    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));

    RETURN_IF_FAILED(ResourceMapFileData::CreateInstance(sectionType, pSections, pSchemaCollection, pData, cbData, &m_pFileData));

    m_pSections = pSections;
    m_pSchema = m_pFileData->GetSchema();
    m_pDecisionInfo = m_pFileData->GetDecisionInfo();

    RETURN_IF_FAILED(InitResourceMapSubtree(this, 0));

    // We might have an associated links section
    int linkSectionIndex = 0;

    while (pSections->TryGetSectionIndexByType(gResourceLinkSectionType, 0, linkSectionIndex, &linkSectionIndex))
    {
        const ResourceLinkSection* links;
        RETURN_IF_FAILED(
            pSections->GetResourceLinkSection(pSchemaCollection, 0, static_cast<BaseFile::SectionIndex>(linkSectionIndex), &links));

        if (links->GetSchema() == m_pSchema)
        {
            m_links = links;
            m_pFileData->SetLinks(links);
            break;
        }
        linkSectionIndex++;
    }

    return S_OK;
}

ResourceMapBase::~ResourceMapBase()
{
    delete m_pFileData;

    m_pFileData = nullptr;
}

HRESULT ResourceMapBase::SetPackageRootPath(_In_ PCWSTR pPath) const { return m_pFileData->SetPackageRootPath(pPath); }

PCWSTR ResourceMapBase::GetPackageRootPath() const { return m_pFileData->GetPackageRootPath(); }

const IDecisionInfo* ResourceMapBase::GetDecisionInfo() const { return m_pFileData->GetDecisionInfo(); }

const IHierarchicalSchema* ResourceMapBase::GetSchema() const { return m_pFileData->GetSchema(); }

const IHierarchicalSchema* ResourceMapBase::GetOriginalSchema() const { return m_pFileData->GetOriginalSchema(); }

int ResourceMapBase::GetNumResources() const { return m_pFileData->GetNumResources(); }

HRESULT ResourceMapBase::GetResourceByIndex(_In_ int resourceIndexInSchema, _Inout_ NamedResourceResult* pResourceOut) const
{
    int decisionIndex = -1;
    int firstCandidateIndex = -1;

    RETURN_IF_FAILED(m_pFileData->GetRawResourceInfo(resourceIndexInSchema, &decisionIndex, &firstCandidateIndex));

    RETURN_IF_FAILED(pResourceOut->Set(m_pFileData, resourceIndexInSchema, decisionIndex, firstCandidateIndex));

    return S_OK;
}

int ResourceMapBase::GetTotalNumResourceValues() const { return m_pFileData->GetTotalNumResourceValues(); }

HRESULT ResourceMapBase::GetResource(_In_ PCWSTR pPath, _Inout_ NamedResourceResult* pResourceOut) const
{
    int schemaScopeIndex = -1;
    int schemaItemIndex = -1;

    RETURN_HR_IF_EXPECTED(E_INVALIDARG, (pPath == nullptr) || (*pPath == 0));

    if (!m_pSchema->Contains(pPath, 0, &schemaScopeIndex, &schemaItemIndex))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
    }

    if (schemaItemIndex < 0)
    {
        // Could return DEF_INVALID_OBJECT if we want to distinguish
        // mismatch from unknown item.
        return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
    }

    return GetResourceByIndex(schemaItemIndex, pResourceOut);
}

HRESULT ResourceMapBase::MoveToSubtree(_In_ PCWSTR) const { return E_NOTIMPL; }

HRESULT
ResourceMapBase::SetDecisionInfoOverride(_In_ const IDecisionInfo* pOverrideDecisions, _In_ const RemapUInt16* pOverrideDecisionMap) const
{
    return m_pFileData->SetDecisionInfoOverride(pOverrideDecisions, pOverrideDecisionMap);
}

void ResourceMapBase::ResetDecisionInfoOverride() const { m_pFileData->ResetDecisionInfoOverride(); }

HRESULT ResourceMapBase::SetSchemaOverride(_In_ const IHierarchicalSchema* pOverrideSchema) const
{
    return m_pFileData->SetSchemaOverride(pOverrideSchema);
}

HRESULT ResourceMapBase::SetLinks(_In_ const IResourceLinks* links)
{
    if (HaveLinks())
    {
        return E_DEF_ALREADY_INITIALIZED;
    }

    m_links = links;
    return S_OK;
}

// IResourceLinks implementation
int ResourceMapBase::GetNumReferencedSchemas() const { return (HaveLinks() ? m_links->GetNumReferencedSchemas() : 1); }

HRESULT ResourceMapBase::GetReferencedSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const
{
    if (HaveLinks())
    {
        return m_links->GetReferencedSchema(index, result);
    }

    if (index == 0)
    {
        *result = m_pSchema;
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

int ResourceMapBase::GetNumInternalLinks() const { return HaveLinks() ? m_links->GetNumInternalLinks() : 0; }

int ResourceMapBase::GetNumFullLinks() const { return HaveLinks() ? m_links->GetNumFullLinks() : 0; }

int ResourceMapBase::GetNumTotalLinks() const { return HaveLinks() ? m_links->GetNumTotalLinks() : 0; }

int ResourceMapBase::GetNumLinksByResourceIndex() const { return HaveLinks() ? m_links->GetNumLinksByResourceIndex() : 0; }

HRESULT ResourceMapBase::GetInternalResourceLink(
    _In_ UINT32 linkIndexInSection,
    _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
    _Out_opt_ UINT32* mapsToItemIndex) const
{
    if (HaveLinks())
    {
        return m_links->GetInternalResourceLink(linkIndexInSection, mapsToSchema, mapsToItemIndex);
    }

    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

HRESULT ResourceMapBase::GetFullResourceLink(
    _In_ UINT32 linkIndexInSection,
    _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
    _Out_opt_ UINT32* mapsToItemIndex) const
{
    if (HaveLinks())
    {
        return m_links->GetFullResourceLink(linkIndexInSection, mapsToSchema, mapsToItemIndex);
    }

    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

HRESULT ResourceMapBase::GetResourceLinkById(
    _In_ UINT32 linkIndexInSection,
    _In_ UINT32* linksFromResourceIndex,
    _Out_ const IHierarchicalSchema** mapsToSchema,
    _Out_ UINT32* linksToResourceIndex) const
{
    if (HaveLinks())
    {
        return m_links->GetResourceLinkById(linkIndexInSection, linksFromResourceIndex, mapsToSchema, linksToResourceIndex);
    }

    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

bool ResourceMapBase::TryGetResourceLinkForResourceIndex(
    _In_ UINT32 linksFromResourceIndex,
    _Out_ const IHierarchicalSchema** linksToSchema,
    _Out_ UINT32* linksToResourceIndex) const
{
    if (HaveLinks())
    {
        return m_links->TryGetResourceLinkForResourceIndex(linksFromResourceIndex, linksToSchema, linksToResourceIndex);
    }

    return false;
}

} // namespace Microsoft::Resources
