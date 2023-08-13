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
        void AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        void AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions);
        void AddPackageSetById(hstring const& packageSetId);
        void AddPackageSetById(hstring const& packageSetId, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageRuntimeManager : PackageRuntimeManagerT<PackageRuntimeManager, implementation::PackageRuntimeManager>
    {
    };
}
