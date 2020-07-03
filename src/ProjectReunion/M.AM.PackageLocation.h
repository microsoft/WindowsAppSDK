#pragma once
#include "Microsoft.ApplicationModel.PackageLocation.g.h"

namespace winrt::Microsoft::ApplicationModel::implementation
{
    struct PackageLocation : PackageLocationT<PackageLocation>
    {
        PackageLocation() = default;

        PackageLocation(Microsoft::ApplicationModel::Package const& package);
        hstring Path();
        Windows::Storage::StorageFolder Location();
        hstring InstalledPath();
        void InstalledPath(hstring const& value);
        hstring MutablePath();
        void MutablePath(hstring const& value);
        hstring EffectivePath();
        void EffectivePath(hstring const& value);
        hstring EffectiveExternalPath();
        void EffectiveExternalPath(hstring const& value);
        hstring UserEffectiveExternalPath();
        void UserEffectiveExternalPath(hstring const& value);
        hstring MachineEffectiveExternalPath();
        void MachineEffectiveExternalPath(hstring const& value);
        Windows::Storage::StorageFolder InstalledLocation();
        void InstalledLocation(Windows::Storage::StorageFolder const& value);
        Windows::Storage::StorageFolder MutableLocation();
        void MutableLocation(Windows::Storage::StorageFolder const& value);
        Windows::Storage::StorageFolder EffectiveLocation();
        void EffectiveLocation(Windows::Storage::StorageFolder const& value);
        Windows::Storage::StorageFolder EffectiveExternalLocation();
        void EffectiveExternalLocation(Windows::Storage::StorageFolder const& value);
        Windows::Storage::StorageFolder UserEffectiveExternalLocation();
        void UserEffectiveExternalLocation(Windows::Storage::StorageFolder const& value);
        Windows::Storage::StorageFolder MachineEffectiveExternalLocation();
        void MachineEffectiveExternalLocation(Windows::Storage::StorageFolder const& value);

    private:
        Microsoft::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::ApplicationModel::factory_implementation
{
    struct PackageLocation : PackageLocationT<PackageLocation, implementation::PackageLocation>
    {
    };
}
