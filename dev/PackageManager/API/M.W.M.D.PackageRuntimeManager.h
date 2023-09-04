// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageRuntimeManager.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageRuntimeManager : PackageRuntimeManagerT<PackageRuntimeManager>
    {
        PackageRuntimeManager() = default;

        static winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager GetDefault();
        winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions);
        winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition AddPackageSetById(hstring const& packageSetId);
        winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition AddPackageSetById(hstring const& packageSetId, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions);
    private:
        winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition AddPackageSetItem(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions);
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet) const;
        void Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem) const;
        void Validate(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options) const;
        void Validate(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options) const;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageRuntimeManager : PackageRuntimeManagerT<PackageRuntimeManager, implementation::PackageRuntimeManager>
    {
    };
}
