// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.AM.DD.AddPackageDependencyOptions.h"
#include "Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
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
