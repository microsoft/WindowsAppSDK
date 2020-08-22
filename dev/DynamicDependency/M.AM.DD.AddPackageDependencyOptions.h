// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.ApplicationModel.DynamicDependency.AddPackageDependencyOptions.g.h"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    struct AddPackageDependencyOptions : AddPackageDependencyOptionsT<AddPackageDependencyOptions>
    {
        AddPackageDependencyOptions() = default;

        int32_t Rank();
        void Rank(int32_t value);
        bool PrependIfRankCollision();
        void PrependIfRankCollision(bool value);
    };
}
namespace winrt::Microsoft::ApplicationModel::DynamicDependency::factory_implementation
{
    struct AddPackageDependencyOptions : AddPackageDependencyOptionsT<AddPackageDependencyOptions, implementation::AddPackageDependencyOptions>
    {
    };
}
