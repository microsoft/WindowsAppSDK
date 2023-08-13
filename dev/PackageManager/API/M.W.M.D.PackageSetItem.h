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

        winrt::Windows::Foundation::Uri PackageUri();
        void PackageUri(winrt::Windows::Foundation::Uri const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel DeploymentProcessingModel();
        void DeploymentProcessingModel(winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel const& value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority DeploymentPriority();
        void DeploymentPriority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value);

    private:
        hstring m_id;
        hstring m_packageFamilyName;
        winrt::Windows::ApplicationModel::PackageVersion m_minVersion{};
        winrt::Windows::Management::Deployment::PackageTypes m_packageTypeFilter{};
        winrt::Windows::Foundation::Uri m_packageUri{ nullptr };
        winrt::Microsoft::Windows::Management::Deployment::DeploymentProcessingModel m_deploymentProcessingModel{};
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority m_deploymentPriority{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageSetItem : PackageSetItemT<PackageSetItem, implementation::PackageSetItem>
    {
    };
}
