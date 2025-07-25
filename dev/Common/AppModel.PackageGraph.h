// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __APPMODEL_PACKAGEGRAPH_H
#define __APPMODEL_PACKAGEGRAPH_H

#include <appmodel.h>

namespace AppModel::PackageGraph
{
inline HRESULT GetCurrentPackageGraph(
    const UINT32 flags,
    uint32_t& packageInfoCount,
    const PACKAGE_INFO*& packageInfo,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer)
{
   packageInfoCount = 0;
    packageInfo = nullptr;

    uint32_t bufferLength{};
    LONG rc{ ::GetCurrentPackageInfo(flags, &bufferLength, nullptr, &packageInfoCount) };
    if ((rc == APPMODEL_ERROR_NO_PACKAGE) || (packageInfoCount == 0))
   {
        // No packages. We�re done
        return S_OK;
    }
    RETURN_HR_IF(HRESULT_FROM_WIN32(rc), rc != ERROR_INSUFFICIENT_BUFFER);

    buffer = wil::make_unique_cotaskmem<BYTE[]>(bufferLength);
    RETURN_IF_WIN32_ERROR(::GetCurrentPackageInfo(flags, &bufferLength, buffer.get(), &packageInfoCount));
    packageInfo = reinterpret_cast<PACKAGE_INFO*>(buffer.get());
    return S_OK;
}

/// Return the package information for the first package in a package family in the current process' package graph (if any)
/// @param packageFamilyName the package family.
/// @param packageGraphCount number of packages in packageGraph.
/// @param packageGraph current packageGraph.
/// @return pointer to the first package in the package family in the package graph, or NULL if not found.
inline PACKAGE_INFO* GetPackageInFamily(PCWSTR packageFamilyName, uint32_t& packageGraphCount, wil::unique_cotaskmem_ptr<PACKAGE_INFO>& packageGraph)
{
    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    uint32_t packageGraphCount{};
    const PACKAGE_INFO* packageInfo{};
    RETURN_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageGraphCount, packageInfo, packageGraph));
    const auto frameworkPackageFamilyName{ ::WindowsAppRuntime::VersionInfo::Framework::GetPackageFamilyName() };
    for (uint32_t index=0; index < packageGraphCount; ++index)
    {
        if (CompareStringOrdinal(packageInfo[index].packageFamilyName, -1, packageFamilyName, -1, TRUE) == CSTR_EQUAL)
        {
            // Found the Windows App SDK framework package in the package graph
            return packageInfo + index;
        }
    }

    // Didn't find the Windows App SDK framework package in the package graph
    packageGraphCount = 0;
    packageGraph.reset();
    return nullptr;
}

/// Return the package information for the first package in a package family in the current process' package graph (if any)
/// @param packageFamilyName the package family.
/// @param buffer memory for the package graph information.
/// @return pointer to the first package in the package family in the package graph, or NULL if not found.
inline PACKAGE_INFO* GetPackageInFamily(PCSTR packageFamilyName, wil::unique_cotaskmem_ptr<PACKAGE_INFO>& buffer)
{
    uint32_t packageGraphCount{};
    return GetFramework(packageFamilyName, packageGraphCount, buffer);
}
}
}

#endif // __APPMODEL_PACKAGEGRAPH_H
