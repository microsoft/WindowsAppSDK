// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Common\BaseInternal.h"

namespace Microsoft::Resources
{

template<class T>
class DynamicArray : public DefObject
{
public:
    static HRESULT CreateInstance(_In_ UINT szInit, _Outptr_ DynamicArray<T>** array)
    {
        *array = nullptr;

        AutoDeletePtr<DynamicArray<T>> pRtrn = new DynamicArray<T>();
        RETURN_IF_NULL_ALLOC(pRtrn);

        if (szInit != 0)
        {
            pRtrn->m_pData = _DefArray_AllocZeroed(T, szInit);
            RETURN_IF_NULL_ALLOC(pRtrn->m_pData);

#pragma prefast(suppress : __WARNING_HIGH_PRIORITY_OVERFLOW_POSTCONDITION "The allocator allocates szInit elements of T size.");
            pRtrn->m_szData = szInit;
        }

        *array = pRtrn.Detach();

        return S_OK;
    }

    DynamicArray() : m_pData(nullptr), m_szData(0), m_nData(0) {}

    ~DynamicArray() { Def_Free(m_pData); }

    _Success_(return ) HRESULT Add(_In_ T pv, _Out_opt_ int* pIndexOut = nullptr)
    {
        if (pIndexOut != nullptr)
        {
            *pIndexOut = 0;
        }

        if (m_nData >= m_szData)
        {
            RETURN_IF_FAILED_EXPECTED(Extend(m_nData + 1, false));
        }

        m_pData[m_nData] = pv;

        if (pIndexOut != nullptr)
        {
            *pIndexOut = m_nData;
        }

        m_nData++;
        return S_OK;
    }

    HRESULT Insert(_In_opt_ T pv, _In_ UINT ind)
    {
        // can't add more than one element beyond the end of the array
        RETURN_HR_IF_EXPECTED(E_INVALIDARG, ind > m_nData);

        // make sure we have room
        if (m_nData >= m_szData)
        {
            RETURN_IF_FAILED_EXPECTED(Extend(m_nData + 1, false));
        }

        // move existing data out of the way
        if (ind < m_nData)
        {
            memmove(&m_pData[ind + 1], &m_pData[ind], (m_nData - ind) * sizeof(T));
        }

        // insert & update to new size
        m_pData[ind] = pv;
        m_nData++;

        return S_OK;
    }

    _Success_(return == true)
    bool TryGet(_In_ UINT ind, _Out_ T* pValueOut) const
    {
        _Analysis_assume_(m_szData >= m_nData);

        if (ind >= m_nData)
        {
            return false;
        }
        *pValueOut = m_pData[ind];
        return true;
    }

    HRESULT Get(_In_ UINT ind, _Out_ T* value) const
    {
        *value = NULL;
        _Analysis_assume_(m_szData >= m_nData);

        RETURN_HR_IF_EXPECTED(E_INVALIDARG, ind >= m_nData);

        *value = m_pData[ind];
        return S_OK;
    }

    HRESULT Delete(_In_ UINT ind)
    {
        _Analysis_assume_(m_szData >= m_nData);

        RETURN_HR_IF_EXPECTED(E_INVALIDARG, ind >= m_nData);

        for (int i = ind; i < m_nData - 1; i++)
        {
            m_pData[i] = m_pData[i + 1];
        }
        m_nData--;
        return S_OK;
    }

    HRESULT Set(_In_ UINT ind, T value)
    {
        _Analysis_assume_(m_szData >= m_nData);

        RETURN_HR_IF_EXPECTED(E_INVALIDARG, ind >= m_nData);

        m_pData[ind] = value;
        return S_OK;
    }

    HRESULT ExtendAndSet(_In_ UINT index, T value, _Out_opt_ T* pOldValue = nullptr)
    {
        if (index >= m_nData)
        {
            RETURN_IF_FAILED_EXPECTED(SetExtent(index + 1));
        }

        _Analysis_assume_(index < m_szData);

        if (pOldValue != nullptr)
        {
            *pOldValue = m_pData[index];
        }

        m_pData[index] = value;
        return S_OK;
    }

    UINT Count() const { return m_nData; }

    T* GetAll() const { return m_pData; }

    void Reset() { m_nData = 0; }

    HRESULT SetExtent(_In_ UINT extent)
    {
        RETURN_HR_IF_EXPECTED(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), extent < m_nData);

        if (extent > m_szData)
        {
            RETURN_IF_FAILED_EXPECTED(Extend(extent, true));
        }

        m_nData = extent;
        return S_OK;
    }

protected:
    HRESULT Extend(_In_ UINT szExtend, _In_ bool exact)
    {
        if (szExtend <= m_szData)
        {
            // already big enough
            return S_OK;
        }

        UINT szNew = ((m_szData > 0) ? m_szData : szExtend);
        if (!exact)
        {
            while (szNew < szExtend)
            {
                szNew *= 2;
            }
        }
        else
        {
            szNew = szExtend;
        }

        _Analysis_assume_(m_szData >= m_nData);
        RETURN_HR_IF(E_OUTOFMEMORY, !_DefArray_TryEnsureSize(&m_pData, T, m_nData, szNew));
        m_szData = szNew;

        return S_OK;
    }

    _Field_size_opt_(m_szData) T* m_pData;

    UINT m_szData;
    UINT m_nData;
};

} // namespace Microsoft::Resources