// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/common/Base.h"
#include "mrm/DefObject.h"
#include "mrm/Results.h"
#include "mrm/Atoms.h"
#include "mrm/common/file/FileBaseSections.h"

namespace Microsoft::Resources
{

typedef wil::unique_any_handle_null<decltype(&::_DefCloseHandle), ::_DefCloseHandle> unique_DefHandle;
void DefFreeMemory(void* p);
using deffree_deleter = wil::function_deleter<decltype(&DefFreeMemory), DefFreeMemory>;

template<typename T>
using unique_deffree_ptr = wistd::unique_ptr<T, deffree_deleter>;

class BaseFile;
class FileSectionResult;

/*!
     * Interface definition for section readers.  Each UID file section reader 
     * implements this interface.
     */
class IFileSection : public DefObject
{
public:
    virtual ~IFileSection() {};

    virtual DEFFILE_SECTION_TYPEID GetSectionType() const = 0;
    virtual UINT32 GetSectionQualifier() const = 0;
    virtual UINT32 GetDataSize() const = 0;
    virtual const BYTE* GetData(__out_opt UINT32* = NULL) const = 0;
    virtual HRESULT GetTotalSize(_Out_ UINT32* size) const = 0;
    virtual HRESULT GetSectionHeader(_Out_ const DEFFILE_SECTION_HEADER** header) const = 0;
    virtual DEFFILE_SECTION_INDEX GetSectionIndex() const = 0;
    virtual const BaseFile* const GetParentFile() const = 0;
    virtual UINT16 GetFlags() const = 0;
    virtual UINT16 GetSectionFlags() const = 0;
};

class BaseFileSectionResult;

/*! 
     * \defgroup DefFile_Readers Read UID-formatted files
     * @{
     * \defgroup BaseFile BaseFile: Basic file structure and utilities
     * @{
     */

class BaseFile : public DefObject
{
protected:
    UINT32 m_flags;
    DEFFILE_HEADER* m_pHeader;
    DEFFILE_TOC_ENTRY* m_pToc;
    DEFFILE_SECTION_HEADER** m_ppSections;

    // Internal values for "m_flags"
    static const UINT32 BaseFileOwnsDataFlag = 0x010000;

public:
    typedef DEFFILE_SECTION_INDEX SectionIndex;
    typedef DEFFILE_SECTION_COUNT SectionCount;

    static const SectionIndex SectionIndexNone = DEFFILE_SECTION_INDEX_NONE;
    static const SectionCount MaxSectionIndex = DEFFILE_MAX_SECTION_INDEX;
    static const SectionCount MaxSectionCount = DEFFILE_MAX_SECTION_COUNT;
    static const DEFFILE_SECTION_TYPEID SectionTypeNone;

    // Public values for "flags" parameter to constructors
    static const UINT32 DefaultFlags = 0x0000;
    static const UINT32 MapFileFlag = 0x0001;
    static const UINT32 LoadFileFlag = 0x0002;
    static const UINT32 ValidFlags = (MapFileFlag | LoadFileFlag);

    typedef enum
    {
        IsAtomPoolSection = DEFFILE_IS_ATOM_POOL_SECTION,
        IsAtomDataSection = DEFFILE_IS_ATOM_METADATA_SECTION
    } GlobalFlags;

    static HRESULT CreateInstance(__in PCWSTR pFileName, _Outptr_ BaseFile** newFile);

    static HRESULT CreateInstance(__in UINT32 flags, __in PCWSTR pFileName, _Outptr_ BaseFile** newFile);

    static HRESULT CreateInstance(
        __in UINT32 flags,
        __in_bcount(cbData) const BYTE* pData,
        __in size_t cbData,
        _Outptr_ BaseFile** newFile);

    virtual ~BaseFile();

    const DEFFILE_HEADER* GetFileHeader() const { return m_pHeader; }

    size_t GetFileSizeInBytes() const { return m_pHeader->cbTotal; }

    bool SectionIsPresent(__inout SectionIndex index) { return (index >= 0) && (index < m_pHeader->sizeToc); }

    SectionCount GetNumSections() const { return m_pHeader->sizeToc; }

    HRESULT GetToc(_Out_ const DEFFILE_TOC_ENTRY** entry) const { return GetTocEntry(0, entry); }

    HRESULT GetTocEntry(_In_ int index, _Out_ const DEFFILE_TOC_ENTRY** entry) const;

    HRESULT GetSectionHeader(_In_ int index, _Out_ const DEFFILE_SECTION_HEADER** header) const;

    HRESULT GetSectionData(_In_ int index, _Out_ const void** data, _Out_ UINT32* pcbSectionSizeOut) const;

    /*!
        * Gets the section index for the first section with the specified section type
        */
    BaseFile::SectionIndex GetFirstSectionIndex(__in DEFFILE_SECTION_TYPEID type) const;

    BaseFile::SectionIndex GetNextSectionIndex(__in BaseFile::SectionIndex startIndex, __in DEFFILE_SECTION_TYPEID type) const;

    BaseFile::SectionIndex GetSectionIndex(__in DEFFILE_SECTION_TYPEID type, __in UINT32 qualifier) const;

    HRESULT
    ValidateSection(__in DEFFILE_SECTION_INDEX sectionIndex, __in const DEFFILE_SECTION_HEADER* pHeader, __in size_t cbSectionData) const;

    virtual HRESULT GetFileSectionResultObject(_Outptr_ BaseFileSectionResult** result) const;

    virtual HRESULT GetFileSection(__in BaseFile::SectionIndex sectionIndex, __out BaseFileSectionResult* pSectionOut) const;

    /*!
         * Checks if two files are identical. Use the "identity" fields and the unique name.
        */
    bool IsIdentical(__in const BaseFile* pOther) const;
    static bool AreIdentical(__in const BaseFile* pFile1, __in const BaseFile* pFile2);

    /*!
         * Determines if two section types are equal.
         */
    static bool SectionTypesEqual(__in const DEFFILE_SECTION_TYPEID& type1, __in const DEFFILE_SECTION_TYPEID& type2)
    {
        return ((type1.ullType[0] == type2.ullType[0]) && (type1.ullType[1] == type2.ullType[1]));
    }

    static const UINT32 DefaultAlignment = DEFFILE_DEFAULT_ALIGN;
    static const UINT32 Align64Bit = 8;
    static const UINT32 Align32Bit = 4;
    static const UINT32 Align16Bit = 2;

    static bool IsValidAlignment(UINT32 alignment)
    {
        if ((alignment != Align64Bit) && (alignment != Align32Bit) && (alignment != Align16Bit))
        {
            return false;
        }
        return true;
    }

    /*!
         * Determines the amount of space used by the required structure of a DEF 
         * file (header, trailer and table-of-contents) give the number of sections
         * in the file.   The data associated with each section (including section
         * headers and trailers) is _not_ included.
         */
    static UINT32 GetStructureOverhead(__in UINT32 nSections)
    {
        return sizeof(DEFFILE_HEADER) + sizeof(DEFFILE_TRAILER) + (nSections * sizeof(DEFFILE_TOC_ENTRY));
    }

    static UINT32 GetSectionStructureOverhead() { return sizeof(DEFFILE_SECTION_HEADER) + sizeof(DEFFILE_SECTION_TRAILER); }

    static HRESULT ValidateSectionStructure(__in_bcount(cbData) const VOID* pData, __in UINT32 cbData);

    static HRESULT ValidateStructure(__in_bcount(cbData) const void* pData, __in size_t cbData);

    static bool IsValidSectionIndex(int index) { return ((index >= 0) && (index <= MaxSectionIndex)); }

    static bool IsValidSectionCount(int nSections) { return ((nSections >= 0) && (nSections <= MaxSectionCount)); }

    static inline int PadData(int size, int boundary = DefaultAlignment) { return ((size + boundary - 1) / boundary) * boundary; }

    static inline int TruncData(int size, int boundary = DefaultAlignment) { return ((size / boundary) * boundary); }

    static inline bool IsAligned(int size, int boundary = DefaultAlignment) { return (size == PadData(size, boundary)); }

    static inline int PadSectionData(int size) { return PadData(size, DefaultAlignment); }

    /*!
         * Verifies that a DEF file section contains a correct and undamaged
         * end-of-section marker.
         */
    static HRESULT ValidateSectionTrailer(__in_bcount(cbData) const void* pData, __in UINT32 cbData);

    static inline DEFFILE_TOC_ENTRY* GetToc(__in const DEFFILE_HEADER* pHdr)
    {
        return ((DEFFILE_TOC_ENTRY*)(((BYTE*)pHdr) + pHdr->tocOffset));
    }

    static inline BYTE* GetSectionData(__in const DEFFILE_HEADER* pHdr, int offset)
    {
        return ((BYTE*)(((BYTE*)pHdr) + pHdr->sectionDataOffset + offset));
    }

    static inline UINT32 GetSectionDataSize(__in const DEFFILE_TOC_ENTRY* pToc)
    {
        return pToc->cbSectionTotal - GetSectionStructureOverhead();
    }

    static DEFFILE_SECTION_HEADER* GetSectionHeader(__in const DEFFILE_HEADER* pHdr, __in const DEFFILE_TOC_ENTRY* pToc)
    {
        if (pHdr && pToc)
        {
            return ((DEFFILE_SECTION_HEADER*)GetSectionData(pHdr, pToc->offset));
        }
        return NULL;
    }

    static void* GetSectionData(__in const DEFFILE_HEADER* pHdr, __in const DEFFILE_TOC_ENTRY* pToc)
    {
        return ((void*)&GetSectionHeader(pHdr, pToc)[1]);
    }

    static HRESULT GetSectionData(_In_ const DEFFILE_SECTION_HEADER* pHeader, _Out_ const void** data, _Out_ UINT32* pcbSectionDataSizeOut);

    static DEFFILE_SECTION_TRAILER* GetSectionTrailer(__in const DEFFILE_SECTION_HEADER* pHdr)
    {
        if (!pHdr)
        {
            return NULL;
        }
        return ((DEFFILE_SECTION_TRAILER*)(((BYTE*)pHdr) + PadSectionData(pHdr->cbSectionTotal) - sizeof(DEFFILE_SECTION_TRAILER)));
    }

    static inline DEFFILE_TRAILER* GetFileTrailer(__in DEFFILE_HEADER* pHdr)
    {
        return ((DEFFILE_TRAILER*)(((BYTE*)pHdr) + PadSectionData(pHdr->cbTotal) - sizeof(DEFFILE_TRAILER)));
    }

    static HRESULT LoadFileData(
        _In_ PCWSTR pFileName,
        _Out_ size_t* pcbDataOut,
        _Outptr_result_buffer_maybenull_(*pcbDataOut) VOID** ppDataOut);

    HRESULT GetFileData(_Inout_ BlobResult* pBlobOut) const { return pBlobOut->SetRef(m_pHeader, m_pHeader->cbTotal); }

    static HRESULT MapFileData(
        _In_ PCWSTR pFileName,
        _Out_ size_t* pcbDataOut,
        _Outptr_result_buffer_maybenull_(*pcbDataOut) const VOID** ppDataOut);

    static void UnmapFileData(_In_ const VOID* pMappedData);

protected:
    BaseFile() : m_flags(0), m_pHeader(NULL), m_pToc(NULL), m_ppSections(NULL) {}

    HRESULT Init(__in UINT32 flags, __in PCWSTR pFileName);

    HRESULT Init(__in UINT32 flags, __in_bcount(cbData) const BYTE* pData, __in size_t cbData);

    HRESULT InitFromData(__in_bcount(cbData) const void* pData, __in size_t cbData);

    HRESULT UnmapFileData();

    static HRESULT ValidateTocEntryAgainstSectionData(__in const DEFFILE_TOC_ENTRY* pToc, __in const DEFFILE_SECTION_HEADER* pHeader);
};

class FileSectionBase : public IFileSection
{
protected:
    DEFFILE_SECTION_INDEX m_sectionIndex;
    const DEFFILE_SECTION_HEADER* m_pSectionHeader;
    const BaseFile* m_pParentFile;

    FileSectionBase();

    HRESULT
    Init(
        __in_opt const IFileSection* const pSection,
        __in_bcount(cbData) const void* const pData,
        __in int cbData,
        __in const DEFFILE_SECTION_TYPEID& type);

    HRESULT Init(__in_opt const IFileSection* const pSection, __in_bcount(cbData) const void* const pData, __in int cbData);

    virtual ~FileSectionBase();

public: // IFileSection implementation
    virtual DEFFILE_SECTION_TYPEID GetSectionType() const;
    virtual UINT32 GetSectionQualifier() const;
    virtual UINT32 GetDataSize() const;
    virtual const BYTE* GetData(__out_opt UINT32* pcbData = NULL) const;
    virtual HRESULT GetTotalSize(_Out_ UINT32* size) const;
    virtual HRESULT GetSectionHeader(_Out_ const DEFFILE_SECTION_HEADER** header) const;
    virtual DEFFILE_SECTION_INDEX GetSectionIndex() const;
    virtual const BaseFile* const GetParentFile() const;
    virtual UINT16 GetFlags() const;
    virtual UINT16 GetSectionFlags() const;
};

class BaseFileSectionResult : public FileSectionBase
{
public:
    BaseFileSectionResult();
    virtual ~BaseFileSectionResult() {}

    static HRESULT CreateInstance(_Outptr_ BaseFileSectionResult** result);

    HRESULT SetSectionIndex(__in const BaseFile* pParentFile, __in BaseFile::SectionIndex sectionIndex);
};

} // namespace Microsoft::Resources
