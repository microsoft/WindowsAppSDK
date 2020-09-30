// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "StdAfx.h"
#include "mrm/build/AIDict.h"

namespace Microsoft::Resources::Build
{

/*
  * AtomIndexedDictionaryBase::Iterator declaration
  */
class AtomIndexedDictionaryBase::Iterator : public DefObject
{
protected:
    const AtomIndexedDictionaryBase* m_pDict;
    int m_currentAtomIndex;
    const AIDictRange* m_pCurrentRange;

    Iterator(_In_ const AtomIndexedDictionaryBase* pDict);

public:
    static HRESULT CreateInstance(_In_ const AtomIndexedDictionaryBase* pDict, _Outptr_ AtomIndexedDictionaryBase::Iterator** result);

    ~Iterator();

    const AtomIndexedDictionaryBase* GetDictionary();

    int GetCurrentAtomIndex();

    void SetCurrentAtomIndex(_In_ int index);

    const AIDictRange* GetCurrentRange();

    void SetCurrentRange(_In_opt_ const AIDictRange* pRange);
};

/*
  * AtomIndexedDictionaryBase::AIDictRange declaration
  */
class AtomIndexedDictionaryBase::AIDictRange : public DefObject
{
public:
    static const int ElemsPerRange = 32;

protected:
    Atom::Index m_base;
    int m_indices[ElemsPerRange];
    AIDictRange* m_pNext;

    AIDictRange(_In_ int base);

public:
    static HRESULT CreateInstance(int base, _Outptr_ AIDictRange** result);

    ~AIDictRange();

    AIDictRange* GetNext();

    Atom::Index GetMinAtom();

    Atom::Index GetMaxAtom();

    HRESULT GetNextInternedAtom(
        _In_ Atom::Index firstCandidate,
        _Out_ Atom::Index* pNextAtomOut,
        _Out_ int* pInternalIndexOut,
        _Out_ const AIDictRange** ppContainingRangeOut) const;

    bool TryGetInternalIndexForAtom(_In_ Atom::Index atomIndex, _Out_opt_ int* pInternalIndexOut) const;

    static HRESULT AssignInternalIndex(_Inout_ AIDictRange** ppRangeInOut, _In_ Atom::Index atomIndex, _In_ int internalIndex);
};

AtomIndexedDictionaryBase::AtomIndexedDictionaryBase(_In_ const IAtomPool* pNames, _In_ Strategy strategy) :
    m_pNames(pNames),
    m_strategy(strategy),
    m_minAtomIndex(Atom::IndexNone),
    m_maxAtomIndex(Atom::IndexNone),
    m_numItems(0),
    m_sizeItems(0),
    m_pRanges(nullptr)
{
    if (m_strategy == Auto)
    {
        int nAtoms = m_pNames->GetNumAtoms();
        if (nAtoms > 1000)
        {
            m_strategy = Sparse;
        }
        else if (nAtoms > 100)
        {
            m_strategy = Subset;
        }
        else
        {
            m_strategy = Full;
        }
    }
}

AtomIndexedDictionaryBase::~AtomIndexedDictionaryBase()
{
    delete m_pRanges;
    m_pRanges = nullptr;
    m_pNames = nullptr;
    m_minAtomIndex = m_maxAtomIndex = Atom::IndexNone;
    m_numItems = m_sizeItems = 0;
}

bool AtomIndexedDictionaryBase::TryGetInternalIndex(_In_ Atom::Index nameIndex, _Out_opt_ int* pInternalIndexOut) const
{
    if (!m_pNames->Contains(nameIndex))
    {
        return false;
    }

    int internalIndex = -1;
    if ((m_minAtomIndex >= 0) && (nameIndex >= m_minAtomIndex) && (nameIndex <= m_maxAtomIndex))
    {
        // We know the index is valid for our pool of names, but we need
        // to be sure that it falls in the range of elements for which
        // space has been allocated.  We need this check even with the
        // "Full" strategy in case the underlying atom pool has grown in
        // size since we allocated or data.
        switch (m_strategy)
        {
        case Full:
            internalIndex = static_cast<int>(nameIndex);
            break;
        case Subset:
            internalIndex = nameIndex - m_minAtomIndex;
            break;
        case Sparse:
            if (m_pRanges != nullptr)
            {
                (void)m_pRanges->TryGetInternalIndexForAtom(nameIndex, &internalIndex);
            }
            break;
        }
    }

    if (pInternalIndexOut != nullptr)
    {
        *pInternalIndexOut = internalIndex;
    }

    if ((internalIndex < 0) || (internalIndex >= m_numItems))
    {
        // legitimate index, but we haven't allocated space for it yet.
        // No error, but return false;
        return false;
    }
    return true;
}

bool AtomIndexedDictionaryBase::TryGetInternalIndex(_In_ PCWSTR pName, _Out_opt_ int* pInternalIndexOut) const
{
    Atom::Index atomIndex = Atom::NullAtomIndex;
    if ((pName == nullptr) || FAILED(m_pNames->GetIndex(pName, &atomIndex)))
    {
        return false;
    }
    return TryGetInternalIndex(atomIndex, pInternalIndexOut);
}

bool AtomIndexedDictionaryBase::TryGetInternalIndex(_In_ Atom name, _Out_opt_ int* pInternalIndexOut) const
{
    Atom::Index nameIndex = Atom::NullAtomIndex;
    if (FAILED(m_pNames->GetIndex(name, &nameIndex)))
    {
        return false;
    }
    return TryGetInternalIndex(nameIndex, pInternalIndexOut);
}

HRESULT AtomIndexedDictionaryBase::GetOrAddInternalIndex(_In_ Atom::Index nameIndex, _Out_opt_ int* pInternalIndexOut)
{
    if (TryGetInternalIndex(nameIndex, pInternalIndexOut))
    {
        return S_OK;
    }

    int internalIndex = -1;
    // Legitimate index but no space allocated.  Expand our elements.
    switch (m_strategy)
    {
    case Full:
    {
        int newSize = m_pNames->GetNumAtoms();
        RETURN_IF_FAILED(Extend(m_numItems, newSize, 0));

        m_sizeItems = m_numItems = m_pNames->GetNumAtoms();
        m_minAtomIndex = 0;
        m_maxAtomIndex = m_numItems - 1;
        internalIndex = nameIndex;
    }
    break;
    case Subset:
    {
        Atom::Index newMin = ((nameIndex < m_minAtomIndex) || (m_minAtomIndex < 0) ? nameIndex : m_minAtomIndex);
        Atom::Index newMax = ((nameIndex > m_maxAtomIndex) ? nameIndex : m_maxAtomIndex);
        int newSize = newMax - newMin + 1;
        int offset = ((m_minAtomIndex >= 0) ? m_minAtomIndex - newMin : 0);

        RETURN_IF_FAILED(Extend(m_numItems, newSize, offset));

        m_minAtomIndex = newMin;
        m_maxAtomIndex = newMax;
        m_sizeItems = m_numItems = newSize;
        internalIndex = nameIndex - m_minAtomIndex;
    }
    break;
    case Sparse:
    {
        if (m_numItems >= m_sizeItems)
        {
            int newSize = ((m_sizeItems < 1) ? InitialSparseSize : m_sizeItems * 2);
            RETURN_IF_FAILED(Extend(m_sizeItems, newSize, 0));

            m_sizeItems = newSize;
        }

        RETURN_IF_FAILED(AIDictRange::AssignInternalIndex(&m_pRanges, nameIndex, m_numItems));

        internalIndex = m_numItems++;
        if ((m_minAtomIndex < 0) || (nameIndex < m_minAtomIndex))
        {
            m_minAtomIndex = nameIndex;
        }

        if (nameIndex > m_maxAtomIndex)
        {
            m_maxAtomIndex = nameIndex;
        }
    }
    break;
    }
    if (pInternalIndexOut)
    {
        *pInternalIndexOut = internalIndex;
    }
    return S_OK;
}

HRESULT AtomIndexedDictionaryBase::GetOrAddInternalIndex(_In_ PCWSTR pName, _Out_opt_ int* pInternalIndexOut)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pName);

    Atom::Index atomIndex = Atom::NullAtomIndex;
    RETURN_IF_FAILED(m_pNames->GetIndex(pName, &atomIndex));

    return GetOrAddInternalIndex(atomIndex, pInternalIndexOut);
}

HRESULT AtomIndexedDictionaryBase::GetOrAddInternalIndex(_In_ Atom name, _Out_opt_ int* pInternalIndexOut)
{
    Atom::Index atomIndex = Atom::NullAtomIndex;
    RETURN_IF_FAILED(m_pNames->GetIndex(name, &atomIndex));

    return GetOrAddInternalIndex(atomIndex, pInternalIndexOut);
}

bool AtomIndexedDictionaryBase::ItemHasData(_In_ Atom::Index nameIndex) const
{
    int internalIndex = -1;
    if (!TryGetInternalIndex(nameIndex, &internalIndex))
    {
        return false;
    }
    return InternalItemHasData(internalIndex);
}

bool AtomIndexedDictionaryBase::ItemHasData(_In_ PCWSTR pItemName) const
{
    int internalIndex = -1;
    if (!TryGetInternalIndex(pItemName, &internalIndex))
    {
        return false;
    }
    return InternalItemHasData(internalIndex);
}

bool AtomIndexedDictionaryBase::ItemHasData(_In_ Atom itemName) const
{
    int internalIndex = -1;
    if (!TryGetInternalIndex(itemName, &internalIndex))
    {
        return false;
    }
    return InternalItemHasData(internalIndex);
}

HRESULT AtomIndexedDictionaryBase::NewIterator(_Outptr_ AtomIndexedDictionaryBase::Iterator** result) const
{
    return Iterator::CreateInstance(this, result);
}

HRESULT AtomIndexedDictionaryBase::ResetIterator(_Inout_ AtomIndexedDictionaryBase::Iterator* pState) const
{
    RETURN_HR_IF(E_INVALIDARG, (pState == nullptr) || (pState->GetDictionary() != this));

    pState->SetCurrentAtomIndex(Atom::IndexNone);
    pState->SetCurrentRange(nullptr);
    return S_OK;
}

int AtomIndexedDictionaryBase::GetMaxInternalIndex() const
{
    if (m_minAtomIndex >= 0)
    {
        switch (m_strategy)
        {
        case Full:
            return m_maxAtomIndex;
        case Subset:
            return m_maxAtomIndex - m_minAtomIndex;
        case Sparse:
            return m_numItems;
        }
    }
    return -1;
}

HRESULT AtomIndexedDictionaryBase::GetNextInternedAtomWithData(
    _Inout_ AtomIndexedDictionaryBase::Iterator* pState,
    _Out_ Atom::Index* pAtomIndexOut,
    _Out_opt_ int* pInternalIndexOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (pState == nullptr) || (pState->GetDictionary() != this) || (pAtomIndexOut == nullptr));

    if (m_minAtomIndex < 0)
    {
        // Nothing in the dictionary.  Not an error, but no result.
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    if (m_strategy != Sparse)
    {
        Atom::Index thisAtom = pState->GetCurrentAtomIndex();
        Atom::Index nextAtom = ((thisAtom == Atom::IndexNone) ? m_minAtomIndex : thisAtom + 1);

        int nextInternal = ((m_strategy == Full) ? nextAtom : nextAtom - m_minAtomIndex);
        int maxInternal = GetMaxInternalIndex();

        for (int i = nextInternal; i <= maxInternal; i++, nextAtom++)
        {
            if (InternalItemHasData(i))
            {
                pState->SetCurrentAtomIndex(nextAtom);
                *pAtomIndexOut = nextAtom;

                if (pInternalIndexOut != nullptr)
                {
                    *pInternalIndexOut = i;
                }
                return S_OK;
            }
        }
    }
    else
    {
        // sparse strategy - iterate through the masks
        const AIDictRange* pRange = pState->GetCurrentRange();
        Atom::Index nextAtom = pState->GetCurrentAtomIndex() + 1;
        int internalIndex = -1;

        if (pRange == nullptr)
        {
            pRange = m_pRanges;
            nextAtom = m_pRanges->GetMinAtom();
        }
        while (pRange != nullptr)
        {
            if (SUCCEEDED(pRange->GetNextInternedAtom(nextAtom, &nextAtom, &internalIndex, &pRange)) && InternalItemHasData(internalIndex))
            {

                pState->SetCurrentAtomIndex(nextAtom);
                pState->SetCurrentRange(pRange);
                *pAtomIndexOut = nextAtom;

                if (pInternalIndexOut != nullptr)
                {
                    *pInternalIndexOut = internalIndex;
                }
                return S_OK;
            }
        }
    }
    // no more items with data
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT AtomIndexedDictionaryBase::DeleteIterator(_Inout_opt_ AtomIndexedDictionaryBase::Iterator* pState) const
{
    if (pState != nullptr)
    {
        RETURN_HR_IF(E_INVALIDARG, (pState->GetDictionary() != this));
    }

    delete pState;
    return S_OK;
}

/*
  * AtomIndexedDictionaryBase::Iterator implementation
  */
AtomIndexedDictionaryBase::Iterator::Iterator(_In_ const AtomIndexedDictionaryBase* pDict) :
    m_pDict(pDict), m_currentAtomIndex(Atom::IndexNone), m_pCurrentRange(nullptr)
{}

HRESULT AtomIndexedDictionaryBase::Iterator::CreateInstance(
    _In_ const AtomIndexedDictionaryBase* pDict,
    _Outptr_ AtomIndexedDictionaryBase::Iterator** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pDict);

    Iterator* pRtrn = new Iterator(pDict);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *result = pRtrn;
    return S_OK;
}

AtomIndexedDictionaryBase::Iterator::~Iterator() {}

const AtomIndexedDictionaryBase* AtomIndexedDictionaryBase::Iterator::GetDictionary() { return m_pDict; }

int AtomIndexedDictionaryBase::Iterator::GetCurrentAtomIndex() { return m_currentAtomIndex; }

void AtomIndexedDictionaryBase::Iterator::SetCurrentAtomIndex(_In_ int index) { m_currentAtomIndex = index; }

const AtomIndexedDictionaryBase::AIDictRange* AtomIndexedDictionaryBase::Iterator::GetCurrentRange() { return m_pCurrentRange; }

void AtomIndexedDictionaryBase::Iterator::SetCurrentRange(_In_opt_ const AtomIndexedDictionaryBase::AIDictRange* pRange)
{
    m_pCurrentRange = pRange;
}

AtomIndexedDictionaryBase::AIDictRange::AIDictRange(_In_ int base) : m_base(base), m_pNext(nullptr)
{
    for (int i = 0; i < ElemsPerRange; i++)
    {
        m_indices[i] = -1;
    }
}

HRESULT AtomIndexedDictionaryBase::AIDictRange::CreateInstance(int base, _Outptr_ AIDictRange** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, base < 0);

    *result = new AIDictRange(base);
    RETURN_IF_NULL_ALLOC(*result);

    return S_OK;
}

AtomIndexedDictionaryBase::AIDictRange::~AIDictRange()
{
    delete m_pNext;
    m_pNext = nullptr;
}

AtomIndexedDictionaryBase::AIDictRange* AtomIndexedDictionaryBase::AIDictRange::GetNext() { return m_pNext; }

Atom::Index AtomIndexedDictionaryBase::AIDictRange::GetMinAtom() { return m_base; }

Atom::Index AtomIndexedDictionaryBase::AIDictRange::GetMaxAtom() { return m_base + ElemsPerRange - 1; }

HRESULT AtomIndexedDictionaryBase::AIDictRange::GetNextInternedAtom(
    _In_ Atom::Index firstCandidate,
    _Out_ Atom::Index* pNextAtomOut,
    _Out_ int* pInternalIndexOut,
    _Out_ const AIDictRange** ppContainingRangeOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (pNextAtomOut == nullptr) || (pInternalIndexOut == nullptr) || (ppContainingRangeOut == nullptr));

    const AIDictRange* pRange = this;
    while (pRange != nullptr)
    {
        // If firstCandidate is above our base, use offset check to see if it falls in our range
        // If firstCandidate is below our base, first valid offset is automatically 0
        int offset = ((firstCandidate >= pRange->m_base) ? (firstCandidate - pRange->m_base) : 0);
        if ((offset >= 0) && (offset < ElemsPerRange))
        {
            // the first candidate falls in this range,
            // now find an interned atom.
            while (offset < ElemsPerRange)
            {
                if (pRange->m_indices[offset] != -1)
                {
                    *pNextAtomOut = static_cast<Atom::Index>(pRange->m_base + offset);
                    *pInternalIndexOut = pRange->m_indices[offset];
                    *ppContainingRangeOut = pRange;
                    return S_OK;
                }
                offset++;
            }
        }
        pRange = pRange->m_pNext;
    }
    *pNextAtomOut = Atom::IndexNone;
    *pInternalIndexOut = -1;
    *ppContainingRangeOut = nullptr;
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

bool AtomIndexedDictionaryBase::AIDictRange::TryGetInternalIndexForAtom(_In_ Atom::Index atomIndex, _Out_opt_ int* pInternalIndexOut) const
{
    const AIDictRange* pRange = this;

    while (pRange != nullptr)
    {
        int offset = atomIndex - pRange->m_base;
        if (offset < 0)
        {
            // We've searched past any containing range
            break;
        }
        else if (offset >= ElemsPerRange)
        {
            // Keep looking
            pRange = pRange->m_pNext;
        }
        else
        {
            // It's in this range.  See if an internal
            // index has been assigned.
            if (pInternalIndexOut != nullptr)
            {
                *pInternalIndexOut = pRange->m_indices[offset];
            }
            return (pRange->m_indices[offset] >= 0);
        }
    }

    if (pInternalIndexOut)
    {
        *pInternalIndexOut = -1;
    }
    return false;
}

HRESULT AtomIndexedDictionaryBase::AIDictRange::AssignInternalIndex(
    _Inout_ AIDictRange** ppRangeInOut,
    _In_ Atom::Index atomIndex,
    _In_ int internalIndex)
{
    RETURN_HR_IF(E_INVALIDARG, (ppRangeInOut == nullptr) || (internalIndex < 0));

    AIDictRange* pPrev = nullptr;
    AIDictRange* pRange = *ppRangeInOut;

    while (pRange != nullptr)
    {
        int offset = atomIndex - pRange->m_base;
        if (offset < 0)
        {
            // need to prepend a new range
            break;
        }
        else if (offset >= ElemsPerRange)
        {
            // keep searching
            pPrev = pRange;
            pRange = pRange->m_pNext;
        }
        else
        {
            if ((pRange->m_indices[offset] >= 0) && (pRange->m_indices[offset] != internalIndex))
            {
                return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
            }
            pRange->m_indices[offset] = internalIndex;
            return S_OK;
        }
    }

    // need to create a new range
    int base = (atomIndex / ElemsPerRange) * ElemsPerRange;
    RETURN_IF_FAILED(AIDictRange::CreateInstance(base, &pRange));

    pRange->m_indices[atomIndex - base] = internalIndex;
    if (pPrev)
    {
        pRange->m_pNext = pPrev->m_pNext;
        pPrev->m_pNext = pRange;
    }
    else
    {
        pRange->m_pNext = *ppRangeInOut;
        *ppRangeInOut = pRange;
    }
    return S_OK;
}

} // namespace Microsoft::Resources::Build