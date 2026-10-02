// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

//------------------------------------------------------------------
// File: DataSectionBuilder.cpp
//
// DataSectionBuilder class definition.
//------------------------------------------------------------------

#include "StdAfx.h"

namespace Microsoft::Resources::Build
{

/*
* DataBlobBuilder Implementation.
*/

/*
** Private constructor.
*/
DataBlobBuilder::DataBlobBuilder() : m_offset(0), m_pHeadDataList(NULL) {}

HRESULT DataBlobBuilder::Init()
{
    m_pHeadDataList = reinterpret_cast<MEM_LINKED_DATABLOB*>(_DefArray_Alloc(BYTE, maxListBufferSize + sizeof(MEM_LINKED_DATABLOB)));
    RETURN_IF_NULL_ALLOC(m_pHeadDataList);

    m_pHeadDataList->fIsGivenData = false;
    m_pHeadDataList->nSize = 0;
    m_pHeadDataList->pNext = NULL;
    m_pHeadDataList->pData = reinterpret_cast<BYTE*>(m_pHeadDataList + 1);
    m_pCurDataList = m_pHeadDataList;

    return S_OK;
}

/*
* Creates and returns CompiledItemInfoBuilder object.
*/
HRESULT DataBlobBuilder::CreateInstance(_Outptr_ DataBlobBuilder** result)
{
    *result = nullptr;

    AutoDeletePtr<DataBlobBuilder> builder = new DataBlobBuilder();
    RETURN_IF_NULL_ALLOC(builder);
    RETURN_IF_FAILED(builder->Init());

    *result = builder.Detach();
    return S_OK;
}

/*
* Destructor.
*/
DataBlobBuilder::~DataBlobBuilder()
{
    while (m_pHeadDataList)
    {
        m_pCurDataList = m_pHeadDataList->pNext;
        _DefFree(m_pHeadDataList);
        m_pHeadDataList = m_pCurDataList;
    }
}

/*!
      * Appends the specified data to the data segment as
      * a reference, and
      * returns the offset at which it was added.  Does not
      * check to see if the value is already in the buffer.
      */
HRESULT DataBlobBuilder::AddDataAsReference(__in_bcount(cbData) const BYTE* pData, __in UINT32 cbData, __out UINT32* pWrittenOffset)
{
    RETURN_HR_IF(E_INVALIDARG, (pWrittenOffset == nullptr) || (pData == nullptr) || (cbData == 0));

    MEM_LINKED_DATABLOB* pNewDataList = reinterpret_cast<MEM_LINKED_DATABLOB*>(_DefArray_Alloc(BYTE, sizeof(MEM_LINKED_DATABLOB)));
    RETURN_IF_NULL_ALLOC(pNewDataList);

    pNewDataList->fIsGivenData = true;
    pNewDataList->nSize = 0;
    pNewDataList->pNext = NULL;
    pNewDataList->pData = const_cast<BYTE*>(pData);
    m_pCurDataList->pNext = pNewDataList;
    m_pCurDataList = m_pCurDataList->pNext;

    *pWrittenOffset = m_offset;

    // We might want to let the next caller specify the padding
    // they need instead of just assuming that everybody needs
    // 32-bit alignment.
    m_pCurDataList->nSize += _DEFFILE_PAD(cbData, 4);
    m_offset += _DEFFILE_PAD(cbData, 4);

    return S_OK;
}

/*!
      * Copies the specified data to the data segment and
      * returns the offset at which it was added.  Does not
      * check to see if the value is already in the buffer.
      */
HRESULT DataBlobBuilder::AddData(__in_bcount(cbData) const BYTE* pData, __in UINT32 cbData, __out UINT32* pWrittenOffset)
{
    RETURN_HR_IF(E_INVALIDARG, (pWrittenOffset == nullptr) || (pData == nullptr) || (cbData == 0));

    // it doesn't handle data that is beyond maxListBufferSize (1M) or
    // it is given data pointer to another instance bundle
    if ((m_pCurDataList->nSize + _DEFFILE_PAD(cbData, 4) > maxListBufferSize) || m_pCurDataList->fIsGivenData)
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    MEM_LINKED_DATABLOB* pNewDataList =
        reinterpret_cast<MEM_LINKED_DATABLOB*>(_DefArray_AllocZeroed(BYTE, _DEFFILE_PAD(cbData, 4) + sizeof(MEM_LINKED_DATABLOB)));
    RETURN_IF_NULL_ALLOC(pNewDataList);

    pNewDataList->fIsGivenData = false;
    pNewDataList->nSize = 0;
    pNewDataList->pNext = NULL;
    pNewDataList->pData = reinterpret_cast<BYTE*>(pNewDataList + 1);
    m_pCurDataList->pNext = pNewDataList;
    m_pCurDataList = m_pCurDataList->pNext;

    // Copy the given data and note the offset.
    memcpy_s(&(m_pCurDataList->pData[m_pCurDataList->nSize]), (maxListBufferSize - m_pCurDataList->nSize), pData, cbData);
    *pWrittenOffset = m_offset;

    // We might want to let the next caller specify the padding
    // they need instead of just assuming that everybody needs
    // 32-bit alignment.
    m_pCurDataList->nSize += _DEFFILE_PAD(cbData, 4);
    m_offset += _DEFFILE_PAD(cbData, 4);

    return S_OK;
}

bool DataBlobBuilder::TryFindData(__in_bcount(cbData) const BYTE* pData, __in UINT32 cbData, __in UINT32 dataBlobBuilderOffset) const
{
    if ((pData == nullptr) || (cbData == 0))
    {
        return false;
    }

    UINT32 nOffset = 0;
    bool bFound = false;
    MEM_LINKED_DATABLOB* pDataListItr = m_pHeadDataList;
    while (pDataListItr)
    {
        if ((pDataListItr->nSize == _DEFFILE_PAD(cbData, 4)) && (nOffset == dataBlobBuilderOffset))
        {
            if (memcmp(pData, pDataListItr->pData, cbData) == 0)
            {
                bFound = true;
                break;
            }
        }
        nOffset += _DEFFILE_PAD(pDataListItr->nSize, 4);
        pDataListItr = pDataListItr->pNext;
    }
    return bFound;
}

bool DataBlobBuilder::TryGetStringData(__in UINT32 wantOffset, __inout StringResult* pStringOut) const
{
    UINT32 offset = 0;
    MEM_LINKED_DATABLOB* pEntry = m_pHeadDataList;

    while (pEntry)
    {
        if (wantOffset < (offset + pEntry->nSize))
        {
            return SUCCEEDED(pStringOut->SetRef((PCWSTR)&pEntry->pData[wantOffset - offset]));
        }
        offset += pEntry->nSize;
        pEntry = pEntry->pNext;
    }
    return false;
}

bool DataBlobBuilder::TryGetBlobData(__in UINT32 wantOffset, __in UINT32 cbData, __inout BlobResult* pBlobOut) const
{
    UINT32 offset = 0;
    MEM_LINKED_DATABLOB* pEntry = m_pHeadDataList;

    while (pEntry)
    {
        if (wantOffset < (offset + pEntry->nSize))
        {
            if ((wantOffset + cbData) > (offset + pEntry->nSize))
            {
                // can't stitch together a value from adjacent buffers
                return false;
            }
            return SUCCEEDED(pBlobOut->SetRef(&pEntry->pData[wantOffset - offset], cbData));
        }
        offset += pEntry->nSize;
        pEntry = pEntry->pNext;
    }
    return false;
}

/*
* Returns Maximum size of the buffer needed to create DataSectionBuilder Section
*/
UINT32 DataBlobBuilder::GetMaxSizeInBytesOfDataBlob() const { return m_offset; }

/*
* Build Data Blob.
*/
HRESULT DataBlobBuilder::BuildDataBlob(__out_bcount(cbBuffer) VOID* pBuffer, __in UINT32 cbBuffer, __out_opt UINT32* pcbWritten) const
{
    // special case empty write
    if ((pBuffer == NULL) && (cbBuffer == 0))
    {
        *pcbWritten = 0;
        return S_OK;
    }

    RETURN_HR_IF(E_INVALIDARG, (pBuffer == nullptr) || (cbBuffer < m_offset));

    UINT32 cbWritten = 0;
    m_pCurDataList = m_pHeadDataList;
    BYTE* pDestBuffer = reinterpret_cast<BYTE*>(pBuffer);

    while (m_pCurDataList)
    {

        memcpy_s(&pDestBuffer[cbWritten], cbBuffer - cbWritten, m_pCurDataList->pData, m_pCurDataList->nSize);

        cbWritten += m_pCurDataList->nSize;
        m_pCurDataList = m_pCurDataList->pNext;
    }

    if (pcbWritten)
    {
        *pcbWritten = cbWritten;
    }

    return S_OK;
}

/*
* DataSectionBuilder Implementation.
*/

/*
** Private constructor.
*/
DataSectionBuilder::DataSectionBuilder() : DataBlobBuilder(), m_sectionIndex(BaseFile::SectionIndexNone) {}

/*
* Creates and returns CompiledItemInfoBuilder object.
*/
HRESULT DataSectionBuilder::CreateInstance(_Outptr_ DataSectionBuilder** result)
{
    *result = nullptr;
    AutoDeletePtr<DataSectionBuilder> builder = new DataSectionBuilder();
    RETURN_IF_NULL_ALLOC(builder);
    RETURN_IF_FAILED(builder->Init());

    *result = builder.Detach();
    return S_OK;
}

//! Implements ISectionBuilder::Finalize
HRESULT DataSectionBuilder::Finalize() { return S_OK; }

//! Implements ISectionBuilder::GetMaxSizeInBytes
UINT32 DataSectionBuilder::GetMaxSizeInBytes() const { return GetMaxSizeInBytesOfDataBlob(); }

//! Implements ISectionBuilder::Build
HRESULT DataSectionBuilder::Build(__out_bcount(cbBuffer) VOID* pBuffer, __in UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const
{
    return BuildDataBlob(pBuffer, cbBuffer, pcbWrittenOut);
}

/*
* Destructor.
*/
DataSectionBuilder::~DataSectionBuilder() {}

/*
     * DataItemsSectionBuilder
     */

DataItemsSectionBuilder::DataItemsSectionBuilder() :
    m_finalized(false),
    m_sectionIndex(BaseFile::SectionIndexNone),
    m_numSmallItems(0),
    m_sizeSmallItems(0),
    m_cbSmallItemDataUsed(0),
    m_cbSmallItemDataCapacity(0),
    m_pSmallItemData(NULL),
    m_pSmallItems(NULL),
    m_numLargeItems(0),
    m_sizeLargeItems(0),
    m_cbLargeItemDataUsed(0),
    m_cbLargeItemDataCapacity(0),
    m_pLargeItemData(NULL),
    m_pLargeItems(NULL)
{}

HRESULT DataItemsSectionBuilder::CreateInstance(_Outptr_ DataItemsSectionBuilder** result)
{
    *result = nullptr;

    DataItemsSectionBuilder* pRtrn = new DataItemsSectionBuilder();
    RETURN_IF_NULL_ALLOC(pRtrn);

    *result = pRtrn;
    return S_OK;
}

DataItemsSectionBuilder::~DataItemsSectionBuilder()
{
    m_finalized = false;

    m_numSmallItems = m_sizeSmallItems = 0;
    m_cbSmallItemDataUsed = m_cbSmallItemDataCapacity = 0;
    if (m_pSmallItems != NULL)
    {
        Def_Free(m_pSmallItems);
        m_pSmallItems = NULL;
    }
    if (m_pSmallItemData != NULL)
    {
        Def_Free(m_pSmallItemData);
        m_pSmallItemData = NULL;
    }

    m_numLargeItems = m_sizeLargeItems = 0;
    m_cbLargeItemDataUsed = m_cbLargeItemDataCapacity = 0;
    if (m_pLargeItems != NULL)
    {
        Def_Free(m_pLargeItems);
        m_pLargeItems = NULL;
    }
    if (m_pLargeItemData != NULL)
    {
        Def_Free(m_pLargeItemData);
        m_pLargeItemData = NULL;
    }
}

HRESULT DataItemsSectionBuilder::AddDataItem(
    __in_bcount(cbData) const VOID* pData,
    __in UINT32 cbData,
    __in int align,
    __out PrebuildItemReference* pRefOut)
{
    RETURN_HR_IF(E_INVALIDARG, (pData == nullptr) || (cbData == 0) || (pRefOut == nullptr));
    RETURN_HR_IF(E_INVALIDARG, (align != 1) && (align != 2) && (align != 4) && (align != 8));

    m_finalized = false;

    int startOffset = _DEFFILE_PAD(m_cbSmallItemDataUsed, align);
    bool isLarge = ((startOffset + cbData) > DEFFILE_SMALL_DATA_ITEM_MAX_SIZE) || (align == 8);

    if (!isLarge)
    {
        // EnsureSmallCapacity takes the total required capacity, not the additional capacity
        RETURN_IF_FAILED(EnsureSmallItemCapacity(startOffset + cbData));

        __analysis_assume((startOffset + cbData) < m_cbSmallItemDataCapacity);
        __analysis_assume((m_numSmallItems < m_sizeSmallItems));

        // zero out any pad bytes
        while (m_cbSmallItemDataUsed < startOffset)
        {
            m_pSmallItemData[m_cbSmallItemDataUsed++] = 0;
        }

        // Data duplicate check can be done:
        // At first attempt, we do not check if the data is duplicate as it could increase build time exponentially (past experience).
        // However if there are many duplicate resources that hamper disk footprint, then we can revisit it.

        // And copy the data
        errno_t err = memcpy_s(&m_pSmallItemData[startOffset], (m_cbSmallItemDataCapacity - startOffset), pData, cbData);
        RETURN_IF_FAILED(ErrnoToHResult(err));

        m_pSmallItems[m_numSmallItems].offset = startOffset;
        m_pSmallItems[m_numSmallItems].cbData = cbData;

        pRefOut->isLarge = false;
        pRefOut->index = m_numSmallItems;

        m_cbSmallItemDataUsed = startOffset + cbData;
        m_numSmallItems++;
    }
    else
    {
        startOffset = _DEFFILE_PAD(m_cbLargeItemDataUsed, align);

        // EnsureLargeCapacity takes the total required capacity, not the additional capacity
        RETURN_IF_FAILED(EnsureLargeItemCapacity(startOffset + cbData));

        __analysis_assume((startOffset + cbData) < m_cbLargeItemDataCapacity);
        __analysis_assume((m_numLargeItems < m_sizeLargeItems));

        // zero out any pad bytes
        while (m_cbLargeItemDataUsed < startOffset)
        {
            m_pLargeItemData[m_cbLargeItemDataUsed++] = 0;
        }

        // Data duplicate check can be done:
        // At first attempt, we do not check if the data is duplicate as it could increase build time exponentially (past experience).
        // However if there are many duplicate resources that hamper disk footprint, then we can revisit it.

        // And copy the data
        errno_t err = memcpy_s(&m_pLargeItemData[startOffset], (m_cbLargeItemDataCapacity - startOffset), pData, cbData);
        RETURN_IF_FAILED(ErrnoToHResult(err));

        m_pLargeItems[m_numLargeItems].offset = startOffset;
        m_pLargeItems[m_numLargeItems].cbData = cbData;

        pRefOut->isLarge = true;
        pRefOut->index = m_numLargeItems;

        m_cbLargeItemDataUsed = startOffset + cbData;
        m_numLargeItems++;
    }
    return S_OK;
}

HRESULT DataItemsSectionBuilder::AddDataString(__in PCWSTR pString, __out PrebuildItemReference* pRefOut)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pString);

    return AddDataItem(pString, static_cast<UINT32>((wcslen(pString) + 1) * sizeof(WCHAR)), pRefOut);
}

HRESULT
DataItemsSectionBuilder::AddDataString(__in_ecount(cchString) PCWSTR pString, __in int cchString, __out PrebuildItemReference* pRefOut)
{
    RETURN_HR_IF(E_INVALIDARG, (pString == nullptr) || (cchString < 0));

    size_t len = wcsnlen(pString, cchString);
    RETURN_HR_IF(E_INVALIDARG, len == static_cast<size_t>(cchString));

    return AddDataItem(pString, static_cast<UINT32>((len + 1) * sizeof(WCHAR)), pRefOut);
}

HRESULT DataItemsSectionBuilder::GetBuiltItemInfo(__in const PrebuildItemReference* pPrebuildRef, __out BuiltItemReference* pRefOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (pPrebuildRef == nullptr) || (pRefOut == nullptr));

    int maxIndex = -1;
    int offset = 0;
    if (pPrebuildRef->isLarge)
    {
        offset = m_numSmallItems;
        maxIndex = m_numLargeItems - 1;
    }
    else
    {
        offset = 0;
        maxIndex = m_numSmallItems - 1;
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (pPrebuildRef->index < 0) || (pPrebuildRef->index > maxIndex));

    pRefOut->fileIndex = 0;
    pRefOut->sectionIndex = m_sectionIndex;
    pRefOut->itemIndex = (offset + pPrebuildRef->index);
    return S_OK;
}

HRESULT DataItemsSectionBuilder::GetDataBlob(_In_ int itemIndex, _Inout_ BlobResult* pBlobResult) const
{
    if (itemIndex < m_numSmallItems)
    {

        int offset = m_pSmallItems[itemIndex].offset;
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), offset >= m_cbSmallItemDataCapacity);

        RETURN_IF_FAILED(pBlobResult->SetRef(&m_pSmallItemData[offset], m_pSmallItems[itemIndex].cbData));
    }
    else
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), itemIndex >= (m_numSmallItems + m_numLargeItems));

        int indexFromLargeBase = itemIndex - m_numSmallItems;

        int offset = m_pLargeItems[indexFromLargeBase].offset;
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), offset >= m_cbLargeItemDataCapacity);

        RETURN_IF_FAILED(pBlobResult->SetRef(&m_pLargeItemData[offset], m_pLargeItems[indexFromLargeBase].cbData));
    }

    return S_OK;
}

/*!
     * \name ISectionBuilder Implementation
     * @{
     */

HRESULT DataItemsSectionBuilder::Finalize()
{
    m_finalized = true;
    return S_OK;
}

UINT32 DataItemsSectionBuilder::GetMaxSizeInBytes() const
{
    UINT32 maxSize = sizeof(DEFFILE_DATAITEMS_HEADER) + (m_numSmallItems * sizeof(DEFFILE_DATA_ITEM_SMALL)) +
                     (m_numLargeItems * sizeof(DEFFILE_DATA_ITEM_LARGE)) + m_cbSmallItemDataUsed;
    // align to 64 bits before the large items section
    maxSize = _DEFFILE_PAD(maxSize, BaseFile::Align64Bit) + _DEFFILE_PAD(m_cbLargeItemDataUsed, BaseFile::Align64Bit);
    return maxSize;
}

HRESULT DataItemsSectionBuilder::Build(__out_bcount(cbBuffer) VOID* pBuffer, __in UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pBuffer);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), cbBuffer < GetMaxSizeInBytes());

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(pBuffer, cbBuffer));

    RETURN_HR_IF(E_DEF_NOT_READY, !m_finalized);

    if (pcbWrittenOut != NULL)
    {
        *pcbWrittenOut = 0;
    }

    HRESULT hr = S_OK;
    DEFFILE_DATAITEMS_HEADER* pHdr = _SECTION_BUILDER_NEXT(data, DEFFILE_DATAITEMS_HEADER, &hr);
    RETURN_IF_FAILED(hr);

    if (m_numLargeItems > 0xffffff)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_TOO_MANY_RESOURCES);
    }

    if (m_numLargeItems > 0xffff)
    {
        pHdr->flags = ((m_numLargeItems & 0xff0000) | DEFFILE_DATAITEMS_EXTENDED_LARGE_ITEMS);
    }
    else
    {
        pHdr->flags = 0;
    }
    pHdr->numSmallItems = static_cast<UINT16>(m_numSmallItems);
    pHdr->numLargeItems = static_cast<UINT16>(m_numLargeItems);
    pHdr->cbData = 0; // we'll update later with what we actually write

    if (m_numSmallItems > 0)
    {
        DEFFILE_DATA_ITEM_SMALL* pItems = _SECTION_BUILDER_NEXT_ARRAY(data, m_numSmallItems, DEFFILE_DATA_ITEM_SMALL, &hr);
        RETURN_IF_FAILED(hr);

        __analysis_assume(m_sizeSmallItems >= m_numSmallItems);

        if (pItems != NULL)
        {
            for (int i = 0; i < m_numSmallItems; i++)
            {
                pItems[i].cbData = static_cast<UINT16>(m_pSmallItems[i].cbData);
                pItems[i].offset = static_cast<UINT16>(m_pSmallItems[i].offset);
            }
        }
    }

    if (m_numLargeItems > 0)
    {
        DEFFILE_DATA_ITEM_LARGE* pItems = _SECTION_BUILDER_NEXT_ARRAY(data, m_numLargeItems, DEFFILE_DATA_ITEM_LARGE, &hr);
        RETURN_IF_FAILED(hr);

        // Large data starts at the first 64-bit boundary after the small data.
        UINT32 dataOffset = static_cast<UINT32>(
            _DEFFILE_PAD(data.UsedBufferSizeInBytes() + m_cbSmallItemDataUsed, BaseFile::Align64Bit) - data.UsedBufferSizeInBytes());

        __analysis_assume(m_sizeLargeItems >= m_numLargeItems);

        if (pItems != NULL)
        {
            for (int i = 0; i < m_numLargeItems; i++)
            {
                pItems[i].cbData = static_cast<UINT32>(m_pLargeItems[i].cbData);
                pItems[i].offset = static_cast<UINT32>(m_pLargeItems[i].offset + dataOffset);
            }
        }
    }

    size_t used = data.UsedBufferSizeInBytes();

    if (m_cbSmallItemDataUsed > 0)
    {
        BYTE* pData = _SECTION_BUILDER_NEXT_ARRAY(data, m_cbSmallItemDataUsed, BYTE, &hr);
        RETURN_IF_FAILED(hr);

        errno_t err = memcpy_s(pData, m_cbSmallItemDataUsed, m_pSmallItemData, m_cbSmallItemDataUsed);
        // ErrnoFailed will set status if something failed.  Just fall through regardless.
        RETURN_IF_FAILED(ErrnoToHResult(err));
    }

    if (m_cbLargeItemDataUsed > 0)
    {
        // large data must be aligned to 64-bit boundary
        _SECTION_BUILDER_PAD(&data, BaseFile::Align64Bit, &hr);

        BYTE* pData = _SECTION_BUILDER_NEXT_ARRAY(data, m_cbLargeItemDataUsed, BYTE, &hr);
        RETURN_IF_FAILED(hr);

        errno_t err = memcpy_s(pData, m_cbLargeItemDataUsed, m_pLargeItemData, m_cbLargeItemDataUsed);

        // ErrnoFailed will set status if something failed.  Just fall through regardless.
        RETURN_IF_FAILED(ErrnoToHResult(err));
    }

    _SECTION_BUILDER_PAD(&data, &hr);
    RETURN_IF_FAILED(hr);

    // Might not have needed all that padding
    pHdr->cbData = static_cast<UINT32>(data.UsedBufferSizeInBytes() - used);

    if (pcbWrittenOut != NULL)
    {
        *pcbWrittenOut = static_cast<UINT32>(data.UsedBufferSizeInBytes());
    }
    return S_OK;
}

HRESULT DataItemsSectionBuilder::EnsureLargeItemCapacity(__in int cbTotal)
{
    // ensure space for item
    if (m_numLargeItems >= m_sizeLargeItems)
    {
        int newSize = ((m_sizeLargeItems == 0) ? InitialLargeItemSize : (m_sizeLargeItems * 2));
        if (!_DefArray_TryEnsureSize(&m_pLargeItems, struct ItemRef, m_sizeLargeItems, newSize))
        {
            return E_OUTOFMEMORY;
        }
        m_sizeLargeItems = newSize;
    }

    // ensure spacee for the data
    if (cbTotal > m_cbLargeItemDataCapacity)
    {
        size_t newSize = ((m_cbLargeItemDataCapacity == 0) ? InitialLargeItemDataCapacity : (m_cbLargeItemDataCapacity * 2));
        newSize = max(newSize, cbTotal);

        if (!_DefArray_TryEnsureSize(&m_pLargeItemData, BYTE, m_cbLargeItemDataCapacity, newSize))
        {
            return E_OUTOFMEMORY;
        }
        m_cbLargeItemDataCapacity = static_cast<UINT32>(newSize);
    }

    return S_OK;
}

HRESULT DataItemsSectionBuilder::EnsureSmallItemCapacity(__in int cbTotal)
{
    // ensure space for the item
    if (m_numSmallItems >= m_sizeSmallItems)
    {
        int newSize = ((m_sizeSmallItems == 0) ? InitialSmallItemSize : (m_sizeSmallItems * 2));
        if (!_DefArray_TryEnsureSize(&m_pSmallItems, struct ItemRef, m_sizeSmallItems, newSize))
        {
            return E_OUTOFMEMORY;
        }
        m_sizeSmallItems = newSize;
    }

    // ensure spacee for the data
    if (cbTotal > m_cbSmallItemDataCapacity)
    {
        size_t newSize = ((m_cbSmallItemDataCapacity == 0) ? InitialSmallItemDataCapacity : (m_cbSmallItemDataCapacity * 2));
        newSize = max(newSize, cbTotal);

        if (!_DefArray_TryEnsureSize(&m_pSmallItemData, BYTE, m_cbSmallItemDataCapacity, newSize))
        {
            return E_OUTOFMEMORY;
        }
        m_cbSmallItemDataCapacity = static_cast<UINT32>(newSize);
    }

    return S_OK;
}

} // namespace Microsoft::Resources::Build