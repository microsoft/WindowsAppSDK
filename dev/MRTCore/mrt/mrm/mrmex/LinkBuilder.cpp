// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

class LinkBuilderFileData : public DefObject
{
public:
    LinkBuilderFileData() :
        m_header(nullptr),
        m_schemas(nullptr),
        m_schemaData(nullptr),
        m_internalLinks(nullptr),
        m_largeInternalLinks(nullptr),
        m_fullLinks(nullptr),
        m_largeFullLinks(nullptr),
        m_linksById(nullptr),
        m_largeLinksById(nullptr),
        m_totalSizeInBytes(0)
    {}

    HRESULT
    Init(_Out_writes_bytes_(bufferSizeInBytes) VOID* buffer, _In_ UINT32 bufferSizeInBytes, _In_ const MRMFILE_RESOURCE_LINK_HEADER& header)
    {
        SectionBuilderParser data;
        RETURN_IF_FAILED(data.Set(buffer, bufferSizeInBytes));

        HRESULT hr = S_OK;
        m_header = _SECTION_BUILDER_NEXT(data, MRMFILE_RESOURCE_LINK_HEADER, &hr);
        m_schemas = _SECTION_BUILDER_NEXT_ARRAY(data, header.numSchemas, MRMFILE_LINK_SCHEMA_MAP, &hr);
        m_schemaData = _SECTION_BUILDER_NEXT_ARRAY(data, header.schemaDataSizeInBytes, BYTE, &hr);

        data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);

        m_internalLinks = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumSmallInternalLinks(&header), UINT16, &hr);
        data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);
        m_largeInternalLinks = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumLargeInternalLinks(&header), UINT32, &hr);

        m_fullLinks = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumSmallFullLinks(&header), MRMFILE_FULL_LINK, &hr);
        m_largeFullLinks = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumLargeFullLinks(&header), MRMFILE_LARGE_FULL_LINK, &hr);

        m_linksById = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumSmallLinksById(&header), MRMFILE_LINK_BY_ID, &hr);
        m_largeLinksById = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumLargeLinksById(&header), MRMFILE_LARGE_LINK_BY_ID, &hr);

        m_totalSizeInBytes = static_cast<UINT32>(data.UsedBufferSizeInBytes());

        RETURN_IF_FAILED(hr);

        _Analysis_assume_(m_header != nullptr);
        *m_header = header;

        return S_OK;
    }

    static int GetNumSmallInternalLinks(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header) { return header->firstLargeInternalLink; }
    static int GetNumLargeInternalLinks(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header)
    {
        return header->numInternalLinks - header->firstLargeInternalLink;
    }
    static int GetNumTotalInternalLinks(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header) { return header->numInternalLinks; }

    static int GetNumSmallFullLinks(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header) { return header->firstLargeFullLink; }
    static int GetNumLargeFullLinks(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header)
    {
        return header->numFullLinks - header->firstLargeFullLink;
    }
    static int GetNumTotalFullLinks(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header) { return header->numFullLinks; }

    static int GetNumSmallLinksById(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header) { return header->firstLargeLinkById; }
    static int GetNumLargeLinksById(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header)
    {
        return header->numLinksById - header->firstLargeLinkById;
    }
    static int GetNumTotalLinksById(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header) { return header->numLinksById; }

    static int GetNumTotalLinks(_In_ const MRMFILE_RESOURCE_LINK_HEADER* header)
    {
        return GetNumTotalInternalLinks(header) + GetNumTotalFullLinks(header);
    }

    int GetNumSmallInternalLinks() const { return GetNumSmallInternalLinks(m_header); }
    int GetNumLargeInternalLinks() const { return GetNumLargeInternalLinks(m_header); }
    int GetNumTotalInternalLinks() const { return GetNumTotalInternalLinks(m_header); }

    int GetNumSmallFullLinks() const { return GetNumSmallFullLinks(m_header); }
    int GetNumLargeFullLinks() const { return GetNumLargeFullLinks(m_header); }
    int GetNumTotalFullLinks() const { return GetNumTotalFullLinks(m_header); }

    int GetNumSmallLinksById() const { return GetNumSmallLinksById(m_header); }
    int GetNumLargeLinksById() const { return GetNumLargeLinksById(m_header); }
    int GetNumTotalLinksById() const { return GetNumTotalLinksById(m_header); }

    int GetNumTotalLinks() const { return GetNumTotalLinks(m_header); }

    size_t GetTotalSizeInBytes() const { return m_totalSizeInBytes; }

    using DefObject::operator delete;

    ~LinkBuilderFileData() {}

    int GetNumSchemas() const { return m_header->numSchemas; }
    UINT16 GetSchemaDataSizeInBytes() const { return m_header->schemaDataSizeInBytes; }

    HRESULT WriteSchemaSectionIndex(_In_ UINT32 index, _In_ UINT32 sectionIndex)
    {
        if (sectionIndex == BaseFile::SectionIndexNone)
        {
            return E_DEF_NOT_READY;
        }
        else if ((index < GetNumSchemas()) && (sectionIndex < MRMFILE_MAP_MAX_STANDARD_VALUE))
        {
            m_schemas[index].offsetOrSectionIndex = static_cast<UINT16>(sectionIndex);
            m_schemas[index].dataSizeInBytes = 0;
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT
    WriteSchemaBlob(_In_ UINT32 index, _In_ UINT32 offset, _In_reads_bytes_(dataSizeInBytes) const void* data, _In_ UINT32 dataSizeInBytes)
    {
        if ((index < GetNumSchemas()) && (offset < GetSchemaDataSizeInBytes()) && (data != nullptr) && (dataSizeInBytes > 0) &&
            ((offset + dataSizeInBytes) <= GetSchemaDataSizeInBytes()) && ((offset + dataSizeInBytes) > offset)) // overflow
        {
            m_schemas[index].offsetOrSectionIndex = static_cast<UINT16>(offset);
            m_schemas[index].dataSizeInBytes = static_cast<UINT16>(dataSizeInBytes);
            CopyMemory(&m_schemaData[offset], data, dataSizeInBytes);
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT WriteSmallInternalLink(_In_ UINT32 index, _In_ UINT32 linksToResourceIndex)
    {
        if ((index < GetNumSmallInternalLinks()) && (linksToResourceIndex <= MRMFILE_MAP_MAX_STANDARD_VALUE))
        {
            m_internalLinks[index] = static_cast<UINT16>(linksToResourceIndex);
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT WriteLargeInternalLink(_In_ UINT32 index, _In_ UINT32 linksToResourceIndex)
    {
        if (index < GetNumLargeInternalLinks())
        {
            m_largeInternalLinks[index] = linksToResourceIndex;
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT WriteSmallFullLink(_In_ UINT32 index, _In_ UINT32 linksToSchemaIndex, _In_ UINT32 linksToResourceIndex)
    {
        if ((index < GetNumSmallFullLinks()) && (linksToSchemaIndex < GetNumSchemas()) &&
            (linksToResourceIndex < MRMFILE_MAP_MAX_STANDARD_VALUE))
        {
            m_fullLinks[index].schemaIndex = static_cast<UINT16>(linksToSchemaIndex);
            m_fullLinks[index].resourceIndex = static_cast<UINT16>(linksToResourceIndex);
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT WriteLargeFullLink(_In_ UINT32 index, _In_ UINT32 linksToSchemaIndex, _In_ UINT32 linksToResourceIndex)
    {
        if ((index < GetNumLargeFullLinks()) && (linksToSchemaIndex < GetNumSchemas()))
        {
            m_largeFullLinks[index].schemaIndex = static_cast<UINT16>(linksToSchemaIndex);
            m_largeFullLinks[index].pad = 0;
            m_largeFullLinks[index].resourceIndex = linksToResourceIndex;
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT WriteSmallLinkById(_In_ UINT32 index, _In_ UINT32 linksFromResourceIndex, _In_ UINT32 linksToLinkIndex)
    {
        if ((index < GetNumSmallLinksById()) && (linksFromResourceIndex < MRMFILE_MAP_MAX_STANDARD_VALUE) &&
            (linksToLinkIndex < MRMFILE_MAP_MAX_STANDARD_VALUE) && (linksToLinkIndex < GetNumTotalLinks()))
        {
            m_linksById[index].myResourceIndex = static_cast<UINT16>(linksFromResourceIndex);
            m_linksById[index].linkIndexInTable = static_cast<UINT16>(linksToLinkIndex);
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT WriteLargeLinkById(_In_ UINT32 index, _In_ UINT32 linksFromResourceIndex, _In_ UINT32 linksToLinkIndex)
    {
        if ((index < GetNumLargeLinksById()) && (linksToLinkIndex < GetNumTotalLinks()))
        {
            m_largeLinksById[index].myResourceIndex = linksFromResourceIndex;
            m_largeLinksById[index].pad = 0;
            m_largeLinksById[index].linkIndexInTable = static_cast<UINT16>(linksToLinkIndex);
        }
        else
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        return S_OK;
    }

    HRESULT SortLinksById() { return E_NOTIMPL; }

protected:
    MRMFILE_RESOURCE_LINK_HEADER* m_header;
    MRMFILE_LINK_SCHEMA_MAP* m_schemas;
    BYTE* m_schemaData;
    UINT16* m_internalLinks;
    UINT32* m_largeInternalLinks;
    MRMFILE_FULL_LINK* m_fullLinks;
    MRMFILE_LARGE_FULL_LINK* m_largeFullLinks;
    MRMFILE_LINK_BY_ID* m_linksById;
    MRMFILE_LARGE_LINK_BY_ID* m_largeLinksById;

    UINT32 m_totalSizeInBytes;
};

HRESULT
ResourceLinkSectionBuilder::CreateInstance(_In_ HierarchicalSchemaSectionBuilder* schema, _Outptr_ ResourceLinkSectionBuilder** result)
{
    *result = nullptr;

    AutoDeletePtr<ResourceLinkSectionBuilder> rtrn = new ResourceLinkSectionBuilder();
    RETURN_IF_NULL_ALLOC(rtrn);
    RETURN_IF_FAILED(rtrn->Init(schema));

    *result = rtrn.Detach();
    return S_OK;
}

ResourceLinkSectionBuilder::~ResourceLinkSectionBuilder()
{
    for (int i = 0; i < m_schemas.Count(); i++)
    {
        // we own the references but not the sections
        SchemaRef* sr;
        if (SUCCEEDED(m_schemas.GetPtrValue(i, &sr)))
        {
            delete sr->ref;
        }
    }

    if (m_items != nullptr)
    {
        AtomIndexedDictionaryBase::Iterator* iter;
        (void)m_items->NewIterator(&iter);

        if (iter != nullptr)
        {
            Atom::Index index;
            ItemRef ref;

            while (SUCCEEDED(m_items->GetNextItem(iter, &index, &ref)))
            {
                if (ref.linksToResourceName != nullptr)
                {
                    Def_Free(ref.linksToResourceName);
                }
            }

            (void)m_items->DeleteIterator(iter);
        }
    }
}

HRESULT ResourceLinkSectionBuilder::AddResourceLink(_In_ int linkFromResourceIndex, _In_ PCWSTR linkToResourceName)
{
    return AddResourceLink(linkFromResourceIndex, m_schema, linkToResourceName);
}

HRESULT ResourceLinkSectionBuilder::AddResourceLink(_In_ PCWSTR linkFromResourceName, _In_ PCWSTR linkToResourceName)
{
    return AddResourceLink(linkFromResourceName, m_schema, linkToResourceName);
}

_Success_(return == true)
bool ResourceLinkSectionBuilder::TryGetResourceIndex(_In_ int schemaIndex, _In_ PCWSTR resourceName, _Out_ Atom::Index* resourceIndex) const
{
    SchemaRef* haveSchema;
    (void)m_schemas.GetPtrValue(schemaIndex, &haveSchema);

    if (haveSchema == nullptr)
    {
        return false;
    }

    if (haveSchema->section == nullptr)
    {
        return false;
    }

    return haveSchema->section->GetItemNames()->TryGetIndex(resourceName, resourceIndex);
}

_Success_(return == true)
bool ResourceLinkSectionBuilder::TryGetResourceLinkByResourceIndex(
    _In_ int resourceIndexInSchema,
    _Out_opt_ int* linksToSchemaIndex,
    _Out_opt_ int* linksToResourceIndex) const
{
    if ((resourceIndexInSchema < 0) || (resourceIndexInSchema >= m_schema->GetNumItems()))
    {
        return false;
    }

    ItemRef linkData;
    if (m_items->TryGetItemData(resourceIndexInSchema, &linkData))
    {
        if (linkData.linksToResourceIndex < 0)
        {
            Atom::Index index;

            if (!TryGetResourceIndex(linkData.linksToSchemaIndex, linkData.linksToResourceName, &index))
            {
                return false;
            }

            linkData.linksToResourceIndex = index;
            if (FAILED(m_items->SetItemData(resourceIndexInSchema, linkData, true)))
            {
                return false;
            }
        }

        if (linksToSchemaIndex != nullptr)
        {
            *linksToSchemaIndex = linkData.linksToSchemaIndex;
        }

        if (linksToResourceIndex != nullptr)
        {
            *linksToResourceIndex = linkData.linksToResourceIndex;
        }

        return true;
    }

    return false;
}

HRESULT ResourceLinkSectionBuilder::AddResourceLink(
    _In_ int linkFromResourceIndex,
    _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
    _In_ PCWSTR linkToResourceName)
{
    if ((linkFromResourceIndex < 0) || (linkFromResourceIndex >= m_schema->GetNumItems()))
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    int linkToIndex = -1;
    (void)linkToSchema->GetItemNames()->TryGetIndex(linkToResourceName, &linkToIndex);

    int schemaIndex = -1;
    for (int i = 0; i < m_schemas.Count(); i++)
    {
        SchemaRef* haveSchema;
        (void)m_schemas.GetPtrValue(i, &haveSchema);
        if (linkToSchema == haveSchema->section)
        {
            schemaIndex = i;
            break;
        }
    }

    if (schemaIndex < 0)
    {
        SchemaRef ref = {linkToSchema, nullptr};
        RETURN_IF_FAILED(m_schemas.Add(ref, &schemaIndex));
    }

    if (schemaIndex >= 0)
    {
        ItemRef ref = {schemaIndex, -1, SmallInternal, static_cast<UINT32>(-1), nullptr};

        if (linkToIndex >= 0)
        {
            ref.linksToResourceIndex = linkToIndex;
        }
        else
        {
            RETURN_IF_FAILED(DefString_Dup(linkToResourceName, &(ref.linksToResourceName)));
        }

        RETURN_IF_FAILED(m_items->SetItemData(linkFromResourceIndex, ref, false));
    }

    return S_OK;
}

HRESULT ResourceLinkSectionBuilder::AddResourceLink(
    _In_ PCWSTR linkFromResourceName,
    _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
    _In_ PCWSTR linkToResourceName)
{
    int linkFromResourceIndex;
    RETURN_IF_FAILED(m_schema->GetOrAddItem(linkFromResourceName, &linkFromResourceIndex));

    return AddResourceLink(linkFromResourceIndex, linkToSchema, linkToResourceName);
}

bool ResourceLinkSectionBuilder::IsValid() const { return true; }

HRESULT ResourceLinkSectionBuilder::FinalizeSchemas()
{
    // until external schemas are supported, m_finalizedSchemaDataSizeInBytes is always 0.
    m_finalizedSchemaDataSizeInBytes = 0;
    m_numFinalizedSchemas = m_schemas.Count();

    for (int i = 0; i < m_schemas.Count(); i++)
    {
        SchemaRef* schema;
        // if we have a section builder, we can use a section reference, which requires
        // no additional data.   Otherwise we need to store a schema reference.
        if (SUCCEEDED(m_schemas.GetPtrValue(i, &schema)) && (schema->section == nullptr))
        {
            if ((schema->ref != nullptr))
            {
                // we don't handle external references yet
                return E_NOTIMPL;
            }
        }
    }

    if (m_finalizedSchemaDataSizeInBytes > 0)
    {
        m_finalizedSchemaDataSizeInBytes = _DEFFILE_PAD(m_finalizedSchemaDataSizeInBytes, BaseFile::Align32Bit);
    }

    return S_OK;
}

HRESULT ResourceLinkSectionBuilder::FinalizeLinks()
{
    m_numFinalizedSmallInternalLinks = m_numFinalizedLargeInternalLinks = 0;
    m_numFinalizedSmallFullLinks = m_numFinalizedLargeFullLinks = 0;
    m_numFinalizedSmallLinksById = m_numFinalizedLargeLinksById = 0;

    // First we compute the link tables
    for (auto iItem = m_items->GetMinAtomIndex(); iItem <= m_items->GetMaxAtomIndex(); iItem++)
    {
        ItemRef item;
        if (!m_items->TryGetItemData(iItem, &item))
        {
            // nothing present for the item, keep going
            continue;
        }

        if (item.linksToResourceIndex < 0)
        {
            Atom::Index resourceIndex;
            if (!TryGetResourceIndex(item.linksToSchemaIndex, item.linksToResourceName, &resourceIndex))
            {
                return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
            }

            item.linksToResourceIndex = static_cast<int>(resourceIndex);
        }

        if (IsLarge(&item))
        {
            item.finalizedLinkIndex = (IsInternal(&item) ? m_numFinalizedLargeInternalLinks++ : m_numFinalizedLargeFullLinks++);
            item.finalizedLinkType = (IsInternal(&item) ? LargeInternal : LargeFull);
        }
        else
        {
            item.finalizedLinkIndex = (IsInternal(&item) ? m_numFinalizedSmallInternalLinks++ : m_numFinalizedSmallFullLinks++);
            item.finalizedLinkType = (IsInternal(&item) ? SmallInternal : SmallFull);
        }

        RETURN_IF_FAILED(m_items->SetItemData(iItem, item, true));
    }

    // Now that we have a final count for each of the item types, we can compute linksById
    for (auto iItem = m_items->GetMinAtomIndex(); iItem <= m_items->GetMaxAtomIndex(); iItem++)
    {
        ItemRef item;
        if (!m_items->TryGetItemData(iItem, &item))
        {
            // nothing present for the item, keep going
            continue;
        }

        if (item.finalizedLinkType == LargeInternal)
        {
            item.finalizedLinkIndex += m_numFinalizedSmallInternalLinks;
        }
        else if (item.finalizedLinkType == SmallFull)
        {
            item.finalizedLinkIndex += (m_numFinalizedSmallInternalLinks + m_numFinalizedLargeInternalLinks);
        }
        else if (item.finalizedLinkType == LargeFull)
        {
            item.finalizedLinkIndex += (m_numFinalizedSmallInternalLinks + m_numFinalizedLargeInternalLinks + m_numFinalizedSmallFullLinks);
        }

        if (IsLarge(iItem | item.finalizedLinkIndex))
        {
            m_numFinalizedLargeLinksById++;
        }
        else
        {
            m_numFinalizedSmallLinksById++;
        }

        RETURN_IF_FAILED(m_items->SetItemData(iItem, item, true));
    }
    return S_OK;
}

HRESULT ResourceLinkSectionBuilder::Finalize()
{
    if (m_finalized)
    {
        return S_OK;
    }

    RETURN_IF_FAILED(FinalizeSchemas());
    RETURN_IF_FAILED(FinalizeLinks());

    m_finalized = true;

    return S_OK;
}

UINT32 ResourceLinkSectionBuilder::GetMaxSizeInBytes() const
{
    if (!m_finalized)
    {
        return 0;
    }

    UINT32 size = sizeof(MRMFILE_RESOURCE_LINK_HEADER);
    size += (m_numFinalizedSchemas * sizeof(MRMFILE_LINK_SCHEMA_MAP));
    size += _DEFFILE_PAD(m_finalizedSchemaDataSizeInBytes, BaseFile::Align32Bit);
    size += _DEFFILE_PAD(m_numFinalizedSmallInternalLinks * sizeof(UINT16), BaseFile::Align32Bit);
    size += (m_numFinalizedLargeInternalLinks * sizeof(UINT32));
    size += (m_numFinalizedSmallFullLinks * sizeof(MRMFILE_FULL_LINK));
    size += (m_numFinalizedLargeFullLinks * sizeof(MRMFILE_LARGE_FULL_LINK));
    size += (m_numFinalizedSmallLinksById * sizeof(MRMFILE_LINK_BY_ID));
    size += (m_numFinalizedLargeLinksById * sizeof(MRMFILE_LARGE_LINK_BY_ID));
    return size;
}

HRESULT
ResourceLinkSectionBuilder::Build(
    _Out_writes_bytes_(bufferSizeInBytes) VOID* buffer,
    _In_ UINT32 bufferSizeInBytes,
    _Out_opt_ UINT32* numBytesWritten) const
{
    RETURN_HR_IF(E_DEF_NOT_READY, !m_finalized);

    if (numBytesWritten != nullptr)
    {
        *numBytesWritten = 0;
    }

    MRMFILE_RESOURCE_LINK_HEADER header;

    header.numSchemas = static_cast<UINT16>(m_schemas.Count());
    header.schemaDataSizeInBytes = static_cast<UINT16>(m_finalizedSchemaDataSizeInBytes);
    header.numInternalLinks = static_cast<UINT16>(m_numFinalizedSmallInternalLinks + m_numFinalizedLargeInternalLinks);
    header.firstLargeInternalLink = static_cast<UINT16>(m_numFinalizedSmallInternalLinks);
    header.numFullLinks = static_cast<UINT16>(m_numFinalizedSmallFullLinks + m_numFinalizedLargeFullLinks);
    header.firstLargeFullLink = static_cast<UINT16>(m_numFinalizedSmallFullLinks);
    header.numLinksById = static_cast<UINT16>(m_numFinalizedSmallLinksById + m_numFinalizedLargeLinksById);
    header.firstLargeLinkById = static_cast<UINT16>(m_numFinalizedSmallLinksById);

    LinkBuilderFileData data;
    RETURN_IF_FAILED(data.Init(buffer, bufferSizeInBytes, header));

    // schemas
    if (m_schema->GetSectionIndex() == BaseFile::SectionIndexNone)
    {
        return E_DEF_NOT_READY;
    }

    for (int i = 0; i < m_schemas.Count(); i++)
    {
        SchemaRef* schema;
        RETURN_IF_FAILED(m_schemas.GetPtrValue(i, &schema));

        if (schema->section != nullptr)
        {
            RETURN_IF_FAILED(data.WriteSchemaSectionIndex(i, schema->section->GetSectionIndex()));
        }
        else
        {
            // references to external schemas not supported yet
            return E_NOTIMPL;
        }
    }

    int numBuiltSmallInternalLinks = 0;
    int numBuiltLargeInternalLinks = 0;
    int numBuiltSmallFullLinks = 0;
    int numBuiltLargeFullLinks = 0;
    int numBuiltSmallLinksById = 0;
    int numBuiltLargeLinksById = 0;

    for (auto i = m_items->GetMinAtomIndex(); (i <= m_items->GetMaxAtomIndex()); i++)
    {
        ItemRef item;
        if (!m_items->TryGetItemData(i, &item))
        {
            // nothing present for the item, keep going
            continue;
        }

        DEF_ASSERT(item.linksToResourceIndex >= 0);

        if (IsLarge(&item))
        {
            if (IsInternal(&item))
            {
                RETURN_IF_FAILED(data.WriteLargeInternalLink(numBuiltLargeInternalLinks++, item.linksToResourceIndex));
            }
            else
            {
                RETURN_IF_FAILED(data.WriteLargeFullLink(numBuiltLargeFullLinks++, item.linksToSchemaIndex, item.linksToResourceIndex));
            }
        }
        else
        {
            if (IsInternal(&item))
            {
                RETURN_IF_FAILED(data.WriteSmallInternalLink(numBuiltSmallInternalLinks++, item.linksToResourceIndex));
            }
            else
            {
                RETURN_IF_FAILED(data.WriteSmallFullLink(numBuiltSmallFullLinks++, item.linksToSchemaIndex, item.linksToResourceIndex));
            }
        }

        if (IsLarge(i | item.finalizedLinkIndex))
        {
            RETURN_IF_FAILED(data.WriteLargeLinkById(numBuiltLargeLinksById++, i, item.finalizedLinkIndex));
        }
        else
        {
            RETURN_IF_FAILED(data.WriteSmallLinkById(numBuiltSmallLinksById++, i, item.finalizedLinkIndex));
        }
    }

    // not sure we actually need to do that
    // ok = ok && data.SortLinksById(status);

    if (numBytesWritten != nullptr)
    {
        *numBytesWritten = static_cast<UINT32>(data.GetTotalSizeInBytes());
    }

    return S_OK;
}

ResourceLinkSectionBuilder::ResourceLinkSectionBuilder() :
    m_finalized(false),
    m_sectionIndex(BaseFile::SectionIndexNone),
    m_schema(nullptr),
    m_items(nullptr),
    m_numFinalizedSchemas(0),
    m_finalizedSchemaDataSizeInBytes(0),
    m_numFinalizedSmallInternalLinks(0),
    m_numFinalizedLargeInternalLinks(0),
    m_numFinalizedSmallFullLinks(0),
    m_numFinalizedLargeFullLinks(0),
    m_numFinalizedSmallLinksById(0),
    m_numFinalizedLargeLinksById(0)
{}

HRESULT ResourceLinkSectionBuilder::Init(_In_ HierarchicalSchemaSectionBuilder* schema)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, schema);

    m_schema = schema;

    RETURN_IF_FAILED(m_schemas.Init(10, &CompareGenericType<SchemaRef>, nullptr));

    SchemaRef ref = {schema, nullptr};
    RETURN_IF_FAILED(m_schemas.Add(ref, nullptr));

    RETURN_IF_FAILED(
        AtomIndexedStructDictionary<ItemRef>::CreateInstance(schema->GetItemNames(), AtomIndexedDictionaryBase::Strategy::Auto, &m_items));

    return S_OK;
}

} // namespace Microsoft::Resources::Build
