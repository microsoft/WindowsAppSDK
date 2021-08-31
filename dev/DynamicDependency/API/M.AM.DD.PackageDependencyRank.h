// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
