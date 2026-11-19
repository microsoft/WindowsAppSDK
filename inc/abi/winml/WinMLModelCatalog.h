// Copyright (C) Microsoft Corporation. All rights reserved.
#pragma once

#include "WinMLAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WinMLModelCatalogSource* WinMLModelCatalogSourceHandle;
typedef struct WinMLModelCatalog* WinMLModelCatalogHandle;
typedef struct WinMLCatalogModelInfo* WinMLCatalogModelInfoHandle;
typedef struct WinMLCatalogModelInstance* WinMLCatalogModelInstanceHandle;

typedef enum WinMLCatalogModelInstanceStatus
{
    WinMLCatalogModelInstanceStatus_Available = 0,
    WinMLCatalogModelInstanceStatus_InProgress = 1,
    WinMLCatalogModelInstanceStatus_Unavailable = 2
} WinMLCatalogModelInstanceStatus;

typedef enum WinMLCatalogModelStatus
{
    WinMLCatalogModelStatus_Ready = 0,
    WinMLCatalogModelStatus_NotReady = 1
} WinMLCatalogModelStatus;

typedef struct WinMLCatalogModelInstanceResult
{
    WinMLCatalogModelInstanceStatus status;
    HRESULT extendedError;
    WinMLCatalogModelInstanceHandle instance;
} WinMLCatalogModelInstanceResult;

typedef BOOL (CALLBACK* WinMLCatalogModelInfoEnumCallback)(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _In_opt_ void* context
);

STDAPI WinMLModelCatalogSourceCreateFromUri(
    _In_z_ const char* uri,
    _Out_ WinMLModelCatalogSourceHandle* source
);

STDAPI WinMLModelCatalogSourceCreateFromUriAsync(
    _In_z_ const char* uri,
    _Inout_ WinMLAsyncBlock* async
);

STDAPI WinMLModelCatalogSourceCreateFromUriWithHeaders(
    _In_z_ const char* uri,
    _In_ size_t headerCount,
    _In_reads_(headerCount) const char* const* headerKeys,
    _In_reads_(headerCount) const char* const* headerValues,
    _Out_ WinMLModelCatalogSourceHandle* source
);

STDAPI WinMLModelCatalogSourceCreateFromUriWithHeadersAsync(
    _In_z_ const char* uri,
    _In_ size_t headerCount,
    _In_reads_(headerCount) const char* const* headerKeys,
    _In_reads_(headerCount) const char* const* headerValues,
    _Inout_ WinMLAsyncBlock* async
);

STDAPI WinMLModelCatalogSourceGetResult(
    _In_ WinMLAsyncBlock* async,
    _Out_ WinMLModelCatalogSourceHandle* source
);

STDAPI_(void) WinMLModelCatalogSourceRelease(
    _In_opt_ WinMLModelCatalogSourceHandle source
);

STDAPI WinMLModelCatalogSourceGetIdSize(
    _In_ WinMLModelCatalogSourceHandle source,
    _Out_ size_t* size
);

STDAPI WinMLModelCatalogSourceGetId(
    _In_ WinMLModelCatalogSourceHandle source,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLModelCatalogSourceGetUriSize(
    _In_ WinMLModelCatalogSourceHandle source,
    _Out_ size_t* size
);

STDAPI WinMLModelCatalogSourceGetUri(
    _In_ WinMLModelCatalogSourceHandle source,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLModelCatalogCreate(
    _In_ size_t sourceCount,
    _In_reads_(sourceCount) const WinMLModelCatalogSourceHandle* sources,
    _Out_ WinMLModelCatalogHandle* catalog
);

STDAPI_(void) WinMLModelCatalogRelease(
    _In_opt_ WinMLModelCatalogHandle catalog
);

STDAPI WinMLModelCatalogEnumExecutionProviders(
    _In_ WinMLModelCatalogHandle catalog,
    _In_ WinMLStringEnumCallback callback,
    _In_opt_ void* context
);

STDAPI WinMLModelCatalogSetExecutionProviders(
    _In_ WinMLModelCatalogHandle catalog,
    _In_ size_t count,
    _In_reads_(count) const char* const* executionProviders
);

STDAPI WinMLModelCatalogGetAvailableModel(
    _In_ WinMLModelCatalogHandle catalog,
    _In_z_ const char* idOrName,
    _Out_ WinMLCatalogModelInfoHandle* modelInfo
);

STDAPI WinMLModelCatalogGetAvailableModels(
    _In_ WinMLModelCatalogHandle catalog,
    _In_ WinMLCatalogModelInfoEnumCallback callback,
    _In_opt_ void* context
);

STDAPI WinMLModelCatalogFindModel(
    _In_ WinMLModelCatalogHandle catalog,
    _In_z_ const char* idOrName,
    _Out_ WinMLCatalogModelInfoHandle* modelInfo
);

STDAPI WinMLModelCatalogFindModelAsync(
    _In_ WinMLModelCatalogHandle catalog,
    _In_z_ const char* idOrName,
    _Inout_ WinMLAsyncBlock* async
);

STDAPI WinMLModelCatalogFindAllModels(
    _In_ WinMLModelCatalogHandle catalog,
    _In_ WinMLCatalogModelInfoEnumCallback callback,
    _In_opt_ void* context
);

STDAPI WinMLModelCatalogFindAllModelsAsync(
    _In_ WinMLModelCatalogHandle catalog,
    _Inout_ WinMLAsyncBlock* async
);

STDAPI WinMLModelCatalogFindModelGetResult(
    _In_ WinMLAsyncBlock* async,
    _Out_ WinMLCatalogModelInfoHandle* modelInfo
);

STDAPI WinMLModelCatalogFindAllModelsGetResult(
    _In_ WinMLAsyncBlock* async,
    _In_ WinMLCatalogModelInfoEnumCallback callback,
    _In_opt_ void* context
);

STDAPI_(void) WinMLCatalogModelInfoRelease(
    _In_opt_ WinMLCatalogModelInfoHandle modelInfo
);

STDAPI WinMLCatalogModelInfoGetIdSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetId(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetNameSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetName(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetPublisherSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetPublisher(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetSourceIdSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetSourceId(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetVersionSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetVersion(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetLicenseSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetLicense(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetLicenseUriSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetLicenseUri(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetLicenseTextSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetLicenseText(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetUriSize(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ size_t* size
);

STDAPI WinMLCatalogModelInfoGetUri(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLCatalogModelInfoGetModelSizeInBytes(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ UINT64* size
);

STDAPI WinMLCatalogModelInfoEnumExecutionProviders(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _In_ WinMLStringEnumCallback callback,
    _In_opt_ void* context
);

STDAPI WinMLCatalogModelInfoGetStatus(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Out_ WinMLCatalogModelStatus* status
);

STDAPI WinMLCatalogModelInfoGetInstanceAsync(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _Inout_ WinMLAsyncBlock* async
);

STDAPI WinMLCatalogModelInfoGetInstanceWithHeadersAsync(
    _In_ WinMLCatalogModelInfoHandle modelInfo,
    _In_ size_t headerCount,
    _In_reads_(headerCount) const char* const* headerKeys,
    _In_reads_(headerCount) const char* const* headerValues,
    _Inout_ WinMLAsyncBlock* async
);

STDAPI WinMLCatalogModelInfoGetInstanceResult(
    _In_ WinMLAsyncBlock* async,
    _Out_ WinMLCatalogModelInstanceResult* result
);

STDAPI_(void) WinMLCatalogModelInstanceRelease(
    _In_opt_ WinMLCatalogModelInstanceHandle instance
);

STDAPI WinMLCatalogModelInstanceEnumModelPaths(
    _In_ WinMLCatalogModelInstanceHandle instance,
    _In_ WinMLStringEnumCallback callback,
    _In_opt_ void* context
);

STDAPI WinMLCatalogModelInstanceGetModelInfo(
    _In_ WinMLCatalogModelInstanceHandle instance,
    _Out_ WinMLCatalogModelInfoHandle* modelInfo
);

STDAPI WinMLCatalogModelInstanceClose(
    _In_ WinMLCatalogModelInstanceHandle instance
);

#ifdef __cplusplus
}
#endif
