// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.EnsureIsReadyOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct EnsureIsReadyOptions : EnsureIsReadyOptionsT<EnsureIsReadyOptions>
    {
        EnsureIsReadyOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel DeploymentProcessingModel();
        void DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority DeploymentPriority();
        void DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value);

    private:
        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel m_deploymentProcessingModel{};
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority m_deploymentPriority{ winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority::Normal };
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct EnsureIsReadyOptions : EnsureIsReadyOptionsT<EnsureIsReadyOptions, implementation::EnsureIsReadyOptions>
    {
    };
}
