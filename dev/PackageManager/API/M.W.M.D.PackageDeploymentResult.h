// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageDeploymentResult.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageDeploymentResult : PackageDeploymentResultT<PackageDeploymentResult>
    {
        PackageDeploymentResult() = default;

        winrt::guid ActivityId();
    };
}
