// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "windowsappruntime_definitions.h"

using namespace winrt;
using namespace Windows::System;

// Information about the type of packages that are embedded
// More properties can be added as-needed, such as type - framework | main | appinstaller | bundle
// For now all packages are frameworks and only the processor architecture is meaningful.

namespace WindowsAppRuntimeInstaller {

    enum class DeploymentBehavior
    {
        Default,        // Package will be deployed based on its properties alone.
        Framework,      // Package will be treated as a framework, even if it is not.
    };

    struct ResourcePackageInfo
    {
        std::wstring id;
        std::wstring resourceType;
        DeploymentBehavior deploymentBehavior{ DeploymentBehavior::Default };
    };

    static ResourcePackageInfo c_packages[] =
    {
    #if defined(MSIX_FRAMEWORK_ARM64_LISTENTRY)
        MSIX_FRAMEWORK_ARM64_LISTENTRY
    #endif
    #if defined(MSIX_FRAMEWORK_X64_LISTENTRY)
        MSIX_FRAMEWORK_X64_LISTENTRY
    #endif
    #if defined(MSIX_FRAMEWORK_X86_LISTENTRY)
        MSIX_FRAMEWORK_X86_LISTENTRY
    #endif

    #if defined(MSIX_MAIN_ARM64_LISTENTRY)
        MSIX_MAIN_ARM64_LISTENTRY
    #endif
    #if defined(MSIX_MAIN_X64_LISTENTRY)
        MSIX_MAIN_X64_LISTENTRY
    #endif
    #if defined(MSIX_MAIN_X86_LISTENTRY)
        MSIX_MAIN_X86_LISTENTRY
    #endif

    #if defined(MSIX_SINGLETON_ARM64_LISTENTRY)
        MSIX_SINGLETON_ARM64_LISTENTRY
    #endif
    #if defined(MSIX_SINGLETON_X64_LISTENTRY)
        MSIX_SINGLETON_X64_LISTENTRY
    #endif
    #if defined(MSIX_SINGLETON_X86_LISTENTRY)
        MSIX_SINGLETON_X86_LISTENTRY
    #endif

    #if defined(MSIX_DDLM_ARM64_LISTENTRY)
        MSIX_DDLM_ARM64_LISTENTRY
    #endif
    #if defined(MSIX_DDLM_X64_LISTENTRY)
        MSIX_DDLM_X64_LISTENTRY
    #endif
    #if defined(MSIX_DDLM_X86_LISTENTRY)
        MSIX_DDLM_X86_LISTENTRY
    #endif
    };

    struct ResourceLicenseInfo
    {
        std::wstring id;
        std::wstring resourceType;
    };

    #if !defined(MSIX_PROCESS_LICENSES)
    #if defined(MSIX_MAIN_LICENSE_LISTENTRY) || defined(MSIX_SINGLETON_LICENSE_LISTENTRY)
    #define MSIX_PROCESS_LICENSES
    #else
    #undef MSIX_PROCESS_LICENSES
    #endif
    #endif

    #if defined(MSIX_PROCESS_LICENSES)
    static ResourceLicenseInfo c_licenses[] =
    {
    #if defined(MSIX_MAIN_LICENSE_LISTENTRY)
        MSIX_MAIN_LICENSE_LISTENTRY
    #endif

    #if defined(MSIX_SINGLETON_LICENSE_LISTENTRY)
        MSIX_SINGLETON_LICENSE_LISTENTRY
    #endif
    };
    #endif
}
