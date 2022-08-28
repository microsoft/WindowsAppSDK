// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    struct PackageDependencyRank
    {
        PackageDependencyRank() = default;

        static int32_t Default();
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::factory_implementation
{
    struct PackageDependencyRank : PackageDependencyRankT<PackageDependencyRank, implementation::PackageDependencyRank>
    {
    };
}
