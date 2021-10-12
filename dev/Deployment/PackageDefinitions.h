// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>

#define WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX                       L"Microsoft.WindowsAppRuntime"
#define WINDOWSAPPRUNTIME_PACKAGE_NAME_DDLMPREFIX                   L"Microsoft.WinAppRuntime"
#define WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID                       L"8wekyb3d8bbwe"
#define WINDOWSAPPRUNTIME_PACKAGE_NAME_DELIMETER                    L"_"
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DELIMETER             L"."
#define WINDOWSAPPRUNTIME_PACKAGE_NAME_SUFFIX                       WINDOWSAPPRUNTIME_PACKAGE_NAME_DELIMETER WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_MAIN                  L"Main"
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON             L"Singleton"
#define WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DDLM                  L"DDLM"
#define WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER                  L"MSIX"
#define WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION          L".msix"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    // See https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackages.md#3-package-naming

    // Packages have different naming schmes depending on whether they are versioned or unversioned.
    enum class PackageVersionType
    {
        Versioned,      // Package has a normal versioned name with major.minor and tag.
        Unversioned,    // Package has no major.minor version in the name.
        Framework,      // Package has a framework-like version with architecture in the name.
    };

    struct PackageIdentifier
    {
        std::wstring prefix;
        std::wstring identifier;
        PackageVersionType versionType;
    };

    // All supported SubTypeNames.
    static PackageIdentifier c_subTypeNames[] =
    {
        { WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_MAIN, PackageVersionType::Versioned },
        { WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON, PackageVersionType::Unversioned },
        { WINDOWSAPPRUNTIME_PACKAGE_NAME_DDLMPREFIX, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DDLM, PackageVersionType::Framework },
    };

    // All packages that the DeploymentAPI will attempt check and deploy from the framework.
    static PackageIdentifier c_targetPackages[] =
    {
        { WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_MAIN, PackageVersionType::Versioned },
        { WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON, PackageVersionType::Unversioned },
    };
}
