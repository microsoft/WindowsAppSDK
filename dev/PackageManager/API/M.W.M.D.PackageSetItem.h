// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageSetItem.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageSetItem : PackageSetItemT<PackageSetItem>
    {
        PackageSetItem() = default;

        hstring Id();
        void Id(hstring const& value);
        hstring PackageFamilyName();
        void PackageFamilyName(hstring const& value);
        winrt::Windows::ApplicationModel::PackageVersion MinVersion();
        void MinVersion(winrt::Windows::ApplicationModel::PackageVersion const& value);
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures ProcessorArchitectureFilter();
        void ProcessorArchitectureFilter(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures const& value);
        winrt::Windows::Foundation::Uri PackageUri();
        void PackageUri(winrt::Windows::Foundation::Uri const& value);

    private:
        hstring m_id;
        hstring m_packageFamilyName;
        winrt::Windows::ApplicationModel::PackageVersion m_minVersion{};
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures m_processorArchitectureFilter{};
        winrt::Windows::Foundation::Uri m_packageUri{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageSetItem : PackageSetItemT<PackageSetItem, implementation::PackageSetItem>
    {
    };
}
