// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

HRESULT ReverseFileMap::Init(__in_opt const IFileSection* pSection, __in_bcount(cbData) const void* pData, __in int cbData)
{
    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));

    SectionParser data;
    RETURN_IF_FAILED(data.Set(pData, cbData));

    HRESULT hr = S_OK;
    const MRMFILE_REVERSEFILEMAP_HEADER* pHeader = _SECTION_PARSER_NEXT(data, MRMFILE_REVERSEFILEMAP_HEADER, &hr);
    RETURN_IF_FAILED(hr);

    if (pHeader->numFiles < 1)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    m_pHeader = pHeader;
    m_pEntries = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numFiles, MRMFILE_REVERSEFILEMAP_ENTRY, &hr);
    data.GetPadBytes(BaseFile::Align32Bit, &hr, NULL);

    RETURN_IF_FAILED(hr);

    m_cbSection = cbData;

    RETURN_IF_FAILED(HierarchicalNames::CreateInstance(
        gHierarchicalNamesSectionType,
        data.RemainingBuffer(),
        static_cast<int>(data.RemainingBufferSizeInBytes()),
        (HierarchicalNames**)&m_pNames));
    m_cbSection = cbData;

    return S_OK;
}

HRESULT ReverseFileMap::CreateInstance(__in_opt const IFileSection* const pSection, _Outptr_ ReverseFileMap** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pSection);

    AutoDeletePtr<ReverseFileMap> pRtrn = new ReverseFileMap();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSection, pSection->GetData(), pSection->GetDataSize()));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ReverseFileMap::CreateInstance(__in_bcount(cbData) const void* pData, __in int cbData, _Outptr_ ReverseFileMap** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pData);

    AutoDeletePtr<ReverseFileMap> pRtrn = new ReverseFileMap();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(nullptr, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

ReverseFileMap::ReverseFileMap() : m_pHeader(NULL), m_pEntries(NULL), m_pNames(NULL) {}

ReverseFileMap::~ReverseFileMap() { delete m_pNames; }

const DEFFILE_SECTION_TYPEID ReverseFileMap::GetSectionTypeId() { return gReverseFileMapSectionType; }

bool ReverseFileMap::TryGetReverseMapCandidateIndex(__in PCWSTR pCandidateValue, __out int* pReverseMapIndexOut) const
{
    int scopeIndexOut;
    int nameIndexOut;
    return m_pNames->Contains(pCandidateValue, &scopeIndexOut, pReverseMapIndexOut, &nameIndexOut);
}

HRESULT
ReverseFileMap::GetCandidateInfo(_In_ int reverseMapIndex, _Out_ int* pQualifierSetIndexOut, _Out_ int* pNamedResourceIndexOut) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (reverseMapIndex < 0) || (reverseMapIndex > m_pHeader->numFiles - 1));

    *pQualifierSetIndexOut = m_pEntries[reverseMapIndex].qualifierSetIndex;
    *pNamedResourceIndexOut = m_pEntries[reverseMapIndex].namedResourceIndex;
    return S_OK;
}

} // namespace Microsoft::Resources
