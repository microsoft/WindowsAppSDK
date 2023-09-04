// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageSetManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageSetManager.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageSetManager PackageSetManager::GetDefault()
    {
        throw hresult_not_implemented();
    }
    void PackageSetManager::Add(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        throw hresult_not_implemented();
    }
    void PackageSetManager::Update(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        throw hresult_not_implemented();
    }
    void PackageSetManager::Remove(hstring const& packageSetId)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageSet PackageSetManager::Get(hstring const& packageSetId)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSet> PackageSetManager::Find(winrt::Microsoft::Windows::Management::Deployment::FindPackageSetOptions const& options)
    {
        throw hresult_not_implemented();
    }
}
