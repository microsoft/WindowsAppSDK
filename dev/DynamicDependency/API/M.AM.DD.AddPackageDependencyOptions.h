// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions.g.h"

#include <MsixDynamicDependency.h>

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    struct AddPackageDependencyOptions : AddPackageDependencyOptionsT<AddPackageDependencyOptions>
    {
        AddPackageDependencyOptions() = default;

        int32_t Rank();
        void Rank(int32_t value);
        bool PrependIfRankCollision();
        void PrependIfRankCollision(bool value);

    private:
        int32_t m_rank{ MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT };
        bool m_prependIfRankCollision{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::factory_implementation
{
    struct AddPackageDependencyOptions : AddPackageDependencyOptionsT<AddPackageDependencyOptions, implementation::AddPackageDependencyOptions>
    {
    };
}
