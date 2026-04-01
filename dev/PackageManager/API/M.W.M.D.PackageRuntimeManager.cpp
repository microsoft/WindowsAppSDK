// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageRuntimeManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageRuntimeManager.g.cpp"

#include "M.W.M.D.PackageSetItemRuntimeDisposition.h"
#include "M.W.M.D.PackageSetRuntimeDisposition.h"

#include <MddWin11.h>
#include <MsixDynamicDependency.h>
#include <wil_msixdynamicdependency.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager PackageRuntimeManager::GetDefault()
    {
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageRuntimeManager>();
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition PackageRuntimeManager::AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
        return AddPackageSet(packageSet, createOptions, addOptions);
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition PackageRuntimeManager::AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions)
    {
        // Check parameter(s)
        Validate(packageSet);
        Validate(createOptions);
        Validate(addOptions);

        winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition packageSetRuntimeDisposition;
        packageSetRuntimeDisposition.PackageSetId(packageSet.Id());
        auto packageSetItemRuntimeDispositions{ packageSetRuntimeDisposition.PackageSetItemRuntimeDispositions() };

        const auto packageSetItems{ packageSet.Items() };
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            auto packageSetItemRuntimeDisposition{ AddPackageSetItem(packageSetItem, createOptions, addOptions) };
            packageSetItemRuntimeDispositions.Append(packageSetItemRuntimeDisposition);
        }

        return packageSetRuntimeDisposition;
    }
    void PackageRuntimeManager::RemovePackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition const& packageSetRuntimeDisposition)
    {
        const auto packageSetItemRuntimeDispositions{ packageSetRuntimeDisposition.PackageSetItemRuntimeDispositions() };
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition& packageSetItemRuntimeDisposition : packageSetItemRuntimeDispositions)
        {
            RemovePackageSetItem(packageSetItemRuntimeDisposition);
        }
    }

    winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition PackageRuntimeManager::AddPackageSetItem(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions)
    {
        auto createPackageDependencyOptions{ MddCreatePackageDependencyOptions::None };
        WI_SetFlagIf(createPackageDependencyOptions, MddCreatePackageDependencyOptions::DoNotVerifyDependencyResolution, !createOptions.VerifyDependencyResolution());
        wil::unique_process_heap_string packageDependencyId;
        THROW_IF_FAILED(MddCore::Win11::TryCreatePackageDependency(nullptr, packageSetItem.PackageFamilyName(),
            packageSetItem.MinVersion(), packageSetItem.ProcessorArchitectureFilter(),
            createOptions, &packageDependencyId));

        auto addPackageDependencyOptions{ MddAddPackageDependencyOptions::None };
        WI_SetFlagIf(addPackageDependencyOptions, MddAddPackageDependencyOptions::PrependIfRankCollision, addOptions.PrependIfRankCollision());
        wil::unique_mdd_package_dependency_context mddPackageDependencyContext{};
        wil::unique_process_heap_string packageFullName;
        THROW_IF_FAILED(MddCore::Win11::AddPackageDependency(packageDependencyId.get(), addOptions, &mddPackageDependencyContext, &packageFullName));

        auto packageSetItemRuntimeDisposition{ winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageSetItemRuntimeDisposition>(
            packageSetItem.Id(), packageFullName.get(), packageDependencyId.get(), mddPackageDependencyContext.get()) };
        mddPackageDependencyContext.reset();
        return packageSetItemRuntimeDisposition;
    }

    void PackageRuntimeManager::RemovePackageSetItem(winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition const& packageSetItemRuntimeDisposition)
    {
        const auto packageDependencyContextId{ packageSetItemRuntimeDisposition.PackageDependencyContextId() };
        MddCore::Win11::RemovePackageDependency(packageDependencyContextId);

        const auto packageDependencyId{ packageSetItemRuntimeDisposition.PackageDependencyId() };
        MddCore::Win11::DeletePackageDependency(packageDependencyId);
    }

    void PackageRuntimeManager::Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet) const
    {
        THROW_HR_IF(E_INVALIDARG, packageSet.Id().empty());
        const auto& packageSetItems{ packageSet.Items() };
        THROW_HR_IF(E_INVALIDARG, packageSetItems.Size() == 0);
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            Validate(packageSetItem);
        }
    }

    void PackageRuntimeManager::Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem) const
    {
        const auto packageFamilyName{ packageSetItem.PackageFamilyName() };
        THROW_IF_WIN32_ERROR_MSG(VerifyPackageFamilyName(packageFamilyName.c_str()), "PackageFamilyName:%ls", packageFamilyName.c_str());

        const auto packageUri{ packageSetItem.PackageUri() };
        THROW_HR_IF_NULL_MSG(E_INVALIDARG, packageUri, "PackageUri:<null>");
    }

    void PackageRuntimeManager::Validate(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& /*options*/ ) const
    {
        // Nothing to do!
    }

    void PackageRuntimeManager::Validate(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& /*options*/) const
    {
        // Nothing to do!
    }
}
