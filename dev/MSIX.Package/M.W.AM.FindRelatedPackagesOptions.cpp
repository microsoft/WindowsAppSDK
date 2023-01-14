// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.FindRelatedPackagesOptions.h"

#include "Microsoft.Windows.ApplicationModel.FindRelatedPackagesOptions.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    FindRelatedPackagesOptions::FindRelatedPackagesOptions(winrt::Microsoft::Windows::ApplicationModel::PackageRelationship const& Relationship) :
        m_relationship(Relationship)
    {
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageRelationship FindRelatedPackagesOptions::Relationship()
    {
        return m_relationship;
    }
    void FindRelatedPackagesOptions::Relationship(winrt::Microsoft::Windows::ApplicationModel::PackageRelationship const& value)
    {
        m_relationship = value;
    }
    bool FindRelatedPackagesOptions::IncludeFrameworks()
    {
        return m_includeFrameworks;
    }
    void FindRelatedPackagesOptions::IncludeFrameworks(bool value)
    {
        m_includeFrameworks = value;
    }
    bool FindRelatedPackagesOptions::IncludeHostRuntimes()
    {
        return m_includeHostRuntimes;
    }
    void FindRelatedPackagesOptions::IncludeHostRuntimes(bool value)
    {
        m_includeHostRuntimes = value;
    }
    bool FindRelatedPackagesOptions::IncludeOptionals()
    {
        return m_includeOptionals;
    }
    void FindRelatedPackagesOptions::IncludeOptionals(bool value)
    {
        m_includeOptionals = value;
    }
    bool FindRelatedPackagesOptions::IncludeResources()
    {
        return m_includeResources;
    }
    void FindRelatedPackagesOptions::IncludeResources(bool value)
    {
        m_includeResources = value;
    }
}
