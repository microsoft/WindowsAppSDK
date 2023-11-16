// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageVolume.h"
#include "Microsoft.Windows.Management.Deployment.PackageVolume.g.cpp"
#include <frameworkudk/AppxPackageVolumeReset.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageVolume::PackageVolume(winrt::Windows::Management::Deployment::PackageVolume const& value)
    {
        m_isSystemVolume = value.IsSystemVolume();
        m_mountPoint = value.MountPoint();
        m_name = value.Name();
        m_packageStorePath = value.PackageStorePath();
        m_supportsHardLinks = value.SupportsHardLinks();
        m_isFullTrustPackageSupported = value.IsFullTrustPackageSupported();
        m_isAppxInstallSupported = value.IsAppxInstallSupported();
        //TODO m_packageStatus = value.Status();
    }
    bool PackageVolume::IsSystemVolume()
    {
        return m_isSystemVolume;
    }
    hstring PackageVolume::MountPoint()
    {
        return m_mountPoint;
    }
    hstring PackageVolume::Name()
    {
        return m_name;
    }
    hstring PackageVolume::PackageStorePath()
    {
        return m_packageStorePath;
    }
    bool PackageVolume::SupportsHardLinks()
    {
        return m_supportsHardLinks;
    }
    bool PackageVolume::IsFullTrustPackageSupported()
    {
        return m_isFullTrustPackageSupported;
    }
    bool PackageVolume::IsAppxInstallSupported()
    {
        return m_isAppxInstallSupported;
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolumeStatus PackageVolume::Status()
    {
        throw hresult_not_implemented();
    }
    bool PackageVolume::CheckReset()
    {
        bool needsReset{};
        THROW_IF_FAILED(AppxPackageVolumeReset_CheckDeviceForAppReset(Name().c_str(), &needsReset)); // use PackageStorePath instead of Name?
        return needsReset;
    }
    void PackageVolume::Reset()
    {
        THROW_IF_FAILED(AppxPackageVolumeReset_Reset(Name().c_str()));
    }
}
