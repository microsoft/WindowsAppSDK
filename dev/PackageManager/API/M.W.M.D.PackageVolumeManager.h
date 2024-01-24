// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageVolumeManager.g.h"
#include "M.W.M.D.PackageVolume.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageVolumeManager
    {
        PackageVolumeManager() = default;

        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> FindPackageVolumes();
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume FindPackageVolumeByPath(hstring const& path);
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume FindPackageVolumeByMediaId(hstring const& mediaId);
        static winrt::Microsoft::Windows::Management::Deployment::PackageVolume FindPackageVolumeByName(hstring const& name);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageVolumeManager : PackageVolumeManagerT<PackageVolumeManager, implementation::PackageVolumeManager>
    {
    };
}
