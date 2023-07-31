// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageDeploymentProgress.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageDeploymentProgress : PackageDeploymentProgressT<PackageDeploymentProgress>
    {
        PackageDeploymentProgress() = default;

        PackageDeploymentProgress(
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressState const& state,
            uint32_t percentage);

        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressState State();
        uint32_t Percentage();

    private:
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressState m_state{};
        uint32_t m_percentage{};
    };
}
