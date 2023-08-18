// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageDeploymentResult.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageDeploymentResult : PackageDeploymentResultT<PackageDeploymentResult>
    {
        PackageDeploymentResult() = default;
        PackageDeploymentResult(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus status, winrt::hresult const& extendedError, winrt::guid const& activityId);

        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus Status();
        winrt::hresult ExtendedError();
        winrt::guid ActivityId();

    private:
        PackageDeploymentStatus m_status{};
        const winrt::hresult m_extendedError;
        winrt::guid m_activityId{};
    };
}
