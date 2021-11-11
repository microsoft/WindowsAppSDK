#pragma once
#include "pch.h"
#include "packages.h"

namespace WindowsAppRuntimeInstaller {

    enum class Options
    {
        InstallPackages = 0x0001,
        InstallLicenses = 0x0002,
        Quiet           = 0x0004,
    };
    DEFINE_ENUM_FLAG_OPERATORS(Options)

    struct PackageProperties
    {
        wil::unique_cotaskmem_string fullName;
        wil::unique_cotaskmem_string familyName;
        winrt::Windows::System::ProcessorArchitecture architecture{ winrt::Windows::System::ProcessorArchitecture::Unknown };
        std::uint64_t version{};
        bool isFramework{};
    };

    HRESULT DeployPackages(const WindowsAppRuntimeInstaller::Options options) noexcept;

    HRESULT InstallLicenses(const WindowsAppRuntimeInstaller::Options options) noexcept;
}
