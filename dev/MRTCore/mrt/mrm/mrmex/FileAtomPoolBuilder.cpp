// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "StdAfx.h"

namespace Microsoft::Resources::Build
{

FileAtomPoolBuilder::FileAtomPoolBuilder() : m_pStrings(nullptr), m_offset(nullptr), m_hash(nullptr), m_flags(0) {}

HRESULT FileAtomPoolBuilder::Init(_In_opt_ PCWSTR pDescription, _In_ WriteableStringPool* pStrings, UINT32 flags)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pStrings);

    m_finalized = false;
    m_flags = flags;
    m_hashMethod = ((flags & fIsCaseInsensitive) ? Atom::HashMethodCaseInsensitive : Atom::HashMethodDefault);

    m_group = NULL;
    m_poolIndex = Atom::NullPoolIndex;

    SecureZeroMemory(m_description, _countof(m_description));
    if (pDescription != NULL)
    {
        RETURN_IF_FAILED(DefString_CchCopy(m_description, _countof(m_description), pDescription));
    }

    m_numAtoms = 0;
    m_sizeAtoms = 0;
    m_hash = NULL;
    m_offset = NULL;
    m_sectionIndex = 0;
    m_pStrings = pStrings;

    return S_OK;
}

HRESULT FileAtomPoolBuilder::CreateInstance(__in PCWSTR pDescription, bool isCaseInsensitive, _Outptr_ FileAtomPoolBuilder** result)
{
    *result = nullptr;

    UINT32 stringsFlags = (isCaseInsensitive ? WriteableStringPool::fCompareCaseInsensitive : WriteableStringPool::fCompareDefault);
    AutoDeletePtr<WriteableStringPool> pStrings;
    RETURN_IF_FAILED(WriteableStringPool::CreateInstance(stringsFlags, &pStrings));

    RETURN_IF_FAILED(FileAtomPoolBuilder::CreateInstance(pDescription, pStrings, isCaseInsensitive, result));
    (*result)->m_flags |= fStringPoolIsOwned;
    pStrings.Detach();

    return S_OK;
}

HRESULT
FileAtomPoolBuilder::CreateInstance(
    __in PCWSTR pDescription,
    __in WriteableStringPool* pStrings,
    bool isCaseInsensitive,
    _Outptr_ FileAtomPoolBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pStrings == nullptr) || (pDescription == nullptr));
    RETURN_HR_IF(E_INVALIDARG, wcslen(pDescription) >= FileAtomPool::DescriptionLength);

    UINT32 flags = (isCaseInsensitive ? fIsCaseInsensitive : fDefault) | fIsNotSorted;
    AutoDeletePtr<FileAtomPoolBuilder> pRtrn = new FileAtomPoolBuilder();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pDescription, pStrings, flags));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileAtomPoolBuilder::CreateInstance(__in const IAtomPool* pCloneFrom, _Outptr_ FileAtomPoolBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pCloneFrom);

    AutoDeletePtr<FileAtomPoolBuilder> pRtrn;
    RETURN_IF_FAILED(FileAtomPoolBuilder::CreateInstance(pCloneFrom->GetDescription(), pCloneFrom->GetIsCaseInsensitive(), &pRtrn));

    RETURN_IF_FAILED(pRtrn->Extend(pCloneFrom->GetNumAtoms()));
    ;

    StringResult str;
    for (Atom::Index i = 0; i < pCloneFrom->GetNumAtoms(); i++)
    {
        if (!pCloneFrom->TryGetString(i, &str))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        Atom atom;
        RETURN_IF_FAILED(pRtrn->GetOrAddAtom(str.GetRef(), &atom));
        RETURN_HR_IF(E_DEF_ATOM_BAD_POOL, atom.GetIndex() != i);
    }

    *result = pRtrn.Detach();
    return S_OK;
}

FileAtomPoolBuilder::~FileAtomPoolBuilder()
{
    if (m_pStrings && (m_flags & fStringPoolIsOwned))
    {
        delete m_pStrings;
        m_pStrings = NULL;
    }
    m_sizeAtoms = m_numAtoms = 0;
    if (m_offset != NULL)
    {
        _DefFree(m_offset);
        m_offset = NULL;
    }
    if (m_hash != NULL)
    {
        _DefFree(m_hash);
        m_hash = NULL;
    }
}

HRESULT FileAtomPoolBuilder::Extend(__in size_t newSize)
{
    if (newSize <= m_sizeAtoms)
    {
        return S_OK;
    }

    RETURN_HR_IF(E_DEF_WRITEABLE_ATOMPOOL_FULL, newSize >= Atom::MaxAtomIndex);

    if ((!_DefArray_TryEnsureSize(&m_hash, DEFFILE_ATOMPOOL_HASHINDEX, m_sizeAtoms, newSize)) ||
        (!_DefArray_TryEnsureSize(&m_offset, UINT32, m_sizeAtoms, newSize)))
    {
        return E_OUTOFMEMORY;
    }

    if ((m_hash == NULL) || (m_offset == NULL))
    {
        return E_OUTOFMEMORY;
    }
    m_sizeAtoms = (Atom::Index)newSize;
    return S_OK;
}

HRESULT FileAtomPoolBuilder::GetOrAddAtom(__in PCWSTR pString, _Out_ Atom* result, __out_opt bool* pIsNewOut)
{
    *result = Atom::NullAtom;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pString));

    if (pIsNewOut != NULL)
    {
        *pIsNewOut = false;
    }

    Atom rtrn = Atom::NullAtom;
    if (TryGetAtom(pString, &rtrn))
    {
        *result = rtrn;
        return S_OK;
    }

    m_finalized = false;
    // otherwise, add the string.
    if (m_numAtoms >= m_sizeAtoms)
    {
        size_t newSize = ((m_sizeAtoms == 0) ? DefaultInitialSize : (m_sizeAtoms * 2));
        RETURN_IF_FAILED(Extend(newSize));
        DEF_ASSERT(m_sizeAtoms > m_numAtoms);
    }

    m_hash[m_numAtoms].hash = Atom::HashString(pString, m_hashMethod);
    m_hash[m_numAtoms].index = m_numAtoms;

    m_offset[m_numAtoms] = m_pStrings->GetOrAddStringOffset(pString);
    RETURN_HR_IF(E_ABORT, m_offset[m_numAtoms] == -1);

    rtrn.Set(m_numAtoms, m_poolIndex);
    m_numAtoms++;

    if (pIsNewOut != NULL)
    {
        *pIsNewOut = true;
    }

    *result = rtrn;
    return S_OK;
}

HRESULT FileAtomPoolBuilder::GetString(Atom atom, _Out_ PCWSTR* result) const
{
    *result = nullptr;

    if ((atom.GetIndex() == Atom::NullAtomIndex) && (atom.GetPoolIndex() == Atom::NullPoolIndex))
    {
        *result = Atom::NullString;
        return S_OK;
    }

    RETURN_HR_IF(E_DEF_ATOM_BAD_POOL, atom.GetPoolIndex() != m_poolIndex);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_INDEX), atom.GetIndex() >= m_numAtoms);

    *result = m_pStrings->GetString(m_offset[atom.GetIndex()]);

    return S_OK;
}

HRESULT FileAtomPoolBuilder::GetString(Atom::Index index, _Out_ PCWSTR* result) const
{
    *result = nullptr;
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_INDEX), index >= m_numAtoms);

    *result = m_pStrings->GetString(m_offset[index]);
    return S_OK;
}

bool FileAtomPoolBuilder::TryGetString(Atom atom, __inout_opt StringResult* pStringOut) const
{
    if ((atom.GetIndex() == Atom::NullAtomIndex) && (atom.GetPoolIndex() == Atom::NullPoolIndex))
    {
        return SUCCEEDED(StringResult::SetRef(pStringOut, Atom::NullString));
    }

    if (atom.GetPoolIndex() != m_poolIndex)
    {
        (void)StringResult::SetRef(pStringOut, NULL);
        // Not an error for a Try* function. Just return
        // false without setting an error.
        return false;
    }
    return TryGetString(atom.GetIndex(), pStringOut);
}

bool FileAtomPoolBuilder::TryGetString(Atom::Index index, __inout_opt StringResult* pStringOut) const
{

    (void)StringResult::SetRef(pStringOut, NULL);

    if (index >= m_numAtoms)
    {
        // Not an error for a Try* function. Just return
        // false without setting an error.
        return false;
    }

    return SUCCEEDED(m_pStrings->GetString(m_offset[index], pStringOut));
}

bool FileAtomPoolBuilder::TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const
{
    Atom::Index index;

    if (pString == nullptr)
    {
        return false;
    }

    if (DefString_IsEmpty(pString))
    {
        pAtomOut->Set(DEF_ATOM_NULL);
        return true;
    }

    if (!TryGetIndex(pString, &index))
    {
        if (pAtomOut)
            pAtomOut->Set(Atom::NullAtomIndex, Atom::NullPoolIndex);
        return false;
    }
    if (pAtomOut)
    {
        pAtomOut->Set(index, m_poolIndex);
    }
    return true;
}

bool FileAtomPoolBuilder::TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const
{
    Atom::Index i;
    Atom::Hash hash;

    if (pString == nullptr)
    {
        return false;
    }

    if (DefString_IsEmpty(pString))
    {
        // Either way we return the NULL atom.
        // it's the expected answer.
        if (pIndexOut)
            *pIndexOut = Atom::NullAtomIndex;
        return true;
    }

    hash = Atom::HashString(pString, m_hashMethod);
    for (i = 0; i < m_numAtoms; i++)
    {
        if (m_hash[i].hash == hash)
        {
            if (m_pStrings->Equals(m_offset[m_hash[i].index], pString))
            {
                if (pIndexOut)
                {
                    *pIndexOut = i;
                }
                return true;
            }
        }
    }
    if (pIndexOut)
        *pIndexOut = 0;
    return false;
}

bool FileAtomPoolBuilder::Contains(__in PCWSTR pString) const { return TryGetIndex(pString, NULL); }

bool FileAtomPoolBuilder::Contains(__in Atom atom) const
{
    return ((atom.GetPoolIndex() == m_poolIndex) && (atom.GetIndex() < m_numAtoms));
}

bool FileAtomPoolBuilder::Equals(__in Atom atom, __in PCWSTR pString) const
{
    PCWSTR pMyString;

    if (pString == nullptr)
    {
        return false;
    }

    if (!pString[0])
    {
        return ((atom.GetIndex() == Atom::NullAtomIndex) && (atom.GetPoolIndex() == Atom::NullPoolIndex));
    }

    if (FAILED(GetString(atom, &pMyString)))
    {
        return false;
    }

    if (GetIsCaseInsensitive())
    {
        return (DefString_ICompare(pString, pMyString) == Def_Equal);
    }
    return (DefString_Compare(pString, pMyString) == Def_Equal);
}

bool FileAtomPoolBuilder::IsValid() const
{
    if ((m_poolIndex == Atom::NullPoolIndex) || m_poolIndex == Atom::PoolIndexNone)
    {
        return false;
    }
    return true;
}

HRESULT FileAtomPoolBuilder::Finalize()
{
    if (!IsValid())
    {
        return E_DEF_ATOM_BAD_POOL;
    }
    m_finalized = true;
    return S_OK;
}

UINT32
FileAtomPoolBuilder::GetMaxSizeInBytes() const
{
    if (!m_finalized)
    {
        return 0;
    }
    return FileAtomPool::GetSizeInBytes(m_numAtoms, m_pStrings->GetNumCharsInPool());
}

HRESULT FileAtomPoolBuilder::Build(__out_bcount(cbBuffer) VOID* pBuffer, UINT32 cbBuffer, __out_opt UINT32* pcbWritten) const
{
    UINT32 cbAtomPoolSize = 0;
    DEFFILE_ATOMPOOL_HEADER header;

    RETURN_HR_IF_NULL(E_INVALIDARG, pBuffer);
    RETURN_HR_IF(E_DEF_NOT_READY, !m_finalized);

    if (pcbWritten)
    {
        *pcbWritten = 0;
    }

    cbAtomPoolSize = GetMaxSizeInBytes();
    __analysis_assume(cbAtomPoolSize > 0);

    RETURN_HR_IF(E_INVALIDARG, cbBuffer < cbAtomPoolSize);

    header.flags = m_flags;

    SecureZeroMemory(header.desc, DEFFILE_ATOMPOOL_DESC_LENGTH * sizeof(WCHAR));
    RETURN_IF_FAILED(DefString_CchCopy(header.desc, _countof(header.desc), m_description));

    header.desc[DEFFILE_ATOMPOOL_DESC_LENGTH - 1] = 0;

    header.cchPool = m_pStrings->GetNumCharsInPool();
    header.nAtoms = m_numAtoms;
    header.poolIndex = m_poolIndex;

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(pBuffer, cbBuffer));

    HRESULT hr = S_OK;
    DEFFILE_ATOMPOOL_HEADER* pHdr = _SECTION_BUILDER_NEXT(data, DEFFILE_ATOMPOOL_HEADER, &hr);
    RETURN_IF_FAILED(hr);

    *pHdr = header;

    DEFFILE_ATOMPOOL_HASHINDEX* pHashes = _SECTION_BUILDER_NEXT_ARRAY(data, m_numAtoms, DEFFILE_ATOMPOOL_HASHINDEX, &hr);
    RETURN_IF_FAILED(hr);

    size_t cbData = m_numAtoms * sizeof(DEFFILE_ATOMPOOL_HASHINDEX);
    errno_t err = memcpy_s(pHashes, cbData, m_hash, cbData);
    RETURN_IF_FAILED(ErrnoToHResult(err));

    UINT32* pOffsets = _SECTION_BUILDER_NEXT_ARRAY(data, m_numAtoms, UINT32, &hr);
    RETURN_IF_FAILED(hr);

    cbData = m_numAtoms * sizeof(UINT32);
    err = memcpy_s(pOffsets, cbData, m_offset, cbData);
    RETURN_IF_FAILED(ErrnoToHResult(err));

    WCHAR* pChars = _SECTION_BUILDER_NEXT_ARRAY(data, m_pStrings->GetNumCharsInPool(), WCHAR, &hr);
    RETURN_IF_FAILED(hr);

    cbData = m_pStrings->GetNumCharsInPool() * sizeof(WCHAR);
    err = memcpy_s(pChars, cbData, m_pStrings->GetBuffer(), cbData);
    RETURN_IF_FAILED(ErrnoToHResult(err));

    if (pcbWritten)
    {
        *pcbWritten = (UINT32)data.UsedBufferSizeInBytes();
    }
    return S_OK;
}

} // namespace Microsoft::Resources::Build
