// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

//------------------------------------------------------------------
// File: ISectionBuilder.h
//
// ISectionBuilder interface declaration. This is an abstract class and cannot be instantiated.
//------------------------------------------------------------------

#pragma once

namespace Microsoft::Resources::Build
{

/*!
     * \addtogroup DefBuild
     * @{
     * \addtogroup DefBuild_Common
     * @{
     * \defgroup DataSectionBuilder Data BLOB section builder
     * @{
     */

//
// Memory linked list buffer
// memory layout
// MEM_LINKED_DATABLOB
// BYTE[1M].
typedef struct _MEM_LINKED_DATABLOB
{
    bool fIsGivenData;
    UINT32 nSize;
    BYTE* pData; // next address after the structure
    struct _MEM_LINKED_DATABLOB* pNext;
} MEM_LINKED_DATABLOB;

class DataBlobBuilder : public DefObject
{
protected:
    MEM_LINKED_DATABLOB* m_pHeadDataList;
    mutable MEM_LINKED_DATABLOB* m_pCurDataList;
    UINT32 m_offset;
    static const UINT32 maxListBufferSize = 1024 * 1024; // 1M

protected:
    DataBlobBuilder();

    HRESULT Init();

public:
    /*!
        * \name Constructors & Destructors
        * @{
        */

    static HRESULT CreateInstance(_Outptr_ DataBlobBuilder** result);

    virtual ~DataBlobBuilder();

    /*!@}*/

    /*!
         * Copies the specified data to the data segment and
         * returns the offset at which it was added.  Does not
         * check to see if the value is already in the buffer.
         */
    virtual HRESULT AddData(__in_bcount(cbData) const BYTE* pData, __in UINT32 cbData, __out UINT32* pWrittenOffset);

    /*!
        * Appends the specified data to the data segment as
        * a reference, and
        * returns the offset at which it was added.  Does not
        * check to see if the value is already in the buffer.
        */
    virtual HRESULT AddDataAsReference(__in_bcount(cbData) const BYTE* pData, __in UINT32 cbData, __out UINT32* pWrittenOffset);

    /*!
         * Iterates through the data list entries and returns true if the given pData with size cbData 
         * is present at offset dataBlobBuilderOffset.
         * Returns false otherwise.
         */
    bool TryFindData(__in_bcount(cbData) const BYTE* pData, __in UINT32 cbData, __in UINT32 dataBlobBuilderOffset) const;

    bool TryGetStringData(__in UINT32 offset, __inout StringResult* pStringOut) const;

    bool TryGetBlobData(__in UINT32 offset, __in UINT32 cbData, __inout BlobResult* pBlobOut) const;

    virtual UINT32 GetCurrentDataSize() const { return m_offset; }

    virtual UINT32 GetMaxSizeInBytesOfDataBlob() const;

    virtual HRESULT BuildDataBlob(__out_bcount(cbBuffer) VOID* pBuffer, __in UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const;
};

//! \ref ISectionBuilder "Section Builder" for a generic data section.
class DataSectionBuilder : public DataBlobBuilder, public ISectionBuilder
{
private:
    BaseFile::SectionIndex m_sectionIndex;

protected:
    DataSectionBuilder();

public:
    /*!
        * \name Constructors & Destructors
        * @{
        */
    static HRESULT CreateInstance(_Outptr_ DataSectionBuilder** result);

    virtual ~DataSectionBuilder();

    /*!
         * \name ISectionBuilder Implementation
         * @{
         */

    //! Implements ISectionBuilder::IsValid
    bool IsValid() const { return true; }

    //! Implements ISectionBuilder::Finalize
    HRESULT Finalize();

    //! Implements ISectionBuilder::GetMaxSizeInBytes
    //! ISectionBuilder::GetMaxSizeInBytes uses implementation in DataBlobBuilder
    //   Override in this class if necessary.
    UINT32 GetMaxSizeInBytes() const;

    //! Implements ISectionBuilder::Build
    //! ISectionBuilder::Build implemented uses implementation in DataBlobBuilder
    //   Override in this class if necessary.
    HRESULT Build(__out_bcount(cbBuffer) VOID* pBuffer, __in UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const;

    //! Implements ISectionBuilder::GetSectionType
    DEFFILE_SECTION_TYPEID GetSectionType() const { return gDataSectionType; }

    //! Implements ISectionBuilder::GetFlags
    UINT16 GetFlags() const { return 0; }

    //! Implements ISectionBuilder::GetSectionFlags
    UINT16 GetSectionFlags() const { return 0; }

    //! Implements ISectionBuilder::GetSectionQualifier
    UINT32 GetSectionQualifier() const { return 0; }

    //! Implements ISectionBuilder::SetSectionIndex
    void SetSectionIndex(BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }

    //! Implements ISectionBuilder::GetSectionIndex
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

    /*!@}*/
};

class DataItemsSectionBuilder : public ISectionBuilder
{
private:
    bool m_finalized;
    BaseFile::SectionIndex m_sectionIndex;

    struct ItemRef
    {
        int offset;
        int cbData;
    };

    int m_numSmallItems;
    int m_sizeSmallItems;
    int m_cbSmallItemDataUsed;
    int m_cbSmallItemDataCapacity;

    __ecount(m_sizeSmallItems) struct ItemRef* m_pSmallItems;
    __bcount(m_cbSmallItemDataCapacity) BYTE* m_pSmallItemData;

    int m_numLargeItems;
    int m_sizeLargeItems;
    int m_cbLargeItemDataUsed;
    int m_cbLargeItemDataCapacity;

    __ecount(m_sizeLargeItems) struct ItemRef* m_pLargeItems;
    __bcount(m_cbLargeItemDataCapacity) BYTE* m_pLargeItemData;

    static const unsigned int InitialSmallItemSize = 32;
    static const unsigned int InitialSmallItemDataCapacity = 1024;

    static const unsigned int InitialLargeItemSize = 32;
    static const unsigned int InitialLargeItemDataCapacity = 1024;

    DataItemsSectionBuilder();

    HRESULT EnsureLargeItemCapacity(__in int cbTotal);
    HRESULT EnsureSmallItemCapacity(__in int cbTotal);

public:
    /*!
        * \name Constructors & Destructors
        * @{
        */

    static HRESULT CreateInstance(_Outptr_ DataItemsSectionBuilder** result);

    virtual ~DataItemsSectionBuilder();

    typedef struct _PrebuildItemReference
    {
        bool isLarge;
        int index;
    } PrebuildItemReference;

    typedef struct _BuiltItemReference
    {
        UINT16 fileIndex;
        UINT16 sectionIndex;
        UINT32 itemIndex;
    } BuiltItemReference;

    static const int DefaultAlignment = BaseFile::Align32Bit; // align to 32-bit boundary by default

    /*!
         * Copies the specified data to the data segment and
         * returns the offset at which it was added.  Forces
         * alignment to the specified boundary.  Does not
         * check to see if the value is already in the buffer.
         */
    HRESULT AddDataItem(
        __in_bcount(cbData) const VOID* pData,
        __in UINT32 cbData,
        __in int align, // 1, 2, 4 or 8
        __out PrebuildItemReference* pRefOut);

    HRESULT AddDataItem(__in_bcount(cbData) const VOID* pData, __in UINT32 cbData, __out PrebuildItemReference* pRefOut)
    {
        return AddDataItem(pData, cbData, DefaultAlignment, pRefOut);
    }

    /*!
         * Copies the specified string to the data segment (including
         * null-terminator) and returns the offset at which it was
         * added.  Does not check to see if the value is already in
         * the buffer.
         */
    HRESULT AddDataString(__in PCWSTR pString, __out PrebuildItemReference* pRefOut);

    /*! 
         * Copies the specified string to the data segment (including
         * null-terminator), to a supplied maximum length.  Fails
         * if the string exceeds the supplied length.
         *
         * Returns the offset at which it was added.  Does not check
         * to see if the value is already in the buffer.
         *
         * \return HRESULT
         */
    HRESULT AddDataString(__in_ecount(cchString) PCWSTR pString, __in int cchString, __out PrebuildItemReference* pRefOut);

    /*! 
         * Turns a PrebuildItemReference into a BuiltItemReference
         * that can be used to construct an instance locator.
         * 
         * \return HRESULT
         */
    HRESULT GetBuiltItemInfo(__in const PrebuildItemReference* pPrebuildReference, __out BuiltItemReference* pRefOut) const;

    /*! 
         * Return string by its item index. It ignore large index or not since the item index 
         * indicate whether it is large or not.
         * 
         * \return HRESULT
         */

    HRESULT GetDataBlob(_In_ int itemIndex, _Inout_ BlobResult* pBlobResult) const;

    /*!
         * \name ISectionBuilder Implementation
         * @{
         */

    bool IsValid() const { return true; }

    HRESULT Finalize();

    UINT32 GetMaxSizeInBytes() const;

    HRESULT Build(__out_bcount(cbBuffer) VOID* pBuffer, __in UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return gDataItemsSectionType; }

    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }
};

} // namespace Microsoft::Resources::Build