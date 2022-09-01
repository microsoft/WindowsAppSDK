// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

#define FileSection_TypeIsInvalid(SECTION, DESIRED) \
    (((SECTION) == NULL) || !BaseFile::SectionTypesEqual((SECTION)->GetSectionType(), (DESIRED)))

namespace Microsoft::Resources::Build
{

HRESULT FileAtomPoolCopier::Init(__in const IFileSection* const pFileSection, __in RemapInfo* pRemap)
{
    RETURN_IF_FAILED(SectionCopier::Init(pFileSection, pRemap));

    if (FileSection_TypeIsInvalid(m_pFileSection, FileAtomPool::GetSectionTypeId()))
    {
        return E_INVALIDARG;
    }

    if ((m_pFileSection->GetFlags() & (UINT32)BaseFile::IsAtomPoolSection) == 0)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    AutoDeletePtr<FileAtomPool> pPool;
    RETURN_IF_FAILED(FileAtomPool::CreateInstance(m_pFileSection, &pPool));

    m_originalIndex = pPool->GetPoolIndex();
    return S_OK;
}

HRESULT FileAtomPoolCopier::CreateInstance(
    __in const IFileSection* const pFileSection,
    __in RemapInfo* pRemap,
    _Outptr_ FileAtomPoolCopier** result)
{
    *result = nullptr;
    AutoDeletePtr<FileAtomPoolCopier> pRtrn = new FileAtomPoolCopier();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pFileSection, pRemap));

    *result = pRtrn.Detach();
    return S_OK;
}

UINT32
FileAtomPoolCopier::GetSectionQualifier() const
{
    // if we've been remapped, use our new index as the
    // qualifier.  Otherwise stick with the old one.
    Atom::PoolIndex newIndex = Atom::PoolIndexNone;
    if (m_pRemap && m_pRemap->TryGetAtomPoolMapping(m_originalIndex, &newIndex))
    {
        return static_cast<UINT32>(newIndex);
    }
    return m_pFileSection->GetSectionQualifier();
}

HRESULT FileAtomPoolCopier::RemapSectionData(__inout_bcount(cbSectionData) void* pSectionData, __in UINT32 cbSectionData) const
{
    Atom::PoolIndex newIndex = Atom::PoolIndexNone;
    RETURN_HR_IF(E_INVALIDARG, (pSectionData == nullptr) || (cbSectionData < sizeof(DEFFILE_ATOMPOOL_HEADER)));

    // For an atom pool, we only remap the pool index and the qualifier
    if (m_pRemap && m_pRemap->TryGetAtomPoolMapping(m_originalIndex, &newIndex))
    {
        DEFFILE_ATOMPOOL_HEADER* pHeader = reinterpret_cast<DEFFILE_ATOMPOOL_HEADER*>(pSectionData);
        pHeader->poolIndex = (DEF_ATOM_POOL_INDEX)newIndex;
    }
    return S_OK;
}

} // namespace Microsoft::Resources::Build