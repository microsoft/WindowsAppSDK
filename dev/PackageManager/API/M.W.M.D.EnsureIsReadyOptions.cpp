// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "M.W.M.D.EnsureIsReadyOptions.h"
#include "Microsoft.Windows.Management.Deployment.EnsureIsReadyOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel EnsureIsReadyOptions::DeploymentProcessingModel()
    {
        return m_deploymentProcessingModel;
    }
    void EnsureIsReadyOptions::DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value)
    {
        m_deploymentProcessingModel = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority EnsureIsReadyOptions::DeploymentPriority()
    {
        return m_deploymentPriority;
    }
    void EnsureIsReadyOptions::DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value)
    {
        m_deploymentPriority = value;
    }
}
