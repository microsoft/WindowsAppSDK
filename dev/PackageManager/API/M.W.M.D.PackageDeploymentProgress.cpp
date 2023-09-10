// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentProgress.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentProgress.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageDeploymentProgress::PackageDeploymentProgress(
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus const& status,
        double percentage) :
        m_status(status),
        m_percentage(percentage)
    {
    }

    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus PackageDeploymentProgress::status()
    {
        return m_status;
    }
    void PackageDeploymentProgress::status(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus const& value)
    {
        m_status = value;
    }
    double PackageDeploymentProgress::percentage()
    {
        return m_percentage;
    }
    void PackageDeploymentProgress::percentage(double value)
    {
        m_percentage = value;
    }
}
