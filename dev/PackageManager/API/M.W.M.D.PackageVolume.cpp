// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageVolume.h"
#include "Microsoft.Windows.Management.Deployment.PackageVolume.g.cpp"

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
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> PackageVolume::FindPackageVolumes()
    {
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume> microsoftPackageVolumes{ winrt::single_threaded_vector<winrt::Microsoft::Windows::Management::Deployment::PackageVolume>() };

        winrt::Windows::Management::Deployment::PackageManager packageManager;
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Management::Deployment::PackageVolume> windowsPackageVolumes{ packageManager.FindPackageVolumes() };
        for (winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume : windowsPackageVolumes)
        {
            auto microsoftPackageVolume{ winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageVolume>(windowsPackageVolume) };
            microsoftPackageVolumes.Append(microsoftPackageVolume);
        }
        return microsoftPackageVolumes;
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume PackageVolume::FindPackageVolumeByPath(hstring const& path)
    {
        const auto c_volumePathNameMaxLength{ MAX_PATH };
        wchar_t volumePathName[c_volumePathNameMaxLength]{};//AKA volumeMountPoint
        THROW_IF_WIN32_BOOL_FALSE_MSG(::GetVolumePathNameW(path.c_str(), volumePathName, ARRAYSIZE(volumePathName)), "Path:%ls", path.c_str());
        GUID mediaId{};
        const size_t c_volumeNameMaxLength{ 50 };   // "\\?\Volume{GUID}\" == 11 + 11111111-2222-3333-4444-555555555555 + 2 + null-terminator == 11 + 36 + 3 = 50
        wchar_t volumeName[c_volumeNameMaxLength]{};
        THROW_IF_WIN32_BOOL_FALSE_MSG(::GetVolumeNameForVolumeMountPoint(volumePathName, volumeName, ARRAYSIZE(volumeName)), "Path:%ls VolumePathName:%ls", path.c_str(), volumePathName);
        const auto volumeNameLength{ wcslen(volumeName) };
        THROW_HR_IF_MSG(E_UNEXPECTED, volumeNameLength == 0, "Path:%ls VolumePathName:%ls", path.c_str(), volumePathName);
        const auto offset{ volumeNameLength - 1 };
        if (volumeName[offset] == L'\\')
        {
            volumeName[offset] = L'\0';
        }
        return FindPackageVolumeByName(winrt::hstring{ volumeName });
    }
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume PackageVolume::FindPackageVolumeByName(hstring const& name)
    {
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume{ packageManager.FindPackageVolume(mediaId) };
        return winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageVolume>(windowsPackageVolume);
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
    bool PackageVolume::IsRepairNeeded()
    {
        throw hresult_not_implemented();
    }
    void PackageVolume::Repair()
    {
        throw hresult_not_implemented();
    }
}
