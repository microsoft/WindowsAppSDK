#pragma once
#include "pch.h"
#include "project_reunion_definitions.h"

using namespace winrt;
using namespace Windows::System;

// Information about the type of packages that are embedded
// More properties can be added as-needed, such as type - framework | main | appinstaller | bundle
// For now all packages are frameworks and only the processor architecture is meaningful.

namespace ProjectReunionInstaller {

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
    #if defined(PR_FRAMEWORK_X86_LISTENTRY)
        PR_FRAMEWORK_X86_LISTENTRY
    #endif
    #if defined(PR_FRAMEWORK_X64_LISTENTRY)
        PR_FRAMEWORK_X64_LISTENTRY
    #endif
    #if defined(PR_FRAMEWORK_ARM64_LISTENTRY)
        PR_FRAMEWORK_ARM64_LISTENTRY
    #endif
    #if defined(PR_MAIN_X86_LISTENTRY)
        PR_MAIN_X86_LISTENTRY
    #endif
    #if defined(PR_MAIN_X64_LISTENTRY)
        PR_MAIN_X64_LISTENTRY
    #endif
    #if defined(PR_MAIN_ARM64_LISTENTRY)
        PR_MAIN_ARM64_LISTENTRY
    #endif
    #if defined(PR_DDLM_X86_LISTENTRY)
        PR_DDLM_X86_LISTENTRY
    #endif
    #if defined(PR_DDLM_X64_LISTENTRY)
        PR_DDLM_X64_LISTENTRY
    #endif
    #if defined(PR_DDLM_ARM64_LISTENTRY)
        PR_DDLM_ARM64_LISTENTRY
    #endif
    };
}
