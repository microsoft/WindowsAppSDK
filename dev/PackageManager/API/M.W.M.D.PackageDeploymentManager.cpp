// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager PackageDeploymentManager::GetDefault()
    {
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageDeploymentManager>();
    }
    bool PackageDeploymentManager::IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet)
    {
        for (winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSet.PackageSetItems())
        {
            if (!IsReady(packageSetItem))
            {
                (void) LOG_HR_MSG(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED,
                                  L"Id:%ls PackageFamilyName:%ls MinVersion:%hu.%hu.%hu.%hu PackageTypes:0x%X",
                                  packageSetItem.Id(),
                                  packageSetItem.PackageFamilyName(),
                                  packageSetItem.MinVersion().Major,
                                  packageSetItem.MinVersion().Minor,
                                  packageSetItem.MinVersion().Build,
                                  packageSetItem.MinVersion().Revision);
                return false;
            }
        }
        return true;
    }
    bool PackageDeploymentManager::IsReadyByPackageSetId(hstring const& packageSetId)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageDeploymentManager::EnsureIsReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageDeploymentManager::EnsureIsReadyByPackageSetIdAsync(hstring packageSetId)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageDeploymentManager::AddPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageDeploymentManager::AddPackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options)
    {
        throw hresult_not_implemented();
    }

    bool PackageDeploymentManager::IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem)
    {
        const AppModel::Identity::PackageVersion minVersion{ packageSetItem.MinVersion() };
        auto criteria{ wil::str_printf<wil::unique_cotaskmem_string>(L"Id:%ls PackageFamilyName=%ls, MinVersion=%hu.%hu.%hu.%hu",
                                                                     packageSetItem.Id().c_str(), packageSetItem.PackageFamilyName().c_str(),
                                                                     minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision) };

        const auto packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework |
                                 winrt::Windows::Management::Deployment::PackageTypes::Main };
        auto packages{ m_packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring(), packageSetItem.PackageFamilyName(), packageTypes) };
    (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_SCAN_FOR_DDLM, "Bootstrap.Intitialize: Scanning packages for %ls", criteria.get());
    int packagesScanned{};
        for (winrt::Windows::ApplicationModel::Package& package : packages)
        {
        ++packagesScanned;

            const AppModel::Identity::PackageVersion packgeVersion{ package.Identity().Version };
            if (packageVersion < minVersion)
            {
            (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_NO_MATCH,
                             "Bootstrap.Intitialize: %ls not applicable. Version doesn't match MinVersion criteria (%ls)",
                             packageFullName.c_str(), criteria.get());
            continue;
            }
#if 0
        // Does the architecture match?
        const auto architecture{ packageId.Architecture() };
        const auto currentArchitecture{ AppModel::Identity::GetCurrentArchitecture() };
        if (architecture != currentArchitecture)
        {
            (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_NO_MATCH,
                             "Bootstrap.Intitialize: %ls not applicable. Architecture doesn't match current architecture %ls (%ls)",
                             packageFullName.c_str(), ::AppModel::Identity::GetCurrentArchitectureAsString(), criteria.get());
            continue;
        }
#endif

            // Gotcha!
            (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_MATCH,
                             "Bootstrap.Intitialize: %ls is applicable (%ls)",
                             packageFullName.c_str(), criteria.get());
        }
        return true;
    }
}
