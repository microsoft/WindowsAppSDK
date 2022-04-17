// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#if __has_include(<WindowsAppSDK-VersionInfo.h>)
#   include <WindowsAppSDK-VersionInfo.h>
#   define WINDOWSAPPRUNTIME_SELFCONTAINED_EXPECTED_PACKAGEFAMILYNAME   WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W
#elif __has_include(<WindowsAppRuntime-VersionInfo.h>)
#   include <WindowsAppRuntime-VersionInfo.h>
#   define WINDOWSAPPRUNTIME_SELFCONTAINED_EXPECTED_PACKAGEFAMILYNAME   WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W
#else
#   define WINDOWSAPPRUNTIME_SELFCONTAINED_EXPECTED_PACKAGEFAMILYNAME   nullptr
#endif
#include <AppModel.PackageGraph.h>

#include "WindowsAppRuntime.SelfContained.h"

static std::wstring g_test_frameworkPackageFamilyName;

STDAPI WindowsAppRuntime_IsSelfContained(
    BOOL* isSelfContained) noexcept try
{
    *isSelfContained = FALSE;

    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    uint32_t packageInfoCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    RETURN_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageInfoCount, packageInfo, buffer));
    PCWSTR c_frameworkPackageFamilyName{ !g_test_frameworkPackageFamilyName.empty() ?
                                            g_test_frameworkPackageFamilyName.c_str() :
                                            WINDOWSAPPRUNTIME_SELFCONTAINED_EXPECTED_PACKAGEFAMILYNAME };
    for (uint32_t index=0; index < packageInfoCount; ++index)
    {
        if (CompareStringOrdinal(packageInfo[index].packageFamilyName, -1, c_frameworkPackageFamilyName, -1, TRUE) == CSTR_EQUAL)
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

STDAPI WindowsAppRuntime_SelfContainedTestInitialize(
    PCWSTR frameworkPackageFamilyName) noexcept try
{
    if (!frameworkPackageFamilyName || (*frameworkPackageFamilyName == L'0'))
    {
        // Shutdown test support
        g_test_frameworkPackageFamilyName.clear();
    }
    else
    {
        // Initialize test support
        g_test_frameworkPackageFamilyName = frameworkPackageFamilyName;
    }
    return S_OK;
}
CATCH_RETURN();
