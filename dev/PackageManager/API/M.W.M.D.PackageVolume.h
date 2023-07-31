// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageVolume.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageVolume : PackageVolumeT<PackageVolume>
    {
        PackageVolume() = default;

        bool IsOffline();
        void IsOffline(bool value);
        bool IsSystemVolume();
        void IsSystemVolume(bool value);
        hstring MountPoint();
        void MountPoint(hstring const& value);
        hstring Name();
        void Name(hstring const& value);
        hstring PackageStorePath();
        void PackageStorePath(hstring const& value);
        bool SupportsHardLinks();
        void SupportsHardLinks(bool value);
        bool IsFullTrustPackageSupported();
        void IsFullTrustPackageSupported(bool value);
        bool IsAppxInstallSupported();
        void IsAppxInstallSupported(bool value);

    private:
        bool m_isOffline{};
        bool m_isSystemVolume{};
        hstring m_mountPoint;
        hstring m_name;
        hstring m_packageStorePath;
        bool m_supportsHardLinks{};
        bool m_isFullTrustPackageSupported{};
        bool m_isAppxInstallSupported{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageVolume : PackageVolumeT<PackageVolume, implementation::PackageVolume>
    {
    };
}
