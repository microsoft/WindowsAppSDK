// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentProgress.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentProgress.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageDeploymentProgress::PackageDeploymentProgress(
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressState const& state,
        uint32_t percentage) :
        m_state(state),
        m_percentage(percentage)
    {
    }

    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressState PackageDeploymentProgress::State()
    {
        return m_state;
    }

    uint32_t PackageDeploymentProgress::Percentage()
    {
        return m_percentage;
    }
}
