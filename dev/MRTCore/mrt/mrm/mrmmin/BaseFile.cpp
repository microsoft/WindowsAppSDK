// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources
{

const DEFFILE_SECTION_TYPEID BaseFile::SectionTypeNone = {0};

static bool IsFileOnFixedDrive(_In_ PCWSTR filePath)
{
    WCHAR drive[3] = {};
    if ((filePath != nullptr) && (filePath[0] != 0) && (filePath[1] != 0))
    {
        drive[0] = filePath[0];
        drive[1] = filePath[1];

        UINT driveType = _DefGetDriveTypeW(drive);
        if ((driveType == DRIVE_FIXED) || (driveType == DRIVE_UNKNOWN) || (driveType == DRIVE_NO_ROOT_DIR))
        {
            // Default to true even if we somehow cannot figure out the type
            return true;
        }
        else
        {
            return false;
        }
    }

    // default to true
    return true;
}

BaseFileSectionResult::BaseFileSectionResult() : FileSectionBase() {}

HRESULT BaseFileSectionResult::CreateInstance(_Outptr_ BaseFileSectionResult** result)
{
    BaseFileSectionResult* pFileSectionResult = new BaseFileSectionResult();
    RETURN_IF_NULL_ALLOC(pFileSectionResult);

    *result = pFileSectionResult;

    return S_OK;
}

HRESULT BaseFileSectionResult::SetSectionIndex(__in const BaseFile* pParentFile, __in BaseFile::SectionIndex sectionIndex)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pParentFile);

    m_pParentFile = pParentFile;
    m_sectionIndex = sectionIndex;
    RETURN_IF_FAILED(m_pParentFile->GetSectionHeader(sectionIndex, &m_pSectionHeader));

    return S_OK;
}

HRESULT BaseFile::GetFileSectionResultObject(_Outptr_ BaseFileSectionResult** result) const
{
    return BaseFileSectionResult::CreateInstance(result);
}

HRESULT BaseFile::GetFileSection(__in BaseFile::SectionIndex sectionIndex, __out BaseFileSectionResult* pSectionOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pSectionOut);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), !IsValidSectionIndex(sectionIndex));

    RETURN_IF_FAILED(pSectionOut->SetSectionIndex(this, sectionIndex));

    return S_OK;
}

HRESULT BaseFile::InitFromData(__in_bcount(cbData) const void* pData, __in size_t cbData)
{
    DEFFILE_HEADER* pHeader = (DEFFILE_HEADER*)pData;
    int i;
    BYTE* pSectionData;

    RETURN_IF_FAILED(ValidateStructure(pData, cbData));

    m_pHeader = pHeader;
    m_pToc = GetToc(pHeader);
    m_ppSections = _DefArray_Alloc(DEFFILE_SECTION_HEADER*, pHeader->sizeToc);
    RETURN_IF_NULL_ALLOC(m_ppSections);

    pSectionData = GetSectionData(pHeader, 0);
    for (i = 0; i < pHeader->sizeToc; i++)
    {
        m_ppSections[i] = (DEFFILE_SECTION_HEADER*)&pSectionData[m_pToc[i].offset];
    }
    return S_OK;
}

HRESULT
BaseFile::LoadFileData(_In_ PCWSTR pFileName, _Out_ size_t* pcbDataOut, _Outptr_result_buffer_maybenull_(*pcbDataOut) VOID** ppDataOut)
{
    unique_DefHandle hFile;
    DWORD cbData = 0;
    DWORD cbRead = 0;
    LARGE_INTEGER fileLen = {0};

    DEF_ASSERT((pcbDataOut != NULL) && (ppDataOut != NULL));

    *pcbDataOut = 0;
    *ppDataOut = nullptr;

    RETURN_IF_FAILED((_DefCreateFile(pFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, &hFile)));

    RETURN_IF_FAILED(_DefGetFileSizeEx(hFile.get(), &fileLen));

    cbData = (UINT32)fileLen.LowPart;
    unique_deffree_ptr<VOID> pBaseFileData(_DefBlob_AllocZeroed(cbData));
    RETURN_IF_NULL_ALLOC(pBaseFileData.get());

    RETURN_IF_FAILED(_DefReadFile(hFile.get(), pBaseFileData.get(), cbData, &cbRead));

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), cbRead != cbData);

    *pcbDataOut = cbData;
    *ppDataOut = pBaseFileData.release();

    return S_OK;
}

HRESULT
BaseFile::MapFileData(_In_ PCWSTR pFileName, _Out_ size_t* pcbDataOut, _Outptr_result_buffer_maybenull_(*pcbDataOut) const VOID** ppDataOut)
{
    unique_DefHandle hFile;
    unique_DefHandle hMapping;
    PVOID pBaseFileData = NULL;
    LARGE_INTEGER fileLen = {0};

    DEF_ASSERT((pcbDataOut != NULL) && (ppDataOut != NULL));

    *pcbDataOut = 0;
    *ppDataOut = nullptr;

    RETURN_IF_FAILED(_DefCreateFile(pFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, &hFile));
    RETURN_IF_FAILED(_DefGetFileSizeEx(hFile.get(), &fileLen));
    RETURN_IF_FAILED(_DefCreateFileMapping(hFile.get(), NULL, PAGE_READONLY, 0, 0, NULL, &hMapping));
    RETURN_IF_FAILED(_DefMapViewOfFile(hMapping.get(), FILE_MAP_READ, 0, 0, 0, &pBaseFileData));

    *pcbDataOut = fileLen.QuadPart;
    *ppDataOut = pBaseFileData;

    return S_OK;
}

void BaseFile::UnmapFileData(_In_ const VOID* pData)
{
    DEF_ASSERT(pData != NULL);
    _DefUnmapViewOfFile(const_cast<VOID*>(pData));
}

HRESULT BaseFile::UnmapFileData()
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pHeader);
    RETURN_HR_IF(E_DEF_NOT_READY, ((m_flags & (BaseFileOwnsDataFlag | MapFileFlag)) != (BaseFileOwnsDataFlag | MapFileFlag)));

    UnmapFileData(m_pHeader);
    m_pHeader = NULL;
    return S_OK;
}

HRESULT BaseFile::CreateInstance(__in PCWSTR pFileName, _Outptr_ BaseFile** newFile) { return CreateInstance(0, pFileName, newFile); }

HRESULT BaseFile::CreateInstance(__in UINT32 flags, __in PCWSTR pFileName, _Outptr_ BaseFile** newFile)
{
    *newFile = nullptr;

    AutoDeletePtr<BaseFile> pRtrn = new BaseFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(flags, pFileName));

    *newFile = pRtrn.Detach();
    return S_OK;
}

HRESULT BaseFile::CreateInstance(__in UINT32 flags, __in_bcount(cbData) const BYTE* pData, __in size_t cbData, _Outptr_ BaseFile** newFile)
{
    *newFile = nullptr;

    AutoDeletePtr<BaseFile> pRtrn = new BaseFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(flags, pData, cbData));

    *newFile = pRtrn.Detach();
    return S_OK;
}

HRESULT BaseFile::Init(__in UINT32 flags, __in PCWSTR pFileName)
{
    DEF_ASSERT((pFileName != NULL) && (pFileName[0] != L'\0'));

    RETURN_HR_IF(E_INVALIDARG, (flags & ~ValidFlags) != 0);

    bool isMapped = ((flags & MapFileFlag) != 0);
    size_t cbData = 0;
    union
    {
        const VOID* pcData;
        VOID* pData;
    } data;
    data.pData = NULL;

    if (isMapped)
    {
        // We will load the file if it's on removable drive so that removal of the drive will not
        // cause exception on data accessing. The perf will be worse. But the perf on removable
        // drive is not great to start with.
        isMapped = IsFileOnFixedDrive(pFileName);
    }

    HRESULT hr = (isMapped ? MapFileData(pFileName, &cbData, &data.pcData) : LoadFileData(pFileName, &cbData, &data.pData));
    RETURN_IF_FAILED(hr);

    hr = InitFromData(data.pcData, cbData);
    if (SUCCEEDED(hr))
    {
        m_flags = (flags | BaseFileOwnsDataFlag);
    }
    else if (isMapped)
    {
        UnmapFileData(data.pcData);
    }
    else
    {
        Def_Free(data.pData);
    }

    return hr;
}

HRESULT BaseFile::Init(__in UINT32 flags, __in_bcount(cbData) const BYTE* pData, __in size_t cbData)
{
    m_flags = flags;

    RETURN_HR_IF_NULL(E_INVALIDARG, pData);
    RETURN_IF_FAILED(InitFromData(pData, cbData));

    return S_OK;
}

BaseFile::SectionIndex BaseFile::GetFirstSectionIndex(__in DEFFILE_SECTION_TYPEID type) const
{
    DEFFILE_SECTION_INDEX sectionIndex;
    DEFFILE_TOC_ENTRY* pToc;

    if (m_pHeader != NULL)
    {
        // look for the section that is of interest in TOC
        for (pToc = m_pToc, sectionIndex = 0; sectionIndex < m_pHeader->sizeToc; sectionIndex++, pToc++)
        {
            if (pToc->cbSectionTotal == 0)
            {
                continue;
            }
            if (SectionTypesEqual(pToc->type, type))
            {
                return sectionIndex;
            }
        }
    }

    return BaseFile::SectionIndexNone;
}

BaseFile::SectionIndex BaseFile::GetNextSectionIndex(__in BaseFile::SectionIndex startIndex, __in DEFFILE_SECTION_TYPEID type) const
{
    BaseFile::SectionIndex i;
    DEFFILE_TOC_ENTRY* pToc;

    if ((startIndex < 0) || (m_pHeader == NULL) || (startIndex >= m_pHeader->sizeToc))
    {
        return -1;
    }

    // look for the section that is of interest in TOC
    for (pToc = (m_pToc + startIndex + 1), i = startIndex + 1; i < m_pHeader->sizeToc; i++, pToc++)
    {
        if (pToc->cbSectionTotal == 0)
        {
            continue;
        }
        if (SectionTypesEqual(pToc->type, type))
        {
            return i;
        }
    }

    return -1;
}

BaseFile::SectionIndex BaseFile::GetSectionIndex(__in DEFFILE_SECTION_TYPEID type, __in UINT32 qualifier) const
{
    DEFFILE_SECTION_INDEX sectionIndex;
    DEFFILE_TOC_ENTRY* pToc;

    if (m_pHeader != NULL)
    {
        // look for the section that is of interest in TOC
        for (pToc = m_pToc, sectionIndex = 0; sectionIndex < m_pHeader->sizeToc; sectionIndex++, pToc++)
        {
            if (pToc->cbSectionTotal == 0)
            {
                continue;
            }
            if (SectionTypesEqual(pToc->type, type) && (pToc->qualifier == qualifier))
            {
                return sectionIndex;
            }
        }
    }

    return BaseFile::SectionIndexNone;
}

HRESULT BaseFile::GetTocEntry(__in int index, _Out_ const DEFFILE_TOC_ENTRY** entry) const
{
    *entry = nullptr;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pHeader);
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_pHeader->sizeToc - 1));

    *entry = &m_pToc[index];

    return S_OK;
}

HRESULT BaseFile::GetSectionHeader(__in int index, _Out_ const DEFFILE_SECTION_HEADER** header) const
{
    *header = nullptr;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pHeader);
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_pHeader->sizeToc - 1));

    const DEFFILE_SECTION_HEADER* pSectionHeader = GetSectionHeader(m_pHeader, &m_pToc[index]);
    if (!pSectionHeader)
    {
        return S_OK;
    }

    DEF_ASSERT(m_pHeader->sizeToc != 0);
    UINT32 cbOtherSectionSize = m_pHeader->tocOffset + sizeof(DEFFILE_TRAILER);
    cbOtherSectionSize += (sizeof(DEFFILE_TOC_ENTRY) * m_pHeader->sizeToc);
    cbOtherSectionSize += ((m_pHeader->sizeToc - 1) * BaseFile::GetSectionStructureOverhead());

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), cbOtherSectionSize >= m_pHeader->cbTotal);

    UINT32 maxSize = m_pHeader->cbTotal - cbOtherSectionSize;
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), pSectionHeader->cbSectionTotal > maxSize);

    *header = pSectionHeader;

    return S_OK;
}

HRESULT
BaseFile::GetSectionData(_In_ int index, _Out_ const void** data, _Out_ UINT32* pcbSectionSizeOut) const
{
    *data = nullptr;

    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pHeader);
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_pHeader->sizeToc - 1));
    RETURN_HR_IF_NULL(E_INVALIDARG, pcbSectionSizeOut);

    *pcbSectionSizeOut = GetSectionDataSize(&m_pToc[index]);
    *data = GetSectionData(m_pHeader, &m_pToc[index]);

    return S_OK;
}

bool BaseFile::IsIdentical(__in const BaseFile* pOther) const
{
    if (pOther == NULL)
    {
        return FALSE;
    }
    // TODO: compare file identities for real
    return (pOther == this);
}

bool BaseFile::AreIdentical(__in const BaseFile* pFile1, __in const BaseFile* pFile2)
{
    if (pFile1 == pFile2)
        return true;
    if ((pFile1 == NULL) || (pFile2 == NULL))
        return false;
    return pFile1->IsIdentical(pFile2);
}

HRESULT BaseFile::ValidateStructure(__in_bcount(cbData) const void* pData, __in size_t cbData)
{
    DEFFILE_HEADER* pHeader = (DEFFILE_HEADER*)pData;
    DEFFILE_TRAILER* pTrailer = NULL;
    DEFFILE_TOC_ENTRY* pToc;
    size_t minSize = sizeof(DEFFILE_HEADER) + sizeof(DEFFILE_TRAILER);
    BYTE* pSectionData;
    UINT32 cbSectionData;

    // basic sanity checks:
    // 1) Do we even have enough data to hold header and trailer
    // 2) If so, the BLOB should begin with at HEADER.  If we assume
    //    that it does, is our byte count reasonable?
    RETURN_HR_IF_NULL(E_INVALIDARG, pData);

    // make sure we have a full header before dereferencing pHeader
    // and make sure the header is at least plausible
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), (cbData < minSize) || (cbData < pHeader->cbTotal) || (pHeader->cbTotal < minSize));

    // Header is potentially valid.  Look for a matching trailer.
    pTrailer = GetFileTrailer(pHeader);
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE),
        (pTrailer->marker != DEFFILE_FILE_END_MARKER) || (pHeader->magic.ullMagic != pTrailer->magic.ullMagic) ||
            (pHeader->cbTotal != pTrailer->cbTotal));

    // Okay, this sure _looks_ like a DEF file.  Do we have a TOC?
    size_t cbToc = sizeof(DEFFILE_TOC_ENTRY) * pHeader->sizeToc;
    minSize = pHeader->tocOffset + cbToc + sizeof(DEFFILE_TRAILER);
    // Don't have enough room for the header, TOC & trailer?
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), pHeader->cbTotal < minSize);

    // Is the TOC plausible
    // TOC clobbers the header or is improperly aligned?
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), (pHeader->tocOffset < sizeof(DEFFILE_HEADER)) || (!IsAligned(pHeader->tocOffset)));

    // NOTE: The trailer check (third condition) doesn't add much value since we validate
    // the sections individually anyway. But we poke that page already as part of the validation,
    // so it is essentially free. Therefore we keep it.
    // Section data clobbers the header, is improperly aligned or extends past the end of the file?
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE),
        (pHeader->sectionDataOffset < pHeader->tocOffset + cbToc) || (!IsAligned(pHeader->sectionDataOffset)) ||
            (pHeader->sectionDataOffset >= (pHeader->cbTotal - sizeof(DEFFILE_TRAILER))));

    // TOC is plausible. Check each entry.
    // Section data begins after the last TOC entry and cannot extend into the file trailer.
    // We do not validate the the invidiual sections now since it would end up paging in a lot of
    // the file. Instead we validate the sections when they are initialized and only check the TOC here.
    pToc = GetToc(pHeader);
    pSectionData = GetSectionData(pHeader, 0);
    cbSectionData = static_cast<UINT32>((reinterpret_cast<BYTE*>(pTrailer) - static_cast<BYTE*>(pSectionData)));

    for (int i = 0; i < pHeader->sizeToc; i++)
    {
        // Sanity check our size and offset.
        DEFFILE_TOC_ENTRY* pCurrentToc = &pToc[i];

        // NULL entries are allowed, so only check if the offset or section size is not zero.
        if ((pCurrentToc->cbSectionTotal != 0) || (pCurrentToc->offset != 0))
        {

            RETURN_HR_IF(
                HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE),
                (pCurrentToc->offset > cbSectionData) ||
                    (pCurrentToc->cbSectionTotal < sizeof(DEFFILE_SECTION_HEADER) + sizeof(DEFFILE_SECTION_TRAILER)) ||
                    (pCurrentToc->cbSectionTotal > cbSectionData) || (pCurrentToc->offset + pCurrentToc->cbSectionTotal > cbSectionData));
        }
    }

    return S_OK;
}

HRESULT BaseFile::ValidateSection(
    __in DEFFILE_SECTION_INDEX sectionIndex,
    __in const DEFFILE_SECTION_HEADER* pHeader,
    __in size_t cbSectionData) const
{
    // >= because it's 0-indexed.
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), sectionIndex < 0 || sectionIndex >= m_pHeader->sizeToc);

    if (cbSectionData == 0)
    {
        // We allow zero-size sections.
        return S_OK;
    }

    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), pHeader);

    RETURN_IF_FAILED(ValidateTocEntryAgainstSectionData(&m_pToc[sectionIndex], pHeader));

    return S_OK;
}

HRESULT BaseFile::GetSectionData(_In_ const DEFFILE_SECTION_HEADER* pHeader, _Out_ const void** data, _Out_ UINT32* pcbSectionDataSizeOut)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pHeader);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), (pHeader->cbSectionTotal < GetSectionStructureOverhead()));

    *pcbSectionDataSizeOut = pHeader->cbSectionTotal - GetSectionStructureOverhead();
    *data = &pHeader[1];

    return S_OK;
}

HRESULT BaseFile::ValidateSectionStructure(__in_bcount(cbData) const VOID* pData, __in UINT32 cbData)
{
    // All we can do to generically validate a section is
    // make sure that there's a trailer where we expect
    // it and that it refers back to the header.
    return ValidateSectionTrailer(pData, cbData);
}

HRESULT BaseFile::ValidateTocEntryAgainstSectionData(__in const DEFFILE_TOC_ENTRY* pToc, __in const DEFFILE_SECTION_HEADER* pHeader)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pToc);
    RETURN_HR_IF_NULL(E_INVALIDARG, pHeader);

    if ((pToc->cbSectionTotal == 0) && (pToc->offset == 0))
    {
        // NULL entries are allowed
        return S_OK;
    }

    // TOC entry and header must match exactly.
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE),
        (!SectionTypesEqual(pToc->type, pHeader->type)) || (pToc->cbSectionTotal != pHeader->cbSectionTotal) ||
            (pToc->qualifier != pHeader->qualifier) || (pToc->flags != pHeader->flags) || (pToc->sectionFlags != pHeader->sectionFlags));

    // header and trailer must match exactly
    DEFFILE_SECTION_TRAILER* pTrailer = GetSectionTrailer(pHeader);
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE),
        (pTrailer->marker != DEFFILE_SECTION_END_MARKER) || (pTrailer->cbSectionTotal != pHeader->cbSectionTotal));

    return S_OK;
}

HRESULT
BaseFile::ValidateSectionTrailer(__in_bcount(cbData) const void* pData, __in UINT32 cbData)
{
    DEFFILE_SECTION_HEADER* pHeader = (DEFFILE_SECTION_HEADER*)pData;
    DEFFILE_SECTION_TRAILER* pTrailer = NULL;

    RETURN_HR_IF_NULL(E_INVALIDARG, pData);
    RETURN_HR_IF(E_INVALIDARG, cbData < sizeof(DEFFILE_SECTION_HEADER) + sizeof(DEFFILE_SECTION_TRAILER));
    RETURN_HR_IF(E_INVALIDARG, pHeader->cbSectionTotal > cbData);

    pTrailer = GetSectionTrailer(pHeader);
    if ((pTrailer->marker == DEFFILE_SECTION_END_MARKER) && (pTrailer->cbSectionTotal == pHeader->cbSectionTotal))
    {
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
}

BaseFile::~BaseFile()
{
    if (m_ppSections)
    {
        _DefFree(m_ppSections);
    }

    // Delete m_pHeader if BaseFile owns them.
    if (m_pHeader && (m_flags & BaseFileOwnsDataFlag))
    {
        if (m_flags & MapFileFlag)
        {
            UnmapFileData();
        }
        else
        {
            _DefFree(m_pHeader);
        }
        m_pHeader = NULL;
    }
}

FileSectionBase::~FileSectionBase() {}

FileSectionBase::FileSectionBase() : m_pParentFile(NULL), m_sectionIndex(DEFFILE_SECTION_INDEX_NONE), m_pSectionHeader(NULL) {}

HRESULT FileSectionBase::Init(
    __in_opt const IFileSection* const pSection,
    __in_bcount(cbData) const void* const pData,
    __in int cbData,
    __in const DEFFILE_SECTION_TYPEID& type)
{
    if (pSection != nullptr)
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), !BaseFile::SectionTypesEqual(pSection->GetSectionType(), type));
    }

    RETURN_IF_FAILED(Init(pSection, pData, cbData));

    return S_OK;
}

HRESULT
FileSectionBase::Init(__in_opt const IFileSection* const pSection, __in_bcount(cbData) const void* const /* pData */, __in int cbData)
{
    // Note: We don't fail for empty pdata and cbData = 0
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), cbData < 0);

    if (pSection != nullptr)
    {
        m_pParentFile = pSection->GetParentFile();
        m_sectionIndex = pSection->GetSectionIndex();
        RETURN_IF_FAILED(pSection->GetSectionHeader(&m_pSectionHeader));

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), cbData > pSection->GetDataSize());

        if (m_pParentFile != nullptr)
        {
            RETURN_IF_FAILED(m_pParentFile->ValidateSection(m_sectionIndex, m_pSectionHeader, cbData));
        }
    }
    return S_OK;
}

DEFFILE_SECTION_TYPEID
FileSectionBase::GetSectionType() const { return (m_pSectionHeader ? m_pSectionHeader->type : BaseFile::SectionTypeNone); }

UINT16
FileSectionBase::GetFlags() const { return (m_pSectionHeader ? m_pSectionHeader->flags : 0); }

UINT16
FileSectionBase::GetSectionFlags() const { return (m_pSectionHeader ? m_pSectionHeader->sectionFlags : 0); }

UINT32
FileSectionBase::GetSectionQualifier() const { return (m_pSectionHeader ? m_pSectionHeader->qualifier : 0); }

UINT32
FileSectionBase::GetDataSize() const
{
    if ((m_pSectionHeader == NULL) || (m_pSectionHeader->cbSectionTotal < BaseFile::GetSectionStructureOverhead()))
    {
        return 0;
    }

    return (m_pSectionHeader->cbSectionTotal - BaseFile::GetSectionStructureOverhead());
}

const BYTE* FileSectionBase::GetData(__out_opt UINT32* pcbData) const
{
    if ((m_pSectionHeader == NULL) || (m_pSectionHeader->cbSectionTotal < BaseFile::GetSectionStructureOverhead()))
    {
        if (pcbData != NULL)
        {
            *pcbData = 0;
        }
        return NULL;
    }
    if (pcbData)
    {
        *pcbData = m_pSectionHeader->cbSectionTotal - BaseFile::GetSectionStructureOverhead();
    }
    return reinterpret_cast<const BYTE*>(&m_pSectionHeader[1]);
}

HRESULT FileSectionBase::GetTotalSize(_Out_ UINT32* size) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT), m_pSectionHeader == NULL);

    *size = (m_pSectionHeader ? m_pSectionHeader->cbSectionTotal : 0);
    return S_OK;
}

HRESULT FileSectionBase::GetSectionHeader(_Out_ const DEFFILE_SECTION_HEADER** header) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT), m_pSectionHeader == NULL);

    *header = m_pSectionHeader;
    return S_OK;
}

DEFFILE_SECTION_INDEX FileSectionBase::GetSectionIndex() const { return m_sectionIndex; }

const BaseFile* const FileSectionBase::GetParentFile() const { return m_pParentFile; }

} // namespace Microsoft::Resources