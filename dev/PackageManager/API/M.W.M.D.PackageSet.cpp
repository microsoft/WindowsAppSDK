// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageSet.h"
#include "Microsoft.Windows.Management.Deployment.PackageSet.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    hstring PackageSet::Id()
    {
        throw hresult_not_implemented();
    }
    void PackageSet::Id(hstring const& value)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItem> PackageSet::PackageSetItems()
    {
        throw hresult_not_implemented();
    }
    void PackageSet::PackageSetItems(winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItem> const& value)
    {
        throw hresult_not_implemented();
    }
}
