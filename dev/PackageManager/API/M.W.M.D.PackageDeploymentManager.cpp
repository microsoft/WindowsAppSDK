// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.cpp"

#include "M.W.M.D.PackageDeploymentResult.h"
#include "M.W.M.D.PackageDeploymentProgress.h"
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
        Validate(packageSet);

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
        //TODO auto logTelemetry{ PackageDeploymentTelemetry::CreateChannelAsync::Start(g_telemetryHelper, remoteId) };

        auto strong = get_strong(); //TODO why?

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        //TODO logTelemetry.IgnoreCurrentThread();

        // Allow to register the progress and complete handler
        co_await resume_background();

        //TODO auto logTelemetryContinuation = logTelemetry.ContinueOnCurrentThread();

        auto progress{ co_await winrt::get_progress_token() };
        auto packageDeploymentProgress{
            winrt::make<
                winrt::Microsoft::Windows::Management::Deployment::implementation::PackageDeploymentProgress>(
                    PackageDeploymentProgressStatus::Queued, 0) };
        progress(packageDeploymentProgress);

        // Check parameter(s)
        Validate(packageSet);

        // Is there any work to do?
        packageDeploymentProgress.status(PackageDeploymentProgressStatus::InProgress);
        const UINT32 c_progressPercentageStartOfIsReady{ 1 };
        packageDeploymentProgress.percentage(c_progressPercentageStartOfIsReady);
        progress(packageDeploymentProgress);
        if (IsReady(packageSet))
        {
            co_return winrt::make<PackageDeploymentResult>(
                PackageDeploymentStatus::CompletedSuccess, S_OK, /*TODO*/winrt::guid{});
        }

        const UINT32 c_progressPercentageStartOfInstalls{ 10 };
        packageDeploymentProgress.percentage(c_progressPercentageStartOfInstalls);
        progress(packageDeploymentProgress);
        auto packageSetItems{ packageSet.PackageSetItems() };
        const UINT32 progressIncrementPerPackageSetItem{ (100 - c_progressPercentageStartOfInstalls) / packageSetItems.Size() };
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            try
            {
                EnsureIsReadyAsync(packageSetItem);
            }
            catch (...)
            {
                auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
                co_return winrt::make<PackageDeploymentResult>(
                    PackageDeploymentStatus::CompletedFailure, exception.code(), /*TODO*/winrt::guid{});
            }
        }

        co_return winrt::make<PackageDeploymentResult>(
            PackageDeploymentStatus::CompletedSuccess, S_OK, /*TODO*/winrt::guid{});

        //TODO logTelemetry.Stop();
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

    void PackageDeploymentManager::Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        THROW_HR_IF(E_INVALIDARG, packageSet.Id().empty());
        const auto& packageSetItems{ packageSet.PackageSetItems() };
        THROW_HR_IF(E_INVALIDARG, packageSetItems.Size() == 0);
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            Validate(packageSetItem);
        }
    }

    void PackageDeploymentManager::Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem)
    {
        const auto packageFamilyName{ packageSetItem.PackageFamilyName() };
        THROW_IF_WIN32_ERROR_MSG(VerifyPackageFamilyName(packageFamilyName.c_str()), "PackageFamilyName:%ls", packageFamilyName.c_str());

        const auto packageUri{ packageSetItem.PackageUri() };
        THROW_HR_IF_NULL_MSG(E_INVALIDARG, packageUri, "PackageUri:<null>");
    }

    void PackageDeploymentManager::EnsureIsReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem)
    {
        if (IsReady(packageSetItem))
        {
            return;
        }

        auto packageUri{ packageSetItem.PackageUri() };
        winrt::Windows::Management::Deployment::AddPackageOptions options;
        auto deploymentOperation{ m_packageManager.AddPackageByUriAsync(packageUri, options) };
        deploymentOperation.get();
        const auto deploymentResult{ deploymentOperation.GetResults() };
        winrt::hresult hr{};
        winrt::hresult extendedHr{};
        if (deploymentOperation.Status() != winrt::Windows::Foundation::AsyncStatus::Completed)
        {
            return !hr ?
                THROW_HR_MSG(hr, "%ls", packageUri.ToString().c_str()) :
                THROW_HR_MSG(extendedHr, "%ls", packageUri.ToString().c_str());
        }
    }
}
