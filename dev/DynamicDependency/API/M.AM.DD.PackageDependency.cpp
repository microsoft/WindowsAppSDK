// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.AM.DD.PackageDependency.h"
#include "Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency.g.cpp"

#include "M.AM.DD.PackageDependencyContext.h"

#include "PackageDependencyManager.h"

#include <MsixDynamicDependency.h>
#include <wil/resource.h>
#include <wil_msixdynamicdependency.h>

#include <M.AM.Converters.h>

#include "MddWin11.h"

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    PackageDependency::PackageDependency(hstring const& id) :
        m_id(id)
    {
    }

    winrt::PackageDependency PackageDependency::GetFromId(hstring const& id)
    {
        // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
        if (MddCore::Win11::IsSupported())
        {
            //TODO:47775758 GetResolved2 GetPackageDependencyInfo2(userSid, id.c_str(), &packageDependencyInfo)
        }
        else
        {
            auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
            auto exists{ MddCore::PackageDependencyManager::ExistsPackageDependency(tokenUser->User.Sid, id.c_str()) };
            if (!exists)
            {
                return nullptr;
            }
        }
        return winrt::make<implementation::PackageDependency>(id);
    }

    winrt::PackageDependency PackageDependency::GetFromIdForSystem(hstring const& id)
    {
        // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
        if (MddCore::Win11::IsSupported())
        {
            //TODO:47775758 GetResolved2 GetPackageDependencyInfo2(userSid, id.c_str(), &packageDependencyInfo)
        }
        else
        {
            auto exists{ MddCore::PackageDependencyManager::ExistsPackageDependency(nullptr, id.c_str()) };
            if (!exists)
            {
                return nullptr;
            }
        }
        return winrt::make<implementation::PackageDependency>(id);
    }

    winrt::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, winrt::Windows::ApplicationModel::PackageVersion const& minVersion)
    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
        const auto mddMinVersion{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ MddPackageDependencyProcessorArchitectures::None };
        const auto mddLifetimeKind{ MddPackageDependencyLifetimeKind::Process };
        const PCWSTR mddLifetimeArtifact{};
        const auto mddOptions{ MddCreatePackageDependencyOptions::None };
        return Create(tokenUser->User.Sid, packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddLifetimeArtifact, mddOptions);
    }

    winrt::PackageDependency PackageDependency::Create(hstring const& packageFamilyName, winrt::Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options)
    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
        const auto mddMinVersion{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToArchitectures(options.Architectures()) };
        const auto mddLifetimeKind{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToLifetimeKind(options.LifetimeArtifactKind()) };
        const auto mddLifetimeArtifact{ options.LifetimeArtifact().c_str() };
        const auto mddOptions{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToCreateOptions(options) };
        return Create(tokenUser->User.Sid, packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddLifetimeArtifact, mddOptions);
    }

    winrt::PackageDependency PackageDependency::CreateForSystem(hstring const& packageFamilyName, winrt::Windows::ApplicationModel::PackageVersion const& minVersion, winrt::CreatePackageDependencyOptions const& options)
    {
        const auto mddMinVersion{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToVersion(minVersion) };
        const auto mddArchitectures{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToArchitectures(options.Architectures()) };
        const auto mddLifetimeKind{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToLifetimeKind(options.LifetimeArtifactKind()) };
        const auto mddLifetimeArtifact{ options.LifetimeArtifact().c_str() };
        auto mddOptions{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToCreateOptions(options, MddCreatePackageDependencyOptions::ScopeIsSystem) };
        return Create(nullptr, packageFamilyName.c_str(), mddMinVersion, mddArchitectures, mddLifetimeKind, mddLifetimeArtifact, mddOptions);
    }

    uint32_t PackageDependency::PackageGraphRevisionId()
    {
        return MddGetPackageGraphRevisionId();
    }

    uint32_t PackageDependency::GenerationId()
    {
        return PackageGraphRevisionId();
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
        wil::unique_mdd_package_dependency_context packageDependencyContext;
        winrt::check_hresult(MddAddPackageDependency(m_id.c_str(), rank, mddOptions, &packageDependencyContext, nullptr));
        auto context{ winrt::make<implementation::PackageDependencyContext>(packageDependencyContext.get()) };
        packageDependencyContext.release();
        return context;
    }

    winrt::PackageDependencyContext PackageDependency::Add(Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options)
    {
        const auto rank{ options.Rank() };
        const auto mddOptions{ ::Microsoft::Windows::ApplicationModel::DynamicDependency::ToAddOptions(options) };
        wil::unique_mdd_package_dependency_context packageDependencyContext;
        winrt::check_hresult(MddAddPackageDependency(m_id.c_str(), rank, mddOptions, &packageDependencyContext, nullptr));
        auto context{ winrt::make<implementation::PackageDependencyContext>(packageDependencyContext.get()) };
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
        winrt::check_hresult(MddTryCreatePackageDependency(userSid, packageFamilyName, minVersion, architectures, lifetimeKind, lifetimeArtifact, options, wil::out_param(packageDependencyId)));
        return GetFromId(packageDependencyId.get());
    }
}
