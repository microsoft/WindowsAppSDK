  #pragma once

// This header defines the packages included in the installer.
// By default, the project will use test packages built for verification of this installer.

// For building the installer with non-test packages, include a "windowsappsdk_definitions_override.h" file.
// If present, the override header will be loaded to change the package definitions such as the path.
// Preprocessor definitions used in the override header must be supported by the resource compiler.

// Override header file example:
//
// #pragma once
//
// #undef WAS_FRAMEWORK_X86_PATH
// #define WAS_FRAMEWORK_X86_PATH "custompackages\\my_custom_x86_framework.appx"
//

// Each package has a package definition listed below.
// Names for macros are intentionally kept short due to resource compiler length limitations.

// x86 Framework
#define WAS_FRAMEWORK_X86_ID L"WAS_FWPACKAGE_X86"
#define WAS_FRAMEWORK_X86_RCID WAS_FWPACKAGE_X86
#define WAS_FRAMEWORK_X86_TYPE L"PACKAGE"
#define WAS_FRAMEWORK_X86_RCTYPE PACKAGE
#define WAS_FRAMEWORK_X86_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_FRAMEWORK_X86_PATH
    #define WAS_FRAMEWORK_X86_PATH "..\\test\\testpackages\\framework_x86.msix"
#endif

// x64 Framework
#define WAS_FRAMEWORK_X64_ID L"WAS_FWPACKAGE_X64"
#define WAS_FRAMEWORK_X64_RCID WAS_FWPACKAGE_X64
#define WAS_FRAMEWORK_X64_TYPE L"PACKAGE"
#define WAS_FRAMEWORK_X64_RCTYPE PACKAGE
#define WAS_FRAMEWORK_X64_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_FRAMEWORK_X64_PATH
    #define WAS_FRAMEWORK_X64_PATH "..\\test\\testpackages\\framework_x64.msix"
#endif

// arm64 Framework
#define WAS_FRAMEWORK_ARM64_ID L"WAS_FWPACKAGE_ARM64"
#define WAS_FRAMEWORK_ARM64_RCID WAS_FWPACKAGE_ARM64
#define WAS_FRAMEWORK_ARM64_TYPE L"PACKAGE"
#define WAS_FRAMEWORK_ARM64_RCTYPE PACKAGE
#define WAS_FRAMEWORK_ARM64_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_FRAMEWORK_ARM64_PATH
    #define WAS_FRAMEWORK_ARM64_PATH "..\\test\\testpackages\\framework_arm64.msix"
#endif

// x86 Main
#define WAS_MAIN_X86_ID L"WAS_MAINPACKAGE_X86"
#define WAS_MAIN_X86_RCID WAS_MAINPACKAGE_X86
#define WAS_MAIN_X86_TYPE L"PACKAGE"
#define WAS_MAIN_X86_RCTYPE PACKAGE
#define WAS_MAIN_X86_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_MAIN_X86_PATH
    #define WAS_MAIN_X86_PATH "..\\test\\testpackages\\main_x86.msix"
#endif

// x64 Main
#define WAS_MAIN_X64_ID L"WAS_MAINPACKAGE_X64"
#define WAS_MAIN_X64_RCID WAS_MAINPACKAGE_X64
#define WAS_MAIN_X64_TYPE L"PACKAGE"
#define WAS_MAIN_X64_RCTYPE PACKAGE
#define WAS_MAIN_X64_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_MAIN_X64_PATH
    #define WAS_MAIN_X64_PATH "..\\test\\testpackages\\main_x64.msix"
#endif

// arm64 Main
#define WAS_MAIN_ARM64_ID L"WAS_MAINPACKAGE_ARM64"
#define WAS_MAIN_ARM64_RCID WAS_MAINPACKAGE_ARM64
#define WAS_MAIN_ARM64_TYPE L"PACKAGE"
#define WAS_MAIN_ARM64_RCTYPE PACKAGE
#define WAS_MAIN_ARM64_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_MAIN_ARM64_PATH
    #define WAS_MAIN_ARM64_PATH "..\\test\\testpackages\\main_arm64.msix"
#endif

// x86 Main
#define WAS_SINGLETON_X86_ID L"WAS_SINGLETONPACKAGE_X86"
#define WAS_SINGLETON_X86_RCID WAS_SINGLETONPACKAGE_X86
#define WAS_SINGLETON_X86_TYPE L"PACKAGE"
#define WAS_SINGLETON_X86_RCTYPE PACKAGE
#define WAS_SINGLETON_X86_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_SINGLETON_X86_PATH
    #define WAS_SINGLETON_X86_PATH "..\\test\\testpackages\\main_x86.msix"
#endif

// x64 Main
#define WAS_SINGLETON_X64_ID L"WAS_SINGLETONPACKAGE_X64"
#define WAS_SINGLETON_X64_RCID WAS_SINGLETONPACKAGE_X64
#define WAS_SINGLETON_X64_TYPE L"PACKAGE"
#define WAS_SINGLETON_X64_RCTYPE PACKAGE
#define WAS_SINGLETON_X64_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_SINGLETON_X64_PATH
    #define WAS_SINGLETON_X64_PATH "..\\test\\testpackages\\main_x64.msix"
#endif

// arm64 Main
#define WAS_SINGLETON_ARM64_ID L"WAS_SINGLETONPACKAGE_ARM64"
#define WAS_SINGLETON_ARM64_RCID WAS_SINGLETONPACKAGE_ARM64
#define WAS_SINGLETON_ARM64_TYPE L"PACKAGE"
#define WAS_SINGLETON_ARM64_RCTYPE PACKAGE
#define WAS_SINGLETON_ARM64_BEHAVIOR DeploymentBehavior::Default
#ifndef WAS_SINGLETON_ARM64_PATH
    #define WAS_SINGLETON_ARM64_PATH "..\\test\\testpackages\\main_arm64.msix"
#endif

// x86 DDLM
#define WAS_DDLM_X86_ID L"WAS_DDLMPACKAGE_X86"
#define WAS_DDLM_X86_RCID WAS_DDLMPACKAGE_X86
#define WAS_DDLM_X86_TYPE L"PACKAGE"
#define WAS_DDLM_X86_RCTYPE PACKAGE
#define WAS_DDLM_X86_BEHAVIOR DeploymentBehavior::Framework
#ifndef WAS_DDLM_X86_PATH
    #define WAS_DDLM_X86_PATH "..\\test\\testpackages\\ddlm_x86.msix"
#endif

// x64 DDLM
#define WAS_DDLM_X64_ID L"WAS_DDLMPACKAGE_X64"
#define WAS_DDLM_X64_RCID WAS_DDLMPACKAGE_X64
#define WAS_DDLM_X64_TYPE L"PACKAGE"
#define WAS_DDLM_X64_RCTYPE PACKAGE
#define WAS_DDLM_X64_BEHAVIOR DeploymentBehavior::Framework
#ifndef WAS_DDLM_X64_PATH
    #define WAS_DDLM_X64_PATH "..\\test\\testpackages\\ddlm_x64.msix"
#endif

// arm64 DDLM
#define WAS_DDLM_ARM64_ID L"WAS_DDLMPACKAGE_ARM64"
#define WAS_DDLM_ARM64_RCID WAS_DDLMPACKAGE_ARM64
#define WAS_DDLM_ARM64_TYPE L"PACKAGE"
#define WAS_DDLM_ARM64_RCTYPE PACKAGE
#define WAS_DDLM_ARM64_BEHAVIOR DeploymentBehavior::Framework
#ifndef WAS_DDLM_ARM64_PATH
    #define WAS_DDLM_ARM64_PATH "..\\test\\testpackages\\ddlm_arm64.msix"
#endif


// Package Inclusion
// Each package has a package list entry which defines its inclusion in packages.h and the .rc script.
// To not include a package, undefine the *_LISTENTRY and *_RCENTRY entries. At least one package must be included.

#define WAS_FRAMEWORK_X86_LISTENTRY { WAS_FRAMEWORK_X86_ID, WAS_FRAMEWORK_X86_TYPE, WAS_FRAMEWORK_X86_BEHAVIOR },
#define WAS_FRAMEWORK_X86_RCENTRY WAS_FRAMEWORK_X86_RCID WAS_FRAMEWORK_X86_RCTYPE WAS_FRAMEWORK_X86_PATH

#define WAS_FRAMEWORK_X64_LISTENTRY  { WAS_FRAMEWORK_X64_ID, WAS_FRAMEWORK_X64_TYPE, WAS_FRAMEWORK_X64_BEHAVIOR },
#define WAS_FRAMEWORK_X64_RCENTRY WAS_FRAMEWORK_X64_RCID WAS_FRAMEWORK_X64_RCTYPE WAS_FRAMEWORK_X64_PATH

// arm64 is included only on arm64 builds
#if defined(_M_ARM64)
    #define WAS_FRAMEWORK_ARM64_LISTENTRY { WAS_FRAMEWORK_ARM64_ID, WAS_FRAMEWORK_ARM64_TYPE, WAS_FRAMEWORK_ARM64_BEHAVIOR },
    #define WAS_FRAMEWORK_ARM64_RCENTRY WAS_FRAMEWORK_ARM64_RC WAS_FRAMEWORK_ARM64_RCTYPE WAS_FRAMEWORK_ARM64_PATH
#endif

#define WAS_MAIN_X86_LISTENTRY { WAS_MAIN_X86_ID, WAS_MAIN_X86_TYPE, WAS_MAIN_X86_BEHAVIOR },
#define WAS_MAIN_X86_RCENTRY WAS_MAIN_X86_RCID WAS_MAIN_X86_RCTYPE WAS_MAIN_X86_PATH

#define WAS_MAIN_X64_LISTENTRY  { WAS_MAIN_X64_ID, WAS_MAIN_X64_TYPE, WAS_MAIN_X64_BEHAVIOR },
#define WAS_MAIN_X64_RCENTRY WAS_MAIN_X64_RCID WAS_MAIN_X64_RCTYPE WAS_MAIN_X64_PATH

// arm64 is included only on arm64 builds
#if defined(_M_ARM64)
    #define WAS_MAIN_ARM64_LISTENTRY { WAS_MAIN_ARM64_ID, WAS_MAIN_ARM64_TYPE, WAS_MAIN_ARM64_BEHAVIOR },
    #define WAS_MAIN_ARM64_RCENTRY WAS_MAIN_ARM64_RC WAS_MAIN_ARM64_RCTYPE WAS_MAIN_ARM64_PATH
#endif

#define WAS_DDLM_X86_LISTENTRY { WAS_DDLM_X86_ID, WAS_DDLM_X86_TYPE, WAS_DDLM_X86_BEHAVIOR },
#define WAS_DDLM_X86_RCENTRY WAS_DDLM_X86_RCID WAS_DDLM_X86_RCTYPE WAS_DDLM_X86_PATH

#define WAS_DDLM_X64_LISTENTRY  { WAS_DDLM_X64_ID, WAS_DDLM_X64_TYPE, WAS_DDLM_X64_BEHAVIOR },
#define WAS_DDLM_X64_RCENTRY WAS_DDLM_X64_RCID WAS_DDLM_X64_RCTYPE WAS_DDLM_X64_PATH

// arm64 is included only on arm64 builds
#if defined(_M_ARM64)
    #define WAS_DDLM_ARM64_LISTENTRY { WAS_DDLM_ARM64_ID, WAS_DDLM_ARM64_TYPE, WAS_DDLM_ARM64_BEHAVIOR },
    #define WAS_DDLM_ARM64_RCENTRY WAS_DDLM_ARM64_RC WAS_DDLM_ARM64_RCTYPE WAS_DDLM_ARM64_PATH
#endif

// This is defined in the vcxproj based on existence of the header in the same directory.
// It is defined in both the c compiler preprocessor definitions and the resource compiler preprocessor definitions.
#ifdef USE_DEFINITIONS_OVERRIDE_HEADER
    #include "windowsappsdk_definitions_override.h"
#endif
