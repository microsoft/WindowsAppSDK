// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources
{

#define _PoolIndexIsExcludedFromGroup(SELF, INDEX) (((SELF) == nullptr) || ((INDEX) >= (SELF)->m_maxPoolIndex))

#define _AtomIsExcludedFromGroup(SELF, ATOM) \
    (((SELF) == NULL) || ((((ATOM).GetPoolIndex() >= (SELF)->m_maxPoolIndex) || (!(SELF)->m_pools[(ATOM).GetPoolIndex()]))))

#define _ArgIsInvalidPoolIndexForGroup(SELF, INDEX) (((INDEX) == DEF_ATOM_NULL_POOL_INDEX) || ((INDEX) >= (SELF)->m_sizePools))

AtomPoolGroup::AtomPoolGroup() : m_flags(0), m_sizePools(0), m_pools(NULL), m_pAssumeOwnership(NULL), m_maxPoolIndex(0), m_nPools(0) {}

HRESULT AtomPoolGroup::CreateInstance(__in int nPools, _Outptr_ AtomPoolGroup** group)
{
    *group = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (nPools < 0) || (nPools > Atom::MaxPoolCount));

    AutoDeletePtr<AtomPoolGroup> pRtrn = new AtomPoolGroup();
    RETURN_IF_NULL_ALLOC(pRtrn);

    if (nPools > 0)
    {
        pRtrn->m_pools = _DefArray_AllocZeroed(IAtomPool*, nPools + 1);
        RETURN_IF_NULL_ALLOC(pRtrn->m_pools);

        pRtrn->m_pAssumeOwnership = _DefArray_AllocZeroed(bool, nPools + 1);
        RETURN_IF_NULL_ALLOC(pRtrn->m_pAssumeOwnership);

        pRtrn->m_sizePools = (Atom::PoolIndex)nPools + 1;
    }

    *group = pRtrn.Detach();
    return S_OK;
}

AtomPoolGroup::~AtomPoolGroup()
{
    for (int iItr = 0; iItr < m_sizePools; iItr++)
    {
        if (true == m_pAssumeOwnership[iItr])
        {
            delete m_pools[iItr];
        }
    }
    _DefFree(m_pools);
    _DefFree(m_pAssumeOwnership);
}

HRESULT AtomPoolGroup::ExtendPools(__in Atom::PoolIndex newMaxIndex)
{
    RETURN_HR_IF(E_INVALIDARG, newMaxIndex > Atom::MaxPoolIndex);

    if (newMaxIndex >= m_sizePools)
    {
        if (!_DefArray_TryEnsureSize(&m_pools, IAtomPool*, m_sizePools, newMaxIndex + 1))
        {
            return E_OUTOFMEMORY;
        }
        if (!_DefArray_TryEnsureSize(&m_pAssumeOwnership, bool, m_sizePools, newMaxIndex + 1))
        {
            return E_OUTOFMEMORY;
        }
        m_sizePools = newMaxIndex + 1;
    }
    return S_OK;
}

_Success_(return == true)
bool AtomPoolGroup::TryGetAtomPool(__in Atom::PoolIndex index, __out_opt IAtomPool** ppPoolOut) const
{
    if (ppPoolOut == nullptr)
    {
        return false;
    }

    if (index > m_maxPoolIndex)
    {
        return false;
    }

    if (ppPoolOut)
    {
        *ppPoolOut = m_pools[index];
    }
    return (m_pools[index] != NULL);
}

IAtomPool* AtomPoolGroup::GetAtomPool(__in Atom::PoolIndex index) const
{
    if ((index < 0) || (index > m_maxPoolIndex - 1) || (m_pools[index] == NULL))
    {
        return NULL;
    }

    return m_pools[index];
}

HRESULT
AtomPoolGroup::RemoveAtomPool(__inout IAtomPool* pPool)
{
    RETURN_HR_IF(E_INVALIDARG, (m_pools == nullptr) || (pPool == nullptr));
    RETURN_HR_IF(E_INVALIDARG, pPool->GetAtomPoolGroup() != this);
    RETURN_HR_IF(E_INVALIDARG, (pPool->GetPoolIndex() < 0) || (pPool->GetPoolIndex() > m_sizePools - 1));

    Atom::PoolIndex nPoolIndex = pPool->GetPoolIndex();
    // pPool points to this group and is in range
    pPool->SetAtomPoolGroup(NULL);
    if (m_pools[nPoolIndex] == pPool)
    {
        if ((true == m_pAssumeOwnership[nPoolIndex]))
        {
            delete pPool;
        }
        m_pools[nPoolIndex] = NULL;
        m_pAssumeOwnership[nPoolIndex] = false;
        m_nPools--;
    }
    return S_OK;
}

/*
         *  AtomPoolGroup takes responsibility of deleting pPool passed here if
         *  and only if bAssumeOwnership is given as true by the caller.
         */
HRESULT
AtomPoolGroup::AddAtomPool(__inout IAtomPool* pPool, __in Atom::PoolIndex index, __in bool bAssumeOwnership)
{
    RETURN_HR_IF(E_INVALIDARG, (m_pools == nullptr) || (pPool == nullptr) || _ArgIsInvalidPoolIndexForGroup(this, index));

    IAtomPool* pOldPool = NULL;

    // make sure the old pool doesn't point back here
    pOldPool = m_pools[index];
    if (pOldPool && (pOldPool->GetAtomPoolGroup() == this))
    {
        pOldPool->SetAtomPoolGroup(NULL);
    }

    // If the new pool is already part of another AtomPoolGroup,
    // clean it up.
    if (pPool->GetAtomPoolGroup())
    {
        RETURN_IF_FAILED(RemoveAtomPool(pPool));
    }

    pPool->SetPoolIndex(index);
    m_pools[index] = pPool;
    m_pAssumeOwnership[index] = bAssumeOwnership;
    if (index > m_maxPoolIndex)
    {
        m_maxPoolIndex = index;
    }
    m_nPools++;
    pPool->SetAtomPoolGroup(this);
    return S_OK;
}

/*
         *  Use of bAssumeOwnership as defined above.
         */
HRESULT
AtomPoolGroup::AddAtomPool(__inout IAtomPool* pPool, __in bool bAssumeOwnership)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pPool);

    if (pPool->GetAtomPoolGroup() == this)
    {
        return S_OK;
    }

    // pool 0 is reserved.  start at 1.
    for (Atom::PoolIndex i = 1; i < m_sizePools; i++)
    {
        if (m_pools[i] == NULL)
        {
            return AddAtomPool(pPool, i, bAssumeOwnership);
        }
    }

    RETURN_IF_FAILED(ExtendPools(m_maxPoolIndex + 1));

    return AddAtomPool(pPool, m_maxPoolIndex + 1, bAssumeOwnership);
}

bool AtomPoolGroup::AtomsEqual(__in Atom atom1, __in Atom atom2) const
{
    Atom::Comparison compare = atom1.Compare(atom2);
    IAtomPool* pPool1;
    IAtomPool* pPool2;
    StringResult string1;
    StringResult string2;

    if (compare == DEF_ATOMS_EQUAL)
        return true;
    if (compare == DEF_ATOMS_UNEQUAL)
        return false;
    // indeterminate
    if (_AtomIsExcludedFromGroup(this, atom1) || _AtomIsExcludedFromGroup(this, atom2))
    {
        return false;
    }

    pPool1 = m_pools[atom1.GetPoolIndex()];
    pPool2 = m_pools[atom2.GetPoolIndex()];

    if ((!pPool1->TryGetString(atom1, &string1)) || (!pPool2->TryGetString(atom2, &string2)))
    {
        return false;
    }
    DEFCOMPARISON result;
    // todo. case insensitivity handling isn't complete here since below condition shoud follow by some agreement
    if (pPool1->GetIsCaseInsensitive() && pPool2->GetIsCaseInsensitive())
    {
        (void)string1.ICompare(&string2, &result);
        return (result == DEFCOMPARISON::Def_Equal);
    }
    // if both is default or one of them is case insensitive, we just compare the string as default
    (void)string1.Compare(&string2, &result);
    return (result == DEFCOMPARISON::Def_Equal);
}

HRESULT
AtomPoolGroup::GetString(__in Atom atom, __inout StringResult* pStrResult) const
{
    if (!TryGetString(atom, pStrResult))
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_INDEX);
    }

    return S_OK;
}

bool AtomPoolGroup::TryGetString(Atom atom, __out StringResult* pStrResult) const
{
    if ((atom.GetPoolIndex() >= m_sizePools) || (atom.GetPoolIndex() < 0) || (!m_pools[atom.GetPoolIndex()]))
    {
        return false;
    }

    return m_pools[atom.GetPoolIndex()]->TryGetString(atom, pStrResult);
}

} // namespace Microsoft::Resources
