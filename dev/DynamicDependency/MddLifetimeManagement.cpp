// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "MddLifetimeManagement.h"

STDAPI MddLifetimeManagementGC() noexcept try
{
    // Enumerate for all DynamicDependency Lifetime Management (DDLM) packages and remove redundantly unnecessary packages
    // 1. Same MAJOR version (breaking change boundary)
    // 2. Same architecture
    //
    // For each permutation of 1+2 if 2+ package are found determine the 'best match' to keep. Other packages found
    // with a version less than the 'best match' are redundant and can be removed.
    //
    // Don't remove pacakges in use. We can't determine if a package is in-use but Windows can.
    // Attempting to remove a package in-use will fail with HRESULT_FROM_WIN32(ERROR_PACKAGES_IN_USE).
    // Treat that as a non-error.
    //
    // We have no direct way to determine all DDLM packages so we'll enumerate each possible MAJOR version
    // up to a reasonable maximum. This is a maintenance type API not needed in hot paths so the minor cost
    // to ask for a few potential future versions with no matches isn't a performance concern.

    const UINT32 c_maxMajorVersion{ 9 };
    PCWSTR c_architectures[]{ L"x86", L"x64", L"arm64" };
    for (UINT32 majorVersion=0; majorVersion <= c_maxMajorVersion; ++majorVersion)
    {
        for (auto architecture : c_architectures)
        {
            // Look for windows.appExtension with name="com.microsoft.projectreunion.ddlm.<majorversion>.<architecture>"
            WCHAR appExtensionName[100]{};
            wsprintf(appExtensionName, L"com.microsoft.projectreunion.ddlm.%hu.%s", majorVersion, architecture);

            auto catalog{ winrt::Windows::ApplicationModel::AppExtensions::AppExtensionCatalog::Open(appExtensionName) };
            auto appExtensions{ catalog.FindAllAsync().get() };
            for (auto appExtension : appExtensions)
            {
            }
        }
    }
    return S_OK;
}
CATCH_RETURN();
