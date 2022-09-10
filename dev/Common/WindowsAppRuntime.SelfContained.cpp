// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <AppModel.PackageGraph.h>

#include "WindowsAppRuntime.VersionInfo.h"
#include "WindowsAppRuntime.SelfContained.h"

STDAPI WindowsAppRuntime_IsSelfContained(
    BOOL* isSelfContained) noexcept try
{
    *isSelfContained = FALSE;

    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    uint32_t packageInfoCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    RETURN_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageInfoCount, packageInfo, buffer));
    const auto frameworkPackageFamilyName{ ::WindowsAppRuntime::VersionInfo::Framework::GetPackageFamilyName() };
    for (uint32_t index=0; index < packageInfoCount; ++index)
    {
        if (CompareStringOrdinal(packageInfo[index].packageFamilyName, -1, frameworkPackageFamilyName.c_str(), -1, TRUE) == CSTR_EQUAL)
        {
            // Found the Windows App SDK framework package in the package graph. Not self-contained!
            return S_OK;
        }
    }

    // Didn't find the Windows App SDK framework package in the package graph. We're self-contained!
    *isSelfContained = TRUE;
    return S_OK;
}
CATCH_RETURN();
