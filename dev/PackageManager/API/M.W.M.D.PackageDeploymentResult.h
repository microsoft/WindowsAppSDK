// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageDeploymentResult.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageDeploymentResult : PackageDeploymentResultT<PackageDeploymentResult>
    {
        PackageDeploymentResult() = default;
        PackageDeploymentResult(
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus status,
            winrt::guid const& activityId);
        PackageDeploymentResult(
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus status,
            winrt::guid const& activityId,
            winrt::hresult const& error,
            winrt::hresult const& extendedError,
            winrt::hstring const& errorText);

        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus Status();
        winrt::hresult Error();
        winrt::hresult ExtendedError();
        winrt::hstring ErrorText();
        winrt::guid ActivityId();

    private:
        PackageDeploymentStatus m_status{};
        winrt::hresult m_error;
        winrt::hresult m_extendedError;
        winrt::hstring m_errorText;
        winrt::guid m_activityId{};
    };
}
