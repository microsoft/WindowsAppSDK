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

    PCWSTR frameworkPackageFamilyName{};
    const auto getFrameworkPackageFamilyNameResult{
        WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(&frameworkPackageFamilyName) };
    if (getFrameworkPackageFamilyNameResult == HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND))
    {
        // The aggregate runtime resource is not deployed with component-only self-contained apps.
        *isSelfContained = TRUE;
        return S_OK;
    }
    RETURN_IF_FAILED(getFrameworkPackageFamilyNameResult);

    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    uint32_t packageInfoCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    RETURN_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageInfoCount, packageInfo, buffer));
    for (uint32_t index=0; index < packageInfoCount; ++index)
    {
        if (CompareStringOrdinal(packageInfo[index].packageFamilyName, -1, frameworkPackageFamilyName, -1, TRUE) == CSTR_EQUAL)
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
