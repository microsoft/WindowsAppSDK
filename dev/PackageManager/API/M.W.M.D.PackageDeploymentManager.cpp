// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager PackageDeploymentManager::GetDefault()
    {
        throw hresult_not_implemented();
    }
    bool PackageDeploymentManager::IsReady(hstring const& packageSetId)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageDeploymentManager::EnsureIsReadyAsync(hstring packageSetId)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageDeploymentManager::AddPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageDeploymentManager::AddPackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options)
    {
        throw hresult_not_implemented();
    }
}
