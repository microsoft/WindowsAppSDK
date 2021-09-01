// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDDETOURPACKAGEGRAPH_H)
#define MDDDETOURPACKAGEGRAPH_H

HRESULT WINAPI MddDetourPackageGraphInitialize() noexcept;

void WINAPI MddDetourPackageGraphShutdown() noexcept;

LONG WINAPI GetCurrentStaticPackageInfo(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) noexcept;

#endif // MDDDETOURPACKAGEGRAPH_H
