// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Microsoft::Resources::Build
{

/*!
     * \addtogroup DefBuild
     * @{
     * \addtogroup DefBuild_Common
     * @{
     * \defgroup TWriteableStringPool Generic string pool for build phase
     * @{
     */

template<typename TSC, typename TCH>
class PoolStringOps
{
private:
    PoolStringOps() {}
};

template<>
class PoolStringOps<PCWSTR, WCHAR>
{
public:
    static bool StringsMatch(_In_ PCWSTR pString1, _In_ PCWSTR pString2, _In_ DEFCOMPAREOPTIONS options)
    {
        return (DefString_CompareWithOptions(pString1, pString2, options) == 0);
    }

    static size_t StringLength(_In_ PCWSTR pString) { return wcslen(pString); }

    static HRESULT StringCchCopy(_Out_writes_(cchCopy) WCHAR* pDestination, _In_ size_t cchCopy, _In_reads_(cchCopy) PCWSTR pSource)
    {
        return DefString_CchCopy(pDestination, cchCopy, pSource);
    }

    static HRESULT SetResult(_In_ PCWSTR pString, _Inout_ StringResult* pStringOut) { return pStringOut->SetRef(pString); }
};

/*!
     * A simple string pool for sharing like strings at build time. 
     * TSW = Writable string type (e.g. PWSTR)
     * TSC = Constant string type (e.g. PCWSTR)
     * TCH = Character type (e.g. WCHAR)
     */
template<typename TSW, typename TSC, typename TCH>
class TWriteableStringPool : public DefObject
{
private:
    UINT32 m_flags;
    DEFCOMPAREOPTIONS m_comparison;

    UINT32 m_numChars;
    UINT m_sizeChars;
    TCH* m_pChars;

protected:
    typedef PoolStringOps<TSC, TCH> StringOps;

protected:
    TWriteableStringPool() {}

    /*! 
         * Protected constructor for \ref TWriteableStringPool that initializes
         * the string pool to use a supplied, static buffer.
         * 
         * \param comparison
         * Specifies the rules used to compare and unify strings.
         *
         * \param pBuffer
         * The buffer into which the string pool will be generated. 
         *
         * \param cchPool
         * The size of the string pool supplied by \ref pBuffer, in characters.
         */
    HRESULT Init(_In_reads_(cchPool) TCH* pBuffer, _In_ UINT32 cchPool, _In_ UINT32 comparison)
    {
        RETURN_HR_IF(E_INVALIDARG, (pBuffer == nullptr) || (cchPool < 1));

        m_flags = fExternalBuffer;
        m_comparison =
            (((comparison & fCompareCaseInsensitive) != 0) ? DEFCOMPAREOPTIONS::DefCompare_CaseInsensitive :
                                                             DEFCOMPAREOPTIONS::DefCompare_Default);
        m_pChars = pBuffer;
        m_pChars[0] = static_cast<TCH>(0);
        m_numChars = 1;
        m_sizeChars = cchPool;

        return S_OK;
    }

    /*! 
         * Protected constructor for \ref TWriteableStringPool that allocates
         * a resizable buffer with a supplied initial size.
         * 
         * \param comparison
         * Specifies the rules used to compare and unify strings.
         *
         * \param cchInitial
         * Specifies the initial size of the buffer, in characters.
         */
    HRESULT Init(_In_ UINT32 comparison, _In_ UINT32 cchInitial)
    {
        RETURN_HR_IF(E_INVALIDARG, cchInitial < 1);

        m_flags = 0;
        m_comparison =
            (((comparison & fCompareCaseInsensitive) != 0) ? DEFCOMPAREOPTIONS::DefCompare_CaseInsensitive :
                                                             DEFCOMPAREOPTIONS::DefCompare_Default);
        m_numChars = 0;
        m_sizeChars = cchInitial;
        m_pChars = _DefArray_AllocZeroed(WCHAR, cchInitial);
        RETURN_IF_NULL_ALLOC(m_pChars);

        // Offset 0 is always NULL.
        m_pChars[0] = 0;
        m_numChars = 1;

        return S_OK;
    }

    /*! 
         * Extends the string pool at least enough to accomodate a string
         * of a specified length.
         * 
         * \param cchNeeded
         * Specifies the amount of space needed, in characters.
         * 
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    HRESULT ExtendToFit(_In_ UINT32 cchNeeded)
    {
        if (cchNeeded <= m_sizeChars)
        {
            return S_OK;
        }

        if ((m_flags & fExternalBuffer) != 0)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE);
        }

        // normally we're size doubling, but if we get a large request just allocate
        // it all in one go.
        ULONG newSize = (cchNeeded > m_sizeChars * 2) ? cchNeeded : m_sizeChars * 2;
        if (!_DefArray_TryEnsureSize(&m_pChars, TCH, m_sizeChars, newSize))
        {
            return E_OUTOFMEMORY;
        }

        m_sizeChars = newSize;
        return S_OK;
    }

    static const UINT32 DefaultInitialSize = 256; //!< Default initial size for a resizable buffer.
    static const UINT32 fExternalBuffer = 0x0100; //!< Flag indicating an external buffer that cannot be extended or freed.

public:
    static const UINT32 fCompareDefault = 0x0000; //!< Flag specifying default (ordinal) comparison
    static const UINT32 fCompareCaseInsensitive = 0x0001; //!< Flag specifying case-insensitive comparison

    static HRESULT CreateInstance(
        _In_reads_(cchPool) TCH* pBuffer,
        _In_ UINT32 cchPool,
        _In_ UINT32 comparison,
        _Outptr_ TWriteableStringPool** result)
    {
        *result = nullptr;

        AutoDeletePtr<TWriteableStringPool> pool = new TWriteableStringPool();
        RETURN_IF_NULL_ALLOC(pool);

        RETURN_IF_FAILED(pool->Init(pBuffer, cchPool, comparison));
        *result = pool.Detach();

        return S_OK;
    }

    /*! 
         * Protected constructor for \ref TWriteableStringPool that allocates
         * a resizable buffer with a supplied initial size.
         * 
         * \param comparison
         * Specifies the rules used to compare and unify strings.
         *
         * \param cchInitial
         * Specifies the initial size of the buffer, in characters.
         * 
         * \param result
         * Returns a new instance
         */
    static HRESULT CreateInstance(_In_ UINT32 comparison, _In_ UINT32 cchInitial, _Outptr_ TWriteableStringPool** result)
    {
        *result = nullptr;

        AutoDeletePtr<TWriteableStringPool> pool = new TWriteableStringPool();
        RETURN_IF_NULL_ALLOC(pool);

        RETURN_IF_FAILED(pool->Init(comparison, cchInitial));
        *result = pool.Detach();

        return S_OK;
    }

    /*!
         * \name Constructors & Destructors
         * @{
         */
    virtual ~TWriteableStringPool()
    {
        m_sizeChars = m_numChars = 0;
        if (m_pChars && ((m_flags & fExternalBuffer) == 0))
        {
            _DefFree(m_pChars);
        }
        m_pChars = NULL;
    }

    /*!@}*/

    /*! 
         * Gets the number of characters currently in use in the string pool.
         * \return UINT32
         * The number of characters in use in the string pool.
         */
    UINT32 GetNumCharsInPool() const { return m_numChars; }

    /*! 
         * Gets the offset of a specified string in the string pool.  If the string
         * is not already present, adds the string and returns the offset of the 
         * new string.
         * 
         * \param pString
         * The string to be added.
         * 
         * \return UINT32
         * Returns the offset of the string that matches \ref pString
         * in the string pool, or -1 if an error occurs.
         */
    int GetOrAddStringOffset(_In_opt_ TSC pString)
    {
        int offset;
        size_t cchString;

        if ((!pString) || (!pString[0]))
        {
            return 0;
        }

        if (TryGetStringOffset(pString, &offset))
        {
            return offset;
        }

        cchString = StringOps::StringLength(pString) + 1;
        if (FAILED(ExtendToFit(static_cast<UINT32>(m_numChars + cchString))))
        {
            return -1;
        }

        // note: Can't Cat here because the pool holds many strings
        offset = m_numChars;
        if (FAILED(StringOps::StringCchCopy(m_pChars + offset, m_sizeChars - offset, pString)))
        {
            return -1;
        }

        m_numChars += static_cast<UINT32>(cchString);
        return offset;
    }

    /*! 
         * Reports whether the string pool uses case-insensitive comparison.
         * 
         * \return bool
         * Returns true if the string pool uses case-insensitive comparison, 
         * false otherwise.
         */
    bool GetIsCaseInsensitive() const { return ((m_comparison & fCompareCaseInsensitive) != 0); }

    /*! 
         * Gets the offset of a specified string in the string pool, reporting an error
         * if no matching string is found.
         * 
         * \param pString
         * The string to be retrieved.
         * 
         * \return int
         * Returns the offset of the matching string in the string pool, or
         * -1 if an error occurs or if no matching string is found.
         */
    int GetStringOffset(_In_ PCWSTR pString) const
    {
        int offset = 0;

        if (!TryGetStringOffset(pString, &offset))
        {
            return -1;
        }
        return offset;
    }

    /*! 
         * Tries to get the offset of a specified string in the string pool.  Does
         * not report an error if no matching string is found.
         * 
         * \param pString
         * The string to be retrieved.
         *
         * \param pOffsetOut
         * Returns the offset of a matching string in the string pool, or -1 if
         * no matching string is found.
         * 
         * \return bool
         * Returns true if a matching string is found, false if an error occurs or
         * if no matching string is found.
         */
    _Success_(return ) bool TryGetStringOffset(_In_ PCWSTR pString, _Out_ int* pOffsetRtrn) const
    {
        if ((!pString) || (!pString[0]))
        {
            // not an error - NULL and empty string both map to element 0
            if (pOffsetRtrn)
            {
                *pOffsetRtrn = 0;
            }
            return true;
        }

        for (int i = 1; i < static_cast<int>(m_numChars); i++)
        {
            if ((pString[0] == m_pChars[i]) && StringOps::StringsMatch(pString, &m_pChars[i], m_comparison))
            {
                if (pOffsetRtrn)
                {
                    *pOffsetRtrn = i;
                }
                return true;
            }
        }
        if (pOffsetRtrn)
        {
            *pOffsetRtrn = -1;
        }
        return false;
    }

    /*!
         * Gets the string at a specified offset in the string pool.
         *
         * \param offset
         * Specifies the offset of the desired string.
         *
         * \return PCWSTR
         * Returns a pointer to the matching string inside the
         * string buffer.
         */
    PCWSTR GetString(_In_ int offset) const
    {
        if ((offset < 0) || (offset > static_cast<int>(m_sizeChars - 1)))
        {
            return nullptr;
        }

        return &m_pChars[offset];
    }

    /*! 
         * Gets the string at a specified offset in the string pool.
         * Reports an error if the offset is out of range.
         *
         * \param offset
         * Specifies the offset of the desired string.
         *
         * \param pStringOut
         * A _ref StringResult in which the requested string is
         * returned.
         * 
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    HRESULT GetString(_In_ int offset, _Inout_opt_ StringResult* pStringOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (offset < 0) || (offset > static_cast<int>(m_sizeChars - 1)));

        if (pStringOut)
        {
            RETURN_IF_FAILED(StringOps::SetResult(&m_pChars[offset], pStringOut));
        }

        return S_OK;
    }

    /*! 
         * Determines if a supplied string matches a specified
         * location in the string pool, using the comparison 
         * rules in effect for this pool.
         * 
         * \param offset
         * The offset in the string buffer to be compared.
         *
         * \param pString
         * The string to be compared.
         *
         * \return bool
         * Returns true if the string match, false if the strings
         * do not match or if an error occurs.
         */
    bool Equals(_In_ UINT32 offset, _In_ PCWSTR pString) const
    {
        if (offset >= m_sizeChars)
        {
            return false;
        }

        if (pString == nullptr)
        {
            pString = L"";
        }

        return StringOps::StringsMatch(&m_pChars[offset], pString, m_comparison);
    }

    /*! 
         * Returns a read-only pointer to the buffer used by the string pool.
         * 
         * \return PCWSTR
         * The buffer used by the string pool.
         */
    PCWSTR GetBuffer() const { return m_pChars; }
};

class WriteableStringPool : public TWriteableStringPool<PWSTR, PCWSTR, WCHAR>
{
public:
    static HRESULT CreateInstance(_Outptr_ WriteableStringPool** result) { return CreateInstance(DefaultInitialSize, false, result); }

    /*! 
         * Creates a resizable \ref WriteableStringPool with the default size and
         * the specified comparison method.
         * 
         * \param comparison
         * Specifies the comparison method to be used.
         * 
         * \param result
         * Returns a pointer to the new pool, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(_In_ UINT32 comparison, _Outptr_ WriteableStringPool** result)
    {
        return CreateInstance(DefaultInitialSize, comparison, result);
    }

    /*! 
         * Creates a resizable \ref WriteableStringPool with the specified size and
         * the comparison method.         
         * 
         * \param cchInitial
         * Specifies the initial size for the buffer, in characters.
         *
         * \param comparison
         * Specifies the comparison method to be used.
         * 
         * \param result
         * Returns a pointer to the new pool, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(_In_ UINT32 cchInitial, _In_ UINT32 comparison, _Outptr_ WriteableStringPool** result)
    {
        *result = nullptr;
        RETURN_HR_IF(E_INVALIDARG, cchInitial == 0);
        RETURN_IF_FAILED(
            TWriteableStringPool::CreateInstance(comparison, cchInitial, (TWriteableStringPool<PWSTR, PCWSTR, WCHAR>**)result));

        return S_OK;
    }

    /*! 
         * Creates a static \ref WriteableStringPool using a supplied static
         * buffer and the default comparison method.
         * 
         * \param pBuffer
         * The static buffer into which strings will be generated
         *
         * \param cchBuffer
         * The size of \ref pBuffer, in characters.
         *
         * \param result
         * Returns a pointer to the new pool, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(_In_reads_(cchBuffer) WCHAR* pBuffer, _In_ UINT32 cchBuffer, _Outptr_ WriteableStringPool** result)
    {
        return CreateInstance(pBuffer, cchBuffer, fCompareDefault, result);
    }

    /*! 
         * Creates a static \ref WriteableStringPool using a supplied static
         * buffer and specified comparison method.
         * 
         * \param pBuffer
         * The static buffer into which strings will be generated
         *
         * \param cchBuffer
         * The size of \ref pBuffer, in characters.
         *
         * \param comparison
         * Specifies the comparison method to be used.
         * 
         * \param result
         * Returns a pointer to the new pool, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(
        _In_reads_(cchBuffer) WCHAR* pBuffer,
        _In_ UINT32 cchBuffer,
        _In_ UINT32 comparison,
        _Outptr_ WriteableStringPool** result)
    {
        *result = nullptr;
        RETURN_HR_IF(E_INVALIDARG, (pBuffer == nullptr) || (cchBuffer < 1));

        RETURN_IF_FAILED(
            TWriteableStringPool::CreateInstance(pBuffer, cchBuffer, comparison, (TWriteableStringPool<PWSTR, PCWSTR, WCHAR>**)result));

        return S_OK;
    }

    virtual ~WriteableStringPool() {}

protected:
    WriteableStringPool() {}
};

} // namespace Microsoft::Resources::Build