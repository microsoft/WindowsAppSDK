// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.RemovePackageSetOptions.h"
#include "Microsoft.Windows.Management.Deployment.RemovePackageSetOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel RemovePackageSetOptions::DeploymentProcessingModel()
    {
        return m_deploymentProcessingModel;
    }
    void RemovePackageSetOptions::DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value)
    {
        m_deploymentProcessingModel = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority RemovePackageSetOptions::DeploymentPriority()
    {
        return m_deploymentPriority;
    }
    void RemovePackageSetOptions::DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value)
    {
        m_deploymentPriority = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions RemovePackageSetOptions::RemovePackageOptions()
    {
        return m_removePackageOptions;
    }
    void RemovePackageSetOptions::RemovePackageOptions(winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions const& value)
    {
        m_removePackageOptions = value;
    }
}
