// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageDeploymentManager.h"
#include "Microsoft.Windows.Management.Deployment.PackageDeploymentManager.g.cpp"

#include "M.W.M.D.PackageDeploymentResult.h"
#include "MsixPackageManager.h"
#include "PackageDeploymentResolver.h"

#include "PackageManagerTelemetry.h"

static_assert(static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::Default) == static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::Default),
              "winrt::Windows::Management::Deployment::StubPackageOption::Default != winrt::Windows::Management::Deployment::StubPackageOption::Default");
static_assert(static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::InstallFull) == static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::InstallFull),
              "winrt::Windows::Management::Deployment::StubPackageOption::InstallFull != winrt::Windows::Management::Deployment::StubPackageOption::InstallFull");
static_assert(static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::InstallStub) == static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::InstallStub),
              "winrt::Windows::Management::Deployment::StubPackageOption::InstallStub != winrt::Windows::Management::Deployment::StubPackageOption::InstallStub");
static_assert(static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::UsePreference) == static_cast<int>(winrt::Windows::Management::Deployment::StubPackageOption::UsePreference),
              "winrt::Windows::Management::Deployment::StubPackageOption::UsePreference != winrt::Windows::Management::Deployment::StubPackageOption::UsePreference");

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager PackageDeploymentManager::GetDefault()
    {
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageDeploymentManager>();
    }
    bool PackageDeploymentManager::IsPackageReady(hstring const& package)
    {
        if (VerifyPackageFullName(package.c_str()) == ERROR_SUCCESS)
        {
            return IsReadyByPackageFullName(package);
        }

        const winrt::Windows::Foundation::Uri packageUri{ package };
        const auto packageAbsoluteUri{ packageUri.AbsoluteUri() };
        if (!packageAbsoluteUri.empty())
        {
            return IsPackageReadyByUri(packageUri);
        }
        THROW_HR_MSG(E_INVALIDARG, "%ls", package.c_str());
    }
    bool PackageDeploymentManager::IsPackageReadyByUri(winrt::Windows::Foundation::Uri const& packageUri)
    {
        throw hresult_not_implemented();
    }
    bool PackageDeploymentManager::IsPackageSetReady(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet)
    {
        Validate(packageSet);

        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSet.Items())
        {
            if (!IsReady(packageSetItem))
            {
                (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_FAILED,
                                 "Id=%ls PackageFamilyName=%ls MinVersion=%hu.%hu.%hu.%hu ArchitectureFilter:0x%X",
                                 packageSetItem.Id().c_str(),
                                 packageSetItem.PackageFamilyName().c_str(),
                                 packageSetItem.MinVersion().Major,
                                 packageSetItem.MinVersion().Minor,
                                 packageSetItem.MinVersion().Build,
                                 packageSetItem.MinVersion().Revision,
                                 packageSetItem.ProcessorArchitectureFilter());
                return false;
            }
        }
        return true;
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::EnsurePackageReadyAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::EnsurePackageReadyByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::EnsurePackageSetReadyAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options)
    {
        auto logTelemetry{ PackageManagementTelemetry::EnsurePackageSetReadyAsync::Start(packageSet.Id()) };

        auto strong{ get_strong() };

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        // Allow to register the progress and complete handler
        logTelemetry.IgnoreCurrentThread();
        co_await resume_background();   // Allow to register the progress and complete handler
        auto logTelemetryContinuation{ logTelemetry.ContinueOnCurrentThread() };

        auto progress{ co_await winrt::get_progress_token() };
        auto packageDeploymentProgress{
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress{
                PackageDeploymentProgressStatus::Queued, 0} };
        progress(packageDeploymentProgress);

        // Check parameter(s)
        Validate(packageSet);

        // Is there any work to do?
        packageDeploymentProgress.Status = PackageDeploymentProgressStatus::InProgress;
        const double c_progressPercentageStartOfIsReady{ 0.01 };
        packageDeploymentProgress.Progress = c_progressPercentageStartOfIsReady;
        progress(packageDeploymentProgress);
        if (IsPackageSetReady(packageSet))
        {
            co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, winrt::guid{});
        }

        const double c_progressPercentageStartOfInstalls{ 0.10 };
        packageDeploymentProgress.Progress = c_progressPercentageStartOfInstalls;
        progress(packageDeploymentProgress);
        auto packageSetItems{ packageSet.Items() };
        const double progressIncrementPerPackageSetItem{ (1.0 - c_progressPercentageStartOfInstalls) / packageSetItems.Size() };
        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            const auto packageFamilyName{ packageSetItem.PackageFamilyName() };
            const auto packageUri{ packageSetItem.PackageUri() };
            try
            {
                error = LOG_IF_FAILED_MSG(EnsureReadyAsync(packageSetItem, options, packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                          "Error:0x%08X (0x%08X) PackageFamilyName:%ls PackageUri:%ls : %ls",
                                          error, extendedError, packageFamilyName.c_str(), packageUri.ToString().c_str(), errorText.c_str());
            }
            catch (...)
            {
                auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
                error = LOG_HR_MSG(exception.code(), "Error:0x%08X (0x%08X) PackageFamilyName:%ls PackageUri:%ls : %ls", error, extendedError, packageFamilyName.c_str(), packageUri.ToString().c_str(), errorText.c_str());
            }
            if (FAILED(error))
            {
                co_return winrt::make<PackageDeploymentResult>(
                    PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
            }
            packageDeploymentProgress.Progress = packageDeploymentProgress.Progress + progressIncrementPerPackageSetItem;
            progress(packageDeploymentProgress);
        }

        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);

        logTelemetry.Stop(packageSet.Id());
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::AddPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options)
    {
        const winrt::Windows::Foundation::Uri packageUri{ package };
        const auto packageAbsoluteUri{ packageUri.AbsoluteUri() };
        if (!packageAbsoluteUri.empty())
        {
            const std::wstring packageAsString{ package.c_str() };
            if (packageAsString.ends_with(L".appinstaller"))
            {
                //TODO: return AddPackageByAppInstallerFileAsync(packageUri);
                throw hresult_not_implemented();
            }
            else
            {
                return AddPackageByUriAsync(packageUri, options);
            }
        }
        THROW_HR_MSG(E_INVALIDARG, "%ls", package.c_str());
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::AddPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options)
    {
        const winrt::hstring packageUriAsString{ packageUri.ToString() };
        auto logTelemetry{ PackageManagementTelemetry::AddPackageByUriAsync::Start(packageUriAsString) };

        auto strong{ get_strong() };

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        // Allow to register the progress and complete handler
        logTelemetry.IgnoreCurrentThread();
        co_await resume_background();   // Allow to register the progress and complete handler
        auto logTelemetryContinuation{ logTelemetry.ContinueOnCurrentThread() };

        auto progress{ co_await winrt::get_progress_token() };
        auto packageDeploymentProgress{
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress{
                PackageDeploymentProgressStatus::Queued, 0} };
        progress(packageDeploymentProgress);

        // Check parameter(s)
        //TODO Validate(packageSet);

        winrt::Windows::Management::Deployment::AddPackageOptions addOptions{ ToOptions(options) };
        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        try
        {
            error = LOG_IF_FAILED_MSG(AddAsync(packageUri, addOptions, packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                      "ExtendedError:0x%08X PackageUri:%ls",
                                      extendedError, packageUri.ToString().c_str());
        }
        catch (...)
        {
            const auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            error = LOG_HR_MSG(exception.code(), "ExtendedError:0x%08X PackageUri:%ls", extendedError, packageUri.ToString().c_str());
        }
        if (FAILED(error))
        {
            co_return winrt::make<PackageDeploymentResult>(
                PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
        }

        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);

        logTelemetry.Stop(packageUriAsString);
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::AddPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options)
    {
        auto logTelemetry{ PackageManagementTelemetry::AddPackageSetAsync::Start(packageSet.Id()) };

        auto strong{ get_strong() };

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        // Allow to register the progress and complete handler
        logTelemetry.IgnoreCurrentThread();
        co_await resume_background();   // Allow to register the progress and complete handler
        auto logTelemetryContinuation{ logTelemetry.ContinueOnCurrentThread() };

        auto progress{ co_await winrt::get_progress_token() };
        auto packageDeploymentProgress{
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress{
                PackageDeploymentProgressStatus::Queued, 0} };
        progress(packageDeploymentProgress);

        // Check parameter(s)
        Validate(packageSet);

        packageDeploymentProgress.Status = PackageDeploymentProgressStatus::InProgress;
        const double c_progressPercentageStartOfInstalls{ 0.10 };
        packageDeploymentProgress.Progress = c_progressPercentageStartOfInstalls;
        progress(packageDeploymentProgress);
        auto packageSetItems{ packageSet.Items() };
        const double progressIncrementPerPackageSetItem{ (1.0 - c_progressPercentageStartOfInstalls) / packageSetItems.Size() };
        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            try
            {
                error = LOG_IF_FAILED_MSG(AddAsync(packageSetItem, options, packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                          "ExtendedError:0x%08X PackageFamilyName:%ls PackageUri:%ls",
                                          extendedError, packageSetItem.PackageFamilyName().c_str(), packageSetItem.PackageUri().ToString().c_str());
                packageDeploymentProgress.Progress = packageDeploymentProgress.Progress + progressIncrementPerPackageSetItem;
                progress(packageDeploymentProgress);
            }
            catch (...)
            {
                const auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
                error = LOG_HR_MSG(exception.code(), "ExtendedError:0x%08X PackageFamilyName:%ls PackageUri:%ls", extendedError, packageSetItem.PackageFamilyName().c_str(), packageSetItem.PackageUri().ToString().c_str());
            }
            if (FAILED(error))
            {
                co_return winrt::make<PackageDeploymentResult>(
                    PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
            }
        }

        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);

        logTelemetry.Stop(packageSet.Id());
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::StagePackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options)
    {
        const winrt::Windows::Foundation::Uri packageUri{ package };
        const auto packageAbsoluteUri{ packageUri.AbsoluteUri() };
        if (!packageAbsoluteUri.empty())
        {
            return StagePackageByUriAsync(packageUri, options);
        }
        THROW_HR_MSG(E_INVALIDARG, "%ls", package.c_str());
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::StagePackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options)
    {
        const winrt::hstring packageUriAsString{ packageUri.ToString() };
        auto logTelemetry{ PackageManagementTelemetry::StagePackageByUriAsync::Start(packageUriAsString) };

        auto strong{ get_strong() };

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        logTelemetry.IgnoreCurrentThread();
        co_await resume_background();   // Allow to register the progress and complete handler
        auto logTelemetryContinuation{ logTelemetry.ContinueOnCurrentThread() };

        auto progress{ co_await winrt::get_progress_token() };
        auto packageDeploymentProgress{
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress{
                PackageDeploymentProgressStatus::Queued, 0} };
        progress(packageDeploymentProgress);

        // Check parameter(s)
        //TODO Validate(packageSet);

        winrt::Windows::Management::Deployment::StagePackageOptions stageOptions{ ToOptions(options) };
        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        try
        {
            error = LOG_IF_FAILED_MSG(StageAsync(packageUri, stageOptions, packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                      "ExtendedError:0x%08X PackageUri:%ls",
                                      extendedError, packageUri.ToString().c_str());
        }
        catch (...)
        {
            const auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            error = LOG_HR_MSG(exception.code(), "ExtendedError:0x%08X PackageUri:%ls", extendedError, packageUri.ToString().c_str());
        }
        if (FAILED(error))
        {
            co_return winrt::make<PackageDeploymentResult>(
                PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
        }

        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);

        logTelemetry.Stop(packageUriAsString);
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::StagePackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options)
    {
        auto logTelemetry{ PackageManagementTelemetry::StagePackageSetAsync::Start(packageSet.Id()) };

        auto strong{ get_strong() };

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        // Allow to register the progress and complete handler
        logTelemetry.IgnoreCurrentThread();
        co_await resume_background();   // Allow to register the progress and complete handler
        auto logTelemetryContinuation{ logTelemetry.ContinueOnCurrentThread() };

        auto progress{ co_await winrt::get_progress_token() };
        auto packageDeploymentProgress{
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress{
                PackageDeploymentProgressStatus::Queued, 0} };
        progress(packageDeploymentProgress);

        // Check parameter(s)
        Validate(packageSet);

        packageDeploymentProgress.Status = PackageDeploymentProgressStatus::InProgress;
        const double c_progressPercentageStartOfInstalls{ 0.10 };
        packageDeploymentProgress.Progress = c_progressPercentageStartOfInstalls;
        progress(packageDeploymentProgress);
        auto packageSetItems{ packageSet.Items() };
        const double progressIncrementPerPackageSetItem{ (1.0 - c_progressPercentageStartOfInstalls) / packageSetItems.Size() };
        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            try
            {
                error = LOG_IF_FAILED_MSG(StageAsync(packageSetItem, options, packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                          "ExtendedError:0x%08X PackageFamilyName:%ls PackageUri:%ls",
                                          extendedError, packageSetItem.PackageFamilyName().c_str(), packageSetItem.PackageUri().ToString().c_str());
                packageDeploymentProgress.Progress = packageDeploymentProgress.Progress + progressIncrementPerPackageSetItem;
                progress(packageDeploymentProgress);
            }
            catch (...)
            {
                const auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
                error = LOG_HR_MSG(exception.code(), "ExtendedError:0x%08X PackageFamilyName:%ls PackageUri:%ls", extendedError, packageSetItem.PackageFamilyName().c_str(), packageSetItem.PackageUri().ToString().c_str());
            }
            if (FAILED(error))
            {
                co_return winrt::make<PackageDeploymentResult>(
                    PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
            }
        }

        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);

        logTelemetry.Stop(packageSet.Id());
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RegisterPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RegisterPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RegisterPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RemovePackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options)
    {
        if (VerifyPackageFamilyName(package.c_str()) == ERROR_SUCCESS)
        {
            return RemovePackageByFamilyNameAsync(package, options);
        }
        else if (VerifyPackageFullName(package.c_str()) == ERROR_SUCCESS)
        {
            return RemovePackageByFullNameAsync(package, options);
        }
        THROW_HR_MSG(E_INVALIDARG, "%ls", package.c_str());
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RemovePackageByFullNameAsync(hstring packageFullName, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RemovePackageByFamilyNameAsync(hstring packageFamilyName, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RemovePackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RemovePackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::ResetPackageAsync(hstring package)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::ResetPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::ResetPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RepairPackageAsync(hstring package)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RepairPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::RepairPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::ProvisionPackageAsync(hstring package, winrt::Microsoft::Windows::Management::Deployment::ProvisionPackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::ProvisionPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri, winrt::Microsoft::Windows::Management::Deployment::ProvisionPackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::ProvisionPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet, winrt::Microsoft::Windows::Management::Deployment::ProvisionPackageOptions options)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::DeprovisionPackageAsync(hstring package)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::DeprovisionPackageByUriAsync(winrt::Windows::Foundation::Uri packageUri)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
    PackageDeploymentManager::DeprovisionPackageSetAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet)
    {
        throw hresult_not_implemented();
    }
    bool PackageDeploymentManager::IsPackageRegistrationPending(hstring const& packageFamilyName)
    {
        return IsPackageRegistrationPendingForUser(hstring{}, packageFamilyName);
    }
    bool PackageDeploymentManager::IsPackageRegistrationPendingForUser(hstring const& userSecurityId, hstring const& packageFamilyName)
    {
        throw hresult_not_implemented();
    }

    bool PackageDeploymentManager::IsReadyByPackageFullName(hstring const& packageFullName)
    {
        return ::Microsoft::Windows::ApplicationModel::PackageDeploymentResolver::FindAny(m_packageManager, packageFullName);
    }

    bool PackageDeploymentManager::IsReady(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem)
    {
        const AppModel::Identity::PackageVersion minVersion{ packageSetItem.MinVersion() };
        const auto processorArchitectureFilter{ packageSetItem.ProcessorArchitectureFilter() };
        return ::Microsoft::Windows::ApplicationModel::PackageDeploymentResolver::FindAny(m_packageManager, packageSetItem.PackageFamilyName(), minVersion, processorArchitectureFilter);
    }

    void PackageDeploymentManager::Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet) const
    {
        THROW_HR_IF(E_INVALIDARG, packageSet.Id().empty());
        const auto& packageSetItems{ packageSet.Items() };
        THROW_HR_IF(E_INVALIDARG, packageSetItems.Size() == 0);
        for (const winrt::Microsoft::Windows::Management::Deployment::PackageSetItem& packageSetItem : packageSetItems)
        {
            Validate(packageSetItem);
        }
    }

    void PackageDeploymentManager::Validate(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem) const
    {
        const auto packageFamilyName{ packageSetItem.PackageFamilyName() };
        THROW_IF_WIN32_ERROR_MSG(VerifyPackageFamilyName(packageFamilyName.c_str()), "PackageFamilyName:%ls", packageFamilyName.c_str());

        const auto packageUri{ packageSetItem.PackageUri() };
        THROW_HR_IF_NULL_MSG(E_INVALIDARG, packageUri, "PackageUri:<null>");
    }

    HRESULT PackageDeploymentManager::EnsureReadyAsync(
        winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem,
        winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions const& options,
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
        wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
        HRESULT& extendedError,
        winrt::hstring& errorText,
        winrt::guid& activityId)
    {
        extendedError = S_OK;
        errorText.clear();
        activityId = winrt::guid{};

        if (IsReady(packageSetItem))
        {
            return S_OK;
        }

        auto packageUri{ packageSetItem.PackageUri() };
        winrt::Windows::Management::Deployment::AddPackageOptions addOptions{ ToOptions(options) };
        auto deploymentOperation{ m_packageManager.AddPackageByUriAsync(packageUri, addOptions) };
        deploymentOperation.Progress([&](winrt::Windows::Foundation::IAsyncOperationWithProgress<
                                            winrt::Windows::Management::Deployment::DeploymentResult,
                                            winrt::Windows::Management::Deployment::DeploymentProgress> const& /*sender*/,
                                         winrt::Windows::Management::Deployment::DeploymentProgress const& progressInfo)
        {
            packageDeploymentProgress.Progress = PercentageToProgress(progressInfo.percentage);
            progress(packageDeploymentProgress);
        });
        deploymentOperation.get();
        try
        {
            const auto deploymentResult{ deploymentOperation.GetResults() };
            const HRESULT error{ static_cast<HRESULT>(deploymentOperation.ErrorCode()) };
            extendedError = deploymentResult.ExtendedErrorCode();
            errorText = deploymentResult.ErrorText();
            activityId = deploymentResult.ActivityId();
            const auto status{ deploymentOperation.Status() };
            if (status == winrt::Windows::Foundation::AsyncStatus::Error)
            {
                RETURN_IF_FAILED_MSG(error,
                                     "ExtendedError:0x%08X PackageFamilyName:%ls PackageUri:%ls : %ls",
                                     extendedError, packageSetItem.PackageFamilyName().c_str(), packageSetItem.PackageUri().ToString().c_str(), errorText.c_str());

                // Status=Error but SUCCEEDED(error) == This.Should.Never.Happen.
                FAIL_FAST_HR_MSG(E_UNEXPECTED,
                                 "ExtendedError:0x%08X PackageFamilyName:%ls PackageUri:%ls : %ls",
                                 extendedError, packageSetItem.PackageFamilyName().c_str(), packageUri.ToString().c_str(), errorText.c_str());
            }
            else if (status == winrt::Windows::Foundation::AsyncStatus::Canceled)
            {
                RETURN_WIN32_MSG(ERROR_CANCELLED, "%ls", packageUri.ToString().c_str());
            }
            FAIL_FAST_HR_IF_MSG(E_UNEXPECTED, status != winrt::Windows::Foundation::AsyncStatus::Completed,
                                "Status:%d %ls", static_cast<int32_t>(status), packageUri.ToString().c_str());
        }
        catch (...)
        {
            auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            THROW_HR_MSG(exception.code(),
                         "ExtendedError:0x%08X PackageFamilyName:%ls PackageUri:%ls : %ls",
                         extendedError, packageSetItem.PackageFamilyName().c_str(), packageSetItem.PackageUri().ToString().c_str(), errorText.c_str());
        }
        return S_OK;
    }

    HRESULT PackageDeploymentManager::AddAsync(
        winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem,
        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& options,
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
        wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
        HRESULT& extendedError,
        winrt::hstring& errorText,
        winrt::guid& activityId)
    {
        extendedError = S_OK;
        errorText.clear();
        activityId = winrt::guid{};

        auto packageUri{ packageSetItem.PackageUri() };
        winrt::Windows::Management::Deployment::AddPackageOptions addOptions{ ToOptions(options) };
        RETURN_IF_FAILED(AddAsync(packageUri, addOptions, packageDeploymentProgress, progress, extendedError, errorText, activityId));
        return S_OK;
    }

    HRESULT PackageDeploymentManager::AddAsync(
        winrt::Windows::Foundation::Uri const& packageUri,
        winrt::Windows::Management::Deployment::AddPackageOptions const& addOptions,
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
        wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
        HRESULT& extendedError,
        winrt::hstring& errorText,
        winrt::guid& activityId)
    {
        extendedError = S_OK;
        errorText.clear();
        activityId = winrt::guid{};

        auto deploymentOperation{ m_packageManager.AddPackageByUriAsync(packageUri, addOptions) };
        deploymentOperation.Progress([&](winrt::Windows::Foundation::IAsyncOperationWithProgress<
                                            winrt::Windows::Management::Deployment::DeploymentResult,
                                            winrt::Windows::Management::Deployment::DeploymentProgress> const& /*sender*/,
                                         winrt::Windows::Management::Deployment::DeploymentProgress const& progressInfo)
        {
            packageDeploymentProgress.Progress = PercentageToProgress(progressInfo.percentage);
            progress(packageDeploymentProgress);
        });
        deploymentOperation.get();
        try
        {
            const auto deploymentResult{ deploymentOperation.GetResults() };
            const HRESULT error{ static_cast<HRESULT>(deploymentOperation.ErrorCode()) };
            extendedError = deploymentResult.ExtendedErrorCode();
            errorText = deploymentResult.ErrorText();
            activityId = deploymentResult.ActivityId();
            const auto status{ deploymentOperation.Status() };
            if (status == winrt::Windows::Foundation::AsyncStatus::Error)
            {
                if (error == HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_DOWNGRADE))
                {
                    // Newer version already installed. Success!
                    (void)LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_DOWNGRADE),
                                     "ExtendedError:0x%08X PackageUri:%ls : %ls",
                                     extendedError, packageUri.ToString().c_str(), errorText.c_str());
                    extendedError = error;
                    errorText.clear();
                    return S_OK;
                }
                RETURN_IF_FAILED_MSG(error,
                                     "ExtendedError:0x%08X PackageUri:%ls : %ls",
                                     extendedError, packageUri.ToString().c_str(), errorText.c_str());

                // Status=Error but SUCCEEDED(error) == This.Should.Never.Happen.
                FAIL_FAST_HR_MSG(E_UNEXPECTED,
                                 "ExtendedError:0x%08X PackageUri:%ls : %ls",
                                 extendedError, packageUri.ToString().c_str(), errorText.c_str());
            }
            else if (status == winrt::Windows::Foundation::AsyncStatus::Canceled)
            {
                RETURN_WIN32_MSG(ERROR_CANCELLED, "%ls", packageUri.ToString().c_str());
            }
            FAIL_FAST_HR_IF_MSG(E_UNEXPECTED, status != winrt::Windows::Foundation::AsyncStatus::Completed,
                                "Status:%d PackageUri:%ls : %ls", static_cast<int32_t>(status), packageUri.ToString().c_str(), errorText.c_str());
        }
        catch (...)
        {
            auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            THROW_HR_MSG(exception.code(),
                         "ExtendedError:0x%08X PackageUri:%ls : %ls",
                         extendedError, packageUri.ToString().c_str(), errorText.c_str());
        }
        return S_OK;
    }

    HRESULT PackageDeploymentManager::StageAsync(winrt::Microsoft::Windows::Management::Deployment::PackageSetItem const& packageSetItem,
        winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions const& options,
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
        wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
        HRESULT& extendedError,
        winrt::hstring& errorText,
        winrt::guid& activityId)
    {
        extendedError = S_OK;
        errorText.clear();
        activityId = winrt::guid{};

        auto packageUri{ packageSetItem.PackageUri() };
        winrt::Windows::Management::Deployment::StagePackageOptions stageOptions{ ToOptions(options) };
        RETURN_IF_FAILED(StageAsync(packageUri, stageOptions, packageDeploymentProgress, progress, extendedError, errorText, activityId));
        return S_OK;
    }

    HRESULT PackageDeploymentManager::StageAsync(
        winrt::Windows::Foundation::Uri const& packageUri,
        winrt::Windows::Management::Deployment::StagePackageOptions const& stageOptions,
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
        wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
        HRESULT& extendedError,
        winrt::hstring& errorText,
        winrt::guid& activityId)
    {
        extendedError = S_OK;
        errorText.clear();
        activityId = winrt::guid{};

        auto deploymentOperation{ m_packageManager.StagePackageByUriAsync(packageUri, stageOptions) };
        deploymentOperation.Progress([&](winrt::Windows::Foundation::IAsyncOperationWithProgress<
                                            winrt::Windows::Management::Deployment::DeploymentResult,
                                            winrt::Windows::Management::Deployment::DeploymentProgress> const& /*sender*/,
                                         winrt::Windows::Management::Deployment::DeploymentProgress const& progressInfo)
        {
            packageDeploymentProgress.Progress = PercentageToProgress(progressInfo.percentage);
            progress(packageDeploymentProgress);
        });
        deploymentOperation.get();
        try
        {
            const auto deploymentResult{ deploymentOperation.GetResults() };
            const HRESULT error{ static_cast<HRESULT>(deploymentOperation.ErrorCode()) };
            extendedError = deploymentResult.ExtendedErrorCode();
            errorText = deploymentResult.ErrorText();
            activityId = deploymentResult.ActivityId();
            const auto status{ deploymentOperation.Status() };
            if (status == winrt::Windows::Foundation::AsyncStatus::Error)
            {
                if (error == HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_DOWNGRADE))
                {
                    // Newer version already installed. Success!
                    (void)LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_DOWNGRADE),
                                     "ExtendedError:0x%08X PackageUri:%ls : %ls",
                                     extendedError, packageUri.ToString().c_str(), errorText.c_str());
                    extendedError = error;
                    errorText.clear();
                    return S_OK;
                }
                RETURN_IF_FAILED_MSG(error,
                                     "ExtendedError:0x%08X PackageUri:%ls : %ls",
                                     extendedError, packageUri.ToString().c_str(), errorText.c_str());

                // Status=Error but SUCCEEDED(error) == This.Should.Never.Happen.
                FAIL_FAST_HR_MSG(E_UNEXPECTED,
                                 "ExtendedError:0x%08X PackageUri:%ls : %ls",
                                 extendedError, packageUri.ToString().c_str(), errorText.c_str());
            }
            else if (status == winrt::Windows::Foundation::AsyncStatus::Canceled)
            {
                RETURN_WIN32_MSG(ERROR_CANCELLED, "%ls", packageUri.ToString().c_str());
            }
            FAIL_FAST_HR_IF_MSG(E_UNEXPECTED, status != winrt::Windows::Foundation::AsyncStatus::Completed,
                                "Status:%d PackageUri:%ls : %ls", static_cast<int32_t>(status), packageUri.ToString().c_str(), errorText.c_str());
        }
        catch (...)
        {
            auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            THROW_HR_MSG(exception.code(),
                         "ExtendedError:0x%08X PackageUri:%ls : %ls",
                         extendedError, packageUri.ToString().c_str(), errorText.c_str());
        }
        return S_OK;
    }

    winrt::Windows::Management::Deployment::PackageVolume PackageDeploymentManager::ToPackageVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& packageVolume) const
    {
        if (packageVolume)
        {
            const auto name{ packageVolume.Name() };
            if (!name.empty())
            {
                auto toPackageVolume{ m_packageManager.FindPackageVolume(name) };
                return toPackageVolume;
            }
        }
        return nullptr;
    }

    winrt::Windows::Management::Deployment::AddPackageOptions PackageDeploymentManager::ToOptions(winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& options) const
    {
        if (!options)
        {
            return winrt::Windows::Management::Deployment::AddPackageOptions();
        }

        winrt::Windows::Management::Deployment::AddPackageOptions toOptions;
        const auto targetVolume{ options.TargetVolume() };
        if (targetVolume)
        {
            const auto toPackageVolume{ ToPackageVolume(targetVolume) };
            if (toPackageVolume)
            {
                toOptions.TargetVolume(toPackageVolume);
            }
        }
        for (const auto uri : options.DependencyPackageUris())
        {
            toOptions.DependencyPackageUris().Append(uri);
        }
        for (const auto packageFamilyName : options.OptionalPackageFamilyNames())
        {
            toOptions.OptionalPackageFamilyNames().Append(packageFamilyName);
        }
        for (const auto uri : options.OptionalPackageUris())
        {
            toOptions.OptionalPackageUris().Append(uri);
        }
        for (const auto uri : options.RelatedPackageUris())
        {
            toOptions.RelatedPackageUris().Append(uri);
        }
        toOptions.ExternalLocationUri(options.ExternalLocationUri());
        toOptions.StubPackageOption(static_cast<winrt::Windows::Management::Deployment::StubPackageOption>(options.StubPackageOption()));
        toOptions.AllowUnsigned(options.AllowUnsigned());
        toOptions.DeveloperMode(options.DeveloperMode());
        toOptions.ForceAppShutdown(options.ForceAppShutdown());
        toOptions.ForceTargetAppShutdown(options.ForceTargetAppShutdown());
        toOptions.ForceUpdateFromAnyVersion(options.ForceUpdateFromAnyVersion());
        toOptions.InstallAllResources(options.InstallAllResources());
        toOptions.RequiredContentGroupOnly(options.RequiredContentGroupOnly());
        toOptions.RetainFilesOnFailure(options.RetainFilesOnFailure());
        toOptions.StageInPlace(options.StageInPlace());
        toOptions.DeferRegistrationWhenPackagesAreInUse(options.DeferRegistrationWhenPackagesAreInUse());
        if (options.IsExpectedDigestsSupported())
        {
            const auto expectedDigests{ options.ExpectedDigests() };
            if (expectedDigests)
            {
                auto toExpectedDigests{ toOptions.ExpectedDigests() };
                for (const auto expectedDigest : expectedDigests)
                {
                    toExpectedDigests.Insert(expectedDigest.Key(), expectedDigest.Value());
                }
            }
        }
        if (options.IsLimitToExistingPackagesSupported())
        {
            toOptions.LimitToExistingPackages(options.LimitToExistingPackages());
        }
        return toOptions;
    }

    winrt::Windows::Management::Deployment::StagePackageOptions PackageDeploymentManager::ToOptions(winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions const& options) const
    {
        winrt::Windows::Management::Deployment::StagePackageOptions toOptions;
        const auto targetVolume{ options.TargetVolume() };
        if (targetVolume)
        {
            const auto toPackageVolume{ ToPackageVolume(targetVolume) };
            if (toPackageVolume)
            {
                toOptions.TargetVolume(toPackageVolume);
            }
        }
        for (const auto uri : options.DependencyPackageUris())
        {
            toOptions.DependencyPackageUris().Append(uri);
        }
        for (const auto packageFamilyName : options.OptionalPackageFamilyNames())
        {
            toOptions.OptionalPackageFamilyNames().Append(packageFamilyName);
        }
        for (const auto uri : options.OptionalPackageUris())
        {
            toOptions.OptionalPackageUris().Append(uri);
        }
        for (const auto uri : options.RelatedPackageUris())
        {
            toOptions.RelatedPackageUris().Append(uri);
        }
        toOptions.ExternalLocationUri(options.ExternalLocationUri());
        toOptions.StubPackageOption(static_cast<winrt::Windows::Management::Deployment::StubPackageOption>(options.StubPackageOption()));
        toOptions.DeveloperMode(options.DeveloperMode());
        toOptions.ForceUpdateFromAnyVersion(options.ForceUpdateFromAnyVersion());
        toOptions.InstallAllResources(options.InstallAllResources());
        toOptions.RequiredContentGroupOnly(options.RequiredContentGroupOnly());
        toOptions.StageInPlace(options.StageInPlace());
        toOptions.AllowUnsigned(options.AllowUnsigned());
        if (options.IsExpectedDigestsSupported())
        {
            const auto expectedDigests{ options.ExpectedDigests() };
            if (expectedDigests)
            {
                auto toExpectedDigests{ toOptions.ExpectedDigests() };
                for (const auto expectedDigest : expectedDigests)
                {
                    toExpectedDigests.Insert(expectedDigest.Key(), expectedDigest.Value());
                }
            }
        }
        return toOptions;
    }

    winrt::Windows::Management::Deployment::RegisterPackageOptions PackageDeploymentManager::ToOptions(winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions const& options) const
    {
        winrt::Windows::Management::Deployment::RegisterPackageOptions toOptions;
        const auto appDataVolume{ options.AppDataVolume() };
        if (appDataVolume)
        {
            const auto toPackageVolume{ ToPackageVolume(appDataVolume) };
            if (toPackageVolume)
            {
                toOptions.AppDataVolume(toPackageVolume);
            }
        }
        for (const auto uri : options.DependencyPackageUris())
        {
            toOptions.DependencyPackageUris().Append(uri);
        }
        for (const auto packageFamilyName : options.OptionalPackageFamilyNames())
        {
            toOptions.OptionalPackageFamilyNames().Append(packageFamilyName);
        }
        toOptions.ExternalLocationUri(options.ExternalLocationUri());
        toOptions.DeveloperMode(options.DeveloperMode());
        toOptions.ForceAppShutdown(options.ForceAppShutdown());
        toOptions.ForceTargetAppShutdown(options.ForceTargetAppShutdown());
        toOptions.ForceUpdateFromAnyVersion(options.ForceUpdateFromAnyVersion());
        toOptions.InstallAllResources(options.InstallAllResources());
        toOptions.StageInPlace(options.StageInPlace());
        toOptions.AllowUnsigned(options.AllowUnsigned());
        toOptions.DeferRegistrationWhenPackagesAreInUse(options.DeferRegistrationWhenPackagesAreInUse());
        if (options.IsExpectedDigestsSupported())
        {
            const auto expectedDigests{ options.ExpectedDigests() };
            if (expectedDigests)
            {
                auto toExpectedDigests{ toOptions.ExpectedDigests() };
                for (const auto expectedDigest : expectedDigests)
                {
                    toExpectedDigests.Insert(expectedDigest.Key(), expectedDigest.Value());
                }
            }
        }
        return toOptions;
    }

    winrt::Windows::Management::Deployment::RemovalOptions PackageDeploymentManager::ToOptions(winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions const& options) const
    {
        auto toOptions{ winrt::Windows::Management::Deployment::RemovalOptions::None };
        if (options.PreserveApplicationData())
        {
            toOptions |= winrt::Windows::Management::Deployment::RemovalOptions::PreserveApplicationData;
        }
        if (options.PreserveRoamableApplicationData())
        {
            toOptions |= winrt::Windows::Management::Deployment::RemovalOptions::PreserveRoamableApplicationData;
        }
        if (options.RemoveForAllUsers())
        {
            toOptions |= winrt::Windows::Management::Deployment::RemovalOptions::RemoveForAllUsers;
        }
        return toOptions;
    }

    winrt::Windows::Management::Deployment::AddPackageOptions PackageDeploymentManager::ToOptions(winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions const& /*options*/) const
    {
        return winrt::Windows::Management::Deployment::AddPackageOptions();
    }

    double PackageDeploymentManager::PercentageToProgress(uint32_t percentage)
    {
        return static_cast<double>(percentage) / 100.0;
    }
}
