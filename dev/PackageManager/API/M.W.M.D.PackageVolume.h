// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageVolume.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageVolume : PackageVolumeT<PackageVolume>
    {
        PackageVolume() = delete;
        PackageVolume(winrt::Windows::Management::Deployment::PackageVolume const& value);

        bool IsSystemVolume();
        hstring MountPoint();
        hstring Name();
        hstring PackageStorePath();
        bool SupportsHardLinks();
        bool IsFullTrustPackageSupported();
        bool IsAppxInstallSupported();
        bool IsRepairNeeded();
        void Repair();

    private:
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
