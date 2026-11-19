// Copyright (C) Microsoft Corporation. All rights reserved.
#pragma once

#include "WinMLAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WinMLEpCatalog* WinMLEpCatalogHandle;
typedef struct WinMLEp* WinMLEpHandle;

typedef enum WinMLEpReadyState
{
    WinMLEpReadyState_Ready = 0,
    WinMLEpReadyState_NotReady = 1,
    WinMLEpReadyState_NotPresent = 2
} WinMLEpReadyState;

typedef enum WinMLEpCertification
{
    WinMLEpCertification_Unknown = 0,
    WinMLEpCertification_Certified = 1,
    WinMLEpCertification_Uncertified = 2
} WinMLEpCertification;

typedef struct WinMLEpInfo
{
    const char* name;
    const char* version;
    const char* packageFamilyName;
    const char* libraryPath;
    const char* packageRootPath;
    WinMLEpReadyState readyState;
    WinMLEpCertification certification;
} WinMLEpInfo;

typedef BOOL (CALLBACK* WinMLEpEnumCallback)(
    _In_ WinMLEpHandle ep,
    _In_ const WinMLEpInfo* info,
    _In_opt_ void* context
);

STDAPI WinMLEpCatalogCreate(
    _Out_ WinMLEpCatalogHandle* catalog
);

STDAPI_(void) WinMLEpCatalogRelease(
    _In_opt_ WinMLEpCatalogHandle catalog
);

STDAPI WinMLEpCatalogEnumProviders(
    _In_ WinMLEpCatalogHandle catalog,
    _In_ WinMLEpEnumCallback callback,
    _In_opt_ void* context
);

STDAPI WinMLEpCatalogFindProvider(
    _In_ WinMLEpCatalogHandle catalog,
    _In_z_ const char* providerName,
    _In_opt_z_ const char* packageFamilyName,
    _Out_ WinMLEpHandle* ep
);

STDAPI WinMLEpGetNameSize(
    _In_ WinMLEpHandle ep,
    _Out_ size_t* size
);

STDAPI WinMLEpGetName(
    _In_ WinMLEpHandle ep,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLEpGetVersionSize(
    _In_ WinMLEpHandle ep,
    _Out_ size_t* size
);

STDAPI WinMLEpGetVersion(
    _In_ WinMLEpHandle ep,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLEpGetPackageFamilyNameSize(
    _In_ WinMLEpHandle ep,
    _Out_ size_t* size
);

STDAPI WinMLEpGetPackageFamilyName(
    _In_ WinMLEpHandle ep,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLEpGetLibraryPathSize(
    _In_ WinMLEpHandle ep,
    _Out_ size_t* size
);

STDAPI WinMLEpGetLibraryPath(
    _In_ WinMLEpHandle ep,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLEpGetPackageRootPathSize(
    _In_ WinMLEpHandle ep,
    _Out_ size_t* size
);

STDAPI WinMLEpGetPackageRootPath(
    _In_ WinMLEpHandle ep,
    size_t bufferSize,
    _Out_writes_to_(bufferSize, *bufferUsed) char* buffer,
    _Out_opt_ size_t* bufferUsed
);

STDAPI WinMLEpGetReadyState(
    _In_ WinMLEpHandle ep,
    _Out_ WinMLEpReadyState* state
);

STDAPI WinMLEpGetCertification(
    _In_ WinMLEpHandle ep,
    _Out_ WinMLEpCertification* certification
);

STDAPI WinMLEpEnsureReady(
    _In_ WinMLEpHandle ep
);

STDAPI WinMLEpEnsureReadyAsync(
    _In_ WinMLEpHandle ep,
    _Inout_ WinMLAsyncBlock* async
);

#ifdef __cplusplus
}
#endif
