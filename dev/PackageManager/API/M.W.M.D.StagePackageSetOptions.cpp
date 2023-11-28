// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.StagePackageSetOptions.h"
#include "Microsoft.Windows.Management.Deployment.StagePackageSetOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel StagePackageSetOptions::DeploymentProcessingModel()
    {
        return m_deploymentProcessingModel;
    }
    void StagePackageSetOptions::DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value)
    {
        m_deploymentProcessingModel = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority StagePackageSetOptions::DeploymentPriority()
    {
        return m_deploymentPriority;
    }
    void StagePackageSetOptions::DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value)
    {
        m_deploymentPriority = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions StagePackageSetOptions::StagePackageOptions()
    {
        return m_stagePackageOptions;
    }
    void StagePackageSetOptions::StagePackageOptions(winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions const& value)
    {
        m_stagePackageOptions = value;
    }
}
