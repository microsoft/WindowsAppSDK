// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;
namespace TPM = ::Test::Packages::Main;
namespace TPMT = ::Test::PackageManager::Tests;

namespace Test::PackageManager::Tests
{
    class PackageDeploymentManagerTests_Base
    {
    protected:
        winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus(PCWSTR packageFullName)
        {
            return TPMT::GetPackageStatus(m_packageManager, packageFullName);
        }

        void SetPackageStatus(PCWSTR packageFullName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::SetPackageStatus(m_packageManager, packageFullName, status);
        }

        void SetPackageStatusByPackageFamilyName(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::SetPackageStatusByPackageFamilyName(m_packageManager, packageFamilyName, status);
        }

        void ClearPackageStatus(PCWSTR packageFullName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::ClearPackageStatus(m_packageManager, packageFullName, status);
        }

        void ClearPackageStatusByPackageFamilyName(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::ClearPackageStatusByPackageFamilyName(m_packageManager, packageFamilyName, status);
        }

        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult WaitForDeploymentOperation(
            winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>& deploymentOperation)
        {
            using namespace winrt::Windows::Foundation;
            using namespace winrt::Microsoft::Windows::Management::Deployment;
            AsyncOperationProgressHandler<PackageDeploymentResult, PackageDeploymentProgress> progressCallback(
                [&](const IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>&, PackageDeploymentProgress progress)
            {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"...State:%d Percentage:%lf", static_cast<int>(progress.Status), progress.Progress));
                }
            );
            deploymentOperation.Progress(progressCallback);
            auto deploymentResult{ deploymentOperation.get() };
            return deploymentResult;
        }

    protected:
        winrt::Windows::Management::Deployment::PackageManager m_packageManager;
    };
}
