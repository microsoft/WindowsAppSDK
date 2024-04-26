// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources::Build
{

/*!
     * The AtomIndexedDictionaryBase class provides common functionality for
     * atom-indexed dictionary templates.  Type-safe atom-indexed dictionaries
     * should be derived directly from the templates.
     *
     * Atom-indexed dictionaries resize appropriately if the atom pool
     * used for the index increases in size, which makes the safe for
     * use at build time with an AtomPoolBuilder.
     *
     * An atom-indexed dictionary contains an internal contiguous pool of
     * element data plus a mapping from atom index to the "internal" index
     * of the atom in the internal pool of elements.  The AtomIndexedDictionaryBase
     * class manages the size of the internal pool and the mapping from atom
     * index to internal index.  It calls abstract protected methods to resize the pool
     * as appropriate - derived classes must take care to preserve object semantics
     * when implementing the internal resize methods (e.g. use copy constructors or
     * copy memory directly as appropriate).
     *
     * Atom-indexed dictionaries support three allocation strategies:
     * 1) Full
     *    Allocate contiguous space for all of the items in the atom pool,
     *    regardless of which items actually have associated data in
     *    the dictionary.
     *
     *    For a full dictionary, atom index and internal index are the same.
     *    Full dictionaries only resize if the underlying atom pool increases
     *    in size.
     *
     * 2) Subset
     *    Allocate contiguous space for the minimum range that covers
     *    the items that actually have associated data in the
     *    dictionary.
     *
     *    For a subset dictionary, the internal index is the atom index minus
     *    that of the lowest-indexed atom for which data is present in the dictionary.
     *    A subset dictionary resizes whenever the range of covered atoms increases.
     *
     * 3) Sparse
     *    Allocate space as needed for items that have associated
     *    data in the dictionary.
     *
     *    For a sparse dictionary, the mapping from atom index to internal index is
     *    undefined.  A sparse dictionary creates inserts data into the pool in the
     *    order it is added to the dictionary and grows the pool when it fills.
     */
class AtomIndexedDictionaryBase : public DefObject
{
public:
    /*!
         * Specifies the allocation strategy to be used for a particular atom-indexed
         * dictionary.
         */
    typedef enum _Strategy
    {
        Auto = 0,
        Full = 1,
        Subset = 2,
        Sparse = 3
    } Strategy;

    class Iterator;

protected:
    class AIDictRange;
    static const int InitialSparseSize = 10;

    const IAtomPool* m_pNames;
    Strategy m_strategy;

    int m_minAtomIndex;
    int m_maxAtomIndex;
    int m_numItems;
    int m_sizeItems;
    AIDictRange* m_pRanges;

    /*!
         * Protected constructor for \ref AtomiIndexedDictionaryBase
         *
         * \param pNames
         * Specifies the \ref AtomPool used to index the dictionary.
         *
         * \param strategy
         * Specifies the allocation strategy to be used by the dictionary.
         */
    AtomIndexedDictionaryBase(_In_ const IAtomPool* pNames, _In_ Strategy strategy);

    /*!
         * Gets the internal index that corresponds to an item
         * specified by name as a string.  Does not create a
         * mapping for the item if it is not already present
         * in the dictionary.
         *
         * \param pName
         * The name of the item for which an internal index
         * is to be returned.
         *
         * \param pInternalIndexOut
         * Returns the corresonding internal index.  Returns -1 if
         * there is no matching index or if an error occurs.
         *
         * \return bool
         * Returns true if an internal index was found, false if
         * the item has no internal index or if an error occurs.
         */
    _Success_(return == true)
    bool TryGetInternalIndex(_In_ PCWSTR pName, _Out_opt_ int* pInternalIndexOut) const;

    /*!
         * Gets the internal index that corresponds to an item
         * specified by name as an atom.  Does not create a
         * mapping for the item if it is not already present
         * in the dictionary.
         *
         * \param name
         * The name of the item for which an internal index
         * is to be returned.
         *
         * \param pInternalIndexOut
         * Returns the corresonding internal index.  Returns -1 if
         * there is no matching index or if an error occurs.
         *
         * \return bool
         * Returns true if an internal index was found, false if
         * the item has no internal index or if an error occurs.
         */
    _Success_(return == true)
    bool TryGetInternalIndex(_In_ Atom name, _Out_opt_ int* pInternalIndexOut) const;

    /*!
         * Gets the internal index that corresponds to an item
         * specified by name as an index into the atom pool.
         * Does not create a mapping for the item if it is not
         * already present in the dictionary.
         *
         * \param nameIndex
         * The index in the atom pool for which an internal index
         * is to be returned.
         *
         * \param pInternalIndexOut
         * Returns the corresonding internal index.  Returns -1 if
         * there is no matching index or if an error occurs.
         *
         * \return bool
         * Returns true if an internal index was found, false if
         * the item has no internal index or if an error occurs.
         */
    _Success_(return == true)
    bool TryGetInternalIndex(_In_ Atom::Index nameIndex, _Out_opt_ int* pInternalIndexOut) const;

    /*!
         * Gets the internal index that corresponds to an item
         * specified by name as a string.  Allocates a new
         * index if the item is valid for the atom pool but
         * not present in the dictionary.
         *
         * \param pName
         * The name of the item for which an internal index
         * is to be returned.
         *
         * \param pInternalIndexOut
         * Returns the corresonding internal index.  Returns -1 if
         * an error occurs.
         *
         * \return HRESULT
         * Returns S_OK if an internal index was found or added,
         * or failure if an error occurs.
         */
    HRESULT GetOrAddInternalIndex(_In_ PCWSTR pName, _Out_opt_ int* pInternalIndexOut);

    /*!
         * Gets the internal index that corresponds to an item
         * specified by name as an atom.  Allocates a new
         * index if the item is valid for the atom pool but
         * not present in the dictionary.
         *
         * \param name
         * The name of the item for which an internal index
         * is to be returned.
         *
         * \param pInternalIndexOut
         * Returns the corresonding internal index.  Returns -1 if
         * an error occurs.
         *
         * \return HRESULT
         * Returns S_OK if an internal index was found or added,
         * or failure if an error occurs.
         */
    HRESULT GetOrAddInternalIndex(_In_ Atom name, _Out_opt_ int* pInternalIndexOut);

    /*!
         * Gets the internal index that corresponds to an item
         * specified as an index into the atom pool for the
         * dictionary.  Allocates a new index if the item is
         * valid for the atom pool but not present in the dictionary.
         *
         * \param nameIndex
         * The name of the item for which an internal index
         * is to be returned.
         *
         * \param pInternalIndexOut
         * Returns the corresonding internal index.  Returns -1 if
         * an error occurs.
         *
         * \return HRESULT
         * Returns S_OK if an internal index was found or added,
         * or failure if an error occurs.
         */
    HRESULT GetOrAddInternalIndex(_In_ Atom::Index nameIndex, _Out_opt_ int* pInternalIndexOut);

    /*!
         * Resizes the internal pool of item data.
         *
         * Abstract method that must be implemented by classes derived
         * from ref AtomIndexedDictionaryBase.  Derived classes must
         * take care to respect object semantics (e.g. use memory copy
         * or copy constructors as appropriate).
         *
         * \param oldSize
         * Specifies the original size of the item data pool, in elements.
         *
         * \param newSize
         * Specifies the new size of the item data pool, in elements.
         *
         * \param offset
         * Specifies the index of the old data in the newly allocated pool.
         *
         * \return HRESULT
         * Returns S_OK if the pool is successfully extended, failure if an error occurs.
         */
    virtual HRESULT Extend(_In_ int oldSize, _In_ int newSize, _In_ int offset) = 0;

    /*!
         * Indicates whether the dictionary contains data for an individual
         * item, specified by internal index.
         *
         * Abstract method must be implemented by classes that derive
         * from \ref AtomIndexedDictionaryBase.
         *
         * \param internalIndex
         * The internal index of the item to be tested.
         *
         * \return HRESULT
         * Returns S_OK if the item has data, failure if the item has no data or
         * if an error occurs.
         */
    virtual bool InternalItemHasData(_In_ int internalIndex) const = 0;

    int GetMaxInternalIndex() const;

    /*!
         * \defgroup Iterators
         *
         * @{
         * Internal helper function for iterators.  Given the current
         * state of an iterator, returns the index of the next highest
         * atom that has data associated with it.  Optionally returns
         * the internal index as well.
         *
         * \param pState
         * The current state of the iterator.
         *
         * \param pAtomIndexOut
         * Returns the index of the next atom that has associated data.
         *
         * \param pInternalIndexOut
         * If non-NULL, returns the internal index of the next atom that
         * has associated data.
         *
         * \return HRESULT
         * Returns S_OK on success.  Returns failure if there are no more
         * items with data or if an error occurs.
         * @}
         */
    HRESULT GetNextInternedAtomWithData(
        _Inout_ AtomIndexedDictionaryBase::Iterator* pState,
        _Out_ Atom::Index* pAtomIndexOut,
        _Out_opt_ int* pInternalIndexOut) const;

public:
    /*!
         * Destructor for \ref AtomIndexedDictionaryBase object.
         *
         */
    virtual ~AtomIndexedDictionaryBase();

    /*!
         * Gets the atom pool used to index this atom-indexed dictionary.
         *
         * \return IAtomPool*
         * Returns a pointer to the atom pool used to indexd this atom-indexed
         * dictionary.
         */
    const IAtomPool* GetNames() { return m_pNames; }

    /*!
         * Reports whether the dictionary contains data for an item specified by
         * name.
         *
         * \param pItemName
         * The name of the item to be checked.
         *
         * \return bool
         * Returns true if the dictionary contains data for the item.  Returns
         * false if the dictionary does not contain data for the item or if an
         * error occurs.
         */
    bool ItemHasData(_In_ PCWSTR pItemName) const;

    /*!
         * Reports whether the dictionary contains data for an item specified as
         * an atom.
         *
         * \param itemName
         * The name of the item to be checked.
         *
         * \return bool
         * Returns true if the dictionary contains data for the item.  Returns
         * false if the dictionary does not contain data for the item or if an
         * error occurs.
         */
    bool ItemHasData(_In_ Atom itemName) const;

    /*!
         * Reports whether the dictionary contains data for an item specified as
         * an index into the atom pool for this dictionary.
         *
         * \param itemNameIndex
         * The index in the atom pool for this dictionary of the item to be checked.
         *
         * \return bool
         * Returns true if the dictionary contains data for the item.  Returns
         * false if the dictionary does not contain data for the item or if an
         * error occurs.
         */
    bool ItemHasData(_In_ Atom::Index itemNameIndex) const;

    /*!
         * \addtogroup Iterators
         * @{
         */

    /*!
         * Creates a new iterator for this dictionary.  Must
         * be freed with \ref DeleteIterator.
         *
         * \param result
         * Returns a pointer to the newly created iterator,
         * or nullptr if an error occurs.
         *
         * \return HRESULT
         */
    HRESULT NewIterator(_Outptr_ AtomIndexedDictionaryBase::Iterator** result) const;

    /*!
         * Resets the specified iterator to start again from the
         * beginning of the dictionary.
         *
         * \param pState
         * The \ref AtomIndexedDictionaryBase::Iterator to be reset.
         *
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    HRESULT ResetIterator(_Inout_ AtomIndexedDictionaryBase::Iterator* pState) const;

    /*!
         * Given the current state of an iterator, gets the atom index
         * of the next item in the dictionary that has data associated
         * with it.  Returns the first item if the iterator is newly
         * created or reset.
         *
         * \param pState
         * The state of the \ref AtomIndexedDictionaryBase::Iterator to be
         * used.
         *
         * \param pAtomIndexOut
         * Returns the index of the next atom that has data associated with it,
         * or \ref Atom::IndexNone if no more atoms have data.
         *
         * \return HRESULT
         * Returns S_OK if an atom with data was found.  Returns failure if there
         * are no more atoms with data or if an error occurs.
         */
    HRESULT GetNextItem(_Inout_ AtomIndexedDictionaryBase::Iterator* pState, _Inout_ Atom::Index* pAtomIndexOut) const
    {
        return GetNextInternedAtomWithData(pState, pAtomIndexOut, nullptr);
    }

    /*!
         * Deletes an iterator state associated with this dictionary.  Must
         * have been created by \ref NewIterator.
         *
         * \param pState
         * The iterator state to be deleted.
         *
         * \return HRESULT
         * Returns S_OK if the state is deleted, failure if an error occurs.
         */
    HRESULT DeleteIterator(_Inout_opt_ AtomIndexedDictionaryBase::Iterator* pState) const;

    /*!
         * Gets the lowest atom index that has been assigned an internal
         * index in the dictionary.
         *
         * \return Atom::Index
         * Returns the lowest index in the table, or Atom::IndexNone if no
         * internal indices have been allocated.
         *
         */
    Atom::Index GetMinAtomIndex() { return m_minAtomIndex; }

    /*!
         * Gets the largest atom index that has been assigned an internal
         * index in the dictionary.
         *
         * \return Atom::Index
         * Returns the largest index in the table, or Atom::IndexNone if no
         * internal indices have been allocated.
         *
         */
    Atom::Index GetMaxAtomIndex() const { return m_maxAtomIndex; }
};

/*!
     * @}
     */

/*!
     * Template for an atom-indexed dictionary that stores a scalar value
     * for some or all of the names in an associated atom pool.
     *
     * A SENTINEL value supplied to the template indicates that no data
     * is present for an item.
     */
template<typename TELEM, TELEM SENTINEL>
class AtomIndexedScalarDictionary : public AtomIndexedDictionaryBase
{
protected:
    __field_ecount(m_sizeItems) TELEM* m_pElems;

    AtomIndexedScalarDictionary(_In_ const IAtomPool* pNames, _In_ Strategy strategy) :
        AtomIndexedDictionaryBase(pNames, strategy), m_pElems(nullptr)
    {}

    virtual HRESULT Extend(_In_ int oldSize, _In_ int newSize, _In_ int offset)
    {
        if (_DefArray_TryExpandAndRelocate(m_pElems, sizeof(TELEM), oldSize, newSize, offset, reinterpret_cast<void**>(&m_pElems)))
        {
            int i;
            for (i = 0; i < offset; i++)
            {
                m_pElems[i] = SENTINEL;
            }
            for (i = offset + oldSize; i < newSize; i++)
            {
                m_pElems[i] = SENTINEL;
            }
            return S_OK;
        }
        return E_OUTOFMEMORY;
    }

    virtual bool InternalItemHasData(_In_ int internalIndex) const { return (m_pElems[internalIndex] != SENTINEL); }

public:
    /*!
         * Static factory method for objects of this class.  Guarantees that it will:
         * - use a nothrow constructor
         * - not return NULL without also returning a descriptive error status
         * - return a status of Success if it returns a dictionary
         *
         * \param pNames
         * Specifies the atom pool used to index the dictionary.
         *
         * \param strategy
         * Specifies the allocation strategy to be used for the dictionary.
         *
         * \param result
         * Return the new dictionary, or NULL if an error occurs.
         *
         * \return HRESULT
         */
    static HRESULT CreateInstance(_In_ const IAtomPool* pNames, _In_ Strategy strategy, _Outptr_ AtomIndexedScalarDictionary** result)
    {
        *result = nullptr;
        RETURN_HR_IF_NULL(E_INVALIDARG, pNames);

        AtomIndexedScalarDictionary* pRtrn = new AtomIndexedScalarDictionary(pNames, strategy);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;

        return S_OK;
    }

    virtual ~AtomIndexedScalarDictionary() { _DefFree(m_pElems); }

    /*!
         * Gets the data associated with an element specified as an atom.
         *
         * \param name
         * Specifies the element for which data is to be retrieved.
         *
         * \param pElemOut
         * Returns the data associated with the element, or SENTINEL if
         * the element has no associated data.
         *
         * \return bool
         * Returns true if data was found for the element.  Returns false
         * if no data was found or if an error occurs.
         */
    bool TryGetItemData(_In_ Atom name, _Out_opt_ TELEM* pElemOut) const
    {
        int internalIndex = -1;
        if (TryGetInternalIndex(name, &internalIndex) && (m_pElems[internalIndex] != SENTINEL))
        {
            if (pElemOut != nullptr)
            {
                *pElemOut = m_pElems[internalIndex];
            }
            return true;
        }

        if (pElemOut)
        {
            *pElemOut = SENTINEL;
        }
        return false;
    }

    /*!
         * Gets the data associated with an element specified as an string.
         *
         * \param pName
         * Specifies the element for which data is to be retrieved.
         *
         * \param pElemOut
         * Returns the data associated with the element, or SENTINEL if
         * the element has no associated data.
         *
         * \return bool
         * Returns true if data was found for the element.  Returns false
         * if no data was found or if an error occurs.
         */
    bool TryGetItemData(_In_ PCWSTR pName, _Out_opt_ TELEM* pElemOut) const
    {
        int internalIndex = -1;
        if (TryGetInternalIndex(pName, &internalIndex) && (m_pElems[internalIndex] != SENTINEL))
        {
            if (pElemOut != nullptr)
            {
                *pElemOut = m_pElems[internalIndex];
            }
            return true;
        }
        if (pElemOut != nullptr)
        {
            *pElemOut = SENTINEL;
        }
        return false;
    }

    /*!
         * Gets the data associated with an element specified an index
         * into the atom pool for this dictionary.
         *
         * \param nameIndex
         * Specifies the element for which data is to be retrieved.
         *
         * \param pElemOut
         * Returns the data associated with the element, or SENTINEL if
         * the element has no associated data.
         *
         * \return bool
         * Returns true if data was found for the element.  Returns false
         * if no data was found or if an error occurs.
         */
    bool TryGetItemData(_In_ Atom::Index nameIndex, _Out_opt_ TELEM* pElemOut) const
    {
        int internalIndex = -1;
        if (TryGetInternalIndex(nameIndex, &internalIndex) && (m_pElems[internalIndex] != SENTINEL))
        {
            if (pElemOut != nullptr)
            {
                *pElemOut = m_pElems[internalIndex];
            }
            return true;
        }

        if (pElemOut != nullptr)
        {
            *pElemOut = SENTINEL;
        }
        return false;
    }

    /*!
         * Sets data in the dictionary for an element specified
         * as a string.
         *
         * \param pName
         * Specifies the element for which the data is to be set.
         *
         * \param data
         * The data to be stored for the element.
         *
         * \param clobber
         * If true, the new value will be written regardless of whether
         * the element already has associated data.  If clobber is false,
         * setting data for an element that already has something defined
         * yields an error.
         *
         * \return HRESULT
         * Returns S_OK if the value was set, failure if an error occurs.
         */
    HRESULT SetItemData(_In_ PCWSTR pName, _In_ TELEM data, _In_ bool clobber)
    {
        int internalIndex = -1;
        RETURN_IF_FAILED(GetOrAddInternalIndex(pName, &internalIndex));

        if ((!clobber) && (m_pElems[internalIndex] != SENTINEL))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }
        m_pElems[internalIndex] = data;
        return S_OK;
    }

    /*!
         * Sets data in the dictionary for an element specified
         * as an atom.
         *
         * \param name
         * Specifies the element for which the data is to be set.
         *
         * \param data
         * The data to be stored for the element.
         *
         * \param clobber
         * If true, the new value will be written regardless of whether
         * the element already has associated data.  If clobber is false,
         * setting data for an element that already has something defined
         * yields an error.
         *
         * \return HRESULT
         * Returns S_OK if the value was set, failure if an error occurs.
         */
    HRESULT SetItemData(_In_ Atom name, _In_ TELEM data, _In_ bool clobber)
    {
        int internalIndex = -1;
        RETURN_IF_FAILED(GetOrAddInternalIndex(name, &internalIndex));

        if ((!clobber) && (m_pElems[internalIndex] != SENTINEL))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }
        m_pElems[internalIndex] = data;
        return S_OK;
    }

    /*!
         * Sets data in the dictionary for an element specified
         * as an index into the atom pool for this dictionary.
         *
         * \param nameIndex
         * Specifies the element for which the data is to be set.
         *
         * \param data
         * The data to be stored for the element.
         *
         * \param clobber
         * If true, the new value will be written regardless of whether
         * the element already has associated data.  If clobber is false,
         * setting data for an element that already has something defined
         * yields an error.
         *
         * \return HRESULT
         * Returns S_OK if the value was set, failure if an error occurs.
         */
    HRESULT SetItemData(_In_ Atom::Index nameIndex, _In_ TELEM data, _In_ bool clobber)
    {
        int internalIndex = -1;
        RETURN_IF_FAILED(GetOrAddInternalIndex(nameIndex, &internalIndex));

        if ((!clobber) && (m_pElems[internalIndex] != SENTINEL))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }
        m_pElems[internalIndex] = data;
        return S_OK;
    }

    /*!
         * Given the current state of an iterator, gets the atom index
         * of the next item in the dictionary that has data associated
         * with it.  Optionally returns the data associated with the
         * atom.  Returns the first item if the iterator is newly
         * created or reset.
         *
         * \param pState
         * The state of the \ref AtomIndexedDictionaryBase::Iterator to be
         * used.
         *
         * \param pAtomIndexOut
         * Returns the index of the next atom that has data associated with it,
         * or \ref Atom::IndexNone if no more atoms have data.
         *
         * \param pValueOut
         * If non-NULL, returns the data associated with the returned
         * atom.  If no more atoms are found, returns the value of the
         * template SENTINEL parameter.
         *
         * \return HRESULT
         * Returns S_OK if an atom with data was found.  Returns failure if there
         * are no more atoms with data or if an error occurs.
         */
    HRESULT GetNextItem(_Inout_ AtomIndexedDictionaryBase::Iterator* pState, _Out_ Atom::Index* pAtomIndexOut, _Out_ TELEM* pValueOut) const
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, pValueOut);

        int internalIndex = -1;
        RETURN_IF_FAILED(GetNextInternedAtomWithData(pState, pAtomIndexOut, &internalIndex));
        *pValueOut = m_pElems[internalIndex];

        return S_OK;
    }
};

/*!
     * Template for an atom-indexed dictionary that holds values of
     * a structure type.  Structure elements cannot be compared to
     * some sentinel value, but they can be copied using raw memory
     * options and cannot rely on constructors or destructors for
     * initialization or cleanup.
     */
template<typename TELEM>
class AtomIndexedStructDictionary : public AtomIndexedDictionaryBase
{
protected:
    TELEM* m_pElems;
    bool* m_pPresent;

    AtomIndexedStructDictionary(_In_ const IAtomPool* pNames, _In_ Strategy strategy) :
        AtomIndexedDictionaryBase(pNames, strategy), m_pPresent(nullptr), m_pElems(nullptr)
    {}

    virtual HRESULT Extend(_In_ int oldSize, _In_ int newSize, _In_ int offset)
    {
        if ((_DefArray_TryExpandAndRelocate(m_pElems, sizeof(TELEM), oldSize, newSize, offset, reinterpret_cast<void**>(&m_pElems))) &&
            (_DefArray_TryExpandAndRelocate(m_pPresent, sizeof(bool), oldSize, newSize, offset, reinterpret_cast<void**>(&m_pPresent))))
        {
            return S_OK;
        }
        return E_OUTOFMEMORY;
    }

    virtual bool InternalItemHasData(_In_ int internalIndex) const { return m_pPresent[internalIndex]; }

public:
    /*!
         * Static factory method for objects of this class.  Guarantees that it will:
         * - use a nothrow constructor
         * - not return NULL without also returning a descriptive error status
         * - return a status of Success if it returns a dictionary
         *
         * \param pNames
         * Specifies the atom pool used to index the dictionary.
         *
         * \param strategy
         * Specifies the allocation strategy to be used for the dictionary.
         *
         * \param result
         * Return the new dictionary, or NULL if an error occurs.
         *
         * \return HRESULT
         */
    static HRESULT CreateInstance(
        _In_ const IAtomPool* pNames,
        _In_ Strategy strategy,
        _Outptr_ AtomIndexedStructDictionary<TELEM>** result)
    {
        *result = nullptr;
        RETURN_HR_IF_NULL(E_INVALIDARG, pNames);

        AtomIndexedStructDictionary<TELEM>* pRtrn = new AtomIndexedStructDictionary(pNames, strategy);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    /*!
         * Dictionary destructor.
         */
    virtual ~AtomIndexedStructDictionary()
    {
        _DefFree(m_pElems);
        _DefFree(m_pPresent);
    }

    /*!
         * Gets the data associated with an element specified as a
         * string.
         *
         * \param pName
         * Specifies the element for which data is to be retrieved.
         *
         * \param pElemOut
         * Returns the data associated with the element.  Contents are
         * not modified if an error occurs or if no data has been stored
         * for the element.
         *
         * \return bool
         * Returns true if data was found for the element.  Returns false
         * if no data was found or if an error occurs.
         */
    _Success_(return == true)
    bool TryGetItemData(_In_ PCWSTR pName, _Out_opt_ TELEM* pElemOut) const
    {
        int internalIndex = -1;
        if (TryGetInternalIndex(pName, &internalIndex) && m_pPresent[internalIndex])
        {
            if (pElemOut != nullptr)
            {
                *pElemOut = m_pElems[internalIndex];
            }
            return true;
        }
        return false;
    }

    /*!
         * Gets the data associated with an element specified as an atom.
         *
         * \param name
         * Specifies the element for which data is to be retrieved.
         *
         * \param pElemOut
         * Returns the data associated with the element.  Contents are
         * not modified if an error occurs or if no data has been stored
         * for the element.
         *
         * \return bool
         * Returns true if data was found for the element.  Returns false
         * if no data was found or if an error occurs.
         */
    _Success_(return == true)
    bool TryGetItemData(_In_ Atom name, _Out_opt_ TELEM* pElemOut) const
    {
        int internalIndex = -1;
        if (TryGetInternalIndex(name, &internalIndex) && m_pPresent[internalIndex])
        {
            if (pElemOut != nullptr)
            {
                *pElemOut = m_pElems[internalIndex];
            }
            return true;
        }
        return false;
    }

    /*!
         * Gets the data associated with an element specified as an
         * index into the atom pool for this dictionary.
         *
         * \param nameIndex
         * Specifies the element for which data is to be retrieved.
         *
         * \param pElemOut
         * Returns the data associated with the element.  Contents are
         * not modified if an error occurs or if no data has been stored
         * for the element.
         *
         * \return bool
         * Returns true if data was found for the element.  Returns false
         * if no data was found or if an error occurs.
         */
    _Success_(return == true)
    bool TryGetItemData(_In_ Atom::Index nameIndex, _Out_opt_ TELEM* pElemOut) const
    {
        int internalIndex = -1;
        if (TryGetInternalIndex(nameIndex, &internalIndex) && m_pPresent[internalIndex])
        {
            if (pElemOut != nullptr)
            {
                *pElemOut = m_pElems[internalIndex];
            }
            return true;
        }
        return false;
    }

    /*!
         * Sets data in the dictionary for an element specified
         * as a string.
         *
         * \param pName
         * Specifies the element for which the data is to be set.
         *
         * \param data
         * The data to be stored for the element.
         *
         * \param clobber
         * If true, the new value will be written regardless of whether
         * the element already has associated data.  If clobber is false,
         * setting data for an element that already has something defined
         * yields an error.
         *
         * \return HRESULT
         * Returns S_OK if the value was set, failure if an error occurs.
         */
    HRESULT SetItemData(_In_ PCWSTR pName, _In_ TELEM data, _In_ bool clobber)
    {
        int internalIndex = -1;
        RETURN_IF_FAILED(GetOrAddInternalIndex(pName, &internalIndex));

        if ((!clobber) && m_pPresent[internalIndex])
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }
        m_pElems[internalIndex] = data;
        m_pPresent[internalIndex] = true;
        return S_OK;
    }

    /*!
         * Sets data in the dictionary for an element specified
         * by atom.
         *
         * \param name
         * Specifies the element for which the data is to be set.
         *
         * \param data
         * The data to be stored for the element.
         *
         * \param clobber
         * If true, the new value will be written regardless of whether
         * the element already has associated data.  If clobber is false,
         * setting data for an element that already has something defined
         * yields an error.
         *
         * \return HRESULT
         * Returns S_OK if the value was set, failure if an error occurs.
         */
    HRESULT SetItemData(_In_ Atom name, _In_ TELEM data, _In_ bool clobber)
    {
        int internalIndex = -1;
        RETURN_IF_FAILED(GetOrAddInternalIndex(name, &internalIndex));

        if ((!clobber) && m_pPresent[internalIndex])
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }
        m_pElems[internalIndex] = data;
        m_pPresent[internalIndex] = true;
        return S_OK;
    }

    /*!
         * Sets data in the dictionary for an element specified
         * as an index into the atom pool for this dictionary.
         *
         * \param nameIndex
         * Specifies the element for which the data is to be set.
         *
         * \param data
         * The data to be stored for the element.
         *
         * \param clobber
         * If true, the new value will be written regardless of whether
         * the element already has associated data.  If clobber is false,
         * setting data for an element that already has something defined
         * yields an error.
         *
         * \return HRESULT
         * Returns S_OK if the value was set, failure if an error occurs.
         */
    HRESULT SetItemData(_In_ Atom::Index nameIndex, _In_ TELEM data, _In_ bool clobber)
    {
        int internalIndex = -1;
        RETURN_IF_FAILED(GetOrAddInternalIndex(nameIndex, &internalIndex));

        if ((!clobber) && m_pPresent[internalIndex])
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }
        m_pElems[internalIndex] = data;
        m_pPresent[internalIndex] = true;
        return S_OK;
    }

    /*!
         * Given the current state of an iterator, gets the atom index
         * of the next item in the dictionary that has data associated
         * with it.  Optionally returns the data associated with the
         * atom.  Returns the first item if the iterator is newly
         * created or reset.
         *
         * \param pState
         * The state of the \ref AtomIndexedDictionaryBase::Iterator to be
         * used.
         *
         * \param pAtomIndexOut
         * Returns the index of the next atom that has data associated with it,
         * or \ref Atom::IndexNone if no more atoms have data.
         *
         * \param pValueOut
         * If non-NULL, returns the data associated with the returned
         * atom.  If no more atoms are found, this return parameter is
         * not modified.
         *
         * \return HRESULT
         * Returns S_OK if an atom with data was found.  Returns failure if there
         * are no more atoms with data or if an error occurs.
         */
    HRESULT GetNextItem(_Inout_ AtomIndexedDictionaryBase::Iterator* pState, _Out_ Atom::Index* pAtomIndexOut, _Out_ TELEM* pValueOut) const
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, pValueOut);

        int internalIndex = -1;
        RETURN_IF_FAILED(GetNextInternedAtomWithData(pState, pAtomIndexOut, &internalIndex));
        *pValueOut = m_pElems[internalIndex];
        return S_OK;
    }
};

} // namespace Microsoft::Resources::Build
