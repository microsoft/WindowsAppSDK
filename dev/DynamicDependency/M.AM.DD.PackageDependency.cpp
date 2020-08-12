// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.AM.DD.PackageDependency.h"
#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependency.g.cpp"

#include "M.AM.DD.PackageDependencyContext.h"

#include <MsixDynamicDependency.h>
#include <wil/resource.h>
#include <wil_msixdynamicdependency.h>

#include <M.AM.Converters.h>

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    PackageDependency::PackageDependency(hstring const& id) :
        m_id(id)
    {
    }

    winrt::PackageDependency PackageDependency::GetFromId(hstring const& id)
    {
        return winrt::make<implementation::PackageDependency>(id);
    }

    winrt::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion)
    {
        const auto mddMinVersion{ ::Microsoft::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ MddPackageDependencyProcessorArchitectures::None };
        const auto mddLifetimeKind{ MddPackageDependencyLifetimeKind::Process };
        const auto mddOptions{ MddCreatePackageDependencyOptions::None };
        return Create(packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddOptions);
    }

    winrt::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options)
    {
        const auto mddMinVersion{ ::Microsoft::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ ::Microsoft::ApplicationModel::DynamicDependency::ToArchitectures(options.Architectures()) };
        const auto mddLifetimeKind{ ::Microsoft::ApplicationModel::DynamicDependency::ToLifetimeKind(options.LifetimeArtifactKind()) };
        const auto mddOptions{ ::Microsoft::ApplicationModel::DynamicDependency::ToCreateOptions(options) };
        return Create(packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddOptions);
    }

    winrt::PackageDependency PackageDependency::CreateForSystem(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options)
    {
        const auto mddMinVersion{ ::Microsoft::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ ::Microsoft::ApplicationModel::DynamicDependency::ToArchitectures(options.Architectures()) };
        const auto mddLifetimeKind{ ::Microsoft::ApplicationModel::DynamicDependency::ToLifetimeKind(options.LifetimeArtifactKind()) };
        auto mddOptions{ ::Microsoft::ApplicationModel::DynamicDependency::ToCreateOptions(options, MddCreatePackageDependencyOptions::ScopeIsSystem) };
        return Create(packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddOptions);
    }

    hstring PackageDependency::Id()
    {
        return m_id;
    }

    void PackageDependency::Delete()
    {
        MddDeletePackageDependency(m_id.c_str());
    }

    winrt::PackageDependencyContext PackageDependency::Add()
    {
        const auto rank{ MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT };
        const auto mddOptions{ MddAddPackageDependencyOptions::None };
        wil::unique_package_dependency_context packageDependencyContext;
        THROW_IF_FAILED(MddAddPackageDependency(m_id.c_str(), rank, mddOptions, &packageDependencyContext, nullptr));
        auto context{ winrt::make<implementation::PackageDependencyContext>(std::move(packageDependencyContext.get())) };
        packageDependencyContext.release();
        return context;
    }

    winrt::PackageDependencyContext PackageDependency::Add(Microsoft::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options)
    {
        const auto rank{ options.Rank() };
        const auto mddOptions{ ::Microsoft::ApplicationModel::DynamicDependency::ToAddOptions(options) };
        wil::unique_package_dependency_context packageDependencyContext;
        THROW_IF_FAILED(MddAddPackageDependency(m_id.c_str(), rank, mddOptions, &packageDependencyContext, nullptr));
        auto context{ winrt::make<implementation::PackageDependencyContext>(std::move(packageDependencyContext.get())) };
        packageDependencyContext.release();
        return context;
    }

    winrt::PackageDependency PackageDependency::Create(
        PCWSTR packageFamilyName,
        PACKAGE_VERSION minVersion,
        MddPackageDependencyProcessorArchitectures architectures,
        MddPackageDependencyLifetimeKind lifetimeKind,
        MddCreatePackageDependencyOptions options)
    {
        wil::unique_process_heap_string packageDependencyId;
        THROW_IF_FAILED(MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectures, lifetimeKind, nullptr, options, wil::out_param(packageDependencyId)));
        return GetFromId(packageDependencyId.get());
    }
}
