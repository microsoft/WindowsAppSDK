// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.RegisterPackageSetOptions.h"
#include "Microsoft.Windows.Management.Deployment.RegisterPackageSetOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel RegisterPackageSetOptions::DeploymentProcessingModel()
    {
        return m_deploymentProcessingModel;
    }
    void RegisterPackageSetOptions::DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value)
    {
        m_deploymentProcessingModel = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority RegisterPackageSetOptions::DeploymentPriority()
    {
        return m_deploymentPriority;
    }
    void RegisterPackageSetOptions::DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value)
    {
        m_deploymentPriority = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions RegisterPackageSetOptions::RegisterPackageOptions()
    {
        return m_registerPackageOptions;
    }
    void RegisterPackageSetOptions::RegisterPackageOptions(winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions const& value)
    {
        m_registerPackageOptions = value;
    }
}
