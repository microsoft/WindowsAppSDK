// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources
{

_Use_decl_annotations_ HRESULT FileDataSection::Init(const IFileSection* pSection, const void* pData, int cbData)
{
    if ((pSection != nullptr) && (!BaseFile::SectionTypesEqual(gDataSectionType, pSection->GetSectionType())))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));
    m_pData = reinterpret_cast<const BYTE*>(pData);
    m_cbData = cbData;

    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataSection::CreateInstance(const void* pData, int cbData, FileDataSection** result)
{
    *result = nullptr;

    AutoDeletePtr<FileDataSection> pRtrn = new FileDataSection;
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(NULL, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataSection::CreateInstance(IFileSection* pSection, FileDataSection** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pSection);

    UINT32 cbData = 0;
    const BYTE* pData = pSection->GetData(&cbData);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT), pData == nullptr);

    AutoDeletePtr<FileDataSection> pRtrn = new FileDataSection();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSection, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataSection::GetDataRef(UINT32 offset, const BYTE** result, size_t* pcbBytesLeftOut) const
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, offset >= m_cbData);

    *result = m_pData + offset;

    if (pcbBytesLeftOut != nullptr)
    {
        *pcbBytesLeftOut = m_cbData - offset;
    }
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataSection::GetDataRef(UINT32 offset, size_t cbData, const BYTE** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (offset >= m_cbData) || ((offset + cbData) >= m_cbData));

    *result = m_pData + offset;
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataSection::GetDataRef(UINT32 offset, UINT32 cbData, BlobResult* pData) const
{
    RETURN_HR_IF(E_INVALIDARG, (offset >= m_cbData) || ((offset + cbData) > m_cbData));

    RETURN_IF_FAILED(pData->SetRef(m_pData + offset, cbData));

    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataItemsSection::Init(const IFileSection* pSection, const void* pData, int cbData)
{
    SectionParser data;

    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData, gDataItemsSectionType));
    RETURN_IF_FAILED(ValidateHeader(pData, cbData));
    RETURN_IF_FAILED(data.Set(pData, cbData));

    HRESULT hr = S_OK;
    m_pHeader = _SECTION_PARSER_NEXT(data, DEFFILE_DATAITEMS_HEADER, &hr);
    if (m_pHeader)
    {
        if (m_pHeader->numSmallItems > 0)
        {
            m_pSmallItems = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numSmallItems, DEFFILE_DATA_ITEM_SMALL, &hr);
        }
        if (m_pHeader->numLargeItems > 0)
        {
            m_pLargeItems = _SECTION_PARSER_NEXT_ARRAY(data, GetNumberOfLargeItems(m_pHeader), DEFFILE_DATA_ITEM_LARGE, &hr);
        }
        if (m_pHeader->cbData > 0)
        {
            m_pData = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cbData, BYTE, &hr);
        }
    }

    return hr;
}

_Use_decl_annotations_ HRESULT FileDataItemsSection::CreateInstance(const void* pData, int cbData, FileDataItemsSection** result)
{
    *result = nullptr;

    AutoDeletePtr<FileDataItemsSection> pRtrn = new FileDataItemsSection();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(NULL, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataItemsSection::CreateInstance(IFileSection* pSection, FileDataItemsSection** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pSection);

    UINT32 cbData = 0;
    const BYTE* pData = pSection->GetData(&cbData);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT), pData == nullptr);

    AutoDeletePtr<FileDataItemsSection> pRtrn = new FileDataItemsSection();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSection, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataItemsSection::ValidateHeader(const void* pData, UINT32 cbData)
{
    const DEFFILE_DATAITEMS_HEADER* pHdr = static_cast<const DEFFILE_DATAITEMS_HEADER*>(pData);

    RETURN_HR_IF(E_INVALIDARG, (pHdr == nullptr) || (cbData < sizeof(DEFFILE_DATAITEMS_HEADER)));

    size_t minSize = sizeof(DEFFILE_DATAITEMS_HEADER) + (pHdr->numSmallItems * sizeof(DEFFILE_DATA_ITEM_SMALL)) +
                     (GetNumberOfLargeItems(pHdr) * sizeof(DEFFILE_DATA_ITEM_LARGE)) + pHdr->cbData;
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), minSize > cbData);
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataItemsSection::GetItemDataRef(UINT32 index, const BYTE** result, UINT32* pcbDataOut) const
{
    *result = nullptr;

    size_t offset = 0;
    size_t cbItemData = 0;

    if (index < m_pHeader->numSmallItems)
    {
        offset = m_pSmallItems[index].offset;
        cbItemData = m_pSmallItems[index].cbData;
    }
    else if ((index - m_pHeader->numSmallItems) < GetNumberOfLargeItems(m_pHeader))
    {
        offset = m_pLargeItems[index - m_pHeader->numSmallItems].offset;
        cbItemData = m_pLargeItems[index - m_pHeader->numSmallItems].cbData;
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    if ((offset + cbItemData) > m_pHeader->cbData)
    {
        // File data is bad - the entry points outside of the data
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    if (pcbDataOut != nullptr)
    {
        *pcbDataOut = static_cast<UINT32>(cbItemData);
    }

    *result = &m_pData[offset];
    return S_OK;
}

_Use_decl_annotations_ HRESULT FileDataItemsSection::GetItemDataRef(UINT32 index, BlobResult* pData) const
{
    UINT32 cbData;
    const BYTE* pLocalData;
    RETURN_IF_FAILED(GetItemDataRef(index, &pLocalData, &cbData));
    if (pLocalData)
    {
        RETURN_IF_FAILED(pData->SetRef(pLocalData, cbData));
    }

    return S_OK;
}

} // namespace Microsoft::Resources