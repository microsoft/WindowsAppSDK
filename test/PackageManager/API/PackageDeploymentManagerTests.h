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
    inline bool SkipIfFeatureNotSupported(
        const winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature feature,
        PCWSTR message)
    {
        const bool isSupported{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature) };
        if (!isSupported)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, message);
        }
        return !isSupported;
    }

    inline bool SkipIfFeatureNotSupported_PackageUriScheme_ms_uup()
    {
        const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::PackageUriScheme_ms_uup };
        PCWSTR message{ L"ms-uup: not supported on this system. Skipping test" };
        return TPMT::SkipIfFeatureNotSupported(feature, message);
    }

    inline bool SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable()
    {
        const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::IsPackageReadyOrNewerAvailable };
        PCWSTR message{ L"IsPackageReadyOrNewerAvailable not supported on this system. Skipping test" };
        return TPMT::SkipIfFeatureNotSupported(feature, message);
    }

    inline bool SkipIfFeatureNotSupported_RemovePackageByUri()
    {
        const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::RemovePackageByUri };
        PCWSTR message{ L"RemovePackageByUri not supported on this system. Skipping test" };
        return TPMT::SkipIfFeatureNotSupported(feature, message);
    }

    inline bool SkipIfFeatureNotSupported_ResetPackage()
    {
        const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
        PCWSTR message{ L"ResetPackage not supported on this system. Skipping test" };
        return TPMT::SkipIfFeatureNotSupported(feature, message);
    }

    inline bool SkipIfFeatureNotSupported_RepairPackage()
    {
        const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::RepairPackage };
        PCWSTR message{ L"RepairPackage not supported on this system. Skipping test" };
        return TPMT::SkipIfFeatureNotSupported(feature, message);
    }

    inline bool SkipIfFeatureNotSupported_ProvisionPackage_Framework()
    {
        const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ProvisionPackage_Framework };
        PCWSTR message{ L"ProvisionPackage.Framework not supported on this system. Skipping test" };
        return TPMT::SkipIfFeatureNotSupported(feature, message);
    }

    inline bool PreBootstrap_SkipIfFeatureNotSupported(
        const winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature feature,
        PCWSTR message)
    {
        // NOTE: Some tests can't use winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature
        //       due to chicken/egg dependencies (can't use it before Bootstrapper's initialized but need access
        //       before Bootstrapper's initialized...). So we'll handle them by directly calling the FrameworkUdk
        //
        // NOTE: Only support necessary features here.
        switch (feature)
        {
            case winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ProvisionPackage_Framework:
            {
                //TODO Awaiting ProvisionPackageForAllUsersAsync() support for Framework packages
                //return IsPackageDeploymentFeatureSupported(L"ProvisionPackage.Framework");
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, message);
                return true;
            }
            default:
            {
                // Unsupported pre-Bootstrap feature check
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Blocked, message);
                VERIFY_FAIL(WEX::Common::String().Format(L"Feature:%d", static_cast<int>(feature)));
                return true;
            }
        }
    }

    inline bool PreBootstrap_SkipIfFeatureNotSupported_ProvisionPackage_Framework()
    {
        const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ProvisionPackage_Framework };
        PCWSTR message{ L"ProvisionPackage.Framework not supported on this system. Skipping test" };
        return TPMT::PreBootstrap_SkipIfFeatureNotSupported(feature, message);
    }

    void VerifyDeploymentSucceeded(
        const winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult& deploymentResult,
        PCSTR filename,
        int line,
        PCSTR function);

    class PackageDeploymentManagerTests_Base
    {
    protected:
        inline bool DoNotExecuteTestMethod() const
        {
            return m_doNotExecuteTestMethod;
        }
        inline void DoNotExecuteTestMethod(const bool doNotExecuteTestMethod)
        {
            m_doNotExecuteTestMethod = doNotExecuteTestMethod;
        }
    private:
        bool m_doNotExecuteTestMethod{};

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
