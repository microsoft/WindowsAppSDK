// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources::Build
{

SectionCopier::SectionCopier() : m_pFileSection(nullptr) {}

HRESULT SectionCopier::Init(__in const IFileSection* const pFileSection, __in RemapInfo* pRemap)
{
    RETURN_HR_IF(E_INVALIDARG, (pFileSection == nullptr) || (pRemap == nullptr));

    BaseFileSectionResult* pFileSectionCopy = NULL;

    UINT32 cbTotalSize;
    RETURN_IF_FAILED(pFileSection->GetTotalSize(&cbTotalSize));

    const DEFFILE_SECTION_HEADER* pHeader;
    RETURN_IF_FAILED(pFileSection->GetSectionHeader(&pHeader));
    if (!pHeader)
    {
        return E_ABORT;
    }
    RETURN_IF_FAILED(BaseFile::ValidateSectionStructure(pHeader, cbTotalSize));

    const BaseFile* pFile = pFileSection->GetParentFile();

    RETURN_IF_FAILED(pFile->GetFileSectionResultObject(&pFileSectionCopy));

    RETURN_IF_FAILED(pFile->GetFileSection(pFileSection->GetSectionIndex(), pFileSectionCopy));

    m_pFileSection = pFileSectionCopy;
    m_sectionIndex = BaseFile::SectionIndexNone;
    m_pRemap = pRemap;

    return S_OK;
}

HRESULT SectionCopier::CreateInstance(__in const IFileSection* const pFileSection, __in RemapInfo* pRemap, _Outptr_ SectionCopier** result)
{
    *result = nullptr;

    AutoDeletePtr<SectionCopier> pRtrn = new SectionCopier();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pFileSection, pRemap));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT SectionCopier::Finalize() { return S_OK; }

UINT32 SectionCopier::GetMaxSizeInBytes() const { return m_pFileSection->GetDataSize(); }

HRESULT SectionCopier::Build(__out_bcount(cbBuffer) VOID* pBuffer, UINT32 cbBuffer, __out_opt UINT32* pcbWritten) const
{
    RETURN_HR_IF(E_INVALIDARG, (pBuffer == nullptr) || (cbBuffer < m_pFileSection->GetDataSize()));

    UINT32 cbData;
    const BYTE* pData = m_pFileSection->GetData(&cbData);
    if (!pData)
    {
        return E_ABORT;
    }

    errno_t err = memcpy_s(pBuffer, cbBuffer, pData, cbData);
    RETURN_IF_FAILED(ErrnoToHResult(err));

    RETURN_IF_FAILED(RemapSectionData(pBuffer, cbBuffer));

    if (pcbWritten)
    {
        *pcbWritten = m_pFileSection->GetDataSize();
    }
    return S_OK;
}

DEFFILE_SECTION_TYPEID
SectionCopier::GetSectionType() const { return m_pFileSection->GetSectionType(); }

UINT16
SectionCopier::GetFlags() const
{
    // The default implementation just copies the source flags.
    // Overload this to change the behavior for a specific section type.
    return m_pFileSection->GetFlags();
}

UINT16
SectionCopier::GetSectionFlags() const
{
    // The default implementation just copies the source section flags.
    // Overload this to change the behavior for a specific section type.
    return m_pFileSection->GetSectionFlags();
}

UINT32
SectionCopier::GetSectionQualifier() const
{
    // The default implementation just copies the source qualifier.
    // Overload this to change the behavior for a specific section type.
    return m_pFileSection->GetSectionQualifier();
}

void SectionCopier::SetSectionIndex(BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }

BaseFile::SectionIndex SectionCopier::GetSectionIndex() const { return m_sectionIndex; }

HRESULT SectionCopier::RemapSectionData(__inout_bcount(cbSectionData) void* pSectionData, __in UINT32 cbSectionData) const
{
    RETURN_HR_IF(E_INVALIDARG, (pSectionData == nullptr) || (cbSectionData == 0));

    // The default base implementation doesn't remap anything. Overload
    // this in derived classes for specific file section types.
    return S_OK;
}

SectionCopier::~SectionCopier()
{
    if (m_pFileSection)
    {
        delete m_pFileSection;
    }
}

} // namespace Microsoft::Resources::Build
