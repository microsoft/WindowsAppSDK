// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageRuntimeManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageRuntimeManager.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager PackageRuntimeManager::GetDefault()
    {
        throw hresult_not_implemented();
    }
    void PackageRuntimeManager::AddPackageSetByIdToPackageGraph(hstring const& packageSetId)
    {
        throw hresult_not_implemented();
    }
    void PackageRuntimeManager::AddPackageSetToPackageGraph(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        throw hresult_not_implemented();
    }
}
