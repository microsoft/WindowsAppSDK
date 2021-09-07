// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>

#define WINDOWSAPPRUNTIME_NAME_IDENTIFIER                           L"WindowsAppRuntime"
#define WINDOWSAPPRUNTIME_IDENTITY_PUBLISHERID                      L"8wekyb3d8bbwe"
#define WINDOWSAPPRUNTIME_NAME_DELIMETER                            L"_"
#define WINDOWSAPPRUNTIME_NAME_SUFFIX                               WINDOWSAPPRUNTIME_NAME_DELIMETER WINDOWSAPPRUNTIME_IDENTITY_PUBLISHERID
#define WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_IDENTIFIER              L"Framework"
#define WINDOWSAPPRUNTIME_MAIN_PACKAGE_IDENTIFIER                   L"Main"
#define WINDOWSAPPRUNTIME_SINGLETON_PACKAGE_IDENTIFIER              L"Singleton"
#define WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER                  L"MSIX"
#define WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION          L".msix"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    struct TargetPackage
    {
        std::wstring identifier;
    };

    static TargetPackage c_targetPackages[] =
    {
        { WINDOWSAPPRUNTIME_MAIN_PACKAGE_IDENTIFIER },
        { WINDOWSAPPRUNTIME_SINGLETON_PACKAGE_IDENTIFIER },
    };
}
