// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.AM.DD.PackageDependency.h"
#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependency.g.cpp"

#include "M.AM.DD.PackageDependencyContext.h"

#include "PackageDependencyManager.h"

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
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
        auto exists{ MddCore::PackageDependencyManager::ExistsPackageDependency(tokenUser->User.Sid, id.c_str()) };
        if (!exists)
        {
            return nullptr;
        }
        return winrt::make<implementation::PackageDependency>(id);
    }

    winrt::PackageDependency PackageDependency::GetFromIdForSystem(hstring const& id)
    {
        auto exists{ MddCore::PackageDependencyManager::ExistsPackageDependency(nullptr, id.c_str()) };
        if (!exists)
        {
            return nullptr;
        }
        return winrt::make<implementation::PackageDependency>(id);
    }

    winrt::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion)
    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
        const auto mddMinVersion{ ::Microsoft::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ MddPackageDependencyProcessorArchitectures::None };
        const auto mddLifetimeKind{ MddPackageDependencyLifetimeKind::Process };
        const PCWSTR mddLifetimeArtifact{};
        const auto mddOptions{ MddCreatePackageDependencyOptions::None };
        return Create(tokenUser->User.Sid, packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddLifetimeArtifact, mddOptions);
    }

    winrt::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options)
    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
        const auto mddMinVersion{ ::Microsoft::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ ::Microsoft::ApplicationModel::DynamicDependency::ToArchitectures(options.Architectures()) };
        const auto mddLifetimeKind{ ::Microsoft::ApplicationModel::DynamicDependency::ToLifetimeKind(options.LifetimeArtifactKind()) };
        const auto mddLifetimeArtifact{ options.LifetimeArtifact().c_str() };
        const auto mddOptions{ ::Microsoft::ApplicationModel::DynamicDependency::ToCreateOptions(options) };
        return Create(tokenUser->User.Sid, packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddLifetimeArtifact, mddOptions);
    }

    winrt::PackageDependency PackageDependency::CreateForSystem(hstring const& packageFamilyName, Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options)
    {
        const auto mddMinVersion{ ::Microsoft::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ ::Microsoft::ApplicationModel::DynamicDependency::ToArchitectures(options.Architectures()) };
        const auto mddLifetimeKind{ ::Microsoft::ApplicationModel::DynamicDependency::ToLifetimeKind(options.LifetimeArtifactKind()) };
        const auto mddLifetimeArtifact{ options.LifetimeArtifact().c_str() };
        auto mddOptions{ ::Microsoft::ApplicationModel::DynamicDependency::ToCreateOptions(options, MddCreatePackageDependencyOptions::ScopeIsSystem) };
        return Create(nullptr, packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddLifetimeArtifact, mddOptions);
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
        PSID userSid,
        PCWSTR packageFamilyName,
        PACKAGE_VERSION minVersion,
        MddPackageDependencyProcessorArchitectures architectures,
        MddPackageDependencyLifetimeKind lifetimeKind,
        PCWSTR lifetimeArtifact,
        MddCreatePackageDependencyOptions options)
    {
        wil::unique_process_heap_string packageDependencyId;
        THROW_IF_FAILED(MddTryCreatePackageDependency(userSid, packageFamilyName, minVersion, architectures, lifetimeKind, lifetimeArtifact, options, wil::out_param(packageDependencyId)));
        return GetFromId(packageDependencyId.get());
    }
}
