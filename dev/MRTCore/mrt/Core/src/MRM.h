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

    // Versioned extension of MrmResourceData used by the *AsView loader variants. MrmResourceData
    // itself is a frozen public ABI and must never grow, so the additional 'isView' state lives on
    // this separate struct. The leading 'size'/'data' members intentionally mirror MrmResourceData
    // in the same order so the two remain layout-compatible. Only the *AsView exports (and
    // MrmFreeResourceData) read or write this type, so no legacy caller ever sees the larger size.
    struct MrmResourceData2
    {
        UINT32 size;
        void* data;

        // When nonzero, 'data' is a non-owning view directly into the memory-mapped, read-only PRI
        // owned by the resource manager. When zero, 'data' is a heap allocation owned by the caller.
        // In both cases the caller must pass this descriptor to MrmFreeResourceData when done. For
        // a view, the caller must also keep the resource manager alive for as long as 'data' is used.
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

    // View-aware loader variants. For embedded/binary resources these may publish a non-owning view
    // directly into the memory-mapped PRI instead of allocating and copying a private heap buffer.
    // The caller must always release the result with MrmFreeResourceData. If 'isView' is nonzero,
    // the caller must keep the required 'resourceManager' argument alive while using 'data'.
    // String/path resources are unaffected and behave exactly as the existing loader variants.
    STDAPI MrmLoadStringOrEmbeddedResourceAsView(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR resourceId,
        _Out_ MrmType* resourceType,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData2* data);

    STDAPI MrmLoadStringOrEmbeddedResourceByIndexAsView(
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

    // Releases an MrmResourceData2 produced by an *AsView loader and clears the descriptor. This
    // must be called after every successful load; it frees owned buffers and safely releases views.
    STDAPI_(void) MrmFreeResourceData(_Inout_opt_ MrmResourceData2* data);

    STDAPI MrmGetFilePathFromName(_In_opt_ PCWSTR filename, _Outptr_ PWSTR* filePath);

#ifdef __cplusplus
}
#endif
