// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependencyRank.g.h"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    struct PackageDependencyRank
    {
        PackageDependencyRank() = default;

        static int32_t Default();
    };
}
namespace winrt::Microsoft::ApplicationModel::DynamicDependency::factory_implementation
{
    struct PackageDependencyRank : PackageDependencyRankT<PackageDependencyRank, implementation::PackageDependencyRank>
    {
    };
}
