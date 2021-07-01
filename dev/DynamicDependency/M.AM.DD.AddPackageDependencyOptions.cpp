// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.AM.DD.AddPackageDependencyOptions.h"
#include "Microsoft.ApplicationModel.DynamicDependency.AddPackageDependencyOptions.g.cpp"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    int32_t AddPackageDependencyOptions::Rank()
    {
        return m_rank;
    }

    void AddPackageDependencyOptions::Rank(int32_t value)
    {
        m_rank = value;
    }

    bool AddPackageDependencyOptions::PrependIfRankCollision()
    {
        return m_prependIfRankCollision;
    }

    void AddPackageDependencyOptions::PrependIfRankCollision(bool value)
    {
        m_prependIfRankCollision = value;
    }
}
