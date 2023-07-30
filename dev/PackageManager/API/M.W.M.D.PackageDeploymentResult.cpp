// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentResult.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentResult.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::guid PackageDeploymentResult::ActivityId()
    {
        throw hresult_not_implemented();
    }
}
