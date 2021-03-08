#pragma once
#include "pch.h"
#include "packages.h"

namespace ProjectReunionInstaller {

    struct PackageProperties
    {
        wil::unique_cotaskmem_string fullName;
        wil::unique_cotaskmem_string familyName;
        winrt::Windows::System::ProcessorArchitecture architecture{ winrt::Windows::System::ProcessorArchitecture::Unknown };
        std::uint64_t version{};
    };

    HRESULT DeployPackages(const bool quiet) noexcept;
}
