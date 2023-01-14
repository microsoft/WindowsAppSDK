// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageLocation.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageLocation : PackageLocationT<PackageLocation>
    {
        PackageLocation() = default;

        PackageLocation(winrt::Microsoft::Windows::ApplicationModel::Package const& package);
        hstring Path();
        winrt::Windows::Storage::StorageFolder Location();
        hstring InstalledPath();
        hstring MutablePath();
        hstring EffectivePath();
        hstring EffectiveExternalPath();
        hstring UserEffectiveExternalPath();
        hstring MachineEffectiveExternalPath();
        winrt::Windows::Storage::StorageFolder InstalledLocation();
        winrt::Windows::Storage::StorageFolder MutableLocation();
        winrt::Windows::Storage::StorageFolder EffectiveLocation();
        winrt::Windows::Storage::StorageFolder EffectiveExternalLocation();
        winrt::Windows::Storage::StorageFolder UserEffectiveExternalLocation();
        winrt::Windows::Storage::StorageFolder MachineEffectiveExternalLocation();

    private:
        winrt::Microsoft::Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageLocation : PackageLocationT<PackageLocation, implementation::PackageLocation>
    {
    };
}
