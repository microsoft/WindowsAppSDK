// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageGraph.h"

#include "Microsoft.Windows.ApplicationModel.PackageGraph.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageGraph::PackageGraph(winrt::Microsoft::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> PackageGraph::FindRelatedPackages()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> PackageGraph::FindRelatedPackages(winrt::Microsoft::Windows::ApplicationModel::FindRelatedPackagesOptions const& options)
    {
        throw hresult_not_implemented();
    }
}
