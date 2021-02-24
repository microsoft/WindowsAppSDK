// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include "BlobResult.h"

namespace Microsoft::Resources
{

_Use_decl_annotations_ HRESULT BlobResult::NewRef(const void* pRef, size_t cbRef, BlobResult** result)
{
    *result = nullptr;

    BlobResult* pSelf = new BlobResult();
    RETURN_IF_NULL_ALLOC(pSelf);

    HRESULT hr = DefBlobResult_InitRef(pSelf->GetBlobResult(), pRef, cbRef);
    if (FAILED(hr))
    {
        delete pSelf;
        return hr;
    }

    *result = pSelf;

    return S_OK;
}

_Use_decl_annotations_ HRESULT BlobResult::NewBuf(const void* pBuf, size_t cbBuf, BlobResult** result)
{
    *result = nullptr;

    BlobResult* pSelf = new BlobResult();
    RETURN_IF_NULL_ALLOC(pSelf);

    HRESULT hr = DefBlobResult_InitBuf(pSelf->GetBlobResult(), pBuf, cbBuf);
    if (FAILED(hr))
    {
        delete pSelf;
        return hr;
    }

    *result = pSelf;

    return S_OK;
}

BlobResult::BlobResult()
{
    m_blobResult.cbBuf = 0;
    m_blobResult.pBuf = NULL;
    m_blobResult.cbRef = 0;
    m_blobResult.pRef = NULL;
}

BlobResult::~BlobResult() { DefBlobResult_Clear(&m_blobResult); }

_Use_decl_annotations_ const void* BlobResult::GetRef(size_t* pcbRefOut) const { return DefBlobResult_GetRef(&m_blobResult, pcbRefOut); }

_Use_decl_annotations_ void* BlobResult::GetWritableRef(size_t* pcbRefOut)
{
    return DefBlobResult_GetWritableRef(&m_blobResult, pcbRefOut);
}

size_t BlobResult::GetSize() const { return DefBlobResult_GetSize(&m_blobResult); }

DEFRESULTTYPE BlobResult::GetType() const { return DefBlobResult_GetType(&m_blobResult); }

DEFBLOBRESULT* BlobResult::GetBlobResult() { return &m_blobResult; }

const DEFBLOBRESULT* BlobResult::GetBlobResult() const { return &m_blobResult; }

_Use_decl_annotations_ DEFCOMPARISON BlobResult::Compare(const BlobResult* pOther) const
{
    if (pOther == nullptr)
    {
        return Def_CompareError;
    }

    return DefBlobResult_Compare(&m_blobResult, pOther->GetBlobResult());
}

_Use_decl_annotations_ HRESULT BlobResult::SetRef(const void* pRef, size_t cbRef)
{
    return DefBlobResult_SetRef(&m_blobResult, pRef, cbRef);
}
_Use_decl_annotations_ HRESULT BlobResult::SetCopy(const void* pBuf, size_t cbBuf)
{
    return DefBlobResult_SetCopy(&m_blobResult, pBuf, cbBuf);
}
_Use_decl_annotations_ HRESULT BlobResult::SetContents(void* pBuffer, size_t cbBuffer)
{
    return DefBlobResult_SetContents(&m_blobResult, pBuffer, cbBuffer);
}

_Use_decl_annotations_ HRESULT BlobResult::SetEmptyContents(size_t cchBufferMin, void** buffer, size_t* pcbBufferOut)
{
    return DefBlobResult_SetEmptyContents(&m_blobResult, cchBufferMin, buffer, pcbBufferOut);
}

_Use_decl_annotations_ HRESULT BlobResult::ReleaseContents(void** ppBufferOut, size_t* pcbBufferOut)
{
    return DefBlobResult_ReleaseContents(&m_blobResult, ppBufferOut, pcbBufferOut);
}

_Use_decl_annotations_ HRESULT BlobResult::CopyToOutParams(size_t cbBuffer, void* pBuffer, size_t* pcbWritten)
{
    if (pcbWritten != nullptr)
    {
        *pcbWritten = m_blobResult.cbRef;
    }

    if ((cbBuffer >= m_blobResult.cbRef) && (pBuffer != nullptr))
    {
        CopyMemory(pBuffer, m_blobResult.pRef, m_blobResult.cbRef);
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
    }

    return S_OK;
}

} // namespace Microsoft::Resources
