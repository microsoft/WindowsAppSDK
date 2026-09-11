// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    DECLARE_HANDLE(MrmManagerHandle);
    DECLARE_HANDLE(MrmContextHandle);
    DECLARE_HANDLE(MrmMapHandle);

    enum MrmType
    {
        MrmType_Unknown,
        MrmType_String,
        MrmType_Path,
        MrmType_Embedded
    };

    struct MrmResourceData
    {
        UINT32 size;
        void* data;
    };

    // Versioned extension of MrmResourceData used by the *NoCopy loader variants. MrmResourceData
    // itself is a frozen public ABI and must never grow, so the additional 'isView' state lives on
    // this separate struct. The leading 'size'/'data' members intentionally mirror MrmResourceData
    // in the same order so the two remain layout-compatible. Only the *NoCopy exports (and
    // MrmFreeResourceData) read or write this type, so no legacy caller ever sees the larger size.
    struct MrmResourceData2
    {
        UINT32 size;
        void* data;

        // When TRUE, 'data' is a non-owning view directly into the memory-mapped, read-only PRI
        // owned by the resource manager. In that case the caller must keep the resource manager
        // alive for as long as 'data' is used, and must NOT free 'data' (MrmFreeResourceData is a
        // no-op for views). When FALSE (the default for zero-initialized instances) 'data' is a heap
        // allocation owned by the caller, freed via MrmFreeResourceData.
        BOOL isView;
    };

    STDAPI MrmCreateResourceManager(_In_ PCWSTR priFileName, _Out_ MrmManagerHandle* resourceManager);
    STDAPI_(void) MrmDestroyResourceManager(_In_opt_ MrmManagerHandle resourceManager);

    STDAPI MrmCreateResourceContext(_In_ MrmManagerHandle resourceManager, _Out_ MrmContextHandle* resourceContext);
    STDAPI_(void) MrmFreeQualifierNamesOrValues(UINT32 size, _In_reads_(size) PWSTR* names);
    STDAPI MrmGetAllQualifierNames(_In_ MrmContextHandle resourceContext, _Out_ UINT32* size, _Outptr_result_buffer_(*size) PWSTR** names);
    STDAPI MrmGetQualifier(_In_ MrmContextHandle resourceContext, _In_ PCWSTR qualifierName, _Outptr_ PWSTR* qualifierValue);
    STDAPI MrmSetQualifier(_In_ MrmContextHandle resourceContext, _In_ PCWSTR qualifierName, _In_ PCWSTR qualifierValue);
    STDAPI_(void) MrmDestroyResourceContext(_In_opt_ MrmContextHandle resourceContext);

    // Resource maps are owned by the resource manager and so do not need to be destroyed.
    STDAPI MrmGetChildResourceMap(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR childResourceMapName,
        _Out_ MrmMapHandle* childResourceMap);

    STDAPI MrmGetResourceCount(_In_ MrmManagerHandle resourceManager, _In_opt_ MrmMapHandle resourceMap, _Out_ UINT32* count);

    STDAPI MrmLoadStringResource(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR resourceId,
        _Outptr_ PWSTR* resourceString);

    STDAPI MrmLoadStringResourceFromResourceUri(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_ PCWSTR resourceUri,
        _Outptr_ PWSTR* resourceString);

    STDAPI MrmLoadEmbeddedResource(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR resourceId,
        _Out_ MrmResourceData* data);

    STDAPI MrmLoadEmbeddedResourceFromResourceUri(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_ PCWSTR resourceUri,
        _Out_ MrmResourceData* data);

    STDAPI MrmLoadStringOrEmbeddedResource(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR resourceId,
        _Out_ MrmType* resourceType,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData* data);

    STDAPI MrmLoadStringOrEmbeddedResourceWithQualifierValues(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR resourceId,
        _Out_ MrmType* resourceType,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData* data,
        _Out_ UINT32* qualifierCount, 
        _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
        _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierValues);

    STDAPI MrmLoadStringOrEmbeddedFromResourceUri(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_ PCWSTR resourceUri,
        _Out_ MrmType* resourceType,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData* data);

    STDAPI MrmLoadStringOrEmbeddedResourceByIndex(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        UINT32 index,
        _Out_ MrmType* resourceType,
        _Outptr_ PWSTR* resourceName,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData* data);

    STDAPI MrmLoadStringOrEmbeddedResourceByIndexWithQualifierValues(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        UINT32 index,
        _Out_ MrmType* resourceType,
        _Outptr_ PWSTR* resourceName,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData* data,
        _Out_ UINT32* qualifierCount, 
        _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
        _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierValues);

    // No-copy loader variants. For embedded/binary resources these publish a non-owning view
    // (MrmResourceData2::isView == TRUE) directly into the memory-mapped PRI instead of allocating
    // and copying a private heap buffer. The caller must keep 'resourceManager' alive while the
    // returned view is in use and must free the result with MrmFreeResourceData (which is a no-op
    // for views). String/path resources are unaffected and behave exactly as the copying variants.
    STDAPI MrmLoadStringOrEmbeddedResourceNoCopy(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR resourceId,
        _Out_ MrmType* resourceType,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData2* data);

    STDAPI MrmLoadStringOrEmbeddedResourceByIndexNoCopy(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        UINT32 index,
        _Out_ MrmType* resourceType,
        _Outptr_ PWSTR* resourceName,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData2* data);

    STDAPI_(void*) MrmAllocateBuffer(size_t size);
    STDAPI_(void) MrmFreeResource(_In_opt_ void* resource);

    // Frees an MrmResourceData2 produced by a *NoCopy loader. Safe for both owned buffers (frees
    // 'data') and views (no-op). Must be used to free results of the *NoCopy variants.
    STDAPI_(void) MrmFreeResourceData(_Inout_opt_ MrmResourceData2* data);

    STDAPI MrmGetFilePathFromName(_In_opt_ PCWSTR filename, _Outptr_ PWSTR* filePath);

#ifdef __cplusplus
}
#endif
