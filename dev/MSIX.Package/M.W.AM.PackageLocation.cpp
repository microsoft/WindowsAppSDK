// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageLocation.h"

#include "Microsoft.Windows.ApplicationModel.PackageLocation.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageLocation::PackageLocation(winrt::Microsoft::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    hstring PackageLocation::Path()
    {
        return EffectivePath();
    }
    winrt::Windows::Storage::StorageFolder PackageLocation::Location()
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
    winrt::Windows::Storage::StorageFolder PackageLocation::InstalledLocation()
    {
        return m_package.W_AM_Package().InstalledLocation();
    }
    winrt::Windows::Storage::StorageFolder PackageLocation::MutableLocation()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder PackageLocation::EffectiveLocation()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder PackageLocation::EffectiveExternalLocation()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder PackageLocation::UserEffectiveExternalLocation()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder PackageLocation::MachineEffectiveExternalLocation()
    {
        throw hresult_not_implemented();
    }
}
