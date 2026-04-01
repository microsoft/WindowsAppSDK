// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageVolume.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageVolume : PackageVolumeT<PackageVolume>
    {
        PackageVolume() = default;
        PackageVolume(winrt::Windows::Management::Deployment::PackageVolume const& value);

        static bool IsFeatureSupported(winrt::Microsoft::Windows::Management::Deployment::PackageVolumeFeature feature);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> FindPackageVolumes();
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume FindPackageVolumeByPath(hstring const& packageStorePath);
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume GetPackageVolumeByPath(hstring const& path);
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume FindPackageVolumeByName(hstring const& name);
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume GetPackageVolumeByName(hstring const& name);
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume GetDefault();
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> AddAsync(hstring packageStorePath);

        bool IsSystemVolume();
        hstring MountPoint();
        hstring Name();
        hstring PackageStorePath();
        bool SupportsHardLinks();
        bool IsAppxInstallSupported();
        bool IsFullTrustPackageSupported();
        bool IsRepairNeeded();
        void Repair();
        bool IsOffline();
        void SetDefault();
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> RemoveAsync();
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> SetOfflineAsync();
        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> SetOnlineAsync();
        winrt::Windows::Foundation::IAsyncOperation<uint64_t> GetAvailableSpaceAsync();

    private:
        HRESULT Remove(
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);

        HRESULT SetOnline(
            const bool online,
            winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress& packageDeploymentProgress,
            wistd::function<void(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress)> progress,
            HRESULT& extendedError,
            winrt::hstring& errorText,
            winrt::guid& activityId);

    private:
        winrt::Windows::Management::Deployment::PackageVolume m_windowsPackageVolume{ nullptr };
        bool m_isSystemVolume{};
        hstring m_mountPoint;
        hstring m_name;
        hstring m_packageStorePath;
        bool m_supportsHardLinks{};
        bool m_isAppxInstallSupported{};
        bool m_isFullTrustPackageSupported{};
        bool m_isOffline{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageVolume : PackageVolumeT<PackageVolume, implementation::PackageVolume>
    {
    };
}
