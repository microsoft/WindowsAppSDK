// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependency.g.h"

#include "winrt_namespaces.h"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    struct PackageDependency : PackageDependencyT<PackageDependency>
    {
        PackageDependency() = default;

        PackageDependency(hstring const& id);

        static winrt::PackageDependency GetFromId(hstring const& id);
        static winrt::PackageDependency Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion);
        static winrt::PackageDependency Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options);
        static winrt::PackageDependency CreateForSystem(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options);
        hstring Id();
        void Delete();
        winrt::PackageDependencyContext Add();
        winrt::PackageDependencyContext Add(Microsoft::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options);

    private:
        static winrt::PackageDependency Create(
            PCWSTR packageFamilyName,
            PACKAGE_VERSION minVersion,
            MddPackageDependencyProcessorArchitectures architectures,
            MddPackageDependencyLifetimeKind lifetimeKind,
            PCWSTR lifetimeArtifact,
            MddCreatePackageDependencyOptions options);

    private:
        hstring m_id;
    };
}
namespace winrt::Microsoft::ApplicationModel::DynamicDependency::factory_implementation
{
    struct PackageDependency : PackageDependencyT<PackageDependency, implementation::PackageDependency>
    {
    };
}
