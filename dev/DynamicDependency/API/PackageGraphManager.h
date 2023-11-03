// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(PACKAGEGRAPHMANAGER_H)
#define PACKAGEGRAPHMANAGER_H

#include <appmodel_msixdynamicdependency.h>

#include <PackageGraph.h>

namespace MddCore
{
class PackageGraphManager
{
public:
    static UINT32 GetPackageGraphRevisionId();

    static UINT32 IncrementPackageGraphRevisionId();

    static UINT32 SetPackageGraphRevisionId(const UINT32 value);

public:
    static HRESULT GetResolvedPackageDependency(
        PCWSTR packageDependencyId,
        wil::unique_process_heap_string& packageFullName);

    static HRESULT GetResolvedPackageDependency2(
        PCWSTR packageDependencyId,
        wil::unique_process_heap_string& packageFullName);

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
    typedef LONG (WINAPI* GetCurrentPackageInfo3Function)(
        const UINT32 flags,
        PackageInfoType packageInfoType,
        UINT32* bufferLength,
        void* buffer,
        UINT32* count);

    static HRESULT GetCurrentPackageInfo3(
        const UINT32 flags,
        PackageInfoType packageInfoType,
        UINT32* bufferLength,
        void* buffer,
        UINT32* count) noexcept;

private:
    static UINT32 SerializePackageInfoToBuffer(
        const UINT32 flags,
        const PackageInfoType packageInfoType,
        const UINT32 bufferLength,
        void* buffer,
        const std::vector<const MddCore::PackageGraphNode*>& matchingPackageInfo,
        const UINT32 dynamicPackagesCount,
        const PACKAGE_INFO* staticPackageInfo,
        const UINT32 staticPackagesCount);

    static void SerializeStringToBuffer(
        const UINT32 bufferLength,
        void*& buffer,
        UINT32& bufferNeeded,
        PWSTR& to,
        PCWSTR from);

    static inline UINT32 wcssize(PCWSTR s)
    {
        return static_cast<UINT32>((wcslen(s) + 1) * sizeof(*s));
    }

private:
    static std::recursive_mutex s_lock;
    static MddCore::PackageGraph s_packageGraph;
    static volatile ULONG s_packageGraphRevisionId;
};
}

#endif // PACKAGEGRAPHMANAGER_H
