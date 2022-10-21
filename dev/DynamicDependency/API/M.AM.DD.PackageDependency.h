// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency.g.h"

#include "winrt_namespaces.h"

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    struct PackageDependency : PackageDependencyT<PackageDependency>
    {
        PackageDependency() = default;

        PackageDependency(hstring const& id);

        static winrt::PackageDependency GetFromId(hstring const& id);
        static winrt::PackageDependency GetFromIdForSystem(hstring const& id);
        static winrt::PackageDependency Create(hstring const& packageFamilyName, winrt::Windows::ApplicationModel::PackageVersion const& minVersion);
        static winrt::PackageDependency Create(hstring const& packageFamilyName, winrt::Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options);
        static winrt::PackageDependency CreateForSystem(hstring const& packageFamilyName, winrt::Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options);
        static uint32_t PackageGraphRevisionId();
        static uint32_t GenerationId();
        hstring Id();
        void Delete();
        winrt::PackageDependencyContext Add();
        winrt::PackageDependencyContext Add(Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options);

    private:
        static winrt::PackageDependency Create(
            PSID userSid,
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
namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::factory_implementation
{
    struct PackageDependency : PackageDependencyT<PackageDependency, implementation::PackageDependency>
    {
    };
}
