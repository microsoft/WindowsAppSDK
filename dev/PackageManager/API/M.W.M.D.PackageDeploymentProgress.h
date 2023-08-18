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
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus const& status,
            uint32_t percentage);

        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus status();
        void status(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus const& value);
        uint32_t percentage();
        void percentage(uint32_t value);

    private:
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus m_status{};
        uint32_t m_percentage{};
    };
}
