// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

HRESULT DefBlobResult_NewRef(_In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef, _Outptr_ DEFBLOBRESULT** result);

HRESULT DefBlobResult_NewBuf(_In_reads_bytes_opt_(cbBuf) const void* pBuf, _In_ size_t cbBuf, _Outptr_ DEFBLOBRESULT** result);

HRESULT DefBlobResult_InitRef(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef);

HRESULT DefBlobResult_InitBuf(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbInitBuf) const void* pInitBuf, _In_ size_t cbInitBuf);

HRESULT DefBlobResult_GetCopy(_In_ const DEFBLOBRESULT* pSelf, _Inout_ DEFBLOBRESULT* pResultOut);

void DefBlobResult_Clear(_Inout_ DEFBLOBRESULT* pSelf);

void DefBlobResult_Delete(_Inout_ DEFBLOBRESULT* pSelf);

_Success_(return != nullptr) _Check_return_ const void* DefBlobResult_GetRef(_In_ const DEFBLOBRESULT* pSelf, _Out_opt_ size_t* pcbRefOut);

_Success_(return != nullptr) _Check_return_ void* DefBlobResult_GetWritableRef(_In_ DEFBLOBRESULT* pSelf, _Out_opt_ size_t* pcbRefOut);

size_t DefBlobResult_GetSize(_In_ const DEFBLOBRESULT* pSelf);

DEFRESULTTYPE DefBlobResult_GetType(_In_ const DEFBLOBRESULT* pSelf);

DEFCOMPARISON DefBlobResult_Compare(_In_ const DEFBLOBRESULT* pSelf, _In_ const DEFBLOBRESULT* pOther);

HRESULT DefBlobResult_SetRef(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef);

HRESULT DefBlobResult_SetCopy(_Inout_ DEFBLOBRESULT* pSelf, _In_reads_bytes_opt_(cbRef) const void* pRef, _In_ size_t cbRef);

HRESULT DefBlobResult_SetContents(_Inout_ DEFBLOBRESULT* pSelf, _Inout_updates_bytes_(cbBuffer) void* pBuffer, _In_ size_t cbBuffer);

HRESULT DefBlobResult_SetEmptyContents(
    _Inout_ DEFBLOBRESULT* pSelf,
    _In_ size_t cbBufferMin,
    _Outptr_opt_result_bytebuffer_to_(*pcbBufferOut, cbBufferMin) void** buffer,
    _Out_opt_ size_t* pcbBufferOut);

HRESULT DefBlobResult_ReleaseContents(
    _Inout_ DEFBLOBRESULT* pSelf,
    _Outptr_result_bytebuffer_(*pcbBufferOut) void** ppBufferOut,
    _Out_ size_t* pcbBufferOut);

#define DefBlobResult_IsInvalid(SELF) \
    (((SELF) == NULL) || (((SELF)->pRef == (SELF)->pBuf) && \
                          (((((SELF)->pBuf == NULL) && ((SELF)->cbBuf > 0)) || (((SELF)->cbBuf == 0) && ((SELF)->pBuf != NULL))) || \
                           ((SELF)->cbBuf > DEFRESULT_MAX))))
