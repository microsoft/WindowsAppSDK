#include "pch.h"

#include "M.AM.PackageLocation.h"

namespace winrt::Microsoft::ApplicationModel::implementation
{
    PackageLocation::PackageLocation(Microsoft::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    hstring PackageLocation::Path()
    {
        return EffectivePath();
    }
    Windows::Storage::StorageFolder PackageLocation::Location()
    {
        return EffectiveLocation();
    }
    hstring PackageLocation::InstalledPath()
    {
        throw hresult_not_implemented();
    }
    hstring PackageLocation::MutablePath()
    {
        throw hresult_not_implemented();
    }
    hstring PackageLocation::EffectivePath()
    {
        throw hresult_not_implemented();
    }
    hstring PackageLocation::EffectiveExternalPath()
    {
        throw hresult_not_implemented();
    }
    hstring PackageLocation::UserEffectiveExternalPath()
    {
        throw hresult_not_implemented();
    }
    hstring PackageLocation::MachineEffectiveExternalPath()
    {
        throw hresult_not_implemented();
    }
    Windows::Storage::StorageFolder PackageLocation::InstalledLocation()
    {
        return m_package.W_AM_Package().InstalledLocation();
    }
    Windows::Storage::StorageFolder PackageLocation::MutableLocation()
    {
        throw hresult_not_implemented();
    }
    Windows::Storage::StorageFolder PackageLocation::EffectiveLocation()
    {
        throw hresult_not_implemented();
    }
    Windows::Storage::StorageFolder PackageLocation::EffectiveExternalLocation()
    {
        throw hresult_not_implemented();
    }
    Windows::Storage::StorageFolder PackageLocation::UserEffectiveExternalLocation()
    {
        throw hresult_not_implemented();
    }
    Windows::Storage::StorageFolder PackageLocation::MachineEffectiveExternalLocation()
    {
        throw hresult_not_implemented();
    }
}
