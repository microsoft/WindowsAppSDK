  #pragma once

// This header defines the packages included in the installer.
// By default, the project will use test packages built for verification of this installer.

// For building the installer with non-test packages, include a "project_reunion_definitions_override.h" file.
// If present, the override header will be loaded to change the package definitions such as the path.
// Preprocessor definitions used in the override header must be supported by the resource compiler.

// Override header file example:
//
// #pragma once
//
// #undef PR_FRAMEWORK_X86_PATH
// #define PR_FRAMEWORK_X86_PATH "custompackages\\my_custom_x86_framework.appx"
//

// Each package has a package definition listed below.
// Names for macros are intentionally kept short due to resource compiler length limitations.

// x86 Framework
#define PR_FRAMEWORK_X86_ID L"PR_FWPACKAGE_X86"
#define PR_FRAMEWORK_X86_RCID PR_FWPACKAGE_X86
#define PR_FRAMEWORK_X86_TYPE L"PACKAGE"
#define PR_FRAMEWORK_X86_RCTYPE PACKAGE
#define PR_FRAMEWORK_X86_BEHAVIOR DeploymentBehavior::Default
#ifndef PR_FRAMEWORK_X86_PATH
    #define PR_FRAMEWORK_X86_PATH "..\\test\\testpackages\\framework_x86.msix"
#endif

// x64 Framework
#define PR_FRAMEWORK_X64_ID L"PR_FWPACKAGE_X64"
#define PR_FRAMEWORK_X64_RCID PR_FWPACKAGE_X64
#define PR_FRAMEWORK_X64_TYPE L"PACKAGE"
#define PR_FRAMEWORK_X64_RCTYPE PACKAGE
#define PR_FRAMEWORK_X64_BEHAVIOR DeploymentBehavior::Default
#ifndef PR_FRAMEWORK_X64_PATH
    #define PR_FRAMEWORK_X64_PATH "..\\test\\testpackages\\framework_x64.msix"
#endif

// arm64 Framework
#define PR_FRAMEWORK_ARM64_ID L"PR_FWPACKAGE_ARM64"
#define PR_FRAMEWORK_ARM64_RCID PR_FWPACKAGE_ARM64
#define PR_FRAMEWORK_ARM64_TYPE L"PACKAGE"
#define PR_FRAMEWORK_ARM64_RCTYPE PACKAGE
#define PR_FRAMEWORK_ARM64_BEHAVIOR DeploymentBehavior::Default
#ifndef PR_FRAMEWORK_ARM64_PATH
    #define PR_FRAMEWORK_ARM64_PATH "..\\test\\testpackages\\framework_arm64.msix"
#endif

// x86 Main
#define PR_MAIN_X86_ID L"PR_MAINPACKAGE_X86"
#define PR_MAIN_X86_RCID PR_MAINPACKAGE_X86
#define PR_MAIN_X86_TYPE L"PACKAGE"
#define PR_MAIN_X86_RCTYPE PACKAGE
#define PR_MAIN_X86_BEHAVIOR DeploymentBehavior::Default
#ifndef PR_MAIN_X86_PATH
    #define PR_MAIN_X86_PATH "..\\test\\testpackages\\main_x86.msix"
#endif

// x64 Main
#define PR_MAIN_X64_ID L"PR_MAINPACKAGE_X64"
#define PR_MAIN_X64_RCID PR_MAINPACKAGE_X64
#define PR_MAIN_X64_TYPE L"PACKAGE"
#define PR_MAIN_X64_RCTYPE PACKAGE
#define PR_MAIN_X64_BEHAVIOR DeploymentBehavior::Default
#ifndef PR_MAIN_X64_PATH
    #define PR_MAIN_X64_PATH "..\\test\\testpackages\\main_x64.msix"
#endif

// arm64 Main
#define PR_MAIN_ARM64_ID L"PR_MAINPACKAGE_ARM64"
#define PR_MAIN_ARM64_RCID PR_MAINPACKAGE_ARM64
#define PR_MAIN_ARM64_TYPE L"PACKAGE"
#define PR_MAIN_ARM64_RCTYPE PACKAGE
#define PR_MAIN_ARM64_BEHAVIOR DeploymentBehavior::Default
#ifndef PR_MAIN_ARM64_PATH
    #define PR_MAIN_ARM64_PATH "..\\test\\testpackages\\main_arm64.msix"
#endif

// x86 DDLM
#define PR_DDLM_X86_ID L"PR_DDLMPACKAGE_X86"
#define PR_DDLM_X86_RCID PR_DDLMPACKAGE_X86
#define PR_DDLM_X86_TYPE L"PACKAGE"
#define PR_DDLM_X86_RCTYPE PACKAGE
#define PR_DDLM_X86_BEHAVIOR DeploymentBehavior::Framework
#ifndef PR_DDLM_X86_PATH
    #define PR_DDLM_X86_PATH "..\\test\\testpackages\\ddlm_x86.msix"
#endif

// x64 DDLM
#define PR_DDLM_X64_ID L"PR_DDLMPACKAGE_X64"
#define PR_DDLM_X64_RCID PR_DDLMPACKAGE_X64
#define PR_DDLM_X64_TYPE L"PACKAGE"
#define PR_DDLM_X64_RCTYPE PACKAGE
#define PR_DDLM_X64_BEHAVIOR DeploymentBehavior::Framework
#ifndef PR_DDLM_X64_PATH
    #define PR_DDLM_X64_PATH "..\\test\\testpackages\\ddlm_x64.msix"
#endif

// arm64 DDLM
#define PR_DDLM_ARM64_ID L"PR_DDLMPACKAGE_ARM64"
#define PR_DDLM_ARM64_RCID PR_DDLMPACKAGE_ARM64
#define PR_DDLM_ARM64_TYPE L"PACKAGE"
#define PR_DDLM_ARM64_RCTYPE PACKAGE
#define PR_DDLM_ARM64_BEHAVIOR DeploymentBehavior::Framework
#ifndef PR_DDLM_ARM64_PATH
    #define PR_DDLM_ARM64_PATH "..\\test\\testpackages\\ddlm_arm64.msix"
#endif


// Package Inclusion
// Each package has a package list entry which defines its inclusion in packages.h and the .rc script.
// To not include a package, undefine the *_LISTENTRY and *_RCENTRY entries. At least one package must be included.

#define PR_FRAMEWORK_X86_LISTENTRY { PR_FRAMEWORK_X86_ID, PR_FRAMEWORK_X86_TYPE, PR_FRAMEWORK_X86_BEHAVIOR },
#define PR_FRAMEWORK_X86_RCENTRY PR_FRAMEWORK_X86_RCID PR_FRAMEWORK_X86_RCTYPE PR_FRAMEWORK_X86_PATH

#define PR_FRAMEWORK_X64_LISTENTRY  { PR_FRAMEWORK_X64_ID, PR_FRAMEWORK_X64_TYPE, PR_FRAMEWORK_X64_BEHAVIOR },
#define PR_FRAMEWORK_X64_RCENTRY PR_FRAMEWORK_X64_RCID PR_FRAMEWORK_X64_RCTYPE PR_FRAMEWORK_X64_PATH

// arm64 is included only on arm64 builds
#if defined(_M_ARM64)
    #define PR_FRAMEWORK_ARM64_LISTENTRY { PR_FRAMEWORK_ARM64_ID, PR_FRAMEWORK_ARM64_TYPE, PR_FRAMEWORK_ARM64_BEHAVIOR },
    #define PR_FRAMEWORK_ARM64_RCENTRY PR_FRAMEWORK_ARM64_RC PR_FRAMEWORK_ARM64_RCTYPE PR_FRAMEWORK_ARM64_PATH
#endif

#define PR_MAIN_X86_LISTENTRY { PR_MAIN_X86_ID, PR_MAIN_X86_TYPE, PR_MAIN_X86_BEHAVIOR },
#define PR_MAIN_X86_RCENTRY PR_MAIN_X86_RCID PR_MAIN_X86_RCTYPE PR_MAIN_X86_PATH

#define PR_MAIN_X64_LISTENTRY  { PR_MAIN_X64_ID, PR_MAIN_X64_TYPE, PR_MAIN_X64_BEHAVIOR },
#define PR_MAIN_X64_RCENTRY PR_MAIN_X64_RCID PR_MAIN_X64_RCTYPE PR_MAIN_X64_PATH

// arm64 is included only on arm64 builds
#if defined(_M_ARM64)
    #define PR_MAIN_ARM64_LISTENTRY { PR_MAIN_ARM64_ID, PR_MAIN_ARM64_TYPE, PR_MAIN_ARM64_BEHAVIOR },
    #define PR_MAIN_ARM64_RCENTRY PR_MAIN_ARM64_RC PR_MAIN_ARM64_RCTYPE PR_MAIN_ARM64_PATH
#endif

#define PR_DDLM_X86_LISTENTRY { PR_DDLM_X86_ID, PR_DDLM_X86_TYPE, PR_DDLM_X86_BEHAVIOR },
#define PR_DDLM_X86_RCENTRY PR_DDLM_X86_RCID PR_DDLM_X86_RCTYPE PR_DDLM_X86_PATH

#define PR_DDLM_X64_LISTENTRY  { PR_DDLM_X64_ID, PR_DDLM_X64_TYPE, PR_DDLM_X64_BEHAVIOR },
#define PR_DDLM_X64_RCENTRY PR_DDLM_X64_RCID PR_DDLM_X64_RCTYPE PR_DDLM_X64_PATH

// arm64 is included only on arm64 builds
#if defined(_M_ARM64)
    #define PR_DDLM_ARM64_LISTENTRY { PR_DDLM_ARM64_ID, PR_DDLM_ARM64_TYPE, PR_DDLM_ARM64_BEHAVIOR },
    #define PR_DDLM_ARM64_RCENTRY PR_DDLM_ARM64_RC PR_DDLM_ARM64_RCTYPE PR_DDLM_ARM64_PATH
#endif

// This is defined in the vcxproj based on existence of the header in the same directory.
// It is defined in both the c compiler preprocessor definitions and the resource compiler preprocessor definitions.
#ifdef USE_DEFINITIONS_OVERRIDE_HEADER
    #include "project_reunion_definitions_override.h"
#endif
