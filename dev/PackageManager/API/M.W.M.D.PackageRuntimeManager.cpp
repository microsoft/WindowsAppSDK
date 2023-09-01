// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageRuntimeManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageRuntimeManager.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager PackageRuntimeManager::GetDefault()
    {
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageRuntimeManager>();
    }
    void PackageRuntimeManager::AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
        AddPackageSet(packageSet, createOptions, addOptions);
    }
    void PackageRuntimeManager::AddPackageSet(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions)
    {
        // Check parameter(s)
        Validate(packageSet);
        Validate(createOptions);
        Validate(addOptions);

        const auto packageSetItems{ packageSet.PackageSetItems() };
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            AddPackageSetItem(packageSetItem, createOptions, addOptions);
        }
    }
    void PackageRuntimeManager::AddPackageSetById(hstring const& packageSetId)
    {
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
        AddPackageSetById(packageSetId, createOptions, addOptions);
    }
    void PackageRuntimeManager::AddPackageSetById(hstring const& packageSetId, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions)
    {
        throw hresult_not_implemented();
    }

    void PackageRuntimeManager::AddPackageSetItem(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& createOptions, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& addOptions)
    {
        throw hresult_not_implemented();
    }

    void PackageRuntimeManager::Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet) const
    {
        THROW_HR_IF(E_INVALIDARG, packageSet.Id().empty());
        const auto& packageSetItems{ packageSet.PackageSetItems() };
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

    void PackageRuntimeManager::Validate(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options) const
    {
        // Nothing to do!
    }

    void PackageRuntimeManager::Validate(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options) const
    {
        // Nothing to do!
    }

}
