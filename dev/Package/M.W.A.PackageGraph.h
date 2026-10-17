// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageGraph.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageGraph
    {
        PackageGraph() = default;

        static hstring GetFilePath(hstring const& filename);
        static hstring GetFilePath(hstring const& filename, winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions const& options);
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageGraph : PackageGraphT<PackageGraph, implementation::PackageGraph>
    {
    };
}
