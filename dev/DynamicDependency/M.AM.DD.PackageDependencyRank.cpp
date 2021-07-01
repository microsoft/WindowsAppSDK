// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.AM.DD.PackageDependencyRank.h"
#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependencyRank.g.cpp"

#include <MsixDynamicDependency.h>

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    int32_t PackageDependencyRank::Default()
    {
        return MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT;
    }
}
