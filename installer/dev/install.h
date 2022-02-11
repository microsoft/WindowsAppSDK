// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "packages.h"
#include "InstallActivityContext.h"

namespace WindowsAppRuntimeInstaller {

    enum class Options
    {
        InstallPackages = 0x0001,
        InstallLicenses = 0x0002,
        Quiet           = 0x0004,
        DryRun          = 0x0008,
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

    HRESULT Deploy(const WindowsAppRuntimeInstaller::Options options) noexcept;

    HRESULT InstallLicenses(const WindowsAppRuntimeInstaller::Options options);

    HRESULT DeployPackages(const WindowsAppRuntimeInstaller::Options options);

    void ShowErrorMessage(const HRESULT hr);
}
