// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageRuntimeManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageRuntimeManager.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager PackageRuntimeManager::GetDefault()
    {
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageRuntimeManager>();
    }
    void PackageRuntimeManager::AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        throw hresult_not_implemented();
    }
    void PackageRuntimeManager::AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions)
    {
        throw hresult_not_implemented();
    }
    void PackageRuntimeManager::AddPackageSetById(hstring const& packageSetId)
    {
        throw hresult_not_implemented();
    }
    void PackageRuntimeManager::AddPackageSetById(hstring const& packageSetId, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions)
    {
        throw hresult_not_implemented();
    }
}
