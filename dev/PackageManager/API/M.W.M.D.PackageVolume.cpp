// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageVolume.h"
#include "Microsoft.Windows.Management.Deployment.PackageVolume.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageVolume::PackageVolume(winrt::Windows::Management::Deployment::PackageVolume const& value)
    {
        IsSystemVolume(value.IsSystemVolume());
        MountPoint(value.MountPoint());
        Name(value.Name());
        PackageStorePath(value.PackageStorePath());
        SupportsHardLinks(value.SupportsHardLinks());
        IsFullTrustPackageSupported(value.IsFullTrustPackageSupported());
        IsAppxInstallSupported(value.IsAppxInstallSupported());
    }
    bool PackageVolume::IsSystemVolume()
    {
        return m_isSystemVolume;
    }
    void PackageVolume::IsSystemVolume(bool value)
    {
        m_isSystemVolume = value;
    }
    hstring PackageVolume::MountPoint()
    {
        return m_mountPoint;
    }
    void PackageVolume::MountPoint(hstring const& value)
    {
        m_mountPoint = value;
    }
    hstring PackageVolume::Name()
    {
        return m_name;
    }
    void PackageVolume::Name(hstring const& value)
    {
        m_name = value;
    }
    hstring PackageVolume::PackageStorePath()
    {
        return m_packageStorePath;
    }
    void PackageVolume::PackageStorePath(hstring const& value)
    {
        m_packageStorePath = value;
    }
    bool PackageVolume::SupportsHardLinks()
    {
        return m_supportsHardLinks;
    }
    void PackageVolume::SupportsHardLinks(bool value)
    {
        m_supportsHardLinks = value;
    }
    bool PackageVolume::IsFullTrustPackageSupported()
    {
        return m_isFullTrustPackageSupported;
    }
    void PackageVolume::IsFullTrustPackageSupported(bool value)
    {
        m_isFullTrustPackageSupported = value;
    }
    bool PackageVolume::IsAppxInstallSupported()
    {
        return m_isAppxInstallSupported;
    }
    void PackageVolume::IsAppxInstallSupported(bool value)
    {
        m_isAppxInstallSupported = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolumeStatus PackageVolume::Status()
    {
        throw hresult_not_implemented();
    }
    void PackageVolume::FixMe()
    {
        throw hresult_not_implemented();
    }
}
