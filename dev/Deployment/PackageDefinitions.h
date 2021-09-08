// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>

#define WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX                       L"Microsoft.WindowsAppRuntime"
#define WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID                       L"8wekyb3d8bbwe"
#define WINDOWSAPPRUNTIME_PACKAGE_NAME_DELIMETER                    L"_"
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DELIMETER             L"."
#define WINDOWSAPPRUNTIME_PACKAGE_NAME_SUFFIX                       WINDOWSAPPRUNTIME_PACKAGE_NAME_DELIMETER WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_MAIN                  L"Main"
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON             L"Singleton"
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DDLM                  L"DDLM"
#define WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER                  L"MSIX"
#define WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION          L".msix"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    // See https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackages.md#3-package-naming
    // To identify a package, it must have the correct name identifier.
    // The Framework package does not have a name identifier, only the prefix and an optional VersionTag.
    // All other packages have a SubtypeName following the prefix.

    struct PackageIdentifier
    {
        std::wstring identifier;
    };

    // All supported SubTypeNames.
    static PackageIdentifier c_subTypeNames[] =
    {
        { WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_MAIN },
        { WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON },
        { WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DDLM },
    };

    // All packages that the DeploymentAPI will attempt check and deploy from the framework.
    static PackageIdentifier c_targetPackages[] =
    {
        { WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_MAIN },
        { WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON },
    };
}
