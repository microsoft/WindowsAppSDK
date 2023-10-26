// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.AddPackageSetOptions.h"
#include "Microsoft.Windows.Management.Deployment.AddPackageSetOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel AddPackageSetOptions::DeploymentProcessingModel()
    {
        return m_deploymentProcessingModel;
    }
    void AddPackageSetOptions::DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value)
    {
        m_deploymentProcessingModel = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority AddPackageSetOptions::DeploymentPriority()
    {
        return m_deploymentPriority;
    }
    void AddPackageSetOptions::DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value)
    {
        m_deploymentPriority = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions AddPackageSetOptions::AddPackageOptions()
    {
        return m_addPackageOptions;
    }
    void AddPackageSetOptions::AddPackageOptions(winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& value)
    {
        m_addPackageOptions = value;
    }
}
