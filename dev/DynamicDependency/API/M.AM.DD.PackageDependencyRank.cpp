// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.AM.DD.PackageDependencyRank.h"
#include "Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank.g.cpp"

#include <MsixDynamicDependency.h>

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    int32_t PackageDependencyRank::Default()
    {
        return MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT;
    }
}
