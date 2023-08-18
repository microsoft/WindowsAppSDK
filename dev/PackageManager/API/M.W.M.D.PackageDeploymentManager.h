// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageDeploymentManager : PackageDeploymentManagerT<PackageDeploymentManager>
    {
        PackageDeploymentManager() = default;

        static winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager GetDefault();
        bool IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        bool IsReadyByPackageSetId(hstring const& packageSetId);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsureIsReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> EnsureIsReadyByPackageSetIdAsync(hstring packageSetId);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options);
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> AddPackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options);

    private:
        bool IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSet);
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem);
        void EnsureIsReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem);

    private:
        winrt::Windows::Management::Deployment::PackageManager m_packageManager;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageDeploymentManager : PackageDeploymentManagerT<PackageDeploymentManager, implementation::PackageDeploymentManager>
    {
    };
}
