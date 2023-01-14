// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageGraph.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageGraph : PackageGraphT<PackageGraph>
    {
        PackageGraph() = default;

        PackageGraph(winrt::Microsoft::Windows::ApplicationModel::Package const& package);
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindRelatedPackages();
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindRelatedPackages(winrt::Microsoft::Windows::ApplicationModel::FindRelatedPackagesOptions const& options);

    private:
        winrt::Microsoft::Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageGraph : PackageGraphT<PackageGraph, implementation::PackageGraph>
    {
    };
}
