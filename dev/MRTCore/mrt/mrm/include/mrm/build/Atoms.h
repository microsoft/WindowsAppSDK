// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/readers/Atoms.h"
#include "mrm/build/FileBuilder.h"
#include "mrm/build/WriteableStringPool.h"

namespace Microsoft::Resources::Build
{

class FileAtomPoolBuilder : public ISectionBuilder, public IAtomPoolWriter
{

private:
    enum Flags
    {
        fDefault = 0x0000,
        fIsCaseInsensitive = 0x0001,
        fIsNotSorted = 0x0004,
        fStringPoolIsOwned = 0x0100
    };

    bool m_finalized;

    UINT32 m_flags;
    Atom::HashMethod m_hashMethod;

    AtomPoolGroup* m_group;
    Atom::PoolIndex m_poolIndex;

    Atom::AtomCount m_numAtoms;
    Atom::AtomCount m_sizeAtoms;
    DEFFILE_ATOMPOOL_HASHINDEX* m_hash;
    UINT32* m_offset;
    WriteableStringPool* m_pStrings;
    WCHAR m_description[FileAtomPool::DescriptionLength];
    BaseFile::SectionIndex m_sectionIndex;

protected:
    static const int DefaultInitialSize = 10;

    FileAtomPoolBuilder();

    HRESULT Init(_In_opt_ PCWSTR pDescription, _In_ WriteableStringPool* pStrings, UINT32 flags);

    HRESULT Extend(__in size_t newSize);

public:
    static HRESULT CreateInstance(__in PCWSTR pDescription, bool isCaseInsensitive, _Outptr_ FileAtomPoolBuilder** result);
    static HRESULT CreateInstance(
        __in PCWSTR pDescription,
        __in WriteableStringPool* pStrings,
        bool isCaseInsensitive,
        _Outptr_ FileAtomPoolBuilder** result);
    static HRESULT CreateInstance(__in const IAtomPool* pCloneFrom, _Outptr_ FileAtomPoolBuilder** result);

    virtual ~FileAtomPoolBuilder();

    WriteableStringPool* GetStringPool() { return m_pStrings; }

    HRESULT GetOrAddAtom(__in PCWSTR pString, _Out_ Atom* result, __out_opt bool* pIsNewOut = NULL);
    AtomPoolGroup* GetAtomPoolGroup() const { return m_group; }
    void SetAtomPoolGroup(AtomPoolGroup* group) { m_group = group; }
    Atom::PoolIndex GetPoolIndex() const { return m_poolIndex; }

    void SetPoolIndex(Atom::PoolIndex index)
    {
        m_poolIndex = index;
        m_finalized = false;
    }

    bool GetIsCaseInsensitive() const { return ((m_flags & fIsCaseInsensitive) != 0); }
    HRESULT GetString(Atom, _Out_ PCWSTR* result) const;
    HRESULT GetString(Atom::Index, _Out_ PCWSTR* result) const;
    bool TryGetString(Atom, __inout_opt StringResult*) const;
    bool TryGetString(Atom::Index, __inout_opt StringResult*) const;
    bool TryGetAtom(__in PCWSTR, __out_opt Atom*) const;
    bool TryGetIndex(__in PCWSTR, __out_opt Atom::Index*) const;
    bool Contains(__in PCWSTR) const;
    bool Contains(__in Atom) const;
    bool Equals(__in Atom, __in PCWSTR) const;
    PCWSTR GetDescription() const { return m_description; }
    Atom::Index GetNumAtoms() const { return m_numAtoms; }

    bool IsValid() const;
    HRESULT Finalize();
    UINT32 GetMaxSizeInBytes() const;

    virtual HRESULT Build(__out_bcount(cbBuffer) VOID* pBuffer, UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return FileAtomPool::GetSectionTypeId(); }

    UINT16 GetFlags() const { return DEFFILE_IS_ATOM_POOL_SECTION; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return static_cast<UINT32>(GetPoolIndex()); }
    void SetSectionIndex(BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }
};

#define E_DEF_WRITEABLE_ATOMPOOL_FULL _DEF_MAKE_STATUS(_DEF_FACILITY_BUILD, 0x10)

#define DefAtomPool_IsFull(NATOMS, PSTATUS) \
    Def_CheckIsGreaterOrEqual(NATOMS, Atom::MaxAtomIndex, L"AtomPool can not be expanded further", E_DEF_WRITEABLE_ATOMPOOL_FULL, PSTATUS)

} // namespace Microsoft::Resources::Build