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
        winrt::Windows::Foundation::Uri PackageUri();
        void PackageUri(winrt::Windows::Foundation::Uri const& value);
        hstring PackageFamilyName();
        void PackageFamilyName(hstring const& value);
        winrt::Windows::ApplicationModel::PackageVersion MinVersion();
        void MinVersion(winrt::Windows::ApplicationModel::PackageVersion const& value);
        winrt::Windows::Management::Deployment::PackageTypes PackageTypeFilter();
        void PackageTypeFilter(winrt::Windows::Management::Deployment::PackageTypes const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel DeploymentProcessingModel();
        void DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority DeploymentPriority();
        void DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageSetItem : PackageSetItemT<PackageSetItem, implementation::PackageSetItem>
    {
    };
}
