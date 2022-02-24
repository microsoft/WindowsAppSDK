// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __MICROSFT_WINDOWSAPPSDK_SELFCONTAINED_H
#define __MICROSFT_WINDOWSAPPSDK_SELFCONTAINED_H

//TODO:37999189 Support 3rd scenario (Yes=DevInnerLoop, Yes=PipelineBuild product, No=PipelineBuild Unit/FunctionalTests)
#if defined(WINDOWSAPPSDK_SELFCONTAINED_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W)
#   define WINDOWSAPPSDK_SELFCONTAINED_DETECT_FRAMEWORK_PACKAGEFAMILYNAME  WINDOWSAPPSDK_SELFCONTAINED_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W
#elif __has_include(<WindowsAppRuntime-VersionInfo.h>)
#   include <WindowsAppRuntime-VersionInfo.h>
#   define WINDOWSAPPSDK_SELFCONTAINED_DETECT_FRAMEWORK_PACKAGEFAMILYNAME  WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W
#else
#   error "Unknown Windows App SDK package family name! WindowsAppRuntime-VersionInfo.h not found and test alternative WINDOWSAPPSDK_SELFCONTAINED_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W not found"
#endif
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
    uint32_t packageInfoCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    THROW_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageInfoCount, packageInfo, buffer));
    for (uint32_t index=0; index < packageInfoCount; ++index)
    {
        auto c_windowsAppRuntimePackageFamilyName{ WINDOWSAPPSDK_SELFCONTAINED_DETECT_FRAMEWORK_PACKAGEFAMILYNAME };
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
