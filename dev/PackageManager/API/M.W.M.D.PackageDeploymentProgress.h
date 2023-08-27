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
            double percentage);

        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus status();
        void status(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus const& value);
        double percentage();
        void percentage(double value);

    private:
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus m_status{};
        double m_percentage{};
    };
}
