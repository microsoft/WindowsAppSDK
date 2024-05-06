// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "mrm/readers/SectionParser.h"

namespace Microsoft::Resources
{

#define FileAtomPool_IsInvalid(SELF) \
    (((SELF) == nullptr) || ((SELF)->m_pHeader == nullptr) || \
     (((SELF)->m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_NONE) && (((SELF)->m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_UNSORTED) || \
                                                                  ((SELF)->m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_CASE_INSENSITIVE))))

#define FileAtomPool_IndexIsExcluded(SELF, INDEX) (FileAtomPool_IsInvalid(SELF) || ((INDEX) < 0) || ((INDEX) >= (SELF)->m_pHeader->nAtoms))

#define FileAtomPool_AtomIsExcluded(SELF, ATOM) \
    (FileAtomPool_IndexIsExcluded((SELF), (ATOM).GetIndex()) || ((SELF)->m_poolIndex != (ATOM).GetPoolIndex()))

#define _PoolIndexIsExcludedFromGroup(SELF, INDEX) (((SELF) == nullptr) || ((INDEX) >= (SELF)->m_sizePools))

#define _AtomIsExcludedFromGroup(SELF, ATOM) \
    (((SELF) == nullptr) || (((ATOM).GetPoolIndex() >= (SELF)->m_sizePools) || (!(SELF)->m_pPools[(ATOM).GetPoolIndex()])))

#define _ArgIsInvalidPoolIndexForGroup(SELF, INDEX) (((INDEX) == DEF_ATOM_NULL_POOL_INDEX) || ((INDEX) >= (SELF)->m_sizePools))

const DEFFILE_SECTION_TYPEID FileAtomPool::gAtomPoolSectionType =
    {'[', 'd', 'e', 'f', '_', '1', 'a', 't', 'o', 'm', '1', '2', ':', '-', ']'};

const DEFFILE_SECTION_TYPEID FileAtomPool::GetSectionTypeId() { return gAtomPoolSectionType; }

FileAtomPool::FileAtomPool() :
    FileSectionBase(),
    m_flags(0),
    m_poolIndex(DEF_ATOM_POOL_INDEX_NONE),
    m_pAll(NULL),
    m_cbTotalSize(0),
    m_pHeader(NULL),
    m_pHashes(NULL),
    m_pOffsets(NULL),
    m_pPool(NULL),
    m_pPoolGroup(NULL)
{}

HRESULT FileAtomPool::Initialize(__in_opt const IFileSection* pSection, __in_bcount(cbData) const void* pData, __in int cbData)
{
    UINT32 cbPoolTotal = 0;
    SectionParser data;

    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));
    RETURN_IF_FAILED(ValidateHeader(pData, cbData, &cbPoolTotal));
    RETURN_IF_FAILED(data.Set(pData, cbData));

    HRESULT hr = S_OK;
    m_pHeader = _SECTION_PARSER_NEXT(data, DEFFILE_ATOMPOOL_HEADER, &hr);
    if (m_pHeader)
    {

        if (!(m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_NONE))
        {
            m_pHashes = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->nAtoms, HashIndex, &hr);
        }
        else
        {
            m_pHashes = NULL;
        }
        m_pOffsets = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->nAtoms, UINT32, &hr);
        m_pPool = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cchPool, WCHAR, &hr);

        m_flags = 0;
        m_poolIndex = m_pHeader->poolIndex;
        m_cbTotalSize = cbPoolTotal;
        m_pAll = NULL;

        // if we want to be paranoid here we can:
        // 1) walk the 'hashes' array to verify that all indices are in range
        // and that the hash values are actually sorted.
        // 2) walk the 'offesets' array to verify that all offsets are in range
    }

    m_flags = 0;
    m_poolIndex = m_pHeader->poolIndex;
    m_pAll = NULL;
    m_cbTotalSize = cbPoolTotal;

    return hr;
}

FileAtomPool::~FileAtomPool() {}

HRESULT FileAtomPool::CreateInstance(__in const IFileSection* pFileSection, _Outptr_ FileAtomPool** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pFileSection);

    UINT32 cbData = 0;
    const void* pData = pFileSection->GetData(&cbData);
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), pData);

    AutoDeletePtr<FileAtomPool> pRtrn = new FileAtomPool();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Initialize(pFileSection, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileAtomPool::CreateInstance(__in_bcount(cbData) const void* pData, __in UINT32 cbData, _Outptr_ FileAtomPool** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pData == nullptr) || (cbData == 0));

    AutoDeletePtr<FileAtomPool> pRtrn = new FileAtomPool();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Initialize(nullptr, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileAtomPool::CreateInstance(__in const FileAtomPool* pFrom, __in Atom::PoolIndex newPoolIndex, _Outptr_ FileAtomPool** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pFrom);

    AutoDeletePtr<FileAtomPool> pRtrn = new FileAtomPool();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Initialize(pFrom, pFrom->GetData(), pFrom->GetDataSize()));
    pRtrn->m_poolIndex = newPoolIndex;

    *result = pRtrn.Detach();
    return S_OK;
}

bool FileAtomPool::TryGetString(Atom atom, __inout_opt StringResult* pStringOut) const
{
    if ((atom.GetPoolIndex() != m_poolIndex) || (atom.GetIndex() >= m_pHeader->nAtoms))
    {
        return false;
    }

    UINT32 offset = m_pOffsets[atom.GetIndex()];
    if (offset >= m_pHeader->cchPool)
    {
        return false;
    }

    if (pStringOut != NULL)
    {
        (void)pStringOut->SetRef(&m_pPool[offset]);
    }
    return true;
}

bool FileAtomPool::TryGetString(Atom::Index index, __inout_opt StringResult* pStringOut) const
{
    if (index >= m_pHeader->nAtoms)
    {
        return false;
    }

    UINT32 offset = m_pOffsets[index];
    if (offset >= m_pHeader->cchPool)
    {
        return false;
    }

    if (pStringOut != NULL)
    {
        (void)pStringOut->SetRef(&m_pPool[offset]);
    }
    return true;
}

/*
     * TODO: review conditions under which TryGetAtom sets an
     * error in pStatus, to make sure they're reasonable.
     */
_Success_(return == true)
bool FileAtomPool::TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const
{
    Atom::Index i;
    bool found = false;

    // TODO: Can we just assume that we're valid?
    if (FileAtomPool_IsInvalid(this) || (pString == nullptr))
    {
        return false;
    }
    if (DefString_IsEmpty(pString))
    {
        // Either way we return the NULL atom.
        // If pSelf is NULL, it's an error.  Otherwise
        // it's the expected answer.
        if (pAtomOut)
            pAtomOut->Set(DEF_ATOM_NULL);
        return true;
    }

    found = TryGetIndex(pString, &i);

    if (found && pAtomOut)
    {
        pAtomOut->Set(i, m_poolIndex);
    }
    return found;
}

_Success_(return == true)
bool FileAtomPool::TryGetHashIndex(__in PCWSTR pString, __out_opt HashIndex* pIndexOut) const
{
    if (m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_NONE)
    {
        return false;
    }

    Atom::Index index;
    if (TryGetIndex(pString, &index))
    {
        return false;
    }

    if (pIndexOut)
    {
        *pIndexOut = m_pHashes[index];
    }
    return true;
}

/*
     * TODO: These implementations of contains and equals are
     * generic enough that they should be moved to a shared
     * base class for atom pool implementations.
     * Get/SetAtomPoolGroup and Get/SetPoolIndex are probably
     * in the same boat.
     */
bool FileAtomPool::Contains(__in PCWSTR pString) const { return TryGetAtom(pString, NULL); }

bool FileAtomPool::Contains(__in Atom atom) const { return TryGetString(atom, NULL); }

bool FileAtomPool::Equals(__in Atom atom, __in PCWSTR pString) const
{
    StringResult myString;
    if ((!pString) || (!pString[0]))
    {
        return (atom.GetUInt64() == 0);
    }
    if (TryGetString(atom, &myString))
    {
        DEFCOMPAREOPTIONS compareOpts = (GetIsCaseInsensitive() ? DefCompare_CaseInsensitive : DefCompare_Default);
        DEFCOMPARISON comp = Def_CompareError;
        (void)myString.CompareWithOptions(pString, compareOpts, &comp);
        return comp == Def_Equal;
    }
    return false;
}

_Success_(return == true)
bool FileAtomPool::TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const
{
    bool found = false;
    Atom::Index i = 0;
    Atom::Hash hash;

    if ((pString == nullptr) || FileAtomPool_IsInvalid(this))
    {
        return false;
    }

    if (m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_NONE)
    {
        for (i = 0; i < m_pHeader->nAtoms; i++)
        {
            if (CompareAtIndex(i, pString) == 0)
            {
                found = true;
                break;
            }
        }
    }
    else if (m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_UNSORTED)
    {
        hash = Atom::HashString(pString, static_cast<Atom::HashMethod>(m_pHeader->flags));
        for (i = 0; i < m_pHeader->nAtoms; i++)
        {
            if ((m_pHashes[i].hash == hash) && (CompareAtHashIndex(i, pString) == 0))
            {
                found = true;
                break;
            }
        }
    }
    else
    {
        Atom::Index low = 0, high = m_pHeader->nAtoms - 1;

        // Binary search
        hash = Atom::HashString(pString, (DEF_ATOM_HASH_METHOD)m_pHeader->flags);
        while (low <= high)
        {
            i = ((high - low) / 2) + low;
            if (hash == m_pHashes[i].hash)
            {
                found = true;
                break;
            }

            if (hash < m_pHashes[i].hash)
            {
                high = i - 1;
            }
            else
            {
                low = i + 1;
            }
        }

        // handle hash collision case
        if (found && (CompareAtHashIndex(i, pString) != 0))
        {
            found = false;
            while (((i - 1) >= low) && (hash == m_pHashes[i - 1].hash))
            {
                i--;
            }
            while (++i <= high)
            {
                if (hash != m_pHashes[i].hash)
                {
                    break;
                }
                if (CompareAtHashIndex(i, pString) == 0)
                {
                    found = true;
                    break;
                }
            }
        }
    }

    if (pIndexOut)
    {
        *pIndexOut = (found ? i : Atom::NullAtomIndex);
    }
    return found;
}

DEFCOMPARISON FileAtomPool::CompareAtIndex(__in Atom::Index index, __in PCWSTR pString) const
{
    if ((pString == nullptr) || (m_pOffsets == nullptr) || (m_pPool == nullptr) || (m_pHeader == nullptr) ||
        FileAtomPool_IndexIsExcluded(this, index))
    {
        return Def_CompareError;
    }

    if (m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_CASE_INSENSITIVE)
    {
        return DefString_ICompare(pString, &m_pPool[m_pOffsets[index]]);
    }
    return DefString_Compare(pString, &m_pPool[m_pOffsets[index]]);
}

DEFCOMPARISON FileAtomPool::CompareAtHashIndex(__in Atom::Index hashIndex, __in PCWSTR pString) const
{
    if ((m_pHashes == nullptr) || (m_pHeader == nullptr) || (hashIndex < 0) || (hashIndex > m_pHeader->nAtoms - 1))
    {
        return Def_CompareError;
    }

    return CompareAtIndex(m_pHashes[hashIndex].index, pString);
}

UINT32 FileAtomPool::GetSizeInBytes(__in const DEFFILE_ATOMPOOL_HEADER* pHeader)
{
    if (pHeader == nullptr)
    {
        return 0;
    }
    return GetSizeInBytes(pHeader->nAtoms, pHeader->cchPool);
}

UINT32 FileAtomPool::GetSizeInBytes(__in UINT32 nAtoms, __in UINT32 cchPool)
{
    UINT32 maxSize;

    // Determine the absolute maximum space we might possibly need.  Note that
    // we might not use it all if there are duplicate or empty strings.
    // Reserve space for:
    // - header
    // - one offset and one hash per string
    // - string pool to hold all strings
    // Padded to 8-byte boundary
    maxSize = sizeof(DEFFILE_ATOMPOOL_HEADER);
    maxSize += nAtoms * sizeof(HashIndex);
    maxSize += nAtoms * sizeof(UINT32);
    maxSize += (cchPool * sizeof(WCHAR));
    return maxSize;
}

UINT32 FileAtomPool::GetMaxSizeInBytesForStrings(__in_ecount(nStrings) PCWSTR* ppStrings, __in UINT32 nStrings) const
{
    UINT32 i;
    UINT32 cchMaxPoolSize = 0;

    if ((ppStrings == nullptr) || (nStrings < 1))
    {
        return 0;
    }

    for (i = 0; i < nStrings; i++)
    {
        if (ppStrings[i] && ppStrings[i][0])
        {
            //! \todo - use intsafe here
            cchMaxPoolSize += static_cast<UINT32>(wcslen(ppStrings[i])) + 1;
        }
    }
    return GetSizeInBytes(nStrings, cchMaxPoolSize);
}

/*!
     * Validates the section header for an atom pool.
     */
HRESULT FileAtomPool::ValidateHeader(__in_bcount(cbData) const void* pData, __in UINT32 cbData, __out_opt UINT32* pcbTotalRtrn)
{
    UINT32 minSize;
    DEFFILE_ATOMPOOL_HEADER* pHdr = (DEFFILE_ATOMPOOL_HEADER*)pData;

    RETURN_HR_IF(E_INVALIDARG, (pHdr == nullptr) || (cbData < sizeof(DEFFILE_ATOMPOOL_HEADER)));
    RETURN_HR_IF(E_DEF_ATOM_BAD_POOL, (pHdr->poolIndex == DEF_ATOM_NULL_POOL_INDEX) || (pHdr->poolIndex == DEF_ATOM_POOL_INDEX_NONE));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), pHdr->desc[DEFFILE_ATOMPOOL_DESC_LENGTH - 1] != 0);

    minSize = GetSizeInBytes(pHdr);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), minSize > cbData);

    if (pcbTotalRtrn)
    {
        *pcbTotalRtrn = cbData;
    }
    return S_OK;
}

FileAtomPool::HashIndex* FileAtomPool::HashIndex_Init(__inout HashIndex* pSelf, __in Atom::Hash hash, __in Atom::Index index)
{
    if (pSelf == nullptr)
    {
        return nullptr;
    }

    pSelf->hash = hash;
    pSelf->index = index;
    return pSelf;
}

/*!
     * FileAtoms Implementation
     */

HRESULT FileAtoms::CreateAtomPoolGroupFromFile(__in const BaseFile* pFile, _Outptr_ AtomPoolGroup** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pFile);

    AutoDeletePtr<AtomPoolGroup> pRtrn;
    RETURN_IF_FAILED(AtomPoolGroup::CreateInstance(0, &pRtrn));
    RETURN_IF_FAILED(InitFromFile(pRtrn, pFile));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileAtoms::InitFromFile(__inout AtomPoolGroup* pGroup, __in const BaseFile* pFile)
{
    int i = 0;
    BaseFile::SectionCount nSections = BaseFile::SectionIndexNone;
    Atom::PoolIndex maxPool = -1;
    const DEFFILE_TOC_ENTRY* pToc = NULL;
    FileAtomPool* pPool = NULL;
    bool bAtomGroupAssumesOwnership = true;

    RETURN_HR_IF(E_INVALIDARG, (pGroup == nullptr) || (pFile == nullptr));

    AutoDeletePtr<BaseFileSectionResult> pFileSectionResult;
    RETURN_IF_FAILED(pFile->GetFileSectionResultObject(&pFileSectionResult));

    nSections = pFile->GetNumSections();
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), nSections == BaseFile::SectionIndexNone);

    // Determine the index of the highest pool
    for (i = 0; i < nSections; i++)
    {
        RETURN_IF_FAILED(pFile->GetTocEntry(i, &pToc));

        if ((!pToc) || (pToc->cbSectionTotal == 0) || (!(pToc->flags & DEFFILE_IS_ATOM_POOL_SECTION)))
        {
            // ignore NULL or non-atom pool sections
            continue;
        }

        if (!BaseFile::SectionTypesEqual(pToc->type, FileAtomPool::GetSectionTypeId()))
        {
            // 9/12/07 (ef) - XXX! Don't handle other atom pool types yet
            return E_NOTIMPL;
        }

        if ((pToc->qualifier == Atom::NullPoolIndex) || (pToc->qualifier > Atom::MaxPoolIndex))
        {
            // ignore out of range or DEF_ATOM_NULL_POOL_INDEX pools or duplicate index pools
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        if (static_cast<int>(pToc->qualifier) > maxPool)
        {
            maxPool = pToc->qualifier;
        }
    }

    if (maxPool < 0)
    {
        //
        // This file does not contain atom pools.
        // Later when loading file references we will extend the atom group to
        // be able hodling all atom pool from referenced files.
        //
        return S_OK;
    }

    RETURN_IF_FAILED(pGroup->ExtendPools((Atom::PoolIndex)maxPool + 1));

    for (i = 0; i < nSections; i++, pToc++)
    {
        RETURN_IF_FAILED(pFile->GetTocEntry(i, &pToc));

        if ((!pToc) || (pToc->cbSectionTotal == 0) || (!BaseFile::SectionTypesEqual(pToc->type, FileAtomPool::GetSectionTypeId())) ||
            (pToc->qualifier > static_cast<UINT32>(maxPool)) || (pToc->qualifier == Atom::NullPoolIndex))
        {
            // ignore NULL or non-atom pool sections
            continue;
        }

        // Fail if an atom pool already exists with this index or if
        // index is illegal (the latter shouldn't happen).
        if (pGroup->TryGetAtomPool((Atom::PoolIndex)pToc->qualifier, NULL))
        {
            return E_DEFFILE_ATOMPOOL_DUPLICATE_POOL_INDEX;
        }
        RETURN_HR_IF(E_INVALIDARG, i > BaseFile::MaxSectionIndex);

        RETURN_IF_FAILED(pFile->GetFileSection(DEFFILE_SECTION_INDEX(i), pFileSectionResult));

        RETURN_IF_FAILED(FileAtomPool::CreateInstance(pFileSectionResult, &pPool));

        RETURN_IF_FAILED(pGroup->AddAtomPool(pPool, (Atom::PoolIndex)pToc->qualifier, bAtomGroupAssumesOwnership));
    }

    return S_OK;
}

HRESULT FileAtoms::RemapAtomPools(
    __in AtomPoolGroup* pSrcGroup,
    __inout AtomPoolGroup* pDestGroup,
    __in_ecount(nMappings) DEFFILE_ATOMPOOL_MAPPING* pMappings,
    __in int nMappings)
{
    bool bAtomGroupAssumesOwnership = true;
    FileAtomPool* pPool = NULL;
    IAtomPool* pOtherPool = NULL;
    Atom::PoolIndex nPool = 0;
    DEFFILE_ATOMPOOL_MAPPING* pMapping = NULL;
    Atom::PoolIndex nMapping = 0;

    RETURN_HR_IF(E_INVALIDARG, (pSrcGroup == nullptr) || (pDestGroup == nullptr) || (pMappings == nullptr));

    //get each atompool from source atompool group. Clone it. remap index and append to pSelf
    for (pMapping = pMappings, nMapping = 0; nMapping < nMappings; nMapping++, pMapping++)
    {
        for (nPool = 0; nPool < pMapping->nPools; nPool++)
        {
            if (!pSrcGroup->TryGetAtomPool(nMapping + nPool, &pOtherPool))
            {
                return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
            }
            if (!pOtherPool)
            {
                // valid pool index, but pool not defined
                continue;
            }

            RETURN_IF_FAILED(FileAtomPool::CreateInstance(static_cast<FileAtomPool*>(pOtherPool), pMapping->destIndex + nPool, &pPool));
            RETURN_IF_FAILED(pDestGroup->AddAtomPool(pPool, pMapping->destIndex + nPool, bAtomGroupAssumesOwnership));
        }
    }
    return S_OK;
}

} // namespace Microsoft::Resources
