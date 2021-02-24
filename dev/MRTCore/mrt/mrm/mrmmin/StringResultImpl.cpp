// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "mrm/common/BaseInternal.h"
#include "stringresult.h"

#define CHECK_DEFSTRING(str) \
    { \
        if (DefStringResult_IsInvalid(str)) \
        { \
            return E_INVALIDARG; \
        } \
    }

void* _Def_Inspect(__in void* pSelf, __in PCWSTR typeStr, Def_DescribeCallback describe)
{
    wprintf(L"#<%s:%p", typeStr, pSelf);
    (*describe)(pSelf);
    wprintf(L">");
    return pSelf;
}

HRESULT _DefStringResult_Alloc(_Outptr_ DEFSTRINGRESULT** result)
{
    *result = _DefAllocZeroed(DEFSTRINGRESULT);
    if (*result == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    return S_OK;
}

HRESULT DefStringResult_New(_In_opt_ PCWSTR pStr, DEFRESULTTYPE type, _Outptr_ DEFSTRINGRESULT** result)
{
    *result = nullptr;

    if (type == DefResultType_Reference)
    {
        return DefStringResult_NewRef(pStr, result);
    }
    if (type == DefResultType_Buffer)
    {
        return DefStringResult_NewBuf(pStr, result);
    }
    return E_INVALIDARG;
}

HRESULT
DefStringResult_NewRef(__in_opt PCWSTR pStr, _Outptr_ DEFSTRINGRESULT** result)
{
    *result = nullptr;

    DEFSTRINGRESULT* pSelf = nullptr;
    HRESULT hr = _DefStringResult_Alloc(&pSelf);
    if (SUCCEEDED(hr))
    {
        hr = DefStringResult_InitRef(pSelf, pStr);
        if (SUCCEEDED(hr))
        {
            *result = pSelf;
            pSelf = nullptr;
        }
    }

    DefStringResult_Delete(pSelf);

    return hr;
}

HRESULT
DefStringResult_NewBuf(__in_opt PCWSTR pStr, _Outptr_ DEFSTRINGRESULT** result)
{
    *result = nullptr;

    DEFSTRINGRESULT* pSelf = nullptr;
    HRESULT hr = _DefStringResult_Alloc(&pSelf);
    if (SUCCEEDED(hr))
    {
        hr = DefStringResult_InitBuf(pSelf, pStr);
        if (SUCCEEDED(hr))
        {
            *result = pSelf;
            pSelf = nullptr;
        }
    }

    DefStringResult_Delete(pSelf);

    return hr;
}

HRESULT
DefStringResult_Init(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr, _In_ DEFRESULTTYPE type)
{
    if (type == DefResultType_Reference)
    {
        return DefStringResult_InitRef(pSelf, pStr);
    }

    if (type == DefResultType_Buffer)
    {
        return DefStringResult_InitBuf(pSelf, pStr);
    }

    return E_INVALIDARG;
}

static HRESULT _DefStringResult_EnsureEmptyBuffer(_Inout_ DEFSTRINGRESULT* pSelf, _In_ size_t cchMinBufferSize)
{
    PWCHAR pNewBuf = nullptr;
    PWCHAR pOldBuf = nullptr;

    if (pSelf == nullptr)
    {
        return E_INVALIDARG;
    }

    if (cchMinBufferSize < 1)
    {
        cchMinBufferSize = 1;
    }

    if (pSelf->pBuf != nullptr)
    {
        if (pSelf->cchBuf >= cchMinBufferSize)
        {
            // Current buffer is big enough.  Truncate
            // it and use it.
            pSelf->pBuf[0] = L'\0';
            pSelf->pRef = pSelf->pBuf;
            return S_OK;
        }
        pOldBuf = pSelf->pBuf;
    }

    pNewBuf = _DefArray_AllocZeroed(WCHAR, cchMinBufferSize);
    if (pNewBuf == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    pNewBuf[0] = L'\0';

    pSelf->pBuf = pNewBuf;
    pSelf->cchBuf = (UINT32)cchMinBufferSize;
    pSelf->pRef = pSelf->pBuf;
    if (pOldBuf)
    {
        Def_Free(pOldBuf);
    }
#pragma prefast(suppress : 26045, "_DefArray_AllocZeroed ensures len(pNewBuf) == cchMinBufferSize")
    return S_OK;
}

static HRESULT _DefStringResult_EnsureBuffer(_Inout_ DEFSTRINGRESULT* pSelf, _In_ size_t cchMinBufferSize)
{
    HRESULT hr = S_OK;
    size_t cchCurrent = 0;
    PWSTR pOldBuf = nullptr;
    PWSTR pNewBuf = nullptr;

    if (pSelf == nullptr)
    {
        return E_INVALIDARG;
    }

    // figure out how big our current string is
    if (pSelf->pRef != nullptr)
    {
        hr = _DefStringCchLength(pSelf->pRef, _DEF_STRSAFE_MAX_CCH, &cchCurrent);
        if (FAILED(hr))
        {
            return hr;
        }
    }

    // We can't shrink the buffer, so if cchMinBufferSize is smaller than
    // the length of our current contents (plus a NUL), extend it.
    if (cchMinBufferSize < (cchCurrent + 1))
    {
        cchMinBufferSize = cchCurrent + 1;
    }

    // Keep the old buffer in case we need to copy its contents
    pOldBuf = pSelf->pBuf;

    // If we have no buffer or if our existing buffer is too small,
    // allocate a new one.
    if (pSelf->pBuf && (pSelf->cchBuf >= cchMinBufferSize))
    {
        // current buffer is big enough.  We're good to go.
        // Check whether reference is different than the buffer
        if (pSelf->pRef != pSelf->pBuf)
        {
            if (pSelf->pRef != nullptr)
            {
                // Ensure existing string is copied to this buffer
                hr = _DefStringCchCopy(pSelf->pBuf, pSelf->cchBuf, pSelf->pRef);
                if (FAILED(hr))
                {
                    return hr;
                }
            }

            // Update pRef to pBuf
            pSelf->pRef = pSelf->pBuf;
        }

        return S_OK;
    }

    pNewBuf = _DefArray_AllocZeroed(WCHAR, cchMinBufferSize);
    if (pNewBuf == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    pNewBuf[0] = L'\0';

    // Copy the previous contents
    if (pSelf->pRef && pSelf->pRef[0])
    {
        hr = _DefStringCchCopy(pNewBuf, cchMinBufferSize, pSelf->pRef);
        if (FAILED(hr))
        {
            Def_Free(pNewBuf);
            return hr;
        }
    }

    pSelf->pBuf = pNewBuf;
    pSelf->cchBuf = (UINT32)cchMinBufferSize;
    pSelf->pRef = pNewBuf;

    if (pOldBuf)
    {
        Def_Free(pOldBuf);
    }
#pragma prefast(suppress : 26045, "_DefArray_AllocZeroed ensures len(pNewBuf) == cchMinBufferSize")
    return S_OK;
}

static HRESULT _DefStringResult_InitEmpty(_Inout_ DEFSTRINGRESULT* pSelf, _In_ size_t cchBuf)
{
    PWSTR pTempStr = nullptr;

    if ((pSelf == nullptr) || (cchBuf > DEFRESULT_MAX))
    {
        return E_INVALIDARG;
    }

    pSelf->pRef = nullptr;

    // Empty
    if (cchBuf == 0)
    {
        pSelf->pBuf = nullptr;
        pSelf->cchBuf = 0;
        return S_OK;
    }

    // Not Empty
    pTempStr = _DefArray_AllocZeroed(wchar_t, cchBuf);
    if (pTempStr == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    pTempStr[0] = L'\0';

    pSelf->pBuf = pTempStr;
    pSelf->cchBuf = (UINT32)cchBuf;
#pragma prefast(suppress : 26045, "_DefArray_AllocZeroed ensures len(pTempStr) == cchBuf")
    return S_OK;
}

HRESULT
DefStringResult_InitRef(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr)
{
    if (pSelf == nullptr)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = _DefStringResult_InitEmpty(pSelf, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    pSelf->pRef = pStr;
    return S_OK;
}

HRESULT
DefStringResult_InitBuf(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pInitStr)
{
    if (pSelf == nullptr)
    {
        return E_INVALIDARG;
    }

    if (pInitStr == nullptr)
    {
        _DefStringResult_InitEmpty(pSelf, 0);
    }
    else
    {
        // Fill with string
        size_t cchInitStr = 0;
        HRESULT hr = _DefStringCchLength(pInitStr, _DEF_STRSAFE_MAX_CCH, &cchInitStr);
        if (FAILED(hr))
        {
            return hr;
        }
        cchInitStr++; // NULL terminator

        if (cchInitStr <= 1)
        {
            _DefStringResult_InitEmpty(pSelf, 0); // will not fail
        }
        else
        {
            // Alloc new buffer
            PWSTR pNewBuf = _DefArray_AllocZeroed(wchar_t, cchInitStr);
            if (pNewBuf == nullptr)
            {
                return E_OUTOFMEMORY;
            }

            hr = _DefStringCchCopy(pNewBuf, cchInitStr, pInitStr);
            if (FAILED(hr))
            {
                _DefFree(pNewBuf);
                return hr;
            }

            pSelf->pBuf = pNewBuf;
            pSelf->cchBuf = (UINT32)cchInitStr;
        }
    }

    pSelf->pRef = pSelf->pBuf;
#pragma prefast(suppress : 26045, "_DefArray_AllocZeroed ensures len(pNewBuf) == cchInitStr")
    return S_OK;
}

HRESULT
DefStringResult_GetCopy(_In_ const DEFSTRINGRESULT* pSelf, _Inout_ DEFSTRINGRESULT* pStringOut)
{
    HRESULT hr = S_OK;
    size_t cchSelf = 0;

    if (DefStringResult_IsInvalid(pSelf) || DefStringResult_IsInvalid(pStringOut))
    {
        return E_INVALIDARG;
    }

    // figure out how much space we need
    hr = DefStringResult_GetLength(pSelf, &cchSelf);
    if (FAILED(hr))
    {
        return hr;
    }
    cchSelf++;

    hr = _DefStringResult_EnsureEmptyBuffer(pStringOut, cchSelf);
    if (FAILED(hr))
    {
        return hr;
    }
    __analysis_assume(pStringOut->cchBuf >= cchSelf);

    if (pSelf->pRef == nullptr)
    {
        // empty string, just terminate it.
#pragma prefast(suppress : 6011, "_DefStringResult_EnsureEmptyBuffer ensures len(pStringOut->pBuf) >= 1")
        pStringOut->pBuf[0] = L'\0';
        return S_OK;
    }

    // Copy our string into the other guy's buffer
    hr = _DefStringCchCopy(pStringOut->pBuf, pStringOut->cchBuf, pSelf->pRef);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

HRESULT
DefStringResult_GetLength(_In_ const DEFSTRINGRESULT* pSelf, _Out_ size_t* pLengthOut)
{
    *pLengthOut = 0;
    size_t cchMax = 0;

    if (DefStringResult_IsInvalid(pSelf) || (pLengthOut == nullptr))
    {
        return E_INVALIDARG;
    }

    *pLengthOut = 0;

    if ((!pSelf->pRef) || (!pSelf->pRef[0]))
    {
        return S_OK;
    }

    cchMax = (pSelf->pBuf == pSelf->pRef) ? pSelf->cchBuf : _DEF_STRSAFE_MAX_CCH;

    return _DefStringCchLength(pSelf->pRef, cchMax, pLengthOut);
}

HRESULT
DefStringResult_GetRef(_In_ const DEFSTRINGRESULT* pSelf, _Out_ PCWSTR* ref)
{
    *ref = nullptr;

    CHECK_DEFSTRING(pSelf);

    *ref = pSelf->pRef;
    return S_OK;
}

HRESULT
DefStringResult_GetWritableRef(_In_ DEFSTRINGRESULT* pSelf, _In_ size_t cchMinBuffer, _Out_ PWSTR* ref, _Out_opt_ size_t* pcchRefOut)
{
    *ref = nullptr;
    if (pcchRefOut)
    {
        *pcchRefOut = 0;
    }

    CHECK_DEFSTRING(pSelf);

    HRESULT hr = _DefStringResult_EnsureBuffer(pSelf, cchMinBuffer);
    if (FAILED(hr))
    {
        return hr;
    }

    if (pcchRefOut)
    {
        *pcchRefOut = pSelf->cchBuf;
    }

    *ref = pSelf->pBuf;
    return S_OK;
}

HRESULT
DefStringResult_GetSize(_In_ const DEFSTRINGRESULT* pSelf, _Out_ size_t* size)
{
    *size = 0;
    CHECK_DEFSTRING(pSelf);

    if (!pSelf->pRef)
    {
        return S_OK;
    }

    if (DefStringResult_GetType(pSelf) == DefResultType_Buffer)
    {
        *size = pSelf->cchBuf;
        return S_OK;
    }

    HRESULT hr = DefStringResult_GetLength(pSelf, size);
    if (SUCCEEDED(hr))
    {
        (*size)++; // include terminator
    }
    return hr;
}

// Internal _GetType used to avoid recursive loop in _Validate
DEFRESULTTYPE
_DefStringResult_GetType(_In_ const DEFSTRINGRESULT* pSelf)
{
    if (pSelf == nullptr)
    {
        return DefResultType_None;
    }

    if (pSelf->pRef == nullptr)
    {
        return DefResultType_None;
    }

    if (pSelf->pRef == pSelf->pBuf)
    {
        return DefResultType_Buffer;
    }

    return DefResultType_Reference;
}

DEFRESULTTYPE
DefStringResult_GetType(_In_ const DEFSTRINGRESULT* pSelf)
{
    if (DefStringResult_IsInvalid(pSelf))
    {
        return DefResultType_None;
    }

    return _DefStringResult_GetType(pSelf);
}

HRESULT
DefStringResult_CompareWithOptions(
    _In_ const DEFSTRINGRESULT* pSelf,
    _In_ PCWSTR pStr,
    DEFCOMPAREOPTIONS fOptions,
    _Out_ DEFCOMPARISON* result)
{
    *result = Def_CompareError;
    if (DefStringResult_IsInvalid(pSelf))
    {
        return E_INVALIDARG;
    }

    // The NULL compares
    if (pSelf->pRef == nullptr)
    {
        *result = ((pStr == nullptr) ? Def_Equal : Def_Less);
        return S_OK;
    }
    else if (pStr == nullptr)
    {
        *result = Def_Greater;
        return S_OK;
    }

    // The 'Real' Compare
    if (fOptions & DefCompare_CaseInsensitive)
    {
        *result = DefString_ICompare(pSelf->pRef, pStr);
        return S_OK;
    }
    *result = DefString_Compare(pSelf->pRef, pStr);
    return S_OK;
}

HRESULT
DefStringResult_Compare(_In_ const DEFSTRINGRESULT* pSelf, _In_ PCWSTR pStr, _Out_ DEFCOMPARISON* result)
{
    return DefStringResult_CompareWithOptions(pSelf, pStr, DefCompare_Default, result);
}

HRESULT
DefStringResult_ICompare(_In_ const DEFSTRINGRESULT* pSelf, _In_ PCWSTR pStr, _Out_ DEFCOMPARISON* result)
{
    return DefStringResult_CompareWithOptions(pSelf, pStr, DefCompare_CaseInsensitive, result);
}

void _DefStringResult_Describe(_In_ const void* pSelfVoid)
{
    const DEFSTRINGRESULT* pSelf = (const DEFSTRINGRESULT*)pSelfVoid;
    if (pSelf != nullptr)
    {
        wprintf(L" ref=\"%s\", buf=\"%s\", cch=%i", pSelf->pRef, pSelf->pBuf, pSelf->cchBuf);
    }
}

void _DefStringResult_Inspect(_In_ const DEFSTRINGRESULT* pSelf) { _Def_Inspect((void*)pSelf, L"String", _DefStringResult_Describe); }

void DefStringResult_Inspect(_In_ const DEFSTRINGRESULT* pSelf)
{
    _DefStringResult_Inspect(pSelf);
    wprintf(L"\n");
}

HRESULT
DefStringResult_SetRef(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr)
{
    CHECK_DEFSTRING(pSelf);

    pSelf->pRef = pStr;
    return S_OK;
}

HRESULT
DefStringResult_SetCopy(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr)
{
    CHECK_DEFSTRING(pSelf);

    if (pStr == nullptr)
    {
        // Release rather than clear on NULL because you can
        // easily clear by setting to an empty string
        return DefStringResult_Clear(pSelf, FALSE);
    }
    else
    {
        // Not NULL
        size_t cchStr = 0;
        HRESULT hr = _DefStringCchLength(pStr, _DEF_STRSAFE_MAX_CCH, &cchStr);
        if (FAILED(hr))
        {
            return hr;
        }

        hr = _DefStringResult_EnsureEmptyBuffer(pSelf, cchStr + 1);
        if (FAILED(hr))
        {
            return hr;
        }

        hr = _DefStringCchCopy(pSelf->pBuf, pSelf->cchBuf, pStr);
        if (FAILED(hr))
        {
            return hr;
        }
    }

    pSelf->pRef = pSelf->pBuf;
    return S_OK;
}

HRESULT
DefStringResult_SetContents(_Inout_ DEFSTRINGRESULT* pSelf, _Inout_ PWSTR pBuffer, _In_ size_t cchBuffer)
{
    if (DefStringResult_IsInvalid(pSelf) || (pBuffer == nullptr) || (cchBuffer == 0))
    {
        return E_INVALIDARG;
    }

    HRESULT hr = DefStringResult_Clear(pSelf, TRUE);
    if (FAILED(hr))
    {
        return hr;
    }

    pSelf->pBuf = pBuffer;
    pSelf->cchBuf = (UINT32)cchBuffer;
    pSelf->pRef = pSelf->pBuf;
#pragma prefast(suppress : 26045, "Caller must ensure null termination")
    return S_OK;
}

HRESULT
DefStringResult_SetEmptyContents(
    _Inout_ DEFSTRINGRESULT* pSelf,
    _In_ size_t cchBufferMin,
    _Out_opt_ WCHAR** result,
    _Out_opt_ size_t* pcchBufferOut)
{
    if (result != nullptr)
    {
        *result = nullptr;
    }

    if (pcchBufferOut)
    {
        *pcchBufferOut = 0;
    }

    if (DefStringResult_IsInvalid(pSelf) || (cchBufferMin == 0))
    {
        return E_INVALIDARG;
    }

    HRESULT hr = _DefStringResult_EnsureEmptyBuffer(pSelf, cchBufferMin);
    if (FAILED(hr))
    {
        return hr;
    }

    if (result != nullptr)
    {
        *result = pSelf->pBuf;
    }

    if (pcchBufferOut)
    {
        *pcchBufferOut = pSelf->cchBuf;
    }
    return S_OK;
}

HRESULT
DefStringResult_ReleaseContents(
    _Inout_ DEFSTRINGRESULT* pSelf,
    _Outptr_result_buffer_(*pcchBufferOut) PWSTR* ppBufferOut,
    _Out_ size_t* pcchBufferOut)
{
    if ((ppBufferOut == nullptr) || (pcchBufferOut == nullptr) || (DefStringResult_IsInvalid(pSelf)) || (pSelf->pBuf == nullptr) ||
        (pSelf->cchBuf == 0))
    {
        return E_INVALIDARG;
    }

    *ppBufferOut = pSelf->pBuf;
    *pcchBufferOut = pSelf->cchBuf;

    return _DefStringResult_InitEmpty(pSelf, 0);
}

HRESULT
_DefResultBuffer_Init(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pInitStr, _In_ size_t cchBuf)
{
    if ((pSelf == nullptr) || (cchBuf > DEFRESULT_MAX))
    {
        return E_INVALIDARG;
    }

    HRESULT hr = _DefStringResult_InitEmpty(pSelf, cchBuf);
    if (FAILED(hr))
    {
        return hr;
    }

    // NULL
    if (pInitStr == nullptr)
    {
        return S_OK;
    }

    // Not NULL
    hr = _DefStringCchCopy(pSelf->pBuf, pSelf->cchBuf, pInitStr);
    if (FAILED(hr))
    {
        DefStringResult_Clear(pSelf, FALSE);
        return hr;
    }

    return S_OK;
}

HRESULT
_DefStringResult_Swap(_Inout_ DEFSTRINGRESULT* pSelf, _Inout_ DEFSTRINGRESULT* pOther)
{
    CHECK_DEFSTRING(pSelf);
    CHECK_DEFSTRING(pOther);

    if (pSelf == pOther)
    {
        return S_OK;
    }

    DEFSTRINGRESULT temp;

    temp.cchBuf = pSelf->cchBuf;
    temp.pBuf = pSelf->pBuf;
    temp.pRef = pSelf->pRef;

    pSelf->cchBuf = pOther->cchBuf;
    pSelf->pBuf = pOther->pBuf;
    pSelf->pRef = pOther->pRef;

    pOther->cchBuf = temp.cchBuf;
    pOther->pBuf = temp.pBuf;
    pOther->pRef = temp.pRef;

    return S_OK;
}

HRESULT
DefStringResult_Concat(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr)
{
    CHECK_DEFSTRING(pSelf);

    if ((!pStr) || ((!pStr[0]) && (pSelf->pRef != nullptr)))
    {
        // Concatenating NULL succeeds but has no effect
        // Concatenting the empty string has no effect on any
        // string, but it turns an existing NULL into an
        // empty string.
        return S_OK;
    }

    // if we have a string already, get its length
    HRESULT hr = E_FAIL;
    size_t cchSelf = 0;
    size_t cchStr = 0;
    PWSTR pDest = nullptr;

    if (pSelf->pRef && pSelf->pRef[0])
    {
        size_t cchSelfMax = ((pSelf->pBuf == pSelf->pRef) ? pSelf->cchBuf : _DEF_STRSAFE_MAX_CCH);
        hr = _DefStringCchLength(pSelf->pRef, cchSelfMax, &cchSelf);
        if (FAILED(hr))
        {
            return hr;
        }
    }

    hr = _DefStringCchLength(pStr, _DEF_STRSAFE_MAX_CCH, &cchStr);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = _DefStringResult_EnsureBuffer(pSelf, cchSelf + cchStr + 1);
    if (FAILED(hr))
    {
        return hr;
    }

    pDest = &pSelf->pBuf[cchSelf];
    hr = _DefStringCchCopy(pDest, pSelf->cchBuf - cchSelf, pStr);
    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

HRESULT
DefStringResult_ConcatPathElement(_Inout_ DEFSTRINGRESULT* pSelf, _In_ PCWSTR pPathElem, _In_ WCHAR separator)
{
    CHECK_DEFSTRING(pSelf);

    if ((!pPathElem) || (!pPathElem[0]))
    {
        // concatenating empty string succeeds but has no effect
        return S_OK;
    }

    HRESULT hr = E_FAIL;
    size_t cchSelf = 0;
    size_t cchPathElem = 0;

    // if we have a string already, get its length
    if (pSelf->pRef && pSelf->pRef[0])
    {
        size_t cchSelfMax = ((pSelf->pBuf == pSelf->pRef) ? pSelf->cchBuf : _DEF_STRSAFE_MAX_CCH);
        hr = _DefStringCchLength(pSelf->pRef, cchSelfMax, &cchSelf);
        if (FAILED(hr))
        {
            return hr;
        }
    }

    hr = _DefStringCchLength(pPathElem, _DEF_STRSAFE_MAX_CCH, &cchPathElem);
    if (FAILED(hr))
    {
        return hr;
    }

    // Reserve space for existing path + slash + new path + NUL
    hr = _DefStringResult_EnsureBuffer(pSelf, cchSelf + cchPathElem + 2);
    if (FAILED(hr))
    {
        return hr;
    }
    __analysis_assume(pSelf->cchBuf >= cchSelf + cchPathElem + 2);

    // knock any trailing slashes off of the head and leading
    // slashes off of the tail
    while ((cchSelf > 0) && (pSelf->pBuf[cchSelf - 1] == separator))
    {
        cchSelf--;
    }

    while ((cchPathElem > 0) && (pPathElem[0] == separator))
    {
        pPathElem++;
        cchPathElem--;
    }

    // now insert a single slash if we aren't at the start of a string.
    if (cchSelf > 0)
    {
        pSelf->pBuf[cchSelf++] = separator;
    }

    // and copy the rest of the path element
    hr = _DefStringCchCopy(&pSelf->pBuf[cchSelf], pSelf->cchBuf - cchSelf, pPathElem);
    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

HRESULT
DefStringResult_IsAbsolutePath(_Inout_ const DEFSTRINGRESULT* pSelf, _In_ WCHAR separator, _Out_ __BOOL* absolutePath)
{
    CHECK_DEFSTRING(pSelf);

    *absolutePath = FALSE;

    if ((!pSelf->pRef) || (!pSelf->pRef[0]))
    {
        return S_OK;
    }

    if (pSelf->pRef[0] == separator)
    {
        *absolutePath = TRUE;
        return S_OK;
    }

    if ((pSelf->pRef[1] == ':') && (pSelf->pRef[2] == separator) && ((pSelf->pRef[0] < 256) && isalpha(pSelf->pRef[0] & 0xff)))
    {
        *absolutePath = TRUE;
        return S_OK;
    }

    return S_OK;
}

HRESULT
DefStringResult_Truncate(_Inout_ DEFSTRINGRESULT* pSelf, _In_ size_t size)
{
    CHECK_DEFSTRING(pSelf);

    HRESULT hr = 0;
    size_t cchSelf = 0;
    PCWSTR pOldRef = nullptr;
    size_t i;

    // if we have a string already, get its length
    if (pSelf->pRef && pSelf->pRef[0])
    {
        size_t cchSelfMax = ((pSelf->pBuf == pSelf->pRef) ? pSelf->cchBuf : _DEF_STRSAFE_MAX_CCH);
        hr = _DefStringCchLength(pSelf->pRef, cchSelfMax, &cchSelf);
        if (FAILED(hr))
        {
            return hr;
        }
    }

    if (size > cchSelf)
    {
        return E_INVALIDARG;
    }
    else if (size == cchSelf)
    {
        // Nothing to do!
        return S_OK;
    }

    __analysis_assume(size < pSelf->cchBuf);

    if (pSelf->pRef == pSelf->pBuf)
    {
        // we own the buffer.  just NUL terminate.
        pSelf->pBuf[size] = L'\0';
        return S_OK;
    }

    // Copy out the old value
    pOldRef = pSelf->pRef;
    pSelf->pRef = nullptr;

    // Ensure we have a private buffer the size we need
    hr = _DefStringResult_EnsureBuffer(pSelf, size + 1);
    if (FAILED(hr))
    {
        // failed!  put back the old value
        pSelf->pRef = pOldRef;
        return hr;
    }

    __analysis_assume(size < pSelf->cchBuf);
    // Now copy the as much as we want of the old
    for (i = 0; i < size; i++)
    {
        pSelf->pBuf[i] = pOldRef[i];
    }
    pSelf->pBuf[size] = L'\0';

    pSelf->pRef = pSelf->pBuf;
    return S_OK;
}

HRESULT
DefStringResult_Clear(_Inout_ DEFSTRINGRESULT* pSelf, _In_ __BOOL releaseBuffer)
{
    CHECK_DEFSTRING(pSelf);

    pSelf->pRef = nullptr;
    if (pSelf->pBuf && releaseBuffer)
    {
        _DefFree(pSelf->pBuf);
        pSelf->pBuf = nullptr;
        pSelf->cchBuf = 0;
    }

    return S_OK;
}

void DefStringResult_Delete(_In_ DEFSTRINGRESULT* pSelf)
{
    if (pSelf == nullptr)
    {
        return;
    }

    DefStringResult_Clear(pSelf, TRUE);
    _DefFree(pSelf);
}

HRESULT
DefStringResult_FindLastOf(_In_ const DEFSTRINGRESULT* pSelf, _In_ WCHAR charToFind, _Out_ __BOOL* found, _Out_ size_t* pCharPos)
{
    if (DefStringResult_IsInvalid(pSelf) || (found == nullptr) || (pCharPos == nullptr))
    {
        return E_INVALIDARG;
    }

    *found = FALSE;
    *pCharPos = 0;

    if ((!pSelf->pRef) || (!pSelf->pRef[0]))
    {
        return S_OK;
    }

    size_t cchLen = 0;
    HRESULT hr = DefStringResult_GetLength(pSelf, &cchLen);
    if (FAILED(hr))
    {
        return hr;
    }

    // DefStringResult_GetLength uses _DefStringCchLength which gives number of chars not including terminating NULL char.
    for (INT32 nLenItr = (INT32)(cchLen - 1); nLenItr >= 0; nLenItr--)
    {
#pragma prefast(suppress : 26018, "cchLen is constrained by nullpos but prefast can't detect that")
        if (pSelf->pRef[nLenItr] == charToFind)
        {
            *found = TRUE;
            *pCharPos = nLenItr;
            break;
        }
    }

    return S_OK;
}

HRESULT
DefStringResult_FindFirstOf(_In_ const DEFSTRINGRESULT* pSelf, _In_ WCHAR charToFind, _Out_ __BOOL* found, _Out_ size_t* pCharPos)
{
    if (DefStringResult_IsInvalid(pSelf) || (found == nullptr) || (pCharPos == nullptr))
    {
        return E_INVALIDARG;
    }

    *found = FALSE;
    *pCharPos = 0;

    if ((!pSelf->pRef) || (!pSelf->pRef[0]))
    {
        return S_OK;
    }

    size_t cchLen = 0;
    HRESULT hr = DefStringResult_GetLength(pSelf, &cchLen);
    if (FAILED(hr))
    {
        return hr;
    }

    // DefStringResult_GetLength uses _DefStringCchLength which gives
    // number of chars not including terminating NULL char.
    for (size_t cchLenItr = 0; cchLenItr < cchLen; cchLenItr++)
    {
#pragma prefast(suppress : 26018, "cchLenItr is constrained by nullpos but prefast can't detect that")
        if (pSelf->pRef[cchLenItr] == charToFind)
        {
            *found = TRUE;
            *pCharPos = cchLenItr;
            break;
        }
    }

    return S_OK;
}

HRESULT
DefStringResult_ReplaceAll(
    _In_ DEFSTRINGRESULT* pSelf,
    _In_ WCHAR charToFind,
    _In_ WCHAR charToReplaceWith,
    _Out_ size_t* pCharPosFirstReplace)
{
    if (DefStringResult_IsInvalid(pSelf) || (pCharPosFirstReplace == nullptr))
    {
        return E_INVALIDARG;
    }

    size_t cchLen = 0;
    __BOOL bReplaced = FALSE;
    __BOOL bHaveBuffer = FALSE;

    *pCharPosFirstReplace = 0;

    bHaveBuffer = (pSelf->pRef == pSelf->pBuf) ? TRUE : FALSE;
    HRESULT hr = DefStringResult_GetLength(pSelf, &cchLen);
    if (FAILED(hr))
    {
        return hr;
    }

    // DefStringResult_GetLength uses _DefStringCchLength which gives
    // number of chars not including terminating null char.
    for (size_t cchLenItr = 0; cchLenItr < cchLen; cchLenItr++)
    {
#pragma prefast(suppress : 26018, "cchLenItr is constrained by nullpos but prefast can't detect that")
        if (pSelf->pRef[cchLenItr] == charToFind)
        {
            if (!bHaveBuffer)
            {
                hr = _DefStringResult_EnsureBuffer(pSelf, 0);
                if (FAILED(hr))
                {
                    return hr;
                }
                bHaveBuffer = TRUE;
            }
            // EnsureBuffer above should have allocated pBuf if it was not present already.
            DEF_ASSERT(pSelf->pBuf == pSelf->pRef);
#pragma prefast(suppress : 26018, "cchLenItr is constrained by nullpos but prefast can't detect that")
            pSelf->pBuf[cchLenItr] = charToReplaceWith;
            if (!bReplaced)
            {
                *pCharPosFirstReplace = cchLenItr;
                bReplaced = TRUE;
            }
        }
    }

    return S_OK;
}

HRESULT
DefStringResult_SetCopyInteger(_In_ DEFSTRINGRESULT* pSelf, _In_ UINT32 nValue)
{
    CHECK_DEFSTRING(pSelf);

    UINT32 nValueMaxNumDigits = 0;
    errno_t err;

    if (nValue == 0)
    {
        return DefStringResult_SetCopy(pSelf, L"0");
    }

    // Max Number of Digits is calculated based on sizeof(UINT32)
    nValueMaxNumDigits = sizeof(UINT32) * 16;

    // Ensure buffer to copy
    HRESULT hr = _DefStringResult_EnsureEmptyBuffer(pSelf, nValueMaxNumDigits + 1);
    if (FAILED(hr))
    {
        return hr;
    }

#pragma prefast(suppress : 26018, "prefix doesn't detect that EnsureEmptyBuffer guarantees size of pSelf->pBuf")
    err = _ui64tow_s(nValue, pSelf->pBuf, nValueMaxNumDigits + 1, 10);
    hr = ErrnoToHResult(err);
    if (FAILED(hr))
    {
        return hr;
    }

    pSelf->pRef = pSelf->pBuf;
    return S_OK;
}

HRESULT
DefStringResult_Contains(_In_ const DEFSTRINGRESULT* pSelf, _In_ PCWSTR subStr, _Out_ __BOOL* result)
{
    *result = FALSE;

    HRESULT hr = 0;
    size_t cchSelf = 0;
    size_t cchSubStr = 0;

    if (pSelf->pRef == nullptr)
    {
        return S_OK;
    }

    // if we have a string already, get its length
    if (pSelf->pRef[0])
    {
        size_t cchSelfMax = ((pSelf->pBuf == pSelf->pRef) ? pSelf->cchBuf : _DEF_STRSAFE_MAX_CCH);
        hr = _DefStringCchLength(pSelf->pRef, cchSelfMax, &cchSelf);
        if (FAILED(hr))
        {
            return hr;
        }
    }

    hr = _DefStringCchLength(subStr, _DEF_STRSAFE_MAX_CCH, &cchSubStr);
    if (FAILED(hr))
    {
        return hr;
    }

    if (cchSubStr > cchSelf)
    {
        return S_OK;
    }

    __analysis_assume(cchSubStr < pSelf->cchBuf);

    PCWSTR comparisonSubStr = wcsstr(pSelf->pRef, subStr);
    if ((comparisonSubStr != nullptr) && (wcscmp(comparisonSubStr, subStr)))
    {
        *result = TRUE;
    }

    return S_OK;
}
