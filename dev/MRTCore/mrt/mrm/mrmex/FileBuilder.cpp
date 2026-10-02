// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include "mrm/build/FileBuilder.h"

namespace Microsoft::Resources::Build
{

FileBuilder::FileBuilder(__in DEFFILE_MAGIC magic) :
    m_phase(Initializing),
    m_magic(magic),
    m_sizeSections(0),
    m_nSections(0),
    m_pSections(NULL),
    m_descriptorIndex(DEFFILE_SECTION_INDEX_NONE),
    m_pData(NULL),
    m_cbData(0),
    m_pHeader(NULL),
    m_pToc(NULL),
    m_pSectionData(NULL),
    m_cbSectionData(0),
    m_nSectionDataUsed(0)
{}

FileBuilder::~FileBuilder()
{
    if (m_pData)
    {
        _DefFree(m_pData);
    }

    //NOTE: Individual sections are not deleted by filebuilder since it doesn't own these sections
    if (m_pSections)
    {
        _DefFree(m_pSections);
    }
}

HRESULT FileBuilder::CreateInstance(__in DEFFILE_MAGIC magic, __in BaseFile::SectionCount sizeSections, _Outptr_ FileBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, !BaseFile::IsValidSectionCount(sizeSections));

    AutoDeletePtr<FileBuilder> pRtrn = new FileBuilder(magic);
    RETURN_IF_NULL_ALLOC(pRtrn);

    // pre-allocate sections array if it was requested
    if (sizeSections > 0)
    {
        pRtrn->m_pSections = _DefArray_Alloc(SectionInfo, sizeSections);
        RETURN_IF_NULL_ALLOC(pRtrn->m_pSections);
        pRtrn->m_sizeSections = static_cast<BaseFile::SectionCount>(sizeSections);
    }

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileBuilder::SetDescriptorIndex(__in BaseFile::SectionIndex index)
{
    RETURN_HR_IF(E_INVALIDARG, (index >= m_nSections) && (index != DEFFILE_SECTION_INDEX_NONE));

    m_descriptorIndex = index;
    return S_OK;
}

HRESULT FileBuilder::AddSection(__in ISectionBuilder* pSectionBuilder)
{
    SectionInfo* pSection;

    RETURN_HR_IF_NULL(E_INVALIDARG, pSectionBuilder);

    if (m_nSections >= m_sizeSections)
    {
        BaseFile::SectionCount newSize = m_sizeSections * 2;
        if (newSize < 1)
        {
            newSize = 10;
        }

        if (!_DefArray_TryEnsureSize(&m_pSections, SectionInfo, m_sizeSections, newSize))
        {
            return E_OUTOFMEMORY;
        }
        m_sizeSections = newSize;
    }

    pSectionBuilder->SetSectionIndex(m_nSections);
    pSection = &m_pSections[m_nSections++];
    pSection->m_pSectionBuilder = pSectionBuilder;

    // no actual data until section is written
    pSection->m_pHeader = NULL;
    pSection->m_pTrailer = NULL;
    pSection->m_pSectionData = NULL;
    pSection->m_cbSectionData = 0;

    return S_OK;
}

HRESULT FileBuilder::GetSectionData(__in INT32 sectionIndex, _Out_ const BYTE** data, _Out_ UINT32* pcbSectionData)
{
    *data = nullptr;
    RETURN_HR_IF(E_INVALIDARG, sectionIndex >= m_nSections);

    *pcbSectionData = m_pSections[sectionIndex].m_cbSectionData;

    *data = m_pSections[sectionIndex].m_pSectionData;
    return S_OK;
}

HRESULT FileBuilder::GetMaxSize(_Out_ UINT32* size)
{
    UINT32 maxSize;
    int i;
    SectionInfo* pSection;

    *size = 0;
    RETURN_HR_IF(E_INVALIDARG, (m_nSections < 1) || (m_pSections == nullptr));

    maxSize = BaseFile::GetStructureOverhead(m_nSections);
    for (i = 0, pSection = m_pSections; i < m_nSections; i++, pSection++)
    {
        UINT32 sectionMaxSize = pSection->m_pSectionBuilder->GetMaxSizeInBytes();
        maxSize += BaseFile::GetSectionStructureOverhead() + BaseFile::PadData(sectionMaxSize);
    }
    *size = maxSize;

    return S_OK;
}

HRESULT FileBuilder::StartGenerating(__out_bcount(cbDataOut) VOID* pDataOut, __in UINT32 cbDataOut)
{
    RETURN_HR_IF(E_INVALIDARG, (pDataOut == nullptr) || (m_nSections < 1) || (cbDataOut < BaseFile::GetStructureOverhead(m_nSections)));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_phase != Finalizing);

    DEFFILE_HEADER* pHeader = (DEFFILE_HEADER*)pDataOut;
    DEFFILE_TRAILER* pTrailer;

    // Let OACR know what's going on
    __analysis_assume(cbDataOut > sizeof(DEFFILE_HEADER));

    m_phase = Generating;
    m_pData = pDataOut;
    m_cbData = BaseFile::TruncData(cbDataOut);
    m_pHeader = pHeader;
    m_pToc = (DEFFILE_TOC_ENTRY*)&pHeader[1];
    m_pSectionData = (BYTE*)&m_pToc[m_nSections];
    m_nSectionDataUsed = 0;
    m_cbSectionData = cbDataOut - BaseFile::GetStructureOverhead(m_nSections);

    pHeader->magic = m_magic;
    pHeader->majorVersion = DEFFILE_VERSION_MAJOR;
    pHeader->minorVersion = DEFFILE_VERSION_MINOR;
    pHeader->cbTotal = m_cbData; // Adjusted to actual value by FinishGenerating.
    pHeader->sizeToc = 0; // Adjusted as sections are generated.
    pHeader->descriptorIndex = m_descriptorIndex;
    pHeader->tocOffset = BaseFile::PadSectionData(sizeof(DEFFILE_HEADER));
    pHeader->sectionDataOffset = BaseFile::PadSectionData((pHeader->tocOffset + m_nSections * sizeof(DEFFILE_TOC_ENTRY)));

    pTrailer = BaseFile::GetFileTrailer(pHeader);
    pTrailer->marker = DEFFILE_FILE_END_MARKER;
    pTrailer->magic = m_magic;
    pTrailer->cbTotal = pHeader->cbTotal;

    // at this point, pDataOut contains a well-formed DEF file with 0 sections and lots of wasted space
    return S_OK;
}

HRESULT FileBuilder::StartSection(__in BaseFile::SectionIndex sectionIndex, _Out_ FileBuilder::SectionInfo** result)
{
    *result = nullptr;

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_phase != Generating);
    RETURN_HR_IF(E_INVALIDARG, (sectionIndex >= m_nSections) || (m_pSections[sectionIndex].m_pSectionData != nullptr));

    FileBuilder::SectionInfo* pSection;
    UINT32 cbSectionData;
    UINT32 cbTotal, sectionMaxSize;

    if ((m_cbSectionData - m_nSectionDataUsed) < (UINT32)BaseFile::GetSectionStructureOverhead())
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    pSection = &m_pSections[sectionIndex];
    sectionMaxSize = pSection->m_pSectionBuilder->GetMaxSizeInBytes();

    // try to give the section as much data as it asked for, padded to appropriate boundary
    cbSectionData = BaseFile::PadData(sectionMaxSize);
    cbTotal = cbSectionData + BaseFile::GetSectionStructureOverhead();

    // can't give it everything it wants.  Just give to the end of the section.
    if (m_nSectionDataUsed + cbTotal > m_cbSectionData)
    {
        cbTotal = m_cbSectionData - m_nSectionDataUsed;
        cbSectionData = cbTotal - BaseFile::GetSectionStructureOverhead();
    }

    pSection->m_pTocEntry = &m_pToc[sectionIndex];
    pSection->m_pHeader = (DEFFILE_SECTION_HEADER*)&m_pSectionData[m_nSectionDataUsed];
    pSection->m_pSectionData = (BYTE*)&pSection->m_pHeader[1];
    pSection->m_cbSectionData = cbSectionData;
    pSection->m_pTrailer = (DEFFILE_SECTION_TRAILER*)&pSection->m_pSectionData[cbSectionData];
    pSection->m_maxDataSize = sectionMaxSize;

    pSection->m_pHeader->type = pSection->m_pSectionBuilder->GetSectionType();
    pSection->m_pHeader->flags = pSection->m_pSectionBuilder->GetFlags();
    pSection->m_pHeader->sectionFlags = pSection->m_pSectionBuilder->GetSectionFlags();
    pSection->m_pHeader->qualifier = pSection->m_pSectionBuilder->GetSectionQualifier();
    pSection->m_pHeader->cbSectionTotal = cbTotal;

    pSection->m_pTrailer->marker = DEFFILE_SECTION_END_MARKER;
    pSection->m_pTrailer->cbSectionTotal = cbTotal;

    pSection->m_pTocEntry->type = pSection->m_pHeader->type;
    pSection->m_pTocEntry->flags = pSection->m_pHeader->flags;
    pSection->m_pTocEntry->sectionFlags = pSection->m_pHeader->sectionFlags;
    pSection->m_pTocEntry->qualifier = pSection->m_pHeader->qualifier;
    pSection->m_pTocEntry->offset = m_nSectionDataUsed;
    pSection->m_pTocEntry->cbSectionTotal = cbTotal;

    m_nSectionDataUsed += cbTotal;
    *result = pSection;

    return S_OK;
}

HRESULT FileBuilder::FinishSection(__in BaseFile::SectionIndex sectionIndex, __in UINT32 cbGenerated)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_phase != Generating);
    RETURN_HR_IF(E_INVALIDARG, (sectionIndex >= m_nSections) || (m_pSections[sectionIndex].m_pSectionData == nullptr));

    SectionInfo* pSection;
    UINT32 cbSectionData;
    UINT32 extent;

    pSection = &m_pSections[sectionIndex];
    if (cbGenerated > pSection->m_maxDataSize)
    {
        return E_DEFFILE_BUILD_SECTION_DATA_TOO_LARGE;
    }

    // first validate the trailer to make sure that section generation didn't step on it
    if ((pSection->m_pTrailer->marker != DEFFILE_SECTION_END_MARKER) ||
        (pSection->m_pTrailer->cbSectionTotal !=
         (UINT32)BaseFile::PadSectionData((pSection->m_maxDataSize) + BaseFile::GetSectionStructureOverhead())))
    {
        return E_DEFFILE_BUILD_SECTION_TRAILER_DAMAGED;
    }

    cbSectionData = BaseFile::PadSectionData(cbGenerated);

    // Now see if we used all of the section data.  If not, relocate the section marker.
    if (cbSectionData != (UINT32)BaseFile::PadSectionData(pSection->m_maxDataSize))
    {
        DEFFILE_SECTION_TRAILER* pOldTrailer = pSection->m_pTrailer;

        pSection->m_pHeader->cbSectionTotal = cbSectionData + BaseFile::GetSectionStructureOverhead();
        pSection->m_pTrailer = BaseFile::GetSectionTrailer(pSection->m_pHeader);
        pSection->m_pTrailer->marker = DEFFILE_SECTION_END_MARKER;
        pSection->m_pTrailer->cbSectionTotal = pSection->m_pHeader->cbSectionTotal;
        pSection->m_pTocEntry->cbSectionTotal = pSection->m_pHeader->cbSectionTotal;

        extent = (UINT32)(((BYTE*)&pOldTrailer[1]) - m_pSectionData);
        if (extent == m_nSectionDataUsed)
        {
            // we're at the end of the space that's been reserved so far so we can give back
            // any space we didn't use.
            m_nSectionDataUsed = extent;
        }
    }

    // Get the qualifier and flags from the build again, since it's possible
    // they changed during the build.  Make sure the header and the TOC entry
    // are in synch.
    pSection->m_pHeader->qualifier = pSection->m_pSectionBuilder->GetSectionQualifier();
    pSection->m_pHeader->flags = pSection->m_pSectionBuilder->GetFlags();
    pSection->m_pHeader->sectionFlags = pSection->m_pSectionBuilder->GetSectionFlags();

    pSection->m_pTocEntry->qualifier = pSection->m_pHeader->qualifier;
    pSection->m_pTocEntry->flags = pSection->m_pHeader->flags;
    pSection->m_pTocEntry->sectionFlags = pSection->m_pHeader->sectionFlags;

    if (sectionIndex + 1 > m_nSections)
    {
        m_nSections = sectionIndex + 1;
    }
    return S_OK;
}

HRESULT FileBuilder::FinishGenerating()
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_phase != Generating);
    RETURN_HR_IF(E_DEFFILE_BUILD_SECTION_DATA_TOO_LARGE, m_nSectionDataUsed > m_cbSectionData);

    int i;
    DEFFILE_TRAILER* pTrailer;

    for (i = 0; i < m_nSections; i++)
    {
        if (m_pSections[i].m_pSectionData == NULL)
        {
            return E_INVALIDARG;
        }
    }

    m_pHeader->sizeToc = (UINT16)m_nSections;
    m_pHeader->cbTotal = BaseFile::GetStructureOverhead(m_nSections) + BaseFile::PadSectionData(m_nSectionDataUsed);

    pTrailer = BaseFile::GetFileTrailer(m_pHeader);
    pTrailer->marker = DEFFILE_FILE_END_MARKER;
    pTrailer->magic = m_pHeader->magic;
    pTrailer->cbTotal = m_pHeader->cbTotal;

    m_phase = Done;
    return S_OK;
}

HRESULT FileBuilder::FinalizeAllSections()
{
    if ((m_phase == Finalizing))
    {
        return S_OK;
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_phase > Building);

    m_phase = Finalizing;
    for (int i = 0; i < m_nSections; i++)
    {
        RETURN_IF_FAILED(m_pSections[i].m_pSectionBuilder->Finalize());
    }
    return S_OK;
}

HRESULT FileBuilder::BuildAllSections()
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_phase != Generating);

    for (int i = 0; i < m_nSections; i++)
    {
        BaseFile::SectionIndex sectionIndex = m_pSections[i].m_pSectionBuilder->GetSectionIndex();
        FileBuilder::SectionInfo* pSectionInfo;
        UINT32 cbWritten = 0;
        RETURN_IF_FAILED(StartSection(sectionIndex, &pSectionInfo));

        RETURN_IF_FAILED(m_pSections[i].m_pSectionBuilder->Build(pSectionInfo->m_pSectionData, pSectionInfo->m_cbSectionData, &cbWritten));
        RETURN_IF_FAILED(FinishSection(sectionIndex, cbWritten));
    }

    return S_OK;
}

HRESULT FileBuilder::GenerateFileContentsInternal()
{
    UINT32 cbBuffer = 0;

    if (NULL == m_pData)
    {
        RETURN_IF_FAILED(FinalizeAllSections());

        //get size of buffer to allocate.
        RETURN_IF_FAILED(GetMaxSize(&cbBuffer));

        //Allocate buffer
        unique_deffree_ptr<VOID> pBuffer(_DefBlob_AllocZeroed(cbBuffer));
        RETURN_IF_NULL_ALLOC(pBuffer.get());

        //Generating file and all sections
        RETURN_IF_FAILED(StartGenerating(pBuffer.get(), cbBuffer));
        pBuffer.release();

        RETURN_IF_FAILED(BuildAllSections());

        RETURN_IF_FAILED(FinishGenerating());
    }

    return S_OK;
}

HRESULT FileBuilder::GenerateFileContents(__deref_out void** ppBufferRtrn, __out_opt UINT32* pBufferLen)
{
    *ppBufferRtrn = nullptr;

    if (pBufferLen)
    {
        *pBufferLen = 0;
    }

    if (nullptr == m_pData)
    {
        RETURN_IF_FAILED(GenerateFileContentsInternal());
    }

    unique_deffree_ptr<void> buffer(_DefBlob_AllocZeroed(m_cbData));
    RETURN_IF_NULL_ALLOC(buffer.get());

    errno_t err = memcpy_s(buffer.get(), m_cbData, m_pData, m_cbData);
    RETURN_IF_FAILED(ErrnoToHResult(err));

    *ppBufferRtrn = buffer.release();
    if (pBufferLen)
    {
        *pBufferLen = m_cbData;
    }

    return S_OK;
}

HRESULT FileBuilder::GenerateFileContents(__out_bcount(cbBufferOut) VOID* pBufferOut, UINT32 cbBufferOut, __out_opt UINT32* pcbWrittenSize)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pBufferOut);

    if (nullptr == m_pData)
    {
        RETURN_IF_FAILED(GenerateFileContentsInternal());
    }

    errno_t err = memcpy_s(pBufferOut, cbBufferOut, m_pData, m_cbData);
    RETURN_IF_FAILED(ErrnoToHResult(err));

    if (pcbWrittenSize != nullptr)
    {
        *pcbWrittenSize = m_cbData;
    }

    return S_OK;
}

HRESULT FileBuilder::WriteToFile(__in PCWSTR pFileName)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFileName));

    // if the identity is enabled, we need to add identity section here

    if (!m_pData)
    {
        RETURN_IF_FAILED(GenerateFileContentsInternal());
    }

    RETURN_HR_IF(E_DEFFILE_FILE_DATA_EMPTY, !m_pData || !m_cbData);

    // TODO - consider a wrapper around file create/write operations, so we can safely be called
    // from any layer in the system.
    wil::unique_handle hfile(CreateFile(pFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL));
    RETURN_LAST_ERROR_IF(hfile.get() == INVALID_HANDLE_VALUE);

    auto cleanupOnFailure = wil::scope_exit([&] {
        hfile.reset();
        DeleteFile(pFileName);
    });

    DWORD cbWritten = 0;
    RETURN_LAST_ERROR_IF(WriteFile(hfile.get(), m_pData, m_cbData, &cbWritten, NULL) == 0);
    RETURN_HR_IF(E_DEFFILE_UNABLE_TO_WRITE, cbWritten != m_cbData);
    RETURN_LAST_ERROR_IF(FlushFileBuffers(hfile.get()) == 0);

    cleanupOnFailure.release();
    return S_OK;
}

} // namespace Microsoft::Resources::Build