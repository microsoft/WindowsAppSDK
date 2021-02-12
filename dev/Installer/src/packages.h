#pragma once
#include "pch.h"
#include "project_reunion_definitions.h"

using namespace winrt;
using namespace Windows::System;

// Information about the type of packages that are embedded
// More properties can be added as-needed, such as type - framework | main | appinstaller | bundle
// For now all packages are frameworks and only the processor architecture is meaningful.

struct ResourcePackageInfo
{
    std::wstring Id;
    std::wstring ResourceType;
};

static ResourcePackageInfo c_packages[] =
{
    { PROJECTREUNION_FRAMEWORK_X86_IDENTIFIER, PROJECTREUNION_FRAMEWORK_X86_TYPE },
    { PROJECTREUNION_FRAMEWORK_X64_IDENTIFIER, PROJECTREUNION_FRAMEWORK_X64_TYPE },
};