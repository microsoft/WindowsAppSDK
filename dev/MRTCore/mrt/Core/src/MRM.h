// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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

    STDAPI_(void*) MrmAllocateBuffer(size_t size);
    STDAPI_(void) MrmFreeResource(_In_opt_ void* resource);

    STDAPI MrmGetFilePathFromName(_In_ PCWSTR filename, _Outptr_ PWSTR* filePath);

#ifdef __cplusplus
}
#endif
