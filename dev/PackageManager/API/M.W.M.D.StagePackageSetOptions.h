// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.StagePackageSetOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct StagePackageSetOptions : StagePackageSetOptionsT<StagePackageSetOptions>
    {
        StagePackageSetOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel DeploymentProcessingModel();
        void DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority DeploymentPriority();
        void DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value);
        winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions StagePackageOptions();
        void StagePackageOptions(winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions const& value);

    private:
        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel m_deploymentProcessingModel{ winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel::Sequential };
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority m_deploymentPriority{ winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority::Normal };
        winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions m_stagePackageOptions;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct StagePackageSetOptions : StagePackageSetOptionsT<StagePackageSetOptions, implementation::StagePackageSetOptions>
    {
    };
}
