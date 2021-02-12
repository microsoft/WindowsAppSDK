#pragma once
#include "pch.h"
#include "packages.h"

struct PackageProperties
{
    wil::unique_cotaskmem_string full_name;
    wil::unique_cotaskmem_string family_name;
    winrt::Windows::System::ProcessorArchitecture architecture = winrt::Windows::System::ProcessorArchitecture::Unknown;
    UINT64 version = 0u;
};

winrt::hresult deploy_package_from_resource(ResourcePackageInfo, bool) noexcept;
