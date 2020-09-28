// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/readers/MrmReaders.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // In-memory representation of a reference blob

    typedef struct
    {
        UINT16 flags;
        UINT16 cbTotal;
        UINT16 cchOriginName;
        UINT16 cbPayload;
    } MRM_REFERENCE_BLOB;

#ifdef __cplusplus
}
#endif

namespace Microsoft::Resources
{

class ResourceReference
{
public:
    static const UINT16 fMrmRefType_UnspecifiedOrigin = 0x0000; // No context (payload self-contained or context implied)
    static const UINT16 fMrmRefType_FileOrigin = 0x0001; // origin is a PRI file
    static const UINT16 fMrmRefType_PackageOrigin = 0x0002; // origin is an AppX package
    static const UINT16 fMrmRefType_ValidOriginFlags = (fMrmRefType_FileOrigin | fMrmRefType_PackageOrigin);

    static const UINT16 fMrmRefPayload_Literal = 0x0100; // payload is a literal
    static const UINT16 fMrmRefPayload_ResourceName = 0x0200; // payload is a resource name
    static const UINT16 fMrmRefPayload_ResourceIndex = 0x0400; // payload is a resource index
    static const UINT16 fMrmRefPayload_ValidPayloadFlags =
        (fMrmRefPayload_Literal | fMrmRefPayload_ResourceName | fMrmRefPayload_ResourceIndex);

    static const UINT16 kMaxBlobSizeInBytes = 8192;

    ResourceReference() : m_cbBlob(0), m_pHeader(nullptr), m_pOrigin(nullptr), m_pPayload(nullptr) {}

    _Success_(return ) HRESULT Set(_In_ size_t cbBlob, _In_reads_bytes_(cbBlob) const void* pBlob);

    static bool HasOrigin(_In_ UINT16 flags) { return ((flags & (fMrmRefType_FileOrigin | fMrmRefType_PackageOrigin)) != 0); }

    bool HasOrigin() const { return (m_pHeader && ((m_pHeader->flags & (fMrmRefType_FileOrigin | fMrmRefType_PackageOrigin)) != 0)); }

    bool OriginIsFile() const { return (m_pHeader && ((m_pHeader->flags & fMrmRefType_FileOrigin) != 0)); }

    bool OriginIsPackage() const { return (m_pHeader && ((m_pHeader->flags & fMrmRefType_PackageOrigin) != 0)); }

    PCWSTR GetOrigin() const { return m_pOrigin; }

    bool PayloadIsLiteral() const { return m_pHeader && ((m_pHeader->flags & fMrmRefPayload_Literal) != 0); }

    bool PayloadIsResourceName() const { return m_pHeader && ((m_pHeader->flags & fMrmRefPayload_ResourceName) != 0); }

    bool PayloadIsResourceIndex() const { return m_pHeader && ((m_pHeader->flags & fMrmRefPayload_ResourceIndex) != 0); }

    _Success_(return ) _Check_return_ HRESULT GetPayload(_Inout_ BlobResult* pBlobResult) const
    {
        return ((m_pHeader && m_pPayload) ? (pBlobResult->SetRef(m_pPayload, m_pHeader->cbPayload)) : (pBlobResult->SetRef(nullptr, 0)));
    }

    const MRM_REFERENCE_BLOB* GetHeader() const { return m_pHeader; }

    /*! 
     * Resolves a reference as a string.  The manager and context are not required for some kinds of 
     * references, so they're optional.
     *
     * Initializing a manager is expensive and often unnecessary, so callers who don't already resources
     * loaded should initialize lazily:  If a call to this method with null pManager/pContext fails with
     * E_MRM_MANAGER_REQUIRED, create a resource manager and repeat the call.
     */
    _Success_(return ) _Check_return_ HRESULT
        ResolveAsString(_In_opt_ IUnifiedResourceView* pManager, _In_opt_ IResolver* pContext, _Inout_ StringResult* pStringOut) const;

protected:
    HRESULT ValidateReferenceBlob();

    size_t m_cbBlob;
    const MRM_REFERENCE_BLOB* m_pHeader;
    PCWSTR m_pOrigin;
    const BYTE* m_pPayload;
};

class ReferenceBuilder
{
public:
    /*! 
     * Gets a blob that refers to a literal string.
     */
    _Success_(return ) static inline HRESULT GetLiteralBlob(_In_ PCWSTR pszLiteral, _Inout_ BlobResult* pBlobOut)
    {
        return BuildReferenceBlob(
            ResourceReference::fMrmRefType_UnspecifiedOrigin | ResourceReference::fMrmRefPayload_Literal,
            NULL,
            (wcslen(pszLiteral) + 1) * sizeof(WCHAR),
            pszLiteral,
            pBlobOut);
    }

    /*!
     * Gets a blob that can be used to refer to a resource from within or outside of an application
    */

    typedef enum
    {
        ExternalReference = 0,
        InternalReference = 1
    } ReferenceBlobUsage;

    _Success_(return ) static HRESULT GetExternalReferenceBlob(
        _In_ UINT16 originFlags,
        _In_ PCWSTR pOrigin,
        _In_ const NamedResourceResult* pResource,
        _Inout_ BlobResult* pBlobOut);

    _Success_(return ) static HRESULT GetInternalReferenceBlob(_In_ const NamedResourceResult* pResource, _Inout_ BlobResult* pBlobOut);

protected:
    _Success_(return ) _Check_return_
        static bool TryGetOnlyValue(_In_ const NamedResourceResult* pResource, _Inout_ StringResult* pValueOut);

    // lays out a blob in memory
    _Success_(return ) static HRESULT BuildReferenceBlob(
        _In_ UINT16 flags,
        _In_opt_ PCWSTR pszOrigin,
        _In_ size_t cbPayload,
        _In_reads_bytes_opt_(cbPayload) const VOID* pPayload,
        _Inout_ BlobResult* pBlobOut);

    _Success_(return ) static inline HRESULT BuildResourceReferenceBlob(
        _In_ UINT16 fileOrPackage,
        _In_ PCWSTR pszOrigin,
        _In_ PCWSTR pszResourceName,
        _Inout_ BlobResult* pBlobOut)
    {
        return BuildReferenceBlob(
            fileOrPackage | ResourceReference::fMrmRefPayload_ResourceName,
            pszOrigin,
            (wcslen(pszResourceName) + 1) * sizeof(WCHAR),
            pszResourceName,
            pBlobOut);
    }
};

} // namespace Microsoft::Resources