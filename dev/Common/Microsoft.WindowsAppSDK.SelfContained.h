// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __MICROSFT_WINDOWSAPPSDK_SELFCONTAINED_H
#define __MICROSFT_WINDOWSAPPSDK_SELFCONTAINED_H

#include <WindowsAppRuntime-VersionInfo.h>
#include <AppModel.PackageGraph.h>

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

namespace Microsoft::WindowsAppSDK::SelfContained
{
inline bool IsSelfContained()
{
    const UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    const PackagePathType packagePathType{ PackagePathType_Install }; // Don't need the path so use the leanest possible answer
    uint32_t packageInfoCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    THROW_IF_FAILED(GetCurrentPackageInfo(flags, packagePathType, packageInfoCount, packageInfo, buffer));
    for (uint32_t index=0; index < packageInfoCount; ++index)
    {
        PCWSTR c_windowsAppRuntimePackageFamilyName{ L"Microsoft.WindowsAppRuntime." _STRINGIZE(WINDOWSAPPSDK_RELEASE_MAJOR) L"_" _STRINGIZE(WINDOWSAPPSDK_RELEASE_MINOR) WINDOWSAPPSDK_RELEASE_VERSION_TAG_W L"_" WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHERID_W };
        if (CompareStringOrdinal(packageInfo[index].packageFamilyName, -1, c_windowsAppRuntimePackageFamilyName, -1, TRUE) == CSTR_EQUAL)
        {
            // Found the Windows App SDK framework package in the package graph. Not self-contained!
            return false;
        }
    }

    // Didn't find the Windows App SDK framework package in the package graph. We're self-contained!
    return true;
}
}

#endif // __MICROSFT_WINDOWSAPPSDK_SELFCONTAINED_H
