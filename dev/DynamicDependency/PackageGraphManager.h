// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(PACKAGEGRAPHMANAGER_H)
#define PACKAGEGRAPHMANAGER_H

#include <PackageGraph.h>

namespace MddCore
{
class PackageGraphManager
{
public:
    static HRESULT ResolvePackageDependency(
        PCWSTR packageDependencyId,
        MddAddPackageDependencyOptions options,
        wil::unique_process_heap_string& packageFullName);

    static HRESULT AddToPackageGraph(
        _In_ PCWSTR packageDependencyId,
        INT32 rank,
        MddAddPackageDependencyOptions options,
        _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
        _Outptr_opt_result_maybenull_ PWSTR* packageFullName);

    static void RemoveFromPackageGraph(
        MDD_PACKAGEDEPENDENCY_CONTEXT context);

    static HRESULT GetPackageDependencyForContext(
        _In_ MDD_PACKAGEDEPENDENCY_CONTEXT context,
        wil::unique_process_heap_string& packageDependencyId);

public:
    typedef LONG (WINAPI* GetCurrentPackageInfo2Function)(
        const UINT32 flags,
        PackagePathType packagePathType,
        UINT32* bufferLength,
        BYTE* buffer,
        UINT32* count);

    static HRESULT GetCurrentPackageInfo2(
        const UINT32 flags,
        PackagePathType packagePathType,
        UINT32* bufferLength,
        BYTE* buffer,
        UINT32* count,
        GetCurrentPackageInfo2Function getCurrentPackageInfo2) noexcept;

private:
    static UINT32 SerializePackageInfoToBuffer(
        const UINT32 flags,
        const PackagePathType packagePathType,
        const UINT32 bufferLength,
        BYTE* buffer,
        const std::vector<const MddCore::PackageGraphNode*>& matchingPackageInfo,
        const UINT32 dynamicPackagesCount,
        const PACKAGE_INFO* staticPackageInfo,
        const UINT32 staticPackagesCount);

    static void SerializeStringToBuffer(
        const UINT32 bufferLength,
        BYTE*& buffer,
        UINT32& bufferNeeded,
        PWSTR& to,
        PCWSTR from);

    static inline UINT32 wcssize(PCWSTR s)
    {
        return static_cast<UINT32>((wcslen(s) + 1) * sizeof(*s));
    }

private:
    static std::mutex s_lock;
    static MddCore::PackageGraph s_packageGraph;
};
}

#endif // PACKAGEGRAPHMANAGER_H
