// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.cpp"

#include "MsixPackageManager.h"
#include "PackageResolver.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager PackageDeploymentManager::GetDefault()
    {
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageDeploymentManager>();
    }
    bool PackageDeploymentManager::IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSet.PackageSetItems())
        {
            if (!IsReady(packageSetItem))
            {
                (void) LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_FAILED,
                                  "Id=%ls PackageFamilyName=%ls MinVersion=%hu.%hu.%hu.%hu",
                                  packageSetItem.Id().c_str(),
                                  packageSetItem.PackageFamilyName().c_str(),
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
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::EnsureIsReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::EnsureIsReadyByPackageSetIdAsync(hstring packageSetId)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::AddPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::AddPackageSetByIdAsync(hstring packageSetId, winrt::Microsoft::Windows::Management::Deployment::AddPackageSetOptions options)
    {
        throw hresult_not_implemented();
    }

    bool PackageDeploymentManager::IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem)
    {
        const AppModel::Identity::PackageVersion minVersion{ packageSetItem.MinVersion() };
        return ::Microsoft::Windows::ApplicationModel::PackageResolver::FindAny(m_packageManager, packageSetItem.PackageFamilyName(), minVersion);
    }
}
