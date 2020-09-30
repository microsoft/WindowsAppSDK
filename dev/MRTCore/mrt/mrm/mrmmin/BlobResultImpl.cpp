// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "mrm/common/BaseInternal.h"
#include "blobresult.h"

static HRESULT _DefBlobResult_Alloc(_Outptr_ DEFBLOBRESULT** result)
{
    *result = _DefAllocZeroed(DEFBLOBRESULT);
    if (*result == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    return S_OK;
}

HRESULT
DefBlobResult_NewRef(_In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef, _Outptr_ DEFBLOBRESULT** result)
{
    *result = nullptr;

    DEFBLOBRESULT* pSelf;
    HRESULT hr = _DefBlobResult_Alloc(&pSelf);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = DefBlobResult_InitRef(pSelf, pRef, cbRef);
    if (FAILED(hr))
    {
        DefBlobResult_Delete(pSelf);
        return hr;
    }

    *result = pSelf;
    return S_OK;
}

HRESULT
DefBlobResult_NewBuf(_In_reads_bytes_opt_(cbBuf) const void* pBuf, _In_ size_t cbBuf, _Outptr_ DEFBLOBRESULT** result)
{
    *result = nullptr;

    DEFBLOBRESULT* pSelf;
    HRESULT hr = _DefBlobResult_Alloc(&pSelf);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = DefBlobResult_InitBuf(pSelf, pBuf, cbBuf);
    if (FAILED(hr))
    {
        DefBlobResult_Delete(pSelf);
        return hr;
    }

    *result = pSelf;
    return S_OK;
}

HRESULT
_DefBlobResult_InitEmpty(_Inout_ DEFBLOBRESULT* pSelf, _In_ size_t cbBuf)
{
    if ((pSelf == nullptr) || (cbBuf > DEFRESULT_MAX))
    {
        return E_INVALIDARG;
    }

    // Empty
    if (cbBuf == 0)
    {
        pSelf->pRef = pSelf->pBuf = nullptr;
        pSelf->cbRef = pSelf->cbBuf = 0;
        return S_OK;
    }

    // Not Empty
    void* pTempBuf = _DefArray_AllocZeroed(BYTE, cbBuf);
    if (pTempBuf == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    pSelf->pRef = pSelf->pBuf = pTempBuf;
    pSelf->cbRef = pSelf->cbBuf = (UINT32)cbBuf;
    return S_OK;
}

HRESULT
DefBlobResult_InitRef(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef)
{
    if (pSelf == nullptr)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = _DefBlobResult_InitEmpty(pSelf, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    pSelf->pRef = pRef;
    pSelf->cbRef = (UINT32)cbRef;
    return S_OK;
}

HRESULT
DefBlobResult_InitBuf(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbInitBuf) const void* pInitBuf, _In_ size_t cbInitBuf)
{
    if (pSelf == nullptr)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = _DefBlobResult_InitEmpty(pSelf, cbInitBuf);
    if (FAILED(hr))
    {
        return hr;
    }

    if ((pInitBuf != nullptr) && (cbInitBuf > 0))
    {
        // Fill with buffer
        errno_t err = memcpy_s(pSelf->pBuf, pSelf->cbBuf, pInitBuf, cbInitBuf);
        if (err != 0)
        {
            DefBlobResult_Clear(pSelf);
            return ErrnoToHResult(err);
        }
    }

    return S_OK;
}

void DefBlobResult_Clear(_Inout_ DEFBLOBRESULT* pSelf)
{
    if (pSelf == nullptr)
    {
        return;
    }

    if (pSelf->pRef == pSelf->pBuf)
    {
        pSelf->pRef = nullptr;
        pSelf->cbRef = 0;
    }

    if (pSelf->pBuf != nullptr)
    {
        _DefFree(pSelf->pBuf);
    }

    pSelf->pBuf = nullptr;
    pSelf->cbBuf = 0;
}

void DefBlobResult_Delete(_Inout_ DEFBLOBRESULT* pSelf)
{
    if (pSelf == nullptr)
    {
        return;
    }

    DefBlobResult_Clear(pSelf);
    _DefFree(pSelf);
}

_Success_(return != nullptr) _Check_return_ const void* DefBlobResult_GetRef(_In_ const DEFBLOBRESULT* pSelf, _Out_opt_ size_t* pcbRefOut)
{
    if (DefBlobResult_IsInvalid(pSelf))
    {
        return nullptr;
    }

    if (pcbRefOut)
    {
        *pcbRefOut = pSelf->cbRef;
    }

    return pSelf->pRef;
}

_Success_(return != nullptr) _Check_return_ void* DefBlobResult_GetWritableRef(_In_ DEFBLOBRESULT* pSelf, _Out_opt_ size_t* pcbRefOut)
{
    if (DefBlobResult_IsInvalid(pSelf))
    {
        return nullptr;
    }

    HRESULT hr = S_OK;
    if (DefBlobResult_GetType(pSelf) != DefResultType_Buffer)
    {
        DefBlobResult_Clear(pSelf);
        hr = DefBlobResult_InitBuf(pSelf, pSelf->pRef, pSelf->cbRef);
    }

    if (pcbRefOut && SUCCEEDED(hr))
    {
        *pcbRefOut = pSelf->cbRef;
    }

    return SUCCEEDED(hr) ? pSelf->pBuf : nullptr;
}

HRESULT
DefBlobResult_GetCopy(_In_ const DEFBLOBRESULT* pSelf, _Inout_ DEFBLOBRESULT* pResultOut)
{
    if (DefBlobResult_IsInvalid(pSelf) || (pResultOut == nullptr))
    {
        return E_INVALIDARG;
    }

    HRESULT hr = DefBlobResult_InitBuf(pResultOut, pSelf->pBuf, pSelf->cbBuf);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = DefBlobResult_InitRef(pResultOut, pSelf->pRef, pSelf->cbRef);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

size_t DefBlobResult_GetSize(_In_ const DEFBLOBRESULT* pSelf)
{
    if (pSelf == nullptr)
    {
        return 0;
    }

    return pSelf->cbRef;
}

// Internal _GetType used to avoid recursive loop in _Validate
static DEFRESULTTYPE _DefBlobResult_GetType(_In_ const DEFBLOBRESULT* pSelf)
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
DefBlobResult_GetType(_In_ const DEFBLOBRESULT* pSelf)
{
    if (DefBlobResult_IsInvalid(pSelf))
    {
        return DefResultType_None;
    }

    return _DefBlobResult_GetType(pSelf);
}

DEFCOMPARISON
DefBlobResult_Compare(_In_ const DEFBLOBRESULT* pSelf, _In_ const DEFBLOBRESULT* pOther)
{
    DEFCOMPARISON result;

    if ((pSelf == nullptr) || (pOther == nullptr))
    {
        return Def_CompareError;
    }

    if ((pSelf->pRef == nullptr) && (pOther->pRef == nullptr))
    {
        return Def_Equal;
    }
    if (pSelf->pRef == nullptr)
    {
        return Def_Less;
    }
    if (pOther->pRef == nullptr)
    {
        return Def_Greater;
    }

    result = DefBlob_Compare(pSelf->pRef, pOther->pRef, min(pSelf->cbRef, pOther->cbRef));
    if ((result != Def_Equal) || (pSelf->cbRef == pOther->cbRef))
    {
        return result;
    }
    else
    { // whichever is larger
        return (pSelf->cbRef > pOther->cbRef) ? Def_Greater : Def_Less;
    }
}

HRESULT
DefBlobResult_SetRef(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef)
{
    if (DefBlobResult_IsInvalid(pSelf))
    {
        return E_INVALIDARG;
    }

    pSelf->pRef = pRef;
    pSelf->cbRef = (UINT32)cbRef; //!< \todo safe UINT/size_t conversion
    return S_OK;
}

HRESULT
DefBlobResult_SetCopy(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef)
{
    errno_t err = 0;

    if (((pRef == nullptr) && (cbRef > 0)) || DefBlobResult_IsInvalid(pSelf))
    {
        return E_INVALIDARG;
    }

    if (pRef == nullptr)
    {
        // Release rather than clear on NULL because you can
        // easily clear by setting to an empty string
        DefBlobResult_Clear(pSelf);
    }
    else
    {
        // Not NULL
        if (cbRef > pSelf->cbBuf)
        {
            // Small Buf: Free and Init larger
            void* pTempBuf = pSelf->pBuf;
            HRESULT hr = _DefBlobResult_InitEmpty(pSelf, cbRef);
            if (FAILED(hr))
            {
                return hr;
            }

            if (pTempBuf != nullptr)
            {
                _DefFree(pTempBuf);
            }
        }

        err = memcpy_s(pSelf->pBuf, pSelf->cbBuf, pRef, cbRef);
        if (err != 0)
        {
            return ErrnoToHResult(err);
        }
    }

    pSelf->pRef = pSelf->pBuf;
    pSelf->cbRef = (UINT32)cbRef; //!< \todo safe UINT/size_t conversion
    return S_OK;
}

HRESULT
DefBlobResult_SetContents(_Inout_ DEFBLOBRESULT* pSelf, _Inout_updates_bytes_(cbBuffer) void* pBuffer, _In_ size_t cbBuffer)
{
    if (DefBlobResult_IsInvalid(pSelf) || (pBuffer == nullptr) || (cbBuffer == 0))
    {
        return E_INVALIDARG;
    }

    if ((DefBlobResult_GetType(pSelf) == DefResultType_Buffer) && (pSelf->pBuf != pBuffer))
    {
        DefBlobResult_Clear(pSelf);
    }

    //! \todo - 32/64 bit conversion
    pSelf->cbRef = pSelf->cbBuf = (UINT32)cbBuffer; //!< \todo safe UINT/size_t conversion
    pSelf->pRef = pSelf->pBuf = pBuffer;

    return S_OK;
}

HRESULT
DefBlobResult_SetEmptyContents(
    _Inout_ DEFBLOBRESULT* pSelf,
    _In_ size_t cbBufferMin,
    _Outptr_opt_result_bytebuffer_to_(*pcbBufferOut, cbBufferMin) void** buffer,
    _Out_opt_ size_t* pcbBufferOut)
{
    if (buffer != nullptr)
    {
        *buffer = nullptr;
    }

    if (DefBlobResult_IsInvalid(pSelf) || (cbBufferMin == 0))
    {
        return E_INVALIDARG;
    }

    if (pSelf->pBuf && (pSelf->cbBuf < cbBufferMin))
    {
        DefBlobResult_Clear(pSelf);
    }

    if (!pSelf->pBuf)
    {
        pSelf->pBuf = Def_Alloc(cbBufferMin);
        if (pSelf->pBuf == nullptr)
        {
            return E_OUTOFMEMORY;
        }
        pSelf->cbBuf = (UINT32)cbBufferMin;
    }

    pSelf->pRef = pSelf->pBuf;
    pSelf->cbRef = pSelf->cbBuf;
    if (pcbBufferOut)
    {
        *pcbBufferOut = pSelf->cbBuf;
    }

    if (buffer != nullptr)
    {
        *buffer = pSelf->pBuf;
    }
    return S_OK;
}

HRESULT
DefBlobResult_ReleaseContents(
    _Inout_ DEFBLOBRESULT* pSelf,
    _Outptr_result_bytebuffer_(*pcbBufferOut) void** ppBufferOut,
    _Out_ size_t* pcbBufferOut)
{
    if ((ppBufferOut == nullptr) || (pcbBufferOut == nullptr) || DefBlobResult_IsInvalid(pSelf) || (pSelf->pBuf == nullptr) ||
        (pSelf->cbBuf == 0))
    {
        return E_INVALIDARG;
    }

    *ppBufferOut = pSelf->pBuf;
    *pcbBufferOut = pSelf->cbBuf;

    HRESULT hr = _DefBlobResult_InitEmpty(pSelf, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}
