// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <shlobj_core.h>

#include <winrt/Windows.Management.Core.h>

#include "UnpackagedApplicationData.h"

#include "ApplicationDataTelemetry.h"

namespace Microsoft::Windows::Storage
{
    UnpackagedApplicationData::UnpackagedApplicationData(winrt::hstring const& publisher, winrt::hstring const& product) :
        m_publisher(publisher),
        m_product(product),
        m_localPath(),
        m_machinePath()
    {
    }
    bool UnpackagedApplicationData::IsMachinePathSupported()
    {
        const auto path{ _MachinePath(m_publisher, m_product) };
        return !path.empty();
    }
    winrt::hstring UnpackagedApplicationData::LocalCachePath()
    {
        // ApplicationData.LocalCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    winrt::hstring UnpackagedApplicationData::LocalPath()
    {
        if (m_localPath.empty())
        {
            wil::unique_cotaskmem_string localAppData;
            //TODO FOLDERID_LocalAppDataLow
            THROW_IF_FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT /*TODO KF_FLAG_CREATE | KF_FLAG_DONT_VERIFY*/, nullptr, wil::out_param(localAppData)));
            std::filesystem::path path{ localAppData.get() };
            path /= m_publisher.c_str();
            path /= m_product.c_str();
            m_localPath = path.c_str();
        }
        return m_localPath;
    }
    winrt::hstring UnpackagedApplicationData::MachinePath()
    {
        const auto path{ _MachinePath(m_publisher, m_product) };
        return winrt::hstring{ path.c_str() };
    }
    winrt::hstring UnpackagedApplicationData::SharedLocalPath()
    {
        // ApplicationData.SharedLocalFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    winrt::hstring UnpackagedApplicationData::TemporaryPath()
    {
        throw winrt::hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::LocalCacheFolder()
    {
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(LocalCachePath()).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::LocalFolder()
    {
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(LocalPath()).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::MachineFolder()
    {
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(MachinePath()).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::SharedLocalFolder()
    {
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(SharedLocalPath()).get();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::TemporaryFolder()
    {
        return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(TemporaryPath()).get();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer UnpackagedApplicationData::LocalSettings()
    {
        throw winrt::hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction UnpackagedApplicationData::ClearAsync(winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality)
    {
        throw winrt::hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction UnpackagedApplicationData::ClearPublisherCacheFolderAsync(winrt::hstring folderName)
    {
        // ApplicationData.PublisherCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    void UnpackagedApplicationData::Close()
    {
        throw winrt::hresult_not_implemented();
    }
    winrt::hstring UnpackagedApplicationData::GetPublisherCachePath(winrt::hstring const& folderName)
    {
        // ApplicationData.PublisherCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    winrt::Windows::Storage::StorageFolder UnpackagedApplicationData::GetPublisherCacheFolder(winrt::hstring const& folderName)
    {
        // ApplicationData.PublisherCacheFolder has no unpackaged equivalent
        throw winrt::hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction UnpackagedApplicationData::ClearMachineFolderAsync()
    {
        throw winrt::hresult_not_implemented();
    }
    std::filesystem::path UnpackagedApplicationData::_MachinePath(winrt::hstring const& publisher, winrt::hstring const& product)
    {
        // Path = %ProgramData%\...publisher...\...product...
        wil::unique_cotaskmem_string programData;
        THROW_IF_FAILED(SHGetKnownFolderPath(FOLDERID_AppDataProgramData, KF_FLAG_DEFAULT /*TODO KF_FLAG_CREATE | KF_FLAG_DONT_VERIFY*/, nullptr, wil::out_param(programData)));
        std::filesystem::path path{ programData.get() };
        path /= publisher.c_str();
        path /= product.c_str();

        // Does it exist?
        if (_PathExists(path))
        {
            return path;
        }
        return std::filesystem::path{};
    }

    bool UnpackagedApplicationData::_PathExists(std::filesystem::path const& path)
    {
        const std::filesystem::directory_entry directoryEntry{ path };
        return directoryEntry.is_directory();
    }
}
