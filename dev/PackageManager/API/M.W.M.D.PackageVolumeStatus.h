// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageVolumeStatus.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageVolumeStatus : PackageVolumeStatusT<PackageVolumeStatus>
    {
        PackageVolumeStatus() = default;

        bool IsOK();
        void IsOK(bool value);
        bool IsOffline();
        void IsOffline(bool value);
        bool IsBroken();
        void IsBroken(bool value);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageVolumeStatus : PackageVolumeStatusT<PackageVolumeStatus, implementation::PackageVolumeStatus>
    {
    };
}
