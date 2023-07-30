// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentProgress.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentProgress.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressState PackageDeploymentProgress::State()
    {
        throw hresult_not_implemented();
    }
    uint32_t PackageDeploymentProgress::Percentage()
    {
        throw hresult_not_implemented();
    }
}
