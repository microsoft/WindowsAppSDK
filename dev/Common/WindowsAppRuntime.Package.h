// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSFT_WINDOWSAPPRUNTIME_PACKAGE_H
#define __MICROSFT_WINDOWSAPPRUNTIME_PACKAGE_H

#if defined(__cplusplus)
#include "AppModel.PackageGraph.h"

namespace WindowsAppRuntime::Package
{
/// Return the package information for the Windows App Runtime runtime (framework) package in the current process' package graph (if any)
/// @note This is a variant of WindowsAppRuntime_IsSelfContained() but returns package details instead of mere existence.
///       You can think of WindowsAppRuntime_IsSelfContained() as a misnomer for `bool WindowsAppRuntime::PackageGraph::IsFrameworkPresent()`.
/// @param packageGraphCount number of packages in packageGraph.
/// @param packageGraph current packageGraph.
/// @return pointer to the Windows App SDK runtime (framework) package in the package graph, or NULL if not found.
inline PACKAGE_INFO* GetFrameworkPackageInfo(uint32_t& packageGraphCount, wil::unique_cotaskmem_ptr<PACKAGE_INFO>& packageGraph)
{
    const auto frameworkPackageFamilyName{ ::WindowsAppRuntime::VersionInfo::Framework::GetPackageFamilyName() };
    return ::AppModel::PackageGraph::GetPackageInFamily(frameworkPackageFamilyName.c_str(), packageGraphCount, packageGraph);
}

/// Return the package information for the Windows App Runtime runtime (framework) package in the current process' package graph (if any)
/// @note This is a variant of WindowsAppRuntime_IsSelfContained() but returns package details instead of mere existence.
///       You can think of WindowsAppRuntime_IsSelfContained() as a misnomer for `bool WindowsAppRuntime::PackageGraph::IsFrameworkPresent()`.
/// @param buffer memory for the package graph information.
/// @return pointer to the Windows App SDK runtime (framework) package in the package graph, or NULL if not found.
inline PACKAGE_INFO* GetFrameworkPackageInfo(wil::unique_cotaskmem_ptr<PACKAGE_INFO>& buffer)
{
    uint32_t packageGraphCount{};
    return GetFrameworkPackageInfo(packageGraphCount, buffer);
}
}
#endif // defined(__cplusplus)

#endif // __MICROSFT_WINDOWSAPPRUNTIME_PACKAGE_H
