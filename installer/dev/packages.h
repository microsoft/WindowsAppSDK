// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
    #if defined(WINDOWSAPPRUNTIME_FRAMEWORK_ARM64_LISTENTRY)
        WINDOWSAPPRUNTIME_FRAMEWORK_ARM64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_FRAMEWORK_X64_LISTENTRY)
        WINDOWSAPPRUNTIME_FRAMEWORK_X64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_FRAMEWORK_X86_LISTENTRY)
        WINDOWSAPPRUNTIME_FRAMEWORK_X86_LISTENTRY
    #endif

    #if defined(WINDOWSAPPRUNTIME_MAIN_ARM64_LISTENTRY)
        WINDOWSAPPRUNTIME_MAIN_ARM64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_MAIN_X64_LISTENTRY)
        WINDOWSAPPRUNTIME_MAIN_X64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_MAIN_X86_LISTENTRY)
        WINDOWSAPPRUNTIME_MAIN_X86_LISTENTRY
    #endif

    #if defined(WINDOWSAPPRUNTIME_SINGLETON_ARM64_LISTENTRY)
        WINDOWSAPPRUNTIME_SINGLETON_ARM64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_SINGLETON_X64_LISTENTRY)
        WINDOWSAPPRUNTIME_SINGLETON_X64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_SINGLETON_X86_LISTENTRY)
        WINDOWSAPPRUNTIME_SINGLETON_X86_LISTENTRY
    #endif

    #if defined(WINDOWSAPPRUNTIME_DDLM_ARM64_LISTENTRY)
        WINDOWSAPPRUNTIME_DDLM_ARM64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_DDLM_X64_LISTENTRY)
        WINDOWSAPPRUNTIME_DDLM_X64_LISTENTRY
    #endif
    #if defined(WINDOWSAPPRUNTIME_DDLM_X86_LISTENTRY)
        WINDOWSAPPRUNTIME_DDLM_X86_LISTENTRY
    #endif
    };

    struct ResourceLicenseInfo
    {
        std::wstring id;
        std::wstring resourceType;
    };

    #if !defined(WINDOWSAPPRUNTIME_PROCESS_LICENSES)
    #if defined(WINDOWSAPPRUNTIME_MAIN_LICENSE_LISTENTRY) || defined(WINDOWSAPPRUNTIME_SINGLETON_LICENSE_LISTENTRY)
    #define WINDOWSAPPRUNTIME_PROCESS_LICENSES
    #else
    #undef WINDOWSAPPRUNTIME_PROCESS_LICENSES
    #endif
    #endif

    #if defined(WINDOWSAPPRUNTIME_PROCESS_LICENSES)
    static ResourceLicenseInfo c_licenses[] =
    {
    #if defined(WINDOWSAPPRUNTIME_MAIN_LICENSE_LISTENTRY)
        WINDOWSAPPRUNTIME_MAIN_LICENSE_LISTENTRY
    #endif

    #if defined(WINDOWSAPPRUNTIME_SINGLETON_LICENSE_LISTENTRY)
        WINDOWSAPPRUNTIME_SINGLETON_LICENSE_LISTENTRY
    #endif
    };
    #endif
}
