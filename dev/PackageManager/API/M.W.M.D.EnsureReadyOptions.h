// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.EnsureReadyOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct EnsureReadyOptions : EnsureReadyOptionsT<EnsureReadyOptions>
    {
        EnsureReadyOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions AddPackageOptions();
    private:
        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions m_addPackageOptions{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct EnsureReadyOptions : EnsureReadyOptionsT<EnsureReadyOptions, implementation::EnsureReadyOptions>
    {
    };
}
