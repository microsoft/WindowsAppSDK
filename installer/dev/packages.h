#pragma once
#include "pch.h"
#include "project_reunion_definitions.h"

using namespace winrt;
using namespace Windows::System;

// Information about the type of packages that are embedded
// More properties can be added as-needed, such as type - framework | main | appinstaller | bundle
// For now all packages are frameworks and only the processor architecture is meaningful.

namespace ProjectReunionInstaller {

    struct ResourcePackageInfo
    {
        std::wstring id;
        std::wstring resourceType;
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
    };
}
