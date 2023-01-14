// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.FindRelatedPackagesOptions.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct FindRelatedPackagesOptions : FindRelatedPackagesOptionsT<FindRelatedPackagesOptions>
    {
        FindRelatedPackagesOptions() = default;

        FindRelatedPackagesOptions(winrt::Microsoft::Windows::ApplicationModel::PackageRelationship const& Relationship);
        winrt::Microsoft::Windows::ApplicationModel::PackageRelationship Relationship();
        void Relationship(winrt::Microsoft::Windows::ApplicationModel::PackageRelationship const& value);
        bool IncludeFrameworks();
        void IncludeFrameworks(bool value);
        bool IncludeHostRuntimes();
        void IncludeHostRuntimes(bool value);
        bool IncludeOptionals();
        void IncludeOptionals(bool value);
        bool IncludeResources();
        void IncludeResources(bool value);

    private:
        winrt::Microsoft::Windows::ApplicationModel::PackageRelationship m_relationship{ winrt::Microsoft::Windows::ApplicationModel::PackageRelationship::Dependencies };
        bool m_includeFrameworks{};
        bool m_includeHostRuntimes{};
        bool m_includeOptionals{};
        bool m_includeResources{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct FindRelatedPackagesOptions : FindRelatedPackagesOptionsT<FindRelatedPackagesOptions, implementation::FindRelatedPackagesOptions>
    {
    };
}
