// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma warning(disable : 4290)
#pragma once

namespace Microsoft::Resources
{

struct Atom
{
private:
    DEF_ATOM m_defAtom;

public:
    typedef DEF_ATOM_INDEX Index;
    typedef DEF_ATOM_COUNT AtomCount;
    typedef DEF_ATOM_POOL_INDEX PoolIndex;
    typedef DEF_ATOM_POOL_COUNT PoolCount;

    typedef DEF_ATOM_INDEX_SMALL SmallIndex;
    typedef DEF_ATOM_COUNT_SMALL SmallCount;
    typedef DEF_ATOM_POOL_INDEX_SMALL SmallPoolIndex;
    typedef DEF_ATOM_POOL_COUNT_SMALL SmallPoolCount;

    typedef DEF_ATOM_COMPARISON Comparison;

    static const Index NullAtomIndex = 0;
    static const Index IndexNone = DEF_ATOM_INDEX_NONE;
    static const Index MaxAtomIndex = DEF_ATOM_MAX_INDEX;
    static const AtomCount MaxAtomCount = DEF_ATOM_MAX_COUNT;

    static const AtomCount MaxAtomCountSmall = DEF_ATOM_MAX_COUNT_SMALL;
    static const Index MaxAtomIndexSmall = DEF_ATOM_MAX_INDEX_SMALL;
    static const SmallIndex SmallIndexNone = DEF_ATOM_MAX_INDEX_SMALL;

    static const PoolCount MaxPoolCountSmall = DEF_ATOM_MAX_POOL_COUNT_SMALL;
    static const PoolIndex MaxPoolIndexSmall = DEF_ATOM_MAX_POOL_INDEX_SMALL;

    static const PoolIndex NullPoolIndex = DEF_ATOM_NULL_POOL_INDEX;
    static const PoolIndex PoolIndexNone = DEF_ATOM_POOL_INDEX_NONE;
    static const PoolIndex MaxPoolIndex = DEF_ATOM_MAX_POOL_INDEX;
    static const PoolCount MaxPoolCount = DEF_ATOM_MAX_POOL_COUNT;
    static const PCWSTR NullString;

    static const Atom NullAtom;

    Atom() { Set(NullAtomIndex, NullPoolIndex); }

    Atom(_In_ Index index, _In_ PoolIndex poolIndex) { Set(index, poolIndex); }

    Atom(_In_ DEF_ATOM atom) : m_defAtom(atom) {}

    Atom(_In_ DEF_ATOM_SMALL atom) { Set(atom.s.index, atom.s.poolIndex); }

    DEF_ATOM GetAtom() const { return m_defAtom; }

    bool IsNull() const { return (m_defAtom.val == 0); }

    bool IsValidNonNull() const { return ((m_defAtom.s.index >= 0) && (m_defAtom.s.poolIndex > 0)); }

    bool IsValidOrNull() const { return ((m_defAtom.val == 0) || ((m_defAtom.s.index >= 0) && (m_defAtom.s.poolIndex > 0))); }

    bool IsValidSmallAtom() const
    {
        // pool & index must both fit in 15 bits
        return ((m_defAtom.uVal & 0xFFFF8000FFFF8000) == 0);
    }

    _Success_(return ) _Check_return_ bool TryGetSmallAtom(_Inout_opt_ DEF_ATOM_SMALL* atom) const
    {
        if (IsValidSmallAtom())
        {
            if (atom != nullptr)
            {
                atom->s.index = static_cast<DEF_ATOM_INDEX_SMALL>(m_defAtom.s.index);
                atom->s.poolIndex = static_cast<DEF_ATOM_POOL_INDEX_SMALL>(m_defAtom.s.poolIndex);
            }

            return true;
        }

        return false;
    }

    HRESULT GetSmallAtom(_Inout_opt_ DEF_ATOM_SMALL* atom) const
    {
        if (IsValidSmallAtom())
        {
            if (atom != nullptr)
            {
                atom->s.index = static_cast<DEF_ATOM_INDEX_SMALL>(m_defAtom.s.index);
                atom->s.poolIndex = static_cast<DEF_ATOM_POOL_INDEX_SMALL>(m_defAtom.s.poolIndex);
            }
            return S_OK;
        }

        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    DEF_ATOM_SMALL GetSmallAtom() const
    {
        DEF_ATOM_SMALL smallAtom;

        if (IsValidSmallAtom())
        {
            smallAtom.s.poolIndex = static_cast<DEF_ATOM_POOL_INDEX_SMALL>(m_defAtom.s.poolIndex);
            smallAtom.s.index = static_cast<DEF_ATOM_INDEX_SMALL>(m_defAtom.s.index);
        }
        else
        {
            smallAtom.val = 0;
        }

        return smallAtom;
    }

    void SetFromUInt64(_In_ UINT64 data) { m_defAtom.uVal = data; }

    void SetFromInt64(_In_ INT64 data) { m_defAtom.val = data; }

    void Set(_In_ Index index, _In_ PoolIndex poolIndex)
    {
        m_defAtom.s.poolIndex = poolIndex;
        m_defAtom.s.index = index;
    }

    void Set(_In_ DEF_ATOM atom) { m_defAtom = atom; }

    void Set(_In_ Atom atom) { m_defAtom = atom.GetAtom(); }

    UINT64 GetUInt64() const { return m_defAtom.uVal; }
    INT64 GetInt64() const { return m_defAtom.val; }

    PoolIndex GetPoolIndex() const { return m_defAtom.s.poolIndex; }
    Index GetIndex() const { return m_defAtom.s.index; }
    Comparison Compare(_In_ Atom) const;

    bool IsEqual(_In_ Atom atom) const { return (m_defAtom.val == atom.GetInt64()); }

    bool IsEqual(_In_ DEF_ATOM_SMALL atom) const
    {
        return ((m_defAtom.s.index == atom.s.index) && (m_defAtom.s.poolIndex == atom.s.poolIndex));
    }

    bool operator==(_In_ const Atom& atom) const { return (m_defAtom.val == atom.GetInt64()); }

    bool operator!=(_In_ const Atom& atom) const { return (m_defAtom.val != atom.GetInt64()); }

    Atom& operator=(int i)
    {
        SetFromInt64(static_cast<INT64>(i));
        return *this;
    }

    typedef DEF_ATOM_HASH Hash;
    typedef DEF_ATOM_HASH_METHOD HashMethod;

    static const HashMethod HashMethodDefault = DEF_HASH_DEFAULT;
    static const HashMethod HashMethodCaseInsensitive = DEF_HASH_CASE_INSENSITIVE;

    static bool IsValidPoolIndex(Atom::Index index) { return (index > 0) && (index <= DEF_ATOM_MAX_INDEX); }

    static bool IsValidSmallPoolIndex(Atom::PoolIndex index) { return (index > 0) && (index <= MaxPoolIndexSmall); }

    static bool IsValidSmallAtomIndex(Atom::Index index) { return (index >= 0) && (index <= MaxAtomIndexSmall); }

    static bool IsValidSmallAtomCount(Atom::AtomCount numAtoms) { return (numAtoms <= MaxAtomCountSmall); }

    static HRESULT GetSmallPoolIndex(_In_ PoolIndex index, _Out_ SmallPoolIndex* smallIndexResult)
    {
        if ((smallIndexResult == nullptr) || !IsValidSmallPoolIndex(index))
        {
            return E_INVALIDARG;
        }

        *smallIndexResult = static_cast<SmallPoolIndex>(index);
        return S_OK;
    }

    HRESULT GetSmallPoolIndex(_Out_ SmallPoolIndex* smallIndexResult) const
    {
        return GetSmallPoolIndex(m_defAtom.s.poolIndex, smallIndexResult);
    }

    static HRESULT GetSmallIndex(_In_ Index index, _Out_ SmallIndex* smallIndexResult)
    {
        if ((smallIndexResult == nullptr) || !IsValidSmallPoolIndex(index))
        {
            return E_INVALIDARG;
        }

        *smallIndexResult = static_cast<SmallIndex>(index);
        return S_OK;
    }

    HRESULT GetSmallIndex(_Out_ SmallIndex* smallIndexResult) const { return GetSmallIndex(m_defAtom.s.index, smallIndexResult); }

    static Hash HashString(_In_ PCWSTR str, _In_ HashMethod hashType);

    //! Generate hash with the default hash method
    static Hash HashString(PCWSTR str) { return HashString(str, HashMethodDefault); }

    /*!
         * \name Class-specific new/delete operators
         * @{
         * We can't derive from DefObject because we don't want a vtbl,
         * but we have to be sure we're allocated consistently.   So we
         * implement class-specific new and delete.
         */

    static void* operator new(size_t size) { return DefObject::operator new(size); }

    static void* operator new(size_t, _In_opt_ void* p) { return p; }

    static void* operator new(size_t size, const struct nothrow_t&) throw() { return DefObject::operator new(size, nothrow); }

    static void* operator new[](size_t size) { return DefObject::operator new[](size); }

    static void* operator new[](size_t size, const nothrow_t&) throw() { return DefObject::operator new[](size, nothrow); }

    static void operator delete(_In_opt_ void* p) { DefObject::operator delete(p); }

    static void operator delete(_In_opt_ void* p, const nothrow_t&) throw() { DefObject::operator delete(p, nothrow); }

    static void operator delete[](_In_opt_ void* p) { DefObject::operator delete[](p); }

    static void operator delete[](_In_opt_ void* p, const nothrow_t&) throw() { DefObject::operator delete[](p, nothrow); }
    //! @}
};

class AtomPoolGroup;

class IAtomPool : public DefObject
{
public:
    virtual ~IAtomPool() {}

    /*!
         * Gets the AtomPoolGroup to which this atom pool belongs.
         */
    virtual AtomPoolGroup* GetAtomPoolGroup() const = 0;

    /*!
         * Sets the AtomPoolGroup to which this atom pool belongs.
         * Does _not_ try to verify that the group has a reference
         * to it.
         */
    virtual void SetAtomPoolGroup(_In_ AtomPoolGroup* pGroup) = 0;

    /*!
         * Gets the index of this atom pool in the group
         * that contains it.
         */
    virtual Atom::PoolIndex GetPoolIndex() const = 0;

    /*!
         * Gets the small index of this atom pool in the group
         * that contains it.
         * \param smallIndexResult
         * Returns the small pool index for this pool.
         *
         * \return HRESULT
         * - HRESULT_FROM_WIN32(ERROR_INVALID_INDEX) if the pool index is too large to fit in
         *   a small index.
         */
    HRESULT GetSmallPoolIndex(_Out_ Atom::SmallPoolIndex* smallIndexResult) const
    {
        return Atom::GetSmallPoolIndex(GetPoolIndex(), smallIndexResult);
    }

    /*!
         * Sets the index of this atom pool.  Does not
         * attempt to verify that the group has a matching
         * reference.
         */
    virtual void SetPoolIndex(_In_ Atom::PoolIndex) = 0;

    /*!
         * Gets a value indicating if this atom pool uses
         * case-insensitive comparisons.
         * TODO: Generalize for other comparison types
         * such as culture-sensitive or normalized?
         */
    virtual bool GetIsCaseInsensitive() const = 0;

    /*!
         * Retrieves a string that corresponds to a specified index from
         * an atom pool.  Returns NULL if if the atom comes from another
         * pool or is illegal.
         */
    virtual bool TryGetString(_In_ Atom atom, _Inout_opt_ StringResult* resultString) const = 0;

    /*!
         * Retrieves a string from an atom pool by index.  Returns NULL
         * if the index is out of range.
         *
         */
    virtual bool TryGetString(_In_ Atom::Index index, _Inout_opt_ StringResult* resultString) const = 0;

    /*!
         * Gets an atom that corresponds to a specified string from an atom
         * pool.   Sets pAtomOut to Atom::NullAtom and returns FALSE if no
         * matching string is found.
         */
    virtual bool TryGetAtom(_In_ PCWSTR str, _Out_opt_ Atom* resultAtom) const = 0;

    /*!
         * Gets an atom that corresponds to a specified index from an atom
         * pool.   Sets resultAtom to Atom::NullAtom and returns FALSE if no
         * matching string is found.
         */
    _Success_(return == true)
    virtual bool TryGetAtom(_In_ Atom::Index index, _Out_opt_ Atom* resultAtom) const
    {
        if (index >= GetNumAtoms())
        {
            return false;
        }

        if (resultAtom != nullptr)
        {
            resultAtom->Set(index, GetPoolIndex());
        }

        return true;
    }

    /*!
         * Gets the index that corresponds to a specified string from an atom
         * pool.   Sets resultIndex to Atom::NullAtomIndex and returns FALSE if
         * no matching string is found.
         */
    virtual bool TryGetIndex(_In_ PCWSTR str, _Out_opt_ Atom::Index* resultIndex) const = 0;

    HRESULT GetIndex(_In_ PCWSTR str, _Out_opt_ Atom::Index* resultIndex) const
    {
        if (!TryGetIndex(str, resultIndex))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        return S_OK;
    }

    HRESULT GetIndex(_In_ Atom name, _Out_opt_ Atom::Index* resultIndex) const
    {
        if (name.GetPoolIndex() != GetPoolIndex())
        {
            return E_DEF_ATOM_BAD_POOL;
        }

        if (name.GetIndex() >= GetNumAtoms())
        {
            return HRESULT_FROM_WIN32(ERROR_INVALID_INDEX);
        }

        if (resultIndex != nullptr)
        {
            *resultIndex = name.GetIndex();
        }
        return S_OK;
    }

    /*!
         * Determines if the atom pool contains an atom that corresponds
         * to a specified string.
         */
    virtual bool Contains(_In_ PCWSTR stringToFind) const = 0;

    /*!
         * Determines if the atom pool contains a specified atom.
         */
    virtual bool Contains(_In_ Atom atom) const = 0;

    /*!
         * Determines if the atom pool contains a specified index.
         */
    virtual bool Contains(_In_ Atom::Index index) const { return (index < GetNumAtoms()); }

    /*!
         * Determines if an atom matches a specified string.
         * Reports an error in pStatus if the atom does not come from
         * this atom pool.
         */
    virtual bool Equals(_In_ Atom atom, _In_ PCWSTR str) const = 0;

    /*!
        * Gets the description of the atom pool. Description doesn't have any functional use now but we keep it around for debugging purpose
        */
    virtual PCWSTR GetDescription() const = 0;

    /*!
        * Returns the number of atoms in the pool.
        */
    virtual Atom::Index GetNumAtoms() const = 0;

    // Most pools currently don't implement this so default to a non-implementation.
    virtual HRESULT Clone(_Outptr_ IAtomPool** /* clonedPool */) { return E_NOTIMPL; }
};

class IAtomPoolWriter : public IAtomPool
{
public:
    virtual ~IAtomPoolWriter() {}

    /*!
        * get or add string
        */
    virtual HRESULT GetOrAddAtom(_In_ PCWSTR str, _Out_ Atom* result, _Out_opt_ bool* resultAtomIsNew = nullptr) = 0;
};

class AtomPoolGroup : public DefObject
{
public:
    AtomPoolGroup();
    virtual ~AtomPoolGroup();

    /*!
         * Creates a new, empty AtomPoolGroup with room for the
         * specified number of atom pools.
         */
    static HRESULT CreateInstance(_In_ int numPools, _Outptr_ AtomPoolGroup** group);

    static HRESULT CreateInstance(_Outptr_ AtomPoolGroup** group) { return CreateInstance(0, group); }

    /*!
         * Extends the pools array to hold at least a specified pool index.
         */
    HRESULT ExtendPools(_In_ Atom::PoolIndex newMaxIndex);

    _Success_(return == true)
    bool TryGetAtomPool(_In_ Atom::PoolIndex index, _Out_opt_ IAtomPool** resultPool) const;

    IAtomPool* GetAtomPool(_In_ Atom::PoolIndex index) const;

    Atom::PoolIndex GetMaxPoolIndex() const { return m_maxPoolIndex; }

    /*!
         * Removes an atom pool from a DEFFILE_ATOMS.
         * Returns true if the pool is successfully removed, false if an error occurs.
         * Silently ignores attempts to remove NULL.  Reports an ATOM_POOL_MISMATCH if
         * pPool comes from another pool.
         */
    HRESULT RemoveAtomPool(_Inout_opt_ IAtomPool* pool);

    /*!
         * Adds an atom pool to a AtomPoolGroup at a specified
         * index.
         * NOTE:
         *    Note that the index specified here does _not_
         * have to match the index specified in the pool
         * header.
         */
    HRESULT AddAtomPool(_Inout_ IAtomPool* pool, _In_ Atom::Index index, _In_ bool assumeOwnership);

    /*!
         * Adds an atom pool to an AtomPoolGroup to the next
         * available index, growing the group if necessary.
         * Ignores the current index of the pool.
         *
         * Succeeds without changes if pool already belongs
         * to this group.  If pool belongs to another group
         * it will be removed from that group and added here
         * at the next available index.
         *
         * Returns HRESULT
         */
    HRESULT AddAtomPool(_Inout_ IAtomPool* pool, _In_ bool assumeOwnership);

    /*!
         * Determines if the strings associated with two
         * atoms are equal, regardless of whether they
         * come from the same pool or not.
         */
    bool AtomsEqual(_In_ Atom atom1, _In_ Atom atom2) const;

    // Returns the number of atompools that could be in this group
    Atom::PoolIndex GetNumPools() const { return m_maxPoolIndex + 1; }
    HRESULT GetString(_In_ Atom atom, _Inout_ StringResult* ResultString) const;
    bool TryGetString(_In_ Atom atom, _Inout_ StringResult* resultString) const;

protected:
private:
    UINT32 m_flags;
    Atom::PoolIndex m_sizePools;
    IAtomPool** m_pools;
    // Value of 'true' in m_pAssumeOwnership[index] implies that
    // AtomPoolGroup takes responsibility of deleting m_pools[index]
    bool* m_pAssumeOwnership;
    Atom::PoolIndex m_maxPoolIndex;
    Atom::PoolIndex m_nPools;
};

/*!
     * An atom pool initialized directly from an array of static strings.
     * Uses the supplied strings directly, so they must remain valid for
     * the life of the pool.
     */
class StaticAtomPool : public IAtomPool
{
protected:
    AtomPoolGroup* m_pAtoms;
    Atom::PoolIndex m_poolIndex;
    PCWSTR m_pDescription;
    _Field_size_(m_numStrings) const PCWSTR* m_ppStrings;
    int m_numStrings;
    DEFCOMPAREOPTIONS m_compareOptions;

    StaticAtomPool(
        _In_reads_opt_(numStrings) const PCWSTR* stringsArray,
        _In_ int numStrings,
        _In_opt_ PCWSTR description,
        _In_ DEFCOMPAREOPTIONS compareOptions) :
        m_pAtoms(nullptr),
        m_poolIndex(Atom::NullPoolIndex),
        m_pDescription(description),
        m_ppStrings(stringsArray),
        m_numStrings(numStrings),
        m_compareOptions(compareOptions)
    {}

public:
    // Default is case-insensitive
    typedef enum _StaticAtomPoolFlags
    {
        CaseInsensitive = 0x0000,
        CaseSensitive = 0x0001,

        Validation = 0x0000,
        NoValidation = 0x0002,

        BlockNullForAtom0 = 0x0000,
        AllowNullForAtom0 = 0x0004,

        DefaultFlags = CaseInsensitive | Validation | BlockNullForAtom0
    } StaticAtomPoolFlags;

    static HRESULT CreateInstance(
        _In_reads_(numStrings) const PCWSTR* stringsArray,
        _In_ int numStrings,
        _In_opt_ PCWSTR description,
        _In_ StaticAtomPoolFlags flags,
        _Outptr_ StaticAtomPool** pool);

    static HRESULT CreateInstance(
        _In_reads_(numStrings) const PCWSTR* stringsArray,
        _In_ int numStrings,
        _In_opt_ PCWSTR description,
        _In_ bool isCaseInsensitive,
        _Outptr_ StaticAtomPool** pool)
    {
        StaticAtomPoolFlags flags = (isCaseInsensitive ? DefaultFlags : CaseSensitive);
        // underlying new validates params
        return CreateInstance(stringsArray, numStrings, description, flags, pool);
    }

    //IAtomPool implementation
    bool Contains(_In_ PCWSTR str) const;

    bool Contains(_In_ Atom atom) const;

    bool Equals(_In_ Atom atom, _In_ PCWSTR str) const;

    AtomPoolGroup* GetAtomPoolGroup() const;
    PCWSTR GetDescription() const;
    bool GetIsCaseInsensitive() const;
    Atom::Index GetNumAtoms() const;
    Atom::PoolIndex GetPoolIndex() const;

    void SetAtomPoolGroup(_In_ AtomPoolGroup* pGroup);

    void SetPoolIndex(_In_ Atom::PoolIndex index);

    _Success_(return == true)
    bool TryGetAtom(_In_ PCWSTR str, _Out_opt_ Atom* resultAtom) const;

    bool TryGetIndex(_In_ PCWSTR str, _Out_opt_ Atom::Index* resultIndex) const;

    bool TryGetString(_In_ Atom atom, _Inout_opt_ StringResult* resultString) const;

    bool TryGetString(_In_ Atom::Index index, _Inout_opt_ StringResult* resultString) const;
};

} // namespace Microsoft::Resources
