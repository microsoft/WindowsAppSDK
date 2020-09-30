// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Microsoft::Resources
{

class RemapUInt16 : DefObject
{
public:
    RemapUInt16();

    static HRESULT CreateInstance(_In_ int initialSize, _Outptr_ RemapUInt16** result);

    static HRESULT CreateInstance(_In_ const RemapUInt16* pCloneFrom, _Outptr_ RemapUInt16** result);

    using DefObject::operator delete;

    virtual ~RemapUInt16();

    int Size() const { return m_sizeMapping; }

    bool IsPresent(_In_ UINT16 item) const;

    bool TryGetMapping(_In_ UINT16 from, _Out_ UINT16* pTo) const;

    bool TrySetMapping(_In_ UINT16 from, _In_ UINT16 to);

    HRESULT SetOrChangeMapping(_In_ UINT16 from, _In_ UINT16 to);

    void Reset();

    HRESULT EnsureSize(_In_ int newSize);

protected:
    bool SetIsPresent(_In_ UINT16 item);

    int m_sizeMapping;
    _Field_size_(m_sizeMapping) UINT16* m_pMapping;

    static const int PresenceMaskWidth = 64;

    union
    {
        UINT64 mask;
        UINT64* masks;
    } m_present;
};

class RemapAtomPool : DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ Atom::PoolIndex sourcePoolIndex,
        _In_ Atom::PoolIndex targetPoolIndex,
        _In_ int numMappedAtomIndexes,
        _In_reads_(numMappedAtomIndexes) const Atom::SmallIndex* mappedAtomIndexes,
        _Outptr_ RemapAtomPool** result);

    using DefObject::operator delete;

    virtual ~RemapAtomPool();

    _Success_(return ) bool TryGetMappedIndex(_In_ Atom::Index sourceAtomIndex, _Out_ Atom::Index* pTargetAtomIndexOut) const;

    _Success_(return ) bool TryGetMappedAtom(_In_ Atom sourceAtom, _Out_ Atom* pTargetAtomOut) const;

    Atom::PoolIndex GetSourcePoolIndex() const { return m_sourcePoolIndex; }
    Atom::PoolIndex GetTargetPoolIndex() const { return m_targetPoolIndex; }

protected:
    RemapAtomPool() : m_mappedAtomIndexes(nullptr) {}

    HRESULT Init(
        _In_ int sourcePoolIndex,
        _In_ int targetPoolIndex,
        _In_ int numMappedAtomIndexes,
        _In_reads_(numMappedAtomIndexes) const Atom::SmallIndex* mappedAtomIndexes);

    int m_sourcePoolIndex;
    int m_targetPoolIndex;
    int m_numMappedAtomIndexes;

    _Field_size_(m_numMappedAtomIndexes) Atom::SmallIndex* m_mappedAtomIndexes;
};

/*! 
     * The RemapInfo class contains mappings for any parts of a file that
     * might need to be remapped when copying sections from one file to
     * another or when interpreting a mapped file.
     */
class RemapInfo : DefObject
{
public:
    RemapInfo();

    /*! 
         * Creates a new empty \see RemapInfo.
         * 
         * \param pStatus
         * Status object to report success or failure.  \see RemapInfo::New guarantees
         * that reported error status matches the return value - it will always
         * report an error if it returns NULL, and will never report an error if
         * it returns a value other than NULL.
         * \return RemapInfo*
         * Returns a 
         */
    static HRESULT CreateInstance(_Outptr_ RemapInfo** result);

    static HRESULT Copy(_In_ RemapInfo* pRemap, _Outptr_ RemapInfo** result);

    using DefObject::operator delete;

    virtual ~RemapInfo();

    /*! 
         * Sets the section mapping in a \see RemapInfo to a specified size.
         * 
         * \param numSections
         * If numSections is greater than zero, the section mapping array is
         * created or resized to the specified size.  If numSections is 0,
         * the section mapping array is freed.  Values less than 0 cause an error.
         * 
         * \param pSectionMapping
         * If present, specifies the section mappings used to initialize the
         * \see RemapInfo.   If pSectionMapping is NULL, the section mapping 
         * array is initialized to yield a no-op mapping (each index maps to itself).
         * It is an error to specify a non-NULL pSectionMapping if numSections is zero.
         *
         * \param pStatus
         * Status object that reports details if an error occurs.
         *
         * \return bool
         * Returns true on success, false if an error occurs.  If SetSectionMapping
         * returns false, pStatus contains additional information about the error.
         */
    HRESULT SetSectionMapping(_In_ BaseFile::SectionCount numSections, _In_reads_opt_(numSections) BaseFile::SectionIndex* pSectionMapping);

    /*! 
         * Sets the atom pool mapping in a \see RemapInfo to a specified size.
         * 
         * \param numPools
         * If numPools is greater than zero, the atom pool mapping array is
         * created or resized to the specified size.  If numPools is 0,
         * the atom pool mapping array is freed.  Values less than 0 cause an error.
         * 
         * \param pPools
         * If present, specifies the atom pool mappings used to initialize the
         * \see RemapInfo.   If pPools is NULL, the atom pool mapping array is
         * initialized to yield a no-op mapping (each index maps to itself).
         * It is an error to specify a non-NULL pPools if numPools
         * is zero.
         *
         * \param pStatus
         * Status object that reports details if an error occurs.
         *
         * \return bool
         * Returns true on success, false if an error occurs.  If SetAtomPoolMapping
         * returns false, pStatus contains additional information about the error.
         */
    HRESULT SetAtomPoolMappingArray(_In_ Atom::PoolCount numPools, _In_reads_opt_(numPools) Atom::PoolIndex* pPools);

    /*! 
         * Adds a mapping for a single atom pool.
         * 
         * \param fromPool
         * The index of the pool to be mapped from.
         *
         * \param toPool
         * The index of the pool to be mapped to.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    HRESULT SetAtomPoolMapping(_In_ Atom::PoolIndex fromPool, _In_ Atom::PoolIndex toPool);

    /*! 
         * Gets the number of elements in the section mapping.
         * 
         * \return BaseFile::SectionCount
         * The number of elements in the section mapping.
         */
    BaseFile::SectionCount GetNumSections() const { return m_numSections; }

    /*! 
         * Gets a mapping for a single section index.
         * 
         * \param from
         * The section index to be remapped.
         * 
         * \param pStatus
         * Returns error details if the section remap fails.
         * 
         * \return BaseFile::SectionIndex
         * Returns the new section index.  If the section index is out
         * of range or if no mapping is defined for the section, reports
         * an appropriate error in pStatus.
         */
    HRESULT GetSectionMapping(_In_ BaseFile::SectionIndex from, _Out_ BaseFile::SectionIndex* index) const;

    /*! 
         * Gets a mapping for a single section index, if defined.
         * 
         * \param from
         * The section index to be remapped.
         *
         * \param pStatus
         * If non-NULL, returns details when an error occurs. TryGetSectionMapping
         * only reports an error if the index to be mapped is illegal
         * or out of range.  If no mapping is defined for the section,
         * it returns success.
         *
         * \param pToOut
         * If non-NULL, the new section index is returned in pToOut.
         * 
         * \return bool
         * Returns true if a valid section mapping was found, false otherwise.
         */
    bool TryGetSectionMapping(_In_ BaseFile::SectionIndex from, _Out_opt_ BaseFile::SectionIndex* pToOut) const;

    /*! 
         * Gets the section mapping for a \see RemapInfo.  Note that this 
         * method returns a pointer to the actual internal member and that
         * the returned value can be edited to change the contents of the
         * \see RemapInfo object.
         * 
         * \param pNumSectionsOut
         * If pNumSectionsOut is non-NULL, this method uses it to report the
         * number of elements in the section mapping.
         * 
         * \return BaseFile::SectionIndex*
         * Returns an pointer to the internal section mapping of the
         * \see RemapInfo object.
         */
    BaseFile::SectionIndex* GetSectionMapping(_Out_opt_ BaseFile::SectionCount* pNumSectionsOut = nullptr) const
    {
        if (pNumSectionsOut)
        {
            *pNumSectionsOut = m_numSections;
        }
        return m_pSectionMapping;
    }

    /*! 
         * Gets the number of elements in the atom pool mapping.
         * 
         * \return Atom::PoolCount
         * The number of elements in the atom pool mapping.
         */
    Atom::PoolCount GetNumAtomPools() const { return m_numPools; }

    /*! 
         * Gets a mapping for a single atom pool index.
         * 
         * \param from
         * The atom pool index to be remapped.
         * 
         * \param pStatus
         * Returns error details if the atom pool remap fails.
         * 
         * \return Atom::PoolIndex
         * Returns the new atom pool index.  If the atom pool index is out
         * of range or if no mapping is defined for the atom pool, reports
         * an appropriate error in pStatus.
         */
    HRESULT GetAtomPoolMapping(_In_ Atom::PoolIndex from, _Out_ Atom::PoolIndex* index) const;

    /*! 
         * Gets a mapping for a single atom pool index, if defined.
         * 
         * \param from
         * The atom pool index to be remapped.
         *
         * \param pStatus
         * if non-NULL, returns details if an error occurs.  TryGetAtomPoolMapping
         * only reports an error if the index to be mapped is illegal
         * or out of range.  If no mapping is defined for the atom pool,
         * it returns success.
         *
         * \param pToOut
         * If non-NULL, the new atom pool index is returned in pToOut.
         * 
         * \return bool
         * Returns true if a valid atom pool mapping was found, false otherwise.
         */
    bool TryGetAtomPoolMapping(_In_ Atom::PoolIndex from, _Out_opt_ Atom::PoolIndex* pToOut) const;

    /*! 
         * Gets the atom pool mapping for a \see RemapInfo.  Note that this 
         * method returns a pointer to the actual internal member and that
         * the returned value can be edited to change the contents of the
         * \see RemapInfo object.
         * 
         * \param pNumPoolsOut
         * If pNumPoolsOut is non-NULL, this method uses it to report the
         * number of elements in the atom pool mapping.
         * 
         * \return Atom::PoolIndex*
         * Returns an pointer to the internal atom pool mapping of the
         * \see RemapInfo object.
         */
    Atom::PoolIndex* GetAtomPoolMapping(_Out_opt_ Atom::PoolCount* pNumPoolsOut = nullptr) const
    {
        if (pNumPoolsOut)
        {
            *pNumPoolsOut = m_numPools;
        }
        return m_pPoolMapping;
    }

    /*! 
         * Remaps an atom using the pool mappings defined in this \see RemapInfo.
         * 
         * \param atom
         * The \see Atom to be remapped.
         *
         * \param pStatus
         * Reports details if an error occurs.
         * 
         * \return Atom
         * Returns the remapped atom, or the Null atom if an error occurs.
         */
    Atom RemapAtom(_In_ Atom atom) const;

    /*! 
         * Remaps an atom using the pool mappings defined in this \ref RemapInfo.
         * 
         * \param atom
         * The \ref Atom to be remapped.
         *
         * \param pStatus
         * Reports details if an error occurs.
         * 
         * \param pAtomRtrn
         * Used to return the remapped atom.  Returns the Null atom if no mapping
         * is poosible or an error occurs.
         *
         * \return Atom
         * Returns true if the atom is remapped, false if no mapping is found or
         * an error occurs.
         */
    HRESULT RemapAtom(_In_ Atom atom, _Out_opt_ Atom* pAtomRtrn) const;

    /*! 
         * Tries to remap an atom using the pool mappings defined in this 
         * \see RemapInfo.
         * 
         * \param atom
         * The \see Atom to be remapped.
         *
         * \param pStatus
         * Reports details if an error occurs.
         *
         * \param pAtomRtrn
         * Return the remapped \see Atom.
         * 
         * \return bool
         * Returns true on success, false otherwise.
         */
    bool TryRemapAtom(_In_ Atom atom, _Out_opt_ Atom* pAtomRtrn) const;

    /*! 
         * Remaps an atom using the pool mappings defined in a suppplied
         * \see RemapInfo.
         * 
         * \param pRemapInfo
         * The \see RemapInfo used to look up the mapping, or NULL to do
         * no remapping.
         *
         * \param atom
         * The \see Atom to be remapped.
         *
         * \param pStatus
         * Reports details if an error occurs.
         * 
         * \return Atom
         * Returns the remapped atom, or the Null atom if an error occurs. 
         * If pRemapInfo is NULL, the returned \see Atom will be the same
         * as the one that was passed it.
         */
    static Atom RemapAtom(_In_ RemapInfo* pRemapInfo, _In_ Atom atom) { return (pRemapInfo ? pRemapInfo->RemapAtom(atom) : atom); }

    /*! 
         * Tries to remap an atom using the pool mappings defined in a 
         * supplied \see RemapInfo.
         * 
         * \param pRemapInfo
         * The \see RemapInfo used to look up the mapping, or NULL to do
         * no remapping.
         *
         * \param atom
         * The \see Atom to be remapped.
         *
         * \param pStatus
         * Reports details if an error occurs.
         *
         * \param pAtomRtrn
         * Return the remapped \see Atom.
         * 
         * \return bool
         * Returns true on success, false otherwise.
         */
    static bool TryRemapAtom(_In_ RemapInfo* pRemapInfo, _In_ Atom atom, _Out_opt_ Atom* pAtomRtrn)
    {
        if (!pRemapInfo)
        {
            if (pAtomRtrn)
            {
                *pAtomRtrn = atom;
            }
            return true;
        }
        return pRemapInfo->TryRemapAtom(atom, pAtomRtrn);
    }

private:
    BaseFile::SectionCount m_numSections;
    BaseFile::SectionIndex* m_pSectionMapping;

    Atom::PoolCount m_numPools;
    Atom::PoolIndex* m_pPoolMapping;
};

} // namespace Microsoft::Resources
