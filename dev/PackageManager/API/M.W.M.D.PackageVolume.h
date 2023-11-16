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

        bool IsSystemVolume();
        hstring MountPoint();
        hstring Name();
        hstring PackageStorePath();
        bool SupportsHardLinks();
        bool IsFullTrustPackageSupported();
        bool IsAppxInstallSupported();
        winrt::Microsoft::Windows::Management::Deployment::PackageVolumeStatus Status();
        bool CheckReset();
        void Reset();

    private:
        bool m_isSystemVolume{};
        hstring m_mountPoint;
        hstring m_name;
        hstring m_packageStorePath;
        bool m_supportsHardLinks{};
        bool m_isFullTrustPackageSupported{};
        bool m_isAppxInstallSupported{};
        //TODO winrt::Microsoft::Windows::Management::Deployment::PackageVolumeStatus m_status{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageVolume : PackageVolumeT<PackageVolume, implementation::PackageVolume>
    {
    };
}
