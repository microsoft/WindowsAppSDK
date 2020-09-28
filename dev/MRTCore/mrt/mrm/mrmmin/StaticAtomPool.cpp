// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources
{

/*! 
     * An atom pool initialized directly from an array of static strings.
     * Uses the supplied strings directly, so they must remain valid for
     * the life of the pool.
     */

HRESULT StaticAtomPool::CreateInstance(
    _In_reads_(numStrings) const PCWSTR* ppStrings,
    _In_ int numStrings,
    _In_opt_ PCWSTR pDescription,
    _In_ StaticAtomPoolFlags flags,
    _Outptr_ StaticAtomPool** pool)
{
    *pool = nullptr;

    RETURN_HR_IF(E_INVALIDARG, numStrings < 0);
    RETURN_HR_IF(E_INVALIDARG, (ppStrings == nullptr) && (numStrings != 0));

    // Fail if any of the strings are NULL or empty
    if ((flags & NoValidation) == 0)
    {
        // if AllowNullForAtom0 is set, don't validate the first atom
        for (int i = ((flags & AllowNullForAtom0) ? 1 : 0); i < numStrings; i++)
        {
            if ((ppStrings[i] == NULL) || (ppStrings[i][0] == L'\0'))
            {
                RETURN_HR(E_DEF_ATOM_BAD_STRING);
            }
        }
    }

    DEFCOMPAREOPTIONS compareOptions = ((flags & CaseSensitive) ? DefCompare_Default : DefCompare_CaseInsensitive);
    StaticAtomPool* pRtrn = new StaticAtomPool(ppStrings, numStrings, pDescription, compareOptions);
    RETURN_IF_NULL_ALLOC(pRtrn);
    *pool = pRtrn;

    return S_OK;
}

bool StaticAtomPool::Contains(__in PCWSTR pString) const { return TryGetIndex(pString, NULL); }

bool StaticAtomPool::Contains(__in Atom atom) const
{
    return ((atom.GetPoolIndex() == m_poolIndex) && (atom.GetIndex() >= 0) && (atom.GetIndex() < m_numStrings));
}

bool StaticAtomPool::Equals(__in Atom atom, __in PCWSTR pString) const
{
    if (DefString_IsEmpty(pString))
    {
        return false;
    }

    if (atom.GetPoolIndex() != m_poolIndex)
    {
        return false;
    }

    if ((atom.GetIndex() < 0) || (atom.GetIndex() > m_numStrings - 1))
    {
        return false;
    }

    return (DefString_CompareWithOptions(m_ppStrings[atom.GetIndex()], pString, m_compareOptions) == Def_Equal);
}

AtomPoolGroup* StaticAtomPool::GetAtomPoolGroup() const { return m_pAtoms; }

PCWSTR StaticAtomPool::GetDescription() const { return ((m_pDescription != NULL) ? m_pDescription : L""); }

bool StaticAtomPool::GetIsCaseInsensitive() const { return ((m_compareOptions & DefCompare_CaseInsensitive) != 0); }

Atom::Index StaticAtomPool::GetNumAtoms() const { return m_numStrings; }

Atom::PoolIndex StaticAtomPool::GetPoolIndex() const { return m_poolIndex; }

void StaticAtomPool::SetAtomPoolGroup(AtomPoolGroup* pGroup) { m_pAtoms = pGroup; }

void StaticAtomPool::SetPoolIndex(Atom::PoolIndex index) { m_poolIndex = index; }

bool StaticAtomPool::TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const
{
    Atom::Index index = Atom::NullAtomIndex;
    if (TryGetIndex(pString, &index))
    {
        if (pAtomOut != NULL)
        {
            pAtomOut->Set(index, m_poolIndex);
        }
        return true;
    }
    return false;
}

bool StaticAtomPool::TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const
{
    if (pIndexOut != NULL)
    {
        *pIndexOut = Atom::NullAtomIndex;
    }

    if (DefString_IsEmpty(pString))
    {
        return false;
    }

    for (int i = 0; i < m_numStrings; i++)
    {
        if (DefString_CompareWithOptions(m_ppStrings[i], pString, m_compareOptions) == Def_Equal)
        {
            if (pIndexOut != NULL)
            {
                *pIndexOut = i;
            }
            return true;
        }
    }
    return false;
}

bool StaticAtomPool::TryGetString(__in Atom atom, __inout_opt StringResult* pStringOut) const
{
    if (atom.GetPoolIndex() != m_poolIndex)
    {
        return false;
    }

    if ((atom.GetIndex() < 0) || (atom.GetIndex() > m_numStrings - 1))
    {
        return false;
    }

    if (pStringOut != NULL)
    {
        if (FAILED(pStringOut->SetRef(m_ppStrings[atom.GetIndex()])))
        {
            return false;
        }
    }
    return true;
}

bool StaticAtomPool::TryGetString(__in Atom::Index index, __inout_opt StringResult* pStringOut) const
{
    if ((index < 0) || (index > m_numStrings - 1))
    {
        return false;
    }

    if (pStringOut != NULL)
    {
        if (FAILED(pStringOut->SetRef(m_ppStrings[index])))
        {
            return false;
        }
    }
    return true;
}

} // namespace Microsoft::Resources