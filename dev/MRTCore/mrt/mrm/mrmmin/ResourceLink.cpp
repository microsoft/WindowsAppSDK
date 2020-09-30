// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

HRESULT ResourceLinkSection::CreateFromSection(
    _In_opt_ const IFileSectionResolver* sectionResolver,
    _In_opt_ const ISchemaCollection* schemaCollection,
    _In_ const IFileSection* const section,
    _Outptr_ ResourceLinkSection** result)
{
    return CreateInstance(sectionResolver, schemaCollection, section->GetSectionType(), section->GetData(), section->GetDataSize(), result);
}

HRESULT ResourceLinkSection::CreateInstance(
    _In_opt_ const IFileSectionResolver* sectionResolver,
    _In_opt_ const ISchemaCollection* schemaCollection,
    _In_ const DEFFILE_SECTION_TYPEID& sectionType,
    _In_reads_bytes_(dataSizeInBytes) const BYTE* rawData,
    _In_ int dataSizeInBytes,
    _Outptr_ ResourceLinkSection** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, rawData);

    AutoDeletePtr<ResourceLinkSection> rtrn = new ResourceLinkSection();
    RETURN_IF_NULL_ALLOC(rtrn);
    RETURN_IF_FAILED(rtrn->Init(sectionType, sectionResolver, schemaCollection, rawData, dataSizeInBytes));

    *result = rtrn.Detach();

    return S_OK;
}

ResourceLinkSection::~ResourceLinkSection() { Def_Free(m_schemas); }

HRESULT
ResourceLinkSection::ResolveSchemaReferences(_In_opt_ const IFileSectionResolver* sections, _In_opt_ const ISchemaCollection* schemas)
{
    for (int i = 0; i < m_header->numSchemas; i++)
    {
        if (m_schemas[i] == nullptr)
        {
            if (m_schemaMap[i].dataSizeInBytes == 0) // section index
            {
                if (sections != nullptr)
                {
                    HierarchicalSchema* schema;
                    RETURN_IF_FAILED(sections->GetSchemaSection(0, m_schemaMap[i].offsetOrSectionIndex, &schema));
                    m_schemas[i] = schema;
                }
                else
                {
                    return E_DEF_NOT_READY;
                }
            }
            else
            {
                if (schemas != nullptr)
                {
                    UINT32 start = m_schemaMap[i].offsetOrSectionIndex;
                    UINT32 size = m_schemaMap[i].dataSizeInBytes;

                    // test for (start+size > start) prevents overflow
                    if ((start < m_header->schemaDataSizeInBytes) && (start + size < m_header->schemaDataSizeInBytes) &&
                        (start + size > start))
                    {
                        AutoDeletePtr<HierarchicalSchemaReference> schemaReference;
                        RETURN_IF_FAILED(HierarchicalSchemaReference::CreateInstance(&m_schemaData[start], size, &schemaReference));

                        RETURN_IF_FAILED(schemas->FindSchema(schemaReference, &m_schemas[i]));
                    }
                    else
                    {
                        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
                    }
                }
                else
                {
                    return E_DEF_NOT_READY;
                }
            }
        }
    }

    if (m_schema == nullptr)
    {
        m_schema = m_schemas[0];
    }

    return S_OK;
}

HRESULT ResourceLinkSection::GetReferencedSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    if ((index >= 0) && (index < GetNumReferencedSchemas()))
    {
        auto rtrn = m_schemas[index];
        if (rtrn == nullptr)
        {
            return E_DEF_NOT_READY;
        }
        *result = rtrn;
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

HRESULT ResourceLinkSection::GetInternalResourceLink(
    _In_ UINT32 linkIndexInSection,
    _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
    _Out_opt_ UINT32* mapsToItemIndex) const
{
    RETURN_HR_IF(E_INVALIDARG, linkIndexInSection >= m_header->numInternalLinks);

    if (mapsToSchema != nullptr)
    {
        *mapsToSchema = m_schema;
    }

    if (linkIndexInSection < m_header->firstLargeInternalLink)
    {
        if (mapsToItemIndex != nullptr)
        {
            *mapsToItemIndex = m_internalLinks[linkIndexInSection];
        }
    }
    else if (m_header->firstLargeInternalLink < m_header->numInternalLinks)
    {
        if (mapsToItemIndex != nullptr)
        {
            *mapsToItemIndex = m_largeInternalLinks[linkIndexInSection - m_header->firstLargeInternalLink];
        }
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    return S_OK;
}

HRESULT ResourceLinkSection::GetFullResourceLink(
    _In_ UINT32 linkIndexInSection,
    _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
    _Out_opt_ UINT32* mapsToItemIndex) const
{
    RETURN_HR_IF(E_INVALIDARG, linkIndexInSection >= m_header->numFullLinks);

    if (linkIndexInSection < m_header->firstLargeFullLink)
    {
        if (mapsToItemIndex != nullptr)
        {
            *mapsToItemIndex = m_fullLinks[linkIndexInSection].resourceIndex;
        }

        if (mapsToSchema != nullptr)
        {
            RETURN_IF_FAILED(GetReferencedSchema(m_fullLinks[linkIndexInSection].schemaIndex, mapsToSchema));
        }
    }
    else if (m_header->firstLargeFullLink < m_header->numFullLinks)
    {
        if (mapsToItemIndex != nullptr)
        {
            *mapsToItemIndex = m_fullLinks[linkIndexInSection - m_header->firstLargeInternalLink].resourceIndex;
        }

        if (mapsToSchema != nullptr)
        {
            RETURN_IF_FAILED(
                GetReferencedSchema(m_fullLinks[linkIndexInSection - m_header->firstLargeInternalLink].schemaIndex, mapsToSchema));
        }
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    return S_OK;
}

HRESULT ResourceLinkSection::GetResourceLink(
    _In_ UINT32 linkIndexInSection,
    _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
    _Out_opt_ UINT32* mapsToItemIndex) const
{

    if (linkIndexInSection < m_header->numInternalLinks)
    {
        return GetInternalResourceLink(linkIndexInSection, mapsToSchema, mapsToItemIndex);
    }

    return GetFullResourceLink(linkIndexInSection - m_header->numInternalLinks, mapsToSchema, mapsToItemIndex);
}

HRESULT ResourceLinkSection::GetResourceLinkById(
    _In_ UINT32 linkIndexInSection,
    _Out_opt_ UINT32* linksFromResourceIndex,
    _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
    _Out_opt_ UINT32* linksToResourceIndex) const
{
    RETURN_HR_IF(E_INVALIDARG, linkIndexInSection >= m_header->numLinksById);

    int from = 1;
    int to = -1;
    if (linkIndexInSection < m_header->firstLargeLinkById)
    {
        from = m_linksById[linkIndexInSection].myResourceIndex;
        to = m_linksById[linkIndexInSection].linkIndexInTable;
    }
    else if (m_header->firstLargeLinkById < m_header->numLinksById)
    {
        linkIndexInSection -= m_header->firstLargeLinkById;

        from = m_largeLinksById[linkIndexInSection].myResourceIndex;
        to = m_largeLinksById[linkIndexInSection].linkIndexInTable;
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    RETURN_IF_FAILED(GetResourceLink(to, mapsToSchema, linksToResourceIndex));

    if (linksFromResourceIndex != nullptr)
    {
        *linksFromResourceIndex = from;
    }

    return S_OK;
}

bool ResourceLinkSection::TryGetResourceLinkForResourceIndex(
    _In_ UINT32 linksFromResourceIndex,
    _Outptr_opt_result_maybenull_ const IHierarchicalSchema** linksToSchema,
    _Out_ UINT32* linksToResourceIndex) const
{
    int to = -1;

    // Check regular links.
    for (int i = 0; i < m_header->firstLargeLinkById; i++)
    {
        if (m_linksById[i].myResourceIndex == linksFromResourceIndex)
        {
            to = m_linksById[i].linkIndexInTable;
            break;
        }
    }

    if (to < 0)
    {
        // Not found in the regular links. Check large links.
        for (int i = m_header->firstLargeLinkById; i < m_header->numLinksById; i++)
        {
            if (m_largeLinksById[i - m_header->firstLargeLinkById].myResourceIndex == linksFromResourceIndex)
            {
                to = m_largeLinksById[i - m_header->firstLargeLinkById].linkIndexInTable;
                break;
            }
        }
    }

    if (to >= 0)
    {
        return SUCCEEDED(GetResourceLink(to, linksToSchema, linksToResourceIndex));
    }

    return false;
}

const DEFFILE_SECTION_TYPEID ResourceLinkSection::GetSectionTypeId() { return gResourceLinkSectionType; }

HRESULT ResourceLinkSection::Init(
    _In_ const DEFFILE_SECTION_TYPEID& sectionType,
    _In_ const IFileSectionResolver* sections,
    _In_ const ISchemaCollection* schemaCollection,
    _In_reads_bytes_(dataSizeInBytes) const BYTE* rawData,
    _In_ UINT32 dataSizeInBytes)
{
    if (!BaseFile::SectionTypesEqual(sectionType, gResourceLinkSectionType))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    SectionParser data;
    RETURN_IF_FAILED(data.Set(rawData, dataSizeInBytes));

    HRESULT hr = S_OK;
    m_header = _SECTION_PARSER_NEXT(data, MRMFILE_RESOURCE_LINK_HEADER, &hr);
    if (m_header == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    if (m_header->numSchemas < 1)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    m_schemaMap = _SECTION_PARSER_NEXT_ARRAY(data, m_header->numSchemas, MRMFILE_LINK_SCHEMA_MAP, &hr);
    if (m_header->schemaDataSizeInBytes > 0)
    {
        m_schemaData = _SECTION_PARSER_NEXT_ARRAY(data, m_header->schemaDataSizeInBytes, BYTE, &hr);
    }
    data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);
    m_internalLinks = _SECTION_PARSER_NEXT_ARRAY(data, m_header->firstLargeInternalLink, UINT16, &hr);
    data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);
    if (m_header->firstLargeInternalLink < m_header->numInternalLinks)
    {
        m_largeInternalLinks =
            _SECTION_PARSER_NEXT_ARRAY(data, (m_header->numInternalLinks - m_header->firstLargeInternalLink), UINT32, &hr);
    }

    m_fullLinks = _SECTION_PARSER_NEXT_ARRAY(data, m_header->firstLargeFullLink, MRMFILE_FULL_LINK, &hr);
    if (m_header->firstLargeFullLink < m_header->numFullLinks)
    {
        m_largeFullLinks =
            _SECTION_PARSER_NEXT_ARRAY(data, (m_header->numFullLinks - m_header->firstLargeFullLink), MRMFILE_LARGE_FULL_LINK, &hr);
    }

    m_linksById = _SECTION_PARSER_NEXT_ARRAY(data, m_header->firstLargeLinkById, MRMFILE_LINK_BY_ID, &hr);
    if (m_header->firstLargeLinkById < m_header->numLinksById)
    {
        m_largeLinksById =
            _SECTION_PARSER_NEXT_ARRAY(data, (m_header->numLinksById - m_header->firstLargeLinkById), MRMFILE_LARGE_LINK_BY_ID, &hr);
    }

    data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);
    RETURN_IF_FAILED(hr);

    m_schemas = _DefArray_AllocZeroed(const IHierarchicalSchema*, m_header->numSchemas);
    RETURN_IF_NULL_ALLOC(m_schemas);

    if ((sections != nullptr) || (schemaCollection != nullptr))
    {
        (void)ResolveSchemaReferences(sections, schemaCollection);
    }

    return S_OK;
}

} // namespace Microsoft::Resources
