// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "mrm/readers/RemapInfo.h"

namespace Microsoft::Resources
{

HRESULT RemapUInt16::CreateInstance(_In_ int initialSize, _Outptr_ RemapUInt16** result)
{
    *result = nullptr;

    AutoDeletePtr<RemapUInt16> pRtrn = new RemapUInt16();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->EnsureSize(initialSize));
    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT RemapUInt16::CreateInstance(_In_ const RemapUInt16* pCloneFrom, _Outptr_ RemapUInt16** result)
{
    *result = nullptr;

    AutoDeletePtr<RemapUInt16> pRtrn;
    RETURN_IF_FAILED(RemapUInt16::CreateInstance(pCloneFrom->m_sizeMapping, &pRtrn));

    // if mapping is NULL, size must be 0.  If mapping is non-NULL, pCloneFrom->m_sizeMapping must be > 0.
    DEF_ASSERT((pCloneFrom->m_pMapping != nullptr) == (pCloneFrom->m_sizeMapping > 0));

    // if there's anything to copy, copy it.
    if ((pCloneFrom->m_pMapping != nullptr) && (pCloneFrom->m_sizeMapping > 0))
    {
        CopyMemory(pRtrn->m_pMapping, pCloneFrom->m_pMapping, (pCloneFrom->m_sizeMapping * sizeof(UINT16)));

        if (pRtrn->m_sizeMapping > PresenceMaskWidth)
        {
            size_t maskSize = ((pRtrn->m_sizeMapping + PresenceMaskWidth - 1) / PresenceMaskWidth);
            CopyMemory(pRtrn->m_present.masks, pCloneFrom->m_present.masks, maskSize * (PresenceMaskWidth / 8));
        }
        else
        {
            pRtrn->m_present.mask = pCloneFrom->m_present.mask;
        }
    }
    *result = pRtrn.Detach();
    return S_OK;
}

RemapUInt16::~RemapUInt16()
{
    if (m_pMapping != nullptr)
    {
        Def_Free(m_pMapping);
        m_pMapping = nullptr;
    }

    if ((m_sizeMapping > PresenceMaskWidth) && (m_present.masks != nullptr))
    {
        Def_Free(m_present.masks);
        m_present.masks = nullptr;
    }

    m_sizeMapping = 0;
}

bool RemapUInt16::IsPresent(_In_ UINT16 item) const
{
    if (item < m_sizeMapping)
    {
        UINT64 mask = 0;
        UINT64 bit = 0;
        if (m_sizeMapping > PresenceMaskWidth)
        {
            mask = m_present.masks[((UINT64)(item / PresenceMaskWidth))];
            bit = (1i64 << (item % PresenceMaskWidth));
        }
        else
        {
            mask = m_present.mask;
            bit = (1i64 << item);
        }
        return ((mask & bit) != 0);
    }

    return false;
}

bool RemapUInt16::SetIsPresent(_In_ UINT16 item)
{
    if (item < m_sizeMapping)
    {
        UINT64 bit = 0;
        if (m_sizeMapping > PresenceMaskWidth)
        {
            bit = (1i64 << (item % PresenceMaskWidth));
            m_present.masks[((UINT64)(item / PresenceMaskWidth))] |= bit;
        }
        else
        {
            bit = (1i64 << item);
            m_present.mask |= bit;
        }
        return true;
    }
    return false;
}

bool RemapUInt16::TryGetMapping(_In_ UINT16 from, _Out_ UINT16* pTo) const
{
    if ((!IsPresent(from)) || (from >= m_sizeMapping))
    {
        *pTo = from;
        return false;
    }

    *pTo = m_pMapping[from];
    return true;
}

bool RemapUInt16::TrySetMapping(_In_ UINT16 from, _In_ UINT16 to)
{
    UINT16 existing = 0;
    // If it already exists, it has to match
    if (TryGetMapping(from, &existing))
    {
        if (existing != to)
        {
            return false;
        }
        return true;
    }

    if (FAILED(EnsureSize(from + 1)))
    {
        return false;
    }

    m_pMapping[from] = to;
    SetIsPresent(from);
    return true;
}

HRESULT RemapUInt16::SetOrChangeMapping(_In_ UINT16 from, _In_ UINT16 to)
{
    RETURN_IF_FAILED(EnsureSize(from + 1));

    m_pMapping[from] = to;
    SetIsPresent(from);
    return S_OK;
}

RemapUInt16::RemapUInt16() : m_sizeMapping(0), m_pMapping(nullptr)
{
    m_present.mask = 0L;
    m_present.masks = nullptr;
}

void RemapUInt16::Reset()
{
    if (m_sizeMapping > PresenceMaskWidth)
    {
        int maskSize = (m_sizeMapping / PresenceMaskWidth) + 1;
        for (int i = 0; i < maskSize; i++)
        {
            m_present.masks[i] = 0;
        }
    }
    else
    {
        m_present.mask = 0;
    }
}

HRESULT RemapUInt16::EnsureSize(_In_ int newSize)
{
    if (newSize > m_sizeMapping)
    {
        if (!_DefArray_TryEnsureSize(&m_pMapping, UINT16, m_sizeMapping, newSize))
        {
            return E_OUTOFMEMORY;
        }

        if (newSize > PresenceMaskWidth)
        {
            size_t oldMaskSize = ((m_sizeMapping + PresenceMaskWidth - 1) / PresenceMaskWidth);
            size_t newMaskSize = ((newSize + PresenceMaskWidth - 1) / PresenceMaskWidth);

            // as long as newMaskSize is <= 1, we dont need to allocate or expand memory
            if ((newMaskSize > 1) && (newMaskSize > oldMaskSize))
            {
                if (oldMaskSize > 1)
                {
                    //m_present.masks already allocated, so expand
                    if (!_DefArray_TryEnsureSize(&m_present.masks, UINT64, oldMaskSize, newMaskSize))
                    {
                        return E_OUTOFMEMORY;
                    }
                }
                else
                {
                    UINT64* pMasks = _DefArray_AllocZeroed(UINT64, newMaskSize);
                    RETURN_IF_NULL_ALLOC(pMasks);

                    pMasks[0] = m_present.mask;
                    m_present.masks = pMasks;
                }
            }
        }

        m_sizeMapping = newSize;
    }
    return S_OK;
}

HRESULT RemapAtomPool::CreateInstance(
    _In_ Atom::PoolIndex sourcePoolIndex,
    _In_ Atom::PoolIndex targetPoolIndex,
    _In_ int numMappedAtomIndexes,
    _In_reads_(numMappedAtomIndexes) const Atom::SmallIndex* mappedAtomIndexes,
    _Outptr_ RemapAtomPool** result)
{
    *result = nullptr;

    AutoDeletePtr<RemapAtomPool> pRtrn = new RemapAtomPool();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(sourcePoolIndex, targetPoolIndex, numMappedAtomIndexes, mappedAtomIndexes));

    *result = pRtrn.Detach();

    return S_OK;
}

RemapAtomPool::~RemapAtomPool()
{
    if (m_mappedAtomIndexes != nullptr)
    {
        Def_Free(m_mappedAtomIndexes);
    }
}

_Success_(return ) bool RemapAtomPool::TryGetMappedIndex(_In_ Atom::Index sourceAtomIndex, _Out_ Atom::Index* pTargetAtomIndexOut) const
{
    if ((sourceAtomIndex < 0) || (sourceAtomIndex >= m_numMappedAtomIndexes))
    {
        return false;
    }

    if (m_mappedAtomIndexes[sourceAtomIndex] == Atom::SmallIndexNone)
    {
        *pTargetAtomIndexOut = Atom::IndexNone;
        return false;
    }

    *pTargetAtomIndexOut = m_mappedAtomIndexes[sourceAtomIndex];
    return true;
}

_Success_(return ) bool RemapAtomPool::TryGetMappedAtom(_In_ Atom sourceAtom, _Out_ Atom* pTargetAtomOut) const
{
    Atom::Index index = sourceAtom.GetIndex();

    if ((sourceAtom.GetPoolIndex() != m_sourcePoolIndex) || ((index < 0) || (index >= m_numMappedAtomIndexes)))
    {
        return false;
    }

    pTargetAtomOut->Set(m_mappedAtomIndexes[index], m_targetPoolIndex);
    return true;
}

HRESULT RemapAtomPool::Init(
    _In_ int sourcePoolIndex,
    _In_ int targetPoolIndex,
    _In_ int numMappedAtomIndexes,
    _In_reads_(numMappedAtomIndexes) const Atom::SmallIndex* mappedAtomIndexes)
{
    m_mappedAtomIndexes = _DefArray_AllocZeroed(Atom::SmallIndex, numMappedAtomIndexes);
    RETURN_IF_NULL_ALLOC(m_mappedAtomIndexes);

    CopyMemory(m_mappedAtomIndexes, mappedAtomIndexes, sizeof(Atom::SmallIndex) * numMappedAtomIndexes);

    m_numMappedAtomIndexes = numMappedAtomIndexes;
    m_sourcePoolIndex = sourcePoolIndex;
    m_targetPoolIndex = targetPoolIndex;

    return S_OK;
}

RemapInfo::RemapInfo()
{
    m_numSections = 0;
    m_pSectionMapping = nullptr;

    m_numPools = 0;
    m_pPoolMapping = nullptr;
}

RemapInfo::~RemapInfo()
{
    if (m_pSectionMapping != nullptr)
    {
        _DefFree(m_pSectionMapping);
        m_numSections = 0;
        m_pSectionMapping = nullptr;
    }

    if (m_pPoolMapping != nullptr)
    {
        _DefFree(m_pPoolMapping);
        m_numPools = 0;
        m_pPoolMapping = nullptr;
    }
}

HRESULT RemapInfo::Copy(_In_ RemapInfo* pRemap, _Outptr_ RemapInfo** result)
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pRemap);

    AutoDeletePtr<RemapInfo> pNewRemap;
    RETURN_IF_FAILED(RemapInfo::CreateInstance(&pNewRemap));

    BaseFile::SectionIndex* pSections = pRemap->GetSectionMapping(&(pNewRemap->m_numSections));
    RETURN_IF_FAILED(pNewRemap->SetSectionMapping(pNewRemap->m_numSections, pSections));

    Atom::PoolCount* pNumPoolsOut = pRemap->GetAtomPoolMapping(&(pRemap->m_numPools));

    RETURN_IF_FAILED(pNewRemap->SetAtomPoolMappingArray(pRemap->m_numPools, pNumPoolsOut));

    *result = pNewRemap.Detach();

    return S_OK;
}

HRESULT RemapInfo::CreateInstance(_Outptr_ RemapInfo** result)
{
    *result = nullptr;

    RemapInfo* pRtrn = new RemapInfo();
    RETURN_IF_NULL_ALLOC(pRtrn);

    *result = pRtrn;

    return S_OK;
}

HRESULT RemapInfo::SetSectionMapping(_In_ BaseFile::SectionCount numSections, _In_reads_opt_(numSections) BaseFile::SectionIndex* pSections)
{
    RETURN_HR_IF(E_INVALIDARG, (numSections < 0) || ((numSections < 1) && pSections));

    if (numSections > 0)
    {
        if ((m_numSections < numSections) || (m_pSectionMapping == nullptr))
        {
            BaseFile::SectionCount* pNewMapping = nullptr;

            // Old mapping is to small.  Make sure we can allocate the new
            // one before freeing the old one, because we don't want to
            // clobber the structure if we fail.
            pNewMapping = _DefArray_Alloc(BaseFile::SectionCount, numSections);
            RETURN_IF_NULL_ALLOC(pNewMapping);

            if (m_pSectionMapping == nullptr)
            {
                _DefFree(m_pSectionMapping);
            }
            m_pSectionMapping = pNewMapping;
        }
        m_numSections = numSections;

        // If we were given a mapping, use it.  Otherwise initialize
        // the mapping to have no mapping for any section.
        if (pSections == nullptr)
        {
            for (BaseFile::SectionCount i = 0; i < numSections; i++)
            {
                m_pSectionMapping[i] = BaseFile::SectionIndexNone;
            }
        }
        else
        {
            for (BaseFile::SectionCount i = 0; i < numSections; i++)
            {
                m_pSectionMapping[i] = pSections[i];
            }
        }
    }
    else if (m_pSectionMapping != nullptr)
    {
        // No new mapping.  If we had one, free it.
        _DefFree(m_pSectionMapping);
        m_pSectionMapping = nullptr;
        m_numSections = 0;
    }
    return S_OK;
}

HRESULT RemapInfo::GetSectionMapping(_In_ BaseFile::SectionIndex from, _Out_ BaseFile::SectionIndex* index) const
{
    *index = BaseFile::SectionIndexNone;

    RETURN_HR_IF(E_DEFFILE_UNDEFINED_MAPPING, !TryGetSectionMapping(from, index));

    return S_OK;
}

bool RemapInfo::TryGetSectionMapping(_In_ BaseFile::SectionIndex from, _Out_opt_ BaseFile::SectionIndex* pToOut) const
{
    if (pToOut != nullptr)
    {
        *pToOut = BaseFile::SectionIndexNone;
    }

    // Illegal value of "from" is an error.  A valid "from" section
    // that maps to nothing returns false but it isn't an error.
    if (!BaseFile::IsValidSectionIndex(from))
    {
        return false;
    }
    else if ((from < 0) || (from >= m_numSections))
    {
        return false;
    }
    else if (BaseFile::IsValidSectionIndex(m_pSectionMapping[from]))
    {
        if (pToOut != nullptr)
        {
            *pToOut = m_pSectionMapping[from];
        }
        return true;
    }

    return false;
}

HRESULT RemapInfo::SetAtomPoolMappingArray(_In_ Atom::PoolCount numPools, _In_reads_opt_(numPools) Atom::PoolIndex* pPools)
{
    RETURN_HR_IF(E_INVALIDARG, (numPools < 0) || ((numPools < 1) && pPools));

    if (numPools > 0)
    {
        if ((m_numPools < numPools) || (m_pPoolMapping == nullptr))
        {
            Atom::PoolCount* pNewMapping = nullptr;

            // Old mapping is to small.  Make sure we can allocate the new
            // one before freeing the old one, because we don't want to
            // clobber the structure if we fail.
            pNewMapping = _DefArray_Alloc(Atom::PoolCount, numPools);
            RETURN_IF_NULL_ALLOC(pNewMapping);

            m_pPoolMapping = pNewMapping;
        }

        m_numPools = numPools;

        // If we were given a mapping, use it.  Otherwise initialize
        // the mapping to be a no-op.
        if (pPools != nullptr)
        {
            for (Atom::PoolCount i = 0; i < numPools; i++)
            {
                m_pPoolMapping[i] = pPools[i];
            }
        }
        else
        {
            for (Atom::PoolCount i = 0; i < numPools; i++)
            {
                m_pPoolMapping[i] = i;
            }
        }
    }
    else if (m_pPoolMapping != nullptr)
    {
        // No new mapping.  If we had one, free it.
        _DefFree(m_pPoolMapping);
        m_pPoolMapping = nullptr;
        m_numPools = 0;
    }

    return S_OK;
}

HRESULT RemapInfo::SetAtomPoolMapping(_In_ Atom::PoolIndex fromPool, _In_ Atom::PoolIndex toPool)
{
    RETURN_HR_IF(E_INVALIDARG, (fromPool < 0) || (fromPool > m_numPools - 1));

    m_pPoolMapping[fromPool] = toPool;
    return S_OK;
}

HRESULT RemapInfo::GetAtomPoolMapping(_In_ Atom::PoolIndex from, _Out_ Atom::PoolIndex* index) const
{
    *index = Atom::PoolIndexNone;

    RETURN_HR_IF(E_DEFFILE_UNDEFINED_MAPPING, !TryGetAtomPoolMapping(from, index));

    return S_OK;
}

bool RemapInfo::TryGetAtomPoolMapping(_In_ Atom::PoolIndex from, _Out_opt_ Atom::PoolIndex* pToOut) const
{
    if (pToOut != nullptr)
    {
        *pToOut = Atom::PoolIndexNone;
    }

    if (!Atom::IsValidPoolIndex(from))
    {
        return false;
    }
    else if ((from < 0) || (from >= m_numPools))
    {
        return false;
    }
    else if (Atom::IsValidPoolIndex(m_pPoolMapping[from]))
    {
        if (pToOut != nullptr)
        {
            *pToOut = m_pPoolMapping[from];
        }
        return true;
    }

    return false;
}

Atom RemapInfo::RemapAtom(_In_ Atom atom) const
{
    Atom rtrn(Atom::NullAtomIndex, Atom::NullPoolIndex);

    Atom::PoolIndex toPool;
    if (FAILED(GetAtomPoolMapping(atom.GetPoolIndex(), &toPool)))
    {
        return rtrn;
    }

    rtrn.Set(atom.GetIndex(), toPool);
    return rtrn;
}

HRESULT RemapInfo::RemapAtom(_In_ Atom atom, _Out_opt_ Atom* pAtomRtrn) const
{
    if (pAtomRtrn != nullptr)
    {
        pAtomRtrn->Set(Atom::NullAtomIndex, Atom::NullPoolIndex);
    }

    // NULL doesn't remap
    if (atom.IsNull())
    {
        if (pAtomRtrn != nullptr)
        {
            *pAtomRtrn = atom;
        }
        return S_OK;
    }

    Atom::PoolIndex toPool = Atom::PoolIndexNone;
    RETURN_IF_FAILED(GetAtomPoolMapping(atom.GetPoolIndex(), &toPool));

    if (pAtomRtrn != nullptr)
    {
        pAtomRtrn->Set(atom.GetIndex(), toPool);
        if (!pAtomRtrn->IsValidNonNull())
        {
            return E_DEF_BAD_ATOM;
        }
    }
    return S_OK;
}

bool RemapInfo::TryRemapAtom(_In_ Atom atom, _Out_opt_ Atom* pAtomRtrn) const
{
    Atom::PoolIndex toPool = Atom::PoolIndexNone;

    // NULL doesn't remap
    if (atom.IsNull())
    {
        if (pAtomRtrn != nullptr)
        {
            *pAtomRtrn = atom;
        }
        return true;
    }

    if (!TryGetAtomPoolMapping(atom.GetPoolIndex(), &toPool))
    {
        if (pAtomRtrn != nullptr)
        {
            pAtomRtrn->Set(Atom::NullAtomIndex, Atom::NullPoolIndex);
        }
        return false;
    }

    if (pAtomRtrn != nullptr)
    {
        pAtomRtrn->Set(atom.GetIndex(), toPool);
        if (!pAtomRtrn->IsValidNonNull())
        {
            return false;
        }
    }
    return true;
}

} // namespace Microsoft::Resources
