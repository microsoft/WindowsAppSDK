// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

HRESULT ReverseFileMapSectionBuilder::CreateInstance(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ const UnifiedEnvironment* pEnvironment,
    _Outptr_ ReverseFileMapSectionBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pPriBuilder == nullptr) || (pEnvironment == nullptr));

    AutoDeletePtr<ReverseFileMapSectionBuilder> pRtrn = new ReverseFileMapSectionBuilder(pPriBuilder, pEnvironment);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init());

    *result = pRtrn.Detach();
    return S_OK;
}

ReverseFileMapSectionBuilder::ReverseFileMapSectionBuilder(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ const UnifiedEnvironment* pEnvironment) :
    m_pPriSectionBuilder(pPriBuilder),
    m_pEntries(NULL),
    m_pEnvironment(pEnvironment),
    m_mapGenerated(false),
    m_buildFlags(0),
    m_pNames(nullptr)
{}

HRESULT ReverseFileMapSectionBuilder::Init()
{
    // Note: pResMapBuilder is owned and managed by pPriBuilder
    ResourceMapSectionBuilder* pResMapBuilder;
    RETURN_IF_FAILED(m_pPriSectionBuilder->GetOrAddPrimaryResourceMapBuilder(&pResMapBuilder));

    m_pSchema = pResMapBuilder->GetSchema();

    RETURN_IF_FAILED(HierarchicalNamesBuilder::CreateInstance(m_buildFlags, m_pPriSectionBuilder->GetAtoms(), &m_pNames));

    RETURN_IF_FAILED(DynamicArray<MRMFILE_REVERSEFILEMAP_ENTRY>::CreateInstance(256, &m_pEntries));

    return S_OK;
}

ReverseFileMapSectionBuilder::~ReverseFileMapSectionBuilder()
{
    delete m_pEntries;
    delete m_pNames;

    m_pEntries = NULL;
    m_pNames = NULL;
}

HRESULT ReverseFileMapSectionBuilder::AddEntry(_In_ int resourceIndex, _In_ int qualifierSetIndex, _Out_ int* index)
{
    *index = -1;
    int indexOut = -1;
    MRMFILE_REVERSEFILEMAP_ENTRY entry;
    entry.namedResourceIndex = static_cast<UINT16>(resourceIndex);
    entry.qualifierSetIndex = static_cast<UINT16>(qualifierSetIndex);
    RETURN_IF_FAILED(m_pEntries->Add(entry, &indexOut));
    *index = indexOut;

    return S_OK;
}

bool ReverseFileMapSectionBuilder::ChildIsScope(_In_ int scopeIndex, _In_ int childIndex)
{
    int childScopeIndex = -1;
    int childItemIndex = -1;

    if (m_pSchema->TryGetScopeChild(scopeIndex, childIndex, &childScopeIndex, &childItemIndex))
    {
        return (childScopeIndex >= 0);
    }

    return false;
}

HRESULT ReverseFileMapSectionBuilder::ReadCandidates(
    _In_ int itemIndex,
    _In_ DynamicArray<ResourceMapSectionBuilder*>* pResourceMapBuilders,
    _In_ ScopeInfo* pScopeInfo)
{
    int numCandidates;
    StringResult strResourceName;

    for (UINT i = 0; i < pResourceMapBuilders->Count(); ++i)
    {
        ResourceMapSectionBuilder* pResMapBuilder;
        RETURN_IF_FAILED(pResourceMapBuilders->Get(i, &pResMapBuilder));
        if (pResMapBuilder->TryGetResourceInfo(itemIndex, &strResourceName, &numCandidates))
        {
            for (int j = 0; j < numCandidates; ++j)
            {
                QualifierSetResult qualSetResult;
                MrmEnvironment::ResourceValueType candidateType;
                StringResult strCandidate;
                if (pResMapBuilder->TryGetCandidateInfo(itemIndex, j, &qualSetResult, &candidateType, &strCandidate))
                {
                    if (MrmEnvironment::IsPathResourceValueType(candidateType))
                    {
                        DEF_ASSERT(!strCandidate.IsEmpty()); // A File candidate cannot be empty.
                        ItemInfo* pItem;
                        RETURN_IF_FAILED(pScopeInfo->GetOrAddItem(strCandidate.GetRef(), &pItem));
                        int index;
                        RETURN_IF_FAILED(AddEntry(itemIndex, qualSetResult.GetIndex(), &index));
                    }
                }
            }
        }
    }
    return S_OK;
}

HRESULT ReverseFileMapSectionBuilder::ReadSubTreeRecursive(
    _In_ int scopeIndex,
    _In_ DynamicArray<ResourceMapSectionBuilder*>* pResourceMapBuilders,
    _In_ ScopeInfo* pScopeInfo)
{
    StringResult strScopeNameOut;
    int numChildrenOut;
    if (m_pSchema->TryGetScopeInfo(scopeIndex, &strScopeNameOut, &numChildrenOut))
    {
        for (UINT32 i = 0; i < numChildrenOut; ++i)
        {
            int childScopeIndex = -1;
            int childItemIndex = -1;
            if (m_pSchema->TryGetScopeChild(scopeIndex, i, &childScopeIndex, &childItemIndex))
            {
                if (childScopeIndex >= 0)
                {
                    RETURN_IF_FAILED(ReadSubTreeRecursive(childScopeIndex, pResourceMapBuilders, pScopeInfo));
                }
                else
                {
                    DEF_ASSERT(childItemIndex >= 0);
                    RETURN_IF_FAILED(ReadCandidates(childItemIndex, pResourceMapBuilders, pScopeInfo));
                }
            }
        }
    }
    return S_OK;
}

HRESULT ReverseFileMapSectionBuilder::GenerateMap(_In_ DynamicArray<ResourceMapSectionBuilder*>* pResourceMapBuilders)
{
    if (IsFinalized() || IsMapGenerated())
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }

    int scopeIndexOut;
    if (m_pSchema->ContainsScope(MrmWindowsCoreConstDefs::Scope_FilePaths, &scopeIndexOut))
    {
        ScopeInfo* pScopeInfo;
        RETURN_IF_FAILED(m_pNames->GetOrAddRootScope(MrmWindowsCoreConstDefs::Scope_FilePaths, &pScopeInfo));
        RETURN_IF_FAILED(ReadSubTreeRecursive(scopeIndexOut, pResourceMapBuilders, pScopeInfo));
    }

    m_mapGenerated = true;

    return S_OK;
}

bool ReverseFileMapSectionBuilder::IsValid() const { return true; }

bool ReverseFileMapSectionBuilder::IsFinalized() const { return m_finalized; }

HRESULT ReverseFileMapSectionBuilder::Finalize()
{
    if (!IsMapGenerated())
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }

    if (!IsValid())
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }

    RETURN_IF_FAILED(m_pNames->Finalize());

    if (IsFinalized())
    {
        return S_OK;
    }

    m_numFileCandidates = m_pEntries->Count();
    m_cbNamesBlob = m_pNames->GetMaxSizeInBytes();

    m_finalized = true;
    return S_OK;
}

UINT32 ReverseFileMapSectionBuilder::GetMaxSizeInBytes() const
{
    if (!IsFinalized())
    {
        return 0;
    }

    UINT32 cbTotal = sizeof(MRMFILE_REVERSEFILEMAP_HEADER) + m_numFileCandidates * sizeof(MRMFILE_REVERSEFILEMAP_ENTRY);
    cbTotal += m_cbNamesBlob;
    return cbTotal;
}

HRESULT
ReverseFileMapSectionBuilder::Build(_Out_writes_bytes_(cbBuffer) VOID* pBuffer, _In_ UINT32 cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const
{
    MRMFILE_REVERSEFILEMAP_HEADER* pHeader;
    MRMFILE_REVERSEFILEMAP_ENTRY* pEntries;
    BYTE* pNamesBlob;

    RETURN_HR_IF_NULL(E_INVALIDARG, pBuffer);
    RETURN_HR_IF(E_DEF_NOT_READY, !IsFinalized());

    if (pcbWrittenOut != NULL)
    {
        *pcbWrittenOut = 0;
    }

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(pBuffer, cbBuffer));

    HRESULT hr = S_OK;
    pHeader = _SECTION_BUILDER_NEXT(data, MRMFILE_REVERSEFILEMAP_HEADER, &hr);
    pEntries = _SECTION_BUILDER_NEXT_ARRAY(data, m_pEntries->Count(), MRMFILE_REVERSEFILEMAP_ENTRY, &hr);

    // determine the size of what we've written so far
    // so we can correctly compute actual written size later
    UINT32 cbNonNames = static_cast<UINT32>(data.UsedBufferSizeInBytes());

    pNamesBlob = _SECTION_BUILDER_NEXT_ARRAY(data, m_cbNamesBlob, BYTE, &hr);

    RETURN_IF_FAILED(hr);

    _Analysis_assume_(pHeader != nullptr);
    _Analysis_assume_(pEntries != nullptr);

    // Header
    pHeader->numFiles = m_numFileCandidates;

    // Entries
    for (int i = 0; i < m_pEntries->Count(); ++i)
    {
        MRMFILE_REVERSEFILEMAP_ENTRY entry;
        if (!m_pEntries->TryGet(i, &entry))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }
        pEntries[i] = entry;
    }

    UINT32 cbNamesWritten = 0;
    RETURN_IF_FAILED(m_pNames->Build(pNamesBlob, m_cbNamesBlob, &cbNamesWritten));

    pHeader->cbTotal = m_numFileCandidates * sizeof(MRMFILE_REVERSEFILEMAP_ENTRY) + cbNamesWritten;
    *pcbWrittenOut = cbNonNames + cbNamesWritten;
    return S_OK;
}

} // namespace Microsoft::Resources::Build