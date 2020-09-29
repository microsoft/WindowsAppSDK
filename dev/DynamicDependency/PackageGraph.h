// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(PACKAGEGRAPH_H)
#define PACKAGEGRAPH_H

#include <MsixDynamicDependency.h>

#include <PackageId.h>
#include <PackageGraphNode.h>

namespace MddCore
{
std::unique_lock<std::mutex> AcquirePackageGraphLock();

typedef LONG (WINAPI * GetCurrentPackageInfo2Function)(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

HRESULT GetCurrentPackageInfo2(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count,
    GetCurrentPackageInfo2Function getCurrentPackageInfo2) noexcept;

UINT32 SerializePackageInfoToBuffer(
    const UINT32 flags,
    const PackagePathType packagePathType,
    const UINT32 bufferLength,
    BYTE* buffer,
    const std::vector<MddCore::PackageGraphNode*>& matchingPackageInfo,
    const UINT32 dynamicPackagesCount,
    const PACKAGE_INFO* staticPackageInfo,
    const UINT32 staticPackagesCount);

void SerializeStringToBuffer(
    const UINT32 bufferLength,
    BYTE*& buffer,
    UINT32& bufferNeeded,
    PWSTR& to,
    PCWSTR from);

HRESULT ResolvePackageDependency(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName) noexcept;

HRESULT ResolvePackageDependency(
    PCWSTR packageDependencyId,
    MddAddPackageDependencyOptions options,
    wil::unique_process_heap_string& packageFullName) noexcept;

bool IsPackageABetterFitPerArchitecture(
    const MddCore::PackageId& bestFit,
    const MddCore::PackageId& candidate);

Architecture GetCurrentArchitecture();

HRESULT AddToPackageGraph(
    PCWSTR packageFullName,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    MDD_PACKAGEDEPENDENCY_CONTEXT& context);

HRESULT RemoveFromPackageGraph(MDD_PACKAGEDEPENDENCY_CONTEXT context);
}

#endif // PACKAGEGRAPH_H
