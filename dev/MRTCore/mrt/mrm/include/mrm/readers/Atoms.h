// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/common/file/FileAtomPool.h"
#include "mrm/readers/BaseFile.h"

namespace Microsoft::Resources
{

class IUIDFile;

class FileAtomPool : public IAtomPool, public FileSectionBase
{
public:
    typedef DEFFILE_ATOMPOOL_HASHINDEX HashIndex;

    static const int DescriptionLength = DEFFILE_ATOMPOOL_DESC_LENGTH;

protected:
    UINT32 m_flags{ 0 };
    Atom::PoolIndex m_poolIndex{ DEF_ATOM_NULL_POOL_INDEX };
    AtomPoolGroup* m_pAll{ nullptr };

    UINT32 m_cbTotalSize{ 0 };

    const DEFFILE_ATOMPOOL_HEADER* m_pHeader{ nullptr };
    const HashIndex* m_pHashes{ nullptr };
    const UINT32* m_pOffsets{ nullptr };
    const WCHAR* m_pPool{ nullptr };
    const WCHAR* m_pPoolGroup{ nullptr };

    static const DEFFILE_SECTION_TYPEID gAtomPoolSectionType;

    FileAtomPool();

    HRESULT Initialize(__in_opt const IFileSection* pSection, __in_bcount(cbData) const void* pData, __in int cbData);

public:
    static HRESULT CreateInstance(__in_bcount(cbData) const void* pData, __in UINT32 cbData, _Outptr_ FileAtomPool** result);
    static HRESULT CreateInstance(__in const IFileSection* pFileSection, _Outptr_ FileAtomPool** result);

    /*!
         * Returns a new FileAtomPool, initialized from the same
         * data as another existing file atom pool, using a supplied
         * index rather than that supplied in the data itself.
         */
    static HRESULT CreateInstance(__in const FileAtomPool* pFrom, __in Atom::PoolIndex newPoolIndex, _Outptr_ FileAtomPool** result);

    virtual ~FileAtomPool();

    // Gets the AtomPoolGroup to which this atom pool belongs.
    AtomPoolGroup* GetAtomPoolGroup() const { return m_pAll; }

    /*!
         * Sets the AtomPoolGroup to which this atom pool belongs.
         * Does _not_ try to verify that the group has a reference
         * to it.
         */
    void SetAtomPoolGroup(AtomPoolGroup* pGroup) { m_pAll = pGroup; }

    PCWSTR GetDescription() const { return m_pHeader->desc; }

    // Gets the index of this atom pool in the group that contains it.
    Atom::PoolIndex GetPoolIndex() const { return m_poolIndex; }

    /*!
         * Sets the index of this atom pool.  Does not
         * attempt to verify that the group has a matching
         * reference.
         */
    void SetPoolIndex(Atom::PoolIndex index) { m_poolIndex = index; }

    /*!
         * Gets a value indicating if this atom pool uses
         * case-insensitive comparisons.
         * TODO: Generalize for other comparison types
         * such as culture-sensitive or normalized?
         */
    bool GetIsCaseInsensitive() const { return ((m_pHeader->flags & DEFFILE_ATOMPOOL_HASH_CASE_INSENSITIVE) != 0); }

    /*!
         * Retrieves a string that corresponds to a specified index from
         * an atom pool.  Returns NULL if if the atom comes from another
         * pool or is illegal.
         */
    bool TryGetString(Atom atom, __inout_opt StringResult* pStringOut) const;

    /*!
         * Retrieves a string from an atom pool by index.  Returns NULL
         * if the index is out of range.
         *
         */
    bool TryGetString(Atom::Index index, __inout_opt StringResult* pStringOut) const;

    /*!
         * Gets an atom that corresponds to a specified string from an atom
         * pool.   Sets pAtomOut to DEF_ATOM_NULL and returns FALSE if no
         * matching string is found.
         */
     _Success_(return == true)
    bool TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const;

    /*!
         * Gets the index that corresponds to a specified string from an atom
         * pool.   Sets pIndexOut to Atom::NullAtomIndex and returns FALSE if
         * no matching string is found.
         */
     _Success_(return == true)
    bool TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const;

    /*!
         * Determines if the atom pool contains an atom that corresponds
         * to a specified string.
         */
    bool Contains(__in PCWSTR pString) const;

    /*!
         * Determines if the atom pool contains a specified atom.
         */
    bool Contains(__in Atom atom) const;

    /*!
         * Determines if an atom matches a specified string.
         * Reports an error in pStatus if the atom does not come from
         * this atom pool.
         */
    bool Equals(__in Atom atom, __in PCWSTR pString) const;

    Atom::Index GetNumAtoms() const { return m_pHeader->nAtoms; }

    /*!
         * Gets the typeid for an atom pool section.
         */
    static const DEFFILE_SECTION_TYPEID GetSectionTypeId();

    /*!
         * Reports the size needed to hold an atom pool with the
         * specified number of atoms and pool characters.
         */
    static UINT32 GetSizeInBytes(__in UINT32 nAtoms, __in UINT32 cchPool);

    static UINT32 GetSizeInBytes(__in const DEFFILE_ATOMPOOL_HEADER* header);

    UINT32 GetMaxSizeInBytesForStrings(__in_ecount(nStrings) PCWSTR* ppStrings, __in UINT32 nStrings) const;

    static HRESULT ValidateHeader(__in_bcount(cbData) const void* pData, __in UINT32 cbData, __out_opt UINT32* pcbTotalRtrn);

protected:
    static HashIndex* HashIndex_Init(__inout HashIndex* pSelf, __in Atom::Hash hash, __in Atom::Index index);

    _Success_(return == true)
    bool TryGetHashIndex(__in PCWSTR pString, __out_opt HashIndex* pIndexOut) const;

    DEFCOMPARISON CompareAtIndex(__in Atom::Index index, __in PCWSTR pString) const;

    DEFCOMPARISON CompareAtHashIndex(__in Atom::Index hashIndex, __in PCWSTR pString) const;
};

class FileAtoms : public DefObject
{
public:
    /*!
         * Extracts all atom pools from supplied DefFile into a newly
         * allocated AtomPoolGroup.
         */
    static HRESULT CreateAtomPoolGroupFromFile(__in const BaseFile* pFile, _Outptr_ AtomPoolGroup** result);

    /*!
         * Extracts all atom pools from DEF file into a
         * supplied DEFFILE_ATOMS.
         */
    static HRESULT InitFromFile(__inout AtomPoolGroup* pAtoms, __in const BaseFile* pFile);

    /*!
         * Remaps atom pools from one group of atom pools to another
        */
    static HRESULT RemapAtomPools(
        __in AtomPoolGroup* pSrcGroup,
        __inout AtomPoolGroup* pDestGroup,
        __in_ecount(nMappings) DEFFILE_ATOMPOOL_MAPPING* pMappings,
        __in int nMappings);
};

} // namespace Microsoft::Resources
