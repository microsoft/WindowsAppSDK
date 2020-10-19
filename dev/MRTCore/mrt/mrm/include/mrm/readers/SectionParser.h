// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Microsoft::Resources
{

/*!
     * Simple helper class to simplify parsing of mapped file sections.
     */

template<typename RETURN_TYPE, typename UNIT_TYPE>
struct SectionParserBase
{
protected:
    _Field_size_bytes_(m_cbData) RETURN_TYPE* m_pData;

    _Field_size_bytes_(m_cbLeft) RETURN_TYPE* m_pNext;

    size_t m_cbData;
    size_t m_cbLeft;

public:
    SectionParserBase() : m_pData(nullptr), m_pNext(nullptr), m_cbData(0), m_cbLeft(0) {}

    HRESULT Set(_In_reads_bytes_(cbData) RETURN_TYPE* pData, _In_ UINT32 cbData)
    {
        RETURN_HR_IF(E_INVALIDARG, (pData == nullptr) || (cbData == 0));

        // Buffer overflow check by invalid input size (fuzzy test)
        const BYTE* pByteData = static_cast<const BYTE*>(pData);
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (pByteData + cbData) < pByteData);

        m_pData = pData;
        m_pNext = pData;
        m_cbData = cbData;
        m_cbLeft = cbData;
        return S_OK;
    }

    HRESULT Reset() { return Set(m_pData, static_cast<UINT32>(m_cbData)); }

    const void* FullBuffer() const { return m_pData; }
    const void* RemainingBuffer() const { return m_pNext; }
    const size_t FullBufferSizeInBytes() const { return m_cbData; }
    const size_t RemainingBufferSizeInBytes() const { return m_cbLeft; }
    const size_t UsedBufferSizeInBytes() const { return m_cbData - m_cbLeft; }

    /*! 
         * Returns a pointer to the next block of data, if
         * there's enough space in the buffer, and moves the
         * cursor over the returned data. 
         *
         * Returns NULL without modifying pStatus or the buffer
         * if pStatus is NULL or if pStatus already contains
         * an error status.
         *
         * Returns NULL but reports success if 0 items are
         * requested.  Items of size 0 cause an error.
         *
         * Returns NULL and sets an appropriate status if
         * any arguments are invalid or if the requested
         * data would overflow the buffer.
         * 
         * \param numItems
         * Specifies the number of items to be returned.
         *
         * \param cbItem
         * Specifies the size of a single item, in bytes.
         * 
         * \param pStatus
         * Reports current status.  Reports updated status if
         * an error occurs.
         *  
         * \return RETURN_TYPE*
         * Returns a pointer to the requested buffer, or NULL 
         * if an error occurs or has already occurred.
         */
    _Success_(return != nullptr)
        _Post_readable_size_(numItems* cbItem) RETURN_TYPE* GetNext(_In_ UINT32 numItems, _In_ size_t cbItem, _Inout_ HRESULT* hr)
    {
        UNIT_TYPE* pRtrn = static_cast<UNIT_TYPE*>(PeekNext(numItems, cbItem, hr));
        if (pRtrn != nullptr)
        {
            size_t cbNeeded = cbItem * numItems;
            // Buffer overflow check by invalid input size (fuzzy test)
            const BYTE* pByteData = static_cast<const BYTE*>(pRtrn);
            if ((pByteData + cbNeeded) < pByteData)
            {
                *hr = HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
                return nullptr;
            }

            m_pNext = &pRtrn[cbNeeded];
            m_cbLeft -= cbNeeded;
        }
        return pRtrn;
    }

    /*! 
         * Returns a pointer to the next block of data, if
         * there's enough space in the buffer, without 
         * moving the cursor. 
         *
         * Returns NULL without modifying pStatus if 
         * pStatus is NULL or if pStatus already contains
         * an error.
         * 
         * Returns NULL but reports success if cbNeeded is 0.
         *
         * Returns NULL and sets an appropriate status if
         * any arguments are invalid or if the requested
         * data would overflow the buffer.
         *
         * \param cbNeeded
         * Specifies the size of of the data to be read, in bytes.
         * 
         * \param pStatus
         * Reports current status.  Reports updated status if
         * an error occurs.
         *  
         * \return const void*
         * Returns a pointer to the requested buffer, or NULL 
         * if an error occurs or has already occurred.
         */
    _Success_(return != nullptr) _Post_readable_byte_size_(cbNeeded) RETURN_TYPE* GetNext(_In_ size_t cbNeeded, _Inout_ HRESULT* hr)
    {
        return GetNext(static_cast<UINT32>(cbNeeded), sizeof(BYTE), hr);
    }

    /*! 
         * Returns a pointer to the next block of data, if
         * there's enough space in the buffer, without 
         * moving the cursor.
         *
         * Returns NULL without modifying pStatus if 
         * pStatus is NULL or if pStatus already contains
         * an error status.
         *
         * Returns NULL but reports success if 0 items are
         * requested.  Items of size 0 cause an error.
         *
         * Returns NULL and sets an appropriate status if
         * any arguments are invalid or if the requested
         * data would overflow the buffer.
         * 
         * \param numItems
         * Specifies the number of items to be returned.
         *
         * \param cbItem
         * Specifies the size of a single item, in bytes.
         * 
         * \param pStatus
         * Reports current status.  Reports updated status if
         * an error occurs.
         *  
         * \return const void*
         * Returns a pointer to the requested buffer, or NULL 
         * if an error occurs or has already occurred.
         */
    _Success_(return != nullptr)
        _Post_readable_size_(numItems* cbItem) RETURN_TYPE* PeekNext(_In_ UINT32 numItems, _In_ size_t cbItem, _Inout_ HRESULT* hr) const
    {
        if (FAILED(*hr))
        {
            return nullptr;
        }

        if (cbItem < 1)
        {
            *hr = E_INVALIDARG;
            return nullptr;
        }

        if ((m_pData == nullptr) || (m_cbData < 1))
        {
            *hr = HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT);
            return nullptr;
        }

        if (numItems == 0)
        {
            // If you ask for 0 items, you get NULL but no error.
            return nullptr;
        }

        size_t cbNeeded = cbItem * numItems;
        if (cbNeeded > m_cbLeft)
        {
            *hr = HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
            return nullptr;
        }
        return m_pNext;
    }

    /*! 
         * Returns a pointer to the next block of data, if
         * there's enough space in the buffer, without 
         * moving the cursor. 
         *
         * Returns NULL and sets an appropriate status if
         * any arguments are invalid or if the requested
         * data would overflow the buffer.
         *
         * Returns NULL without modifying pStatus if 
         * pStatus is NULL or if pStatus already contains
         * an error status.
         * 
         * \param cbNeeded
         * Specifies the size the requested data, in bytes.
         * 
         * \param pStatus
         * Reports current status.  Reports updated status if
         * an error occurs.
         *  
         * \return const void*
         * Returns a pointer to the requested buffer, or NULL 
         * if an error occurs or has already occurred.
         */
    _Success_(return != nullptr) _Post_readable_byte_size_(cbNeeded) RETURN_TYPE* PeekNext(_In_ size_t cbNeeded, _Inout_ HRESULT* hr) const
    {
        return PeekNext(static_cast<UINT32>(cbNeeded), sizeof(BYTE), hr);
    }

    /*! 
         * Moves the cursor to a specified alignment boundary and returns
         * a pointer to the bytes that were skipped.  Returns NULL and succeess
         * if no padding is necessary.  Optionally returns the number of bytes
         * of padding.
         * 
         * \param align
         * Specifies the alignment to which the parser should jump.  Must be
         * 2, 4 or 8.
         *
         * \param pStatus
         * Reports optional status if an error occurs.
         *
         * \param pNumPadBytesOut
         * If non-NULL, used to return the number of pad bytes skipped.
         * 
         * \return UNIT_TYPE*
         * Returns a pointer to the padding bytes.  Returns NULL if no
         * padding is necessary or if an error occurs.
         */
    _Post_readable_byte_size_(
        *pNumPadBytesOut) UNIT_TYPE* GetPadBytes(_In_ size_t align, _Inout_ HRESULT* hr, _Out_opt_ size_t* pNumPadBytesOut)
    {
        if (FAILED(*hr))
        {
            return nullptr;
        }
        if ((align != 2) && (align != 4) && (align != 8))
        {
            *hr = HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
            return nullptr;
        }

        size_t cbUsed = UsedBufferSizeInBytes();
        size_t cbPadded = BaseFile::PadData(static_cast<int>(cbUsed), static_cast<int>(align));
        size_t cbPad = cbPadded - cbUsed;

        if (pNumPadBytesOut != nullptr)
        {
            *pNumPadBytesOut = cbPad;
        }
        return (UNIT_TYPE*)GetNext(static_cast<UINT32>(cbPad), sizeof(BYTE), hr);
    }

    /*! 
         * Moves the cursor to the default alignment boundary and returns
         * a pointer to the bytes that were skipped.  Returns NULL and succeess
         * if no padding is necessary.  Optionally returns the number of bytes
         * of padding.
         * 
         * \param pStatus
         * Reports optional status if an error occurs.
         *
         * \param pNumPadBytesOut
         * If non-NULL, used to return the number of pad bytes skipped.
         * 
         * \return UNIT_TYPE*
         * Returns a pointer to the padding bytes.  Returns NULL if no
         * padding is necessary or if an error occurs.
         */
    _Success_(return != nullptr)
        _Post_readable_byte_size_(*pNumPadBytesOut) UNIT_TYPE* GetPadBytes(_Inout_ HRESULT* hr, _Out_opt_ size_t* pNumPadBytesOut)
    {
        return GetPadBytes(BaseFile::DefaultAlignment, hr, pNumPadBytesOut);
    }
};

typedef SectionParserBase<const void, const BYTE> SectionParser;
typedef SectionParserBase<void, BYTE> SectionBuilderParser;

#define _SECTION_PARSER_NEXT_ARRAY(D, N, T, S) ((SUCCEEDED(*S)) ? static_cast<const T*>((D).GetNext((N), sizeof(T), S)) : NULL)
#define _SECTION_PARSER_NEXT(D, T, S) _SECTION_PARSER_NEXT_ARRAY(D, 1, T, S)

#define _SECTION_BUILDER_NEXT_ARRAY(D, N, T, S) ((SUCCEEDED(*S)) ? static_cast<T*>((D).GetNext((N), sizeof(T), S)) : NULL)
#define _SECTION_BUILDER_NEXT(D, T, S) _SECTION_BUILDER_NEXT_ARRAY(D, 1, T, S)

inline void _SECTION_BUILDER_PAD(_In_ SectionBuilderParser* pData, size_t align, _In_ HRESULT* hr)
{
    if (SUCCEEDED(*hr))
    {
        size_t nPadBytes = 0;
        BYTE* pPad = pData->GetPadBytes(align, hr, &nPadBytes);
        if (pPad != nullptr)
        {
            while (nPadBytes--)
            {
                *pPad++ = 0;
            }
        }
    }
}

inline void _SECTION_BUILDER_PAD(_In_ SectionBuilderParser* pData, _In_ HRESULT* hr)
{
    _SECTION_BUILDER_PAD(pData, BaseFile::DefaultAlignment, hr);
}

} // namespace Microsoft::Resources
