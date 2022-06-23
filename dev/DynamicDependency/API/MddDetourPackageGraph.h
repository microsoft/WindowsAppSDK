// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDDETOURPACKAGEGRAPH_H)
#define MDDDETOURPACKAGEGRAPH_H

#include "appmodel_msixdynamicdependency.h"

HRESULT WINAPI MddDetourPackageGraphInitialize() noexcept;

void WINAPI MddDetourPackageGraphShutdown() noexcept;

LONG WINAPI GetCurrentStaticPackageInfo(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) noexcept;

LONG MddGetPackageInfo1Or2(
    PACKAGE_INFO_REFERENCE packageInfoReference,
    UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

HRESULT MddTrueGetCurrentPackageInfo3(
    UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count);

#endif // MDDDETOURPACKAGEGRAPH_H
