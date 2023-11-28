// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.RemovePackageSetOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct RemovePackageSetOptions : RemovePackageSetOptionsT<RemovePackageSetOptions>
    {
        RemovePackageSetOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel DeploymentProcessingModel();
        void DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority DeploymentPriority();
        void DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value);
        winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions RemovePackageOptions();
        void RemovePackageOptions(winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions const& value);

    private:
        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel m_deploymentProcessingModel{ winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel::Sequential };
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority m_deploymentPriority{ winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority::Normal };
        winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions m_removePackageOptions;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct RemovePackageSetOptions : RemovePackageSetOptionsT<RemovePackageSetOptions, implementation::RemovePackageSetOptions>
    {
    };
}
