// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.AddPackageSetOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct AddPackageSetOptions : AddPackageSetOptionsT<AddPackageSetOptions>
    {
        AddPackageSetOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel DeploymentProcessingModel();
        void DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority DeploymentPriority();
        void DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value);
        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions AddPackageOptions();
        void AddPackageOptions(winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& value);

    private:
        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel m_deploymentProcessingModel{};
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority m_deploymentPriority{ winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority::Normal };
        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions m_addPackageOptions{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct AddPackageSetOptions : AddPackageSetOptionsT<AddPackageSetOptions, implementation::AddPackageSetOptions>
    {
    };
}
