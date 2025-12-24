// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageVolume.h"
#include "Microsoft.Windows.Management.Deployment.PackageVolume.g.cpp"

#include "M.W.M.D.PackageDeploymentResult.h"

#include "PackageVolumeTelemetry.h"

#include <ExportLoader.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    bool PackageVolume::IsFeatureSupported(winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature feature)
    {
        switch (feature)
        {
            case winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature::GetDefault:
            {
                return true;
            }
            case winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature::SetDefault:
            {
                return true;
            }
            case winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature::Add:
            {
                return true;
            }
            case winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature::Remove:
            {
                return true;
            }
            case winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature::SetOffline:
            {
                return true;
            }
            case winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature::SetOnline:
            {
                return true;
            }
            case winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature::GetAvailableSpace:
            {
                return true;
            }
            default:
            {
                std::ignore = LOG_HR_MSG(E_UNEXPECTED, "Feature:%d", static_cast<int>(feature));
                return false;
            }
        }
    }
    PackageVolume::PackageVolume(winrt::Windows::Management::Deployment::PackageVolume const& value)
    {
        m_windowsPackageVolume = value;
        m_isSystemVolume = value.IsSystemVolume();
        m_mountPoint = value.MountPoint();
        m_name = value.Name();
        m_packageStorePath = value.PackageStorePath();
        m_supportsHardLinks = value.SupportsHardLinks();
        m_isAppxInstallSupported = value.IsAppxInstallSupported();
        m_isFullTrustPackageSupported = value.IsFullTrustPackageSupported();
        m_isOffline = value.IsOffline();
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> PackageVolume::FindPackageVolumes()
    {
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> microsoftPackageVolumes{ winrt::single_threaded_vector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume>() };

        winrt::Windows::Management::Deployment::PackageManager packageManager;
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Management::Deployment::PackageVolume> windowsPackageVolumes{ packageManager.FindPackageVolumes() };
        for (winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume : windowsPackageVolumes)
        {
            auto microsoftPackageVolume{ winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageVolume>(windowsPackageVolume) };
            microsoftPackageVolumes.Append(microsoftPackageVolume);
        }
        return microsoftPackageVolumes;
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume PackageVolume::FindPackageVolumeByPath(hstring const& path)
    {
        const auto c_volumePathNameMaxLength{ MAX_PATH };
        wchar_t volumePathName[c_volumePathNameMaxLength]{};//AKA volumeMountPoint
        THROW_IF_WIN32_BOOL_FALSE_MSG(::GetVolumePathNameW(path.c_str(), volumePathName, ARRAYSIZE(volumePathName)), "Path:%ls", path.c_str());
        GUID mediaId{};
        const size_t c_volumeNameMaxLength{ 50 };   // "\\?\Volume{GUID}\" == 11 + 11111111-2222-3333-4444-555555555555 + 2 + null-terminator == 11 + 36 + 3 = 50
        wchar_t volumeName[c_volumeNameMaxLength]{};
        THROW_IF_WIN32_BOOL_FALSE_MSG(::GetVolumeNameForVolumeMountPoint(volumePathName, volumeName, ARRAYSIZE(volumeName)), "Path:%ls VolumePathName:%ls", path.c_str(), volumePathName);
        const auto volumeNameLength{ wcslen(volumeName) };
        THROW_HR_IF_MSG(E_UNEXPECTED, volumeNameLength == 0, "Path:%ls VolumePathName:%ls", path.c_str(), volumePathName);
        const auto offset{ volumeNameLength - 1 };
        if (volumeName[offset] == L'\\')
        {
            volumeName[offset] = L'\0';
        }
        return FindPackageVolumeByName(winrt::hstring{ volumeName });
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume PackageVolume::GetPackageVolumeByPath(hstring const& path)
    {
        const auto c_volumePathNameMaxLength{ MAX_PATH };
        wchar_t volumePathName[c_volumePathNameMaxLength]{};//AKA volumeMountPoint
        THROW_IF_WIN32_BOOL_FALSE_MSG(::GetVolumePathNameW(path.c_str(), volumePathName, ARRAYSIZE(volumePathName)), "Path:%ls", path.c_str());
        GUID mediaId{};
        const size_t c_volumeNameMaxLength{ 50 };   // "\\?\Volume{GUID}\" == 11 + 11111111-2222-3333-4444-555555555555 + 2 + null-terminator == 11 + 36 + 3 = 50
        wchar_t volumeName[c_volumeNameMaxLength]{};
        THROW_IF_WIN32_BOOL_FALSE_MSG(::GetVolumeNameForVolumeMountPoint(volumePathName, volumeName, ARRAYSIZE(volumeName)), "Path:%ls VolumePathName:%ls", path.c_str(), volumePathName);
        const auto volumeNameLength{ wcslen(volumeName) };
        THROW_HR_IF_MSG(E_UNEXPECTED, volumeNameLength == 0, "Path:%ls VolumePathName:%ls", path.c_str(), volumePathName);
        const auto offset{ volumeNameLength - 1 };
        if (volumeName[offset] == L'\\')
        {
            volumeName[offset] = L'\0';
        }
        return GetPackageVolumeByName(winrt::hstring{ volumeName });
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume PackageVolume::FindPackageVolumeByName(hstring const& name)
    {
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume{ packageManager.FindPackageVolume(name) };
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageVolume>(windowsPackageVolume);
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume PackageVolume::GetPackageVolumeByName(hstring const& name)
    {
        try
        {
            winrt::Windows::Management::Deployment::PackageManager packageManager;
            winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume{ packageManager.FindPackageVolume(name) };
            return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageVolume>(windowsPackageVolume);
        }
        catch (winrt::hresult_error const& exception)
        {
            if (exception.code() != HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
            {
                throw;
            }
        }
        return winrt::Microsoft::Windows::Management::Deployment::PackageVolume(nullptr);
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume PackageVolume::GetDefault()
    {
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume{ packageManager.GetDefaultPackageVolume() };
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageVolume>(windowsPackageVolume);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> PackageVolume::AddAsync(hstring packageStorePath)
    {
        auto logTelemetry{ PackageVolumeTelemetry::Add::Start(packageStorePath) };

        //auto strong{ get_strong() };

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        logTelemetry.IgnoreCurrentThread();
        co_await resume_background();   // Allow to register the progress and complete handler

        winrt::Windows::Management::Deployment::PackageManager packageManager;
        winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume{ co_await packageManager.AddPackageVolumeAsync(packageStorePath) };

        logTelemetry.Stop(windowsPackageVolume.MountPoint(), windowsPackageVolume.Name(), windowsPackageVolume.PackageStorePath());
        co_return winrt::make<PackageVolume>(windowsPackageVolume);
    }
    bool PackageVolume::IsSystemVolume()
    {
        return m_isSystemVolume;
    }
    hstring PackageVolume::MountPoint()
    {
        return m_mountPoint;
    }
    hstring PackageVolume::Name()
    {
        return m_name;
    }
    hstring PackageVolume::PackageStorePath()
    {
        return m_packageStorePath;
    }
    bool PackageVolume::SupportsHardLinks()
    {
        return m_supportsHardLinks;
    }
    bool PackageVolume::IsFullTrustPackageSupported()
    {
        return m_isFullTrustPackageSupported;
    }
    bool PackageVolume::IsAppxInstallSupported()
    {
        return m_isAppxInstallSupported;
    }
    bool PackageVolume::IsRepairNeeded()
    {
        // extern "C" HRESULT WINAPI MsixPackageVolumeIsRepairNeeded(_In_ PCWSTR packageVolumePath, _Out_ BOOL* needsReset);
        typedef HRESULT (WINAPI* MsixPackageVolumeIsRepairNeededFunction)(_In_ PCWSTR packageVolumePath, _Out_ BOOL* needsReset);

        wil::unique_hmodule dll(::ExportLoader::Load(L"appxdeploymentclient.dll"));
        auto msixPackageVolumeIsRepairNeeded{ ::ExportLoader::GetFunction<MsixPackageVolumeIsRepairNeededFunction>(dll.get(), "MsixPackageVolumeIsRepairNeeded") };
        BOOL isRepairNeeded{};
        THROW_IF_FAILED(msixPackageVolumeIsRepairNeeded(m_packageStorePath.c_str(), &isRepairNeeded));
        return !!isRepairNeeded;
    }

    void PackageVolume::Repair()
    {
        // extern "C" HRESULT WINAPI MsixPackageVolumeRepair(_In_ PCWSTR packageVolumePath);
        typedef HRESULT (WINAPI* MsixPackageVolumeRepairFunction)(_In_ PCWSTR packageVolumePath);

        wil::unique_hmodule dll(::ExportLoader::Load(L"appxdeploymentclient.dll"));
        auto msixPackageVolumeRepair{ ::ExportLoader::GetFunction<MsixPackageVolumeRepairFunction>(dll.get(), "MsixPackageVolumeRepair") };
        THROW_IF_FAILED(msixPackageVolumeRepair(m_packageStorePath.c_str()));
    }

    bool PackageVolume::IsOffline()
    {
        return m_isOffline;
    }

    void PackageVolume::SetDefault()
    {
        THROW_HR_IF_NULL(E_ILLEGAL_METHOD_CALL, m_windowsPackageVolume);

        winrt::Windows::Management::Deployment::PackageManager packageManager;
        packageManager.SetDefaultPackageVolume(m_windowsPackageVolume);
    }

    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageVolume::RemoveAsync()
    {
        THROW_HR_IF_NULL(E_ILLEGAL_METHOD_CALL, m_windowsPackageVolume);

        auto logTelemetry{ PackageVolumeTelemetry::Remove::Start(m_mountPoint, m_name, m_packageStorePath) };

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

        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        try
        {
            error = LOG_IF_FAILED_MSG(Remove(packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                      "ExtendedError:0x%08X PackageVolume.Remove MountPoint:%ls Name:%ls PackageStorePath:%ls",
                                      extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
        }
        catch (...)
        {
            const auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            error = LOG_HR_MSG(exception.code(),
                               "ExtendedError:0x%08X PackageVolume.Remove MountPoint:%ls Name:%ls PackageStorePath:%ls",
                               extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
        }
        if (FAILED(error))
        {
            co_return winrt::make<PackageDeploymentResult>(
                PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
        }

        logTelemetry.Stop(static_cast<HRESULT>(S_OK));
        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);
    }

    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageVolume::SetOfflineAsync()
    {
        THROW_HR_IF_NULL(E_ILLEGAL_METHOD_CALL, m_windowsPackageVolume);

        auto logTelemetry{ PackageVolumeTelemetry::SetOffline::Start(m_mountPoint, m_name, m_packageStorePath) };

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

        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        try
        {
            error = LOG_IF_FAILED_MSG(SetOnline(false, packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                      "ExtendedError:0x%08X PackageVolume.SetOffline MountPoint:%ls Name:%ls PackageStorePath:%ls",
                                      extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
        }
        catch (...)
        {
            const auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            error = LOG_HR_MSG(exception.code(),
                               "ExtendedError:0x%08X PackageVolume.SetOffline MountPoint:%ls Name:%ls PackageStorePath:%ls",
                               extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
        }
        if (FAILED(error))
        {
            co_return winrt::make<PackageDeploymentResult>(
                PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
        }

        logTelemetry.Stop(static_cast<HRESULT>(S_OK));
        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);
    }

    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> PackageVolume::SetOnlineAsync()
    {
        THROW_HR_IF_NULL(E_ILLEGAL_METHOD_CALL, m_windowsPackageVolume);

        auto logTelemetry{ PackageVolumeTelemetry::SetOnline::Start(m_mountPoint, m_name, m_packageStorePath) };

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

        HRESULT error{};
        HRESULT extendedError{};
        winrt::hstring errorText;
        winrt::guid activityId{};
        try
        {
            error = LOG_IF_FAILED_MSG(SetOnline(true, packageDeploymentProgress, progress, extendedError, errorText, activityId),
                                      "ExtendedError:0x%08X PackageVolume.SetOnline MountPoint:%ls Name:%ls PackageStorePath:%ls",
                                      extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
        }
        catch (...)
        {
            const auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            error = LOG_HR_MSG(exception.code(),
                               "ExtendedError:0x%08X PackageVolume.SetOnline MountPoint:%ls Name:%ls PackageStorePath:%ls",
                               extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
        }
        if (FAILED(error))
        {
            co_return winrt::make<PackageDeploymentResult>(
                PackageDeploymentStatus::CompletedFailure, activityId, error, extendedError, errorText);
        }

        logTelemetry.Stop(static_cast<HRESULT>(S_OK));
        co_return winrt::make<PackageDeploymentResult>(PackageDeploymentStatus::CompletedSuccess, activityId);
    }

    winrt::Windows::Foundation::IAsyncOperation<uint64_t> PackageVolume::GetAvailableSpaceAsync()
    {
        THROW_HR_IF_NULL(E_ILLEGAL_METHOD_CALL, m_windowsPackageVolume);

        auto logTelemetry{ PackageVolumeTelemetry::GetAvailableSpace::Start(m_mountPoint, m_name, m_packageStorePath) };

        auto strong{ get_strong() };

        auto cancellation{ co_await winrt::get_cancellation_token() };
        cancellation.enable_propagation(true);

        uint64_t availableSpace{};
        availableSpace = co_await m_windowsPackageVolume.GetAvailableSpaceAsync();

        logTelemetry.Stop(availableSpace);
        co_return availableSpace;
    }

    HRESULT PackageVolume::Remove(
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
        wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
        HRESULT& extendedError,
        winrt::hstring& errorText,
        winrt::guid& activityId)
    {
        extendedError = S_OK;
        errorText.clear();
        activityId = winrt::guid{};

        winrt::Windows::Management::Deployment::PackageManager packageManager;
        auto deploymentOperation{ packageManager.RemovePackageVolumeAsync(m_windowsPackageVolume) };
        deploymentOperation.Progress([&](winrt::Windows::Foundation::IAsyncOperationWithProgress<
                                            winrt::Windows::Management::Deployment::DeploymentResult,
                                            winrt::Windows::Management::Deployment::DeploymentProgress> const& /*sender*/,
                                         winrt::Windows::Management::Deployment::DeploymentProgress const& progressInfo)
        {
            packageDeploymentProgress.Progress = progressInfo.percentage;
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
                                     "ExtendedError:0x%08X PackageVolume.Remove MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                                     extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());

                // Status=Error but SUCCEEDED(error) == This.Should.Never.Happen.
                FAIL_FAST_HR_MSG(E_UNEXPECTED,
                                 "ExtendedError:0x%08X PackageVolume.Remove MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                                 extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());
            }
            else if (status == winrt::Windows::Foundation::AsyncStatus::Canceled)
            {
                RETURN_WIN32_MSG(ERROR_CANCELLED,
                                 "PackageVolume.Remove MountPoint:%ls Name:%ls PackageStorePath:%ls",
                                 m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
            }
            FAIL_FAST_HR_IF_MSG(E_UNEXPECTED, status != winrt::Windows::Foundation::AsyncStatus::Completed,
                                "Status:%d PackageVolume.Remove MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                                static_cast<int32_t>(status), m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());
        }
        catch (...)
        {
            auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            THROW_HR_MSG(exception.code(),
                         "ExtendedError:0x%08X PackageVolume.Remove MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                         extendedError, m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());
        }
        return S_OK;
    }

    HRESULT PackageVolume::SetOnline(
        const bool online,
        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
        wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
        HRESULT& extendedError,
        winrt::hstring& errorText,
        winrt::guid& activityId)
    {
        extendedError = S_OK;
        errorText.clear();
        activityId = winrt::guid{};

        winrt::Windows::Management::Deployment::PackageManager packageManager;
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Management::Deployment::DeploymentResult, winrt::Windows::Management::Deployment::DeploymentProgress> deploymentOperation;
        if (online)
        {
            deploymentOperation = packageManager.SetPackageVolumeOnlineAsync(m_windowsPackageVolume);
        }
        else
        {
            deploymentOperation = packageManager.SetPackageVolumeOfflineAsync(m_windowsPackageVolume);
        }
        deploymentOperation.Progress([&](winrt::Windows::Foundation::IAsyncOperationWithProgress<
                                            winrt::Windows::Management::Deployment::DeploymentResult,
                                            winrt::Windows::Management::Deployment::DeploymentProgress> const& /*sender*/,
                                         winrt::Windows::Management::Deployment::DeploymentProgress const& progressInfo)
        {
            packageDeploymentProgress.Progress = progressInfo.percentage;
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
                                     "ExtendedError:0x%08X PackageVolume.Set%hs MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                                     extendedError, online ? "Online" : "Offline", m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());

                // Status=Error but SUCCEEDED(error) == This.Should.Never.Happen.
                FAIL_FAST_HR_MSG(E_UNEXPECTED,
                                 "ExtendedError:0x%08X PackageVolume.Set%hs MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                                 extendedError, online ? "Online" : "Offline", m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());
            }
            else if (status == winrt::Windows::Foundation::AsyncStatus::Canceled)
            {
                RETURN_WIN32_MSG(ERROR_CANCELLED,
                                 "PackageVolume.Set%hs MountPoint:%ls Name:%ls PackageStorePath:%ls",
                                 online ? "Online" : "Offline", m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str());
            }
            FAIL_FAST_HR_IF_MSG(E_UNEXPECTED, status != winrt::Windows::Foundation::AsyncStatus::Completed,
                                "Status:%d PackageVolume.Set%hs MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                                static_cast<int32_t>(status), online ? "Online" : "Offline", m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());
        }
        catch (...)
        {
            auto exception{ hresult_error(to_hresult(), take_ownership_from_abi) };
            THROW_HR_MSG(exception.code(),
                         "ExtendedError:0x%08X PackageVolume.Set%hs MountPoint:%ls Name:%ls PackageStorePath:%ls : %ls",
                         extendedError, online ? "Online" : "Offline", m_mountPoint.c_str(), m_name.c_str(), m_packageStorePath.c_str(), errorText.c_str());
        }
        return S_OK;
    }
}
