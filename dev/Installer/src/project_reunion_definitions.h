#pragma once

// x86 Framework
#define PROJECTREUNION_FRAMEWORK_X86_IDENTIFIER L"PR_FWPACKAGE_X86"
#define PROJECTREUNION_FRAMEWORK_X86_RCIDENTIFIER PR_FWPACKAGE_X86
#define PROJECTREUNION_FRAMEWORK_X86_TYPE L"PACKAGE"
#define PROJECTREUNION_FRAMEWORK_X86_RCTYPE PACKAGE
#define PROJECTREUNION_FRAMEWORK_X86_PATH "..\\releasedpackages\\0.1\\x86\\Microsoft.ProjectReunion.0.1.appx"

// x64 Framework
#define PROJECTREUNION_FRAMEWORK_X64_IDENTIFIER L"PR_FWPACKAGE_X64"
#define PROJECTREUNION_FRAMEWORK_X64_RCIDENTIFIER PR_FWPACKAGE_X64
#define PROJECTREUNION_FRAMEWORK_X64_TYPE L"PACKAGE"
#define PROJECTREUNION_FRAMEWORK_X64_RCTYPE PACKAGE
#define PROJECTREUNION_FRAMEWORK_X64_PATH "..\\releasedpackages\\0.1\\x64\\Microsoft.ProjectReunion.0.1.appx"

// The paths above are required to exist in order for this installer to build successfully. Appx packages are
// ignored from git and this is not a release share. Place the appropriate packages in the above path, or
// use the override header described below to change the input paths for the packages.

// For inner loop or other builds, include a "project_reunion_definitions_override.h" with the updated package locations.
// Preprocessor definitions used must be supported by the resource compiler.
// Override file example:
//
// #pragma once
//
// #undef PROJECTREUNION_FRAMEWORK_X86_PATH
// #define PROJECTREUNION_FRAMEWORK_X86_PATH "Packages\\my_custom_x86_framework.appx"
// 

// This is defined in the vcxproj based on existence of the header in the same directory.
// It is defined in both the c compiler preprocessor definitions and the resource compiler preprocessor definitions.
#ifdef USE_DEFINITIONS_OVERRIDE_HEADER
    #include "project_reunion_definitions_override.h"
#endif

