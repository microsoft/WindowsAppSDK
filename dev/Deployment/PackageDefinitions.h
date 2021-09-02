// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>

#define WINDOWSAPPSDK_IDENTITY_PUBLISHERID                      L"8wekyb3d8bbwe"
#define WINDOWSAPPSDK_NAME_DELIMETER                            L"_"
#define WINDOWSAPPSDK_NAME_SUFFIX                               WINDOWSAPPSDK_NAME_DELIMETER WINDOWSAPPSDK_IDENTITY_PUBLISHERID
#define WINDOWSAPPSDK_FRAMEWORK_PACKAGE_IDENTIFIER              L"Framework"
#define WINDOWSAPPSDK_MAIN_PACKAGE_IDENTIFIER                   L"Main"
#define WINDOWSAPPSDK_SINGLETON_PACKAGE_IDENTIFIER              L"Singleton"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    struct TargetPackage
    {
        std::wstring identifier;
    };

    static TargetPackage c_targetPackages[] =
    {
        { WINDOWSAPPSDK_MAIN_PACKAGE_IDENTIFIER },
        { WINDOWSAPPSDK_SINGLETON_PACKAGE_IDENTIFIER },
    };
}
