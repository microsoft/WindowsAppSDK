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
#define PR_FRAMEWORK_X86_PATH "..\\test\\testpackages\\framework_x86.msix"

// x64 Framework
#define PR_FRAMEWORK_X64_ID L"PR_FWPACKAGE_X64"
#define PR_FRAMEWORK_X64_RCID PR_FWPACKAGE_X64
#define PR_FRAMEWORK_X64_TYPE L"PACKAGE"
#define PR_FRAMEWORK_X64_RCTYPE PACKAGE
#define PR_FRAMEWORK_X64_PATH "..\\test\\testpackages\\framework_x64.msix"

// arm64 Framework
#define PR_FRAMEWORK_ARM64_ID L"PR_FWPACKAGE_ARM64"
#define PR_FRAMEWORK_ARM64_RCID PR_FWPACKAGE_ARM64
#define PR_FRAMEWORK_ARM64_TYPE L"PACKAGE"
#define PR_FRAMEWORK_ARM64_RCTYPE PACKAGE
#define PR_FRAMEWORK_ARM64_PATH "..\\test\\testpackages\\framework_arm64.msix"

// Package Inclusion
// Each package has a package list entry which defines its inclusion in packages.h and the .rc script.
// To not include a package, undefine the *_LISTENTRY and *_RCENTRY entries. At least one package must be included.

// x86 is included on all architecture flavors
#define PR_FRAMEWORK_X86_LISTENTRY { PR_FRAMEWORK_X86_ID, PR_FRAMEWORK_X86_TYPE },
#define PR_FRAMEWORK_X86_RCENTRY PR_FRAMEWORK_X86_RCID PR_FRAMEWORK_X86_RCTYPE PR_FRAMEWORK_X86_PATH

// x64 is included on all architecture flavors
#define PR_FRAMEWORK_X64_LISTENTRY  { PR_FRAMEWORK_X64_ID, PR_FRAMEWORK_X64_TYPE },
#define PR_FRAMEWORK_X64_RCENTRY PR_FRAMEWORK_X64_RCID PR_FRAMEWORK_X64_RCTYPE PR_FRAMEWORK_X64_PATH

// arm64 is included only on arm64 builds
#if defined(_M_ARM64)
    #define PR_FRAMEWORK_ARM64_LISTENTRY { PR_FRAMEWORK_ARM64_ID, PR_FRAMEWORK_ARM64_TYPE },
    #define PR_FRAMEWORK_ARM64_RCENTRY PR_FRAMEWORK_ARM64_RC     PR_FRAMEWORK_ARM64_RCTYPE                 PR_FRAMEWORK_ARM64_PATH
#endif

// This is defined in the vcxproj based on existence of the header in the same directory.
// It is defined in both the c compiler preprocessor definitions and the resource compiler preprocessor definitions.
#ifdef USE_DEFINITIONS_OVERRIDE_HEADER
    #include "project_reunion_definitions_override.h"
#endif
