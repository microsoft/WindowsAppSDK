// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/BaseInternal.h"

namespace Microsoft::Resources
{

template<class T>
int __cdecl CompareGenericType(__in const void* arg1, __in const void* arg2)
{
    return DefBlob_Compare(arg1, arg2, sizeof(T));
}

template<class T>
static bool HashGenericType(__in const void* data, INT* pHashOut)
{
    int hash = 23526;
    PBYTE pHash = (PBYTE)data;
    int len = sizeof(T);
    while (len-- > 0)
    {
        BYTE byte = (BYTE)*pHash++;
        if (byte)
        {
            hash *= byte + byte;
        }
    }
    *pHashOut = hash;
    return true;
}

typedef int(__cdecl* VoidComparerFunc)(const void*, const void*);
typedef bool (*VoidHashFunc)(const void*, INT*);

template<typename VALUE, typename CallBackCompareFunc = VoidComparerFunc, typename CallbackHashFunc = VoidHashFunc>

// Hash aware List class. If the hash function isn' given, it will use only (default) comparer function
// for each search and sort.
class DefList : public DefObject
{
private:
    typedef struct _HASH_KEY
    {
        UINT32 keyIndex;
        int hash;
    } HASH_KEY;

    VALUE* m_pData;
    UINT32 m_maxSize;
    UINT32 m_nData;

    CallBackCompareFunc m_pFnComparer;
    CallbackHashFunc m_pFnHash;
    bool m_fSorted;

    HASH_KEY* m_pHashTable;

public:
    DefList() : m_pData(NULL), m_pHashTable(NULL), m_nData(0), m_maxSize(0), m_pFnHash(NULL)
    {
        m_pFnComparer = reinterpret_cast<CallBackCompareFunc>(&CompareGenericType<VALUE>);
    }

    static HRESULT CreateInstance(_Outptr_ DefList<VALUE, CallBackCompareFunc, CallbackHashFunc>** result)
    {
        return CreateInstance(10, &CompareGenericType<VALUE>, NULL, result);
    }

    static HRESULT CreateInstance(UINT32 size, _Outptr_ DefList<VALUE, CallBackCompareFunc, CallbackHashFunc>** result)
    {
        return CreateInstance(size, &CompareGenericType<VALUE>, NULL, result);
    }

    static HRESULT CreateInstance(
        UINT32 size,
        __in CallBackCompareFunc pFnCallBack,
        _Outptr_ DefList<VALUE, CallBackCompareFunc, CallbackHashFunc>** result)
    {
        return CreateInstance(size, pFnCallBack, NULL, result);
    }

    static HRESULT CreateInstance(
        UINT32 size,
        __in CallbackHashFunc pCallBackHash,
        _Outptr_ DefList<VALUE, CallBackCompareFunc, CallbackHashFunc>** result)
    {
        return CreateInstance(size, &CompareGenericType<VALUE>, pCallBackHash, result);
    }

    static HRESULT CreateInstance(
        UINT32 size,
        _In_ CallBackCompareFunc pFnComparer,
        _In_ CallbackHashFunc pFunHash,
        _Outptr_ DefList<VALUE, CallBackCompareFunc, CallbackHashFunc>** result)
    {
        *result = NULL;
        DefList<VALUE, CallBackCompareFunc, CallbackHashFunc>* list = new DefList<VALUE, CallBackCompareFunc, CallbackHashFunc>();
        if (list == NULL)
        {
            return E_OUTOFMEMORY;
        }

        HRESULT hr = list->Init(size, pFnComparer, pFunHash);
        if (FAILED(hr))
        {
            delete list;
            return hr;
        }

        *result = list;
        return S_OK;
    }

    virtual ~DefList()
    {
        if (m_pData)
        {
            _DefFree(m_pData);
        }

        if (m_pHashTable)
        {
            _DefFree(m_pHashTable);
        }
    }

    HRESULT Init(UINT32 size, __in CallBackCompareFunc pFnComparer, __in CallbackHashFunc pFunHash)
    {

        m_nData = 0;
        m_maxSize = size;
        m_pFnComparer = pFnComparer;
        m_pFnHash = pFunHash;
        m_pHashTable = NULL;

        if (m_maxSize == 0)
        {
            m_maxSize = 5;
        }

        m_pData = _DefArray_AllocZeroed(VALUE, m_maxSize);
        if (!m_pData)
        {
            return E_OUTOFMEMORY;
        }

        if (m_pFnHash != NULL)
        {
            m_pHashTable = _DefArray_AllocZeroed(HASH_KEY, m_maxSize);
            if (!m_pHashTable)
            {
                return E_OUTOFMEMORY;
            }
        }

        m_fSorted = false;

        return S_OK;
    }

    HRESULT Add(__in VALUE value, __out_opt INT32* pIndexOut = NULL)
    {
        if (pIndexOut)
        {
            *pIndexOut = -1;
        }
        if (m_maxSize <= m_nData)
        {

            VALUE* pData;
            UINT32 oldSize = m_maxSize;
            UINT32 newSize = ((m_maxSize != 0) ? m_maxSize * 2 : 10);
            HRESULT hr = _DefArray_Expand(m_pData, VALUE, oldSize, newSize, &pData);
            if (FAILED(hr))
            {
                return hr;
            }

            m_pData = pData;

            if (m_pFnHash)
            {

                HASH_KEY* pHashTable;
                hr = _DefArray_Expand(m_pHashTable, HASH_KEY, oldSize, newSize, &pHashTable);
                if (FAILED(hr))
                {
                    return hr;
                }
                m_pHashTable = pHashTable;
            }
            m_maxSize = newSize;
        }

        m_pData[m_nData] = value;

        if (m_pFnHash)
        {
            int valueHash;
            if (!m_pFnHash(&value, &valueHash))
            {
                return E_DEF_LIST_HASH_CALCULATE_FAILED;
            }

            m_pHashTable[m_nData].hash = (valueHash & 0x7fffffff);
            m_pHashTable[m_nData].keyIndex = m_nData;
        }

        if (pIndexOut)
        {
            *pIndexOut = m_nData;
        }

        m_nData++;
        m_fSorted = false;
        return S_OK;
    }

    HRESULT InsertAt(__in UINT32 index, __in VALUE value)
    {
        if (index >= m_nData)
        {
            if (index >= m_nData)
            {
                return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
            }
        }

        m_pData[index] = value;

        if (m_pFnHash)
        {
            int valueHash;
            if (!m_pFnHash(&value, &valueHash))
            {
                return E_DEF_LIST_HASH_CALCULATE_FAILED;
            }
            m_pHashTable[index].hash = (valueHash & 0x7fffffff);
            m_pHashTable[index].keyIndex = index;
        }

        m_fSorted = false;
        return S_OK;
    }

    UINT32 Count() const { return m_nData; }

    UINT32 CurrentCapacity() const { return m_maxSize; }

    bool IsSorted() const { return m_fSorted; }

    UINT32 GetIndex(__in VALUE value) const { return Search(value); }

    bool TryGetIndex(__in VALUE value, __out INT32* pIndexOut) const
    {

        if (!pIndexOut)
        {
            return false;
        }
        int index = Search(value);
        if (index >= 0)
        {
            *pIndexOut = index;
            return true;
        }
        return false;
    }

    bool TryGetValue(__in UINT32 index, __out VALUE* pValueOut) const
    {

        if (!pValueOut)
        {
            return false;
        }

        if (index >= m_nData)
        {
            return false;
        }
        if (m_fSorted)
        {
            if (m_pFnHash)
            {
                *pValueOut = m_pData[m_pHashTable[index].keyIndex];
            }
            else
            {
                *pValueOut = m_pData[index];
            }
        }
        else
        {
            *pValueOut = m_pData[index];
        }

        return true;
    }

    HRESULT GetPtrValue(UINT32 index, _Out_ VALUE** result) const
    {
        *result = NULL;
        if (index >= m_nData)
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }

        if (m_pFnHash)
        {
            *result = &m_pData[m_pHashTable[index].keyIndex];
        }
        else
        {
            *result = &m_pData[index];
        }
        return S_OK;
    }

    HRESULT RemoveAt(UINT32 index)
    {
        if (index >= m_nData)
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }

        m_nData--;
        if (m_nData - index > 0)
        {
            if (m_pFnHash)
            {
                // remove data entry
                MoveMemory(
                    &m_pData[m_pHashTable[index].keyIndex], &m_pData[m_pHashTable[index].keyIndex + 1], (m_nData - index) * sizeof(VALUE));
                // remove hash key entry
                MoveMemory(&m_pHashTable[index], &m_pHashTable[index + 1], (m_nData - index) * sizeof(VALUE));
            }
            else
            {
                MoveMemory(&m_pData[index], &m_pData[index + 1], (m_nData - index) * sizeof(VALUE));
            }
        }

        return S_OK;
    }

    void Clear()
    {
        if (m_pData)
        {
            _DefFree(m_pData);
            m_pData = NULL;
        }

        if (m_pFnHash)
        {
            if (m_pHashTable)
            {
                _DefFree(m_pHashTable);
                m_pHashTable = NULL;
            }
        }

        m_nData = 0;
        m_maxSize = 0;
    }

    void Reset() { m_nData = 0; }

    bool SortValue()
    {
        if (m_pFnHash)
        {
            // hash based sort
            qsort(m_pHashTable, m_nData, sizeof(HASH_KEY), &CompareHashKey);
        }
        else
        {
            // comparer based sort
            VoidComparerFunc pFnVoidComparer = reinterpret_cast<VoidComparerFunc>(m_pFnComparer);
            qsort(m_pData, m_nData, sizeof(VALUE), pFnVoidComparer);
        }

        m_fSorted = true;
        return true;
    }

    bool Contains(__in VALUE value) const
    {
        if (Search(value) >= 0)
        {
            return true;
        }
        return false;
    }

    /*!
            Caller needs to deallocate returned array by calling _DefFree
            */
    HRESULT ToArray(_Outptr_ VALUE** result) const
    {
        *result = NULL;
        VALUE* pArray = _DefArray_AllocZeroed(VALUE, m_nData);
        if (!pArray)
        {
            return E_OUTOFMEMORY;
        }

        for (UINT32 i = 0; i < m_nData; i++)
        {
            if (m_pFnHash)
            {
                pArray[i] = m_pData[m_pHashTable[i].keyIndex];
            }
            else
            {
                pArray[i] = m_pData[i];
            }
        }

        *result = pArray;
        return S_OK;
    }

private:
    static int __cdecl CompareHashKey(__in const void* map1, __in const void* map2)
    {

        int hash1 = static_cast<const HASH_KEY*>(map1)->hash;
        int hash2 = static_cast<const HASH_KEY*>(map2)->hash;

        if (hash1 == hash2)
        {
            return 0;
        }
        else if (hash1 <= 0 && hash2 >= 0)
        {
            return -1;
        }
        else if (hash1 >= 0 && hash2 <= 0)
        {
            return 1;
        }
        else if (hash1 <= 0 && hash2 <= 0)
        {
            if (hash1 < hash2)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return hash1 - hash2;
        }
    }

    int Search(__in VALUE value) const
    {

        int foundIndex = -1;
        int valueHash = 0;

        if (m_pFnHash)
        {
            if (!m_pFnHash(&value, &valueHash))
            {
                return -1;
            }
            valueHash &= 0x7fffffff;
        }

        if (m_fSorted)
        {
            if (m_pFnHash)
            {
                HASH_KEY* pHash = reinterpret_cast<HASH_KEY*>(bsearch(&valueHash, m_pHashTable, m_nData, sizeof(HASH_KEY), CompareHashKey));

                if (pHash)
                {
                    int med = static_cast<int>(pHash - m_pHashTable);
                    if (m_pFnComparer(&m_pData[m_pHashTable[med].keyIndex], &value) == 0)
                    {
                        foundIndex = med;
                    }
                    else
                    {
                        int tempMed = med - 1;
                        while ((tempMed >= 0) && (m_pHashTable[tempMed].hash == valueHash))
                        {
                            if (m_pFnComparer(&m_pData[m_pHashTable[tempMed].keyIndex], &value) == 0)
                            {
                                foundIndex = tempMed;
                            }
                            tempMed--;
                        }
                        tempMed = med + 1;
                        while (m_pHashTable[tempMed].hash == valueHash)
                        {
                            if (m_pFnComparer(&m_pData[m_pHashTable[tempMed].keyIndex], &value) == 0)
                            {
                                foundIndex = tempMed;
                                break;
                            }
                            tempMed++;
                        }
                    }
                }
            }
            else
            { // no hash
                VoidComparerFunc pFnVoidComparer = reinterpret_cast<VoidComparerFunc>(m_pFnComparer);
                VALUE* pValue = reinterpret_cast<VALUE*>(bsearch(&value, m_pData, m_nData, sizeof(VALUE), pFnVoidComparer));

                if (pValue)
                {
                    foundIndex = static_cast<int>(pValue - m_pData);
                }
            }
        }
        else
        { // not sorted
            for (UINT32 i = 0; i < m_nData; i++)
            {
                if (m_pFnHash)
                {
                    if (m_pHashTable[i].hash == valueHash)
                    {
                        if (m_pFnComparer(&m_pData[m_pHashTable[i].keyIndex], &value) == 0)
                        {
                            foundIndex = i;
                            break;
                        }
                    }
                }
                else
                {
                    if (m_pFnComparer(&m_pData[i], &value) == 0)
                    {
                        foundIndex = i;
                        break;
                    }
                }
            }
        }

        return foundIndex;
    }
};

// This is a wrapper class for DefList,
// which helps cleaning up the list of VALUE* in destructor
template<typename VALUE, typename CallBackCompareFunc = VoidComparerFunc, typename CallbackHashFunc = VoidHashFunc>
class DefPointerList : public DefList<VALUE*, CallBackCompareFunc, CallbackHashFunc>
{
public:
    virtual ~DefPointerList()
    {
        for (int i = 0; i < DefList::Count(); i++)
        {
            const VALUE* pMember = nullptr;
            if (TryGetValue(i, &pMember))
            {
                delete (pMember);
            }
        }
    }
};

typedef int (*CompareFuncStringResultType)(const StringResult** ppStringResult1, const StringResult** ppStringResult2);

typedef bool (*HashFuncStringResultType)(const StringResult** ppStringResult1, INT* pHashOut);

typedef DefPointerList<const StringResult, CompareFuncStringResultType, HashFuncStringResultType> StringResultCollection;

} // namespace Microsoft::Resources
